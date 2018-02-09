#pragma once
#ifndef __DNN_TRACKER_CPP_RW_PROPERTY_H__
#define __DNN_TRACKER_CPP_RW_PROPERTY_H__

namespace dnn {

template<class T, class Object,
  typename T(Object::*real_getter)() const,
  typename T(Object::*real_setter)(T const&)>
  class RWProperty {
  Object* my_object;
  public:
    void operator()(Object* obj) { my_object = obj; }

    T get() const { return (my_object->*real_getter)(); }
    T set(T const& value) { return (my_object->*real_setter)(value); }

    T operator()() const { return get(); }
    T operator()(T const& value) { return set(value); }

    operator T() const { return get(); }
    T operator=(T const& value) { return set(value); }

    typedef T value_type;
};

#ifndef Declear_Property
#define Declear_Property(type, class_name, getter, setter, name) \
private:\
DNNTRR_API type getter() const; \
DNNTRR_API type setter(type const& value); \
public:\
RWProperty<type, class_name, &class_name::getter, &class_name::setter> name
#endif //Declear_Property

#ifndef Declear_Properties
#define Declear_Properties(type, class_name, getter_setter, name) \
Declear_Property(type, class_name, getter_setter, getter_setter, name)
#endif //Declear_Properties

#ifndef Define_Setter
#define Define_Setter(type, class_name, setter) \
type class_name::setter(type const& value)
#endif //Define_Setter

#ifndef Define_Getter
#define Define_Getter(type, class_name, getter) \
type class_name::getter() const
#endif

#ifndef Define_Property
#define Define_Property(type, class_name, getter_setter, getter_content, setter_content)\
Define_Getter(type, class_name, getter_setter) getter_content \
Define_Setter(type, class_name, getter_setter) setter_content
#endif //Define_Property

}


#endif //__RW_PROPERTY_H__
