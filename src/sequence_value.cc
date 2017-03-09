
#include <sequence_value.h>

namespace dms {

SequenceValue::SequenceValue(dms_seq_field* seq_field, ByteArray* buffer) 
  : Value(buffer)
  , current_(0)
  , element_value_(NULL) {
  seq_value_.base.base_field = &seq_field->base;
  memcpy_s(seq_value_.base.sys_data, sizeof(seq_value_.base.sys_data),
    this, sizeof(this));
  value_ = &seq_value_.base;
}

SequenceValue::~SequenceValue() {
  if (NULL != element_value_) {
    delete element_value_;
    element_value_ = NULL;
  }
}

int SequenceValue::Init() {
  fixed_size_ = sizeof(int);
  dms_seq_field* seq_field = reinterpret_cast<dms_seq_field*>(
    seq_value_.base.base_field);
  element_value_ = DoCreateValue(seq_field->element_field, buffer_);
  DMS_CHECK_RESULT(element_value_->Init());
  return 0;
}

int SequenceValue::SetPosition(int position) {
  position_ = position;
  current_ = 0;
  // read offset
  int offset = 0;
  DMS_CHECK_RESULT(buffer_->Read<int>(position_, &offset));
  if (offset > 0) {
    // read size
    uint8_t* target = buffer_->begin() + offset;
    uint8_t byte0 = *target;
    bool has_capacity = ((byte0 & 0x80) > 0);
    int size = 0;
    memcpy_s(&size, sizeof(int), target, sizeof(int));
    if (has_capacity) {
      size = (size & 0x7FFFFFFF);
      offset += 2 * sizeof(int);
    } else {
      offset += sizeof(int);
    }
    if (size > 0) {
      DMS_CHECK_RESULT(element_value_->SetPosition(offset));
    } else {
      DMS_CHECK_RESULT(element_value_->Clear());
    }
  } else {
    DMS_CHECK_RESULT(element_value_->Clear());
  }
  return 0;
}

int SequenceValue::Clear() {
  DMS_CHECK_RESULT(element_value_->Clear());
  position_ = -1;
  current_ = 0;
  return 0;
}

int SequenceValue::SetSize(int size) {
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  // read offset
  int offset = 0;
  DMS_CHECK_RESULT(buffer_->Read<int>(position_, &offset));
  // read capacity & size
  int capacity = 0;
  int cur_size = 0;
  uint8_t* target = NULL;
  uint8_t* ctarget = NULL;
  if (offset > 0) {
    // read size
    ctarget = target = buffer_->begin() + offset;
    uint8_t byte0 = *target;
    bool has_capacity = ((byte0 & 0x80) > 0);
    memcpy_s(&cur_size, sizeof(int), target, sizeof(int));
    if (has_capacity) {
      cur_size = (cur_size & 0x7FFFFFFF);
      memcpy_s(&capacity, sizeof(int), target + sizeof(int), sizeof(int));
      capacity += 2 * sizeof(int);
      ctarget += 2 * sizeof(int);
    } else {
      memcpy_s(&capacity, sizeof(int), target, sizeof(int));
      capacity += sizeof(int);
      ctarget += sizeof(int);
    }
  }
  // calculate the new size
  int csize = size * element_value_->fixed_size();
  bool with_capacity = capacity > csize + 2 * sizeof(int);
  int required_size = with_capacity ? csize + 2 * sizeof(int) :
    csize + sizeof(int);
  uint8_t* old_target = target;
  uint8_t* old_ctarget = ctarget;
  int old_capacity = capacity;
  if (required_size > capacity) {
    const int offset = buffer_->size();
    ctarget = target = buffer_->Increment(required_size);
    DMS_CHECK_RESULT(buffer_->Write<int>(position_, offset));
    capacity = required_size;
  }
  if (with_capacity) {
    uint32_t flaged = (size | (1 << 31));
    memcpy_s(ctarget, sizeof(int), &flaged, sizeof(int));
    ctarget += sizeof(int);
    memcpy_s(ctarget, sizeof(int), &capacity, sizeof(int));
    ctarget += sizeof(int);
  } else {
    memcpy_s(ctarget, sizeof(int), &size, sizeof(int));
    ctarget += sizeof(int);
  }
  if (NULL != old_target && cur_size > 0) {
    int old_csize = cur_size * element_value_->fixed_size();
    memcpy_s(ctarget, old_csize, old_ctarget, old_csize);
  }
  if (NULL != old_target) {
    memset(old_target, 0, old_capacity);
  }
  return 0;
}

int SequenceValue::GetSize(int* o_size) const {
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(DoReadSize(o_size));
  return 0;
}

int SequenceValue::SetCurrent(int current) {
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  int size = 0;
  DMS_CHECK_RESULT(DoReadSize(&size));
  DMS_CHECK_RETURN(current < size, DMS_INVALID);
  current_ = current;
  return 0;
}

int SequenceValue::GetCurrent(int* o_current) const {
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  *o_current = current_;
  return 0;
}

int SequenceValue::DoReadSize(int* o_size) const {
  // read offset
  int offset = 0;
  DMS_CHECK_RESULT(buffer_->Read<int>(position_, &offset));
  if (offset > 0) {
    uint8_t* target = buffer_->begin() + offset;
    uint8_t byte0 = *target;
    bool has_capacity = ((byte0 & 0x80) > 0);
    int size = 0;
    memcpy_s(&size, sizeof(int), target, sizeof(int));
    if (has_capacity) {
      size = (size & 0x7FFFFFFF);
    }
    *o_size = size;
  } else {
    *o_size = 0;
  }
  return 0;
}

} // namespace dms