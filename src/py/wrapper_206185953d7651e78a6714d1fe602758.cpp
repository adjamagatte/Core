#include "_core.h"


#if defined(_MSC_VER)
    #if (_MSC_VER == 1900)
namespace boost
{
    template <> autowig::Wrap_206185953d7651e78a6714d1fe602758 const volatile * get_pointer<autowig::Wrap_206185953d7651e78a6714d1fe602758 const volatile >(autowig::Wrap_206185953d7651e78a6714d1fe602758 const volatile *c) { return c; }
}
    #endif
#endif

namespace autowig
{
    class Wrap_206185953d7651e78a6714d1fe602758 : public ::statiskit::ContinuousUnivariateConditionalDistribution, public boost::python::wrapper< struct ::statiskit::ContinuousUnivariateConditionalDistribution >
    {
        public:
            
            virtual class ::std::unique_ptr< struct ::statiskit::UnivariateConditionalDistribution, struct ::std::default_delete< struct ::statiskit::UnivariateConditionalDistribution > >  copy() const
            {
                 ::std::unique_ptr< struct ::statiskit::UnivariateConditionalDistribution, struct ::std::default_delete< struct ::statiskit::UnivariateConditionalDistribution > > ::element_type* result = this->get_override("copy")();
                 return ::std::unique_ptr< struct ::statiskit::UnivariateConditionalDistribution, struct ::std::default_delete< struct ::statiskit::UnivariateConditionalDistribution > > (result);
            }
            virtual unsigned int  get_nb_parameters() const
            { return this->get_override("get_nb_parameters")(); }
            virtual struct ::statiskit::MultivariateSampleSpace const * get_explanatory_space() const
            { return this->get_override("get_explanatory_space")(); }
            virtual class ::std::unique_ptr< struct ::statiskit::UnivariateSampleSpace, struct ::std::default_delete< struct ::statiskit::UnivariateSampleSpace > >  get_response_space() const
            {
                 ::std::unique_ptr< struct ::statiskit::UnivariateSampleSpace, struct ::std::default_delete< struct ::statiskit::UnivariateSampleSpace > > ::element_type* result = this->get_override("get_response_space")();
                 return ::std::unique_ptr< struct ::statiskit::UnivariateSampleSpace, struct ::std::default_delete< struct ::statiskit::UnivariateSampleSpace > > (result);
            }
            virtual struct ::statiskit::UnivariateDistribution const * operator()(struct ::statiskit::MultivariateEvent const & param_0) 
            { return this->get_override("operator()")(param_0); }

        protected:
            

        private:
            

    };

}


void wrapper_206185953d7651e78a6714d1fe602758()
{

    std::string name_fa414b05d29e5f4ea0b6d6cb5cf81b01 = boost::python::extract< std::string >(boost::python::scope().attr("__name__") + ".statiskit");
    boost::python::object module_fa414b05d29e5f4ea0b6d6cb5cf81b01(boost::python::handle<  >(boost::python::borrowed(PyImport_AddModule(name_fa414b05d29e5f4ea0b6d6cb5cf81b01.c_str()))));
    boost::python::scope().attr("statiskit") = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::scope scope_fa414b05d29e5f4ea0b6d6cb5cf81b01 = module_fa414b05d29e5f4ea0b6d6cb5cf81b01;
    boost::python::class_< autowig::Wrap_206185953d7651e78a6714d1fe602758, autowig::Held< autowig::Wrap_206185953d7651e78a6714d1fe602758 >::Type, boost::python::bases< struct ::statiskit::UnivariateConditionalDistribution >, boost::noncopyable > class_206185953d7651e78a6714d1fe602758("ContinuousUnivariateConditionalDistribution", "", boost::python::no_init);

    if(autowig::Held< struct ::statiskit::ContinuousUnivariateConditionalDistribution >::is_class)
    {
        boost::python::implicitly_convertible< autowig::Held< struct ::statiskit::ContinuousUnivariateConditionalDistribution >::Type, autowig::Held< struct ::statiskit::UnivariateConditionalDistribution >::Type >();
        boost::python::objects::class_value_wrapper< autowig::Held< struct ::statiskit::ContinuousUnivariateConditionalDistribution >::Type, boost::python::objects::make_ptr_instance< struct ::statiskit::ContinuousUnivariateConditionalDistribution, boost::python::objects::pointer_holder< autowig::Held< struct ::statiskit::ContinuousUnivariateConditionalDistribution >::Type, struct ::statiskit::ContinuousUnivariateConditionalDistribution > > >();
        //boost::python::implicitly_convertible< autowig::Held< autowig::Wrap_206185953d7651e78a6714d1fe602758 >::Type, autowig::Held< struct ::statiskit::ContinuousUnivariateConditionalDistribution >::Type >();
    }

}