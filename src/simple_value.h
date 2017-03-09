
#ifndef DMS_SIMPLE_VALUE_H__
#define DMS_SIMPLE_VALUE_H__

#include <value.h>

namespace dms {

class SimpleValue : public Value {
 public:
  SimpleValue(dms_field* field, ByteArray* buffer);
  virtual ~SimpleValue();

  // init the value
  virtual int Init();

  // set the position of the value in the owner instance buffer.
  virtual int SetPosition(int position);

  // clear the content of the value
  virtual int Clear();

  // set the char value
  int SetChar(char value);

  // set the short value
  int SetShort(short value);

  // set the int value
  int SetInt(int value);

  // set the long value
  int SetLong(long long value);

  // set the float value
  int SetFloat(float value);

  // set the double value
  int SetDouble(double value);

  // set the sting value
  int SetString(const char* value, int size);

  // get the char value
  int GetChar(char* o_value) const;

  // get the short value
  int GetShort(short* o_value) const;

  // get the int value
  int GetInt(int* o_value) const;

  // get the long value
  int GetLong(long long* o_value) const;

  // get the float value
  int GetFloat(float* o_value) const;

  // get the double value
  int GetDouble(double* o_value) const;

  // get the sting value
  int GetString(const char** o_value, int* o_size) const;

private:
  // the value type
  int type_;
  // the value
  dms_value simple_value_;

  // Disable copying of Value
  DMS_DISALLOW_CONSTRUCTORS(SimpleValue);
};

inline int SimpleValue::SetChar(char value) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_CHAR, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  return buffer_->Write<char>(position_, value);
}

inline int SimpleValue::SetShort(short value) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_SHORT, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  return buffer_->Write<short>(position_, value);
}

inline int SimpleValue::SetInt(int value) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_INT, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  return buffer_->Write<int>(position_, value);
}

inline int SimpleValue::SetLong(long long value) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_LONG, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  return buffer_->Write<long long>(position_, value);
}

inline int SimpleValue::SetFloat(float value) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_FLOAT, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  return buffer_->Write<float>(position_, value);
}

inline int SimpleValue::SetDouble(double value) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_DOUBLE, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  return buffer_->Write<double>(position_, value);
}

inline int SimpleValue::SetString(const char* value, int size) {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_STRING, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  // read current capacity
  int capacity = 0;
  uint8_t* target = NULL;
  int offset = 0;
  DMS_CHECK_RESULT(buffer_->Read<int>(position_, &offset));
  if (offset > 0) {
    target = buffer_->begin() + offset;
    uint8_t byte0 = *target;
    bool has_capacity = ((byte0 & 0x80) > 0);
    if (has_capacity) {
      memcpy_s(&capacity, sizeof(int), target + sizeof(int), sizeof(int));
      capacity += 2 * sizeof(int);
    } else {
      memcpy_s(&capacity, sizeof(int), target, sizeof(int));
      capacity += sizeof(int);
    }
  }
  // calculate the new size
  bool with_capacity = capacity > size + 2 * sizeof(int);
  int required_size = with_capacity ? size + 2 * sizeof(int) :
    size + sizeof(int);
  if (required_size > capacity) {
    if (NULL != target) {
      memset(target, 0, capacity);
    }
    const int offset = buffer_->size();
    target = buffer_->Increment(required_size);
    DMS_CHECK_RESULT(buffer_->Write<int>(position_, offset));
    capacity = required_size;
  }
  if (with_capacity) {
    uint32_t flaged = (size | (1 << 31));
    memcpy_s(target, sizeof(int), &flaged, sizeof(int));
    target += sizeof(int);
    memcpy_s(target, sizeof(int), &capacity, sizeof(int));
    target += sizeof(int);
  } else {
    memcpy_s(target, sizeof(int), &size, sizeof(int));
    target += sizeof(int);
  }
  if (size > 0) {
    memcpy_s(target, size, value, size);
  }
  return 0;
}

inline int SimpleValue::GetChar(char* o_value) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_CHAR, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(buffer_->Read<char>(position_, o_value));
  return 0;
}

inline int SimpleValue::GetShort(short* o_value) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_SHORT, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(buffer_->Read<short>(position_, o_value));
  return 0;
}

inline int SimpleValue::GetInt(int* o_value) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_INT, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(buffer_->Read<int>(position_, o_value));
  return 0;
}

inline int SimpleValue::GetLong(long long* o_value) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_LONG, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(buffer_->Read<long long>(position_, o_value));
  return 0;
}

inline int SimpleValue::GetFloat(float* o_value) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_FLOAT, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(buffer_->Read<float>(position_, o_value));
  return 0;
}

inline int SimpleValue::GetDouble(double* o_value) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_DOUBLE, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  DMS_CHECK_RESULT(buffer_->Read<double>(position_, o_value));
  return 0;
}

inline int SimpleValue::GetString(const char** o_value, int* o_size) const {
  DMS_CHECK_RETURN(type_ == DMS_TYPE_STRING, DMS_INVALID);
  DMS_CHECK_RETURN(position_ >= 0, DMS_INVALID);
  // read the offset
  int offset = 0;
  DMS_CHECK_RESULT(buffer_->Read<int>(position_, &offset));
  if (offset <= 0) {
    *o_size = 0;
    return 0;
  }
  uint8_t* target = buffer_->begin() + offset;
  uint8_t byte0 = *target;
  bool has_capacity = ((byte0 & 0x80) > 0);
  int size = 0;
  memcpy_s(&size, sizeof(int), target, sizeof(int));
  if (has_capacity) {
    size = (size & 0x7FFFFFFF);
    target += 2 * sizeof(int);
  } else {
    target += sizeof(int);
  }
  *o_size = size;
  *o_value = reinterpret_cast<char*>(target);
  return 0;
}

} // namespace dms

#endif // DMS_SIMPLE_VALUE_H__