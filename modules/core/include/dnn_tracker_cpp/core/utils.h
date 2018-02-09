#pragma once
#ifndef __DNN_TRACKER_CORE_UTILS_H__ 
#define __DNN_TRACKER_CORE_UTILS_H__ 

#include "akstdutils/akstdutils.h"
#include "opencv2/opencv.hpp"

namespace dnn {

/*******************************************************************************
* Utils
******************************************************************************/
namespace utils {

template<typename _T>
bool in_range(_T v, _T min, _T max) {
  return((min < v) && (v < max));
}

template<class _T, typename _F>
auto find_if(_T &vec_type, _F func) {
  return std::find_if(vec_type.begin(), vec_type.end(), func);
}

template<class _T, class _IT, typename _F>
bool find_if(_T &vec_type, _IT & it, _F func) {
  it = std::find_if(vec_type.begin(), vec_type.end(), func);
  return (it != vec_type.end());
}

template<class T, typename F>
bool erase_if(T& vec, F& func) {
  bool ret = false;
  for (auto it = vec.begin(); it != vec.end();) {
    if (func(*it)) {
      it = vec.erase(it);
      ret = true;
    }
    else {
      it++;
    }
  }
  return ret;
}


}

/* for for geomery
******************************************************************************/
namespace utils {
cv::Point center(int x, int y, int w, int h);

cv::Point center(cv::Point lt, cv::Size size);

bool is_cross(int sx1, int sy1, int ex1, int ey1, int sx2, int sy2, int ex2, int ey2);

bool is_cross(cv::Point sp1, cv::Point ep1, cv::Point sp2, cv::Point ep2);

bool contain(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

bool contain(cv::Rect parent, cv::Rect child);

}

/* for draw
******************************************************************************/
namespace utils {
void draw_arrow(cv::Mat &img, cv::Point2f pt1, cv::Point2f pt2, cv::Size arrow_size,
                cv::Scalar color, int thickness = 1, int lineType = 8, int shift = 0);
}

}



#endif //__DNN_TRACKER_CORE_UTILS_H__ 
