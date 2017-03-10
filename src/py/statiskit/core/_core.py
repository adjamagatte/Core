__all__ = []

# Import dependency decorator modules
import statiskit.stl._stl
import statiskit.linalg._linalg

# Import Boost.Python module
import __core

# Resolve scopes
__core.statiskit.MeanEstimation.Estimator = __core.statiskit._mean_estimation.Estimator
__core.statiskit.UnivariateData.Generator = __core.statiskit._univariate_data.Generator
__core.statiskit.UnivariateDistributionEstimation.Estimator = __core.statiskit._univariate_distribution_estimation.Estimator
__core.statiskit.MultivariateDistributionEstimation.Estimator = __core.statiskit._multivariate_distribution_estimation.Estimator
__core.statiskit.SizeError.size_type = __core.statiskit._size_error.size_type
__core.statiskit.MultivariateData.Generator = __core.statiskit._multivariate_data.Generator
__core.statiskit.VarianceEstimation.Estimator = __core.statiskit._variance_estimation.Estimator
__core.statiskit.CategoricalMultivariateDistributionEstimation.Estimator = __core.statiskit._categorical_multivariate_distribution_estimation.Estimator
__core.statiskit.NaturalVarianceEstimation.Estimator = __core.statiskit._natural_variance_estimation.Estimator
__core.statiskit.NaturalMeanEstimation.Estimator = __core.statiskit._natural_mean_estimation.Estimator
__core.statiskit.ContinuousMultivariateDistributionEstimation.Estimator = __core.statiskit._continuous_multivariate_distribution_estimation.Estimator
__core.statiskit.ContinuousUnivariateDistributionEstimation.Estimator = __core.statiskit._continuous_univariate_distribution_estimation.Estimator
__core.statiskit.DiscreteMultivariateDistributionEstimation.Estimator = __core.statiskit._discrete_multivariate_distribution_estimation.Estimator
__core.statiskit.CategoricalUnivariateDistributionEstimation.Estimator = __core.statiskit._categorical_univariate_distribution_estimation.Estimator
__core.statiskit.DiscreteUnivariateDistributionEstimation.Estimator = __core.statiskit._discrete_univariate_distribution_estimation.Estimator
__core.statiskit.RegularUnivariateHistogramDistributionSlopeHeuristicSelection.Estimator = __core.statiskit._regular_univariate_histogram_distribution_slope_heuristic_selection.Estimator
__core.statiskit.BinomialDistributionMMEstimation.Estimator = __core.statiskit._binomial_distribution_mm_estimation.Estimator
__core.statiskit.NegativeBinomialDistributionMMEstimation.Estimator = __core.statiskit._negative_binomial_distribution_mm_estimation.Estimator
__core.statiskit.PoissonDistributionMLEstimation.Estimator = __core.statiskit._poisson_distribution_ml_estimation.Estimator
__core.statiskit.IrregularUnivariateHistogramDistributionSlopeHeuristicSelection.Estimator = __core.statiskit._irregular_univariate_histogram_distribution_slope_heuristic_selection.Estimator
__core.statiskit.NormalDistributionMLEstimation.Estimator = __core.statiskit._normal_distribution_ml_estimation.Estimator
__core.statiskit._UnivariateFrequencyDistributionEstimation_0ec596bf98a6521c9bf30c96dc0ff201.Estimator = __core.statiskit.__univariate_frequency_distribution_estimation_0ec596bf98a6521c9bf30c96dc0ff201.Estimator
__core.statiskit.UnivariateHistogramDistributionEstimation.Estimator = __core.statiskit._univariate_histogram_distribution_estimation.Estimator
__core.statiskit._UnivariateFrequencyDistributionEstimation_67548b1b39c8521c8f630ca5b4d502c4.Estimator = __core.statiskit.__univariate_frequency_distribution_estimation_67548b1b39c8521c8f630ca5b4d502c4.Estimator
__core.statiskit._OptimizationEstimation_66ba790876ea5d25be923643f217b67a.Estimator = __core.statiskit.__optimization_estimation_66ba790876ea5d25be923643f217b67a.Estimator
__core.statiskit._OptimizationEstimation_6ab41d8aa0095175b6da7190fc953a97.Estimator = __core.statiskit.__optimization_estimation_6ab41d8aa0095175b6da7190fc953a97.Estimator
__core.statiskit.NegativeBinomialDistributionMLEstimation.Estimator = __core.statiskit._negative_binomial_distribution_ml_estimation.Estimator
__core.statiskit.BinomialDistributionMLEstimation.Estimator = __core.statiskit._binomial_distribution_ml_estimation.Estimator

