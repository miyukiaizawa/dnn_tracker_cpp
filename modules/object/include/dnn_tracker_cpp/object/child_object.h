#pragma once
#ifndef __DNN_TRACKER_CPP_OBJECT_CHILD_OBJECT_H__
#define __DNN_TRACKER_CPP_OBJECT_CHILD_OBJECT_H__
#include "dnn_tracker_cpp/object/dependent_object.h"

namespace dnn {
class parent_object;
class child_object : public dependent_object {
public:
  DNNTRR_API child_object();
  DNNTRR_API child_object(region::track_box box);
  DNNTRR_API child_object(region::inclusive_box box);
  DNNTRR_API virtual ~child_object();

  DNNTRR_API region::track_box& parent();

  DNNTRR_API virtual bool should_ignore() override;

protected:
  DNNTRR_API virtual bool find_reference(object_ptrs_t& objects,
                              object_ptr_t& obj) override;
  DNNTRR_API virtual bool can_add_reference(object_ptrs_t& objects); // override;
  DNNTRR_API virtual bool overwirte_referene(dependent_object* object); // override;
  DNNTRR_API virtual bool remove_unvalid_reference(object_ptrs_t& objects); // override;
  DNNTRR_API virtual void erase_reference(object_ptr_t& object); // override;
  DNNTRR_API virtual region::track_box make_outer(); // override;
  DNNTRR_API virtual void clear_reference(); // override;

private:
  region::track_box parent_;
};
using child_object_ptr = std::shared_ptr<child_object>;

DNNTRR_API std::tstring make_parent_name(child_object& child, object_names& object_names, bool show_datails);

DNNTRR_API child_object_ptr to_child_object(dependent_object_ptr object);

DNNTRR_API bool is_child_object(dependent_object_ptr object);

}

#endif //__CHILD_OBJECT_H__
