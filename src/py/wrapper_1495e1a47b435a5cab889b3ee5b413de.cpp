#include "_core.h"



namespace autowig
{

    void method_decorator_707948007ea950d7bc0027557e87f0ad(class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > const & instance, struct ::statiskit::UnivariateData::Generator & param_out)     { instance.operator*() = param_out; }
}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > const volatile * get_pointer<class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > const volatile >(class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_1495e1a47b435a5cab889b3ee5b413de()
{

    std::string name_a5e4e9231d6351ccb0e06756b389f0af = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".std");
    boost::python::object module_a5e4e9231d6351ccb0e06756b389f0af(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_a5e4e9231d6351ccb0e06756b389f0af.c_str()))));
    boost::python::scope().attr("std") = module_a5e4e9231d6351ccb0e06756b389f0af;
    boost::python::scope scope_a5e4e9231d6351ccb0e06756b389f0af = module_a5e4e9231d6351ccb0e06756b389f0af;
    struct unique_ptr_1495e1a47b435a5cab889b3ee5b413de_to_python
    {
        static PyObject* convert(class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > const & unique_ptr_1495e1a47b435a5cab889b3ee5b413de)
        {
            //return boost::python::incref(boost::python::object(const_cast< class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > & >(unique_ptr_1495e1a47b435a5cab889b3ee5b413de).release()).ptr());
            std::shared_ptr< struct ::statiskit::UnivariateData::Generator  > shared_ptr_1495e1a47b435a5cab889b3ee5b413de(std::move(const_cast< class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > > & >(unique_ptr_1495e1a47b435a5cab889b3ee5b413de)));
            return boost::python::incref(boost::python::object(shared_ptr_1495e1a47b435a5cab889b3ee5b413de).ptr());
        }
    };

    boost::python::to_python_converter< class ::std::unique_ptr< struct ::statiskit::UnivariateData::Generator, struct ::std::default_delete< struct ::statiskit::UnivariateData::Generator > >, unique_ptr_1495e1a47b435a5cab889b3ee5b413de_to_python >();
}