#include "_core.h"



namespace autowig
{

    void method_decorator_4790ba0ff82f5061b1c8b86eeb1377d8(class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > const & instance, struct ::statiskit::MeanEstimation & param_out)     { instance.operator*() = param_out; }
}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > const volatile * get_pointer<class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > const volatile >(class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_bc958e5aa6905fcda520d2cc19bbc8dd()
{

    std::string name_a5e4e9231d6351ccb0e06756b389f0af = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".std");
    boost::python::object module_a5e4e9231d6351ccb0e06756b389f0af(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_a5e4e9231d6351ccb0e06756b389f0af.c_str()))));
    boost::python::scope().attr("std") = module_a5e4e9231d6351ccb0e06756b389f0af;
    boost::python::scope scope_a5e4e9231d6351ccb0e06756b389f0af = module_a5e4e9231d6351ccb0e06756b389f0af;
    struct unique_ptr_bc958e5aa6905fcda520d2cc19bbc8dd_to_python
    {
        static PyObject* convert(class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > const & unique_ptr_bc958e5aa6905fcda520d2cc19bbc8dd)
        {
            //return boost::python::incref(boost::python::object(const_cast< class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > & >(unique_ptr_bc958e5aa6905fcda520d2cc19bbc8dd).release()).ptr());
            std::shared_ptr< struct ::statiskit::MeanEstimation  > shared_ptr_bc958e5aa6905fcda520d2cc19bbc8dd(std::move(const_cast< class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > > & >(unique_ptr_bc958e5aa6905fcda520d2cc19bbc8dd)));
            return boost::python::incref(boost::python::object(shared_ptr_bc958e5aa6905fcda520d2cc19bbc8dd).ptr());
        }
    };

    boost::python::to_python_converter< class ::std::unique_ptr< struct ::statiskit::MeanEstimation, struct ::std::default_delete< struct ::statiskit::MeanEstimation > >, unique_ptr_bc958e5aa6905fcda520d2cc19bbc8dd_to_python >();
}