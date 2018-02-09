#include "dnn_tracker_cpp/draw/background_area.h"

namespace dnn {

background_area::
background_area(cv::Mat& src,
                region::boundary_box& box,
                cv::Size& max_size) {
  area_ = make_background_rect(src, box, max_size);
}

cv::Rect
background_area::
operator()() { return area_; }

cv::Point
background_area::
inner_lt(text_area &area) {
  return cv::Point(area_.x,
                   area_.y + area.line_height());
}

cv::Rect
background_area::
make_background_rect(cv::Mat& src,
                     region::boundary_box& box,
                     cv::Size& max_size) {
  return
    cv::Rect(std::max(box.X - 0, 0),
             std::max(box.Y - max_size.height, 0),
             std::min(max_size.width, src.cols - 1),
             std::min(max_size.height, src.rows - 1));
}

}


