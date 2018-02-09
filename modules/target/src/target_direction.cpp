#include "dnn_tracker_cpp/target/target_direction.h"

namespace dnn {

target_direction::
target_direction() :
  up(false),
  left(false),
  right(false),
  down(false),
  stop(false) {}

target_direction::
target_direction(bool _up,
                 bool _left,
                 bool _down,
                 bool _right,
                 bool _stop) :
  up(_up),
  left(_left),
  right(_right),
  down(_down),
  stop(_stop) {}

target_direction::
target_direction(region::direction dir) :
  up(false),
  left(false),
  right(false),
  down(false),
  stop(false) {

  if ((dir & region::direction::state::up) != region::direction::state::none) {
    up = true;
  }
  if ((dir & region::direction::state::left) != region::direction::state::none) {
    left = true;
  }
  if ((dir & region::direction::state::down) != region::direction::state::none) {
    down = true;
  }
  if ((dir & region::direction::state::right) != region::direction::state::none) {
    right = true;
  }
  if ((dir & region::direction::state::stop) != region::direction::state::none) {
    stop = true;
  }
}

bool
target_direction::
valid_direction(region::direction dir) const {
  bool dst = false;
  dst |= (up) && ((dir & region::direction::state::up) != region::direction::state::none);
  dst |= (left) && ((dir & region::direction::state::left) != region::direction::state::none);
  dst |= (down) && ((dir & region::direction::state::down) != region::direction::state::none);
  dst |= (right) && ((dir & region::direction::state::right) != region::direction::state::none);
  dst |= (stop) && (dir == region::direction::state::stop);
  return dst;
}

}

namespace dnn {

target_direction to_target_direction(region::direction dir) {

  bool up = false, left = false, down = false, right = false, stop = false;

  if ((dir & region::direction::state::up) != region::direction::state::none) {
    up = true;
  }
  if ((dir & region::direction::state::left) != region::direction::state::none) {
    left = true;
  }
  if ((dir & region::direction::state::down) != region::direction::state::none) {
    down = true;
  }
  if ((dir & region::direction::state::right) != region::direction::state::none) {
    right = true;
  }
  if ((dir & region::direction::state::stop) != region::direction::state::none) {
    stop = true;
  }
  return target_direction(up, left, down, right, stop);
}

}

namespace dnn {

target_direction
to_target_direction(const std::tstring& str) {
  region::direction state = region::direction::state::none;

  if (str.find(_T("down")) != str.npos) {
    state |= region::direction::state::down;
  }
  if (str.find(_T("ignore")) != str.npos) {
    state |= region::direction::state::ignore;
  }
  if (str.find(_T("left")) != str.npos) {
    state |= region::direction::state::left;
  }
  if (str.find(_T("none")) != str.npos) {
    state |= region::direction::state::none;
  }
  if (str.find(_T("right")) != str.npos) {
    state |= region::direction::state::right;
  }
  if (str.find(_T("stop")) != str.npos) {
    state |= region::direction::state::stop;
  }
  if (str.find(_T("up")) != str.npos) {
    state |= region::direction::state::up;
  }
  return target_direction(state);
}

target_direction
to_target_direction(bool up,
                    bool down,
                    bool left,
                    bool right,
                    bool stop) {
  region::direction state = region::direction::state::none;
  if (up) {
    state |= region::direction::state::up;
  }
  if (down) {
    state |= region::direction::state::down;
  }
  if (left) {
    state |= region::direction::state::left;
  }
  if (right) {
    state |= region::direction::state::right;
  }
  if (stop) {
    state |= region::direction::state::stop;
  }
  return target_direction(state);
}

}

