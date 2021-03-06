/**********************************************************************************/
/*                                                                                */
/* StatisKit-CoreThis software is distributed under the CeCILL-C license. You     */
/* should have received a copy of the legalcode along with this work. If not, see */
/* <http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html>.                 */
/*                                                                                */
/**********************************************************************************/

#ifndef STATISKIT_CORE_DISTRIBUTION_HPP
#define STATISKIT_CORE_DISTRIBUTION_HPP

namespace statiskit
{
    template<class T>
        UnivariateFrequencyDistribution< T >::UnivariateFrequencyDistribution()
        {}

    template<class T>
        unsigned int UnivariateFrequencyDistribution< T >::get_nb_parameters() const
        { return _pi.size() - 1; }

    template<class T>
        double UnivariateFrequencyDistribution< T >::ldf(const typename T::event_type::value_type& value) const
        { return log(pdf(value)); }
    
    template<class T>
        double UnivariateFrequencyDistribution< T >::pdf(const typename T::event_type::value_type& value) const
        {
            double p;
            typename std::set< typename T::event_type::value_type >::const_iterator it = _values.find(value);
            if(it == _values.end())
            { p = 0.; }
            else
            { p = _pi[distance(_values.cbegin(), it)]; }
            return p;
        }
        
    template<class T>
        std::unique_ptr< UnivariateEvent > UnivariateFrequencyDistribution< T >::simulate() const
        {
            double cp = _pi[0], sp = boost::uniform_01<boost::mt19937&>(__impl::get_random_generator())();
            typename std::set< typename T::event_type::value_type >::const_iterator it = _values.cbegin();
            while(it != _values.cend() && cp < sp)
            {
                ++it;
                cp += _pi[distance(_values.cbegin(), it)];
            }
            if(it == _values.cend())
            { --it; }
            return std::make_unique< ElementaryEvent< typename T::event_type > >(*it);
        }

    template<class T>
        std::set< typename T::event_type::value_type > UnivariateFrequencyDistribution< T >::get_values() const
        { return _values; }

    template<class T>
        const Eigen::VectorXd& UnivariateFrequencyDistribution< T >::get_pi() const
        { return _pi; }

