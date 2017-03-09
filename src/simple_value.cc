
#include <simple_value.h>

namespace dms {

static int FixedSizeOfType(int type) {
  switch (type) {
  case DMS_TYPE_CHAR:
    return 1;

  case DMS_TYPE_SHORT:
    return 2;

  case DMS_TYPE_INT:
    return 4;

  case DMS_TYPE_LONG:
    return 8;

  case DMS_TYPE_FLOAT:
    return 4;

  case DMS_TYPE_DOUBLE:
    return 8;

  case DMS_TYPE_STRING:
    return 4;

  default:
    return 0;
  }
}

SimpleValue::SimpleValue(dms_field* field, ByteArray* buffer) 
  : Value(buffer) {
  type_ = field->type;
  simple_value_.base_field = field;
  memcpy_s(simple_value_.sys_data, sizeof(simple_value_.sys_data), this, 
    sizeof(this));
  value_ = &simple_value_;
  fixed_size_ = FixedSizeOfType(type_);
}

SimpleValue::~SimpleValue() {
  // nothing
}

int SimpleValue::Init() {
  return 0;
}

int SimpleValue::SetPosition(int position) {
  position_ = position;
  return 0;
}

int SimpleValue::Clear() {
  position_ -= -1;
  return 0;
}

} // namespace eq