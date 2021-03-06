/**********************************************************************************/
/*                                                                                */
/* StatisKit-CoreThis software is distributed under the CeCILL-C license. You     */
/* should have received a copy of the legalcode along with this work. If not, see */
/* <http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html>.                 */
/*                                                                                */
/**********************************************************************************/

#include "estimator.h"

namespace statiskit
{
    PoissonDistributionMLEstimation::PoissonDistributionMLEstimation() : ActiveEstimation< PoissonDistribution, DiscreteUnivariateDistributionEstimation >()
    {}

    PoissonDistributionMLEstimation::PoissonDistributionMLEstimation(PoissonDistribution const * estimated, UnivariateData const * data) : ActiveEstimation< PoissonDistribution, DiscreteUnivariateDistributionEstimation >(estimated, data)
    {}

    PoissonDistributionMLEstimation::PoissonDistributionMLEstimation(const PoissonDistributionMLEstimation& estimation) : ActiveEstimation< PoissonDistribution, DiscreteUnivariateDistributionEstimation >(estimation)
    {}

    PoissonDistributionMLEstimation::~PoissonDistributionMLEstimation()
    {}

    PoissonDistributionMLEstimation::Estimator::Estimator()
    {}

    PoissonDistributionMLEstimation::Estimator::Estimator(const Estimator& estimator)
    {}

