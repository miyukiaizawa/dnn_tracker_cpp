#include "dnn_tracker_cpp/region/distance.h"

namespace dnn {
namespace region {

distance::
distance() :
  distance_(0) {}

distance::
distance(double value) :
  distance_(value) {}

distance::
distance(cv::Point sp, cv::Point ep, bool abs) :
  distance_((abs) ? calc_distance(sp, ep) : abs_distance(sp, ep)) {}

double distance(double x, double y, double x2, double y2) {
  return std::pow((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y), 0.5);
  // or
  // std::sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
}

double
distance::
operator()() const {
  return distance_;
}

double
distance::
calc_distance(cv::Point sp, cv::Point ep) {
  return std::pow((ep.x - sp.x) * (ep.x - sp.x)
                  + (ep.y - sp.y) * (ep.y - sp.y), 0.5);
}

double
distance::
abs_distance(cv::Point sp, cv::Point ep) {
  return std::abs(calc_distance(sp, ep));
}

}
}

