/**********************************************************************************/
/*                                                                                */
/* StatisKit-CoreThis software is distributed under the CeCILL-C license. You     */
/* should have received a copy of the legalcode along with this work. If not, see */
/* <http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html>.                 */
/*                                                                                */
/**********************************************************************************/

#include "distribution.h"
#include "base.h"

namespace statiskit
{
    double UnivariateDistribution::loglikelihood(const UnivariateData& data) const
    {
        double llh = 0.;
        std::unique_ptr< UnivariateData::Generator > generator = data.generator();
        while(generator->is_valid() && boost::math::isfinite(llh))
        { 
            llh += generator->weight() * probability(generator->event(), true);
            ++(*generator);
        }
        return llh;
    }

    double CategoricalUnivariateDistribution::probability(const UnivariateEvent* event, const bool& logarithm) const
    {
        double p;
        if(event)
        {
            if(event->get_outcome() == CATEGORICAL)
            {
                switch(event->get_event())
                {
                    case ELEMENTARY:
                        {
                            const std::string& value = static_cast< const CategoricalElementaryEvent* >(event)->get_value();
                            if(logarithm)
                            { p = ldf(value); }
                            else
                            { p = pdf(value); }
                        }
                        break;
                    case CENSORED:
                        {
                            const std::vector< std::string >& values = static_cast< const CategoricalCensoredEvent* >(event)->get_values();
                            p = 0.;
                            for(std::vector< std::string >::const_iterator it = values.cbegin(), it_end = values.cend(); it != it_end; ++it)
                            { p += pdf(*it); }
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    default:
                        if(logarithm)
                        { p = -1 * std::numeric_limits< double >::infinity(); }
                        else
                        { p = 0; }
                        break;
                }
            }
            else if(logarithm)
            { p = -1 * std::numeric_limits< double >::infinity(); }
            else
            { p = 0; }
        }
        else if(logarithm)
        { p = 0; }
        else
        { p = 1.; }
        return p;
    }

    NominalDistribution::NominalDistribution(const std::set< std::string >& values)
    { init(values); }

    NominalDistribution::NominalDistribution(const std::set< std::string >& values, const Eigen::VectorXd& pi)
    { init(values, pi); }

    NominalDistribution::NominalDistribution(const NominalDistribution& nominal)
    { init(nominal); }

    double NominalDistribution::pdf(const int& position) const
    {  return _pi[position]; }
   
    OrdinalDistribution::OrdinalDistribution(const std::vector< std::string >& values)
    {
        init(std::set< std::string >(values.cbegin(), values.cend()));
        _rank = std::vector< Index >(_values.size());
        for(Index size = 0, max_size = _values.size(); size < max_size; ++size)
        { _rank[distance(_values.begin(), _values.find(values[size]))] = size; }
    }

    OrdinalDistribution::OrdinalDistribution(const std::vector< std::string >& values, const Eigen::VectorXd& pi)
    {
        init(std::set< std::string >(values.cbegin(), values.cend()), pi);
        _rank = std::vector< Index >(_values.size());
        for(Index size = 0, max_size = _values.size(); size < max_size; ++size)
        { _rank[distance(_values.begin(), _values.find(values[size]))] = size; }
    }

    OrdinalDistribution::OrdinalDistribution(const OrdinalDistribution& ordinal)
    {
        init(ordinal);
        _rank = ordinal._rank;
    }

    double OrdinalDistribution::pdf(const std::string& value) const
    {
        double p;
        std::set< std::string >::const_iterator it = _values.find(value);
        if(it == _values.end())
        { p = 0.; }
        else
        { p = _pi[distance(_values.cbegin(), it)]; }
        return p;
     }

    double OrdinalDistribution::pdf(const int& position) const
    { return _pi[_rank[position]]; }
    
    double OrdinalDistribution::cdf(const std::string& value) const
    {
        double p = 0.;
        std::set< std::string >::const_iterator it = _values.find(value);
        if(it != _values.cend())
        {
            for(Index size = 0, max_size = _rank[distance(_values.cbegin(), it)]; size <= max_size; ++size)
            { p += _pi[size]; }
        }
        return p;
    }

    std::string OrdinalDistribution::quantile(const double& p) const
    {
        std::vector< std::string > ordered = get_ordered_values();
        Index size = 0, max_size = ordered.size() - 1;
        double _p = _pi[size];
        while(_p < p && size < max_size)
        {
            ++size;
            _p += _pi[size];
        }
        if(size == max_size)
        { --size; }
        return ordered[size];
    }

    const std::vector< Index >& OrdinalDistribution::get_rank() const
    { return _rank; }

    void OrdinalDistribution::set_rank(const std::vector< Index >& rank)
    {
        if(rank.size() != _values.size())
        { throw size_error("rank", rank.size(), _values.size()); }
        Indices order = Indices();
        for(Index size = 0, max_size = _values.size(); size < max_size; ++size)
        { order.insert(order.end(), size); }
        for(Index size = 0, max_size = _values.size(); size < max_size; ++size)
        {
            if(rank[size] >= _values.size())
            { throw interval_error("rank", rank[size], 0, _values.size(), std::make_pair(false, true)); }
            Indices::iterator it = order.find(rank[size]);
            if(it == order.end())
            { throw duplicated_value_error("rank", rank[size]); }
            order.erase(it);
        }
        _rank = rank;
    }

    std::vector< std::string > OrdinalDistribution::get_ordered_values() const
    {
        std::vector< std::string > order(_values.size());
        for(std::set< std::string >::const_iterator it = _values.cbegin(), it_end = _values.cend(); it != it_end; ++it)
        { order[_rank[distance(_values.cbegin(), it)]] = *it; }
        return order;
    }

    void OrdinalDistribution::set_ordered_values(const std::vector< std::string >& ordered_values)
    {
        std::set< std::string > values(ordered_values.cbegin(), ordered_values.cend());
        if(values != _values)
        { throw parameter_error("ordered_values","must contain the same string as in values parameter"); }
        for(Index j=0; j<ordered_values.size(); ++j)
        { _rank[distance(_values.cbegin(), _values.find(ordered_values[j]) ) ] = j; }
    }

    Eigen::VectorXd OrdinalDistribution::get_ordered_pi() const
    {
        Eigen::VectorXd ordered_pi(_pi.rows());
        for(std::set< std::string >::const_iterator it = _values.cbegin(), it_end = _values.cend(); it != it_end; ++it)
        { ordered_pi[_rank[distance(_values.cbegin(), it)]] = pdf(*it); }
        return ordered_pi;  
    }

    void OrdinalDistribution::set_ordered_pi(const Eigen::VectorXd& ordered_pi)
    {
        Eigen::VectorXd _ordered_pi(_pi.rows());
        if(ordered_pi.rows() == _values.size() - 1)
        {
            Index j = 0; 
            while(j < ordered_pi.rows() && ordered_pi[j] >= 0.)
            { ++j; }
            if(j < ordered_pi.rows())
            { throw parameter_error("ordered_pi", "contains negative values"); } 
            double sum = ordered_pi.sum();
            if(sum < 1)
            {
                _ordered_pi.segment(0, _values.size() - 1) = ordered_pi;
                _ordered_pi[_values.size()-1] = 1 - sum;
            }
            else
            { throw parameter_error("ordered_pi", "last category values"); }                
        }
        else if(ordered_pi.rows() == _values.size())
        {
            Index j = 0; 
            while(j < ordered_pi.rows() && ordered_pi[j] >= 0.)
            { ++j; }
            if(j < ordered_pi.rows())
            { throw parameter_error("ordered_pi", "contains negative values"); } 
            _ordered_pi = ordered_pi / ordered_pi.sum();
        }
        else
        { throw parameter_error("ordered_pi", "number of parameters"); }  

        for(Index j=0; j<_pi.size(); ++j)
        { _pi[j] = _ordered_pi[_rank[j]]; }
    }

    double DiscreteUnivariateDistribution::probability(const UnivariateEvent* event, const bool& logarithm) const
    {
        double p;
        if(event)
        {
            if(event->get_outcome() == DISCRETE)
            {
                switch(event->get_event())
                {
                    case ELEMENTARY:
                        {
                            const int& value = static_cast< const DiscreteElementaryEvent* >(event)->get_value();
                            if(logarithm)
                            { p = ldf(value); }
                            else
                            { p = pdf(value); }
                        }
                        break;
                    case CENSORED:
                        {
                            const std::vector< int >& values = static_cast< const DiscreteCensoredEvent* >(event)->get_values();
                            p = 0.;
                            for(std::vector< int >::const_iterator it = values.cbegin(), it_end = values.cend(); it != it_end; ++it)
                            { p += pdf(*it); }
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    case LEFT:
                        {
                            const int& upper_bound = static_cast< const DiscreteLeftCensoredEvent* >(event)->get_upper_bound();
                            p = cdf(upper_bound);
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    case RIGHT:
                        {
                            const int& lower_bound = static_cast< const DiscreteRightCensoredEvent* >(event)->get_lower_bound();
                            p = 1 - cdf(lower_bound - 1);
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    case INTERVAL:
                        {
                            const DiscreteIntervalCensoredEvent* devent = static_cast< const DiscreteIntervalCensoredEvent* >(event);
                            const int& lower_bound = devent->get_lower_bound(), upper_bound = devent->get_lower_bound();
                            p = cdf(upper_bound) - cdf(lower_bound - 1);
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    default:
                        if(logarithm)
                        { p = -1 * std::numeric_limits< double >::infinity(); }
                        else
                        { p = 0; }
                        break;
                }
            }
            else if(logarithm)
            { p = -1 * std::numeric_limits< double >::infinity(); }
            else
            { p = 0; }
        }
        else if(logarithm)
        { p = 0; }
        else
        { p = 1.; }
        return p;
    }

    PoissonDistribution::PoissonDistribution()
    { _theta = 1.; }

    PoissonDistribution::PoissonDistribution(const double& theta)
    {
        if(theta <= 0.)
        { throw lower_bound_error("theta", theta, 0., true); }
        _theta = theta;
    }

    PoissonDistribution::PoissonDistribution(const PoissonDistribution& poisson)
    { _theta = poisson._theta; }

    unsigned int PoissonDistribution::get_nb_parameters() const
    { return 1; }

    const double& PoissonDistribution::get_theta() const
    { return _theta; }

    void PoissonDistribution::set_theta(const double& theta)
    {
        if(theta <= 0.)
        { throw lower_bound_error("theta", theta, 0., true); }
        _theta = theta;
    }

    double PoissonDistribution::ldf(const int& value) const
    {
        double p;
        if(value < 0)
        { p = -1 * std::numeric_limits< double >::infinity(); }
        else
        { p = value * log(_theta) - _theta - boost::math::lgamma(value + 1); }
        return p;
    }
    
    double PoissonDistribution::pdf(const int& value) const
    {
        double p;
        if(value < 0)
        { p = 0; }
        else
        { p = pow(_theta, value) * exp(-_theta) / boost::math::tgamma(value + 1); }
        return p;
    }

    double PoissonDistribution::cdf(const int& value) const
    { 
        double p;
        if(value < 0)
        { p = 0; }
        else
        { p = boost::math::gamma_q(value + 1, _theta); }
        return p;
    }

    int PoissonDistribution::quantile(const double& p) const
    { return std::ceil(boost::math::gamma_q_inva(_theta, p) - 1); }

    double PoissonDistribution::get_mean() const
    { return _theta; }

    double PoissonDistribution::get_variance() const
    { return _theta; }

    std::unique_ptr< UnivariateEvent > PoissonDistribution::simulate() const
    {
        boost::poisson_distribution<> dist(_theta);
        boost::variate_generator<boost::mt19937&, boost::poisson_distribution<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< DiscreteElementaryEvent >(simulator());
    }

    BinomialDistribution::BinomialDistribution()
    {
        _kappa = 1;
        _pi = .5;
    }

    BinomialDistribution::BinomialDistribution(const unsigned int& kappa, const double& pi)
    {
        if(pi < 0 || pi > 1)
        { throw interval_error("pi", pi, 0., 1., std::make_pair(false, false)); }
        _kappa = kappa;
        _pi = pi;
    }

    BinomialDistribution::BinomialDistribution(const BinomialDistribution& binomial)
    {
        _kappa = binomial._kappa;
        _pi = binomial._pi;
    }

    unsigned int BinomialDistribution::get_nb_parameters() const
    { return 2; }

    const unsigned int& BinomialDistribution::get_kappa() const
    { return _kappa; }

    void BinomialDistribution::set_kappa(const unsigned int& kappa)
    { _kappa = kappa; }

    const double& BinomialDistribution::get_pi() const
    { return _pi; }

    void BinomialDistribution::set_pi(const double& pi)
    {
        if(pi < 0 || pi > 1)
        { throw interval_error("pi", pi, 0., 1., std::make_pair(false, false)); }
        _pi = pi;
    }

    double BinomialDistribution::ldf(const int& value) const
    {
        double p;
        if(value < 0 || value > _kappa)
        { p = -1 * std::numeric_limits< double >::infinity(); }
        else if(value == 0)
        { p = _kappa * log(1. - _pi); }
        else if(value == _kappa)
        {  p =  value * log(_pi); }
        else
        { p = boost::math::lgamma(_kappa + 1) - boost::math::lgamma(_kappa - value + 1) - boost::math::lgamma(value + 1) + value * log(_pi) + (_kappa - value) * log(1. - _pi); }
        return p;
    }
    
    double BinomialDistribution::pdf(const int& value) const
    {
        double p;
        if(value < 0 || value > _kappa)
        { p = 0; }
        else if(value == 0)
        { p = pow(1 - _pi, _kappa); }
        else if(value == _kappa)
        { p = pow(_pi, _kappa); }
        else
        { p = boost::math::ibeta_derivative(value + 1, _kappa - value + 1, _pi) / (_kappa + 1); }
        return p;
    }

    double BinomialDistribution::cdf(const int& value) const
    {
        double p;
        if(value < 0)
        { p = 0.; }
        else if(value > _kappa)
        { p = 1.; }
        else
        { p = boost::math::ibetac(value + 1, _kappa - value, _pi); }
        return p;
      }

    int BinomialDistribution::quantile(const double& p) const
    { 
        int value = 0;
        while(cdf(value) < p && value < _kappa)
        { ++value; }
        return value;
    }

    std::unique_ptr< UnivariateEvent > BinomialDistribution::simulate() const
    {
        boost::binomial_distribution<> dist(_kappa, _pi);
        boost::variate_generator<boost::mt19937&, boost::binomial_distribution<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< DiscreteElementaryEvent >(simulator());
    }

    double BinomialDistribution::get_mean() const
    { return _kappa * _pi; }

    double BinomialDistribution::get_variance() const
    { return _kappa * _pi * (1. - _pi); }

    NegativeBinomialDistribution::NegativeBinomialDistribution()
    {
        _kappa = 1.;
        _pi = .5;
    }

    NegativeBinomialDistribution::NegativeBinomialDistribution(const double& kappa, const double& pi)
    {
        if(kappa <= 0.)
        { throw lower_bound_error("kappa", kappa, 0., true); }
        if(pi < 0 || pi > 1)
        { throw interval_error("pi", pi, 0., 1., std::make_pair(false, false)); }
        _kappa = kappa;
        _pi = pi;
    }

    NegativeBinomialDistribution::NegativeBinomialDistribution(const NegativeBinomialDistribution& negbinomial)
    {
        _kappa = negbinomial._kappa;
        _pi = negbinomial._pi;
    }

    unsigned int NegativeBinomialDistribution::get_nb_parameters() const
    { return 2; }

    const double& NegativeBinomialDistribution::get_kappa() const
    { return _kappa; }

    void NegativeBinomialDistribution::set_kappa(const double& kappa)
    {
        if(kappa <= 0.)
        { throw lower_bound_error("kappa", kappa, 0., true); }
        _kappa = kappa;
    }

    const double& NegativeBinomialDistribution::get_pi() const
    { return _pi; }

    void NegativeBinomialDistribution::set_pi(const double& pi)
    {
        if(pi < 0 || pi > 1)
        { throw interval_error("pi", pi, 0., 1., std::make_pair(false, false)); }
        _pi = pi;
    }

    double NegativeBinomialDistribution::ldf(const int& value) const
    {
        double p;
        if(value < 0)
        { p = -1 * std::numeric_limits< double >::infinity(); }
        else
        { p = boost::math::lgamma(value + _kappa) - boost::math::lgamma(_kappa) - boost::math::lgamma(value + 1) + value * log(_pi) + _kappa * log(1 - _pi); }
        return p;
    }
    
    double NegativeBinomialDistribution::pdf(const int& value) const
    {
        double p;
        if(value < 0)
        { p = 0; }
        else
        { p = boost::math::ibeta_derivative(_kappa, value + 1., 1 - _pi) * (1. - _pi) / (_kappa + value); }
        return p;
    }

    double NegativeBinomialDistribution::cdf(const int& value) const
    { return boost::math::ibeta(_kappa, value + 1., 1. - _pi); }

    int NegativeBinomialDistribution::quantile(const double& p) const
    { return std::ceil(boost::math::ibeta_invb(_kappa, 1. - _pi, p) - 1); }

    double NegativeBinomialDistribution::get_mean() const
    { return _kappa * _pi / (1 - _pi); }

    double NegativeBinomialDistribution::get_variance() const
    { return _kappa * _pi / pow(1. - _pi, 2); }

    std::unique_ptr< UnivariateEvent > NegativeBinomialDistribution::simulate() const
    { return std::make_unique< ElementaryEvent< DiscreteEvent > >(quantile(boost::uniform_01<boost::mt19937&>(__impl::get_random_generator())())); }

    double ContinuousUnivariateDistribution::probability(const UnivariateEvent* event, const bool& logarithm) const
    {
        double p;
        if(event)
        {
            if(event->get_outcome() == CONTINUOUS)
            {
                switch(event->get_event())
                {
                    case ELEMENTARY:
                        {
                            const double& value = static_cast< const ContinuousElementaryEvent* >(event)->get_value();
                            if(logarithm)
                            { p = ldf(value); }
                            else
                            { p = pdf(value); }
                        }
                        break;
                    case CENSORED:
                        {
                            const std::vector< double >& values = static_cast< const ContinuousCensoredEvent* >(event)->get_values();
                            p = 0.;
                            for(std::vector< double >::const_iterator it = values.cbegin(), it_end = values.cend(); it != it_end; ++it)
                            { p += pdf(*it); }
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    case LEFT:
                        {
                            const double& upper_bound = static_cast< const ContinuousLeftCensoredEvent* >(event)->get_upper_bound();
                            p = cdf(upper_bound);
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    case RIGHT:
                        {
                            const double& lower_bound = static_cast< const ContinuousRightCensoredEvent* >(event)->get_lower_bound();
                            p = 1 - cdf(lower_bound);
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    case INTERVAL:
                        {
                            const ContinuousIntervalCensoredEvent* cevent = static_cast< const ContinuousIntervalCensoredEvent* >(event);
                            const double& lower_bound = cevent->get_lower_bound(), upper_bound = cevent->get_lower_bound();
                            p = cdf(upper_bound) - cdf(lower_bound);
                            if(logarithm)
                            { p = log(p); }
                        }
                        break;
                    default:
                        if(logarithm)
                        { p = -1 * std::numeric_limits< double >::infinity(); }
                        else
                        { p = 0; }
                        break;
                }
            }
            else if(logarithm)
            { p = -1 * std::numeric_limits< double >::infinity(); }
            else
            { p = 0; }
        }
        else if(logarithm)
        { p = 0; }
        else
        { p = 1.; }
        return p;
    }

    NormalDistribution::NormalDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
    }

    NormalDistribution::NormalDistribution(const double& mu, const double& sigma) 
    {
        _mu = mu;
        _sigma = sigma;
    }

    NormalDistribution::NormalDistribution(const NormalDistribution& normal)
    {
        _mu = normal._mu;
        _sigma = normal._sigma;
    }

    unsigned int NormalDistribution::get_nb_parameters() const
    { return 2; }

    const double& NormalDistribution::get_mu() const
    { return _mu; }

    void NormalDistribution::set_mu(const double& mu)
    { 
        throw parameter_error("mu", "always");
        _mu = mu;
    }

    const double& NormalDistribution::get_sigma() const
    { return _sigma; }

    void NormalDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }

    double NormalDistribution::ldf(const double& value) const
    { return -pow((value - _mu) / _sigma, 2) / 2. - log(_sigma)  - log(boost::math::constants::root_two_pi<double>()); }

    double NormalDistribution::pdf(const double& value) const
    { return exp(ldf(value)); }

    double NormalDistribution::cdf(const double& value) const
    { return 0.5 * erfc( (_mu - value) / (_sigma * boost::math::constants::root_two<double>()  )); }

    double NormalDistribution::quantile(const double& p) const
    { return _mu - _sigma * boost::math::constants::root_two<double>() * boost::math::erfc_inv(2 * p); }

    std::unique_ptr< UnivariateEvent > NormalDistribution::simulate() const
    {
        boost::normal_distribution<> dist(_mu, _sigma);
        boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(simulator());
    }

    double NormalDistribution::get_mean() const
    { return _mu; }

    double NormalDistribution::get_variance() const
    { return pow(_sigma, 2); }

    UnivariateHistogramDistribution::UnivariateHistogramDistribution(const std::set<double>& bins, const std::vector<double>& densities)
    {
        assert(bins.size() > 1);
        assert(bins.size() == densities.size()+1);
        _bins = bins;
        _densities = densities;
        normalize();
    }

    UnivariateHistogramDistribution::UnivariateHistogramDistribution(const UnivariateHistogramDistribution& histogram)
    {
        _bins = histogram._bins;
        _densities = histogram._densities;
    }

    UnivariateHistogramDistribution::~UnivariateHistogramDistribution()
    {}

    unsigned int UnivariateHistogramDistribution::get_nb_parameters() const
    { return _densities.size(); }

    const std::set<double>& UnivariateHistogramDistribution::get_bins() const
    { return _bins; }

    const std::vector<double>& UnivariateHistogramDistribution::get_densities() const
    { return _densities; }

    /*double UnivariateHistogramDistribution::get_bin(const event_type& event) const
    { 
        double bin;
        if(boost::get<double>(event) < *(bins.begin()))
        { bin = -1*INFINITY; }
        else if(boost::get<double>(event) > *(bins.rbegin()))
        { bin = INFINITY ; }
        else
        {
            std::set<double>::const_iterator it = bins.upper_bound(boost::get<double>(event));
            if(it == bins.end())
            { --it; }
            --it;
            bin = *it;
        }
        return bin;
    }*/

    double UnivariateHistogramDistribution::ldf(const double& value) const
    { return log(pdf(value)); }

    double UnivariateHistogramDistribution::pdf(const double& value) const
    {
        double p;
        if(value > *(_bins.rbegin()) || value < *(_bins.begin()))
        { p = 0; }
        else
        {
            std::set<double>::const_iterator it = _bins.upper_bound(value);
            if(it == _bins.end())
            { p = _densities.back(); }
            else
            {
                --it;
                p = _densities[distance(_bins.begin(), it)];
            }
        }
        return p;
    }

    double UnivariateHistogramDistribution::cdf(const double& value) const
    {
        double cp;
        if(value <= (*_bins.begin()))
        { cp = 0.; }
        else
        {
            cp = 0.;
            std::set<double>::const_iterator it = _bins.upper_bound(value);
            std::set<double>::const_iterator itl = _bins.begin(), itu;
            itu = itl;
            ++itu;
            while(itu != it)
            {
                cp += _densities[distance(_bins.begin(), itl)] * (*itu - *itl);
                ++itl;
                ++itu;
            }
            cp += (value - *itl) * _densities[distance(_bins.begin(), itl)];
        }
        return std::min(cp, 1.);
    }

    double UnivariateHistogramDistribution::quantile(const double& p) const
    {
        double q;
        if(p >= 1.)
        { q = *(_bins.rbegin()); }
        else if (p <= 0.)
        { q = *(_bins.begin()); }
        else
        {
            std::set<double>::const_iterator itl = _bins.begin(), itu;
            itu = itl;
            ++itu;
            double cum = 0;
            while(distance(_bins.begin(), itl) < _densities.size() && cum < p)
            {
                cum += _densities[distance(_bins.begin(), itl)] * (*itu - *itl);
                if(cum < p)
                {
                    ++itl;
                    ++itu;
                }
            }
            if(distance(_bins.begin(), itl) == _densities.size())
            { q = (*_bins.rbegin()); }
            else
            {
                cum -= _densities[distance(_bins.begin(), itl)] * (*itu - *itl);
                q = *itl + (p - cum) / _densities[distance(_bins.begin(), itl)];
            }
        }
        return q;
    }

    std::unique_ptr< UnivariateEvent > UnivariateHistogramDistribution::simulate() const
    { return std::make_unique< ContinuousElementaryEvent >(quantile(boost::uniform_01<boost::mt19937&>(__impl::get_random_generator())())); }

    double UnivariateHistogramDistribution::get_mean() const
    {
        double mean = 0.;
        std::set<double>::const_iterator itl = _bins.begin(), itu;
        itu = itl;
        ++itl;
        while(itu != _bins.end())
        {
            mean += (*itl + (*itu - *itl) / 2.) * _densities[distance(_bins.begin(), itl)];
            ++itl;
            ++itu;
        }
        return mean;
    }

    double UnivariateHistogramDistribution::get_variance() const
    {
        double mean = get_mean(), variance = 0.;
        std::set<double>::const_iterator itl = _bins.begin(), itu;
        itu = itl;
        ++itl;
        while(itu != _bins.end())
        {
            variance += pow((*itl + (*itu - *itl) / 2.) - mean, 2) * _densities[distance(_bins.begin(), itl)];
            ++itl;
            ++itu;
        }
        return variance;
    }

    void UnivariateHistogramDistribution::normalize()
    {
        double sum = 0.;
        std::set<double>::const_iterator itl = _bins.begin(), itu;
        itu = itl;
        ++itu;
        while(itu != _bins.end())
        { 
            sum += (*itu - *itl) * _densities[distance(_bins.begin(), itl)];
            ++itl;
            ++itu;
        }
        if(sum != 1.)
        { 
            for(unsigned int i = 0; i < _densities.size(); ++i)
            { _densities[i] /= sum; }
        }
    }

    LogisticDistribution::LogisticDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
    }

    LogisticDistribution::LogisticDistribution(const double& mu, const double& sigma) 
    {
        _mu = mu;
        _sigma = sigma;
    }

    LogisticDistribution::LogisticDistribution(const LogisticDistribution& logistic)
    {
        _mu = logistic._mu;
        _sigma = logistic._sigma;
    }

    unsigned int LogisticDistribution::get_nb_parameters() const
    { return 2; }

    const double& LogisticDistribution::get_mu() const
    { return _mu; }

    void LogisticDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& LogisticDistribution::get_sigma() const
    { return _sigma; }

    void LogisticDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }

    double LogisticDistribution::ldf(const double& value) const
    { return -2*log(cosh(0.5 * (value - _mu) / _sigma)) - log(4 * _sigma); }//(_mu-value)/_sigma - log(sigma) - 2*log(1+exp((_mu-value)/_sigma )); }

    double LogisticDistribution::pdf(const double& value) const
    { return  1/ (4. * _sigma * pow(cosh(0.5 * (value - _mu) / _sigma), 2) ); }

    double LogisticDistribution::cdf(const double& value) const
    { return 0.5 * (1 + tanh(0.5 * (value - _mu) / _sigma)); }

    double LogisticDistribution::quantile(const double& p) const
    { return _mu + _sigma * log(p / (1 - p)); }

    std::unique_ptr< UnivariateEvent > LogisticDistribution::simulate() const
    {       
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double LogisticDistribution::get_mean() const
    { return _mu; }

    double LogisticDistribution::get_variance() const
    { return pow(_sigma * boost::math::constants::pi<double>() , 2) / 3.; }
    
    
    LaplaceDistribution::LaplaceDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
    }

    LaplaceDistribution::LaplaceDistribution(const double& mu, const double& sigma) 
    {
        _mu = mu;
        _sigma = sigma;
    }

    LaplaceDistribution::LaplaceDistribution(const LaplaceDistribution& laplace)
    {
        _mu = laplace._mu;
        _sigma = laplace._sigma;
    }

    unsigned int LaplaceDistribution::get_nb_parameters() const
    { return 2; }

    const double& LaplaceDistribution::get_mu() const
    { return _mu; }

    void LaplaceDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& LaplaceDistribution::get_sigma() const
    { return _sigma; }

    void LaplaceDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }

    double LaplaceDistribution::ldf(const double& value) const
    { return abs(_mu - value) / _sigma - log(2*_sigma); }
    
    double LaplaceDistribution::pdf(const double& value) const
    { return  0.5 * exp( abs(_mu - value) / _sigma) / _sigma; }

    double LaplaceDistribution::cdf(const double& value) const
    {
    	if (value < _mu)
    	{ return 0.5 * exp( (value - _mu) / _sigma); } 
    	else
    	{ return 1 - 0.5 * exp( (_mu - value) / _sigma); }
    }

    double LaplaceDistribution::quantile(const double& p) const
    {
    	if (p < 0.5)
    	{ return _mu + _sigma * log(2*p); } 
    	else
    	{ return _mu - _sigma * log(2-2*p); }
    }

    std::unique_ptr< UnivariateEvent > LaplaceDistribution::simulate() const
    {        
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double LaplaceDistribution::get_mean() const
    { return _mu; }

    double LaplaceDistribution::get_variance() const
    { return 2 * pow(_sigma, 2); }
    
    CauchyDistribution::CauchyDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
    }

    CauchyDistribution::CauchyDistribution(const double& mu, const double& sigma) 
    {
        _mu = mu;
        _sigma = sigma;
    }

    CauchyDistribution::CauchyDistribution(const CauchyDistribution& cauchy)
    {
        _mu = cauchy._mu;
        _sigma = cauchy._sigma;
    }

    unsigned int CauchyDistribution::get_nb_parameters() const
    { return 2; }

    const double& CauchyDistribution::get_mu() const
    { return _mu; }

    void CauchyDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& CauchyDistribution::get_sigma() const
    { return _sigma; }

    void CauchyDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }

    double CauchyDistribution::ldf(const double& value) const
    { return - log( boost::math::constants::pi<double>() *_sigma) - log( 1 +  pow( (value - _mu)/_sigma, 2) ); }
    
    double CauchyDistribution::pdf(const double& value) const
    { return  1/(boost::math::constants::pi<double>() *_sigma * (1 +  pow( (value - _mu)/_sigma, 2) ) ) ; }

    double CauchyDistribution::cdf(const double& value) const
    { return 0.5 + atan((value - _mu)/_sigma)/boost::math::constants::pi<double>() ; }

    double CauchyDistribution::quantile(const double& p) const
    { return _mu + _sigma * tan(boost::math::constants::pi<double>() * (p-0.5) ); }

    std::unique_ptr< UnivariateEvent > CauchyDistribution::simulate() const
    {        
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double CauchyDistribution::get_mean() const
    { return std::numeric_limits< double >::quiet_NaN(); }

    double CauchyDistribution::get_variance() const
    { return std::numeric_limits< double >::quiet_NaN(); }

    NonStandardStudentDistribution::NonStandardStudentDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
        _nu = 1.;
    }

    NonStandardStudentDistribution::NonStandardStudentDistribution(const double& mu, const double& sigma, const double& nu) 
    {
        _mu = mu;
        _sigma = sigma;
        _nu = nu;
    }

    NonStandardStudentDistribution::NonStandardStudentDistribution(const NonStandardStudentDistribution& nsstudent)
    {
        _mu = nsstudent._mu;
        _sigma = nsstudent._sigma;
        _nu = nsstudent._nu;
    }

    unsigned int NonStandardStudentDistribution::get_nb_parameters() const
    { return 3; }

    const double& NonStandardStudentDistribution::get_mu() const
    { return _mu; }

    void NonStandardStudentDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& NonStandardStudentDistribution::get_sigma() const
    { return _sigma; }

    void NonStandardStudentDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }
    
    const double& NonStandardStudentDistribution::get_nu() const
    { return _nu; }

    void NonStandardStudentDistribution::set_nu(const double& nu)
    {
        if(nu <= 0.)
        { throw lower_bound_error("nu", nu, 0., true); }
        _nu = nu;
    }    

    double NonStandardStudentDistribution::ldf(const double& value) const
    { return (1+_nu) * 0.5 * ( log(_nu) - log(_nu + pow((value-_mu)/_sigma, 2) )  ) - 0.5*log(_nu) - log(_sigma) - log(boost::math::beta(_nu*0.5, 0.5) ); }
    
    double NonStandardStudentDistribution::pdf(const double& value) const
    { return pow( _nu/(_nu + pow((value-_mu)/_sigma, 2)) , (1+_nu) * 0.5 ) / ( pow(_nu,0.5) * _sigma * boost::math::beta(_nu*0.5, 0.5) ); }

    double NonStandardStudentDistribution::cdf(const double& value) const
    {
    	double z;
    	if(_nu < 2*(value-_mu)/_sigma)
    	{ z = boost::math::ibeta(_nu*0.5, 0.5, _nu/(_nu+pow((value-_mu)/_sigma, 2) ) ) * 0.5; }
    	else
    	{ z = boost::math::ibetac(0.5, _nu*0.5, pow((value-_mu)/_sigma, 2)/(_nu+pow((value-_mu)/_sigma, 2) ) ) * 0.5; }
    	if(value>_mu)
    	{ return 1-z; }
    	else
    	{return z; }
    }

    double NonStandardStudentDistribution::quantile(const double& p) const
    { 
    	if(p<0.5)
    	{ return _mu - _sigma * ( _nu * ( 1-boost::math::ibeta_invb(_nu*0.5, 0.5, 2*p) )/boost::math::ibeta_invb(_nu*0.5, 0.5, 2*p) ) ; }
    	else if(p>0.5)
    	{ return _mu; }
    	else
    	{ return _mu + _sigma * ( _nu * ( 1-boost::math::ibeta_invb(_nu*0.5, 0.5, 2-2*p) )/boost::math::ibeta_invb(_nu*0.5, 0.5, 2-2*p) ); }   	 
    }

    std::unique_ptr< UnivariateEvent > NonStandardStudentDistribution::simulate() const
    {        
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double NonStandardStudentDistribution::get_mean() const
    {
    	if(_nu>1.)
    	{ return _mu; }
    	else
    	{ return std::numeric_limits< double >::quiet_NaN(); }
    }

    double NonStandardStudentDistribution::get_variance() const
    {
    	if(_nu>2.)
    	{ return _nu/(_nu-2.); }
    	else if(_nu>1.)
    	{ return std::numeric_limits< double >::infinity(); } 
    	else
    	{ return std::numeric_limits< double >::quiet_NaN(); }
    }

    GeneralizedStudentDistribution::GeneralizedStudentDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
        _nu = 1.;
        _delta = 0.;
    }

    GeneralizedStudentDistribution::GeneralizedStudentDistribution(const double& mu, const double& sigma, const double& nu, const double& delta) 
    {
        _mu = mu;
        _sigma = sigma;
        _nu = nu;
        _delta = delta;
    }

    GeneralizedStudentDistribution::GeneralizedStudentDistribution(const GeneralizedStudentDistribution& gstudent)
    {
        _mu = gstudent._mu;
        _sigma = gstudent._sigma;
        _nu = gstudent._nu;
        _delta = gstudent._delta;
    }

    unsigned int GeneralizedStudentDistribution::get_nb_parameters() const
    { return 4; }

    const double& GeneralizedStudentDistribution::get_mu() const
    { return _mu; }

    void GeneralizedStudentDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& GeneralizedStudentDistribution::get_sigma() const
    { return _sigma; }

    void GeneralizedStudentDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }
    
