#pragma once
#ifndef  __DNN_TRACKER_CPP_OBJECT_DEPENDENT_OBJECT_PTRS_H__
#define __DNN_TRACKER_CPP_OBJECT_DEPENDENT_OBJECT_PTRS_H__
#include "dnn_tracker_cpp/object/dependent_object.h"
#include "dnn_tracker_cpp/target.h"

namespace dnn {

class dependent_object_ptrs {
public:
  using value_type = std::shared_ptr<dependent_object>;
  using objects_t = std::vector<value_type>;
  using iterator = objects_t::iterator;
  using const_iterator = objects_t::const_iterator;
public:

  DNNTRR_API dependent_object_ptrs();
  DNNTRR_API dependent_object_ptrs(const dependent_object_ptrs& ptrs);

  DNNTRR_API dependent_object_ptrs& operator=(const dependent_object_ptrs& ptrs);

  DNNTRR_API iterator begin();
  DNNTRR_API const_iterator begin() const;

  DNNTRR_API iterator end();
  DNNTRR_API const_iterator end() const;

  DNNTRR_API iterator find(const dependent_object_ptr obj);
  DNNTRR_API const_iterator find(const dependent_object_ptr obj) const;

  DNNTRR_API iterator find(const region::track_box box);
  DNNTRR_API const_iterator find(const region::track_box box) const;

  DNNTRR_API bool find(const dependent_object_ptr obj, iterator& it);
  DNNTRR_API bool find(const dependent_object_ptr obj, const_iterator& it) const;

  DNNTRR_API bool find(const region::track_box box, iterator& it);
  DNNTRR_API bool find(const region::track_box box, const_iterator& it) const;

  DNNTRR_API void push_back(dependent_object_ptr& obj);

  DNNTRR_API iterator erase(iterator &it);

  DNNTRR_API void resize(size_t size);

  DNNTRR_API size_t size() const;

  DNNTRR_API bool empty() const;

private:
  objects_t objects_;
};

using object_ptrs_iterator = typename dependent_object_ptrs::iterator;

}

namespace dnn {

DNNTRR_API bool find_object(dependent_object_ptrs& objects,
                            dependent_object_ptr& object,
                            dependent_object_ptrs::iterator& it);

DNNTRR_API bool find_object(dependent_object_ptrs& objects,
                            region::track_box& object,
                            dependent_object_ptrs::iterator& it);
}

#endif //__DEPENDENT_OBJECT_PTRS_H__
