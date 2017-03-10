
#include <fstream>
#include <iostream>
#include <vector>

#include <dms.h>

int main() {
  // read xml content
  std::vector<char> content;
  std::ifstream in("simple.xml", std::ios::binary);
  in.seekg(0, std::ios::end);
  size_t fsize = in.tellg();
  content.resize(fsize);
  in.seekg(0, std::ios::beg);
  in.read(&content[0], fsize);
  content.push_back('\0');

  // create schema
  dms_schema schema;
  memset(&schema, 0, sizeof(dms_schema));
  dms_schema_init(&content[0], &schema);
  // create message
  dms_message msg;
  memset(&msg, 0, sizeof(dms_message));
  dms_message_init(&schema, &msg);
  // set field values of the message
  dms_value* field_0 = msg.group_value->children[0];
  dms_value* field_1 = msg.group_value->children[1];
  dms_value* field_2 = msg.group_value->children[2];
  dms_value* field_3 = msg.group_value->children[3];
  dms_value* field_4 = msg.group_value->children[4];
  dms_group_value* field_5 = (dms_group_value*)(msg.group_value->children[5]);
  dms_value* field_5_0 = field_5->children[0];
  dms_value* field_5_1 = field_5->children[1];
  dms_seq_value* field_6 = (dms_seq_value*)(msg.group_value->children[6]);

  // create decode message
  dms_message decode_msg;
  memset(&decode_msg, 0, sizeof(dms_message));
  dms_message_init(&schema, &decode_msg);
  dms_value* decode_field_0 = decode_msg.group_value->children[0];
  dms_value* decode_field_1 = decode_msg.group_value->children[1];
  dms_value* decode_field_2 = decode_msg.group_value->children[2];
  dms_value* decode_field_3 = decode_msg.group_value->children[3];
  dms_value* decode_field_4 = decode_msg.group_value->children[4];
  dms_group_value* decode_field_5 = (dms_group_value*)(decode_msg.group_value->children[5]);
  dms_value* decode_field_5_0 = decode_field_5->children[0];
  dms_value* decode_field_5_1 = decode_field_5->children[1];
  dms_seq_value* decode_field_6 = (dms_seq_value*)(decode_msg.group_value->children[6]);

  // set fields values
  dms_value_set_char(field_0, 'c');
  dms_value_set_short(field_1, 44);
  dms_value_set_int(field_2, 8888);
  dms_value_set_long(field_3, 88989234234234LL);
  dms_value_set_string(field_4, "cdsdcasc", 8);
  dms_value_set_int(field_5_0, 7878);
  dms_value_set_long(field_5_1, 1212341434234234LL);
  dms_seq_value_set_size(field_6, 10);
  for (int i = 0; i < 10; ++i) {
    dms_seq_value_set_current(field_6, i);
    dms_value_set_int(field_6->element_value, 9999 + i);
  }

  // encode the message
  const void* buffer = NULL;
  int buf_size = 0;
  dms_message_encode(&msg, &buffer, &buf_size);

  //decode the message
  dms_message_decode(&decode_msg, buffer, buf_size);

  // get field values
  char f0_val = 0;
  short f1_val = 0;
  int f2_val = 0;
  long long f3_val = 0;
  const char* f4_val = NULL;
  int f4_size = 0;
  int f50_val = 0;
  long long f51_val = 0;
  int f6_elem_val = 0;
  dms_value_get_char(decode_field_0, &f0_val);
  dms_value_get_short(decode_field_1, &f1_val);
  dms_value_get_int(decode_field_2, &f2_val);
  dms_value_get_long(decode_field_3, &f3_val);
  dms_value_get_string(decode_field_4, &f4_val, &f4_size);
  dms_value_get_int(decode_field_5_0, &f50_val);
  dms_value_get_long(decode_field_5_1, &f51_val);
  for (int i = 0; i < 10; ++i) {
    dms_seq_value_set_current(decode_field_6, i);
    dms_value_get_int(decode_field_6->element_value, &f6_elem_val);
  }

  dms_message_destroy(&msg);
  dms_message_destroy(&decode_msg);
  dms_schema_destroy(&schema);
  return 0;
}