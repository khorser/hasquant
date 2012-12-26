
/*  
 Copyright (C) 2004, 2005, 2006, 2007, 2008 Eric Ehlers
 
 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// This file was generated automatically by gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      gensrc/gensrc/stubs/stub.excel.register.file

#include <xlsdk/xlsdkdefines.hpp>

// register functions in category Sequencestatistics with Excel

void registerSequencestatistics(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSequenceStatistics"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlSequenceStatistics"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,Dimension,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SequenceStatistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSequenceStatistics2"),
            // parameter codes
            TempStrNoSize("\x09""CCPKPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlSequenceStatistics2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Dimension,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SequenceStatistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x3B""Sampled values. If omitted, an empty statistics is created."),
            TempStrNoSize("\x63""If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x24""qlSequenceStatisticsAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x24""qlSequenceStatisticsAverageShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the averaged shortfallness for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSequenceStatisticsCorrelation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlSequenceStatisticsCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the correlation Matrix for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSequenceStatisticsCovariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlSequenceStatisticsCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns the covariance Matrix for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlSequenceStatisticsDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlSequenceStatisticsDownsideDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""Returns the square root of the downside variance for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlSequenceStatisticsDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlSequenceStatisticsDownsideVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the variance of observations below zero for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlSequenceStatisticsErrorEstimate"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlSequenceStatisticsErrorEstimate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the error estimate on the mean value for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlSequenceStatisticsGaussianAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x2C""qlSequenceStatisticsGaussianAverageShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the averaged shortfallness for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlSequenceStatisticsGaussianPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x26""qlSequenceStatisticsGaussianPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""ObjectId,X,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the x-th percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlSequenceStatisticsGaussianPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x2B""qlSequenceStatisticsGaussianPotentialUpside"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the reciprocal of VAR at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlSequenceStatisticsGaussianShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x25""qlSequenceStatisticsGaussianShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the probability of missing the given target for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x27""qlSequenceStatisticsGaussianValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x27""qlSequenceStatisticsGaussianValueAtRisk"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the value-at-risk at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSequenceStatisticsInc"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlSequenceStatisticsInc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,Dimension,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class SequenceStatisticsInc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSequenceStatisticsInc2"),
            // parameter codes
            TempStrNoSize("\x09""CCPKPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlSequenceStatisticsInc2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Dimension,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class SequenceStatisticsInc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x3B""Sampled values. If omitted, an empty statistics is created."),
            TempStrNoSize("\x63""If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSequenceStatisticsKurtosis"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSequenceStatisticsKurtosis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the excess kurtosis for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSequenceStatisticsMax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlSequenceStatisticsMax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the maximum sample value for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSequenceStatisticsMean"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlSequenceStatisticsMean"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns the mean for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSequenceStatisticsMin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlSequenceStatisticsMin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the minimum sample value for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSequenceStatisticsPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1E""qlSequenceStatisticsPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""ObjectId,X,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the x-th percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlSequenceStatisticsPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x23""qlSequenceStatisticsPotentialUpside"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,Centile,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the reciprocal of VAR at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0C""the centile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSequenceStatisticsRegret"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1A""qlSequenceStatisticsRegret"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5A""Returns the variance of observations below target for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSequenceStatisticsSamples"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSequenceStatisticsSamples"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the number of samples collected for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlSequenceStatisticsSemiDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlSequenceStatisticsSemiDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x54""Returns the square root of the semivariance for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSequenceStatisticsSemiVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x20""qlSequenceStatisticsSemiVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the variance of observations below the mean for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSequenceStatisticsShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1D""qlSequenceStatisticsShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the probability of missing the given target for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSequenceStatisticsSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x18""qlSequenceStatisticsSize"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""Returns the size (sample dimensionality) for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSequenceStatisticsSkewness"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSequenceStatisticsSkewness"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the skewness for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlSequenceStatisticsStandardDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlSequenceStatisticsStandardDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the the standard deviation for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSequenceStatisticsValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1F""qlSequenceStatisticsValueAtRisk"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the value-at-risk at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSequenceStatisticsVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSequenceStatisticsVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the variance for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSequenceStatisticsWeightSum"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlSequenceStatisticsWeightSum"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the sum of data weights for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Sequencestatistics with Excel

void unregisterSequencestatistics(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSequenceStatistics"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlSequenceStatistics"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,Dimension,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SequenceStatistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlSequenceStatistics"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSequenceStatistics2"),
            // parameter codes
            TempStrNoSize("\x09""CCPKPPPL#"),
            // function display name
            TempStrNoSize("\x15""qlSequenceStatistics2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Dimension,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SequenceStatistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x3B""Sampled values. If omitted, an empty statistics is created."),
            TempStrNoSize("\x63""If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlSequenceStatistics2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x24""qlSequenceStatisticsAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x24""qlSequenceStatisticsAverageShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the averaged shortfallness for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlSequenceStatisticsAverageShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSequenceStatisticsCorrelation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1F""qlSequenceStatisticsCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the correlation Matrix for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlSequenceStatisticsCorrelation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSequenceStatisticsCovariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlSequenceStatisticsCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns the covariance Matrix for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlSequenceStatisticsCovariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlSequenceStatisticsDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlSequenceStatisticsDownsideDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""Returns the square root of the downside variance for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlSequenceStatisticsDownsideDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlSequenceStatisticsDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlSequenceStatisticsDownsideVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the variance of observations below zero for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlSequenceStatisticsDownsideVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlSequenceStatisticsErrorEstimate"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlSequenceStatisticsErrorEstimate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the error estimate on the mean value for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlSequenceStatisticsErrorEstimate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlSequenceStatisticsGaussianAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x2C""qlSequenceStatisticsGaussianAverageShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the averaged shortfallness for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlSequenceStatisticsGaussianAverageShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlSequenceStatisticsGaussianPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x26""qlSequenceStatisticsGaussianPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""ObjectId,X,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the x-th percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlSequenceStatisticsGaussianPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlSequenceStatisticsGaussianPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x2B""qlSequenceStatisticsGaussianPotentialUpside"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the reciprocal of VAR at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlSequenceStatisticsGaussianPotentialUpside"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlSequenceStatisticsGaussianShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x25""qlSequenceStatisticsGaussianShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the probability of missing the given target for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlSequenceStatisticsGaussianShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x27""qlSequenceStatisticsGaussianValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x27""qlSequenceStatisticsGaussianValueAtRisk"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the value-at-risk at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlSequenceStatisticsGaussianValueAtRisk"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSequenceStatisticsInc"),
            // parameter codes
            TempStrNoSize("\x07""CCPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlSequenceStatisticsInc"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,Dimension,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class SequenceStatisticsInc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSequenceStatisticsInc"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSequenceStatisticsInc2"),
            // parameter codes
            TempStrNoSize("\x09""CCPKPPPL#"),
            // function display name
            TempStrNoSize("\x18""qlSequenceStatisticsInc2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Dimension,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class SequenceStatisticsInc and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x29""sample dimensionality. Default value = 0."),
            TempStrNoSize("\x3B""Sampled values. If omitted, an empty statistics is created."),
            TempStrNoSize("\x63""If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSequenceStatisticsInc2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSequenceStatisticsKurtosis"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSequenceStatisticsKurtosis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the excess kurtosis for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlSequenceStatisticsKurtosis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSequenceStatisticsMax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlSequenceStatisticsMax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the maximum sample value for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSequenceStatisticsMax"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSequenceStatisticsMean"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlSequenceStatisticsMean"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns the mean for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSequenceStatisticsMean"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSequenceStatisticsMin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlSequenceStatisticsMin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the minimum sample value for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSequenceStatisticsMin"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSequenceStatisticsPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1E""qlSequenceStatisticsPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""ObjectId,X,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the x-th percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlSequenceStatisticsPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlSequenceStatisticsPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x23""qlSequenceStatisticsPotentialUpside"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,Centile,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the reciprocal of VAR at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0C""the centile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlSequenceStatisticsPotentialUpside"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSequenceStatisticsRegret"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1A""qlSequenceStatisticsRegret"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5A""Returns the variance of observations below target for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlSequenceStatisticsRegret"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSequenceStatisticsSamples"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSequenceStatisticsSamples"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the number of samples collected for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSequenceStatisticsSamples"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlSequenceStatisticsSemiDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlSequenceStatisticsSemiDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x54""Returns the square root of the semivariance for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlSequenceStatisticsSemiDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSequenceStatisticsSemiVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x20""qlSequenceStatisticsSemiVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the variance of observations below the mean for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlSequenceStatisticsSemiVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSequenceStatisticsShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1D""qlSequenceStatisticsShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5C""Returns the probability of missing the given target for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlSequenceStatisticsShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSequenceStatisticsSize"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x18""qlSequenceStatisticsSize"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""Returns the size (sample dimensionality) for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSequenceStatisticsSize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSequenceStatisticsSkewness"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSequenceStatisticsSkewness"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the skewness for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlSequenceStatisticsSkewness"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlSequenceStatisticsStandardDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlSequenceStatisticsStandardDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the the standard deviation for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlSequenceStatisticsStandardDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSequenceStatisticsValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1F""qlSequenceStatisticsValueAtRisk"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Target,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the value-at-risk at a given percentile for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlSequenceStatisticsValueAtRisk"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlSequenceStatisticsVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlSequenceStatisticsVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the variance for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlSequenceStatisticsVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSequenceStatisticsWeightSum"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlSequenceStatisticsWeightSum"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the sum of data weights for the given SequenceStatistics object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLib::SequenceStatistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlSequenceStatisticsWeightSum"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

