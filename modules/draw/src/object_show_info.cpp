#include "dnn_tracker_cpp/draw/object_show_info.h"

namespace dnn {

object_show_info::
object_show_info(const dependent_object_ptr& obj,
                 const object_names& obj_names,
                 bool show_details) :
  obj_name(),
  count(),
  dependency(),
  strings({ &obj_name, &count, &dependency }) {
  make_messages(obj, obj_names, show_details);
}

void
object_show_info::
make_messages(const dependent_object_ptr& obj,
              const object_names& obj_names,
              bool show_details) {
  auto inner = obj->inner();
  make_object_name(obj, obj_names, show_details);
  make_count_info(inner());
  make_dependency(obj, obj_names, true); // should always show object id of relative objects.
}

void
object_show_info::
make_object_name(const dependent_object_ptr& obj,
                 const object_names& obj_names,
                 bool show_details) {

  std::tstringstream tss;
  auto inner = obj->inner();

  tss << obj_names.get(inner());
  if (tss.str().empty()) { return; }

  if (!obj->IsConfirmed) {
    tss << _T("?");
  }

  if (show_details) {
    tss << _T("(") << (int)(inner.Prob * 100) << _T("%)");
    tss << _T("[No.") << inner.TrackId << _T("]");
  }

  obj_name = tss.str();
}

void
object_show_info::
make_count_info(const region::boundary_box& inner) {
  std::tstringstream tss;
  tss << _T(" (") << inner.Count << _T(")");
  count = tss.str();
}

void
object_show_info::
make_dependency(const dependent_object_ptr& obj,
                const object_names& obj_names,
                bool show_details) {

  if (obj_names.get(obj->outer()).empty()) {
    return;
  }
  if (obj->appearance() == dependent_object::appearance_property::real) {
    return;
  }

  std::tstringstream tss;
  auto parent = dynamic_cast<parent_object*>(obj.get());
  if (parent != nullptr && !parent->children().empty()) {
    tss << _T(" (children) ") << make_children_names(*parent, obj_names, show_details);
  }
  auto child = dynamic_cast<child_object*>(obj.get());
  if (child != nullptr && !child->parent().empty()) {
    tss << _T(" (parent) ") << make_parent_name(*child, obj_names, show_details);
  }

  dependency = tss.str();
}

}