#include "_core.h"



namespace autowig
{

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> struct ::statiskit::PoissonDistributionMLEstimation const volatile * get_pointer<struct ::statiskit::PoissonDistributionMLEstimation const volatile >(struct ::statiskit::PoissonDistributionMLEstimation const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_36823ab42b0c57b48d903606aa743329()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::class_< struct ::statiskit::PoissonDistributionMLEstimation, autowig::Held< struct ::statiskit::PoissonDistributionMLEstimation >::Type, boost::python::bases< class ::statiskit::ActiveEstimation< class ::statiskit::PoissonDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation > > > class_36823ab42b0c57b48d903606aa743329("PoissonDistributionMLEstimation", "", boost::python::no_init);
    class_36823ab42b0c57b48d903606aa743329.def(boost::python::init<  >(""));
    class_36823ab42b0c57b48d903606aa743329.def(boost::python::init< class ::statiskit::PoissonDistribution const *, struct ::statiskit::UnivariateData const * >(""));
    class_36823ab42b0c57b48d903606aa743329.def(boost::python::init< struct ::statiskit::PoissonDistributionMLEstimation const & >(""));

    if(autowig::Held< struct ::statiskit::PoissonDistributionMLEstimation >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< struct ::statiskit::PoissonDistributionMLEstimation >::Type, autowig::Held< class ::statiskit::ActiveEstimation< class ::statiskit::PoissonDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation > >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< struct ::statiskit::PoissonDistributionMLEstimation >::Type, boost::python::objects::make_ptr_instance< struct ::statiskit::PoissonDistributionMLEstimation, boost::python::objects::pointer_holder< autowig::Held< struct ::statiskit::PoissonDistributionMLEstimation >::Type, struct ::statiskit::PoissonDistributionMLEstimation > > >();
    }

}