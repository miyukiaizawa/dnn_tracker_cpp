#include "dnn_tracker_cpp/region/collision.h"

namespace dnn {
namespace region {

collision::
collision() :
  left(state::any),
  top(state::any),
  right(state::any),
  bottom(state::any) {}

collision::
collision(state _left,
          state _top,
          state _right,
          state _bottom) :
  left(_left),
  top(_top),
  right(_right),
  bottom(_bottom) {}

bool
collision::
detect(int sx1, int sy1, int ex1, int ey1,
       int sx2, int sy2, int ex2, int ey2) {
  bool ret = true;
  ret &= check_gather_or_less(left, sx1, sx2);
  ret &= check_gather_or_less(top, sy1, sy2);
  ret &= check_gather_or_less(right, ex1, ex2);
  ret &= check_gather_or_less(bottom, ey1, ey2);
  return ret;
}

bool
collision::
detect(cv::Rect r1, cv::Rect r2) {
  return detect(r1.x, r1.y, r1.x + r1.width, r1.y + r1.height,
                r2.x, r2.y, r2.x + r2.width, r2.y + r2.height);
}

bool
collision::
detect(cv::Point sp1, cv::Point ep1,
       cv::Point sp2, cv::Point ep2) {
  return detect(sp1.x, sp1.y, ep1.x, ep1.y,
                sp2.x, sp2.y, ep2.x, ep2.y);
}

bool
collision::
greater(int v1, int v2) {
  return v1 > v2;
}

bool
collision::
less(int v1, int v2) {
  return v1 < v2;
}

bool
collision::
check_gather_or_less(state& state, int v1, int v2) {
  switch (state) {
  case state::greater:
    return greater(v1, v2);
  case state::less:
    return less(v1, v2);
  case state::any:
    return less(v1, v2) || greater(v1, v2) || v1 == v2;
  case state::ignore:
    return true;
  }
  return false;
}

}

namespace region {

collision
any_collision() {
  return collision(collision::state::any,
                   collision::state::any,
                   collision::state::any,
                   collision::state::any);
}

//□:should be set to parent object (car)
collision
contain_collision() {
  return collision(collision::state::less,
                   collision::state::less,
                   collision::state::greater,
                   collision::state::greater);
}

//= : collision is avairable only top & bottom side
collision
within_vertical_collision() {
  return collision(collision::state::greater,
                   collision::state::less,
                   collision::state::less,
                   collision::state::greater);
}

//|| : collision is avairable only left and right side
collision
within_horizontal_collision() {
  return collision(collision::state::less,
                   collision::state::greater,
                   collision::state::greater,
                   collision::state::less);
}

//凸 : should be set to parent object which is viechle which people is riding
collision
convex_collision() {
  return collision(collision::state::less,    //self x is less then another x
                   collision::state::greater, //self y is greater then another y
                   collision::state::greater, //self w is greater then another w
                   collision::state::greater);//self h is greater then another h
}

//凸 : should be set to parent object which is viechle which people is riding
collision
convex_or_within_horizontal_collision() {
  return collision(collision::state::less,
                   collision::state::greater,
                   collision::state::greater,
                   collision::state::any);
}


//凹
collision
concavity_collision() {
  return collision(collision::state::less,
                   collision::state::less,
                   collision::state::greater,
                   collision::state::greater);
}

}

namespace region {

std::tstring
to_tstring(const collision::state& state) {
  switch (state) {
  case collision::state::greater:
    return _T("greater");
  case collision::state::less:
    return _T("less");
  case collision::state::ignore:
    return _T("ignore");
  case collision::state::any:
    return _T("any");
  case collision::state::none:
    return _T("none");
  }
  return _T("none");
}

collision::state
to_collision(const std::tstring & state) {

  if (state.find(_T("greater")) != state.npos) {
    return collision::state::greater;
  }
  if (state.find(_T("less")) != state.npos) {
    return collision::state::less;
  }
  if (state.find(_T("ignore")) != state.npos) {
    return collision::state::ignore;
  }
  if (state.find(_T("any")) != state.npos) {
    return collision::state::any;
  }
  if (state.find(_T("none")) != state.npos) {
    return collision::state::none;
  }
  return collision::state::none;
}

}
}
