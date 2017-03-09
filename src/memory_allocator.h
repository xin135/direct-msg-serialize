
/// @file Defines the memory allocator.

#ifndef DMS_MEMORY_ALLOCATOR_H__
#define DMS_MEMORY_ALLOCATOR_H__

#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

#include <common.h>

namespace dms {

/// This is a helper class used to allocate memory, it may increase memory 
/// size by 50% at least at a time
class MemoryAllocator {
 public:
  MemoryAllocator() 
    : capacity_(0)
    , memory_(NULL) {}
  ~MemoryAllocator() {
    if (memory_) {
      free(memory_);
      memory_ = NULL;
    }
  }

  /// Ensures the memory with the specified size allocated and return
  /// the allocated memory
  void* Ensure(int capacity) {
    if (NULL == memory_) {
      memory_ = malloc(capacity);
      capacity_ = capacity;
      memset(memory_, 0, capacity_);
      return memory_;
    }
    if (capacity > capacity_) {
      int size = capacity_ * 3 / 2;
      int old_capacity = capacity_;
      capacity_ = capacity > size ? capacity : size;
      memory_ = realloc(memory_, capacity_);
      memset(reinterpret_cast<uint8_t*>(memory_) + old_capacity, 0, 
        capacity_ - old_capacity);
    }
    return memory_;
  }

  uint8_t* memory() {
    return reinterpret_cast<uint8_t*>(memory_);
  }

  const uint8_t* memory() const {
    return reinterpret_cast<uint8_t*>(memory_);
  }

  void Clear() {
    if (capacity_ > 0) {
      memset(memory_, 0, capacity_);
    }
  }

 private:
  void* memory_;
  int capacity_;

  // Disable copying of MemoryAllocator
  DMS_DISALLOW_CONSTRUCTORS(MemoryAllocator);
};

} // namespace dms

#endif // DMS_MEMORY_ALLOCATOR_H__