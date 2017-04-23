
#ifndef STATISKIT_CORE_ESTIMATION_H
#define STATISKIT_CORE_ESTIMATION_H

#include "base.h"
#include "sample_space.h"
#include "data.h"
#include "distribution.h"

namespace statiskit
{
    struct STATISKIT_CORE_API sample_space_error : parameter_error
    { sample_space_error(const outcome_type& expected); };

    struct STATISKIT_CORE_API sample_size_error : parameter_error
    { sample_size_error(const unsigned int& minsize); };

    struct STATISKIT_CORE_API overdispersion_error : parameter_error
    { overdispersion_error(); };

    struct STATISKIT_CORE_API underdispersion_error : parameter_error
    { underdispersion_error(); };

    struct STATISKIT_CORE_API UnivariateDistributionEstimation
    {
        typedef UnivariateData data_type;
        typedef UnivariateDistribution estimated_type;

        virtual ~UnivariateDistributionEstimation() = 0;

        virtual estimated_type const * get_estimated() const = 0;
        
        struct STATISKIT_CORE_API Estimator
        { 
            typedef UnivariateDistributionEstimation estimation_type;

            virtual ~Estimator() = 0;

            virtual std::unique_ptr< estimation_type > operator() (const MultivariateData& data, const Index& index) const;
            virtual std::unique_ptr< estimation_type > operator() (const data_type& data, const bool& lazy=true) const = 0;

            virtual std::unique_ptr< Estimator > copy() const = 0;
        };
    };

    template<class D, class B>
    class LazyEstimation : public B
    {
        public:
            LazyEstimation();
            LazyEstimation(D const * estimated);
            LazyEstimation(const LazyEstimation< D, B >& estimation);
            virtual ~LazyEstimation();

            virtual typename B::estimated_type const * get_estimated() const;

        protected:
            D const * _estimated;
    };

    template<class D, class B> class ActiveEstimation : public LazyEstimation< D, B >
    {
        public:
            ActiveEstimation();
            ActiveEstimation(typename B::data_type const * data);
            ActiveEstimation(D const * estimated, typename B::data_type const * data);
            ActiveEstimation(const ActiveEstimation< D, B >& estimation);
            virtual ~ActiveEstimation();

            typename B::data_type const * get_data() const;

        protected:
            typename B::data_type const * _data;
    };

    template<class D, class B> class ListSelection : public ActiveEstimation< D, B >
    {
        public:
            ListSelection();
            ListSelection(typename B::data_type const * data);
            ListSelection(D const * estimated, typename B::data_type const * data);
            ListSelection(const ListSelection< D, B >& estimation);
            virtual ~ListSelection();

            Index size() const;

            B const * get_estimation(const Index& index) const;

            const double& get_score(const Index& index) const;

            class Estimator : public B::Estimator
            {
                public:
                    Estimator();
                    Estimator(const Estimator& estimator);
                    virtual ~Estimator();
                  
                    virtual std::unique_ptr< typename B::Estimator::estimation_type > operator() (typename B::data_type const & data, const bool& lazy=true) const;

                    Index size() const;

                    typename B::Estimator * get_estimator(const Index& index);
                    void set_estimator(const Index& index, const typename B::Estimator& estimator);

                    void add_estimator(const typename B::Estimator& estimator);
                    void remove_estimator(const Index& index);

                protected:
                    std::vector< typename B::Estimator * > _estimators;

                    virtual double scoring(const typename B::estimated_type * estimated, typename B::data_type const & data) const = 0;
            };

            class CriterionEstimator : public Estimator
            {
                public:
                    enum criterion_type {
                        AIC,
                        AICc,
                        BIC,
                        HQIC
                    };

                    CriterionEstimator();
                    CriterionEstimator(const CriterionEstimator& estimator);
                    virtual ~CriterionEstimator();

                    const criterion_type& get_criterion() const;
                    void set_criterion(const criterion_type& criterion);

                protected:
                    criterion_type _criterion;

                    virtual double scoring(const typename B::estimated_type * estimated, typename B::data_type const & data) const;
            };

        protected:
            std::vector< B * > _estimations;
            std::vector< double > _scores;

            void finalize();
    };

    template<class T, class D, class B> class OptimizationEstimationImpl : public ActiveEstimation< D, B >
    {
        public:
            OptimizationEstimationImpl();
            OptimizationEstimationImpl(D const * estimated, typename B::data_type const * data);            
            OptimizationEstimationImpl(const OptimizationEstimationImpl< T, D, B >& estimation);
            virtual ~OptimizationEstimationImpl();

            Index size() const;

            class Estimator : public B::Estimator
            {
                public:
                    Estimator();
                    Estimator(const Estimator& estimator);
                    virtual ~Estimator();

                    const double& get_mindiff() const;
                    void set_mindiff(const double& mindiff);
                    
                    unsigned int get_minits() const;
                    void set_minits(const unsigned int& maxits);

                    unsigned int get_maxits() const;
                    void set_maxits(const unsigned int& maxits);

                protected:
                    double _mindiff;
                    unsigned int _minits;
                    unsigned int _maxits;

                    template<class S> bool run(const unsigned int& its, const S& prev, const S& curr) const;
            };

        protected:
            std::vector< T > _iterations;
    };

    template<class T, class D, class B> struct OptimizationEstimation : OptimizationEstimationImpl<T, D, B >
    {
        // using __impl::OptimizationEstimation<T, D, B >::OptimizationEstimation;
        OptimizationEstimation();
        OptimizationEstimation(D const * estimated, typename B::data_type const * data);
        OptimizationEstimation(const OptimizationEstimation< T, D, B>& estimation);
        virtual ~OptimizationEstimation();

        const T get_iteration(const Index& index) const;

        struct Estimator : OptimizationEstimationImpl<T, D, B >::Estimator
        { 
            Estimator();
            Estimator(const Estimator& estimator);
            virtual ~Estimator();
        };
    };

