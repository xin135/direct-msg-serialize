
#include <group_value.h>

namespace dms {

GroupValue::GroupValue(dms_group_field* group_field, ByteArray* buffer)
  : Value(buffer) {
  group_value_.base.base_field = &group_field->base;
  memcpy_s(group_value_.base.sys_data, sizeof(group_value_.base.sys_data), 
    this, sizeof(this));
  value_ = &group_value_.base;
}

GroupValue::~GroupValue() {
  std::unordered_map<std::string, Value*>::iterator it;
  for (it = children_.begin(); it != children_.end(); ++it) {
    delete it->second;
  }
  children_.clear();
  value_list_.clear();
}

int GroupValue::Init() {
  // only create once
  if (!children_.empty()) {
    return 0;
  }
  dms_group_field* group_field = reinterpret_cast<dms_group_field*>(
    group_value_.base.base_field);
  fixed_size_ = 0;
  for (int i = 0; i < group_field->num_of_children; ++i) {
    dms_field* child_field = group_field->children[i];
    Value* child_value = DoCreateValue(child_field, buffer_);
    children_[child_field->name] = child_value;
    DMS_CHECK_RESULT(child_value->Init());
    value_list_.push_back(child_value->value());
    fixed_size_ += child_value->fixed_size();
  }
  // populate the children
  group_value_.children = NULL;
  if (!value_list_.empty()) {
    group_value_.children = &value_list_[0];
  }
  return 0;
}

int GroupValue::SetPosition(int position) {
  position_ = position;
  int offset = position_;
  for (size_t i = 0; i < value_list_.size(); ++i) {
    Value* value = *(reinterpret_cast<Value**>(value_list_[i]->sys_data));
    DMS_CHECK_RESULT(value->SetPosition(offset));
    offset += value->fixed_size();
  }
  return 0;
}

int GroupValue::Clear() {
  std::unordered_map<std::string, Value*>::iterator it;
  for (it = children_.begin(); it != children_.end(); ++it) {
    DMS_CHECK_RESULT(it->second->Clear());
  }
  position_ -= -1;
  return 0;
}

int GroupValue::GetChild(const char* child_name, Value** o_child) const {
  std::unordered_map<std::string, Value*>::const_iterator it;
  if ((it = children_.find(child_name)) != children_.end()) {
    *o_child = it->second;
    return 0;
  }
  return DMS_NO_EXISTS;
}

} // namespace eq