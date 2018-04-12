#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_OBJECT_DRAWER_H__
#define __DNN_TRACKER_CPP_DRAW_OBJECT_DRAWER_H__
#include "dnn_tracker_cpp/draw/background_area.h"
#include "dnn_tracker_cpp/object.h"

namespace dnn {

class object_drawer {
public:

  DNNTRR_API static void draw(cv::InputArray src,
                              const dependent_object_ptr& object,
                              const dependent_object_ptrs& objects,
                              const object_names& obj_names,
                              const target_objects& targets,
                              text_area& area,
                              bool show_details = true,
                              const cv::Size& arrow_size = cv::Size(5, 10));

private:
  static void draw_boundary(cv::InputArray src,
                            region::boundary_box& box,
                            cv::Scalar& color,
                            int thickness = 5);

  static void draw_trace_arrow(cv::InputArray src,
                               region::boundary_box& curr_box,
                               region::boundary_box& first_box,
                               cv::Size arrow_size,
                               cv::Scalar& color,
                               int thickness = 5);

  static void draw_info_background(cv::InputArray src,
                                   background_area& bg,
                                   cv::Scalar color);

  static void draw_info(cv::InputArray src,
                        object_show_info& info,
                        text_area &area,
                        background_area& bg,
                        cv::Scalar color,
                        bool show_details = true);
};

}

namespace dnn {

DNNTRR_API void draw_boxes(cv::InputArray src,
                           const dependent_object_ptrs& objects,
                           const object_names& obj_names,
                           const target_objects& targets,
                           bool show_details = true,
                           text_area & area = text_area(cv::FONT_HERSHEY_COMPLEX_SMALL, 1.2, 2));

}

#endif //__DNN_TRACKER_CPP_DRAW_OBJECT_DRAWER_H__
