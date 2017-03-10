
#include <schema.h>

#include <sstream>
#include <vector>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include <common.h>

namespace dms {

static int DoParseField(rapidxml::xml_node<char>* field_node,
  dms_field*& o_field);
static int DoParseChildFields(rapidxml::xml_node<char>* node,
  std::vector<dms_field*>* o_fields);

static int DoReadSimpleField(rapidxml::xml_node<char>* field_node,
  dms_field*& o_field) {
  // read name
  rapidxml::xml_attribute<char>* name_attr = field_node->first_attribute(
    "name");
  DMS_CHECK_RETURN(NULL != name_attr, DMS_INVALID);
  std::string name = name_attr->value();
  DMS_CHECK_RETURN(0 != name.size(), DMS_INVALID);
  // create the field
  o_field = new dms_field();
  SafeCopyStr(o_field->name, sizeof(o_field->name), name.c_str());
  // convert the type
  std::string type = field_node->name();
  if (type == "char" || type == "int8") {
    o_field->type = DMS_TYPE_CHAR;
  } else if (type == "short" || type == "int16") {
    o_field->type = DMS_TYPE_SHORT;
  } else if (type == "int" || type == "int32") {
    o_field->type = DMS_TYPE_INT;
  } else if (type == "int64" || type == "long") {
    o_field->type = DMS_TYPE_LONG;
  } else if (type == "string") {
    o_field->type = DMS_TYPE_STRING;
  } else {
    delete o_field;
    o_field = NULL;
    return DMS_INVALID;
  }
  return 0;
}

static int DoParseGroupField(rapidxml::xml_node<char>* field_node,
  dms_group_field*& o_group_field) {
  // read name
  rapidxml::xml_attribute<char>* name_attr = field_node->first_attribute(
    "name");
  DMS_CHECK_RETURN(NULL != name_attr, DMS_INVALID);
  std::string name = name_attr->value();
  DMS_CHECK_RETURN(0 != name.size(), DMS_INVALID);

  o_group_field = new dms_group_field();
  SafeCopyStr(o_group_field->base.name, DMS_FIELD_NAME_LEN,
    name.c_str());
  o_group_field->base.type = DMS_TYPE_GROUP;
  o_group_field->children = NULL;
  o_group_field->num_of_children = 0;
  // read child fields
  std::vector<dms_field*> child_fields;
  int res = DoParseChildFields(field_node, &child_fields);
  if (0 != res) {
    delete o_group_field;
    o_group_field = NULL;
    return res;
  }
  if (!child_fields.empty()) {
    o_group_field->num_of_children = static_cast<int>(child_fields.size());
    o_group_field->children = new dms_field*[child_fields.size()];
    memcpy_s(o_group_field->children, child_fields.size() * sizeof(dms_field*),
      &child_fields[0], child_fields.size() * sizeof(dms_field*));
  }
  return 0;
}

static int DoParseSequenceField(rapidxml::xml_node<char>* field_node,
  dms_seq_field*& o_seq_field) {
  // read name
  rapidxml::xml_attribute<char>* name_attr = field_node->first_attribute(
    "name");
  DMS_CHECK_RETURN(NULL != name_attr, DMS_INVALID);
  std::string name = name_attr->value();
  DMS_CHECK_RETURN(0 != name.size(), DMS_INVALID);

  o_seq_field = new dms_seq_field();
  SafeCopyStr(o_seq_field->base.name, DMS_FIELD_NAME_LEN,
    name.c_str());
  o_seq_field->base.type = DMS_TYPE_SEQUENCE;
  // read child fields
  std::vector<dms_field*> child_fields;
  int res = DoParseChildFields(field_node, &child_fields);
  if (0 != res) {
    delete o_seq_field;
    o_seq_field = NULL;
    return res;
  }
  if (child_fields.empty()) {
    delete o_seq_field;
    o_seq_field = NULL;
    return DMS_INVALID;
  }
  if (1 == child_fields.size()) {
    o_seq_field->element_field = child_fields[0];
  } else {
    dms_group_field* group_field = new dms_group_field();
    memset(group_field, 0, sizeof(dms_group_field));
    group_field->base.type = DMS_TYPE_GROUP;
    group_field->num_of_children = static_cast<int>(child_fields.size());
    group_field->children = new dms_field*[child_fields.size()];
    memcpy_s(group_field->children, child_fields.size() * sizeof(dms_field*),
      &child_fields[0], child_fields.size() * sizeof(dms_field*));
    o_seq_field->element_field = &group_field->base;
  }
  return 0;
}

static int DoParseField(rapidxml::xml_node<char>* field_node, 
  dms_field*& o_field) {
  std::string type = field_node->name();
  if (type == "group") {
    dms_group_field* group_field = NULL;
    DMS_CHECK_RESULT(DoParseGroupField(field_node, group_field));
    o_field = &group_field->base;
    return 0;
  } else if (type == "sequence") {
    dms_seq_field* seq_field = NULL;
    DMS_CHECK_RESULT(DoParseSequenceField(field_node, seq_field));
    o_field = &seq_field->base;
    return 0;
  } else {
    return DoReadSimpleField(field_node, o_field);
  }
}

static int DoParseChildFields(rapidxml::xml_node<char>* node, 
  std::vector<dms_field*>* o_fields) {
  // read all child nodes
  rapidxml::xml_node<char>* field_node = node->first_node();
  while (NULL != field_node) {
    if (rapidxml::node_element == field_node->type()) {
      dms_field* field = NULL;
      DMS_CHECK_RESULT(DoParseField(field_node, field));
      o_fields->push_back(field);
    }

    // get next child node
    field_node = field_node->next_sibling();
  }
  return 0;
}

static void DoReleaseField(dms_field* field) {
  switch (field->type) {
  case DMS_TYPE_GROUP:
    {
      dms_group_field* group_field = reinterpret_cast<dms_group_field*>(field);
      if (NULL != group_field->children) {
        for (int i = 0; i < group_field->num_of_children; ++i) {
          DoReleaseField(group_field->children[i]);
        }
        delete[] group_field->children;
        group_field->children = NULL;
      }
    }
    break;

  case DMS_TYPE_SEQUENCE:
    {
      dms_seq_field* seq_field = reinterpret_cast<dms_seq_field*>(field);
      if (NULL != seq_field->element_field) {
        DoReleaseField(seq_field->element_field);
        seq_field->element_field = NULL;
      }
    }
    break;

  default:
    break;
  }
  // delete the field
  delete field;
}

int InitSchema(const char* xml_desc, dms_schema* schema) {
  try {
    //DMS_CHECK_RESULT(ReleaseSchema(schema));

    // read the config
    std::stringstream ss(xml_desc);
    rapidxml::file<char> fdoc(ss);
    rapidxml::xml_document<char> doc;
    doc.parse<0>(fdoc.data());

    rapidxml::xml_node<char>* root_node = doc.first_node();
    rapidxml::xml_attribute<char>* id_attr = root_node->first_attribute("id");
    DMS_CHECK_RETURN(NULL != id_attr && 0 != strlen(id_attr->value()), 
      DMS_INVALID);

    int id = atoi(id_attr->value());
    DMS_CHECK_RETURN(0 != id, DMS_INVALID);
    schema->schema_id = id;
    DMS_CHECK_RESULT(DoParseGroupField(root_node, schema->root_field));
  } catch (std::runtime_error& /*e*/) {
    return DMS_INVALID;
  }
  return 0;
}

int ReleaseSchema(dms_schema* schema) {
  if (NULL != schema->root_field) {
    DoReleaseField(&schema->root_field->base);
    schema->root_field = NULL;
  }
  schema->schema_id = 0;
  return 0;
}

} // namespace dms