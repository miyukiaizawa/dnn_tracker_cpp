#include "dnn_tracker_cpp/region/inclusive_box.h"

namespace dnn {
namespace region {

inclusive_box::
inclusive_box() :
  inner_(),
  outer_() {
  set_properties();
}

inclusive_box::
inclusive_box(track_box& _inner) :
  inner_(_inner),
  outer_(_inner) {
  set_properties();
}

inclusive_box::
inclusive_box(track_box& _inner,
              track_box& _outer) :
  inner_(_inner),
  outer_(_outer) {
  set_properties();
}

track_box&
inclusive_box::
inner() { return inner_; }

track_box&
inclusive_box::
outer() { return outer_; }

void
inclusive_box::
set_as_outer(track_box& box) { outer_ = box; }

void
inclusive_box::
reset_outer() { outer_ = inner_; }

Define_Property(track_box, inclusive_box, _outer,
{ return outer_; },
{ return outer_ = value; })

Define_Property(track_box, inclusive_box, _inner,
{ return inner_; },
{ return inner_ = value; })

void
inclusive_box::
set_properties() {
  Outer(this);
  Inner(this);
}

}
}
