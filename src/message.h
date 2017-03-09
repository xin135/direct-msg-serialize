
#ifndef DMS_MESSAGE_H__
#define DMS_MESSAGE_H__

#include <dms.h>
#include <common.h>
#include <byte_array.h>

namespace dms {

/**
 * The 'message' is the dynamic object with the members as desciped in the
 * schema.
 */
class Message {
 public:
  Message(const dms_schema* schema, dms_message* msg);
  ~Message();

  // Init the message, including init all the members of this instance
  // and allocate the initial memory for the members.
  int Init();

  // Reset the message, mainly used to clear the content of the instance,
  // reverse the instance to the initial state.
  int Reset();

  // Decode the buffer
  int Decode(const void* buffer, int size, int options);

  // Encode the content and ouput the encoded buffer
  int Encode(const void** o_buffer, int* o_size, int options);

 private:
  // the message
  dms_message* message_;
  // the internal buffer
  ByteArray buffer_;

  // Disable copying of Message
  DMS_DISALLOW_CONSTRUCTORS(Message);
};

} // namespace dms

#endif // DMS_MESSAGE_H__