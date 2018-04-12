#include "dnn_tracker_cpp/draw/object_drawer.h"
#include "dnn_tracker_cpp/draw/object_color.h"
#include "dnn_tracker_cpp/draw/max_size.h"
#include "dnn_tracker_cpp/draw/text_area.h"
#include "dnn_tracker_cpp/draw/object_show_info.h"

namespace dnn {

static
bool
can_show(const child_object_ptr child,
         const dependent_object_ptrs& objects) {
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
can_show(const dependent_object_ptr& object,
         const dependent_object_ptrs& objects) {

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
make_color(const dependent_object_ptr& object,
           const dependent_object_ptrs& objects,
           const object_names& obj_names,
           const target_objects& targets) {

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
draw(cv::InputArray src,
     const dependent_object_ptr& object,
     const dependent_object_ptrs& objects,
     const object_names& obj_names,
     const target_objects& targets,
     text_area& area,
     bool show_details,
     const cv::Size& arrow_size) {

  if (!can_show(object, objects)) {
    return;
  }

  auto outer = object->outer();
  auto inner = object->inner();

  object_show_info info(object, obj_names, show_details);
  background_area bg(src.size(), inner(), max_size(area(info), cv::Size(outer()().w, 0))());
  object_color color = make_color(object, objects, obj_names, targets);

  draw_boundary(src, outer(), color(), area.thickness);
  draw_trace_arrow(src, outer.current_pos, outer.first_pos, arrow_size, color(), area.thickness);
  draw_info_background(src, bg, color());
  draw_info(src, info, area, bg, cv::Scalar::all(0), show_details);

}

void
object_drawer::
draw_boundary(cv::InputArray src,
              region::boundary_box& box,
              cv::Scalar& color,
              int thickness) {
  auto mat = src.getMat();
  cv::rectangle(mat, box.Rect, color, thickness);
}

void
object_drawer::
draw_trace_arrow(cv::InputArray src,
                 region::boundary_box& curr_box,
                 region::boundary_box& first_box,
                 cv::Size arrow_size,
                 cv::Scalar& color,
                 int thickness) {

  auto mat = src.getMat();
  auto first = first_box.center();
  auto current = curr_box.center();
  cv::circle(mat, first, 3, color, thickness, CV_FILLED);
  if (first != current) {
    utils::draw_arrow(mat, first, current, arrow_size, color, thickness);
  }
}

void
object_drawer::
draw_info_background(cv::InputArray src,
                     background_area& bg,
                     cv::Scalar color) {
  auto mat = src.getMat();
  cv::rectangle(mat, bg(), color, CV_FILLED);
}

void
object_drawer::
draw_info(cv::InputArray src,
          object_show_info& info,
          text_area &area,
          background_area& bg,
          cv::Scalar color,
          bool show_details) {

  auto text_pos = bg.inner_lt(area);
  text_pos.y += 3;
  if (info.dependency.empty()) {
    text_pos.y += area.base_line() + 3;
  }

  auto mat = src.getMat();

  cv::putText(mat,
              std::to_string(info.obj_name),
              text_pos,
              area.font, area.font_scale,
              color, area.thickness);

  if (show_details) {
    auto txt_size = cv::getTextSize(std::to_string(info.obj_name),
                                    area.font,
                                    area.font_scale,
                                    area.thickness, 0);

    cv::putText(mat,
                std::to_string(info.count),
                cv::Point((int)(text_pos.x + txt_size.width),
                (int)text_pos.y),
                area.font,
                area.font_scale,
                color,
                area.thickness);
  }
  text_pos.y += area.next_line_offset();

  cv::putText(mat,
              std::to_string(info.dependency),
              text_pos,
              area.font,
              area.font_scale,
              color,
              area.thickness);
}

}

namespace dnn {

void draw_boxes(cv::InputArray src,
                const dependent_object_ptrs& objects,
                const object_names& obj_names,
                const target_objects& targets,
                bool show_details,
                text_area & area) {

  for (auto &object : objects) {
    object_drawer::draw(src,
                        object,
                        objects,
                        obj_names,
                        targets,
                        area,
                        show_details);
  }
}

}


