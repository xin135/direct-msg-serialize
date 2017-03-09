
#include <value.h>

#include <group_value.h>
#include <sequence_value.h>
#include <simple_value.h>

namespace dms {

Value::Value(ByteArray* buffer)
  : buffer_(buffer) 
  , position_(-1)
  , fixed_size_(0)
  , value_(NULL) {
  // nothing
}

Value::~Value() {
  // nothing
}

Value* Value::DoCreateValue(dms_field* field, ByteArray* buffer) {
  switch (field->type) {
  case DMS_TYPE_GROUP:
    return new GroupValue(reinterpret_cast<dms_group_field*>(field), buffer);
  
  case DMS_TYPE_SEQUENCE:
    return new SequenceValue(reinterpret_cast<dms_seq_field*>(field), 
      buffer);

  default:
    return new SimpleValue(field, buffer);
  }
}

} // namespace dms