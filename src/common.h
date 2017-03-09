
#ifndef DMS_COMMON_H__
#define DMS_COMMON_H__

namespace dms {

// help method to copy string
void SafeCopyStr(char* dest, int bufsize, const char* src);

} // namespace eq

/* ¥ÌŒÛ¬Î∂®“Â */
#define DMS_SUCCESS                         0       // success

#define DMS_INVALID                         (-1)    // Invalid parameter, or API misuse
#define DMS_NOMEM                           (-2)    // Memory allocation failed
#define DMS_EOVERFLOW                       (-3)    // Data exceeds the buffer
#define DMS_NO_EXISTS                       (-8)    // The requested element does not exist
#define DMS_FAIL                            (-100)  // Operation failed caused by the internal logic errors

#undef DMS_DISALLOW_CONSTRUCTORS
#define DMS_DISALLOW_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                   \
  void operator=(const TypeName&)

/// The DMS_ARRAYSIZE(arr) macro returns the # of elements in an array arr.
/// The expression is a compile-time constant, and therefore can be
/// used in defining new arrays, for example.
///
/// DMS_ARRAYSIZE catches a few type errors.  If you see a compiler error
///
///   "warning: division by zero in ..."
///
/// when using DMS_ARRAYSIZE, you are (wrongfully) giving it a pointer.
/// You should only use EQ_ARRAYSIZE on statically allocated arrays.

#define DMS_ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

// Check the return value, we do not log here as the error
// should have been logged when generating the error code
#define DMS_CHECK_RESULT(EXPRESSION) \
{int ret=(EXPRESSION);if(0 != ret) return ret;}

#define DMS_CHECK_RETURN(EXPRESSION, RETVAL) \
{if (!(EXPRESSION)){ return (RETVAL);}}

#endif // DMS_COMMON_H__