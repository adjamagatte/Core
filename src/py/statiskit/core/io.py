##################################################################################
#                                                                                #
# StatisKit-CoreThis software is distributed under the CeCILL-C license. You     #
# should have received a copy of the legalcode along with this work. If not, see #
# <http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html>.                 #
#                                                                                #
##################################################################################

import _core

__all__ = ['read_csv', 'from_list', 'from_pandas']

import warnings
from tempfile import NamedTemporaryFile
import os

from controls import controls
from data import UnivariateDataFrame, MultivariateDataFrame
from sample_space import NominalSampleSpace

def read_csv(filepath, sep=None, header=False, **kwargs):
    """
    """
    if sep and not isinstance(sep, basestring):
        raise TypeError('\'sep\' parameter')
    with open(filepath, 'r') as filehandler:
        lines = filehandler.readlines()
    if header:
        names = [name.strip().strip('"').strip("'").strip() for name in lines.pop(0).split(sep)]
        data = [[] for name in names]
    else:
        data = [[] for event in lines[0].split(sep)]
    for line in lines:
        for index, event in enumerate(line.split(sep)):
            data[index].append(event.strip().strip('"').strip("'"))
    data = from_list(*data, **kwargs)
    if header:
        if isinstance(data, UnivariateDataFrame):
            data.name = names.pop()
        elif isinstance(data, MultivariateDataFrame):
                for i, j in enumerate(names):
                    data.components[i].name = j
    return data

def write_csv(data, filepath, sep=' ', header=False, censored=True):
    """
    """
    if not isinstance(data, MultivariateDataFrame):
        raise TypeError('\'data\' parameter')
    if not isinstance(sep, basestring):
        raise TypeError('\'sep\' parameter')
    with open(filepath, 'w') as filehandler:
        if header:
            filehandler.write(sep.join(component.name for component in data.components)+'\n')
        if censored:
            for mevent in data.events:
                line = []
                for uevent in mevent:
                    if uevent is None:
                        line.append('?')
                    else:
                        if isinstance(uevent, _core.__core.statiskit._ElementaryEvent):
                            line.append(str(uevent.value))
                        elif isinstance(uevent, _core.__core.statiskit._SetCensoredEvent):
                            line.append('{' + ', '.join(str(value) for value in uevent.values) + '}')
                        elif isinstance(uevent, _core.__core.statiskit._LeftCensoredEvent):
                            line.append(str(uevent.upper_bound)+'-')
                        elif isinstance(uevent, _core.__core.statiskit._RightCensoredEvent):
                            line.append(str(uevent.lower_bound)+'+')
                        elif isinstance(uevent, _core.__core.statiskit._IntervalCensoredEvent):
                            if isinstance(uevent, _core.__core.statiskit.DiscreteEvent):
                                line.append('[' + str(uevent.lower_bound) + ', ' + str(uevent.upper_bound)+']')
                            elif isinstance(uevent, _core.__core.statiskit.ContinuousEvent):
                                line.append(']' + str(uevent.lower_bound) + ', ' + str(uevent.upper_bound)+'[')
                            else:
                                raise NotImplementedError
                        else:
                            raise NotImplementedError
                filehandler.write(sep.join(line)+'\n')
        else:
            for mevent in data.events:
                line = []
                for uevent in mevent:
                    if uevent is None or not isinstance(uevent, __statiskit_core._ElementaryEvent):
                        warnings.warn('\'data\' parameter contains non-atomic event')
                        line.append('?')
                    else:
                        line.append(str(uevent.value))
                filehandler.write(sep.join(line) + '\n')

MultivariateDataFrame.write_csv = write_csv
del write_csv

def from_list(*data, **kwargs):
    if 'sample_spaces' in kwargs:
        sample_spaces = kwargs.pop('sample_spaces')
    else:
        sample_spaces = []
        for _data in data:
            nbstr = 0
            nbint = 0
            nbflt = 0
            for event in _data:
                try:
                    controls.ZZ(event)
                    nbint += 1
                except:
                    try:
                        controls.RR(event)
                        nbflt += 1
                    except:
                        nbstr += 1
            if nbstr > nbint + nbflt:
                sample_spaces.append(NominalSampleSpace(_data))
            elif nbint > nbstr + nbflt:
                sample_spaces.append(controls.ZZ)
            elif nbflt > nbstr + nbint:
                sample_spaces.append(controls.RR)
            else:
                raise NotImplementedError("cannot determine sample space")
    if len(sample_spaces) == 1:
        sample_space = sample_spaces.pop()
        dataframe = UnivariateDataFrame(sample_space)
        for event in data[-1]:
            dataframe.add_event(sample_space(event))
    else:
        dataframe = MultivariateDataFrame()
        for index, sample_space in enumerate(sample_spaces):
            _dataframe = UnivariateDataFrame(sample_space)
            for event in data[index]:
                _dataframe.add_event(sample_space(event))
            dataframe.add_component(_dataframe)
    return dataframe

def from_pandas(data):
    """
    """
    filehandler = NamedTemporaryFile(delete=False)
    filehandler.close()
    data.to_csv(filehandler.name, sep=';', na_rep='?', index=False)
    data = read_csv(filehandler.name, header=True, sep=';')
    os.unlink(filehandler.name)
    return data

def to_pandas(data):
    """
    """
    filehandler = NamedTemporaryFile(delete=False)
    filehandler.close()
    write_csv(data, filehandler.name, sep=';', header=True, censored=False)
    return read_csv(filehandler.name, sep=';', header=0, na_values=['?', ''])

MultivariateDataFrame.to_pandas = to_pandas
del to_pandas
