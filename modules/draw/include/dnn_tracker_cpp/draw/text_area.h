#pragma once
#ifndef __DNN_TRACKER_CPP_DRAW_TEXT_AREA_H__
#define __DNN_TRACKER_CPP_DRAW_TEXT_AREA_H__
#include "opencv2/opencv.hpp"
#include "dnn_tracker_cpp/draw/object_show_info.h"

namespace dnn {

class text_area {
public:
  DNNTRR_API text_area(cv::HersheyFonts font, double font_scale, int thickness);
  DNNTRR_API cv::Size operator()(const object_show_info &info);
  DNNTRR_API int line_height();
  DNNTRR_API int base_line();
  DNNTRR_API int next_line_offset();
private:
  cv::Size calc_text_area(const object_show_info &info);
  cv::Size get_text_size(const std::tstring& text, int* baseline);

public:
  cv::HersheyFonts font;
  double font_scale;
  int thickness;

private:
  cv::Size text_area_;
  int line_count_;
  int base_line_;
};

}

#endif //__DNN_TRACKER_CPP_DRAW_TEXT_AREA_H__
