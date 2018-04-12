#pragma once
#ifndef __DNN_TRACKER_CPP_REGION_TRACK_BOXES_H__
#define __DNN_TRACKER_CPP_REGION_TRACK_BOXES_H__
#include "dnn_tracker_cpp/region/track_box.h"
#include <vector>

namespace dnn {
namespace region {

class track_boxes {
public:
  using boxes_t = std::vector<track_box>;
  using iterator = boxes_t::iterator;
  using const_iterator = boxes_t::const_iterator;
public:
  DNNTRR_API track_boxes();

  DNNTRR_API boxes_t& operator()();
  DNNTRR_API track_box& operator[](int index);

  DNNTRR_API void push_back(track_box& box);
  DNNTRR_API void clear();
  DNNTRR_API void resize(size_t size);
  DNNTRR_API bool empty();

  DNNTRR_API iterator begin();
  DNNTRR_API const_iterator begin() const;
  DNNTRR_API iterator end();
  DNNTRR_API const_iterator end() const;

  DNNTRR_API iterator erase(iterator it);

  DNNTRR_API iterator find(const region::track_box& object);
  DNNTRR_API const_iterator find(const region::track_box& object) const;

  DNNTRR_API bool find(const region::track_box& object,
                       iterator& it = iterator());
  DNNTRR_API bool find(const region::track_box& object,
                       const_iterator& it = const_iterator()) const;

private:
  boxes_t boxes_;
};

}
}

#endif //__DNN_TRACKER_CPP_REGION_TRACK_BOXES_H__
