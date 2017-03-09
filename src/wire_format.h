
#ifndef DMS_WIRE_FORMAT_H__
#define DMS_WIRE_FORMAT_H__

#include <stdint.h>

namespace dms {

// This class is for internal use by the  library, it contains helpers 
// for implementing the binary wire format.
//
// This class is really a namespace that contains only static methods.
class WireFormat {
 public:
  // Read a 16-bit little-endian integer.
  static void ReadLittleEndian16(const uint8_t* buffer, uint16_t* value);
  // Read a 32-bit little-endian integer.
  static void ReadLittleEndian32(const uint8_t* buffer, uint32_t* value);
  // Read a 64-bit little-endian integer.
  static void ReadLittleEndian64(const uint8_t* buffer, uint64_t* value);

  // Write a 16-bit little-endian integer.
  static void WriteLittleEndian16(uint16_t value, uint8_t* target);
  // Write a 32-bit little-endian integer.
  static void WriteLittleEndian32(uint32_t value, uint8_t* target);
  // Write a 64-bit little-endian integer.
  static void WriteLittleEndian64(uint64_t value, uint8_t* target);

  // Helper functions for converting between floats/doubles and IEEE-754
  // uint32s/uint64s so that they can be written.  (Assumes your platform
  // uses IEEE-754 floats.)
  static inline uint32_t EncodeFloat(float value);
  static inline float DecodeFloat(uint32_t value);
  static inline uint64_t EncodeDouble(double value);
  static inline double DecodeDouble(uint64_t value);

 private:
  // This class is not intend to be instanced
  WireFormat() {}
};

} // namespace dms

#endif // DMS_WIRE_FORMAT_H__