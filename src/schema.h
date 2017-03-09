
#ifndef DMS_SCHEMA_H__
#define DMS_SCHEMA_H__

#include <dms.h>

namespace dms {

int InitSchema(const char* xml_desc, dms_schema* schema);

int ReleaseSchema(dms_schema* schema);

} // namespace dms

#endif // DMS_SCHEMA_H__