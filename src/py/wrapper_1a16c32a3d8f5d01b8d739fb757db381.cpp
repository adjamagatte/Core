#include "_core.h"


void wrapper_1a16c32a3d8f5d01b8d739fb757db381()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    void  (*function_pointer_1a16c32a3d8f5d01b8d739fb757db381)(::statiskit::Index const &) = ::statiskit::set_seed;
    boost::python::def("set_seed", function_pointer_1a16c32a3d8f5d01b8d739fb757db381, "");
}