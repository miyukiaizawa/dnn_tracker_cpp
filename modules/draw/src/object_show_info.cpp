#include "dnn_tracker_cpp/draw/object_show_info.h"

namespace dnn {

object_show_info::
object_show_info(dependent_object_ptr& obj,
                 object_names& obj_names, 
                 bool show_details) :
  obj_name(),
  count(),
  dependency(),
  strings({ &obj_name, &count, &dependency }) {
  make_messages(obj, obj_names, show_details);
}

void
object_show_info::
make_messages(dependent_object_ptr& obj,
              object_names& obj_names,
              bool show_details) {
  auto inner = obj->inner();
  make_object_name(inner(), obj_names, obj->IsCertainCount, show_details);
  make_count_info(inner());
  make_dependency(obj, obj_names, true); // should always show object id of relative objects.
}

void
object_show_info::
make_object_name(region::boundary_box& inner,
                 object_names& obj_names,
                 bool is_certain_count,
                 bool show_details) {

  std::tstringstream tss;

  tss << obj_names.get(inner());
  if (tss.str().empty()) { return; }

  if (!is_certain_count) { tss << _T("?"); }

  if (show_details) {
    tss << _T("(") << (int)(inner.Prob * 100) << _T("%)");
    tss << _T("[No.") << inner.TrackId << _T("]");
  }

  obj_name = tss.str();
}

void
object_show_info::
make_count_info(region::boundary_box& inner) {
  std::tstringstream tss;
  tss << _T(" (") << inner.Count << _T(")");
  count = tss.str();
}

void
object_show_info::
make_dependency(dependent_object_ptr& obj,
                object_names& obj_names, 
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