/**********************************************************************************/
/*                                                                                */
/* StatisKit-CoreThis software is distributed under the CeCILL-C license. You     */
/* should have received a copy of the legalcode along with this work. If not, see */
/* <http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html>.                 */
/*                                                                                */
/**********************************************************************************/

#include "moment.h"

namespace statiskit
{
    qualitative_sample_space_error::qualitative_sample_space_error() : parameter_error("data", "unexpected " + __impl::to_string(CATEGORICAL) + " outcome")
    {}

    NaturalMeanEstimation::NaturalMeanEstimation(const double& mean)
    { _mean = mean; }

    NaturalMeanEstimation::NaturalMeanEstimation(const NaturalMeanEstimation& estimation)
    { _mean = estimation._mean; }

    const double& NaturalMeanEstimation::get_mean() const
    { return _mean; }

    NaturalMeanEstimation::Estimator::Estimator()
    {}

    NaturalMeanEstimation::Estimator::Estimator(const Estimator& estimator)
    {}

    std::unique_ptr< MeanEstimation > NaturalMeanEstimation::Estimator::operator() (const UnivariateData& data) const
    {
        double total = data.compute_total();
        double mean = 0.;
        std::unique_ptr< MeanEstimation > estimation;
        if(total > 0)
        {
            std::unique_ptr< UnivariateData::Generator > generator = data.generator();
            switch(data.get_sample_space()->get_outcome())
            {
                case DISCRETE:
                    while(generator->is_valid())
                    {
                        const UnivariateEvent* event = generator->event();
                        if(event && event->get_event() == ELEMENTARY)
                        { mean += generator->weight() * static_cast< const DiscreteElementaryEvent* >(event)->get_value() / total; }
                        ++(*generator);
                    }
                    break;
                case CONTINUOUS:
                    while(generator->is_valid())
                    {
                        const UnivariateEvent* event = generator->event();
                        if(event && event->get_event() == ELEMENTARY)
                        { mean += generator->weight() * static_cast< const ContinuousElementaryEvent* >(event)->get_value() / total; }
                        ++(*generator);
                    }
                    break;
                default:
                    mean = std::numeric_limits< double >::quiet_NaN();
                    break;
            }
            estimation = std::make_unique< NaturalMeanEstimation >(mean);
        }
        else
        { throw sample_size_error(1); }
        return estimation;
    }

    std::unique_ptr< MeanEstimation::Estimator > NaturalMeanEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    NaturalMeanVectorEstimation::NaturalMeanVectorEstimation(const Eigen::VectorXd& mean)
    { _mean = mean; }

    NaturalMeanVectorEstimation::NaturalMeanVectorEstimation(const NaturalMeanVectorEstimation& estimation)
    { _mean = estimation._mean; }

    NaturalMeanVectorEstimation::Estimator::Estimator()
    {}

    NaturalMeanVectorEstimation::Estimator::Estimator(const Estimator& estimator)
    {}

    std::unique_ptr< MeanVectorEstimation > NaturalMeanVectorEstimation::Estimator::operator() (const MultivariateData& data) const
    {
        Eigen::VectorXd mu = Eigen::VectorXd(data.get_sample_space()->size());
        NaturalMeanEstimation::Estimator estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< UnivariateData > marginal;
        for(Index index = 0, max_index = mu.size(); index < max_index; ++index)
        {
            marginal = data.extract(index);
            mu(index) = estimator(*marginal)->get_mean();
        }
        return std::make_unique< NaturalMeanVectorEstimation >(mu);
    }

    std::unique_ptr< MeanVectorEstimation::Estimator > NaturalMeanVectorEstimation::Estimator::copy() const
    { return std::make_unique< NaturalMeanVectorEstimation::Estimator >(*this); }

    const Eigen::VectorXd& NaturalMeanVectorEstimation::get_mean() const
    { return _mean; }

    VarianceEstimation::VarianceEstimation(const double& mean)
    { _mean = mean; }

    VarianceEstimation::VarianceEstimation(const VarianceEstimation& estimation)
    { _mean = estimation._mean; }

    const double& VarianceEstimation::get_mean() const
    { return _mean; }

    NaturalVarianceEstimation::NaturalVarianceEstimation(const double& mean, const bool& bias, const double& variance) : VarianceEstimation(mean)
    { 
        _bias = bias;
        _variance = variance;
    }

    NaturalVarianceEstimation::NaturalVarianceEstimation(const NaturalVarianceEstimation& estimation) : VarianceEstimation(estimation)
    {
        _bias = estimation._bias;
        _variance = estimation._variance;
    }

