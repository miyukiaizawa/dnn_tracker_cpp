#include "dnn_tracker_cpp/draw/text_area.h"

namespace dnn {

text_area::
text_area(cv::HersheyFonts _font, double _font_scale, int _thickness) :
  text_area_(0, 0),
  line_count_(0),
  font(_font),
  font_scale(_font_scale),
  thickness(_thickness) {}

cv::Size
text_area::
operator()(const object_show_info &info) {
  text_area_ = calc_text_area(info);
  line_count_ = (int)info.strings.size();
  return text_area_;
}

cv::Size
text_area::
calc_text_area(const object_show_info &info) {

  cv::Size dest(0, 0);

  int name_baseline = 0;
  auto name = get_text_size(info.obj_name, &name_baseline);

  int count_baseline = 0;
  auto count = get_text_size(info.count, &count_baseline);

  int dep_baseline = 0;
  auto dep = get_text_size(info.dependency, &dep_baseline);

  dest.width = std::max(std::max(dest.width, (name.width + count.width)), dep.width);
  base_line_ = std::max(std::max(name_baseline, count_baseline), dep_baseline);

  dest.height += (name.height + base_line_);
  if (!info.dependency.empty()) {
    dest.height += (dep.height + base_line_);
  }
  dest.height += (base_line_);


  return dest;
}

cv::Size
text_area::
get_text_size(const std::tstring& text, int* baseline) {
  return getTextSize(to_string(text),
                     font,
                     font_scale,
                     thickness,
                     baseline);
}


int
text_area::
line_height() const { return (int)(text_area_.height / (double)line_count_); }

int
text_area::
base_line() const { return base_line_; }

int
text_area::
next_line_offset() const { return line_height() + base_line(); }

}