    const double& GeneralizedStudentDistribution::get_nu() const
    { return _nu; }

    void GeneralizedStudentDistribution::set_nu(const double& nu)
    {
        if(nu <= 0.)
        { throw lower_bound_error("nu", nu, 0., true); }
        _nu = nu;
    }    

    const double& GeneralizedStudentDistribution::get_delta() const
    { return _delta; }

    void GeneralizedStudentDistribution::set_delta(const double& delta)
    { _delta = delta; }
    
    double GeneralizedStudentDistribution::ldf(const double& value) const
    { return (1+_nu) * 0.5 * ( log(_nu) - log(_nu + pow((value-_mu)/_sigma, 2) )  ) - 0.5*log(_nu) - log(_sigma) - log(boost::math::beta(_nu*0.5, 0.5) ); }
    
    double GeneralizedStudentDistribution::pdf(const double& value) const
    { return pow( _nu/(_nu + pow((value-_mu)/_sigma, 2)) , (1+_nu) * 0.5 ) / ( pow(_nu,0.5) * _sigma * boost::math::beta(_nu*0.5, 0.5) ); }

    double GeneralizedStudentDistribution::cdf(const double& value) const
    {
    	double z;
    	if(_nu < 2*(value-_mu)/_sigma)
    	{ z = boost::math::ibeta(_nu*0.5, 0.5, _nu/(_nu+pow((value-_mu)/_sigma, 2) ) ) * 0.5; }
    	else
    	{ z = boost::math::ibetac(0.5, _nu*0.5, pow((value-_mu)/_sigma, 2)/(_nu+pow((value-_mu)/_sigma, 2) ) ) * 0.5; }
    	if(value>_mu)
    	{ return 1-z; }
    	else
    	{return z; }
    }

