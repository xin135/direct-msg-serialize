
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN  // We only need minimal includes
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <fstream>
#include <iostream>
#include <vector>
#include <stdint.h>

#include <dms.h>

int64_t GetCurrentMicroseconds() {
#if defined _WIN32
  //  Get the high resolution counter's accuracy.
  LARGE_INTEGER ticksPerSecond;
  QueryPerformanceFrequency(&ticksPerSecond);

  //  What time is it?
  LARGE_INTEGER tick;
  QueryPerformanceCounter(&tick);

  //  Convert the tick number into the number of seconds
  //  since the system was started.
  double ticks_div = (double)(ticksPerSecond.QuadPart / 1000000.0);
  return (int64_t)(tick.QuadPart / ticks_div);

#elif defined HAVE_CLOCK_GETTIME && defined CLOCK_MONOTONIC

  //  Use POSIX clock_gettime function to get precise monotonic time.
  struct timespec tv;
  int rc = clock_gettime(CLOCK_MONOTONIC, &tv);
  // Fix case where system has clock_gettime but CLOCK_MONOTONIC is not supported.
  // This should be a configuration check, but I looked into it and writing an 
  // AC_FUNC_CLOCK_MONOTONIC seems beyond my powers.
  if (rc != 0) {
    //  Use POSIX gettimeofday function to get precise time.
    struct timeval tv;
    int rc = gettimeofday(&tv, NULL);
    assert(rc == 0);
    return (tv.tv_sec * (int64_t)1000000 + tv.tv_usec);
  }
  return (tv.tv_sec * (int64_t)1000000 + tv.tv_nsec / 1000);

#elif defined HAVE_GETHRTIME

  return (gethrtime() / 1000);

#else

  //  Use POSIX gettimeofday function to get precise time.
  struct timeval tv;
  int rc = gettimeofday(&tv, NULL);
  return (tv.tv_sec * (int64_t)1000000 + tv.tv_usec);

#endif

}

