#include "dnn_tracker_cpp/region/convexhull.h"

namespace dnn {
namespace region {

convexhull
to_convexhull(const cv::Rect& rect) {
  convexhull dst;
  dst.push_back(rect.tl());
  dst.push_back(rect.br());
  return dst;
}
convexhull
to_convexhull(const cv::Point& tl, const cv::Point& br) {
  convexhull dst;
  dst.push_back(tl);
  dst.push_back(br);
  return dst;
}
convexhull
to_convexhull(const cv::Point2f& tl, const cv::Point2f& br) {
  convexhull dst;
  dst.push_back(tl);
  dst.push_back(br);
  return dst;
}

bool winding_number(const convexhull& convex, const cv::Point2f &pt) {
  if (convex.empty()) {
    return false;
  }
  int winding_number = 0;
  for (int index = 0; index < convex.size() - 2; index++) {
    if (convex[index].y <= pt.y && convex[index + 1].y > pt.y) {
      auto vt = (pt.y - convex[index].y) / (convex[index + 1].y - convex[index].y);
      if (pt.x < (convex[index].x + (vt * (convex[index + 1].x - convex[index].x)))) {
        ++winding_number;
      }
    }
    else if (convex[index].y > pt.y && convex[index + 1].y <= pt.y) {
      auto vt = (pt.y - convex[index].y) / (convex[index + 1].y - convex[index].y);
      if (pt.x < (convex[index].x + (vt * (convex[index + 1].x - convex[index].x)))) {
        --winding_number;
      }
    }
  }
  return (winding_number > 0);
}
bool winding_number(const convexhull& convex, const cv::Point &pt) {
  return winding_number(convex, cv::Point2f((float)pt.x, (float)pt.y));
}

void sort(convexhull& convex) {
  cv::Mat contour = cv::Mat(convex);
  convexhull approx;
  cv::convexHull(contour, approx);
  convex = approx;
}

cv::Point2f center(const convexhull& _convexhull) {
  cv::Point2f pt;
  for (int index = 0; index < _convexhull.size(); index++) {
    pt.x += _convexhull[index].x;
    pt.y += _convexhull[index].y;
  }
  pt /= (double)_convexhull.size();
  return pt;
}

}
}