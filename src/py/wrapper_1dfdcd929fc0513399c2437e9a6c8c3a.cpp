#include "_core.h"



namespace autowig
{

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator const volatile * get_pointer<class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator const volatile >(class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_1dfdcd929fc0513399c2437e9a6c8c3a()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    std::string name_cc9b200ad98c51108cfb0b6bf6bf2bd0 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + "._negative_binomial_distribution_mm_estimation");
    boost::python::object module_cc9b200ad98c51108cfb0b6bf6bf2bd0(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_cc9b200ad98c51108cfb0b6bf6bf2bd0.c_str()))));
    boost::python::scope().attr("_negative_binomial_distribution_mm_estimation") = module_cc9b200ad98c51108cfb0b6bf6bf2bd0;
    boost::python::scope scope_cc9b200ad98c51108cfb0b6bf6bf2bd0 = module_cc9b200ad98c51108cfb0b6bf6bf2bd0;
    struct ::statiskit::MeanEstimation::Estimator * (::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::*method_pointer_71952e0c290e5bcd8c5b4ade259ab339)() = &::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::get_mean;
    void  (::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::*method_pointer_dabecc56e4a8500faf6ab730b4069475)(struct ::statiskit::MeanEstimation::Estimator const &) = &::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::set_mean;
    struct ::statiskit::VarianceEstimation::Estimator * (::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::*method_pointer_881d8b82b1215dc6b7e6c443fd23b529)() = &::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::get_variance;
    void  (::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::*method_pointer_141dc195ffd8504789f22b8bde9c9d73)(struct ::statiskit::VarianceEstimation::Estimator const &) = &::statiskit::NegativeBinomialDistributionMMEstimation::Estimator::set_variance;
    boost::python::class_< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator, autowig::Held< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator >::Type, boost::python::bases< struct ::statiskit::DiscreteUnivariateDistributionEstimation::Estimator > > class_1dfdcd929fc0513399c2437e9a6c8c3a("Estimator", "This class NegativeBinomialDistribution represents a Maximum Likelihood\nEstimator (MLE) of negative binomial distribution parameters\n:math:`\\kappa` and :math:`\\pi`.\n\nThis MLE prededure is described in :cite:`DBB13.` Note\nthat in their paper, the negative binomial distribution probability\ndistribution function is given by\n\n.. math::\n\n\n   P\\left(X = x\\right) = \\frac{\\Gamma\\left(x+\\kappa\\right)}{x! \\Gamma\\left(\\kappa\\right)} \\left(\\frac{\\mu}{\\mu + \\kappa}\\right)^{x} \\left(\\frac{\\kappa}{\\kappa + \\mu}\\right)^{\\kappa}.\n\n This is a reparametrization of the negative binomial distribution\ndescribed by parameters :math:`\\kappa` and :math:`\\pi` with $$\n\n.. seealso::\n\n    :py:class:`statiskit.core.statiskit.NegativeBinomialDistribution`.\n\n", boost::python::no_init);
    class_1dfdcd929fc0513399c2437e9a6c8c3a.def(boost::python::init<  >(""));
    class_1dfdcd929fc0513399c2437e9a6c8c3a.def(boost::python::init< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator const & >(""));
    class_1dfdcd929fc0513399c2437e9a6c8c3a.def("get_mean", method_pointer_71952e0c290e5bcd8c5b4ade259ab339, boost::python::return_value_policy< boost::python::reference_existing_object >(), "");
    class_1dfdcd929fc0513399c2437e9a6c8c3a.def("set_mean", method_pointer_dabecc56e4a8500faf6ab730b4069475, "");
    class_1dfdcd929fc0513399c2437e9a6c8c3a.def("get_variance", method_pointer_881d8b82b1215dc6b7e6c443fd23b529, boost::python::return_value_policy< boost::python::reference_existing_object >(), "");
    class_1dfdcd929fc0513399c2437e9a6c8c3a.def("set_variance", method_pointer_141dc195ffd8504789f22b8bde9c9d73, "");

    if(autowig::Held< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator >::Type, autowig::Held< struct ::statiskit::DiscreteUnivariateDistributionEstimation::Estimator >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator >::Type, boost::python::objects::make_ptr_instance< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator, boost::python::objects::pointer_holder< autowig::Held< class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator >::Type, class ::statiskit::NegativeBinomialDistributionMMEstimation::Estimator > > >();
    }

}