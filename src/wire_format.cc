
#include <wire_format-inl.h>

#include <memory.h>

namespace dms {

#ifdef _MSC_VER
#if defined(_M_IX86)
#define HTQ_LITTLE_ENDIAN 1
#endif
#if _MSC_VER >= 1300
  // If MSVC has "/RTCc" set, it will complain about truncating casts at
  // runtime.  This file contains some intentional truncating casts.
#pragma runtime_checks("c", off)
#endif
#else
#include <sys/param.h>   // __BYTE_ORDER
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN
#define HTQ_LITTLE_ENDIAN 1
#endif
#endif

void WireFormat::ReadLittleEndian16(const uint8_t* buffer, 
  uint16_t* value) {
#if defined(HTQ_LITTLE_ENDIAN)
    memcpy(value, buffer, sizeof(*value));
#else
    *value = (static_cast<uint16_t>(buffer[0])) |
      (static_cast<uint16_t>(buffer[1]) <<  8);
#endif
}

void WireFormat::ReadLittleEndian32(const uint8_t* buffer, uint32_t* value) {
#if defined(HTQ_LITTLE_ENDIAN)
  memcpy(value, buffer, sizeof(*value));
#else
  *value = (static_cast<uint32_t>(buffer[0])) |
    (static_cast<uint32_t>(buffer[1]) <<  8) |
    (static_cast<uint32_t>(buffer[2]) << 16) |
    (static_cast<uint32_t>(buffer[3]) << 24);
#endif
}

// Read a 64-bit little-endian integer.
void WireFormat::ReadLittleEndian64(const uint8_t* buffer, uint64_t* value) {
#if defined(HTQ_LITTLE_ENDIAN)
  memcpy(value, buffer, sizeof(*value));
#else
  uint32_t part0 = (static_cast<uint32_t>(buffer[0])) |
    (static_cast<uint32_t>(buffer[1]) <<  8) |
    (static_cast<uint32_t>(buffer[2]) << 16) |
    (static_cast<uint32_t>(buffer[3]) << 24);
  uint32_t part1 = (static_cast<uint32_t>(buffer[4])) |
    (static_cast<uint32_t>(buffer[5]) <<  8) |
    (static_cast<uint32_t>(buffer[6]) << 16) |
    (static_cast<uint32_t>(buffer[7]) << 24);
  *value = static_cast<uint64_t>(part0) |
    (static_cast<uint64_t>(part1) << 32);
#endif
}

void WireFormat::WriteLittleEndian16(uint16_t value, uint8_t* target) {
#if defined(HTQ_LITTLE_ENDIAN)
  memcpy(target, &value, sizeof(value));
#else
  target[0] = static_cast<uint8_t>(value);
  target[1] = static_cast<uint8_t>(value >>  8);
#endif
}

void WireFormat::WriteLittleEndian32(uint32_t value, uint8_t* target) {
#if defined(HTQ_LITTLE_ENDIAN)
  memcpy(target, &value, sizeof(value));
#else
  target[0] = static_cast<uint8_t>(value);
  target[1] = static_cast<uint8_t>(value >>  8);
  target[2] = static_cast<uint8_t>(value >> 16);
  target[3] = static_cast<uint8_t>(value >> 24);
#endif
}

void WireFormat::WriteLittleEndian64(uint64_t value, uint8_t* target) {
#if defined(HTQ_LITTLE_ENDIAN)
  memcpy(target, &value, sizeof(value));
#else
  uint32_t part0 = static_cast<uint32_t>(value);
  uint32_t part1 = static_cast<uint32_t>(value >> 32);

  target[0] = static_cast<uint8_t>(part0);
  target[1] = static_cast<uint8_t>(part0 >>  8);
  target[2] = static_cast<uint8_t>(part0 >> 16);
  target[3] = static_cast<uint8_t>(part0 >> 24);
  target[4] = static_cast<uint8_t>(part1);
  target[5] = static_cast<uint8_t>(part1 >>  8);
  target[6] = static_cast<uint8_t>(part1 >> 16);
  target[7] = static_cast<uint8_t>(part1 >> 24);
#endif
}

#if defined(_MSC_VER) && _MSC_VER >= 1300
#pragma runtime_checks("c", restore)
#endif  // _MSC_VER

} // namespace dms