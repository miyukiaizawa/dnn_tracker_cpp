#pragma once
#ifndef __DNN_TRACKER_CPP_OBJECT_PARENT_OBJECT_H__
#define __DNN_TRACKER_CPP_OBJECT_PARENT_OBJECT_H__
#include "dnn_tracker_cpp/object/dependent_object.h"

namespace dnn {
class child_object;
class parent_object : public dependent_object {
public:
  DNNTRR_API parent_object(bool _can_has_children = true);
  DNNTRR_API parent_object(region::track_box box, bool _can_has_children = true);
  DNNTRR_API parent_object(region::inclusive_box box, bool _can_has_children = true);
  DNNTRR_API virtual ~parent_object();

  DNNTRR_API parent_object(parent_object* obj);
  DNNTRR_API parent_object& operator = (parent_object* obj);

  DNNTRR_API region::track_boxes& children();
  DNNTRR_API const region::track_boxes& children() const;

  DNNTRR_API bool should_ignore();
  DNNTRR_API virtual bool remove_unvalid_reference(object_ptrs_t& objects) override;

protected:
  DNNTRR_API virtual bool find_reference(object_ptrs_t& objects,
                                         object_ptr_t& obj) override;
  DNNTRR_API virtual bool can_add_reference(object_ptrs_t& objects) override;
  DNNTRR_API virtual bool overwirte_referene(dependent_object* object) override;
  DNNTRR_API virtual void erase_reference(object_ptr_t& object) override;
  DNNTRR_API virtual region::track_box make_outer() override;
  DNNTRR_API virtual void clear_reference() override;

  DNNTRR_API bool can_has_children();

private:
  bool can_has_children_;
  region::track_boxes children_;
};
using parent_object_ptr = std::shared_ptr<parent_object>;

DNNTRR_API std::tstring make_children_names(const parent_object& parent,
                                            const object_names& object_names,
                                            bool show_details);

DNNTRR_API parent_object_ptr to_parent_object(dependent_object_ptr object);

DNNTRR_API bool is_parent_object(dependent_object_ptr object);

}


#endif //__PARENT_OBJECT_H__
