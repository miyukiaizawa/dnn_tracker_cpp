#include "dnn_tracker_cpp/core/utils.h"
#include "akstdutils/akstdutils.h"

namespace dnn {

/* for geomery
******************************************************************************/
namespace utils {

cv::Point center(int x, int y, int w, int h) {
  return cv::Point(x + w / 2, y + h / 2);
}

cv::Point center(cv::Point lt, cv::Size size) {
  return center(lt.x, lt.y, size.width, size.height);
}

bool is_cross(int sx1, int sy1, int ex1, int ey1, int sx2, int sy2, int ex2, int ey2) {
  return
    std::abs((int)(sx1 - sx2)) < ex1 / 2.0 + ex2 / 2.0 &&
    std::abs((int)(sy1 - sy2)) < ey1 / 2.0 + ey2 / 2.0;
}

bool is_cross(cv::Point sp1, cv::Point ep1, cv::Point sp2, cv::Point ep2) {
  return is_cross(sp1.x, sp1.y, ep1.x, ep1.y, sp2.x, sp2.y, ep2.x, ep2.y);
}

bool contain(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return (x1 < x2) && ((x2 + w2) < (x1 + w1)) && (y1 < y2) && ((y2 + h2) < (y1 + h1));
}

bool contain(cv::Rect parent, cv::Rect child) {
  return contain(parent.x, parent.y, parent.width, parent.height,
                 child.x, child.y, child.width, child.height);
}

}


/* for draw
******************************************************************************/
namespace utils {

static
void draw_arrow_tip(cv::Mat &img, cv::Point2f pt2, cv::Point2f up, cv::Size arrow_size,
                    cv::Scalar color, int thickness = 1, int lineType = 8, int shift = 0) {

  cv::Point2f ptl(
    (pt2.x - up.y*arrow_size.width - up.x*arrow_size.height),
    (pt2.y + up.x*arrow_size.width - up.y*arrow_size.height));
  cv::Point2f ptr(
    (pt2.x + up.y*arrow_size.width - up.x*arrow_size.height),
    (pt2.y - up.x*arrow_size.width - up.y*arrow_size.height));

  cv::line(img, pt2, ptl, color, thickness, lineType, shift);
  cv::line(img, pt2, ptr, color, thickness, lineType, shift);

}

void draw_arrow(cv::Mat &img, cv::Point2f pt1, cv::Point2f pt2, cv::Size arrow_size,
                cv::Scalar color, int thickness, int lineType, int shift) {

  cv::Point2f vp((pt2.x - pt1.x), (pt2.y - pt1.y));
  float v = sqrt(vp.x*vp.x + vp.y*vp.y);
  if (v == 0) {
    v = 1;
  }
  cv::Point2f up((vp.x / v), (vp.y / v));

  cv::line(img, pt1, pt2, color, thickness, lineType, shift);
  draw_arrow_tip(img, pt2, up, arrow_size, color, thickness, lineType, shift);

}

}

}