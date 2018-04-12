#include "dnn_tracker_cpp/region/contours.h"
#include "dnn_tracker_cpp/region/distance.h"

namespace dnn {
namespace region {

contours::
contours() :
  data_() {}

contours::contours_t&
contours::
operator()() {
  return data_;
}
convexhull&
contours::
operator[](int index) {
  return data_[index];
}

void
contours::
push_back(const convexhull& _convexhull) {
  data_.push_back(_convexhull);
}

void
contours::
push_back(const cv::Rect& area) {
  auto convex = to_convexhull(area);
  sort(convex);
  data_.push_back(convex);
}

void
contours::
push_back(const cv::Point& tl, const cv::Point& br) {
  auto convex = to_convexhull(tl, br);
  sort(convex);
  data_.push_back(convex);
}

void
contours::
push_back(const cv::Point2f& tl, const cv::Point2f& br) {
  auto convex = to_convexhull(tl, br);
  sort(convex);
  data_.push_back(convex);
}

void
contours::
erase(iterator it) {
  data_.erase(it);
}

void
contours::
clear() {
  data_.clear();
}

void
contours::
resize(size_t size) {
  data_.resize(size);
}

size_t
contours::
capacity() const {
  return data_.capacity();
}

size_t
contours::
size() const {
  return data_.size();
}

contours::iterator
contours::
begin() {
  return data_.begin();
}

contours::const_iterator
contours::
begin() const {
  return data_.begin();
}

contours::iterator
contours::
end() {
  return data_.end();
}

contours::const_iterator
contours::
end() const {
  return data_.end();
}

bool
contours::
empty() const {
  return data_.empty();
}


std::vector<contours::iterator>
contours::
find_areas_including_pt(cv::Point2f &pt) {
  std::vector<iterator>  its;
  for (auto it = data_.begin(); it != data_.end(); ++it) {
    auto convex = *it;
    if (winding_number(convex, pt)) {
      its.push_back(it);
    }
  }
  return its;
}

contours::iterator
contours::
find_closest_area(cv::Point2f pt) {

  //点が含まれている多角形領域を検出
  auto areas = find_areas_including_pt(pt);

  //多角形領域の中から重心との距離が最も近しい領域を検索
  int min_dist = INT_MAX;
  iterator it = data_.end();
  for (auto convex = areas.begin(); convex != areas.end(); ++convex) {
    auto curr_dist = distance(pt, center(*(*convex)), true)();
    if (min_dist > curr_dist) {
      min_dist = (int)curr_dist;
      it = *convex;
    }
  }
  return it;
}


}
}