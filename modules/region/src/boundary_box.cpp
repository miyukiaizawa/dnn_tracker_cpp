#include "dnn_tracker_cpp/region/boundary_box.h"

namespace dnn {
namespace region {

boundary_box::
boundary_box() :
  box_({ 0 }),
  name_() {
  set_properties();
}

boundary_box::
boundary_box(const core::bbox_t& _box) :
  box_(_box),
  name_() {
  set_properties();
}

boundary_box::
boundary_box(const boundary_box& _box) {
  box_ = _box.box_;
  name_ = _box.name_;
  set_properties();
}



void
boundary_box::
set_properties() {
  X(this);
  Y(this);
  Width(this);
  Height(this);
  ObjectId(this);
  TrackId(this);
  Count(this);
  Prob(this);
  ObjectName(this);
  Size(this);
  LT(this);
  BR(this);
  Rect(this);
}

boundary_box&
boundary_box::
operator=(const boundary_box &box) {
  box_ = box.box_;
  name_ = box.name_;
  return (*this);
}

core::bbox_t&
boundary_box::
operator()() {
  return box_;
}

const core::bbox_t&
boundary_box::
operator()() const {
  return box_;
}

bool
boundary_box::
operator==(const boundary_box &box) const {
  bool ret = true;
  ret &= X() == box.X();
  ret &= Y() == box.Y();
  ret &= Width() == box.Width();
  ret &= Height() == box.Height();
  ret &= ObjectId() == box.ObjectId();
  ret &= TrackId() == box.TrackId();
  ret &= Prob() == box.Prob();
  ret &= Count() == box.Count();
  ret &= ObjectName() == box.ObjectName();
  return ret;
}

bool
boundary_box::
operator!=(const boundary_box &box) const {
  bool ret = false;
  ret |= X() != box.X();
  ret |= Y() != box.Y();
  ret |= Width() != box.Width();
  ret |= Height() != box.Height();
  ret |= ObjectId() != box.ObjectId();
  ret |= TrackId() != box.TrackId();
  ret |= Prob() != box.Prob();
  ret |= Count() != box.Count();
  ret |= ObjectName() != box.ObjectName();
  return ret;
}

bool
boundary_box::
is_same_id(const boundary_box &box) const {
  bool ret = true;
  ret &= ObjectId() == box.ObjectId();
  ret &= TrackId() == box.TrackId();
  return ret;
}


bool
boundary_box::
empty() const {
  bool ret = true;
  ret &= X == 0;
  ret &= Y == 0;
  ret &= Width == 0;
  ret &= Height == 0;
  ret &= ObjectId == 0;
  ret &= TrackId == 0;
  ret &= Prob == 0;
  ret &= Count == 0;
  auto tes = ObjectName;
  ret &= ObjectName().empty();
  return ret;
}

void
boundary_box::
clear() {
  X = 0;
  Y = 0;
  Width = 0;
  Height = 0;
  ObjectId = 0;
  TrackId = 0;
  Count = 0;
  Prob = 0;
}

cv::Point
boundary_box::
center() const { return cv::Size((int)(X + Width / 2.0), (int)(Y + Height / 2.0)); }

int
boundary_box::
area() const { return width() * height(); }

Define_Property(int, boundary_box, x,
{ return box_.x; },
{ return box_.x = value; })

Define_Property(int, boundary_box, y,
{ return box_.y; },
{ return box_.y = value; })

Define_Property(int, boundary_box, width,
{ return box_.w; },
{ return box_.w = value; })

Define_Property(int, boundary_box, height,
{ return box_.h; },
{ return box_.h = value; })

Define_Property(int, boundary_box, obj_id,
{ return box_.obj_id; },
{ return box_.obj_id = value; })

Define_Property(int, boundary_box, track_id,
{ return box_.track_id; },
{ return box_.track_id = value; })

Define_Property(int, boundary_box, count,
{ return box_.count; },
{ return box_.count = value; })

Define_Property(float, boundary_box, prob,
{ return box_.prob; },
{ return box_.prob = value; })

Define_Property(std::string, boundary_box, object_name,
{ return name_; },
{ return name_ = value; })

Define_Property(cv::Size, boundary_box, size,
{ return cv::Size(Width, Height); },
{
  Width = value.width;
  Height = value.height;
  return size();
})

Define_Property(cv::Point, boundary_box, lt,
{ return cv::Point(X, Y); },
{
  X = value.x;
  Y = value.y;
  return lt();
})

Define_Property(cv::Point, boundary_box, br,
{ return cv::Point(X + Width, Y + Height); },
{
  return br();
})

Define_Property(cv::Rect, boundary_box, rect,
{ return cv::Rect(X, Y, Width, Height); },
{
  X = value.x;
  Y = value.y;
  Width = value.width;
  Height = value.height;
  return rect();
})

}
}

namespace dnn {
namespace region {

boundary_boxes
make_boundaryboxes(const core::bboxes_t& vec) {
  boundary_boxes dst;
  for (auto& box : vec) {
    dst.push_back(box);
  }
  return dst;
}

bool
is_same_id(const boundary_box &box1,
           const boundary_box &box2) {
  return ((box1.ObjectId == box2.ObjectId)
          && (box1.TrackId == box2.TrackId));
}

}
}