#include "_core.h"



namespace autowig
{

    void method_decorator_5a1154075a4353e9b9b684d4e0a9f31d(class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > const & instance, struct ::statiskit::MultivariateData::Generator & param_out)     { instance.operator*() = param_out; }
}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > const volatile * get_pointer<class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > const volatile >(class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_6eb3528843c6511f97a06a8eb24dda64()
{

    std::string name_a5e4e9231d6351ccb0e06756b389f0af = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".std");
    boost::python::object module_a5e4e9231d6351ccb0e06756b389f0af(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_a5e4e9231d6351ccb0e06756b389f0af.c_str()))));
    boost::python::scope().attr("std") = module_a5e4e9231d6351ccb0e06756b389f0af;
    boost::python::scope scope_a5e4e9231d6351ccb0e06756b389f0af = module_a5e4e9231d6351ccb0e06756b389f0af;
    struct unique_ptr_6eb3528843c6511f97a06a8eb24dda64_to_python
    {
        static PyObject* convert(class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > const & unique_ptr_6eb3528843c6511f97a06a8eb24dda64)
        {
            //return boost::python::incref(boost::python::object(const_cast< class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > & >(unique_ptr_6eb3528843c6511f97a06a8eb24dda64).release()).ptr());
            std::shared_ptr< struct ::statiskit::MultivariateData::Generator  > shared_ptr_6eb3528843c6511f97a06a8eb24dda64(std::move(const_cast< class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > > & >(unique_ptr_6eb3528843c6511f97a06a8eb24dda64)));
            return boost::python::incref(boost::python::object(shared_ptr_6eb3528843c6511f97a06a8eb24dda64).ptr());
        }
    };

    boost::python::to_python_converter< class ::std::unique_ptr< struct ::statiskit::MultivariateData::Generator, struct ::std::default_delete< struct ::statiskit::MultivariateData::Generator > >, unique_ptr_6eb3528843c6511f97a06a8eb24dda64_to_python >();
}