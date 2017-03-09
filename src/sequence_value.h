
#ifndef DMS_SEQUENCE_VALUE_H__
#define DMS_SEQUENCE_VALUE_H__

#include <value.h>

namespace dms {

class SequenceValue : public Value {
 public:
  SequenceValue(dms_seq_field* seq_field, ByteArray* buffer);
  virtual ~SequenceValue();

  // init the value
  virtual int Init();

  // set the position of the value in the owner instance buffer.
  virtual int SetPosition(int position);

  // clear the content of the value
  virtual int Clear();

  // set the size
  int SetSize(int size);

  // get the size
  int GetSize(int* o_size) const;

  // set the current index
  int SetCurrent(int current);

  // get the current index
  int GetCurrent(int* o_current) const;

 private:
  // help to read the size
  int DoReadSize(int* o_size) const;

  // the sequence value
  dms_seq_value seq_value_;
  // the current index
  int current_;
  // the element value
  Value* element_value_;

  // Disable copying of SequenceValue
  DMS_DISALLOW_CONSTRUCTORS(SequenceValue);
};

} // namespace dms

#endif // DMS_SEQUENCE_VALUE_H__