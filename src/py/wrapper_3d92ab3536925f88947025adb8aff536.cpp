#include "_core.h"



namespace autowig
{
    class Wrap_3d92ab3536925f88947025adb8aff536 : public ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution >, public boost::python::wrapper< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >
    {
        public:
            
            virtual double  get_variance() const
            { return this->get_override("get_variance")(); }
                        
            virtual double  get_mean() const
            { return this->get_override("get_mean")(); }
                        
            virtual double  quantile(double const & param_0) const
            { return this->get_override("quantile")(param_0); }
                        
            virtual double  cdf(double const & param_0) const
            { return this->get_override("cdf")(param_0); }
                        
            virtual double  pdf(double const & param_0) const
            { return this->get_override("pdf")(param_0); }
                        
            virtual double  ldf(double const & param_0) const
            { return this->get_override("ldf")(param_0); }
                        
            virtual class ::std::unique_ptr< struct ::statiskit::UnivariateEvent, struct ::std::default_delete< struct ::statiskit::UnivariateEvent > >  simulate() const
            {
                 ::std::unique_ptr< struct ::statiskit::UnivariateEvent, struct ::std::default_delete< struct ::statiskit::UnivariateEvent > > ::element_type* result = this->get_override("simulate")();
                 return ::std::unique_ptr< struct ::statiskit::UnivariateEvent, struct ::std::default_delete< struct ::statiskit::UnivariateEvent > > (result);
            }
                        
            virtual unsigned int  get_nb_parameters() const
            { return this->get_override("get_nb_parameters")(); }
                        

        protected:
            

        private:
            

    };

}

#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> autowig::Wrap_3d92ab3536925f88947025adb8aff536 const volatile * get_pointer<autowig::Wrap_3d92ab3536925f88947025adb8aff536 const volatile >(autowig::Wrap_3d92ab3536925f88947025adb8aff536 const volatile *c) { return c; }
    template <> struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > const volatile * get_pointer<struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > const volatile >(struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > const volatile *c) { return c; }
}
    #endif
#endif



void wrapper_3d92ab3536925f88947025adb8aff536()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::class_< autowig::Wrap_3d92ab3536925f88947025adb8aff536, autowig::Held< autowig::Wrap_3d92ab3536925f88947025adb8aff536 >::Type, boost::python::bases< struct ::statiskit::ContinuousUnivariateDistribution >, boost::noncopyable > class_3d92ab3536925f88947025adb8aff536("_PolymorphicCopy_3d92ab3536925f88947025adb8aff536", "", boost::python::no_init);

    if(autowig::Held< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< autowig::Wrap_3d92ab3536925f88947025adb8aff536 >::Type, autowig::Held< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >::Type >();
        boost::python::register_ptr_to_python< autowig::Held< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >::Type >();
        boost::python::implicitly_convertible< autowig::Held< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >::Type, autowig::Held< struct ::statiskit::ContinuousUnivariateDistribution >::Type >();
        //boost::python::objects::class_value_wrapper< autowig::Held< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >::Type, boost::python::objects::make_ptr_instance< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution >, boost::python::objects::pointer_holder< autowig::Held< struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > >::Type, struct ::statiskit::PolymorphicCopy< struct ::statiskit::UnivariateDistribution, class ::statiskit::GumbelMinDistribution, struct ::statiskit::ContinuousUnivariateDistribution > > > >();
    }

}