    double GeneralizedStudentDistribution::quantile(const double& p) const
    { 
    	if(p<0.5)
    	{ return _mu - _sigma * ( _nu * ( 1-boost::math::ibeta_invb(_nu*0.5, 0.5, 2*p) )/boost::math::ibeta_invb(_nu*0.5, 0.5, 2*p) ) ; }
    	else if(p>0.5)
    	{ return _mu; }
    	else
    	{ return _mu + _sigma * ( _nu * ( 1-boost::math::ibeta_invb(_nu*0.5, 0.5, 2-2*p) )/boost::math::ibeta_invb(_nu*0.5, 0.5, 2-2*p) ); }   	 
    }

    std::unique_ptr< UnivariateEvent > GeneralizedStudentDistribution::simulate() const
    {        
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double GeneralizedStudentDistribution::get_mean() const
    {
    	if(_nu>1.)
    	{ return _mu; }
    	else
    	{ return std::numeric_limits< double >::quiet_NaN(); }
    }

    double GeneralizedStudentDistribution::get_variance() const
    {
    	if(_nu>2.)
    	{ return _nu/(_nu-2.); }
    	else if(_nu>1.)
    	{ return std::numeric_limits< double >::infinity(); } 
    	else
    	{ return std::numeric_limits< double >::quiet_NaN(); }
    }

    GumbelMaxDistribution::GumbelMaxDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
    }

