#include "dnn_tracker_cpp/draw/background_area.h"

namespace dnn {

background_area::
background_area(const cv::Size& image_size,
                const region::boundary_box& box,
                const cv::Size& max_size) {
  area_ = make_background_rect(image_size, box, max_size);
}

cv::Rect
background_area::
operator()() { return area_; }

cv::Point
background_area::
inner_lt(const text_area &area) {
  return cv::Point(area_.x,
                   area_.y + area.line_height());
}

cv::Rect
background_area::
make_background_rect(const cv::Size& image_size,
                     const region::boundary_box& box,
                     const cv::Size& max_size) {
  return
    cv::Rect(std::max(box.X - 0, 0),
             std::max(box.Y - max_size.height, 0),
             std::min(max_size.width, image_size.width - 1),
             std::min(max_size.height, image_size.height - 1));
}

}


