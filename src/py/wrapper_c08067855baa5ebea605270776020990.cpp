#include "_core.h"



namespace autowig
{

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator const volatile * get_pointer<struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator const volatile >(struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_c08067855baa5ebea605270776020990()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    std::string name_c4726473069d576fbb9e53aacbf298ea = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + "._categorical_univariate_distribution_estimation");
    boost::python::object module_c4726473069d576fbb9e53aacbf298ea(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_c4726473069d576fbb9e53aacbf298ea.c_str()))));
    boost::python::scope().attr("_categorical_univariate_distribution_estimation") = module_c4726473069d576fbb9e53aacbf298ea;
    boost::python::scope scope_c4726473069d576fbb9e53aacbf298ea = module_c4726473069d576fbb9e53aacbf298ea;
    boost::python::class_< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator, autowig::Held< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator >::Type, boost::python::bases< struct ::statiskit::UnivariateDistributionEstimation::Estimator > > class_c08067855baa5ebea605270776020990("Estimator", "", boost::python::no_init);
    class_c08067855baa5ebea605270776020990.def(boost::python::init<  >(""));
    class_c08067855baa5ebea605270776020990.def(boost::python::init< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator const & >(""));

    if(autowig::Held< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator >::Type, autowig::Held< struct ::statiskit::UnivariateDistributionEstimation::Estimator >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator >::Type, boost::python::objects::make_ptr_instance< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator, boost::python::objects::pointer_holder< autowig::Held< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator >::Type, struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator > > >();
    }

}