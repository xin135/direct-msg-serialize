
#include <common.h>

#include <string>

namespace dms {

// help method to copy string
void SafeCopyStr(char* dest, int bufsize, const char* src) {
  size_t csize = strlen(src);
  csize = csize >= bufsize ? bufsize - 1 : csize;
  memcpy_s(dest, bufsize, src, csize);
  dest[csize] = '\0';
}

} // namespace eq