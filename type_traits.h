/*
*   Created by Loora1N by 2023/9/26
*/

#ifndef LOOSTL_TYPE_TRAITS_H
#define LOOSTL_TYPE_TRAITS_H

struct __true_type {
};

struct __false_type {
};

template<class _Tp>
struct __type_traits {
    typedef __true_type this_dummy_member_must_be_first;
    typedef __false_type has_trivial_default_constructor;
    typedef __false_type has_trivial_copy_constructor;
    typedef __false_type has_trivial_assignment_operator;
    typedef __false_type has_trivial_destructor;
    typedef __false_type is_POD_type;
};

// #ifndef __STL_NO_BOOL
template<>
struct __type_traits<bool> {
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivial_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
};



#endif /* LOOSTL_TYPE_TRAITS_H */