# Group template specializations
__core.statiskit._IndependentMultivariateDistribution = (__core.statiskit._IndependentMultivariateDistribution_09231b7789ec5a69ad76d8618a8abb42, __core.statiskit._IndependentMultivariateDistribution_0234ba92b21c578b96baa200aec8212e, __core.statiskit._IndependentMultivariateDistribution_d795e2008d505a07a0b1806c150970f3, __core.statiskit._IndependentMultivariateDistribution_fcd0d238df3b57e18bea85b9cc6689bd)
__core.statiskit._IndependentMultivariateDistributionEstimation = (__core.statiskit._IndependentMultivariateDistributionEstimation_b456405435355475acaf2df289118e69, __core.statiskit._IndependentMultivariateDistributionEstimation_0dde50813a6555f8aff9d4b5fa01376d, __core.statiskit._IndependentMultivariateDistributionEstimation_34e9a178ea5a5aebabb3b859d5a63048, __core.statiskit._IndependentMultivariateDistributionEstimation_625725874d5f5fde949f34e8f010537c)
__core.statiskit._SlopeHeuristicSelection = (__core.statiskit._SlopeHeuristicSelection_9ba0310efd9c520c8c9e6cb4ff8fb1a4)
__core.statiskit._LazyEstimation = (__core.statiskit._LazyEstimation_58ce030c450459a79803894a62868fcd, __core.statiskit._LazyEstimation_04e2de3b1dbe5c209454d3480782d464, __core.statiskit._LazyEstimation_281a291cf9465a1e9af25cbee1cf5bad, __core.statiskit._LazyEstimation_3312cf49434759ee93e09764ddc76065, __core.statiskit._LazyEstimation_3fd024ee203f5dbeb9a9f3392ca1db8c, __core.statiskit._LazyEstimation_40c631b5a67d5748bbfdeaa0beedb4e0, __core.statiskit._LazyEstimation_49e18be963b9503a942009b04ff7e676, __core.statiskit._LazyEstimation_8946cbc54c235b72b2e100c2785ce4c3, __core.statiskit._LazyEstimation_8e29fff483a15137a2f1901b2e8a7d98, __core.statiskit._LazyEstimation_db760ff53e0e5dca8e558b09ed12163c, __core.statiskit._LazyEstimation_ef99412d87545a1391d9c6cbb66e08e8, __core.statiskit._LazyEstimation_f10976bafd925ac0bb44461ce1017322)
__core.statiskit._UnivariateFrequencyDistributionEstimation = (__core.statiskit._UnivariateFrequencyDistributionEstimation_0ec596bf98a6521c9bf30c96dc0ff201, __core.statiskit._UnivariateFrequencyDistributionEstimation_67548b1b39c8521c8f630ca5b4d502c4)
__core.statiskit._OptimizationEstimation = (__core.statiskit._OptimizationEstimation_66ba790876ea5d25be923643f217b67a, __core.statiskit._OptimizationEstimation_6ab41d8aa0095175b6da7190fc953a97)
__core.statiskit._ActiveEstimation = (__core.statiskit._ActiveEstimation_1e6a1a608df4519ab51780153780f30d, __core.statiskit._ActiveEstimation_15354690391e57a484015b3b2eb62c1c, __core.statiskit._ActiveEstimation_19ee605677815ce58ebdc169d44e3d8c, __core.statiskit._ActiveEstimation_20f43f33e75f5ed8baf3e95be100740a, __core.statiskit._ActiveEstimation_281622f2e8fd576dae1b13441146f58b, __core.statiskit._ActiveEstimation_36c99cd43c5c5fb8abeb0fd1ca103ac8, __core.statiskit._ActiveEstimation_66ea0b28087057f5abc6f26dadfb4c15, __core.statiskit._ActiveEstimation_9603102166305920b6c85e3416150e99, __core.statiskit._ActiveEstimation_cd878d00f23b5752bfaffc1e4a81de92, __core.statiskit._ActiveEstimation_ea65f72f6e415ac79babe4873fd858fe, __core.statiskit._ActiveEstimation_f490fbe6298d5af89adf9098e57be3d4, __core.statiskit._ActiveEstimation_f7ee2d0fd855596a8c0abbb2be320618)
__core.statiskit._QuantitativeUnivariateFrequencyDistribution = (__core.statiskit._QuantitativeUnivariateFrequencyDistribution_1cfe57e82ce352e4b80ae7c44a661b01, __core.statiskit._QuantitativeUnivariateFrequencyDistribution_839b61ecb09d54819eb38cf69dde50bb)
__core.statiskit._IntervalCensoredEvent = (__core.statiskit._IntervalCensoredEvent_a766c9930af25f8f90f6e118f2ca75d5, __core.statiskit._IntervalCensoredEvent_fb8f1cea3a695accb39f019b3fbd2247)
__core.statiskit._CensoredEvent = (__core.statiskit._CensoredEvent_42c73f7b760d584f96ee42693c708651, __core.statiskit._CensoredEvent_48d411e601675e49961eaa93daeb1835, __core.statiskit._CensoredEvent_fa5e2baabb585a5e93632d2563d88b33)
__core.statiskit._LeftCensoredEvent = (__core.statiskit._LeftCensoredEvent_01ddd51bfe2a5d97b4620b9e2d14360e, __core.statiskit._LeftCensoredEvent_aa6e0b250759574eb903a6b783b18053)
__core.statiskit._UnivariateFrequencyDistribution = (__core.statiskit._UnivariateFrequencyDistribution_0db25688c9bf5a57b1d944dcc1a3b7f2, __core.statiskit._UnivariateFrequencyDistribution_a4463e49d7865a6497ec20612e342cbe, __core.statiskit._UnivariateFrequencyDistribution_bf5b68f25d1f5ab9ad2c936351edf740)
__core.statiskit._RightCensoredEvent = (__core.statiskit._RightCensoredEvent_1ec5dee4e7cb5437b83047021c0ca63f, __core.statiskit._RightCensoredEvent_4f25ed2b505752de8ee46e2e6aa83af6)
__core.statiskit._ElementaryEvent = (__core.statiskit._ElementaryEvent_2f72e6e6db9a5498beee75dbafdc6393, __core.statiskit._ElementaryEvent_85e5d9c1d86a574d8623fe4bb0164527, __core.statiskit._ElementaryEvent_9981958281625422b3b46cea8ec85a6d)
__core.std._Vector = (__core.std._Vector_160b713997e259caa9b19848803d29f1)

