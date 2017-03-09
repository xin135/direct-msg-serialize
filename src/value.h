
#ifndef DMS_VALUE_H__
#define DMS_VALUE_H__

#include <dms.h>
#include <common.h>
#include <byte_array.h>

namespace dms {

class Value {
 public:
  Value(ByteArray* buffer);
  virtual ~Value();

  // init the value, could be extended by derived classes.
  virtual int Init() = 0;

  // set the position of the value in the owner instance buffer,
  // could be extented by the derived classes.
  virtual int SetPosition(int position) = 0;

  // clear the content of the value
  virtual int Clear() = 0;

  // get the eq value
  dms_value* value() {
    return value_;
  }

  // get fixed size
  int fixed_size() const {
    return fixed_size_;
  }

 protected:
  // create the value
  static Value* DoCreateValue(dms_field* field, ByteArray* buffer);

  // the value
  dms_value* value_;
  // the buffer
  ByteArray* buffer_;
  // the position
  int position_;
  // the fixed size
  int fixed_size_;

  // Disable copying of Value
  DMS_DISALLOW_CONSTRUCTORS(Value);
};

} // namespace dms

#endif // DMS_VALUE_H__