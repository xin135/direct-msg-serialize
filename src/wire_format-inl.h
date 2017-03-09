
#ifndef DMS_WIRE_FORMAT_INI_H__
#define DMS_WIRE_FORMAT_INI_H__

#include <wire_format.h>

namespace dms {

inline uint32_t WireFormat::EncodeFloat(float value) {
  union {float f; uint32_t i;};
  f = value;
  return i;
}

inline float WireFormat::DecodeFloat(uint32_t value) {
  union {float f; uint32_t i;};
  i = value;
  return f;
}

inline uint64_t WireFormat::EncodeDouble(double value) {
  union {double f; uint64_t i;};
  f = value;
  return i;
}

inline double WireFormat::DecodeDouble(uint64_t value) {
  union {double f; uint64_t i;};
  i = value;
  return f;
}

} // namespace dms

#endif // DMS_WIRE_FORMAT_INI_H__