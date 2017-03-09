
/// @file Contains the byte array

#ifndef DMS_BYTE_ARRAY_H__
#define DMS_BYTE_ARRAY_H__

#include <stdlib.h>
#include <vector>

#include <common.h>
#include <memory_allocator.h>

namespace dms {

// The utity class used as a dynamic array. 
// In some cases we use this class instead of std::vector for better 
// performance.
class ByteArray {
 public:
  ByteArray()
    : size_(0) {
    // nothing
  }
  ~ByteArray() {
    // nothing
  }

  void Write(const uint8_t* buffer, int size) {
    if (0 == size) return;
    allocator_.Ensure(size_ + size);
    memcpy_s(allocator_.memory() + size_, size, buffer, size);
    size_ += size;
  }

  void Write(uint8_t byte) {
    allocator_.Ensure(size_ + 1);
    allocator_.memory()[size_] = byte;
    size_ += 1;
  }

  uint8_t* Increment(int added) {
    allocator_.Ensure(size_ + added);
    int old_size = size_;
    size_ += added;
    return allocator_.memory() + old_size;
  }

  void Shrink(int size) {
    memmove_s(begin(), size_ - size, 
      begin() + size, size_ - size);
    size_ -= size;
  }

  void Resize(int new_size) {
    if (new_size > size_) {
      Increment(new_size - size_);
    } else {
      size_ = new_size;
    }
  }

  void Clear() {
    size_ = 0;
    allocator_.Clear();
  }

  const uint8_t* begin() const {
    if (0 == size_) return NULL;
    return allocator_.memory();
  }

  const uint8_t* end() const {
    if (0 == size_) return NULL;
    return begin() + size_;
  }

  uint8_t* begin() {
    if (0 == size_) return NULL;
    return allocator_.memory();
  }

  int size() const {
    return size_;
  }

  template<class T>
  int Write(int pos, T value) {
    DMS_CHECK_RETURN(pos < size_, DMS_INVALID);
    memcpy_s(allocator_.memory() + pos, sizeof(T), &value, sizeof(T));
    return 0;
  }

  template<class T>
  int Read(int pos, T* o_value) const {
    DMS_CHECK_RETURN(pos < size_, DMS_INVALID);
    memcpy_s(o_value, sizeof(T), allocator_.memory() + pos, sizeof(T));
    return 0;
  }

 private:
  MemoryAllocator allocator_;
  // the data size
  int size_;

  // Disable copying of ByteArray
  DMS_DISALLOW_CONSTRUCTORS(ByteArray);
};

} // namespace eq

#endif // DMS_BYTE_ARRAY_H__