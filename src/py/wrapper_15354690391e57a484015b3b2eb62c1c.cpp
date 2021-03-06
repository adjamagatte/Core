#include "_core.h"



namespace autowig
{

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > const volatile * get_pointer<class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > const volatile >(class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_15354690391e57a484015b3b2eb62c1c()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    struct ::statiskit::MultivariateData const * (::statiskit::ActiveEstimation< ::statiskit::IndependentMultivariateDistribution< ::statiskit::ContinuousMultivariateDistribution >, ::statiskit::ContinuousMultivariateDistributionEstimation >::*method_pointer_b9dee0407a9a578f8c8e70b341d0c377)() const = &::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation >::get_data;
    boost::python::class_< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation >, autowig::Held< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > >::Type, boost::python::bases< class ::statiskit::LazyEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > > > class_15354690391e57a484015b3b2eb62c1c("_ActiveEstimation_15354690391e57a484015b3b2eb62c1c", "", boost::python::no_init);
    class_15354690391e57a484015b3b2eb62c1c.def(boost::python::init<  >(""));
    class_15354690391e57a484015b3b2eb62c1c.def(boost::python::init< struct ::statiskit::MultivariateData const * >(""));
    class_15354690391e57a484015b3b2eb62c1c.def(boost::python::init< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution > const *, struct ::statiskit::MultivariateData const * >(""));
    class_15354690391e57a484015b3b2eb62c1c.def(boost::python::init< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > const & >(""));
    class_15354690391e57a484015b3b2eb62c1c.def("get_data", method_pointer_b9dee0407a9a578f8c8e70b341d0c377, boost::python::return_value_policy< boost::python::reference_existing_object >(), "");

    if(autowig::Held< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > >::Type, autowig::Held< class ::statiskit::LazyEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > >::Type, boost::python::objects::make_ptr_instance< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation >, boost::python::objects::pointer_holder< autowig::Held< class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > >::Type, class ::statiskit::ActiveEstimation< class ::statiskit::IndependentMultivariateDistribution< struct ::statiskit::ContinuousMultivariateDistribution >, struct ::statiskit::ContinuousMultivariateDistributionEstimation > > > >();
    }

}