# Define aliases
__core.statiskit.UnivariateData.SampleSpaceType = __core.statiskit.UnivariateSampleSpace
__core.statiskit.UnivariateData.EventType = __core.statiskit.UnivariateEvent
__core.statiskit.UnivariateDistributionEstimation.DataType = __core.statiskit.UnivariateData
__core.statiskit.UnivariateDistributionEstimation.EstimatedType = __core.statiskit.UnivariateDistribution
__core.statiskit.UnivariateDistributionEstimation.Estimator.EstimationType = __core.statiskit.UnivariateDistributionEstimation
__core.statiskit.MultivariateDistributionEstimation.DataType = __core.statiskit.MultivariateData
__core.statiskit.MultivariateDistributionEstimation.EstimatedType = __core.statiskit.MultivariateDistribution
__core.statiskit.MultivariateDistributionEstimation.MarginalType = __core.statiskit.UnivariateDistributionEstimation
__core.statiskit.MultivariateDistribution.MarginalType = __core.statiskit.UnivariateDistribution
__core.statiskit.MultivariateDistributionEstimation.Estimator.EstimationType = __core.statiskit.MultivariateDistributionEstimation
__core.statiskit.MultivariateDistributionEstimation.Estimator.MarginalType = __core.statiskit.UnivariateDistributionEstimation
__core.statiskit.UnivariateConditionalDistribution.ResponseType = __core.statiskit.UnivariateDistribution
__core.statiskit.MultivariateData.SampleSpaceType = __core.statiskit.MultivariateSampleSpace
__core.statiskit.MultivariateData.EventType = __core.statiskit.MultivariateEvent
__core.statiskit.CategoricalElementaryEvent = __core.statiskit._ElementaryEvent_2f72e6e6db9a5498beee75dbafdc6393
__core.statiskit.CategoricalUnivariateDistributionLazyEstimation = __core.statiskit._LazyEstimation_3312cf49434759ee93e09764ddc76065
__core.statiskit.MixedIndependentMultivariateDistributionEstimation = __core.statiskit._IndependentMultivariateDistributionEstimation_b456405435355475acaf2df289118e69
__core.statiskit.ContinuousRightCensoredEvent = __core.statiskit._RightCensoredEvent_4f25ed2b505752de8ee46e2e6aa83af6
__core.statiskit.DiscreteUnivariateFrequencyDistributionEstimator = __core.statiskit._UnivariateFrequencyDistributionEstimation_0ec596bf98a6521c9bf30c96dc0ff201.Estimator
__core.statiskit.ContinuousUnivariateFrequencyDistributionEstimation = __core.statiskit._UnivariateFrequencyDistributionEstimation_67548b1b39c8521c8f630ca5b4d502c4
__core.statiskit.ContinuousElementaryEvent = __core.statiskit._ElementaryEvent_9981958281625422b3b46cea8ec85a6d
__core.statiskit.ContinuousUnivariateFrequencyDistribution = __core.statiskit._QuantitativeUnivariateFrequencyDistribution_1cfe57e82ce352e4b80ae7c44a661b01
__core.statiskit.CategoricalIndependentMultivariateDistributionEstimation = __core.statiskit._IndependentMultivariateDistributionEstimation_0dde50813a6555f8aff9d4b5fa01376d
__core.statiskit.ContinuousUnivariateFrequencyDistributionEstimator = __core.statiskit._UnivariateFrequencyDistributionEstimation_67548b1b39c8521c8f630ca5b4d502c4.Estimator
__core.statiskit.CategoricalUnivariateDistributionActiveEstimation = __core.statiskit._ActiveEstimation_20f43f33e75f5ed8baf3e95be100740a
__core.statiskit.DiscreteLeftCensoredEvent = __core.statiskit._LeftCensoredEvent_01ddd51bfe2a5d97b4620b9e2d14360e
__core.statiskit.CategoricalIndependentMultivariateDistribution = __core.statiskit._IndependentMultivariateDistribution_fcd0d238df3b57e18bea85b9cc6689bd
__core.statiskit.DiscreteElementaryEvent = __core.statiskit._ElementaryEvent_85e5d9c1d86a574d8623fe4bb0164527
__core.statiskit.DiscreteUnivariateFrequencyDistributionEstimation = __core.statiskit._UnivariateFrequencyDistributionEstimation_0ec596bf98a6521c9bf30c96dc0ff201
__core.statiskit.DiscreteRightCensoredEvent = __core.statiskit._RightCensoredEvent_1ec5dee4e7cb5437b83047021c0ca63f
__core.statiskit.DiscreteIndependentMultivariateDistribution = __core.statiskit._IndependentMultivariateDistribution_0234ba92b21c578b96baa200aec8212e
__core.statiskit.ContinuousCensoredEvent = __core.statiskit._CensoredEvent_fa5e2baabb585a5e93632d2563d88b33
__core.statiskit.ContinuousLeftCensoredEvent = __core.statiskit._LeftCensoredEvent_aa6e0b250759574eb903a6b783b18053
__core.statiskit.ContinuousIndependentMultivariateDistributionEstimation = __core.statiskit._IndependentMultivariateDistributionEstimation_34e9a178ea5a5aebabb3b859d5a63048
__core.statiskit.DiscreteCensoredEvent = __core.statiskit._CensoredEvent_48d411e601675e49961eaa93daeb1835
__core.statiskit.MixedIndependentMultivariateDistribution = __core.statiskit._IndependentMultivariateDistribution_09231b7789ec5a69ad76d8618a8abb42
__core.statiskit.DiscreteIndependentMultivariateDistributionEstimation = __core.statiskit._IndependentMultivariateDistributionEstimation_625725874d5f5fde949f34e8f010537c
__core.statiskit.DiscreteUnivariateFrequencyDistribution = __core.statiskit._QuantitativeUnivariateFrequencyDistribution_839b61ecb09d54819eb38cf69dde50bb
__core.statiskit.DiscreteIntervalCensoredEvent = __core.statiskit._IntervalCensoredEvent_fb8f1cea3a695accb39f019b3fbd2247
__core.statiskit.ContinuousIntervalCensoredEvent = __core.statiskit._IntervalCensoredEvent_a766c9930af25f8f90f6e118f2ca75d5
__core.statiskit.CategoricalCensoredEvent = __core.statiskit._CensoredEvent_42c73f7b760d584f96ee42693c708651
__core.statiskit.ContinuousIndependentMultivariateDistribution = __core.statiskit._IndependentMultivariateDistribution_d795e2008d505a07a0b1806c150970f3
__core.statiskit.DiscreteUnivariateDistribution.EventType = __core.statiskit.DiscreteEvent
__core.statiskit.ContinuousUnivariateConditionalDistribution.ResponseType = __core.statiskit.ContinuousUnivariateDistribution
__core.statiskit.CategoricalUnivariateConditionalDistribution.ResponseType = __core.statiskit.CategoricalUnivariateDistribution
__core.statiskit.DiscreteMultivariateDistribution.MarginalType = __core.statiskit.DiscreteUnivariateDistribution
__core.statiskit.DiscreteUnivariateConditionalDistribution.ResponseType = __core.statiskit.DiscreteUnivariateDistribution
__core.statiskit.DiscreteEvent.DistributionType = __core.statiskit.DiscreteUnivariateDistribution
__core.statiskit.ContinuousUnivariateDistribution.EventType = __core.statiskit.ContinuousEvent
__core.statiskit.ContinuousMultivariateDistribution.MarginalType = __core.statiskit.ContinuousUnivariateDistribution
__core.statiskit.ContinuousEvent.DistributionType = __core.statiskit.ContinuousUnivariateDistribution
__core.statiskit.DiscreteMultivariateDistributionEstimation.MarginalType = __core.statiskit.DiscreteUnivariateDistributionEstimation
__core.statiskit.CategoricalMultivariateDistribution.MarginalType = __core.statiskit.CategoricalUnivariateDistribution
__core.statiskit.CategoricalEvent.ValueType = statiskit.stl.__stl.std._BasicString_448c20257e485acda59dc59305fceb58
__core.statiskit.CategoricalEvent.DistributionType = __core.statiskit.CategoricalUnivariateDistribution
__core.statiskit.CategoricalUnivariateDistribution.EventType = __core.statiskit.CategoricalEvent
__core.statiskit.CategoricalMultivariateDistributionEstimation.MarginalType = __core.statiskit.CategoricalUnivariateDistributionEstimation
__core.statiskit.ContinuousMultivariateDistributionEstimation.MarginalType = __core.statiskit.ContinuousUnivariateDistributionEstimation
