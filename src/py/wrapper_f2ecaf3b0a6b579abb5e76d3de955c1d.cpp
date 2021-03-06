#include "_core.h"



namespace autowig
{

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator const volatile * get_pointer<class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator const volatile >(class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_f2ecaf3b0a6b579abb5e76d3de955c1d()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    std::string name_748e3ec2e85552f2ab39e490d409b414 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".__optimization_estimation_impl_748e3ec2e85552f2ab39e490d409b414");
    boost::python::object module_748e3ec2e85552f2ab39e490d409b414(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_748e3ec2e85552f2ab39e490d409b414.c_str()))));
    boost::python::scope().attr("__optimization_estimation_impl_748e3ec2e85552f2ab39e490d409b414") = module_748e3ec2e85552f2ab39e490d409b414;
    boost::python::scope scope_748e3ec2e85552f2ab39e490d409b414 = module_748e3ec2e85552f2ab39e490d409b414;
    boost::python::class_< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator, autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator >::Type, boost::python::bases< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator, class ::statiskit::Optimization > > class_f2ecaf3b0a6b579abb5e76d3de955c1d("Estimator", "", boost::python::no_init);
    class_f2ecaf3b0a6b579abb5e76d3de955c1d.def(boost::python::init<  >(""));
    class_f2ecaf3b0a6b579abb5e76d3de955c1d.def(boost::python::init< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator const & >(""));

    if(autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator >::Type, autowig::Held< struct ::statiskit::CategoricalUnivariateDistributionEstimation::Estimator >::Type >();
        boost::python::implicitly_convertible< autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator >::Type, autowig::Held< class ::statiskit::Optimization >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator >::Type, boost::python::objects::make_ptr_instance< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator, boost::python::objects::pointer_holder< autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator >::Type, class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::CategoricalUnivariateMixtureDistribution *, struct ::statiskit::CategoricalUnivariateMixtureDistribution, struct ::statiskit::CategoricalUnivariateDistributionEstimation >::Estimator > > >();
    }

}