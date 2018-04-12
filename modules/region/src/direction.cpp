#include "dnn_tracker_cpp/region/direction.h"

namespace dnn {
namespace region {
direction::
direction() :
  state_(state::stop) {}

direction::
direction(state_t _state) :
  state_(static_cast<state>(_state)) {}

direction::
direction(state _state) :
  state_(_state) {}

direction::
direction(const direction& dir) :
  state_(dir.state_) {}

direction::
direction(cv::Point first_pos, cv::Point current_pos) :
  state_(calc_direction(first_pos, current_pos)) {}

direction::state_t
direction::
operator()() const {
  return static_cast<state_t>(state_);
}

void
direction::
operator=(state_t v) {
  state_ = static_cast<state>(v);
}

direction&
direction::
operator =(const direction& v) {
  this->state_ = v.state_;
  return (*this);
}

direction::state&
direction::
operator =(const state& v) {
  state_ = static_cast<state>(static_cast<state_t>(v));
  return state_;
}

direction::state&
direction::
operator |=(const state& v) {
  state_ = static_cast<state>(static_cast<state_t>(v) | static_cast<state_t>(state_));
  return state_;
}

direction&
direction::
operator |=(const direction& v) {
  state_ = static_cast<state>(static_cast<state_t>(v.state_) | static_cast<state_t>(state_));
  return (*this);
}

direction::state&
direction::
operator &=(const state& v) {
  state_ = static_cast<state>(static_cast<state_t>(v) & static_cast<state_t>(state_));
  return state_;
}

direction&
direction::
operator &=(const direction& v) {
  state_ = static_cast<state>(static_cast<state_t>(v.state_) & static_cast<state_t>(state_));
  return (*this);
}

bool
direction::
operator ==(const state& v) {
  return static_cast<state_t>(v) == static_cast<state_t>(state_);
}

bool
direction::
operator ==(const direction& v) {
  return static_cast<state_t>(v.state_) == static_cast<state_t>(state_);
}

bool
direction::
operator <(const direction& v) const {
  return (state_ < v.state_);
}


direction::state
direction::
calc_direction(cv::Point first_pt, cv::Point currnt_pt) {
  state_t dst = static_cast<state_t>(state::none);
  if (first_pt.x < currnt_pt.x) {
    dst |= static_cast<state_t>(state::right);
  }
  else if (currnt_pt.x < first_pt.x) {
    dst |= static_cast<state_t>(state::left);
  }
  else {
    dst |= static_cast<state_t>(state::hstop);
  }

  if (first_pt.y < currnt_pt.y) {
    dst |= static_cast<state_t>(state::down);
  }
  else if (currnt_pt.y < first_pt.y) {
    dst |= static_cast<state_t>(state::up);
  }
  else {
    dst |= static_cast<state_t>(state::vstop);
  }

  return static_cast<state>(dst);
}

direction::state
operator &(const direction& v1, const direction::state& v2) {
  return static_cast<direction::state>(v1() & static_cast<direction::state_t>(v2));
}

direction::state
operator |(const direction& v1, const direction::state& v2) {
  return static_cast<direction::state>(v1() | static_cast<direction::state_t>(v2));
}

direction
operator &(const direction& v1, const direction& v2) {
  return direction(v1() & v2());
}

direction
operator |(const direction& v1, const direction& v2) {
  return direction(v1() | v2());
}

}
}