#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_BACKGROUND_AREA_H__
#define __DNN_TRACKER_CPP_DRAW_BACKGROUND_AREA_H__

#include "dnn_tracker_cpp/draw/text_area.h"

namespace dnn {

class background_area {
public:
  DNNTRR_API background_area(const cv::Size& image_size, 
                             const region::boundary_box& box, 
                             const cv::Size& max_size);

  DNNTRR_API cv::Rect operator()();
  DNNTRR_API cv::Point inner_lt(const text_area &area);

private:
  cv::Rect make_background_rect(const cv::Size& image_size, 
                                const region::boundary_box& box, 
                                const cv::Size& max_size);
private:
  cv::Rect area_;
};

}

#endif //__DNN_TRACKER_CPP_DRAW_BACKGROUND_AREA_H__