    PoissonDistributionMLEstimation::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > PoissonDistributionMLEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != DISCRETE)
        { throw statiskit::sample_space_error(DISCRETE); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation; 
        NaturalMeanEstimation::Estimator estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< MeanEstimation > _estimation = estimator(data);
        double mean = _estimation->get_mean(); 
        if(boost::math::isfinite(mean))
        {
            PoissonDistribution* poisson = new PoissonDistribution(mean);
            if(lazy)
            { estimation = std::make_unique< LazyEstimation< PoissonDistribution, DiscreteUnivariateDistributionEstimation > >(poisson); }
            else
            { estimation = std::make_unique< PoissonDistributionMLEstimation >(poisson, &data); }
        }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > PoissonDistributionMLEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    BinomialDistributionMLEstimation::BinomialDistributionMLEstimation() : OptimizationEstimation<unsigned int, BinomialDistribution, DiscreteUnivariateDistributionEstimation >()
    {}

    BinomialDistributionMLEstimation::BinomialDistributionMLEstimation(BinomialDistribution const * estimated, UnivariateData const * data) : OptimizationEstimation<unsigned int, BinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimated, data)
    {}
    
    BinomialDistributionMLEstimation::BinomialDistributionMLEstimation(const BinomialDistributionMLEstimation& estimation) : OptimizationEstimation<unsigned int, BinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimation)
    {}

    BinomialDistributionMLEstimation::~BinomialDistributionMLEstimation()
    {}

    BinomialDistributionMLEstimation::Estimator::Estimator() : OptimizationEstimation<unsigned int, BinomialDistribution, DiscreteUnivariateDistributionEstimation >::Estimator()
    { _force = false; }
    
    BinomialDistributionMLEstimation::Estimator::Estimator(const Estimator& estimator) : OptimizationEstimation<unsigned int, BinomialDistribution, DiscreteUnivariateDistributionEstimation >::Estimator(estimator)
    { _force = estimator._force; }

    BinomialDistributionMLEstimation::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > BinomialDistributionMLEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != DISCRETE)
        { throw statiskit::sample_space_error(DISCRETE); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation;
        NaturalMeanEstimation::Estimator mean_estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< MeanEstimation > mean_estimation = mean_estimator(data);
        double mean = mean_estimation->get_mean();
        NaturalVarianceEstimation::Estimator variance_estimator = NaturalVarianceEstimation::Estimator(false);
        std::unique_ptr< VarianceEstimation > variance_estimation = variance_estimator(data, mean);
        double variance = variance_estimation->get_variance(); 
        if(variance > mean && !_force)
        { throw overdispersion_error(); }
        unsigned int kappa = std::max<int>(round(pow(mean, 2)/(mean - variance)), static_cast< DiscreteElementaryEvent* >(data.compute_maximum().get())->get_value());
        BinomialDistribution* binomial = new BinomialDistribution(kappa, mean/double(kappa));
        if(!lazy)
        {
            estimation = std::make_unique< BinomialDistributionMLEstimation >(binomial, &data);
            static_cast< BinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa);
        }
        else
        { estimation = std::make_unique< LazyEstimation< BinomialDistribution, DiscreteUnivariateDistributionEstimation > >(binomial); }
        double curr, prev = binomial->loglikelihood(data);
        unsigned int its = 1;
        --kappa;
        if(kappa > mean)
        {
            if(!lazy)
            { static_cast< BinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa); }
            binomial->set_kappa(kappa);
            binomial->set_pi(mean/double(kappa));
            curr = binomial->loglikelihood(data);
        }
        else
        { curr = prev; }
        if(curr > prev)
        {
            do
            {
                prev = curr;
                --kappa;
                if(!lazy)
                { static_cast< BinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa); }
                binomial->set_kappa(kappa);
                binomial->set_pi(mean/double(kappa));
                curr = binomial->loglikelihood(data);
                ++its;
            } while(run(its, __impl::reldiff(prev, curr)) && curr > prev);
            if(curr < prev)
            {
                ++kappa;
                if(!lazy)
                { static_cast< BinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa); }
                binomial->set_kappa(kappa);
                binomial->set_pi(mean/double(kappa));
            }
        }
        else
        {
            ++kappa;
            do
            {
                prev = curr;
                ++kappa;
                if(!lazy)
                { static_cast< BinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa); }
                binomial->set_kappa(kappa);
                binomial->set_pi(mean/double(kappa));
                curr = binomial->loglikelihood(data);
                ++its;
            } while(run(its, __impl::reldiff(prev, curr)) && curr > prev);
            if(curr < prev)
            {
                --kappa;
                if(!lazy)
                { static_cast< BinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa); }
                binomial->set_kappa(kappa);
                binomial->set_pi(mean/double(kappa));
            }
        }
        return estimation;
    }

    bool BinomialDistributionMLEstimation::Estimator::get_force() const
    { return _force; }

    void BinomialDistributionMLEstimation::Estimator::set_force(const bool& force)
    { _force = force; }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > BinomialDistributionMLEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    BinomialDistributionMMEstimation::BinomialDistributionMMEstimation() : ActiveEstimation< BinomialDistribution, DiscreteUnivariateDistributionEstimation >()
    {}

    BinomialDistributionMMEstimation::BinomialDistributionMMEstimation(BinomialDistribution const * estimated, UnivariateData const * data) : ActiveEstimation< BinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimated, data)
    {}
    
    BinomialDistributionMMEstimation::BinomialDistributionMMEstimation(const BinomialDistributionMMEstimation& estimation) : ActiveEstimation< BinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimation)
    {}

    BinomialDistributionMMEstimation::~BinomialDistributionMMEstimation()
    {}

    BinomialDistributionMMEstimation::Estimator::Estimator()
    {
        _mean = new NaturalMeanEstimation::Estimator();
        _variance = new NaturalVarianceEstimation::Estimator(false);
    }

    BinomialDistributionMMEstimation::Estimator::Estimator(const Estimator& estimator)
    {
        _mean = estimator._mean->copy().release();
        _variance = estimator._variance->copy().release();
    }

    BinomialDistributionMMEstimation::Estimator::~Estimator()
    {
        delete _mean;
        delete _variance;
    }

    std::unique_ptr< UnivariateDistributionEstimation > BinomialDistributionMMEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != DISCRETE)
        { throw statiskit::sample_space_error(DISCRETE); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation; 
        std::unique_ptr< MeanEstimation > mean_estimation = (*_mean)(data);
        double mean = mean_estimation->get_mean(); 
        std::unique_ptr< VarianceEstimation > variance_estimation = (*_variance)(data, mean);
        double variance = variance_estimation->get_variance(); 
        if(boost::math::isfinite(mean) && boost::math::isfinite(variance) && mean > variance)
        {
            unsigned int kappa = std::max<int>(round(pow(mean, 2)/(mean - variance)), static_cast< DiscreteElementaryEvent* >(data.compute_maximum().get())->get_value());
            BinomialDistribution* binomial = new BinomialDistribution(kappa, mean/double(kappa));
            if(lazy)
            { estimation = std::make_unique< LazyEstimation< BinomialDistribution, DiscreteUnivariateDistributionEstimation > >(binomial); }
            else
            { estimation = std::make_unique< BinomialDistributionMMEstimation >(binomial, &data); }
        }
        else
        { throw overdispersion_error(); }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > BinomialDistributionMMEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    MeanEstimation::Estimator* BinomialDistributionMMEstimation::Estimator::get_mean()
    { return _mean; }

    void BinomialDistributionMMEstimation::Estimator::set_mean(const MeanEstimation::Estimator& mean)
    { _mean = mean.copy().release(); }

    VarianceEstimation::Estimator* BinomialDistributionMMEstimation::Estimator::get_variance()
    { return _variance; }

    void BinomialDistributionMMEstimation::Estimator::set_variance(const VarianceEstimation::Estimator& variance)
    { _variance = variance.copy().release(); }

    NegativeBinomialDistributionMLEstimation::NegativeBinomialDistributionMLEstimation() : OptimizationEstimation<double, NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >()
    {}

    NegativeBinomialDistributionMLEstimation::NegativeBinomialDistributionMLEstimation(NegativeBinomialDistribution const * estimated, UnivariateData const * data) : OptimizationEstimation<double, NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimated, data)
    {}
    
    NegativeBinomialDistributionMLEstimation::NegativeBinomialDistributionMLEstimation(const NegativeBinomialDistributionMLEstimation& estimation) : OptimizationEstimation<double, NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimation)
    {}

    NegativeBinomialDistributionMLEstimation::~NegativeBinomialDistributionMLEstimation()
    {}

    NegativeBinomialDistributionMLEstimation::Estimator::Estimator() : OptimizationEstimation<double, NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >::Estimator()
    { _force = false; }
    
    NegativeBinomialDistributionMLEstimation::Estimator::Estimator(const Estimator& estimator) : OptimizationEstimation<double, NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >::Estimator(estimator)
    { _force = estimator._force; }

    NegativeBinomialDistributionMLEstimation::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > NegativeBinomialDistributionMLEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != DISCRETE)
        { throw statiskit::sample_space_error(DISCRETE); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation;
        NaturalMeanEstimation::Estimator mean_estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< MeanEstimation > mean_estimation = mean_estimator(data);
        double mean = mean_estimation->get_mean();
        NaturalVarianceEstimation::Estimator variance_estimator = NaturalVarianceEstimation::Estimator(false);
        std::unique_ptr< VarianceEstimation > variance_estimation = variance_estimator(data, mean);
        double variance = variance_estimation->get_variance();
        if(variance < mean && !_force)
        { throw underdispersion_error(); }
        double total = data.compute_total(), kappa;
        if(variance > mean)
        { kappa = pow(mean, 2)/(variance - mean); }
        else
        { kappa = 1.; }
        NegativeBinomialDistribution* negative_binomial = new NegativeBinomialDistribution(kappa, mean / (mean + kappa));
        if(!lazy)
        {
            estimation = std::make_unique< NegativeBinomialDistributionMLEstimation >(negative_binomial, &data);
            static_cast< NegativeBinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa);
        }
        else
        { estimation = std::make_unique< LazyEstimation< NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation > >(negative_binomial); }
        double prev, curr = negative_binomial->loglikelihood(data);
        unsigned int its = 1;
        do
        {
            prev = curr;
            double alpha = 0;
            std::unique_ptr< UnivariateData::Generator > generator = data.generator();
            while(generator->is_valid())
            {
                const UnivariateEvent* event = generator->event();
                if(event && event->get_event() == ELEMENTARY)
                {
                    for(int nu = 0, max_nu = static_cast< const DiscreteElementaryEvent* >(event)->get_value(); nu < max_nu; ++nu)
                    { alpha += nu/(nu + kappa); }
                }
                ++(*generator);
            }
            alpha /= -total;
            alpha += mean;
            kappa = log(1 + mean/kappa)/alpha;
            if(!lazy)
            { static_cast< NegativeBinomialDistributionMLEstimation* >(estimation.get())->_iterations.push_back(kappa); }
            negative_binomial->set_kappa(kappa);
            negative_binomial->set_pi(mean/(mean + kappa));
            curr = negative_binomial->loglikelihood(data);
            ++its;
        } while(run(its, __impl::reldiff(prev, curr)));
        return estimation;
    }

    bool NegativeBinomialDistributionMLEstimation::Estimator::get_force() const
    { return _force; }

    void NegativeBinomialDistributionMLEstimation::Estimator::set_force(const bool& force)
    { _force = force; }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > NegativeBinomialDistributionMLEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    NegativeBinomialDistributionMMEstimation::NegativeBinomialDistributionMMEstimation() : ActiveEstimation< NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >()
    {}

    NegativeBinomialDistributionMMEstimation::NegativeBinomialDistributionMMEstimation(NegativeBinomialDistribution const * estimated, UnivariateData const * data) : ActiveEstimation< NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimated, data)
    {}
    
    NegativeBinomialDistributionMMEstimation::NegativeBinomialDistributionMMEstimation(const NegativeBinomialDistributionMMEstimation& estimation) : ActiveEstimation< NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation >(estimation)
    {}
    
    NegativeBinomialDistributionMMEstimation::~NegativeBinomialDistributionMMEstimation()
    {}

    NegativeBinomialDistributionMMEstimation::Estimator::Estimator()
    {
        _mean = new NaturalMeanEstimation::Estimator();
        _variance = new NaturalVarianceEstimation::Estimator(false);
    }

    NegativeBinomialDistributionMMEstimation::Estimator::Estimator(const Estimator& estimator)
    {
        _mean = estimator._mean->copy().release();
        _variance = estimator._variance->copy().release();
    }

    NegativeBinomialDistributionMMEstimation::Estimator::~Estimator()
    {
        delete _mean;
        delete _variance;
    }

    std::unique_ptr< UnivariateDistributionEstimation > NegativeBinomialDistributionMMEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != DISCRETE)
        { throw statiskit::sample_space_error(DISCRETE); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation; 
        std::unique_ptr< MeanEstimation > mean_estimation = (*_mean)(data);
        double mean = mean_estimation->get_mean(); 
        std::unique_ptr< VarianceEstimation > variance_estimation = (*_variance)(data, mean);
        double variance = variance_estimation->get_variance(); 
        if(boost::math::isfinite(mean) && boost::math::isfinite(variance) && variance > mean)
        {
            NegativeBinomialDistribution* negbinomial = new NegativeBinomialDistribution(pow(mean, 2)/(variance - mean), 1. - mean/variance);
            if(lazy)
            { estimation = std::make_unique< LazyEstimation< NegativeBinomialDistribution, DiscreteUnivariateDistributionEstimation > >(negbinomial); }
            else
            { estimation = std::make_unique< NegativeBinomialDistributionMMEstimation >(negbinomial, &data); }
        }
        else
        { throw underdispersion_error(); }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > NegativeBinomialDistributionMMEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }
    
    MeanEstimation::Estimator* NegativeBinomialDistributionMMEstimation::Estimator::get_mean()
    { return _mean; }

    void NegativeBinomialDistributionMMEstimation::Estimator::set_mean(const MeanEstimation::Estimator& mean)
    { _mean = mean.copy().release(); }

    VarianceEstimation::Estimator* NegativeBinomialDistributionMMEstimation::Estimator::get_variance()
    { return _variance; }

    void NegativeBinomialDistributionMMEstimation::Estimator::set_variance(const VarianceEstimation::Estimator& variance)
    { _variance = variance.copy().release(); }

    NormalDistributionMLEstimation::NormalDistributionMLEstimation() : ActiveEstimation< NormalDistribution, ContinuousUnivariateDistributionEstimation >()
    {}

    NormalDistributionMLEstimation::NormalDistributionMLEstimation(NormalDistribution const * estimated, UnivariateData const * data) : ActiveEstimation< NormalDistribution, ContinuousUnivariateDistributionEstimation >(estimated, data)
    {}

    NormalDistributionMLEstimation::NormalDistributionMLEstimation(const NormalDistributionMLEstimation& estimation) : ActiveEstimation< NormalDistribution, ContinuousUnivariateDistributionEstimation >(estimation)
    {}

    NormalDistributionMLEstimation::~NormalDistributionMLEstimation()
    {}

    NormalDistributionMLEstimation::Estimator::Estimator()
    {}

    NormalDistributionMLEstimation::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > NormalDistributionMLEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != CONTINUOUS)
        { throw statiskit::sample_space_error(CONTINUOUS); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation;
        NaturalMeanEstimation::Estimator mean_estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< MeanEstimation > mean_estimation = mean_estimator(data);
        double mean = mean_estimation->get_mean(); 
        NaturalVarianceEstimation::Estimator variance_estimator = NaturalVarianceEstimation::Estimator(false);
        std::unique_ptr< VarianceEstimation > variance_estimation = variance_estimator(data, mean);
        double std_err = sqrt(variance_estimation->get_variance()); 
        if(boost::math::isfinite(mean) && boost::math::isfinite(std_err))
        {
            NormalDistribution* normal = new NormalDistribution(mean, std_err);
            if(lazy)
            { estimation = std::make_unique< LazyEstimation< NormalDistribution, ContinuousUnivariateDistributionEstimation > >(normal); }
            else
            { estimation = std::make_unique< NormalDistributionMLEstimation >(normal, &data); }
        }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > NormalDistributionMLEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    UnivariateHistogramDistributionEstimation::UnivariateHistogramDistributionEstimation() : ActiveEstimation< UnivariateHistogramDistribution, ContinuousUnivariateDistributionEstimation >()
    {}

    UnivariateHistogramDistributionEstimation::UnivariateHistogramDistributionEstimation(UnivariateHistogramDistribution const * estimated, UnivariateData const * data) : ActiveEstimation< UnivariateHistogramDistribution, ContinuousUnivariateDistributionEstimation >(estimated, data)
    {}

    UnivariateHistogramDistributionEstimation::UnivariateHistogramDistributionEstimation(const UnivariateHistogramDistributionEstimation& estimation) : ActiveEstimation< UnivariateHistogramDistribution, ContinuousUnivariateDistributionEstimation >(estimation)
    {}

    UnivariateHistogramDistributionEstimation::~UnivariateHistogramDistributionEstimation()
    {}

    UnivariateHistogramDistributionEstimation::Estimator::Estimator()
    { _nb_bins = 0; }

    UnivariateHistogramDistributionEstimation::Estimator::Estimator(const Estimator& estimator)
    { _nb_bins = estimator._nb_bins; }

    UnivariateHistogramDistributionEstimation::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > UnivariateHistogramDistributionEstimation::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != CONTINUOUS)
        { throw statiskit::sample_space_error(CONTINUOUS); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation;
        auto bins = std::set< double >();
        double total = 0., min = std::numeric_limits< double >::infinity(), max = -1 * std::numeric_limits< double >::infinity();
        std::unique_ptr< UnivariateData::Generator > generator = data.generator();
        double nb_bins = 0;
        while(generator->is_valid())
        {
            auto event = generator->event();
            if(event && event->get_event() == ELEMENTARY)
            {
                auto cevent = static_cast< const ContinuousElementaryEvent* >(event);
                min = std::min(min, cevent->get_value());
                max = std::max(max, cevent->get_value());
                total += generator->weight(); 
                nb_bins += 1;                           
            }
            ++(*generator);
        }
        if(_nb_bins != 0)
        { nb_bins = _nb_bins; }
        bins.insert(min - .5 / total * (max - min));
        for(Index index = 1; index < nb_bins; ++index)
        { bins.insert(*(bins.rbegin()) + 1. / nb_bins * (max-min)); }
        bins.insert(max + .5 / nb_bins * (max - min));
        if(bins.size() > 1)
        {
            auto lengths = std::vector< double >(bins.size()-1, 0.);
            std::set< double >::iterator itl = bins.begin(), itr, it_end = bins.end();
            itr = itl;
            ++itr;
            while(itr != it_end)
            {
                lengths[distance(bins.begin(), itl)] = *itr - *itl;
                ++itl;
                ++itr;
            }
            auto densities = std::vector< double >(bins.size()-1, 0.);
            std::set< double >::iterator it;
            generator = data.generator();
            while(generator->is_valid())
            {
                auto event = generator->event();
                if(event)
                {
                    if(event->get_event() == ELEMENTARY)
                    {
                        it = bins.upper_bound(static_cast< const ContinuousElementaryEvent* >(event)->get_value());
                        if(it == bins.end())
                        { densities.back() += generator->weight() / (lengths.back() * total); }
                        else if(it == bins.begin())
                        { densities.front() += generator->weight() / (lengths.front() * total); }
                        else
                        { densities[distance(bins.begin(), it) - 1] += generator->weight() /(lengths[distance(bins.begin(), it) - 1] * total); }
                    }
                }
                ++(*generator);
            }
            UnivariateHistogramDistribution* histogram = new UnivariateHistogramDistribution(bins, densities);
            if(lazy)
            { estimation = std::make_unique< LazyEstimation< UnivariateHistogramDistribution, ContinuousUnivariateDistributionEstimation > >(histogram); }
            else
            { estimation = std::make_unique< UnivariateHistogramDistributionEstimation >(histogram, &data); }
        }
        else
        { throw sample_size_error(1); }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > UnivariateHistogramDistributionEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    const unsigned int& UnivariateHistogramDistributionEstimation::Estimator::get_nb_bins() const
    { return _nb_bins; }

    void UnivariateHistogramDistributionEstimation::Estimator::set_nb_bins(const unsigned int& nb_bins)
    { _nb_bins = nb_bins; }

    RegularUnivariateHistogramDistributionSlopeHeuristicSelection::RegularUnivariateHistogramDistributionSlopeHeuristicSelection(const UnivariateData* data) : SlopeHeuristicSelection< ContinuousUnivariateDistributionEstimation >(data)
    {}

    RegularUnivariateHistogramDistributionSlopeHeuristicSelection::RegularUnivariateHistogramDistributionSlopeHeuristicSelection(const RegularUnivariateHistogramDistributionSlopeHeuristicSelection& selection) : SlopeHeuristicSelection< ContinuousUnivariateDistributionEstimation >(selection)
    {}

    RegularUnivariateHistogramDistributionSlopeHeuristicSelection::~RegularUnivariateHistogramDistributionSlopeHeuristicSelection()
    {}

    RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::Estimator()
    { _maxbins = 100; }

    RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::Estimator(const Estimator& estimator)
    { _maxbins = estimator._maxbins; }

    RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != CONTINUOUS)
        { throw statiskit::sample_space_error(CONTINUOUS); }
        RegularUnivariateHistogramDistributionSlopeHeuristicSelection* cache;
        if(lazy)
        { cache = new RegularUnivariateHistogramDistributionSlopeHeuristicSelection(nullptr); }
        else
        { cache = new RegularUnivariateHistogramDistributionSlopeHeuristicSelection(&data); }
        std::set< double > bins = std::set< double >();
        UnivariateHistogramDistributionEstimation::Estimator estimator = UnivariateHistogramDistributionEstimation::Estimator();
        for(Index nb_bins = _maxbins; nb_bins > 0; --nb_bins)
        {
            estimator.set_nb_bins(nb_bins);
            try
            {
                std::unique_ptr< UnivariateDistributionEstimation > estimation = estimator(data, true);
                UnivariateHistogramDistribution* estimated = const_cast< UnivariateHistogramDistribution* >(static_cast< const UnivariateHistogramDistribution* >(estimation->get_estimated()));
                cache->add(estimated->get_nb_parameters(), estimated->loglikelihood(data), static_cast< UnivariateHistogramDistribution* >(estimated->copy().release()));
            } 
            catch(const std::exception& error)
            {}
        }
        cache->finalize();
        std::unique_ptr< UnivariateDistributionEstimation > estimation;
        if(lazy)
        {
            estimation = std::make_unique< LazyEstimation< UnivariateHistogramDistribution, ContinuousUnivariateDistributionEstimation > >(static_cast< UnivariateHistogramDistribution* >(cache->get_estimated()->copy().release()));
            delete cache;
        }
        else
        { estimation.reset(cache); }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    const unsigned int& RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::get_maxbins() const
    { return _maxbins; }

    void RegularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::set_maxbins(const unsigned int& maxbins)
    {
        if(maxbins == 0)
        { throw statiskit::lower_bound_error("maxbins", 0, 0, true); }
        _maxbins = maxbins;
    }


    IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::IrregularUnivariateHistogramDistributionSlopeHeuristicSelection(const UnivariateData* data) : SlopeHeuristicSelection< ContinuousUnivariateDistributionEstimation >(data)
    {}

    IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::IrregularUnivariateHistogramDistributionSlopeHeuristicSelection(const IrregularUnivariateHistogramDistributionSlopeHeuristicSelection& selection) : SlopeHeuristicSelection< ContinuousUnivariateDistributionEstimation >(selection)
    {}
    
    IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::~IrregularUnivariateHistogramDistributionSlopeHeuristicSelection()
    {}

    IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::Estimator()
    {
        _maxbins = 100; 
        _constant = 1.;
    }

    IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::Estimator(const Estimator& estimator)
    { 
        _maxbins = estimator._maxbins;
        _constant = estimator._constant;
    }

    IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::~Estimator()
    {}

    std::unique_ptr< UnivariateDistributionEstimation > IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::operator() (const UnivariateData& data, const bool& lazy) const
    {
        if(data.get_sample_space()->get_outcome() != CONTINUOUS)
        { throw statiskit::sample_space_error(CONTINUOUS); }
        IrregularUnivariateHistogramDistributionSlopeHeuristicSelection* cache;
        if(lazy)
        { cache = new IrregularUnivariateHistogramDistributionSlopeHeuristicSelection(nullptr); }
        else
        { cache = new IrregularUnivariateHistogramDistributionSlopeHeuristicSelection(&data); }
        std::set< double > bins = std::set< double >();
        unsigned int elements = 0;
        double total = 0., min = std::numeric_limits< double >::infinity(), max = -1 * std::numeric_limits< double >::infinity();
        std::unique_ptr< UnivariateData::Generator > generator = data.generator();
        while(generator->is_valid())
        {
            const UnivariateEvent* event = generator->event();
            if(event && event->get_event() == ELEMENTARY)
            {
                const ContinuousElementaryEvent* cevent = static_cast< const ContinuousElementaryEvent* >(event);
                min = std::min(min, cevent->get_value());
                max = std::max(max, cevent->get_value());
                total += generator->weight();    
            }
            ++(*generator);
        }
        bins.insert(min - .5 / _maxbins * (max - min));
        for(Index index = 1; index < _maxbins; ++index)
        { bins.insert(*(bins.rbegin()) + 1. / _maxbins * (max-min)); }
        bins.insert(max + .5 / _maxbins * (max - min));
        if(bins.size() > 1)
        {
            std::vector< double > lengths = std::vector< double >(bins.size()-1, 0.);
            std::set< double >::iterator itl = bins.begin(), itr, it_end = bins.end();
            itr = itl;
            ++itr;
            while(itr != it_end)
            {
                lengths[distance(bins.begin(), itl)] = *itr - *itl;
                ++itl;
                ++itr;
            }
            std::vector< double > densities = std::vector< double >(bins.size()-1, 0.);
            std::set< double >::iterator it;
            generator = data.generator();
            while(generator->is_valid())
            {
                const UnivariateEvent* event = generator->event();
                if(event)
                {
                    if(event->get_event() == ELEMENTARY)
                    {
                        it = bins.upper_bound(static_cast< const ContinuousElementaryEvent* >(event)->get_value());
                        if(it == bins.end())
                        { densities.back() += generator->weight() /(lengths.back() * total); }
                        else if(it == bins.begin())
                        { densities.front() +=  generator->weight() /(lengths.front() * total); }
                        else
                        { densities[distance(bins.begin(), it) - 1] += generator->weight() /(lengths[distance(bins.begin(), it) - 1] * total); }
                    }
                }
                ++(*generator);
            }
            std::vector< double > entropies = std::vector< double >(densities.size()-1, std::numeric_limits< double >::quiet_NaN());
            for(Index index = 0, max_index = densities.size()-1; index < max_index; ++index)
            {
                entropies[index] = 0;
                if(densities[index] > 0.)
                { entropies[index] += lengths[index] * densities[index] * log(densities[index]); }
                if(densities[index + 1] > 0.)
                { entropies[index] += lengths[index + 1] * densities[index + 1] * log(densities[index + 1]); }
                double p = (lengths[index] * densities[index] + lengths[index + 1] * densities[index+1]) / (lengths[index] + lengths[index + 1]);
                if(p > 0.)
                { entropies[index] -= (lengths[index] + lengths[index + 1]) * p * log(p); }
                else
                { entropies[index] = std::numeric_limits< double >::infinity(); }
            }
            double score = 0.;
            while(bins.size() > 2)
            {
                std::vector< double >::iterator it = std::min_element(entropies.begin(), entropies.end()), itr;
                if(*it > 0)
                {
                    score -= *it;
                    // if(bins.size() < _maxbins)
                    // {
                        UnivariateHistogramDistribution* current = new UnivariateHistogramDistribution(bins, densities);
                        double penshape = bins.size()-1;
                        penshape = penshape * (1 + _constant * log(_maxbins) - _constant * log(penshape));
                        cache->add(penshape, score, current);
                    // }
                }
                itr = it;
                ++itr;
                densities[distance(entropies.begin(), itr)] = lengths[distance(entropies.begin(), it)] * densities[distance(entropies.begin(), it)] + lengths[distance(entropies.begin(), itr)] * densities[distance(entropies.begin(), itr)];
                densities[distance(entropies.begin(), itr)] /= lengths[distance(entropies.begin(), it)] + lengths[distance(entropies.begin(), itr)];
                lengths[distance(entropies.begin(), itr)] = lengths[distance(entropies.begin(), it)] + lengths[distance(entropies.begin(), itr)];
                std::vector< double >::iterator itd = densities.begin();
                advance(itd, distance(entropies.begin(), it));
                densities.erase(itd);
                std::vector< double >::iterator itl = lengths.begin();
                advance(itl, distance(entropies.begin(), it));
                lengths.erase(itl);
                std::set< double >::iterator itb = bins.begin();
                advance(itb, distance(entropies.begin(), itr));
                bins.erase(itb);
                // TODO optimize
                entropies = std::vector< double >(densities.size()-1, std::numeric_limits< double >::quiet_NaN());
                for(Index index = 0, max_index = densities.size()-1; index < max_index; ++index)
                { 
                    entropies[index] = 0;
                    if(densities[index] > 0.)
                    { entropies[index] += lengths[index] * densities[index] * log(densities[index]); }
                    if(densities[index + 1] > 0.)
                    { entropies[index] += lengths[index + 1] * densities[index + 1] * log(densities[index + 1]); }
                    double p = (lengths[index] * densities[index] + lengths[index + 1] * densities[index+1]) / (lengths[index] + lengths[index + 1]);
                    if(p > 0.)
                    { entropies[index] -= (lengths[index] + lengths[index + 1]) * p * log(p); }
                    else
                    { entropies[index] = std::numeric_limits< double >::infinity(); }
                }
            }
            cache->finalize();
        }
        else
        { throw sample_size_error(1); }
        std::unique_ptr< UnivariateDistributionEstimation > estimation;
        if(lazy)
        {
            estimation = std::make_unique< LazyEstimation< UnivariateHistogramDistribution, ContinuousUnivariateDistributionEstimation > >(static_cast<  UnivariateHistogramDistribution* >(cache->get_estimated()->copy().release()));
            delete cache;
        }
        else
        { estimation.reset(cache); }
        return estimation;
    }

    std::unique_ptr< UnivariateDistributionEstimation::Estimator > IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    const unsigned int& IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::get_maxbins() const
    { return _maxbins; }

    void IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::set_maxbins(const unsigned int& maxbins)
    {
        if(maxbins == 0)
        { throw statiskit::lower_bound_error("maxbins", 0, 0, true); }
        _maxbins = maxbins;
    }
    
    const double& IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::get_constant() const
    { return _constant; }

    void IrregularUnivariateHistogramDistributionSlopeHeuristicSelection::Estimator::set_constant(const double& constant)
    {
        if(constant <= 0.)
        { throw statiskit::lower_bound_error("constant", constant, 0.0, true); }
        _constant = constant;
    }

    MultinomialSplittingDistributionEstimation::MultinomialSplittingDistributionEstimation() : ActiveEstimation< MultinomialSplittingDistribution, DiscreteMultivariateDistributionEstimation >()
    { _sum = nullptr; }

    MultinomialSplittingDistributionEstimation::MultinomialSplittingDistributionEstimation(MultinomialSplittingDistribution const * estimated, MultivariateData const * data) : ActiveEstimation< MultinomialSplittingDistribution, DiscreteMultivariateDistributionEstimation >(estimated, data)
    { _sum = nullptr; }

    MultinomialSplittingDistributionEstimation::MultinomialSplittingDistributionEstimation(const MultinomialSplittingDistributionEstimation& estimation) : ActiveEstimation< MultinomialSplittingDistribution, DiscreteMultivariateDistributionEstimation >(estimation)
    { _sum = estimation._sum; }

    MultinomialSplittingDistributionEstimation::~MultinomialSplittingDistributionEstimation()
    { 
        if(_sum)
        { delete _sum; }
        _sum = nullptr;
    }

    const DiscreteUnivariateDistributionEstimation* MultinomialSplittingDistributionEstimation::get_sum() const
    { return _sum; }

    MultinomialSplittingDistributionEstimation::Estimator::Estimator()
    { _sum = nullptr; }

    MultinomialSplittingDistributionEstimation::Estimator::Estimator(const Estimator& estimator)
    {
        if(estimator._sum)
        { _sum = static_cast< DiscreteUnivariateDistributionEstimation::Estimator* >(estimator._sum->copy().release()); }
        else
        { _sum = nullptr; }
    }

    MultinomialSplittingDistributionEstimation::Estimator::~Estimator()
    {
        if(_sum)
        {
            delete _sum;
            _sum = nullptr;
        }
    }

    std::unique_ptr< MultivariateDistributionEstimation > MultinomialSplittingDistributionEstimation::Estimator::operator() (const MultivariateData& data, const bool& lazy) const
    {
        SumData sum_data = SumData(&data);
        DiscreteUnivariateDistributionEstimation* sum_estimation = static_cast< DiscreteUnivariateDistributionEstimation* >(((*_sum)(sum_data, lazy)).release());
        std::unique_ptr< MultivariateDistributionEstimation > estimation;
        std::unique_ptr< MultivariateData::Generator > generator = data.generator();
        Eigen::VectorXd pi = Eigen::VectorXd::Zero(generator->event()->size());
        while(generator->is_valid())
        {
            const MultivariateEvent* mevent = generator->event();
            for(Index component = 0, max_component = mevent->size(); component < max_component; ++component)
            {
                const UnivariateEvent* uevent = mevent->get(component);
                if(uevent && uevent->get_outcome() == DISCRETE && uevent->get_event() == ELEMENTARY)
                { pi[component] += generator->weight() * static_cast< const DiscreteElementaryEvent* >(uevent)->get_value(); }
            }
            ++(*generator);
        }
        MultinomialSplittingDistribution* estimated = new MultinomialSplittingDistribution(static_cast< const DiscreteUnivariateDistribution& >(*(sum_estimation->get_estimated())), pi);
        if(lazy)
        { 
            estimation = std::make_unique< LazyEstimation< MultinomialSplittingDistribution, DiscreteMultivariateDistributionEstimation > >(estimated);
            delete sum_estimation;
        }
        else
        {
            estimation = std::make_unique< MultinomialSplittingDistributionEstimation >(estimated, &data);
            static_cast< MultinomialSplittingDistributionEstimation* >(estimation.get())->_sum = sum_estimation;
        }
        return estimation;
    }

    std::unique_ptr< MultivariateDistributionEstimation::Estimator > MultinomialSplittingDistributionEstimation::Estimator::copy() const
    { return std::make_unique< MultinomialSplittingDistributionEstimation::Estimator >(*this); }

    const DiscreteUnivariateDistributionEstimation::Estimator* MultinomialSplittingDistributionEstimation::Estimator::get_sum() const
    { return _sum; }

    void MultinomialSplittingDistributionEstimation::Estimator::set_sum(const DiscreteUnivariateDistributionEstimation::Estimator& sum)
    { _sum = static_cast< DiscreteUnivariateDistributionEstimation::Estimator* >(sum.copy().release()); }

    // std::unique_ptr< UnivariateData > MultinomialSplittingDistributionEstimation::Estimator::compute_sum(const MultivariateData& data) const
    // {
    //     UnivariateDataFrame* sum_data = new UnivariateDataFrame(get_NN());
    //     std::unique_ptr< MultivariateData::Generator > generator = data.generator();
    //     while(generator->is_valid())
    //     {
    //         int value = 0;
    //         const MultivariateEvent* mevent = generator->event();
    //         for(Index component = 0, max_component = mevent->size(); component < max_component; ++component)
    //         {
    //             const UnivariateEvent* uevent = mevent->get(component);
    //             if(uevent && uevent->get_outcome() == DISCRETE && uevent->get_event() == ELEMENTARY)
    //             { value += static_cast< const DiscreteElementaryEvent* >(uevent)->get_value(); }
    //         }
    //         sum_data->add_event(new DiscreteElementaryEvent(value));
    //         ++(*generator);
    //     }
    //     return std::move(std::unique_ptr< UnivariateData >(sum_data));
    // }

    MultinomialSplittingDistributionEstimation::Estimator::SumData::SumData(const MultivariateData* data)
    { _data = data; }

    MultinomialSplittingDistributionEstimation::Estimator::SumData::~SumData()
    {}

    std::unique_ptr< UnivariateData::Generator > MultinomialSplittingDistributionEstimation::Estimator::SumData::generator() const
    { return std::make_unique< MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator >(_data); }

    const UnivariateSampleSpace* MultinomialSplittingDistributionEstimation::Estimator::SumData::get_sample_space() const
    { return &get_NN(); }

    std::unique_ptr< UnivariateData > MultinomialSplittingDistributionEstimation::Estimator::SumData::copy() const
    {
        UnivariateDataFrame* data = new UnivariateDataFrame(get_NN());
        std::unique_ptr< UnivariateData::Generator > _generator = generator();
        while(_generator->is_valid())
        {
            data->add_event(_generator->event());
            ++(*_generator);
        }
        _generator = generator();
        WeightedSumData* weighted = new WeightedSumData(data);
        for(Index index = 0, max_index = weighted->get_nb_weights(); index < max_index; ++index)
        {
            weighted->set_weight(index, _generator->weight());
            ++(*_generator);
        }
        return std::unique_ptr< UnivariateData >(weighted);
    }

    MultinomialSplittingDistributionEstimation::Estimator::WeightedSumData::WeightedSumData(const UnivariateData* data)
    { init(data); }


    MultinomialSplittingDistributionEstimation::Estimator::WeightedSumData::WeightedSumData(const WeightedSumData& data)
    { 
        init(data);
        _data = data._data->copy().release();
    }

    MultinomialSplittingDistributionEstimation::Estimator::WeightedSumData::~WeightedSumData()
    { delete _data; }

    MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator::Generator(const MultivariateData* data)
    {
       _sum = nullptr;
       _generator = data->generator().release();
    }

    MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator::~Generator()
    {
        if(_sum)
        { delete _sum; }
        _sum = nullptr;
        if(_generator)
        { delete _generator; }
        _generator = nullptr;
    }

    bool MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator::is_valid() const
    { return _generator->is_valid(); }

    UnivariateData::Generator& MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator::operator++()
    {
       ++(*_generator);
       return *this;
    }

    const UnivariateEvent* MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator::event() const
    {
        if(_sum)
        { delete _sum; }
        int value = 0;
        const MultivariateEvent* mevent = _generator->event();
        for(Index component = 0, max_component = mevent->size(); component < max_component; ++component)
        {
            const UnivariateEvent* uevent = mevent->get(component);
            if(uevent && uevent->get_outcome() == DISCRETE && uevent->get_event() == ELEMENTARY)
            { value += static_cast< const DiscreteElementaryEvent* >(uevent)->get_value(); }
        }
        _sum = new DiscreteElementaryEvent(value);
        return _sum;
    }

    double MultinomialSplittingDistributionEstimation::Estimator::SumData::Generator::weight() const
    { return _generator->weight(); }
    
    UnivariateConditionalDistributionEstimation::~UnivariateConditionalDistributionEstimation()
    {}
}
