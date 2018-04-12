#include "dnn_tracker_cpp/region/track_box.h"
#include "dnn_tracker_cpp/core/utils.h"

namespace dnn {
namespace region {

track_box::
track_box() :
  first_pos(),
  current_pos(),
  distance(first_pos.center(), current_pos.center(), true),
  direction(first_pos.center(), current_pos.center()) {
  set_properties();
}

track_box::
track_box(const boundary_box& _first_pos,
          region::collision _collision) :
  first_pos(_first_pos),
  current_pos(_first_pos),
  collision(_collision),
  distance(first_pos.center(), current_pos.center(), true),
  direction(first_pos.center(), current_pos.center()) {
  set_properties();
}

track_box::
track_box(const boundary_box& _first_pos,
          const boundary_box& _current_pos,
          region::collision _collision) :
  first_pos(_first_pos),
  current_pos(_current_pos),
  collision(_collision),
  distance(first_pos.center(), current_pos.center(), true),
  direction(first_pos.center(), current_pos.center()) {
  set_properties();
}

track_box::
track_box(const track_box& box) :
  first_pos(box.first_pos),
  current_pos(box.current_pos),
  collision(box.collision),
  distance(first_pos.center(), current_pos.center(), true),
  direction(first_pos.center(), current_pos.center()) {
  set_properties();
}

void
track_box::
set_properties() {
  FirstPos(this);
  CurrentPos(this);
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
track_box::
operator()() const {
  return (boundary_box&)current_pos;
}

bool
track_box::
operator==(const track_box& box) const {
  return first_pos == box.first_pos;
  //&& current_pos == box.current_pos;
}

bool
track_box::
operator!=(const track_box& box) const {
  return first_pos != box.first_pos;
  //&& current_pos == box.current_pos;
}

track_box&
track_box::
operator=(const track_box& box) {
  first_pos = box.first_pos;
  current_pos = box.current_pos;
  collision = box.collision;
  distance = box.distance;
  direction = box.direction;
  return (*this);
}

track_box&
track_box::
operator <<(boundary_box& _current_box) {
  update(_current_box);
  return (*this);
}

bool
track_box::
empty() const {
  return first_pos.empty() && current_pos.empty();
}

bool
track_box::
is_same_id(const track_box& box) const {
  return current_pos.is_same_id(box.current_pos);
}

void
track_box::
merge(track_box& box) {
  boundary_box merged;
  merged.X = std::min(this->X, box.X);
  merged.Y = std::min(this->Y, box.Y);
  merged.Width = std::min(this->Width, box.Width);
  merged.Height = std::min(this->Height, box.Height);
  merged.ObjectId = this->ObjectId;
  merged.TrackId = this->TrackId;
  update(merged);
}

void
track_box::
update(const boundary_box& _current_box) {
  if (first_pos.empty()) {
    first_pos = _current_box;
  }
  current_pos = _current_box;
  distance = region::distance(first_pos.center(), current_pos.center(), true);
  direction = region::direction(first_pos.center(), current_pos.center());
}

bool
track_box::
detect_collision(track_box& box) {
  return collision.detect(current_pos.Rect, box.current_pos.Rect);
}

void
track_box::
clear() {
  first_pos.clear();
  current_pos.clear();
  collision = region::collision();
  distance = region::distance();
  direction = region::direction();
}

bool
track_box::
is_cross(track_box &box) {
  return utils::is_cross(LT, BR, box.LT, box.BR);
}

bool
track_box::
contain(track_box &box) {
  return utils::contain(Rect, box.Rect);
}

Define_Property(boundary_box, track_box, _first_pos,
{ return first_pos; },
{ return first_pos = value; })

Define_Property(boundary_box, track_box, _current_pos,
{ return current_pos; },
{ return current_pos = value; })

Define_Property(int, track_box, x,
{ return current_pos.X; },
{ current_pos.X = value;
  return value;
})

Define_Property(int, track_box, y,
{ return current_pos.Y; },
{ return current_pos.Y = value; })

Define_Property(int, track_box, width,
{ return current_pos.Width; },
{ return current_pos.Width = value; })

Define_Property(int, track_box, height,
{ return current_pos.Height; },
{ return current_pos.Height = value; })

Define_Property(int, track_box, obj_id,
{ return current_pos.ObjectId; },
{ return current_pos.ObjectId = value; })

Define_Property(int, track_box, track_id,
{ return current_pos.TrackId; },
{ return current_pos.TrackId = value; })

Define_Property(int, track_box, count,
{ return current_pos.Count; },
{ return current_pos.Count = value; })

Define_Property(float, track_box, prob,
{ return current_pos.Prob; },
{ return current_pos.Prob = value; })

Define_Property(std::string, track_box, object_name,
{ return current_pos.ObjectName; },
{ return current_pos.ObjectName = value; })

Define_Property(cv::Size, track_box, size,
{ return current_pos.Size; },
{
  Width = value.width;
  Height = value.height;
  return size();
})

Define_Property(cv::Point, track_box, lt,
{ return current_pos.LT; },
{
  X = value.x;
  Y = value.y;
  return lt();
})

Define_Property(cv::Point, track_box, br,
{ return current_pos.BR; },
{
  return br();
})

Define_Property(cv::Rect, track_box, rect,
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

bool
is_same_id(const track_box &box1,
           const track_box &box2) {
  return ((box1.ObjectId == box2.ObjectId)
          && (box1.TrackId == box2.TrackId));
}
}
}