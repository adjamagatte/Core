##################################################################################
#                                                                                #
# StatisKit-CoreThis software is distributed under the CeCILL-C license. You     #
# should have received a copy of the legalcode along with this work. If not, see #
# <http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html>.                 #
#                                                                                #
##################################################################################

from functools import wraps

import statiskit.core._core
from statiskit.core.__core.statiskit import _LazyEstimation, _ActiveEstimation,\
        UnivariateDistributionEstimation,\
        CategoricalUnivariateDistributionEstimation,\
        DiscreteUnivariateDistributionEstimation, DiscreteUnivariateFrequencyDistributionEstimation,\
        ContinuousUnivariateDistributionEstimation, ContinuousUnivariateFrequencyDistributionEstimation, NormalDistributionMLEstimation, UnivariateHistogramDistributionEstimation, RegularUnivariateHistogramDistributionSlopeHeuristicEstimation, IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation,\
        MultivariateDistributionEstimation, _IndependentMultivariateDistributionEstimation, MixedIndependentMultivariateDistributionEstimation,\
        CategoricalMultivariateDistributionEstimation, CategoricalIndependentMultivariateDistributionEstimation,\
        DiscreteMultivariateDistributionEstimation, DiscreteIndependentMultivariateDistributionEstimation,\
        ContinuousMultivariateDistributionEstimation, ContinuousIndependentMultivariateDistributionEstimation

from statiskit.core.event import outcome_type
from statiskit.core.data_frame import UnivariateDataFrame, MultivariateDataFrame
from statiskit.core.slope_heuristic import Proxy
from statiskit.core.tools import unused_warning

__all__ = ['frequency_estimation',
           'normal_estimation', 'histogram_estimation',
           'independent_estimation']

UnivariateDistributionEstimation.estimated = property(UnivariateDistributionEstimation.get_estimated)
del UnivariateDistributionEstimation.get_estimated

def statiskit_active_estimation_decorator(cls):

    cls.data_frame = property(cls.get_data_frame)
    del cls.get_data_frame

    def pdf_plot(self, axes=None, fmt=('|', '-'), color=('b', 'r'), alpha=(1., 1.), norm=False, **kwargs):
        axes = self.data_frame.pdf_plot(axes=axes, fmt=fmt[0], color=color[0], alpha=alpha[0], norm=norm, **kwargs.pop('data_frame', dict()))
        if isinstance(norm, bool):
            if not norm:
                norm = self.data_frame.compute_total(True)
            else:
                norm = 1.
        return self.estimated.pdf_plot(axes=axes, fmt=fmt[1], color=color[1], alpha=alpha[1], norm=norm, **kwargs.pop('estimated', dict()))

    cls.pdf_plot = pdf_plot
    del pdf_plot

for cls in _ActiveEstimation:
    statiskit_active_estimation_decorator(cls)

def frequency_estimation(data, **kwargs):
    if isinstance(data, UnivariateDataFrame) or isinstance(data, basestring) and data == 'univariate'[:len(data)]:
        if isinstance(data, UnivariateDataFrame):
            outcome = data.sample_space.outcome
        else:
            outcome = kwargs.pop('outcome')
            if not isinstance(outcome, outcome_type):
                raise TypeError('\'outcome\' parameter')
        if outcome == outcome_type.CATEGORICAL:
            estimator = CategoricalUnivariateDistributionEstimation.Estimator()
        elif outcome == outcome_type.DISCRETE:
            estimator = DiscreteUnivariateFrequencyDistributionEstimation.Estimator()
        elif outcome == outcome_type.CONTINUOUS:
            estimator = ContinuousUnivariateFrequencyDistributionEstimation.Estimator()
        else:
            raise ValueError('\'outcome\' parameter')
    else:
        raise NotImplementedError
    for attr in kwargs.keys():
        if hasattr(estimator, attr):
            setattr(estimator, kwargs.pop(attr))
    if isinstance(data, basestring):
        unused_warning(**kwargs)
        return estimator
    else:
        lazy = kwargs.pop('lazy', False)
        unused_warning(**kwargs)
        return estimator(data, lazy)

class ModelsProxy(Proxy):
    pass

def wrapper(f):
    @wraps(f)
    def __getitem__(self, index):
        if isinstance(index, slice):
            return [self[index] for index in xrange(*index.indices(len(self)))]
        else:
            if index < 0:
                index += len(self)
            if not 0 <= index < len(self):
                raise IndexError
            return f(self.obj, index)
    return __getitem__

ModelsProxy.__getitem__ = wrapper(RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.get_model)
RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.models = property(ModelsProxy)
ModelsProxy.__getitem__ = wrapper(IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.get_model)
IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.models = property(ModelsProxy)