    const bool& NaturalVarianceEstimation::get_bias() const
    { return _bias; }

    const double& NaturalVarianceEstimation::get_variance() const
    { return _variance; }
    
    NaturalVarianceEstimation::Estimator::Estimator()
    { _bias = false; }

    NaturalVarianceEstimation::Estimator::Estimator(const bool& bias)
    { _bias = bias; }

    NaturalVarianceEstimation::Estimator::Estimator(const Estimator& estimator)
    { _bias = estimator._bias; }
    
    std::unique_ptr< VarianceEstimation > NaturalVarianceEstimation::Estimator::operator() (const UnivariateData& data, const double& mean) const
    { 
        double total = data.compute_total(), total_square = 0.;
        std::unique_ptr< VarianceEstimation > estimation;
        if(total > 0)
        {
            double variance = 0.;
            std::unique_ptr< UnivariateData::Generator > generator = data.generator();
            switch(data.get_sample_space()->get_outcome())
            {
                case DISCRETE:
                    while(generator->is_valid())
                    {
                        const UnivariateEvent* event = generator->event();
                        if(event && event->get_event() == ELEMENTARY)
                        { 
                            variance += generator->weight() * pow(static_cast< const DiscreteElementaryEvent* >(event)->get_value() - mean, 2) / total;
                            total_square += pow(generator->weight(), 2);
                        }
                        ++(*generator);
                    }
                    break;
                case CONTINUOUS:
                    while(generator->is_valid())
                    {
                        const UnivariateEvent* event = generator->event();
                        if(event && event->get_event() == ELEMENTARY)
                        {
                            variance += generator->weight() * pow(static_cast< const ContinuousElementaryEvent* >(event)->get_value() - mean, 2)/ total;
                            total_square += pow(generator->weight(), 2);
                        }
                        ++(*generator);
                    }
                    break;
                default:
                    variance = std::numeric_limits< double >::quiet_NaN();
                    break;
            }
            if(!_bias)
            {
                total *= total;
                variance *= total/(total - total_square);
            }
            estimation = std::make_unique< NaturalVarianceEstimation >(mean, _bias, variance);
        }
        else
        { throw sample_size_error(1); }
        return estimation;
    }

    std::unique_ptr< VarianceEstimation::Estimator > NaturalVarianceEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    const bool& NaturalVarianceEstimation::Estimator::get_bias() const
    { return _bias; }

    void NaturalVarianceEstimation::Estimator::set_bias(const bool& bias)
    { _bias = bias; }

    CovarianceMatrixEstimation::CovarianceMatrixEstimation(const Eigen::VectorXd& mean)
    { _mean = mean; }

    CovarianceMatrixEstimation::CovarianceMatrixEstimation(const CovarianceMatrixEstimation& estimation)
    { _mean = estimation._mean; }

    const Eigen::VectorXd& CovarianceMatrixEstimation::get_mean() const
    { return _mean; }

    NaturalCovarianceMatrixEstimation::NaturalCovarianceMatrixEstimation(const Eigen::VectorXd& mean, const Eigen::MatrixXd& covariance, const bool& bias) : CovarianceMatrixEstimation(mean)
    { 
        _covariance = covariance;
        _bias = bias;
    }

    NaturalCovarianceMatrixEstimation::NaturalCovarianceMatrixEstimation(const NaturalCovarianceMatrixEstimation& estimation) : CovarianceMatrixEstimation(estimation)
    {
        _covariance = estimation._covariance;
        _bias = estimation._bias;
    }

    const bool& NaturalCovarianceMatrixEstimation::get_bias() const
    { return _bias; }

    const Eigen::MatrixXd& NaturalCovarianceMatrixEstimation::get_covariance() const
    { return _covariance; }

    NaturalCovarianceMatrixEstimation::Estimator::Estimator()
    { _bias = false; }

    NaturalCovarianceMatrixEstimation::Estimator::Estimator(const bool& bias)
    { _bias = bias; }

    NaturalCovarianceMatrixEstimation::Estimator::Estimator(const Estimator& estimator)
    { _bias = estimator._bias; }

    std::unique_ptr< CovarianceMatrixEstimation > NaturalCovarianceMatrixEstimation::Estimator::operator() (const MultivariateData& data, const Eigen::VectorXd& mean) const
    {
        Eigen::MatrixXd covariance = Eigen::MatrixXd(mean.size(), mean.size());
        for(Index i = 0, max_i = mean.size(); i < max_i; ++i)
        {
            covariance(i, i) = compute(data, mean, i, i);
            for(Index j = 0; j < i; ++j)
            {
                covariance(i, j) = compute(data, mean, i, j);
                covariance(j, i) = covariance(i, j);
            }
        }
        if(!_bias)
        {}
        return std::make_unique< NaturalCovarianceMatrixEstimation >(mean, covariance, _bias);
    }

