#include "dnn_tracker_cpp/draw/object_drawer.h"
#include "dnn_tracker_cpp/draw/object_color.h"
#include "dnn_tracker_cpp/draw/max_size.h"
#include "dnn_tracker_cpp/draw/text_area.h"
#include "dnn_tracker_cpp/draw/object_show_info.h"

namespace dnn {

static
bool
can_show(child_object_ptr child,
         dependent_object_ptrs& objects) {
  dnn::dependent_object_ptrs::iterator parent;
  if (!objects.find(child->parent(), parent)) {
    return false;
  }
  if (!parent->get()->CanShow) {
    return false;
  }
  return true;
}
static
bool
can_show(dependent_object_ptr& object,
         dependent_object_ptrs& objects) {

  if (object->appearance() == dependent_object::appearance_property::real) {
    if (!object->CanShow) {
      return false;
    }
  }

  if (object->appearance() == dependent_object::appearance_property::simulate) {
    auto child = to_child_object(object);
    if (child != nullptr && !can_show(child, objects)) {
      return false;
    }
  }

  return true;
}

static
object_color
make_color(
  dependent_object_ptr& object,
  dependent_object_ptrs& objects,
  object_names& obj_names,
  target_objects& targets) {

  auto outer = object->outer();
  if (object->appearance() == dependent_object::appearance_property::real) {
    target_object target;
    if (!targets.find(obj_names[outer()], target)) {
      return object_color::no_color;
    }
    return object_color(object, target, objects, obj_names);
  }

  if (object->appearance() == dependent_object::appearance_property::simulate) {

    auto child = to_child_object(object);
    if (child != nullptr) {
      dnn::dependent_object_ptrs::iterator parent;
      if (!objects.find(child->parent(), parent)) {
        return object_color::no_color;
      }
      target_object parent_target;
      if (!targets.find(obj_names[child->parent()], parent_target)) {
        return object_color::no_color;
      }
      return object_color(*parent, parent_target, objects, obj_names);
    }

    target_object target;
    if (!targets.find(obj_names[object->outer()], target)) {
      return object_color::no_color;
    }
    return object_color(object, target, objects, obj_names);
  }

  return object_color::no_color;
}

}

namespace dnn {

void
object_drawer::
draw(cv::Mat &src,
     dependent_object_ptr& object,
     dependent_object_ptrs& objects,
     object_names& obj_names,
     target_objects& targets,
     text_area& area,
     cv::Size arrow_size) {

  if (!can_show(object, objects)) {
    return;
  }

  auto outer = object->outer();
  auto inner = object->inner();

  object_show_info info(object, obj_names);
  background_area bg(src, inner(), max_size(area(info), cv::Size(outer()().w, 0))());
  object_color color = make_color(object, objects, obj_names, targets);

  draw_boundary(src, outer(), color(), area.thickness);
  draw_trace_arrow(src, outer.current_pos, outer.first_pos, arrow_size, color(), area.thickness);
  draw_info_background(src, bg, color());
  draw_info(src, info, area, bg, cv::Scalar::all(0));

}

void
object_drawer::
draw_boundary(cv::Mat &src,
              region::boundary_box& box,
              cv::Scalar& color,
              int thickness) {
  cv::rectangle(src, box.Rect, color, thickness);
}

void
object_drawer::
draw_trace_arrow(cv::Mat &src,
                 region::boundary_box& curr_box,
                 region::boundary_box& first_box,
                 cv::Size arrow_size,
                 cv::Scalar& color,
                 int thickness) {
  auto first = first_box.center();
  auto current = curr_box.center();
  cv::circle(src, first, 3, color, thickness, CV_FILLED);
  if (first != current) {
    utils::draw_arrow(src, first, current, arrow_size, color, thickness);
  }
}

void
object_drawer::
draw_info_background(cv::Mat &src,
                     background_area& bg,
                     cv::Scalar color) {
  cv::rectangle(src, bg(), color, CV_FILLED);
}

void
object_drawer::
draw_info(cv::Mat &src,
          object_show_info& info,
          text_area &area,
          background_area& bg,
          cv::Scalar color) {
  auto text_pos = bg.inner_lt(area);
  text_pos.y += 3;
  if (info.dependency.empty()) {
    text_pos.y += area.base_line() + 3;
  }

  cv::putText(src,
              std::to_string(info.obj_name), 
              text_pos,
              area.font, area.font_scale,
              color, area.thickness);

  auto txt_size = cv::getTextSize(std::to_string(info.obj_name),
                                  area.font,
                                  area.font_scale,
                                  area.thickness, 0);
  cv::putText(src,
              std::to_string(info.count),
              cv::Point((int)(text_pos.x + txt_size.width),
              (int)text_pos.y),
              area.font,
              area.font_scale,
              color,
              area.thickness);
  text_pos.y += area.next_line_offset();
  cv::putText(src,
              std::to_string(info.dependency),
              text_pos,
              area.font,
              area.font_scale,
              color,
              area.thickness);

}

}

namespace dnn {

void draw_boxes(cv::Mat& src,
                dependent_object_ptrs& objects,
                object_names& obj_names,
                target_objects& targets,
                text_area & area) {

  for (auto &object : objects) {
    object_drawer::draw(src,
                        object,
                        objects,
                        obj_names,
                        targets,
                        area);
  }
}

}