def normal_estimation(algo='mle', **kwargs):
    """
    """
    if algo.lower() == 'mle'[:len(algo)]:
        estimator = NormalDistributionMLEstimation.Estimator()
    else:
        raise ValueError('\'estimator\' parameter')
    for attr in kwargs.keys():
        if hasattr(estimator, attr):
            setattr(estimator, kwargs.pop(attr))
    if 'data' in kwargs:
        data, lazy = kwargs.pop('data'), kwargs.pop('lazy', False)
        unused_warning(**kwargs)
        return estimator(data, lazy)
    else:
        return estimator

UnivariateHistogramDistributionEstimation.Estimator.nb_bins = property(UnivariateHistogramDistributionEstimation.Estimator.get_nb_bins, UnivariateHistogramDistributionEstimation.Estimator.set_nb_bins)
del UnivariateHistogramDistributionEstimation.Estimator.get_nb_bins, UnivariateHistogramDistributionEstimation.Estimator.set_nb_bins

IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.max_bins = property(IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.get_max_bins, IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.set_max_bins)
del IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.get_max_bins, IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.set_max_bins

RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.max_bins = property(RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.get_max_bins, RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.set_max_bins)
del RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.get_max_bins, RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator.set_max_bins

def histogram_estimation(data, **kwargs):
    """
    """
    if isinstance(data, UnivariateDataFrame) or isinstance(data, basestring) and data == 'univariate'[:len(data)]:
        algorithm = kwargs.pop('algorithm', 'she')
        if algorithm is None:
            estimator = UnivariateHistogramDistributionEstimation.Estimator()
        else:
            algorithm = algorithm.lower()
            if algorithm == 'she'[:len(algorithm)]:
                if kwargs.pop('regular', not kwargs.pop('irregular', False)):
                    estimator = RegularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator()
                else:
                    estimator = IrregularUnivariateHistogramDistributionSlopeHeuristicEstimation.Estimator()
            else:
                raise ValueError('\'algorithm\' parameter')
    else:
        raise NotImplementedError
    for attr in kwargs.keys():
        if hasattr(estimator, attr):
            setattr(estimator, attr, kwargs.pop(attr))
    if isinstance(data, basestring):
        unused_warning(**kwargs)
        return estimator
    else:
        lazy = kwargs.pop('lazy', False)
        unused_warning(**kwargs)
        return estimator(data, lazy)

MultivariateDistributionEstimation.estimated = property(MultivariateDistributionEstimation.get_estimated)
del MultivariateDistributionEstimation.get_estimated

def statiskit_independent_multivariate_distribution_estimation_decorator(cls):

    cls.marginals = property(cls.get_marginals)
    del cls.get_marginals

for cls in _IndependentMultivariateDistributionEstimation:
    statiskit_independent_multivariate_distribution_estimation_decorator(cls)

def independent_estimation(data, **kwargs):
    if isinstance(data, MultivariateDataFrame):
        if all(variable.sample_space.outcome is outcome_type.CATEGORICAL for variable in data.variables):
            estimator = CategoricalIndependentMultivariateDistributionEstimation.Estimator()
        elif all(variable.sample_space.outcome is outcome_type.DISCRETE for variable in data.variables):
            estimator = DiscreteIndependentMultivariateDistributionEstimation.Estimator()
        elif all(variable.sample_space.outcome is outcome_type.CONTINUOUS for variable in data.variables):
            estimator = ContinuousIndependentMultivariateDistributionEstimation.Estimator()
        else:
            estimator = MixedIndependentMultivariateDistributionEstimation.Estimator()
    elif isinstance(data, outcome_type):
        if data is outcome_type.MIXED:
            estimator = MixedIndependentMultivariateDistributionEstimation.Estimator()
        elif data is outcome_type.CATEGORICAL:
            estimator = CategoricalIndependentMultivariateDistributionEstimation.Estimator()
        elif data is outcome_type.DISCRETE:
            estimator = DiscreteIndependentMultivariateDistributionEstimation.Estimator()
        elif data is outcome_type.CONTINUOUS:
            estimator = ContinuousIndependentMultivariateDistributionEstimation.Estimator()
        else:
            raise ValueError('\'data\' parameter')
    else:
        raise TypeError('\'data\' parameter')
    for attr in kwargs.keys():
        if hasattr(estimator, attr):
            setattr(estimator, attr, kwargs.pop(attr))
    if isinstance(data, MultivariateDataFrame):
        lazy = kwargs.pop('lazy', False)
        unused_warning(**kwargs)
        return estimator(data, lazy)
    else:
        unused_warning(**kwargs)
        return estimator