    template<class T, class D, class B> struct OptimizationEstimation< T*, D, B> : OptimizationEstimationImpl<T*, D, B >
    {
        // using OptimizationEstimationImpl<T*, D, B >::OptimizationEstimation;
        OptimizationEstimation();
        OptimizationEstimation(D const * estimated, typename B::data_type const * data);
        OptimizationEstimation(const OptimizationEstimation< T*, D, B>& estimation);
        virtual ~OptimizationEstimation();

        const T* get_iteration(const Index& index) const;

        struct Estimator : OptimizationEstimationImpl<T*, D, B >::Estimator
        { 
            Estimator();
            Estimator(const Estimator& estimator);
            virtual ~Estimator();
        };
    };

    struct STATISKIT_CORE_API CategoricalUnivariateDistributionEstimation : UnivariateDistributionEstimation
    { struct STATISKIT_CORE_API Estimator; };

    typedef LazyEstimation< CategoricalUnivariateDistribution, CategoricalUnivariateDistributionEstimation > CategoricalUnivariateDistributionLazyEstimation;
    typedef ActiveEstimation< CategoricalUnivariateDistribution, CategoricalUnivariateDistributionEstimation > CategoricalUnivariateDistributionActiveEstimation;

    typedef ListSelection< CategoricalUnivariateDistribution, CategoricalUnivariateDistributionEstimation > CategoricalUnivariateDistributionListSelection;
    typedef CategoricalUnivariateDistributionListSelection::CriterionEstimator CategoricalUnivariateDistributionCriterionEstimator;


    struct STATISKIT_CORE_API DiscreteUnivariateDistributionEstimation : UnivariateDistributionEstimation
    { struct STATISKIT_CORE_API Estimator : UnivariateDistributionEstimation::Estimator {}; };

    typedef ListSelection< DiscreteUnivariateDistribution, DiscreteUnivariateDistributionEstimation > DiscreteUnivariateDistributionListSelection;
    typedef DiscreteUnivariateDistributionListSelection::CriterionEstimator DiscreteUnivariateDistributionCriterionEstimator;

    struct STATISKIT_CORE_API ContinuousUnivariateDistributionEstimation : UnivariateDistributionEstimation
    { struct STATISKIT_CORE_API Estimator : UnivariateDistributionEstimation::Estimator {}; };

    typedef ListSelection< ContinuousUnivariateDistribution, ContinuousUnivariateDistributionEstimation > ContinuousUnivariateDistributionListSelection;
    typedef ContinuousUnivariateDistributionListSelection::CriterionEstimator ContinuousUnivariateDistributionCriterionEstimator;

    struct STATISKIT_CORE_API MultivariateDistributionEstimation
    {
        typedef MultivariateData data_type;
        typedef MultivariateDistribution estimated_type;
        typedef UnivariateDistributionEstimation marginal_type;

        virtual ~MultivariateDistributionEstimation() = 0;

        virtual estimated_type const * get_estimated() const = 0;
        
        struct STATISKIT_CORE_API Estimator
        {
            typedef MultivariateDistributionEstimation estimation_type;
            typedef UnivariateDistributionEstimation marginal_type;

            virtual ~Estimator() = 0;

            virtual std::unique_ptr< estimation_type > operator() (const data_type& data, const bool& lazy=true) const = 0;

            virtual std::unique_ptr< Estimator > copy() const = 0;
        };
    };

    typedef ListSelection< MultivariateDistribution, MultivariateDistributionEstimation > MixedMultivariateDistributionListSelection;
    typedef MixedMultivariateDistributionListSelection::CriterionEstimator MixedMultivariateDistributionCriterionEstimator;

    struct STATISKIT_CORE_API CategoricalMultivariateDistributionEstimation : MultivariateDistributionEstimation
    {
        typedef CategoricalUnivariateDistributionEstimation marginal_type;

        struct STATISKIT_CORE_API Estimator : MultivariateDistributionEstimation::Estimator {};
    };

    typedef ListSelection< CategoricalMultivariateDistribution, CategoricalMultivariateDistributionEstimation > CategoricalMultivariateDistributionListSelection;
    typedef CategoricalMultivariateDistributionListSelection::CriterionEstimator CategoricalMultivariateDistributionCriterionEstimator;

    struct STATISKIT_CORE_API DiscreteMultivariateDistributionEstimation : MultivariateDistributionEstimation
    {
        typedef DiscreteUnivariateDistributionEstimation marginal_type;

        struct STATISKIT_CORE_API Estimator : MultivariateDistributionEstimation::Estimator {};
    };

    typedef ListSelection< DiscreteMultivariateDistribution, DiscreteMultivariateDistributionEstimation > DiscreteMultivariateDistributionListSelection;
    typedef DiscreteMultivariateDistributionListSelection::CriterionEstimator DiscreteMultivariateDistributionCriterionEstimator;

    struct STATISKIT_CORE_API ContinuousMultivariateDistributionEstimation : MultivariateDistributionEstimation
    {
        typedef ContinuousUnivariateDistributionEstimation marginal_type;

        struct STATISKIT_CORE_API Estimator : MultivariateDistributionEstimation::Estimator {};
    };

    typedef ListSelection< ContinuousMultivariateDistribution, ContinuousMultivariateDistributionEstimation > ContinuousMultivariateDistributionListSelection;
    typedef ContinuousMultivariateDistributionListSelection::CriterionEstimator ContinuousMultivariateDistributionCriterionEstimator;
}

#include "estimation.hpp"
#endif