    template<class T>
        void UnivariateFrequencyDistribution< T >::set_pi(const Eigen::VectorXd& pi)
        {
        	if(pi.rows() == _values.size() - 1)
        	{
		    	Index j = 0; 
		    	while(j < pi.rows() && pi[j] >= 0.)
		    	{ ++j; }
		    	if(j < pi.rows())
		    	{ throw parameter_error("pi", "contains negative values"); } 
		    	double sum = pi.sum();
		    	if(sum < 1)
		    	{
					_pi.segment(0, _values.size() - 1) = pi;
					_pi[_values.size()-1] = 1 - sum;
		    	}
		    	else
		    	{ throw parameter_error("pi", "last category values"); } 		    	
        	}
        	else if(pi.rows() == _values.size())
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

    template<class T>
        void UnivariateFrequencyDistribution< T >::init(const std::set< typename T::event_type::value_type >& values)
        {
            if(values.size() == 0)
            { throw size_error("values", 0, 0, size_error::superior); }
            _values = values;
            _pi = Eigen::VectorXd::Ones(values.size());
            _pi = _pi / _pi.sum();
        }
    
    template<class T>
        void UnivariateFrequencyDistribution< T >::init(const std::set< typename T::event_type::value_type >& values, const Eigen::VectorXd& pi)
        {
            if(values.size() == 0)
            { throw size_error("values", 0, 0, size_error::superior); }
            if(values.size() != pi.size())
            { throw size_error("values", 0, values.size(), size_error::equal); }
            _values = values;
            set_pi(pi);
        }

    template<class T>
        void UnivariateFrequencyDistribution< T >::init(const UnivariateFrequencyDistribution< T >& frequency)
        {
            _values = frequency._values;
            _pi = frequency._pi;
        }

    template<class T>
        QuantitativeUnivariateFrequencyDistribution<T>::QuantitativeUnivariateFrequencyDistribution(const std::set< typename T::event_type::value_type >& values)
        { this->init(values); }

    template<class T>
        QuantitativeUnivariateFrequencyDistribution<T>::QuantitativeUnivariateFrequencyDistribution(const std::set< typename T::event_type::value_type >& values, const Eigen::VectorXd& pi)
        { this->init(values, pi); }

    template<class T>
         QuantitativeUnivariateFrequencyDistribution<T>::QuantitativeUnivariateFrequencyDistribution(const UnivariateFrequencyDistribution< T >& frequency)
         { this->init(frequency); }

    template<class T>
        double QuantitativeUnivariateFrequencyDistribution< T >::cdf(const typename T::event_type::value_type& value) const
        {
            double p = 0.;
            typename std::set< typename T::event_type::value_type >::const_iterator it = this->_values.cbegin();
            while(it != this->_values.cend() && *it <= value)
            {
                p += this->_pi[distance(this->_values.cbegin(), it)];
                ++it;
            }
            if(it == this->_values.cend())
            { p = 1.; }
            return p;
        }

    template<class T>
         typename T::event_type::value_type QuantitativeUnivariateFrequencyDistribution< T >::quantile(const double& p) const
        {
            double tp = 0.;
            typename T::event_type::value_type q;
            typename std::set< typename T::event_type::value_type >::const_iterator it_begin = this->_values.cbegin(), it, it_end = this->_values.cend();
            it = it_begin;
            while(it != it_end && tp < p)
            {
                tp += this->_pi[distance(it_begin, it)];
                ++it;
            }
            if(it != it_begin)
            { --it; }
            q = *it;
            return q;
        }

    template<class T>
        double QuantitativeUnivariateFrequencyDistribution< T >::get_mean() const
        {
            double mean = 0.;
            for(typename std::set< typename T::event_type::value_type >::const_iterator it = this->_values.cbegin(), it_end = this->_values.cend(); it != it_end; ++it)
            { mean += *it * this->_pi[distance(this->_values.cbegin(), it)]; }
            return mean;
        }

    template<class T>
        double QuantitativeUnivariateFrequencyDistribution< T >::get_variance() const
        {
            double mean = get_mean(), variance = 0.;
            for(typename std::set< typename T::event_type::value_type >::const_iterator it = this->_values.cbegin(), it_end = this->_values.cend(); it != it_end; ++it)
            { variance += pow(*it-mean, 2) * this->_pi[distance(this->_values.cbegin(), it)]; }
            return variance;
        }

    template<class T>
        ShiftedDistribution< T >::ShiftedDistribution(const T& distribution, const typename T::event_type::value_type& shift)
        {
            _distribution = static_cast< T* >(distribution.copy().release());
            _shift = shift;
        }

    template<class T>
        ShiftedDistribution< T >::ShiftedDistribution(const ShiftedDistribution< T >& distribution)
        {
            _distribution = static_cast< T* >(distribution._distribution->copy().release());
            _shift = distribution._shift;
        }

    template<class T>
        ShiftedDistribution< T >::~ShiftedDistribution()
        { delete _distribution; }

    template<class T>
        unsigned int ShiftedDistribution< T >::get_nb_parameters() const
        { return _distribution->get_nb_parameters() + 1 * bool(_shift != 0); }

    template<class T>
        std::unique_ptr< UnivariateEvent > ShiftedDistribution< T >::simulate() const
        { return std::make_unique< ElementaryEvent< typename T::event_type > >(static_cast< ElementaryEvent< typename T::event_type > * >(_distribution->simulate().get())->get_value() + _shift); }

    template<class T>
        double ShiftedDistribution< T >::ldf(const typename T::event_type::value_type& value) const
        { return _distribution->ldf(value - _shift); }

    template<class T>
        double ShiftedDistribution< T >::pdf(const typename T::event_type::value_type& value) const
        { return _distribution->pdf(value - _shift); }

    template<class T>
        double ShiftedDistribution< T >::cdf(const typename T::event_type::value_type& value) const
        { return _distribution->cdf(value - _shift); }

    template<class T>
        typename T::event_type::value_type ShiftedDistribution< T >::quantile(const double& p) const
        { return _distribution->quantile(p) + _shift; }

    template<class T>
        double ShiftedDistribution< T >::get_mean() const
        { return _distribution->get_mean() + _shift; }

    template<class T>
        double ShiftedDistribution< T >::get_variance() const
        { return _distribution->get_variance(); }

    template<class T>
        const typename T::event_type::value_type& ShiftedDistribution< T >::get_shift() const
        { return _shift; }

    template<class T>
        void ShiftedDistribution< T >::set_shift(const typename T::event_type::value_type& shift)
        { _shift = shift; }

    template<class T>
        const T* ShiftedDistribution< T >::get_distribution() const
        { return _distribution; }

    template<class T>
        void ShiftedDistribution< T >::set_distribution(const T& distribution)
        { 
            delete _distribution;
            _distribution = static_cast< T* >(distribution.copy().release());
        }

    template<class D>
        IndependentMultivariateDistribution< D >::IndependentMultivariateDistribution(const std::vector< typename D::marginal_type >& marginals)
        {
            _marginals.resize(marginals.size(), nullptr);
            for(Index component = 0, max_component = marginals.size(); component < max_component; ++component)
            { _marginals[component] = static_cast< typename D::marginal_type* >(marginals[index].copy().release()); }
        }

    template<class D>
        IndependentMultivariateDistribution< D >::IndependentMultivariateDistribution(const IndependentMultivariateDistribution< D >& independent)
        {
            _marginals.resize(independent.get_nb_components(), nullptr);
            for(Index component = 0, max_component = independent.get_nb_components(); component < max_component; ++component)
            { _marginals[component] = static_cast< typename D::marginal_type* >(independent._marginals[component]->copy().release()); }
         }

    template<class D>
        IndependentMultivariateDistribution< D >::~IndependentMultivariateDistribution()
        {
            for(Index component = 0, max_component = get_nb_components(); component < max_component; ++component)
            {
                if(_marginals[component])
                { 
                    delete _marginals[component];
                    _marginals[component] = nullptr;
                }
            }
            _marginals.clear();
        }

    template<class D>
        Index IndependentMultivariateDistribution< D >::get_nb_components() const
        { return _marginals.size(); }

    template<class D>
        unsigned int IndependentMultivariateDistribution< D >::get_nb_parameters() const
        {
            unsigned int nb_parameters = 0;
            for(Index component = 0, max_component = get_nb_components(); component < max_component; ++component)
            { nb_parameters += _marginals[component]->get_nb_parameters(); }
            return nb_parameters; 
        }

    template<class D>
        double IndependentMultivariateDistribution< D >::probability(const MultivariateEvent* event, const bool& logarithm) const
        {
            double p = 0.;
            if(event)
            {
                if(event->size() == get_nb_components())
                {
                    for(Index component = 0, max_component = get_nb_components(); component < max_component; ++component)
                    { p += _marginals[component]->probability(event->get(component), true); }
                }
                else
                { throw size_error("event", get_nb_components(), size_error::equal); }
                if(!logarithm)
                { p = exp(p); }
            }
            else if(logarithm)
            { p = 0.; }
            else
            { p = 1.; }
            return p; 
        }

    template<class D>
        typename D::marginal_type* IndependentMultivariateDistribution< D >:: get_marginal(const Index& index) const
        {
            if(index > get_nb_components())
            { throw size_error("index", get_nb_components(), size_error::inferior); }
            return _marginals[index];
        }


    template<class D>
        void IndependentMultivariateDistribution< D >::set_marginal(const Index& index, const typename D::marginal_type& marginal) 
        {
            if(index > get_nb_components())
            { throw size_error("index", get_nb_components(), size_error::inferior); }
            delete _marginals[index];
            _marginals[index] = static_cast< typename D::marginal_type* >(marginal.copy().release());
        }

    template<class D>
        std::unique_ptr< MultivariateEvent > IndependentMultivariateDistribution< D >::simulate() const
        {
            VectorEvent* event = new VectorEvent(get_nb_components());
            for(Index component = 0, max_component = get_nb_components(); component < max_component; ++component)
            { event->set(component, *(_marginals[component]->simulate().get())); }
            return std::unique_ptr< MultivariateEvent >(event);
        }

    template<class D>
        MixtureDistribution< D >::MixtureDistribution()
        {} 

    template<class D>
        MixtureDistribution< D >::~MixtureDistribution()
        {
            for(Index index = 0, max_index = _observations.size(); index < max_index; ++index)
            { 
                delete _observations[index];
                _observations[index] = nullptr;
            }
            _observations.clear();
        } 

    template<class D>
        unsigned int MixtureDistribution< D >::get_nb_parameters() const
        {
            unsigned int nb_parameters = _pi.size() - 1;
            for(Index index = 0, max_index = _observations.size(); index < max_index; ++index)
            { nb_parameters += _observations[index]->get_nb_parameters(); }
            return nb_parameters;
        }     

    template<class D>
        Index MixtureDistribution< D >::get_nb_states() const
        { return _pi.size(); }     

    template<class D>
        const D* MixtureDistribution< D >::get_observation(const Index& index) const
        { 
            if(index >= get_nb_states())
            { throw size_error("index", get_nb_states(), size_error::inferior); }
            return _observations[index];
        }     

    template<class D>
        void MixtureDistribution< D >::set_observation(const Index& index, const D& observation)
        { 
            if(index >= get_nb_states())
            { throw size_error("index", get_nb_states(), size_error::inferior); }
            _observations[index] = static_cast< D* >(observation.copy().release());
        }     

    template<class D>
        const Eigen::VectorXd& MixtureDistribution< D >::get_pi() const
        { return _pi; }     

    template<class D>
        void MixtureDistribution< D >::set_pi(const Eigen::VectorXd& pi)
        {
            if(pi.size() != _observations.size())
            { throw size_error("pi", _pi.size(), size_error::equal); }
            _pi = pi / pi.sum();
        } 


    template<class D>
        Eigen::VectorXd MixtureDistribution< D >::posterior(const typename D::data_type::event_type* event, const bool& logarithm) const
        {
            Eigen::VectorXd p = Eigen::VectorXd::Zero(this->get_nb_states());
            for(typename std::vector< D* >::const_iterator it = this->_observations.cbegin(), it_end = this->_observations.cend(); it != it_end; ++it)
            { p[distance(this->_observations.cbegin(), it)] = log(this->_pi[distance(this->_observations.cbegin(), it)]) + (*it)->probability(event, true); }
            double max = p.maxCoeff();
            for(Index index = 0, max_index = p.size(); index < max_index; ++index)
            {
                if(boost::math::isfinite(p[index]))
                { p[index] = p[index] - max; }
            }
            if(!logarithm)
            {
                for(Index index = 0, max_index = p.size(); index < max_index; ++index)
                {
                    if(boost::math::isfinite(p[index]))
                    { p[index] = exp(p[index]); }
                    else
                    { p[index] = 0.; }
                }
                p = p / p.sum();
            }
            return p;
        }

    template<class D>
        Index MixtureDistribution< D >::assignement(const typename D::data_type::event_type* event) const
        {
            Eigen::VectorXd p = posterior(event, false);
            Index index;
            p.maxCoeff(&index);
            return index;
        }
        
    template<class D>
        double MixtureDistribution< D >::uncertainty(const typename D::data_type::event_type* event) const
        {
            double entropy = 0.;
            Eigen::VectorXd p = posterior(event, true);
            for(Index index = 0, max_index = p.size(); index < max_index; ++index)
            {
                if(boost::math::isfinite(p[index]))
                { entropy -= exp(p[index]) * p[index]; }
            }
            return entropy;
        }

    template<class D>
        double MixtureDistribution< D >::uncertainty(const typename D::data_type& data) const
        {
            double entropy = 0.;
            std::unique_ptr< typename D::data_type::Generator > generator = data.generator();
            while(generator->is_valid())
            {
                entropy += generator->weight() * uncertainty(generator->event());
                ++(*generator);
            }
            return entropy;
        }

    template<class D>
        void MixtureDistribution< D >::init(const std::vector< D* > observations, const Eigen::VectorXd& pi)
        {
            _observations.resize(observations.size());
            for(Index index = 0, max_index = observations.size(); index < max_index; ++index)
            { _observations[index] = static_cast< D* >(observations[index]->copy().release()); }
            set_pi(pi);
        }

    template<class D>
        void MixtureDistribution< D >::init(const MixtureDistribution< D >& mixture)
        {
            _observations.resize(mixture._observations.size());
            for(Index index = 0, max_index = mixture._observations.size(); index < max_index; ++index)
            { _observations[index] = static_cast< D* >(mixture._observations[index]->copy().release()); }
            _pi = mixture._pi;
        } 

     template<class D>
        UnivariateMixtureDistribution< D >::UnivariateMixtureDistribution() : MixtureDistribution < D >()
        {}

    template<class D>
        UnivariateMixtureDistribution< D >::~UnivariateMixtureDistribution()
        {} 

    template<class D>
        double UnivariateMixtureDistribution< D >::ldf(const typename D::event_type::value_type& value) const
        { return log(pdf(value)); }

    template<class D>
        double UnivariateMixtureDistribution< D >::pdf(const typename D::event_type::value_type& value) const
        {
            double p = 0.;
            for(Index index = 0, max_index = this->get_nb_states(); index < max_index; ++index)
            { p += this->_pi[index] * this->_observations[index]->pdf(value); }
            return p;
        }

    template<class D>
        std::unique_ptr< UnivariateEvent > UnivariateMixtureDistribution< D >::simulate() const
        {
            double cp = this->_pi[0], sp = boost::uniform_01<boost::mt19937&>(__impl::get_random_generator())();
            Index index = 0, max_index = this->get_nb_states();
            while(cp < sp && index < max_index)
            {
                ++index;
                cp += this->_pi[index];
            }
            return this->_observations[index]->simulate();
        }

    template<class D>
        QuantitativeUnivariateMixtureDistribution< D >::QuantitativeUnivariateMixtureDistribution() : UnivariateMixtureDistribution < D >()
        {}

    template<class D>
        QuantitativeUnivariateMixtureDistribution< D >::~QuantitativeUnivariateMixtureDistribution()
        {} 

    template<class D>
        double QuantitativeUnivariateMixtureDistribution< D >::cdf(const typename D::event_type::value_type& value) const
        {
            double cp = 0;
            for(Index index = 0, max_index = this->get_nb_states(); index < max_index; ++index)
            { cp += this->_pi[index] * this->_observations[index]->cdf(value); }
            return cp;
        }

    template<class D>
        double QuantitativeUnivariateMixtureDistribution< D >::get_mean() const
        {
            double mean = 0;
            for(Index index = 0, max_index = this->get_nb_states(); index < max_index; ++index)
            { mean += this->_pi[index] * this->_observations[index]->get_mean(); }
            return mean;
        }

    template<class D>
        double QuantitativeUnivariateMixtureDistribution< D >::get_variance() const
        {
            double mean = get_mean(), variance = 0;
            for(Index index = 0, max_index = this->get_nb_states(); index < max_index; ++index)
            { variance += this->_pi[index] * (pow(this->_observations[index]->get_mean() - mean, 2) + this->_observations[index]->get_variance()); }
            return variance;
        }
 
     template<class D>
        MultivariateMixtureDistribution< D >::MultivariateMixtureDistribution(const std::vector< D* > observations, const Eigen::VectorXd& pi)
        {
            this->init(observations, pi);
            typename std::vector< D* >::const_iterator it = observations.cbegin(), it_end = observations.cend();
            Index nb_components = (*it)->get_nb_components();
            ++it;
            while(it != it_end)
            {
                if((*it)->get_nb_components() != nb_components)
                { throw parameter_error("observations", "not same number of components"); }
                ++it;
            }

        }

    template<class D>
        MultivariateMixtureDistribution< D >::MultivariateMixtureDistribution(const MultivariateMixtureDistribution< D >& mixture)
        { this->init(mixture); } 

    template<class D>
        MultivariateMixtureDistribution< D >::~MultivariateMixtureDistribution()
        {} 

    template<class D>
        void MultivariateMixtureDistribution< D >::set_observation(const Index& index, const D& observation)
        { 
            if(observation.get_nb_components() != get_nb_components())
            { throw parameter_error("observation", "not same number of components"); }
            MixtureDistribution< D >::set_observation(index, observation);
        }

    template<class D>
        Index MultivariateMixtureDistribution< D >::get_nb_components() const
        { return this->_observations.back()->get_nb_components(); }

    template<class D>
        double MultivariateMixtureDistribution< D >::probability(const MultivariateEvent* event, const bool& logarithm) const
        {
            double p = 0.;
            for(Index index = 0, max_index = this->get_nb_states(); index < max_index; ++index)
            { p += this->_pi[index] * this->_observations[index]->probability(event, false); }
            if(logarithm)
            { p = log(p); }
            return p;
        }

    template<class D>
        std::unique_ptr< MultivariateEvent > MultivariateMixtureDistribution< D >::simulate() const
        {
            double cp = this->_pi[0], sp = boost::uniform_01<boost::mt19937&>(__impl::get_random_generator())();
            Index index = 0, max_index = this->get_nb_states();
            while(cp < sp && index < max_index)
            {
                ++index;
                cp += this->_pi[index];
            }
            return this->_observations[index]->simulate();
        }
}

#endif
