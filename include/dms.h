/**
 * Direct message serialize library.
 *
 * Copyright (C) 2017 hainan, ning.  All rights reserved.
 *
 *    Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *    http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef DMS_API_H__
#define DMS_API_H__

// Handle DSO symbol visibility
#if defined _WIN32
  #if defined DMS_STATIC
    #define DMS_API
  #else
    #if defined DMS_SDK_EXPORT
      #define DMS_API __declspec(dllexport)
    #else
      #define DMS_API __declspec(dllimport)
    #endif
  #endif
#else
  #if defined __SUNPRO_C  || defined __SUNPRO_CC
    #define DMS_API __global
  #elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
    #define DMS_API __attribute__ ((visibility("default")))
  #else
    #define DMS_API
  #endif
#endif

/// Define the max field name length
#define DMS_FIELD_NAME_LEN       64


/// Define a field data type. 0 is reserved for errors.
typedef enum _dms_type {
  DMS_TYPE_CHAR     = 1,    // char, 1 byte
  DMS_TYPE_SHORT    = 2,    // short, 2 bytes
  DMS_TYPE_INT      = 3,    // int, 4 bytes
  DMS_TYPE_LONG     = 4,    // long, 8 bytes
  DMS_TYPE_FLOAT    = 5,    // float, 4 bytes
  DMS_TYPE_DOUBLE   = 6,    // double, 8 bytes
  DMS_TYPE_STRING   = 7,    // string, could be used as bytes array
  DMS_TYPE_GROUP    = 8,    // group field
  DMS_TYPE_SEQUENCE = 9     // sequence field
} dms_type;

/// Represents a generic field definion of a message. The field could be
/// any type, and if this is a compound type (group or sequence), the pointer
/// to this field could be casted to corresponding concrete field type. 
typedef struct _dms_field {
  int               type;
  char              name[DMS_FIELD_NAME_LEN];
} dms_field;

/// Represents a group field detinition of a message. A group field
/// is a compound field which contains a sequence of child fields.
/// The order of the fields definitions is just the order of the fields 
/// in the message buffer.
typedef struct _dms_group_field {
  dms_field         base;
  dms_field**       children;
  int               num_of_children;
} dms_group_field;

/// Represents a sequence field definition of a message. A sequence field
/// defines an array field with fixed element type. For instance, a sequence
/// field with the INT element field means a INT array field. 
typedef struct _dms_seq_field {
  dms_field         base;
  dms_field*        element_field;
} dms_seq_field;

/// Represents a schema. A schema defines static struct of a message, it
/// contains a sequence of fields definitions. The order of the fields
/// definitions is just the order of the fields in the message buffer.
typedef struct _dms_schema {
  int               schema_id;
  dms_group_field*  root_field;
} dms_schema;

/// Represents generic value of a message field. The field could be
/// any type, and if this is a compound type (group or sequence) value, 
/// the pointer to this value could be casted to corresponding concrete 
/// value type. 
typedef struct _dms_value {
  dms_field*        base_field;
  char              sys_data[16];
} dms_value;

/// Represents a group value of a message. It contains values of the child
/// fields of the groups, and the order of the child values is just the
/// order of the child fields.
typedef struct _dms_group_value {
  dms_value         base;
  dms_value**       children;
} dms_group_value;

/// Represents a sequence value of a message. The element value in it 
/// represents the currently selected element in the array.
typedef struct _dms_seq_value {
  dms_value         base;
  dms_value*        element_value;
} dms_seq_value;

/// Represents the message. A message is created based on a pre-defined
/// schema. And the values of the message fields could be accessed through
/// the group value in it.
typedef struct _dms_message {
  const dms_schema* schema;
  dms_group_value*  group_value;
  char              sys_data[16];
} dms_message;

/// Creates a schema based on the xml detinitions in the description
/// string. 
DMS_API int dms_schema_init(const char* xml_desc, dms_schema* schema);

/// Destroy the schema object.
DMS_API int dms_schema_destroy(dms_schema* schema);

/// Creates a message based on the input schema.
DMS_API int dms_message_init(const dms_schema* schema, dms_message* msg);

/// Destroy the message object.
DMS_API int dms_message_destroy(dms_message* msg);

/// Reset the fields of the input message to default values.
DMS_API int dms_message_reset(dms_message* msg);

/// Decode the input buffer and populates the message with the content. The
/// format of the content must adhere to the schema definition of the message.
DMS_API int dms_message_decode(dms_message* msg, const void* buffer, int size);

/// Encode the message and output the buffer of the encoded content. It's
/// supposed to used the decode API to use the encoded buffer, just be sure
/// the schema is the same when decoding.
DMS_API int dms_message_encode(dms_message* msg, const void** o_buffer, 
  int* o_size);

/// Sets the value for the specified field value object. The value type must
/// be the same as the field type definition, otherwise the operation would
/// fail.
DMS_API int dms_value_set_char(dms_value* fvalue, char value);
DMS_API int dms_value_set_short(dms_value* fvalue, short value);
DMS_API int dms_value_set_int(dms_value* fvalue, int value);
DMS_API int dms_value_set_long(dms_value* fvalue, long long value);
DMS_API int dms_value_set_float(dms_value* fvalue, float value);
DMS_API int dms_value_set_double(dms_value* fvalue, double value);
DMS_API int dms_value_set_string(dms_value* fvalue,
  const char* value, int size);

/// Gets the value from the specified field value object. The value type must
/// be the same as the field type definition, otherwise the operation would
/// fail.
DMS_API int dms_value_get_char(const dms_value* fvalue, char* o_value);
DMS_API int dms_value_get_short(const dms_value* fvalue, short* o_value);
DMS_API int dms_value_get_int(const dms_value* fvalue, int* o_value);
DMS_API int dms_value_get_long(const dms_value* fvalue, long long* o_value);
DMS_API int dms_value_get_float(const dms_value* fvalue, float* o_value);
DMS_API int dms_value_get_double(const dms_value* fvalue, double* o_value);
DMS_API int dms_value_get_string(const dms_value* fvalue, 
  const char** o_value, int* o_size);

/// Help method to get the child field value object of the input group value.
DMS_API int dms_group_value_get_child(const dms_group_value* group_value,
  const char* child_name, dms_value** o_child);

/// Sets the number of elements in the specified sequence value.
DMS_API int dms_seq_value_set_size(dms_seq_value* seq_value,
  int size);
 
/// Gets the number of elements of the specified sequence value.
DMS_API int dms_seq_value_get_size(const dms_seq_value* seq_value,
  int* o_size);

/// Sets the index of the elements to be operated on for the input sequence
/// value.
DMS_API int dms_seq_value_set_current(dms_seq_value* seq_value,
  int current_index);

/// Gets the index of the elements currelty operating on for the input sequence
/// value.
DMS_API int dms_seq_value_get_current(const dms_seq_value* seq_value,
  int* o_current_index);

#endif // DMS_API_H__