int main() {
  // read xml content
  std::vector<char> content;
  std::ifstream in("test.xml", std::ios::binary);
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
  // get fields of the message
  dms_value* field_0 = msg.group_value->children[0];
  dms_value* field_1 = msg.group_value->children[1];
  dms_value* field_2 = msg.group_value->children[2];
  dms_value* field_3 = msg.group_value->children[3];
  dms_value* field_4 = msg.group_value->children[4];
  dms_value* field_5 = msg.group_value->children[5];
  dms_value* field_6 = msg.group_value->children[6];
  dms_value* field_7 = msg.group_value->children[7];
  dms_value* field_8 = msg.group_value->children[8];
  dms_value* field_9 = msg.group_value->children[9];
  dms_value* field_10 = msg.group_value->children[10];
  dms_value* field_11 = msg.group_value->children[11];
  dms_value* field_12 = msg.group_value->children[12];
  dms_value* field_13 = msg.group_value->children[13];
  dms_value* field_14 = msg.group_value->children[14];
  dms_value* field_15 = msg.group_value->children[15];
  dms_value* field_16 = msg.group_value->children[16];
  dms_value* field_17 = msg.group_value->children[17];
  dms_value* field_18 = msg.group_value->children[18];
  dms_value* field_19 = msg.group_value->children[19];
  dms_value* field_20 = msg.group_value->children[20];
  dms_value* field_21 = msg.group_value->children[21];
  dms_value* field_22 = msg.group_value->children[22];
  dms_value* field_23 = msg.group_value->children[23];
  dms_value* field_24 = msg.group_value->children[24];
  dms_value* field_25 = msg.group_value->children[25];
  dms_value* field_26 = msg.group_value->children[26];
  dms_value* field_27 = msg.group_value->children[27];
  dms_value* field_28 = msg.group_value->children[28];
  dms_value* field_29 = msg.group_value->children[29];
  dms_value* field_30 = msg.group_value->children[30];
  dms_value* field_31 = msg.group_value->children[31];
  dms_value* field_32 = msg.group_value->children[32];
  dms_value* field_33 = msg.group_value->children[33];
  dms_value* field_34 = msg.group_value->children[34];
  dms_value* field_35 = msg.group_value->children[35];

  // create decode message
  dms_message decode_msg;
  memset(&decode_msg, 0, sizeof(dms_message));
  dms_message_init(&schema, &decode_msg);
  dms_value* decode_field_0 = decode_msg.group_value->children[0];
  dms_value* decode_field_1 = decode_msg.group_value->children[1];
  dms_value* decode_field_2 = decode_msg.group_value->children[2];
  dms_value* decode_field_3 = decode_msg.group_value->children[3];
  dms_value* decode_field_4 = decode_msg.group_value->children[4];
  dms_value* decode_field_5 = decode_msg.group_value->children[5];
  dms_value* decode_field_6 = decode_msg.group_value->children[6];
  dms_value* decode_field_7 = decode_msg.group_value->children[7];
  dms_value* decode_field_8 = decode_msg.group_value->children[8];
  dms_value* decode_field_9 = decode_msg.group_value->children[9];
  dms_value* decode_field_10 = decode_msg.group_value->children[10];
  dms_value* decode_field_11 = decode_msg.group_value->children[11];
  dms_value* decode_field_12 = decode_msg.group_value->children[12];
  dms_value* decode_field_13 = decode_msg.group_value->children[13];
  dms_value* decode_field_14 = decode_msg.group_value->children[14];
  dms_value* decode_field_15 = decode_msg.group_value->children[15];
  dms_value* decode_field_16 = decode_msg.group_value->children[16];
  dms_value* decode_field_17 = decode_msg.group_value->children[17];
  dms_value* decode_field_18 = decode_msg.group_value->children[18];
  dms_value* decode_field_19 = decode_msg.group_value->children[19];
  dms_value* decode_field_20 = decode_msg.group_value->children[20];
  dms_value* decode_field_21 = decode_msg.group_value->children[21];
  dms_value* decode_field_22 = decode_msg.group_value->children[22];
  dms_value* decode_field_23 = decode_msg.group_value->children[23];
  dms_value* decode_field_24 = decode_msg.group_value->children[24];
  dms_value* decode_field_25 = decode_msg.group_value->children[25];
  dms_value* decode_field_26 = decode_msg.group_value->children[26];
  dms_value* decode_field_27 = decode_msg.group_value->children[27];
  dms_value* decode_field_28 = decode_msg.group_value->children[28];
  dms_value* decode_field_29 = decode_msg.group_value->children[29];
  dms_value* decode_field_30 = decode_msg.group_value->children[30];
  dms_value* decode_field_31 = decode_msg.group_value->children[31];
  dms_value* decode_field_32 = decode_msg.group_value->children[32];
  dms_value* decode_field_33 = decode_msg.group_value->children[33];
  dms_value* decode_field_34 = decode_msg.group_value->children[34];
  dms_value* decode_field_35 = decode_msg.group_value->children[35];

  int64_t start = GetCurrentMicroseconds() / 1000;

  static const int kTestCount = 100000;

  // get field values
  char f0_val = 0;
  short f1_val = 0;
  int f2_val = 0;
  long long f3_val = 0;
  const char* f4_val = NULL;
  int f4_size = 0;
  int f5_val = 0;
  int f6_val = 0;
  int f7_val = 0;
  int f8_val = 0;
  int f9_val = 0;
  const char* f10_val = NULL;
  int f10_size = 0;
  const char* f11_val = NULL;
  int f11_size = 0;
  const char* f12_val = NULL;
  int f12_size = 0;
  const char* f13_val = NULL;
  int f13_size = 0;
  const char* f14_val = NULL;
  int f14_size = 0;
  const char* f15_val = NULL;
  int f15_size = 0;
  short f16_val = 0;
  short f17_val = 0;
  short f18_val = 0;
  short f19_val = 0;
  int f20_val = 0;
  int f21_val = 0;
  int f22_val = 0;
  char f23_val = 0;
  short f24_val = 0;
  int f25_val = 0;
  float f26_val = 0;
  float f27_val = 0;
  float f28_val = 0;
  float f29_val = 0;
  float f30_val = 0;
  double f31_val = 0;
  double f32_val = 0;
  double f33_val = 0;
  double f34_val = 0;
  double f35_val = 0;

  for (int i = 0; i < kTestCount; ++i) {
    // set fields values
    dms_value_set_char(field_0, 'c');
    dms_value_set_short(field_1, 44);
    dms_value_set_int(field_2, 8888);
    dms_value_set_long(field_3, 88989234234234LL);
    dms_value_set_string(field_4, "cdsdcasc", 8);
    dms_value_set_int(field_5, 8889);
    dms_value_set_int(field_6, 88881);
    dms_value_set_int(field_7, 88882);
    dms_value_set_int(field_8, 88883);
    dms_value_set_int(field_9, 88884);
    dms_value_set_string(field_10, "cdsdcasc", 8);
    dms_value_set_string(field_11, "cdsdcasc", 8);
    dms_value_set_string(field_12, "cdsdcasc", 8);
    dms_value_set_string(field_13, "cdsdcasc", 8);
    dms_value_set_string(field_14, "cdsdcasc", 8);
    dms_value_set_string(field_15, "cdsdcasc", 8);
    dms_value_set_short(field_16, 44);
    dms_value_set_short(field_17, 441);
    dms_value_set_short(field_18, 442);
    dms_value_set_short(field_19, 443);
    dms_value_set_int(field_20, 4455);
    dms_value_set_int(field_21, 4455);
    dms_value_set_int(field_22, 4455);
    dms_value_set_char(field_23, 8888);
    dms_value_set_short(field_24, 9990);
    dms_value_set_int(field_25, 88884);
    dms_value_set_float(field_26, 999.4f);
    dms_value_set_float(field_27, 999.4f);
    dms_value_set_float(field_28, 999.4f);
    dms_value_set_float(field_29, 999.4f);
    dms_value_set_float(field_30, 999.4f);
    dms_value_set_double(field_31, 99944444.4);
    dms_value_set_double(field_32, 99944444.4);
    dms_value_set_double(field_33, 99944444.4);
    dms_value_set_double(field_34, 99944444.4);
    dms_value_set_double(field_35, 99944444.4);

    // encode the message
    const void* buffer = NULL;
    int buf_size = 0;
    dms_message_encode(&msg, &buffer, &buf_size);

    //decode the message
    dms_message_decode(&decode_msg, buffer, buf_size);

    
    
    dms_value_get_char(decode_field_0, &f0_val);
    dms_value_get_short(decode_field_1, &f1_val);
    dms_value_get_int(decode_field_2, &f2_val);
    dms_value_get_long(decode_field_3, &f3_val);
    dms_value_get_string(decode_field_4, &f4_val, &f4_size);
    dms_value_get_int(decode_field_5, &f5_val);
    dms_value_get_int(decode_field_6, &f6_val);
    dms_value_get_int(decode_field_7, &f7_val);
    dms_value_get_int(decode_field_8, &f8_val);
    dms_value_get_int(decode_field_9, &f9_val);
    dms_value_get_string(decode_field_10, &f10_val, &f10_size);
    dms_value_get_string(decode_field_11, &f11_val, &f11_size);
    dms_value_get_string(decode_field_12, &f12_val, &f12_size);
    dms_value_get_string(decode_field_13, &f13_val, &f13_size);
    dms_value_get_string(decode_field_14, &f14_val, &f14_size);
    dms_value_get_string(decode_field_15, &f15_val, &f15_size);
    dms_value_get_short(decode_field_16, &f16_val);
    dms_value_get_short(decode_field_17, &f17_val);
    dms_value_get_short(decode_field_18, &f18_val);
    dms_value_get_short(decode_field_19, &f19_val);
    dms_value_get_int(decode_field_20, &f20_val);
    dms_value_get_int(decode_field_21, &f21_val);
    dms_value_get_int(decode_field_22, &f22_val);
    dms_value_get_char(decode_field_23, &f23_val);
    dms_value_get_short(decode_field_24, &f24_val);
    dms_value_get_int(decode_field_25, &f25_val);
    dms_value_get_float(decode_field_26, &f26_val);
    dms_value_get_float(decode_field_27, &f27_val);
    dms_value_get_float(decode_field_28, &f28_val);
    dms_value_get_float(decode_field_29, &f29_val);
    dms_value_get_float(decode_field_30, &f30_val);
    dms_value_get_double(decode_field_31, &f31_val);
    dms_value_get_double(decode_field_32, &f32_val);
    dms_value_get_double(decode_field_33, &f33_val);
    dms_value_get_double(decode_field_34, &f34_val);
    dms_value_get_double(decode_field_35, &f35_val);
  }

  int64_t elapsed = GetCurrentMicroseconds() / 1000 - start;
  std::cout << "Elapsed: " << elapsed / 1000 << "s " << elapsed % 1000 << "ms";

  dms_message_destroy(&msg);
  dms_message_destroy(&decode_msg);
  dms_schema_destroy(&schema);
  return 0;
}