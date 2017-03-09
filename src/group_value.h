
#ifndef DMS_GROUP_VALUE_H__
#define DMS_GROUP_VALUE_H__

#include <unordered_map>

#include <value.h>

namespace dms {

class GroupValue : public Value {
 public:
  GroupValue(dms_group_field* group_field, ByteArray* buffer);
  virtual ~GroupValue();

  // init the value
  virtual int Init();

  // set the position of the value in the owner instance buffer.
  virtual int SetPosition(int position);

  // clear the content of the value
  virtual int Clear();

  // get the child withe the specified name
  int GetChild(const char* child_name, Value** o_child) const;

 private:

  // the group value
  dms_group_value group_value_;
  // the member values
  std::unordered_map<std::string, Value*> children_;
  // list of the children
  std::vector<dms_value*> value_list_;

  // Disable copying of GroupValue
  DMS_DISALLOW_CONSTRUCTORS(GroupValue);
};

} // namespace dms

#endif // DMS_GROUP_VALUE_H__