#include "dnn_tracker_cpp/draw/max_size.h"

namespace dnn {

max_size::
max_size(cv::Size a, cv::Size b) {
  size_ = cv::Size(std::max(a.width, b.width), std::max(a.height, b.height));
}

max_size::
max_size(cv::Size a, int bx, int by) :
  max_size(a, cv::Size(bx, by)) {}

max_size::
max_size(int ax, int ay, int bx, int by) :
  max_size(cv::Size(ax, ay), cv::Size(bx, by)) {}

max_size::
max_size(int ax, int ay, cv::Size b) :
  max_size(cv::Size(ax, ay), b) {}

cv::Size&
max_size::
operator()() { return size_; }

}