    std::unique_ptr< CovarianceMatrixEstimation::Estimator > NaturalCovarianceMatrixEstimation::Estimator::copy() const
    { return std::make_unique< Estimator >(*this); }

    const bool& NaturalCovarianceMatrixEstimation::Estimator::get_bias() const
    { return _bias; }

    void NaturalCovarianceMatrixEstimation::Estimator::set_bias(const bool& bias)
    { _bias = bias; }

    double NaturalCovarianceMatrixEstimation::Estimator::compute(const MultivariateData& data, const Eigen::VectorXd& mean, const Index& i, const Index& j) const
    {
        double covariance = 0., total = 0., total_square = 0.;
        switch(data.get_sample_space()->get(i)->get_outcome())
        {
            case CATEGORICAL:
                covariance = std::numeric_limits< double >::quiet_NaN();
                break;
            case DISCRETE:
                switch(data.get_sample_space()->get(j)->get_outcome())
                {
                    case CATEGORICAL:
                        covariance = std::numeric_limits< double >::quiet_NaN();
                        break;
                    case DISCRETE:
                        {
                            std::unique_ptr< MultivariateData::Generator > generator = data.generator();
                            while(generator->is_valid())
                            {
                                double _covariance = 0;
                                const UnivariateEvent* event = generator->event()->get(i);
                                if(event && event->get_event() == ELEMENTARY)
                                { 
                                    _covariance = static_cast< const DiscreteElementaryEvent* >(event)->get_value() - mean(i);
                                    event = generator->event()->get(j);
                                    if(event && event->get_event() == ELEMENTARY)
                                    {
                                        _covariance *= static_cast< const DiscreteElementaryEvent* >(event)->get_value() - mean(j);
                                        covariance += _covariance * generator->weight();
                                        total += generator->weight();
                                        total_square += pow(generator->weight(), 2);
                                    }
                                }
                                ++(*generator);
                            }
                        }
                        break;
                    case CONTINUOUS:
                        {
                            std::unique_ptr< MultivariateData::Generator > generator = data.generator();
                            while(generator->is_valid())
                            {
                                double _covariance = 0;
                                const UnivariateEvent* event = generator->event()->get(i);
                                if(event && event->get_event() == ELEMENTARY)
                                { 
                                    _covariance = static_cast< const DiscreteElementaryEvent* >(event)->get_value() - mean(i);
                                    event = generator->event()->get(j);
                                    if(event && event->get_event() == ELEMENTARY)
                                    {
                                        _covariance *= static_cast< const ContinuousElementaryEvent* >(event)->get_value() - mean(j);
                                        covariance += _covariance * generator->weight();
                                        total += generator->weight();
                                        total_square += pow(generator->weight(), 2);
                                    }
                                }
                                ++(*generator);
                            }
                        }
                        break;
                }
                break;
            case CONTINUOUS:
                switch(data.get_sample_space()->get(j)->get_outcome())
                {
                    case CATEGORICAL:
                        covariance = std::numeric_limits< double >::quiet_NaN();
                        break;
                    case DISCRETE:
                        {
                            std::unique_ptr< MultivariateData::Generator > generator = data.generator();
                            while(generator->is_valid())
                            {
                                double _covariance = 0;
                                const UnivariateEvent* event = generator->event()->get(i);
                                if(event && event->get_event() == ELEMENTARY)
                                { 
                                    _covariance = static_cast< const ContinuousElementaryEvent* >(event)->get_value() - mean(i);
                                    event = generator->event()->get(j);
                                    if(event && event->get_event() == ELEMENTARY)
                                    {
                                        _covariance *= static_cast< const DiscreteElementaryEvent* >(event)->get_value() - mean(j);
                                        covariance += _covariance * generator->weight();
                                        total += generator->weight();
                                        total_square += pow(generator->weight(), 2);
                                    }
                                }
                                ++(*generator);
                            }
                        }
                        break;
                    case CONTINUOUS:
                        {
                            std::unique_ptr< MultivariateData::Generator > generator = data.generator();
                            while(generator->is_valid())
                            {
                                double _covariance = 0;
                                const UnivariateEvent* event = generator->event()->get(i);
                                if(event && event->get_event() == ELEMENTARY)
                                { 
                                    _covariance = static_cast< const ContinuousElementaryEvent* >(event)->get_value() - mean(i);
                                    event = generator->event()->get(j);
                                    if(event && event->get_event() == ELEMENTARY)
                                    {
                                        _covariance *= static_cast< const ContinuousElementaryEvent* >(event)->get_value() - mean(j);
                                        covariance += _covariance * generator->weight();
                                        total += generator->weight();
                                        total_square += pow(generator->weight(), 2);
                                    }
                                }
                                ++(*generator);
                            }
                        }
                        break;
                }
                break;
        }
        covariance /= total;
        if(!_bias)
        { 
            total = pow(total, 2.);
            covariance *= total / (total - total_square);
        }
        return covariance;
    }
    /*CoVarianceEstimation::CoVarianceEstimation(const std::array< double, 2 >& means)
    { _means = means; }

    CoVarianceEstimation::CoVarianceEstimation(const CoVarianceEstimation& estimation)
    { _means = estimation._means; }

    const std::array< double, 2 >& CoVarianceEstimation::get_means() const
    { return _means; }
    
    std::unique_ptr< CoVarianceEstimation > CoVarianceEstimation::Estimator::operator() (const UnivariateData& data) const
    {
        NaturalMeanEstimation::Estimator estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< MeanEstimation > estimation = estimator(data);
        double mean = estimation->get_mean();
        return operator() (data, mean);
    }

    std::unique_ptr< CoVarianceEstimation > CoVarianceEstimation::Estimator::operator() (const UnivariateData& data, const double& mean) const
    {
        std::unique_ptr< MultivariateDataFrame > datas = std::make_unique< MultivariateDataFrame >();
        datas->append_component(data);
        datas->append_component(data);
        std::array< double, 2 > means{ {mean, mean} };
        return operator() (0, 1, datas, means);
    }

    std::unique_ptr< CoVarianceEstimation > CoVarianceEstimation::Estimator::operator() (const Index& i, const Index& j, const std::unique_ptr< MultivariateDataFrame > data) const
    {
        NaturalMeanEstimation::Estimator estimator = NaturalMeanEstimation::Estimator();
        std::unique_ptr< MeanEstimation > estimation_i = estimator(data.get_component(i));
        std::unique_ptr< MeanEstimation > estimation_j = estimator(data.get_component(j));
        std::array< double, 2 > means{ {estimation_i->get_mean(), estimation_j->get_mean()} };
        return operator() (i, j, data, means);
    }

    NaturalCoVarianceEstimation::NaturalCoVarianceEstimation(const std::array< double, 2 >& means, const double& covariance, const bool& bias) : CoVarianceEstimation(means)
    {
        _covariance = covariance;
        _bias = bias;
    }

    NaturalCoVarianceEstimation::NaturalCoVarianceEstimation(const NaturalCoVarianceEstimation& estimation) : CoVarianceEstimation(estimation)
    {
        _covariance = estimation._covariance;
        _bias = estimation._bias;
    }

    const bool& NaturalCoVarianceEstimation::get_bias() const
    { return _bias; }

    const double& NaturalCoVarianceEstimation::get_covariance() const
    { return _covariance; }

    NaturalCoVarianceEstimation::Estimator::Estimator(const bool& bias)
    { _bias = bias; }

    NaturalCoVarianceEstimation::Estimator::Estimator(const Estimator& estimator)
    { _bias = estimator._bias; }

    std::unique_ptr< CoVarianceEstimation > NaturalCoVarianceEstimation::Estimator::operator() (const Index& i, const Index& j, const std::unique_ptr< MultivariateDataFrame > data, const std::array< double, 2 >& means) const
    {
        if(!data)
        { throw std::runtime_error("None"); }
        if(!*data)
        { throw std::runtime_error("invalid"); }
        double total = data.compute_total(), covariance;
        if(total > 0 && data.size() > 0 && boost::math::isfinite(means.at(0) + means.at(1)))
        {
            Index index = 0, max_index = data.size();
            double total_square = 0;
            const UnivariateData&& data_i = data.get_component(i), data_j = data.get_component(j);
            switch(data_i->get_sample_space()->get_outcome())
            {
                case CATEGORICAL:
                    covariance = std::numeric_limits< double >::quiet_NaN();
                    break;
                case DISCRETE:
                    switch(data_j->get_sample_space()->get_outcome())
                    {
                        case CATEGORICAL:
                            covariance = std::numeric_limits< double >::quiet_NaN();
                            break;
                        case DISCRETE:
                            covariance = 0.;
                            while(boost::math::isfinite(covariance) && index < max_index)
                            {
                                const UnivariateEvent* event_i = data_i->get_event(index);
                                if(event_i && event_i->get_event() == ELEMENTARY)
                                {
                                    const UnivariateEvent* event_j = data_j->get_event(index);
                                    if(event_j && event_j->get_event() == ELEMENTARY)
                                    { 
                                        covariance += data.get_weight(index) * (static_cast< const DiscreteElementaryEvent* >(event_i)->get_value() - means.at(i)) * (static_cast< const DiscreteElementaryEvent* >(event_j)->get_value() - means.at(j)) / total;
                                        total_square += pow(data.get_weight(index), 2);
                                    }
                                }
                                ++index;
                            }
                            break;
                        case CONTINUOUS:
                            covariance = 0.;
                            while(boost::math::isfinite(covariance) && index < max_index)
                            {
                                const UnivariateEvent* event_i = data_i->get_event(index);
                                if(event_i && event_i->get_event() == ELEMENTARY)
                                {
                                    const UnivariateEvent* event_j = data_j->get_event(index);
                                    if(event_j && event_j->get_event() == ELEMENTARY)
                                    { 
                                        covariance += data.get_weight(index) * (static_cast< const DiscreteElementaryEvent* >(event_i)->get_value() - means.at(i)) * (static_cast< const ContinuousElementaryEvent* >(event_j)->get_value() - means.at(j)) / total; 
                                        total_square += pow(data.get_weight(index), 2);                                        
                                    }
                                }
                                ++index;
                            }
                            break;
                    }
                    break;
                case CONTINUOUS:
                    switch(data_j->get_sample_space()->get_outcome())
                    {
                        case CATEGORICAL:
                            covariance = std::numeric_limits< double >::quiet_NaN();
                            break;
                        case DISCRETE:
                            covariance = 0.;
                            while(boost::math::isfinite(covariance) && index < max_index)
                            {
                                const UnivariateEvent* event_i = data_i->get_event(index);
                                if(event_i && event_i->get_event() == ELEMENTARY)
                                {
                                    const UnivariateEvent* event_j = data_j->get_event(index);
                                    if(event_j && event_j->get_event() == ELEMENTARY)
                                    {
                                        covariance += data.get_weight(index) * (static_cast< const ContinuousElementaryEvent* >(event_i)->get_value() - means.at(i)) * (static_cast< const DiscreteElementaryEvent* >(event_j)->get_value() - means.at(j)) / total;
                                        total_square += pow(data.get_weight(index), 2);                                        
                                    }
                                }
                                ++index;
                            }
                            break;
                        case CONTINUOUS:
                            covariance = 0.;
                            while(boost::math::isfinite(covariance) && index < max_index)
                            {
                                const UnivariateEvent* event_i = data_i->get_event(index);
                                if(event_i && event_i->get_event() == ELEMENTARY)
                                {
                                    const UnivariateEvent* event_j = data_j->get_event(index);
                                    if(event_j && event_j->get_event() == ELEMENTARY)
                                    { 
                                        covariance += data.get_weight(index) * (static_cast< const ContinuousElementaryEvent* >(event_i)->get_value() - means.at(i)) * (static_cast< const ContinuousElementaryEvent* >(event_j)->get_value() - means.at(j)) / total;
                                        total_square += pow(data.get_weight(index), 2);                                        
                                    }
                                }
                                ++index;
                            }
                            break;
                    }
                    break;
            }
            if(boost::math::isfinite(covariance) && !_bias)
            {
                total *= total; 
                covariance *= total / (total - total_square);
            }
        }
        else
        { covariance = std::numeric_limits< double >::quiet_NaN(); }
        return std::make_unique< NaturalCoVarianceEstimation >(means, covariance, _bias);
    }

    const bool& NaturalCoVarianceEstimation::Estimator::get_bias() const
    { return _bias; }

    void NaturalCoVarianceEstimation::Estimator::set_bias(const bool& bias)
    { _bias = bias; }

    /*double MomentEstimator::operator() (const std::array< const UnivariateData*, 3 >& df) const
    {
        std::array< double, 3 > mean{ {(*this)(df.at(0), na_omit),
                                       (*this)(df.at(1), na_omit),
                                       (*this)(df.at(2), na_omit)} };
        return (*this)(df, mean, na_omit);
    }

    double MomentEstimator::operator() (const std::array< const UnivariateData*, 3 >& df, const std::array< double, 3 >& mean) const
    {
        std::array< double, 3 > stderror{ {(*this)(std::array< const UnivariateData*, 2 >{ {df.at(0), df.at(0)} }, std::array< double, 2 >{ {mean.at(0), mean.at(0)} }, na_omit),
                                           (*this)(std::array< const UnivariateData*, 2 >{ {df.at(1), df.at(1)} }, std::array< double, 2 >{ {mean.at(1), mean.at(1)} }, na_omit),
                                           (*this)(std::array< const UnivariateData*, 2 >{ {df.at(2), df.at(2)} }, std::array< double, 2 >{ {mean.at(2), mean.at(2)} }, na_omit)} };
        stderror.at(0) = sqrt(stderror.at(0));
        stderror.at(1) = sqrt(stderror.at(1));
        stderror.at(2) = sqrt(stderror.at(2));
        return (*this)(df, mean, stderror, na_omit);
    }

    double MomentEstimator::operator() (const std::array< const UnivariateData*, 4 >& df) const
    {
        std::array< double, 4 > mean{ {(*this)(df.at(0), na_omit),
                                       (*this)(df.at(1), na_omit),
                                       (*this)(df.at(2), na_omit),
                                       (*this)(df.at(3), na_omit)} };
        return (*this)(df, mean, na_omit);
    }

    double MomentEstimator::operator() (const std::array< const UnivariateData*, 4 >& df, const std::array< double, 4 >& mean) const
    {
        std::array< double, 4 > stderror{ {(*this)(std::array< const UnivariateData*, 2 >{ {df.at(0), df.at(0)} }, std::array< double, 2 >{ {mean.at(0), mean.at(0)} }, na_omit),
                                           (*this)(std::array< const UnivariateData*, 2 >{ {df.at(1), df.at(1)} }, std::array< double, 2 >{ {mean.at(1), mean.at(1)} }, na_omit),
                                           (*this)(std::array< const UnivariateData*, 2 >{ {df.at(2), df.at(2)} }, std::array< double, 2 >{ {mean.at(2), mean.at(2)} }, na_omit),
                                           (*this)(std::array< const UnivariateData*, 2 >{ {df.at(3), df.at(3)} }, std::array< double, 2 >{ {mean.at(3), mean.at(3)} }, na_omit)} };
        stderror.at(0) = sqrt(stderror.at(0));
        stderror.at(1) = sqrt(stderror.at(1));
        stderror.at(2) = sqrt(stderror.at(2));
        stderror.at(3) = sqrt(stderror.at(3));
        return (*this)(df, mean, stderror, na_omit);
    }

    NaturalMomentEstimator::NaturalMomentEstimator(const bool& biased)
    { _biased = biased; }

    NaturalMomentEstimator::NaturalMomentEstimator(const NaturalMomentEstimator& estimator)
    { _biased = estimator._biased; }

    NaturalMomentEstimator::~NaturalMomentEstimator()
    {}

    double NaturalMomentEstimator::operator() (const UnivariateData* df) const
    {
        double total;
        if(df && df->get_sample_space()->get_outcome() != CATEGORICAL)
        { total = df->compute_total(na_omit); }
        else
        { total = std::numeric_limits< double >::quiet_NaN(); }
        double mean;
        if(boost::math::isfinite(total))
        {
            mean = 0.;
            switch(df->get_sample_space()->get_outcome())
            {
                case DISCRETE:
                    for(Index index = 0, max_index = df->size(); index < max_index; ++index)
                    { mean += get_value< DiscreteEvent >(df, index, na_omit)/total; }
                    break;
                case CONTINUOUS:
                    for(Index index = 0, max_index = df->size(); index < max_index; ++index)
                    { mean += get_value< ContinuousEvent >(df, index, na_omit)/total; }
                    break;
                default:
                    mean = std::numeric_limits< double >::quiet_NaN();
                    break;
            }
        }
        else
        { mean = total; }
        return mean;
    }

    double NaturalMomentEstimator::operator() (const std::array< const UnivariateData*, 2 >& df, const std::array< double, 2 >& mean) const
    {
        double total;
        if(df.at(0) && df.at(1) && df.at(0)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(1)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(0)->size() == df.at(1)->size())
        { total = std::min(df.at(0)->compute_total(na_omit), df.at(1)->compute_total(na_omit)); }
        else
        { total = std::numeric_limits< double >::quiet_NaN(); }
        double covariance;
        if(boost::math::isfinite(total))
        {
            covariance = 0.;
            Index index = 0;
            std::array< Index, 2 > max_index{ {df.at(0)->size(), df.at(1)->size()} };
            switch(df.at(0)->get_sample_space()->get_outcome())
            {
                case DISCRETE:
                    switch(df.at(1)->get_sample_space()->get_outcome())
                    {
                        case DISCRETE:
                            while(index < max_index.at(0) || index < max_index.at(1))
                            {
                                covariance += (get_value< DiscreteEvent >(df.at(0), index, mean[0], na_omit)-mean[0]) *
                                    (get_value< DiscreteEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/total;
                                ++index;
                            }
                            break;
                        case CONTINUOUS:
                            while(index < max_index.at(0) || index < max_index.at(1))
                            {
                                covariance += (get_value< DiscreteEvent >(df.at(0), index, mean[0], na_omit)-mean[0]) * 
                                    (get_value< ContinuousEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/total;
                                ++index;
                            }
                            break;
                        default:
                            covariance = std::numeric_limits< double >::quiet_NaN();
                            break;
                    }
                    break;
                case CONTINUOUS:
                    switch(df.at(1)->get_sample_space()->get_outcome())
                    {
                        case DISCRETE:
                            while(index < max_index.at(0) || index < max_index.at(1))
                            {
                                covariance += (get_value< ContinuousEvent >(df.at(0), index, mean[0], na_omit)-mean[0]) *
                                    (get_value< DiscreteEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/total;
                                ++index;
                            }
                            break;
                        case CONTINUOUS:
                            while(index < max_index.at(0) || index < max_index.at(1))
                            {
                                covariance += (get_value< ContinuousEvent >(df.at(0), index, mean[0], na_omit)-mean[0]) *
                                    (get_value< ContinuousEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/total;
                                ++index;
                            }
                            break;
                        default:
                            covariance = std::numeric_limits< double >::quiet_NaN();
                            break;
                    }
                    break;
                default:
                    covariance = std::numeric_limits< double >::quiet_NaN();
                    break;
            }
            if(boost::math::isfinite(covariance) && !_biased)
            { covariance *= total/(total-1); }
        }
        else
        { covariance = total; }
        return covariance;
    }

    double NaturalMomentEstimator::operator() (const std::array< const UnivariateData*, 3 >& df, const std::array<double, 3>& mean, const std::array<double, 3>& stderror) const
    {
        double total;
        if(df.at(0) && df.at(1) && df.at(2) && df.at(0)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(1)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(2)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(0)->size() == df.at(1)->size() && df.at(1)->size() == df.at(2)->size())
        { total = std::min(df.at(0)->compute_total(na_omit), std::min(df.at(1)->compute_total(na_omit), df.at(2)->compute_total(na_omit))); }
        else
        { total = std::numeric_limits< double >::quiet_NaN(); }
        double coskewness;
        if(boost::math::isfinite(total))
        {
            coskewness = 0.;
            Index index = 0;
            std::array< Index, 3 > max_index{ {df.at(0)->size(), df.at(1)->size(), df.at(2)->size()} };
            switch(df.at(0)->get_sample_space()->get_outcome())
            {
                case DISCRETE:
                    switch(df.at(1)->get_sample_space()->get_outcome())
                    {
                        case DISCRETE:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< DiscreteEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< DiscreteEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< DiscreteEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                case CONTINUOUS:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< DiscreteEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< DiscreteEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< ContinuousEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                default:
                                    coskewness = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        case CONTINUOUS:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< DiscreteEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< ContinuousEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< DiscreteEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                case CONTINUOUS:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< DiscreteEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< ContinuousEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< ContinuousEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                default:
                                    coskewness = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        default:
                            coskewness = std::numeric_limits< double >::quiet_NaN();
                            break;
                    }
                    break;
                case CONTINUOUS:
                    switch(df.at(1)->get_sample_space()->get_outcome())
                    {
                        case DISCRETE:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< ContinuousEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< DiscreteEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< DiscreteEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                case CONTINUOUS:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< ContinuousEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< DiscreteEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< ContinuousEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                default:
                                    coskewness = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        case CONTINUOUS:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< ContinuousEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< ContinuousEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< DiscreteEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                case CONTINUOUS:
                                    while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2))
                                    {
                                        coskewness += ((get_value< ContinuousEvent >(df.at(0), index, mean[0], na_omit)-mean[0])/stderror[0] *
                                                (get_value< ContinuousEvent >(df.at(1), index, mean[1], na_omit)-mean[1])/stderror[1] *
                                                (get_value< ContinuousEvent >(df.at(2), index, mean[2], na_omit)-mean[2])/stderror[2])/total;
                                        ++index;
                                    }
                                    break;
                                default:
                                    coskewness = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        default:
                            coskewness = std::numeric_limits< double >::quiet_NaN();
                            break;
                    }
                    break;
                default:
                    coskewness = std::numeric_limits< double >::quiet_NaN();
                    break;
            }
            if(boost::math::isfinite(coskewness) && !_biased)
            { coskewness *= total/(total-1)*total/(total-2); }
        }
        else
        { coskewness = total; }
        return coskewness;
    }

    double NaturalMomentEstimator::operator() (const std::array< const UnivariateData*, 4 >& df, const std::array<double, 4>& mean, const std::array<double, 4>& stderror) const
    {
        double total;
        if(df.at(0) && df.at(1) && df.at(2) && df.at(3) && df.at(0)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(1)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(2)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(3)->get_sample_space()->get_outcome() != CATEGORICAL && df.at(0)->size() == df.at(1)->size() && df.at(1)->size() == df.at(2)->size() && df.at(2)->size() == df.at(3)->size())
        { total = std::min(df.at(0)->compute_total(na_omit), std::min(df.at(1)->compute_total(na_omit), std::min(df.at(2)->compute_total(na_omit), df.at(3)->compute_total(na_omit)))); }
        else
        { total = std::numeric_limits< double >::quiet_NaN(); }
        double cokurtosis;
        if(boost::math::isfinite(total))
        {
            cokurtosis = 0.;
            Index index = 0;
            std::array< Index, 4 > max_index = { {df.at(0)->size(), df.at(1)->size(), df.at(2)->size(), df.at(3)->size()} };
            switch(df.at(0)->get_sample_space()->get_outcome())
            {
                case DISCRETE:
                    switch(df.at(1)->get_sample_space()->get_outcome())
                    {
                        case DISCRETE:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                case CONTINUOUS:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                default:
                                    cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        case CONTINUOUS:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                case CONTINUOUS:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< ContinuousEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< DiscreteEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< ContinuousEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                default:
                                    cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        default:
                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                            break;
                    }
                    break;
                case CONTINUOUS:
                    switch(df.at(1)->get_sample_space()->get_outcome())
                    {
                        case DISCRETE:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                case CONTINUOUS:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                default:
                                    cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        case CONTINUOUS:
                            switch(df.at(2)->get_sample_space()->get_outcome())
                            {
                                case DISCRETE:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< DiscreteEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< DiscreteEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                case CONTINUOUS:
                                    switch(df.at(3)->get_sample_space()->get_outcome())
                                    {
                                        case DISCRETE:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< ContinuousEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< DiscreteEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                            break;
                                        case CONTINUOUS:
                                            while(index < max_index.at(0) || index < max_index.at(1) || index < max_index.at(2) || index < max_index.at(3))
                                            {
                                                cokurtosis += ((get_value< ContinuousEvent >(df.at(0)->get_event(index).get(), mean[0], na_omit)-mean[0])/stderror[0] *
                                                        (get_value< ContinuousEvent >(df.at(1)->get_event(index).get(), mean[1], na_omit)-mean[1])/stderror[1] *
                                                        (get_value< ContinuousEvent >(df.at(2)->get_event(index).get(), mean[2], na_omit)-mean[2])/stderror[2] *
                                                        (get_value< ContinuousEvent >(df.at(3)->get_event(index).get(), mean[3], na_omit)-mean[3])/stderror[3])/total;
                                                ++index;
                                            }
                                        default:
                                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                            break;
                                    }
                                    break;
                                default:
                                    cokurtosis = std::numeric_limits< double >::quiet_NaN();
                                    break;
                            }
                            break;
                        default:
                            cokurtosis = std::numeric_limits< double >::quiet_NaN();
                            break;
                    }
                    break;
                default:
                    cokurtosis = std::numeric_limits< double >::quiet_NaN();
                    break;
            }
            if(boost::math::isfinite(cokurtosis) && !_biased)
            {
                cokurtosis *= total/(total-1)*total/(total-2)*(total+1)/(total-3);
                cokurtosis -= 3*(total-1)*(total-1)/((total-2)*(total-3));
            }
            else
            { cokurtosis -= 3.; }
        }
        else
        { cokurtosis = total; }
        return cokurtosis;
    }

    const bool& NaturalMomentEstimator::get_biased() const
    { return _biased; }

    std::unique_ptr< MomentEstimator > NaturalMomentEstimator::copy() const
    { return std::make_unique< NaturalMomentEstimator >(*this); }*/
}
