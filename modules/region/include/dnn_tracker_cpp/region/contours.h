#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_CONTOURS_H__
#define __DNN_TRACKER_CPP_REGION_CONTOURS_H__
#include "dnn_tracker_cpp/region/convexhull.h"

namespace dnn {
namespace region {

class contours {
public:
  using contours_t = std::vector<convexhull>;
  using iterator = contours_t::iterator;
  using const_iterator = contours_t::const_iterator;

  DNNTRR_API contours();

  DNNTRR_API contours_t& operator()();
  DNNTRR_API convexhull& operator[](int index);

  DNNTRR_API void push_back(const convexhull& _convexhull);
  DNNTRR_API void push_back(const cv::Rect& area);
  DNNTRR_API void push_back(const cv::Point& tl, const cv::Point& br);
  DNNTRR_API void push_back(const cv::Point2f& tl, const cv::Point2f& br);

  DNNTRR_API void erase(iterator it);
  DNNTRR_API void clear();
  DNNTRR_API void resize(size_t size);
  DNNTRR_API size_t capacity() const;
  DNNTRR_API size_t size() const;

  DNNTRR_API iterator begin();
  DNNTRR_API const_iterator begin() const;
  DNNTRR_API iterator end();
  DNNTRR_API const_iterator end() const;

  DNNTRR_API bool empty() const;

  DNNTRR_API std::vector<iterator> find_areas_including_pt(cv::Point2f &pt);

  DNNTRR_API iterator find_closest_area(cv::Point2f pt);

protected:
  contours_t data_;
};

}
}


#endif //__DNN_TRACKER_CPP_REGION_CONTOURS_H__
