
#include <dms.h>

#include <string>

#include <common.h>
#include <schema.h>
#include <simple_value.h>
#include <group_value.h>
#include <sequence_value.h>
#include <message.h>

int dms_schema_init(const char* xml_desc, dms_schema* schema) {
  DMS_CHECK_RETURN(NULL != xml_desc && 0 != strlen(xml_desc) && 
    NULL != schema, DMS_INVALID);
  return dms::InitSchema(xml_desc, schema);
}

int dms_schema_destroy(dms_schema* schema) {
  DMS_CHECK_RETURN(NULL != schema, DMS_INVALID);
  return dms::ReleaseSchema(schema);
}

int dms_message_init(const dms_schema* schema, dms_message* dms_msg) {
  DMS_CHECK_RETURN(NULL != schema && NULL != dms_msg, DMS_INVALID);
  dms::Message* msg = new dms::Message(schema, dms_msg);
  int res = msg->Init();
  if (0 != res) {
    delete msg;
    memset(dms_msg, 0, sizeof(dms_message));
  }
  return res;
}

int dms_message_destroy(dms_message* dms_msg) {
  DMS_CHECK_RETURN(NULL != dms_msg, DMS_INVALID);
  dms::Message* msg = *reinterpret_cast<dms::Message**>(
    dms_msg->sys_data);
  if (NULL != msg) {
    delete msg;
  }
  memset(dms_msg, 0, sizeof(dms_message));
  return 0;
}

int dms_message_reset(dms_message* dms_msg) {
  DMS_CHECK_RETURN(NULL != dms_msg, DMS_INVALID);
  dms::Message* msg = *reinterpret_cast<dms::Message**>(
    dms_msg->sys_data);
  DMS_CHECK_RETURN(NULL != msg, DMS_INVALID);
  return msg->Reset();
}

int dms_message_decode(dms_message* dms_msg, const void* buffer, int size, 
  int options) {
  DMS_CHECK_RETURN(NULL != dms_msg && NULL != buffer && 0 != size,
    DMS_INVALID);
  dms::Message* msg = *reinterpret_cast<dms::Message**>(
    dms_msg->sys_data);
  DMS_CHECK_RETURN(NULL != msg, DMS_INVALID);
  return msg->Decode(buffer, size, options);
}

int dms_message_encode(dms_message* dms_msg, const void** o_buffer,
  int* o_size, int options) {
  DMS_CHECK_RETURN(NULL != dms_msg && NULL != o_buffer && NULL != o_size,
    DMS_INVALID);
  dms::Message* msg = *reinterpret_cast<dms::Message**>(dms_msg->sys_data);
  DMS_CHECK_RETURN(NULL != msg, DMS_INVALID);
  return msg->Encode(o_buffer, o_size, options);
}

int dms_value_set_char(dms_value* fvalue, char value) {
  DMS_CHECK_RETURN(NULL != fvalue, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetChar(value);
}

int dms_value_set_short(dms_value* fvalue, short value) {
  DMS_CHECK_RETURN(NULL != fvalue, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetShort(value);
}

int dms_value_set_int(dms_value* fvalue, int value) {
  DMS_CHECK_RETURN(NULL != fvalue, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetInt(value);
}

int dms_value_set_long(dms_value* fvalue, long long value) {
  DMS_CHECK_RETURN(NULL != fvalue, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetLong(value);
}

int dms_value_set_float(dms_value* fvalue, float value) {
  DMS_CHECK_RETURN(NULL != fvalue, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetFloat(value);
}

int dms_value_set_double(dms_value* fvalue, double value) {
  DMS_CHECK_RETURN(NULL != fvalue, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetDouble(value);
}

int dms_value_set_string(dms_value* fvalue,
  const char* value, int size) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != value, DMS_INVALID);
  dms::SimpleValue* dest = *reinterpret_cast<dms::SimpleValue**>(
    fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetString(value, size);
}

int dms_value_get_char(const dms_value* fvalue, char* o_value) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value, DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetChar(o_value);
}

int dms_value_get_short(const dms_value* fvalue, short* o_value) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value, DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetShort(o_value);
}

int dms_value_get_int(const dms_value* fvalue, int* o_value) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value, DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetInt(o_value);
}

int dms_value_get_long(const dms_value* fvalue, long long* o_value) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value, DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetLong(o_value);
}

int dms_value_get_float(const dms_value* fvalue, float* o_value) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value, DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetFloat(o_value);
}

int dms_value_get_double(const dms_value* fvalue, double* o_value) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value, DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetDouble(o_value);
}

int dms_value_get_string(const dms_value* fvalue, const char** o_value,
  int* o_size) {
  DMS_CHECK_RETURN(NULL != fvalue && NULL != o_value && NULL != o_size, 
    DMS_INVALID);
  const dms::SimpleValue* dest =
    *reinterpret_cast<const dms::SimpleValue* const*>(fvalue->sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetString(o_value, o_size);
}

int dms_group_value_get_child(const dms_group_value* group_value,
  const char* child_name, dms_value** o_child) {
  DMS_CHECK_RETURN(NULL != group_value && NULL != child_name &&
    NULL != o_child && 0 != strlen(child_name), DMS_INVALID);
  const dms::GroupValue* dest =
    *reinterpret_cast<const dms::GroupValue* const*>(
    group_value->base.sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  dms::Value* cvalue = NULL;
  DMS_CHECK_RESULT(dest->GetChild(child_name, &cvalue));
  *o_child = cvalue->value();
  return 0;
}

int dms_seq_value_set_size(dms_seq_value* seq_value, int size) {
  DMS_CHECK_RETURN(NULL != seq_value && size >= 0, DMS_INVALID);
  dms::SequenceValue* dest =
    *reinterpret_cast<dms::SequenceValue**>(
    seq_value->base.sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetSize(size);
}

int dms_seq_value_get_size(const dms_seq_value* seq_value, int* o_size) {
  DMS_CHECK_RETURN(NULL != seq_value && NULL != o_size, DMS_INVALID);
  const dms::SequenceValue* dest =
    *reinterpret_cast<const dms::SequenceValue* const*>(
    seq_value->base.sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetSize(o_size);
}

int dms_seq_value_set_current(dms_seq_value* seq_value, int current_index) {
  DMS_CHECK_RETURN(NULL != seq_value && current_index >= 0, DMS_INVALID);
  dms::SequenceValue* dest =
    *reinterpret_cast<dms::SequenceValue**>(
    seq_value->base.sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->SetCurrent(current_index);
}

int dms_seq_value_get_current(const dms_seq_value* seq_value,
  int* o_current_index) {
  DMS_CHECK_RETURN(NULL != seq_value && NULL != o_current_index,
    DMS_INVALID);
  const dms::SequenceValue* dest =
    *reinterpret_cast<const dms::SequenceValue* const*>(
    seq_value->base.sys_data);
  DMS_CHECK_RETURN(NULL != dest, DMS_INVALID);
  return dest->GetCurrent(o_current_index);
}