#include "_core.h"



namespace autowig
{

    void method_decorator_0aaf48f87d855f588f43fb5a78d0595e(class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > const & instance, struct ::statiskit::MeanVectorEstimation & param_out)     { instance.operator*() = param_out; }
}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > const volatile * get_pointer<class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > const volatile >(class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_12b1fae574cb5e328c0214875274f281()
{

    std::string name_a5e4e9231d6351ccb0e06756b389f0af = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".std");
    boost::python::object module_a5e4e9231d6351ccb0e06756b389f0af(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_a5e4e9231d6351ccb0e06756b389f0af.c_str()))));
    boost::python::scope().attr("std") = module_a5e4e9231d6351ccb0e06756b389f0af;
    boost::python::scope scope_a5e4e9231d6351ccb0e06756b389f0af = module_a5e4e9231d6351ccb0e06756b389f0af;
    struct unique_ptr_12b1fae574cb5e328c0214875274f281_to_python
    {
        static PyObject* convert(class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > const & unique_ptr_12b1fae574cb5e328c0214875274f281)
        {
            //return boost::python::incref(boost::python::object(const_cast< class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > & >(unique_ptr_12b1fae574cb5e328c0214875274f281).release()).ptr());
            std::shared_ptr< struct ::statiskit::MeanVectorEstimation  > shared_ptr_12b1fae574cb5e328c0214875274f281(std::move(const_cast< class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > > & >(unique_ptr_12b1fae574cb5e328c0214875274f281)));
            return boost::python::incref(boost::python::object(shared_ptr_12b1fae574cb5e328c0214875274f281).ptr());
        }
    };

    boost::python::to_python_converter< class ::std::unique_ptr< struct ::statiskit::MeanVectorEstimation, struct ::std::default_delete< struct ::statiskit::MeanVectorEstimation > >, unique_ptr_12b1fae574cb5e328c0214875274f281_to_python >();
}