    GumbelMaxDistribution::GumbelMaxDistribution(const double& mu, const double& sigma) 
    {
        _mu = mu;
        _sigma = sigma;
    }

    GumbelMaxDistribution::GumbelMaxDistribution(const GumbelMaxDistribution& gumbel_max)
    {
        _mu = gumbel_max._mu;
        _sigma = gumbel_max._sigma;
    }

    unsigned int GumbelMaxDistribution::get_nb_parameters() const
    { return 2; }

    const double& GumbelMaxDistribution::get_mu() const
    { return _mu; }

    void GumbelMaxDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& GumbelMaxDistribution::get_sigma() const
    { return _sigma; }

    void GumbelMaxDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }

    double GumbelMaxDistribution::ldf(const double& value) const
    { return (_mu - value) / _sigma - exp((_mu - value) / _sigma) - log(_sigma); }
    
    double GumbelMaxDistribution::pdf(const double& value) const
    { return exp( (_mu - value) / _sigma - exp((_mu - value) / _sigma) ) / _sigma ; }

    double GumbelMaxDistribution::cdf(const double& value) const
    { return  exp( - exp((_mu - value) / _sigma) ); }

    double GumbelMaxDistribution::quantile(const double& p) const
    { return _mu - _sigma * log( -log(p) ); }

    std::unique_ptr< UnivariateEvent > GumbelMaxDistribution::simulate() const
    {        
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double GumbelMaxDistribution::get_mean() const
    { return _mu + _sigma * boost::math::constants::euler<double>(); }

    double GumbelMaxDistribution::get_variance() const
    { return pow(_sigma *  boost::math::constants::pi<double>(), 2) / 6.; }
    
    GumbelMinDistribution::GumbelMinDistribution() 
    {
        _mu = 0.;
        _sigma = 1.;
    }

    GumbelMinDistribution::GumbelMinDistribution(const double& mu, const double& sigma) 
    {
        _mu = mu;
        _sigma = sigma;
    }

    GumbelMinDistribution::GumbelMinDistribution(const GumbelMinDistribution& gumbel_min)
    {
        _mu = gumbel_min._mu;
        _sigma = gumbel_min._sigma;
    }

    unsigned int GumbelMinDistribution::get_nb_parameters() const
    { return 2; }

    const double& GumbelMinDistribution::get_mu() const
    { return _mu; }

    void GumbelMinDistribution::set_mu(const double& mu)
    { _mu = mu; }

    const double& GumbelMinDistribution::get_sigma() const
    { return _sigma; }

    void GumbelMinDistribution::set_sigma(const double& sigma)
    {
        if(sigma <= 0.)
        { throw lower_bound_error("sigma", sigma, 0., true); }
        _sigma = sigma;
    }

    double GumbelMinDistribution::ldf(const double& value) const
    { return (value - _mu) / _sigma - exp( (value - _mu) / _sigma) - log(_sigma); }
    
    double GumbelMinDistribution::pdf(const double& value) const
    { return exp( (value - _mu)/ _sigma - exp( (value - _mu)/ _sigma) ) / _sigma ; }

    double GumbelMinDistribution::cdf(const double& value) const
    { return  1 - exp( - exp((value - _mu) / _sigma) ); }

    double GumbelMinDistribution::quantile(const double& p) const
    { return _mu + _sigma * log( -log(1-p) ); }

    std::unique_ptr< UnivariateEvent > GumbelMinDistribution::simulate() const
    {        
        boost::uniform_01<> dist;
        boost::variate_generator<boost::mt19937&, boost::uniform_01<> > simulator(__impl::get_random_generator(), dist);
        return std::make_unique< ContinuousElementaryEvent >(quantile(simulator()));
    }

    double GumbelMinDistribution::get_mean() const
    { return - _mu + _sigma * boost::math::constants::euler<double>(); }

    double GumbelMinDistribution::get_variance() const
    { return pow(_sigma *  boost::math::constants::pi<double>(), 2) / 6.; }
     
    double MultivariateDistribution::loglikelihood(const MultivariateData& data) const
    {
        double llh = 0.;
        std::unique_ptr< MultivariateData::Generator > generator = data.generator();
        while(generator->is_valid() && boost::math::isfinite(llh))
        { 
            llh += generator->weight() * probability(generator->event(), true);
            ++(*generator);
        }
        return llh;
    }

    CategoricalUnivariateMixtureDistribution::CategoricalUnivariateMixtureDistribution(const std::vector< CategoricalUnivariateDistribution* > observations, const Eigen::VectorXd& pi)
    { init(observations, pi); }

    CategoricalUnivariateMixtureDistribution::CategoricalUnivariateMixtureDistribution(const CategoricalUnivariateMixtureDistribution& mixture)
    { init(mixture); }

    CategoricalUnivariateMixtureDistribution::~CategoricalUnivariateMixtureDistribution()
    {}

    double CategoricalUnivariateMixtureDistribution::pdf(const int& position) const
    {
        double p = 0.;
        for(Index index = 0, max_index = get_nb_states(); index < max_index; ++index)
        { p += _pi[index] * _observations[index]->pdf(position); }
        return p;        
    }

    std::set< std::string > CategoricalUnivariateMixtureDistribution::get_values() const
    {
        std::set< std::string > values = std::set< std::string >();
        for(Index index = 0, max_index = get_nb_states(); index < max_index; ++index)
        { 
            std::set< std::string > _values = _observations[index]->get_values();
            values.insert(_values.cbegin(), _values.cend());
        }
        return values;
    }

    MultinomialSplittingDistribution::MultinomialSplittingDistribution(const DiscreteUnivariateDistribution& sum, const Eigen::VectorXd& pi)
    {
        // _sum = static_cast< DiscreteUnivariateDistribution* >(sum.copy().release());
        set_sum(sum);
        _pi = Eigen::VectorXd::Ones(pi.size());
        set_pi(pi);
    }

    MultinomialSplittingDistribution::MultinomialSplittingDistribution(const MultinomialSplittingDistribution& multinomial)
    {
        _sum = static_cast< DiscreteUnivariateDistribution* >(multinomial._sum->copy().release());
        _pi = multinomial._pi;
    }

    MultinomialSplittingDistribution::~MultinomialSplittingDistribution()
    { delete _sum; }

    Index MultinomialSplittingDistribution::get_nb_components() const
    { return _pi.size(); }

    unsigned int MultinomialSplittingDistribution::get_nb_parameters() const
    { return _sum->get_nb_parameters() + _pi.size() - 1; }

    double MultinomialSplittingDistribution::probability(const MultivariateEvent* event, const bool& logarithm) const
    {
        double p;
        if(event && event->size() == get_nb_components())
        {
            try
            {
                int kappa = 0;
                for(Index component = 0, max_component = get_nb_components(); component < max_component; ++component)
                {
                    const UnivariateEvent* uevent = event->get(component);
                    if(uevent)
                    {
                        if(uevent->get_outcome() == DISCRETE && uevent->get_event() == ELEMENTARY)
                        { kappa += static_cast< const DiscreteElementaryEvent* >(uevent)->get_value(); }
                        else
                        { throw std::exception(); }
                    }
                }                
                p = 0.;
                double sum = 0.;
                BinomialDistribution binomial = BinomialDistribution(kappa, 0);
                const UnivariateEvent* uevent;
                for(Index component = 0, max_component = get_nb_components() - 1; component < max_component; ++component)
                {
                    uevent = event->get(component);
                    if(uevent)
                    {
                        if(uevent->get_outcome() == DISCRETE && uevent->get_event() == ELEMENTARY)
                        {
                            int value = static_cast< const DiscreteElementaryEvent* >(uevent)->get_value();
                            binomial.set_pi(_pi[component] / (1 - sum));
                            p += binomial.ldf(value);
                            kappa -= value;
                        }
                        else
                        { throw std::exception(); }
                    }
                    sum += _pi[component];
                    binomial.set_kappa(kappa);
                }
                uevent = event->get(get_nb_components() - 1);
                if(uevent->get_outcome() != DISCRETE || uevent->get_event() != ELEMENTARY || static_cast< const DiscreteElementaryEvent* >(uevent)->get_value() != kappa)
                { p = log(0.); }
            }
            catch(const std::exception& error)
            { p = log(0.); }
        }
        else
        { p = log(0.); }
        if(!logarithm)
        { p = exp(p); }
        return p;
    }

    std::unique_ptr< MultivariateEvent > MultinomialSplittingDistribution::simulate() const
    {
        int kappa = static_cast< DiscreteElementaryEvent* >(_sum->simulate().get())->get_value();
        double sum = 0.;
        BinomialDistribution binomial = BinomialDistribution(kappa, 0);
        VectorEvent* event = new VectorEvent(get_nb_components());
        for(Index component = 0, max_component = get_nb_components(); component < max_component; ++component)
        { 
            binomial.set_pi(_pi[component] / (1 - sum));
            event->set(component, *(binomial.simulate().get()));
            kappa -= static_cast< const DiscreteElementaryEvent* >(event->get(component))->get_value();
            sum += _pi[component];
            binomial.set_kappa(kappa);
        }
        return std::unique_ptr< MultivariateEvent >(event);
    }

    const DiscreteUnivariateDistribution* MultinomialSplittingDistribution::get_sum() const
    { return _sum; }
    
    void MultinomialSplittingDistribution::set_sum(const DiscreteUnivariateDistribution& sum)
    { 
        if(sum.cdf(-1) > 0.)
        { throw parameter_error("sum", "must have a natural numbers subset as support"); }
        _sum = static_cast< DiscreteUnivariateDistribution* >(sum.copy().release()); 
    }

    const Eigen::VectorXd& MultinomialSplittingDistribution::get_pi() const
    { return _pi; }

    void MultinomialSplittingDistribution::set_pi(const Eigen::VectorXd& pi)
    {
        if(pi.rows() == _pi.size() - 1)
        {
            Index j = 0; 
            while(j < pi.rows() && pi[j] >= 0.)
            { ++j; }
            if(j < pi.rows())
            { throw parameter_error("pi", "contains negative values"); } 
            double sum = pi.sum();
            if(sum < 1)
            {
                _pi.block(0, 0, _pi.size() - 1, 1) = pi / sum;
                _pi[_pi.size()-1] = 1 - sum;
            }
            else
            { throw parameter_error("pi", "last category values"); }                
        }
        else if(pi.rows() == _pi.size())
        {
            Index j = 0; 
            while(j < pi.rows() && pi[j] >= 0.)
            { ++j; }
            if(j < pi.rows())
            { throw parameter_error("pi", "contains negative values"); } 
            _pi = pi / pi.sum();
        }
        else
        { throw parameter_error("pi", "number of parameters"); }
    }
    
    MultinormalDistribution::MultinormalDistribution(const Eigen::VectorXd& mu, const Eigen::MatrixXd& sigma)
    {
        _mu = mu;
        _sigma = sigma;
    }
     MultinormalDistribution::MultinormalDistribution(const MultinormalDistribution& normal)
     {
        _mu = normal._mu;
        _sigma = normal._mu;
     }

     MultinormalDistribution::~MultinormalDistribution()
     {}

    Index MultinormalDistribution:: get_nb_components() const
    { return _mu.size(); }

    unsigned int MultinormalDistribution::get_nb_parameters() const
    { return _sigma.size() + _mu.size(); }
    
    std::unique_ptr< MultivariateEvent > MultinormalDistribution::simulate() const
    {
        Eigen::VectorXd x(get_nb_components());
        boost::normal_distribution<> dist(0.,1.);
        boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > simulator(__impl::get_random_generator(), dist);
        for (Index index = 0, max_index = x.size(); index < max_index; ++index)
        { x(index) = simulator(); }
        Eigen::LLT<Eigen:: MatrixXd> llt(_sigma);
        Eigen::MatrixXd B = llt.matrixL();
        x = _mu + B*x;
        return std::make_unique< VectorEvent >(x);
    }

    const Eigen::VectorXd& MultinormalDistribution::get_mu() const
    {return _mu;}
    void MultinormalDistribution::set_mu(const Eigen::VectorXd& mu)
    {_mu = mu ;}

    const Eigen::MatrixXd& MultinormalDistribution::get_sigma() const
    {return _sigma ;}
    void MultinormalDistribution::set_sigma(const Eigen::MatrixXd& sigma)
            {_sigma = sigma ;}


    double MultinormalDistribution::probability(const MultivariateEvent* event, const bool& logarithm) const
    {
        throw not_implemented_error("probability");
        return 0.;
    }

    DiscreteUnivariateMixtureDistribution::DiscreteUnivariateMixtureDistribution(const std::vector< DiscreteUnivariateDistribution* > observations, const Eigen::VectorXd& pi)
    { init(observations, pi); }

    DiscreteUnivariateMixtureDistribution::DiscreteUnivariateMixtureDistribution(const DiscreteUnivariateMixtureDistribution& mixture)
    { init(mixture); }

    DiscreteUnivariateMixtureDistribution::~DiscreteUnivariateMixtureDistribution()
    {}

    int DiscreteUnivariateMixtureDistribution::quantile(const double& p) const
    {
        int lv = _observations[0]->quantile(p);
        int rv = lv;
        for(Index index = 1, max_index = get_nb_states(); index < max_index; ++index)
        {
            int current = _observations[index]->quantile(p);
            if(current < lv)
            { lv = current; }
            else if(current > rv)
            { rv = current; }
        }
        --lv;
        while(cdf(lv) >= p)
        { --lv; }
        ++rv;
        while(cdf(rv) <= p)
        { ++rv; }
        double lp = cdf(lv), rp = cdf(rv);
        do
        {
            int mv = (rv + lv)/2;
            double mp = cdf(mv);
            if(mp < p)
            {
                lv = mv;
                lp = mp;
            }
            else
            {
                rv = mv;
                rp = mp;
            }
        } while(rv - lv > 1);
        return rv;
    }

    ContinuousUnivariateMixtureDistribution::ContinuousUnivariateMixtureDistribution(const std::vector< ContinuousUnivariateDistribution* > observations, const Eigen::VectorXd& pi)
    { 
        init(observations, pi);
        _epsilon = 1e-6;
    }

    ContinuousUnivariateMixtureDistribution::ContinuousUnivariateMixtureDistribution(const ContinuousUnivariateMixtureDistribution& mixture)
    {
        init(mixture);
        _epsilon = mixture._epsilon;
    }

    ContinuousUnivariateMixtureDistribution::~ContinuousUnivariateMixtureDistribution()
    {}

    double ContinuousUnivariateMixtureDistribution::quantile(const double& p) const
    {
        double lv = _observations[0]->quantile(p);
        double rv = lv;
        for(Index index = 1, max_index = get_nb_states(); index < max_index; ++index)
        {
            double current = _observations[0]->quantile(p);
            if(current < lv)
            { lv = current; }
            else if(current > rv)
            { rv = current; }
        }
        double lp = cdf(lv), rp = cdf(rv);
        do
        {
            int mv = (rv + lv)/2;
            double mp = cdf(mv);
            if(mp < p)
            {
                lv = mv;
                lp = mp;
            }
            else
            {
                rv = mv;
                rp = mp;
            } 
        } while(rv - lv > _epsilon);
        return rv;
    }

    double ContinuousUnivariateMixtureDistribution::get_epsilon() const
    { return _epsilon; }

    void ContinuousUnivariateMixtureDistribution::set_epsilon(const double& epsilon)
    { 
        if(epsilon <= 0.)
        { throw lower_bound_error("epsilon", epsilon, 0., true); }
        _epsilon = epsilon;
    }
}
