#include "_core.h"



namespace autowig
{

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::statiskit::NaturalVarianceEstimation::Estimator const volatile * get_pointer<class ::statiskit::NaturalVarianceEstimation::Estimator const volatile >(class ::statiskit::NaturalVarianceEstimation::Estimator const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_7d5fb1216d2b55f899fc284e8d9774c2()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    std::string name_52a96e7b6d23543982ff67d6b77fe98e = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + "._natural_variance_estimation");
    boost::python::object module_52a96e7b6d23543982ff67d6b77fe98e(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_52a96e7b6d23543982ff67d6b77fe98e.c_str()))));
    boost::python::scope().attr("_natural_variance_estimation") = module_52a96e7b6d23543982ff67d6b77fe98e;
    boost::python::scope scope_52a96e7b6d23543982ff67d6b77fe98e = module_52a96e7b6d23543982ff67d6b77fe98e;
    bool const & (::statiskit::NaturalVarianceEstimation::Estimator::*method_pointer_358b4c58950f56bfb8bfc2507f654d05)() const = &::statiskit::NaturalVarianceEstimation::Estimator::get_bias;
    void  (::statiskit::NaturalVarianceEstimation::Estimator::*method_pointer_c65d3ec547be5b3691943eb26d83ae67)(bool const &) = &::statiskit::NaturalVarianceEstimation::Estimator::set_bias;
    boost::python::class_< class ::statiskit::NaturalVarianceEstimation::Estimator, autowig::Held< class ::statiskit::NaturalVarianceEstimation::Estimator >::Type, boost::python::bases< struct ::statiskit::VarianceEstimation::Estimator > > class_7d5fb1216d2b55f899fc284e8d9774c2("Estimator", "", boost::python::no_init);
    class_7d5fb1216d2b55f899fc284e8d9774c2.def(boost::python::init<  >(""));
    class_7d5fb1216d2b55f899fc284e8d9774c2.def(boost::python::init< bool const & >(""));
    class_7d5fb1216d2b55f899fc284e8d9774c2.def(boost::python::init< class ::statiskit::NaturalVarianceEstimation::Estimator const & >(""));
    class_7d5fb1216d2b55f899fc284e8d9774c2.def("get_bias", method_pointer_358b4c58950f56bfb8bfc2507f654d05, boost::python::return_value_policy< boost::python::return_by_value >(), "");
    class_7d5fb1216d2b55f899fc284e8d9774c2.def("set_bias", method_pointer_c65d3ec547be5b3691943eb26d83ae67, "");

    if(autowig::Held< class ::statiskit::NaturalVarianceEstimation::Estimator >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< class ::statiskit::NaturalVarianceEstimation::Estimator >::Type, autowig::Held< struct ::statiskit::VarianceEstimation::Estimator >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< class ::statiskit::NaturalVarianceEstimation::Estimator >::Type, boost::python::objects::make_ptr_instance< class ::statiskit::NaturalVarianceEstimation::Estimator, boost::python::objects::pointer_holder< autowig::Held< class ::statiskit::NaturalVarianceEstimation::Estimator >::Type, class ::statiskit::NaturalVarianceEstimation::Estimator > > >();
    }

}