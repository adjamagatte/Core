#include "_core.h"



namespace autowig
{
    class Wrap_223fb8b8797b558497d5dea978484cfc : public ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator, public boost::python::wrapper< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >
    {
        public:
            
            virtual class ::std::unique_ptr< struct ::statiskit::UnivariateDistributionEstimation::Estimator, struct ::std::default_delete< struct ::statiskit::UnivariateDistributionEstimation::Estimator > >  copy() const
            {
                 ::std::unique_ptr< struct ::statiskit::UnivariateDistributionEstimation::Estimator, struct ::std::default_delete< struct ::statiskit::UnivariateDistributionEstimation::Estimator > > ::element_type* result = this->get_override("copy")();
                 return ::std::unique_ptr< struct ::statiskit::UnivariateDistributionEstimation::Estimator, struct ::std::default_delete< struct ::statiskit::UnivariateDistributionEstimation::Estimator > > (result);
            }
                        
            virtual class ::std::unique_ptr< struct ::statiskit::UnivariateDistributionEstimation, struct ::std::default_delete< struct ::statiskit::UnivariateDistributionEstimation > >  operator()(::statiskit::UnivariateDistributionEstimation::data_type const & param_0, bool const & param_1) const
            {
                 ::std::unique_ptr< struct ::statiskit::UnivariateDistributionEstimation, struct ::std::default_delete< struct ::statiskit::UnivariateDistributionEstimation > > ::element_type* result = this->get_override("operator()")(param_0, param_1);
                 return ::std::unique_ptr< struct ::statiskit::UnivariateDistributionEstimation, struct ::std::default_delete< struct ::statiskit::UnivariateDistributionEstimation > > (result);
            }
                        

        protected:
            

        private:
            

    };

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> autowig::Wrap_223fb8b8797b558497d5dea978484cfc const volatile * get_pointer<autowig::Wrap_223fb8b8797b558497d5dea978484cfc const volatile >(autowig::Wrap_223fb8b8797b558497d5dea978484cfc const volatile *c) { return c; }
    template <> struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator const volatile * get_pointer<struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator const volatile >(struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_223fb8b8797b558497d5dea978484cfc()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    std::string name_ee3148dbf8425c8f8a5c5a280fb4586c = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".__optimization_estimation_ee3148dbf8425c8f8a5c5a280fb4586c");
    boost::python::object module_ee3148dbf8425c8f8a5c5a280fb4586c(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_ee3148dbf8425c8f8a5c5a280fb4586c.c_str()))));
    boost::python::scope().attr("__optimization_estimation_ee3148dbf8425c8f8a5c5a280fb4586c") = module_ee3148dbf8425c8f8a5c5a280fb4586c;
    boost::python::scope scope_ee3148dbf8425c8f8a5c5a280fb4586c = module_ee3148dbf8425c8f8a5c5a280fb4586c;
    boost::python::class_< autowig::Wrap_223fb8b8797b558497d5dea978484cfc, autowig::Held< autowig::Wrap_223fb8b8797b558497d5dea978484cfc >::Type, boost::python::bases< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >, boost::noncopyable > class_223fb8b8797b558497d5dea978484cfc("Estimator", "", boost::python::no_init);

    if(autowig::Held< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< autowig::Wrap_223fb8b8797b558497d5dea978484cfc >::Type, autowig::Held< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::Type >();
        boost::python::register_ptr_to_python< autowig::Held< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::Type >();
        boost::python::implicitly_convertible< autowig::Held< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::Type, autowig::Held< class ::statiskit::OptimizationEstimationImpl< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::Type, boost::python::objects::make_ptr_instance< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator, boost::python::objects::pointer_holder< autowig::Held< struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator >::Type, struct ::statiskit::OptimizationEstimation< struct ::statiskit::DiscreteUnivariateMixtureDistribution *, struct ::statiskit::DiscreteUnivariateMixtureDistribution, struct ::statiskit::DiscreteUnivariateDistributionEstimation >::Estimator > > >();
    }

}