
#include <message.h>

#include <group_value.h>

namespace dms {

Message::Message(const dms_schema* schema, dms_message* msg)
  : message_(msg) {
  message_->schema = schema;
  void* ptr = this;
  memcpy_s(msg->sys_data, sizeof(msg->sys_data), &ptr, sizeof(this));
}

Message::~Message() {
  if (NULL != message_->group_value) {
    GroupValue* group_value = *reinterpret_cast<GroupValue**>(
      message_->group_value->base.sys_data);
    delete group_value;
  }
}

int Message::Init() {
  GroupValue* group_value = new GroupValue(
    message_->schema->root_field, &buffer_);
  DMS_CHECK_RESULT(group_value->Init());
  message_->group_value = reinterpret_cast<dms_group_value*>(
    group_value->value());
  // allocate the init memory
  buffer_.Increment(group_value->fixed_size());
  // set the position to the begining
  DMS_CHECK_RESULT(group_value->SetPosition(0));
  return 0;
}

int Message::Reset() {
  GroupValue* group_value = *reinterpret_cast<GroupValue**>(
    message_->group_value->base.sys_data);
  group_value->Clear();
  buffer_.Clear();
  buffer_.Increment(group_value->fixed_size());
  DMS_CHECK_RESULT(group_value->SetPosition(0));
  return 0;
}

int Message::Decode(const void* buffer, int size, int options) {
  GroupValue* group_value = *reinterpret_cast<GroupValue**>(
    message_->group_value->base.sys_data);
  group_value->Clear();
  buffer_.Clear();
  buffer_.Write(reinterpret_cast<const uint8_t*>(buffer), size);
  DMS_CHECK_RESULT(group_value->SetPosition(0));
  return 0;
}

int Message::Encode(const void** o_buffer, int* o_size, int options) {
  *o_buffer = buffer_.begin();
  *o_size = buffer_.size();
  return 0;
}

} // namespace dms