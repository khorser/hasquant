
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

// register functions in category Statistics with Excel

void registerStatistics(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlGaussianAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x1A""qlGaussianAverageShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x23""Returns the averaged shortfallness."),
            // parameter descriptions
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlGaussianDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlGaussianDownsideDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x13""Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""Returns the square root of the downside variance."),
            // parameter descriptions
            TempStrNoSize("\x37""mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlGaussianDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x1A""qlGaussianDownsideVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x13""Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the variance of observations below zero."),
            // parameter descriptions
            TempStrNoSize("\x3B""the mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlGaussianExpectedShortfall"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlGaussianExpectedShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the expected loss in case that the loss exceeded a VaR threshold."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x14""qlGaussianPercentile"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x14""qlGaussianPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""X,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1C""Returns the x-th percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x37""mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlGaussianPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x19""qlGaussianPotentialUpside"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Returns the reciprocal of VAR at a given percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlGaussianRegret"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x10""qlGaussianRegret"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Returns the variance of observations below target."),
            // parameter descriptions
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x37""mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x13""qlGaussianShortfall"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x13""qlGaussianShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Returns the probability of missing the given target."),
            // parameter descriptions
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGaussianTopPercentile"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x17""qlGaussianTopPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""X,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Returns the x-th top percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlGaussianValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x15""qlGaussianValueAtRisk"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the value-at-risk at a given percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlIncrementalStatistics"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlIncrementalStatistics"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class IncrementalStatistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x6A""Sampled values. If omitted, an empty statistics is created. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x6C""Weights. If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlStatistics"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlStatistics"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class Statistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x6A""Sampled values. If omitted, an empty statistics is created. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x6C""Weights. If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlStatisticsAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1C""qlStatisticsAverageShortfall"),
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
            TempStrNoSize("\x43""Returns the averaged shortfallness for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsDownsideDeviation"),
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
            TempStrNoSize("\x51""Returns the square root of the downside variance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlStatisticsDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlStatisticsDownsideVariance"),
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
            TempStrNoSize("\x50""Returns the variance of observations below zero for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlStatisticsErrorEstimate"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlStatisticsErrorEstimate"),
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
            TempStrNoSize("\x4D""Returns the error estimate on the mean value for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsExpectedShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsExpectedShortfall"),
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
            TempStrNoSize("\x69""Returns the expected loss in case that the loss exceeded a VaR threshold for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0C""the centile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x24""qlStatisticsGaussianAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x24""qlStatisticsGaussianAverageShortfall"),
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
            TempStrNoSize("\x43""Returns the averaged shortfallness for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlStatisticsGaussianDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlStatisticsGaussianDownsideDeviation"),
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
            TempStrNoSize("\x51""Returns the square root of the downside variance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlStatisticsGaussianDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlStatisticsGaussianDownsideVariance"),
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
            TempStrNoSize("\x50""Returns the variance of observations below zero for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlStatisticsGaussianExpectedShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x25""qlStatisticsGaussianExpectedShortfall"),
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
            TempStrNoSize("\x69""Returns the expected loss in case that the loss exceeded a VaR threshold for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlStatisticsGaussianPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1E""qlStatisticsGaussianPercentile"),
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
            TempStrNoSize("\x3C""Returns the x-th percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlStatisticsGaussianPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x23""qlStatisticsGaussianPotentialUpside"),
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
            TempStrNoSize("\x54""Returns the reciprocal of VAR at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlStatisticsGaussianRegret"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1A""qlStatisticsGaussianRegret"),
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
            TempStrNoSize("\x56""Returns the variance of observations below the target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsGaussianShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsGaussianShortfall"),
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
            TempStrNoSize("\x54""Returns the probability of missing the given target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x21""qlStatisticsGaussianTopPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x21""qlStatisticsGaussianTopPercentile"),
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
            TempStrNoSize("\x40""Returns the x-th top percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlStatisticsGaussianValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1F""qlStatisticsGaussianValueAtRisk"),
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
            TempStrNoSize("\x50""Returns the value-at-risk at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlStatisticsKurtosis"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlStatisticsKurtosis"),
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
            TempStrNoSize("\x3C""Returns the excess kurtosis for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlStatisticsMax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlStatisticsMax"),
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
            TempStrNoSize("\x41""Returns the maximum sample value for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlStatisticsMean"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x10""qlStatisticsMean"),
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
            TempStrNoSize("\x31""Returns the mean for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlStatisticsMin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlStatisticsMin"),
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
            TempStrNoSize("\x41""Returns the minimum sample value for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlStatisticsPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x16""qlStatisticsPercentile"),
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
            TempStrNoSize("\x3C""Returns the x-th percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlStatisticsPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1B""qlStatisticsPotentialUpside"),
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
            TempStrNoSize("\x54""Returns the reciprocal of VAR at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0C""the centile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x12""qlStatisticsRegret"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x12""qlStatisticsRegret"),
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
            TempStrNoSize("\x52""Returns the variance of observations below target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlStatisticsSamples"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x13""qlStatisticsSamples"),
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
            TempStrNoSize("\x48""Returns the number of samples collected for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlStatisticsSemiDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlStatisticsSemiDeviation"),
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
            TempStrNoSize("\x4C""Returns the square root of the semivariance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlStatisticsSemiVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlStatisticsSemiVariance"),
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
            TempStrNoSize("\x54""Returns the variance of observations below the mean for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlStatisticsShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x15""qlStatisticsShortfall"),
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
            TempStrNoSize("\x54""Returns the probability of missing the given target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlStatisticsSkewness"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlStatisticsSkewness"),
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
            TempStrNoSize("\x35""Returns the skewness for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsStandardDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsStandardDeviation"),
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
            TempStrNoSize("\x43""Returns the the standard deviation for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x19""qlStatisticsTopPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x19""qlStatisticsTopPercentile"),
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
            TempStrNoSize("\x40""Returns the x-th top percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlStatisticsValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x17""qlStatisticsValueAtRisk"),
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
            TempStrNoSize("\x50""Returns the value-at-risk at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlStatisticsVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlStatisticsVariance"),
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
            TempStrNoSize("\x35""Returns the variance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlStatisticsWeightSum"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlStatisticsWeightSum"),
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
            TempStrNoSize("\x40""Returns the sum of data weights for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Statistics with Excel

void unregisterStatistics(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlGaussianAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x1A""qlGaussianAverageShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x23""Returns the averaged shortfallness."),
            // parameter descriptions
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlGaussianAverageShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlGaussianDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlGaussianDownsideDeviation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x13""Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x31""Returns the square root of the downside variance."),
            // parameter descriptions
            TempStrNoSize("\x37""mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlGaussianDownsideDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlGaussianDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x05""PPPP#"),
            // function display name
            TempStrNoSize("\x1A""qlGaussianDownsideVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x13""Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the variance of observations below zero."),
            // parameter descriptions
            TempStrNoSize("\x3B""the mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlGaussianDownsideVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlGaussianExpectedShortfall"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlGaussianExpectedShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the expected loss in case that the loss exceeded a VaR threshold."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlGaussianExpectedShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x14""qlGaussianPercentile"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x14""qlGaussianPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""X,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1C""Returns the x-th percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x37""mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlGaussianPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlGaussianPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x19""qlGaussianPotentialUpside"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Returns the reciprocal of VAR at a given percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlGaussianPotentialUpside"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlGaussianRegret"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x10""qlGaussianRegret"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Returns the variance of observations below target."),
            // parameter descriptions
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x37""mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x45""standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlGaussianRegret"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x13""qlGaussianShortfall"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x13""qlGaussianShortfall"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x34""Returns the probability of missing the given target."),
            // parameter descriptions
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlGaussianShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlGaussianTopPercentile"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x17""qlGaussianTopPercentile"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""X,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Returns the x-th top percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlGaussianTopPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlGaussianValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x06""PEPPP#"),
            // function display name
            TempStrNoSize("\x15""qlGaussianValueAtRisk"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""Target,Mean,StdDev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the value-at-risk at a given percentile."),
            // parameter descriptions
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x3B""The mean of the gaussian distribution. Default value = 0.0."),
            TempStrNoSize("\x49""The standard deviation of the gaussian distribution. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlGaussianValueAtRisk"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x17""qlIncrementalStatistics"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x17""qlIncrementalStatistics"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class IncrementalStatistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x6A""Sampled values. If omitted, an empty statistics is created. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x6C""Weights. If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlIncrementalStatistics"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlStatistics"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlStatistics"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Values,Weights,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Construct an object of class Statistics and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x6A""Sampled values. If omitted, an empty statistics is created. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x6C""Weights. If omitted, all sampled values have the same weight. Default value = std::vector<QuantLib::Real>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlStatistics"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlStatisticsAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1C""qlStatisticsAverageShortfall"),
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
            TempStrNoSize("\x43""Returns the averaged shortfallness for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlStatisticsAverageShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsDownsideDeviation"),
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
            TempStrNoSize("\x51""Returns the square root of the downside variance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlStatisticsDownsideDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlStatisticsDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlStatisticsDownsideVariance"),
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
            TempStrNoSize("\x50""Returns the variance of observations below zero for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlStatisticsDownsideVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlStatisticsErrorEstimate"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlStatisticsErrorEstimate"),
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
            TempStrNoSize("\x4D""Returns the error estimate on the mean value for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlStatisticsErrorEstimate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsExpectedShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsExpectedShortfall"),
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
            TempStrNoSize("\x69""Returns the expected loss in case that the loss exceeded a VaR threshold for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0C""the centile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlStatisticsExpectedShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x24""qlStatisticsGaussianAverageShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x24""qlStatisticsGaussianAverageShortfall"),
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
            TempStrNoSize("\x43""Returns the averaged shortfallness for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlStatisticsGaussianAverageShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlStatisticsGaussianDownsideDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlStatisticsGaussianDownsideDeviation"),
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
            TempStrNoSize("\x51""Returns the square root of the downside variance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlStatisticsGaussianDownsideDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlStatisticsGaussianDownsideVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlStatisticsGaussianDownsideVariance"),
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
            TempStrNoSize("\x50""Returns the variance of observations below zero for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlStatisticsGaussianDownsideVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlStatisticsGaussianExpectedShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x25""qlStatisticsGaussianExpectedShortfall"),
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
            TempStrNoSize("\x69""Returns the expected loss in case that the loss exceeded a VaR threshold for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlStatisticsGaussianExpectedShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlStatisticsGaussianPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1E""qlStatisticsGaussianPercentile"),
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
            TempStrNoSize("\x3C""Returns the x-th percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlStatisticsGaussianPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlStatisticsGaussianPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x23""qlStatisticsGaussianPotentialUpside"),
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
            TempStrNoSize("\x54""Returns the reciprocal of VAR at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlStatisticsGaussianPotentialUpside"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlStatisticsGaussianRegret"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1A""qlStatisticsGaussianRegret"),
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
            TempStrNoSize("\x56""Returns the variance of observations below the target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlStatisticsGaussianRegret"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsGaussianShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsGaussianShortfall"),
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
            TempStrNoSize("\x54""Returns the probability of missing the given target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlStatisticsGaussianShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x21""qlStatisticsGaussianTopPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x21""qlStatisticsGaussianTopPercentile"),
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
            TempStrNoSize("\x40""Returns the x-th top percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlStatisticsGaussianTopPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlStatisticsGaussianValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1F""qlStatisticsGaussianValueAtRisk"),
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
            TempStrNoSize("\x50""Returns the value-at-risk at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlStatisticsGaussianValueAtRisk"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlStatisticsKurtosis"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlStatisticsKurtosis"),
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
            TempStrNoSize("\x3C""Returns the excess kurtosis for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlStatisticsKurtosis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlStatisticsMax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlStatisticsMax"),
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
            TempStrNoSize("\x41""Returns the maximum sample value for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlStatisticsMax"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x10""qlStatisticsMean"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x10""qlStatisticsMean"),
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
            TempStrNoSize("\x31""Returns the mean for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlStatisticsMean"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlStatisticsMin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x0F""qlStatisticsMin"),
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
            TempStrNoSize("\x41""Returns the minimum sample value for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlStatisticsMin"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlStatisticsPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x16""qlStatisticsPercentile"),
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
            TempStrNoSize("\x3C""Returns the x-th percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlStatisticsPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlStatisticsPotentialUpside"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x1B""qlStatisticsPotentialUpside"),
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
            TempStrNoSize("\x54""Returns the reciprocal of VAR at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0C""the centile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlStatisticsPotentialUpside"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x12""qlStatisticsRegret"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x12""qlStatisticsRegret"),
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
            TempStrNoSize("\x52""Returns the variance of observations below target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlStatisticsRegret"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlStatisticsSamples"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x13""qlStatisticsSamples"),
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
            TempStrNoSize("\x48""Returns the number of samples collected for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlStatisticsSamples"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlStatisticsSemiDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlStatisticsSemiDeviation"),
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
            TempStrNoSize("\x4C""Returns the square root of the semivariance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlStatisticsSemiDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlStatisticsSemiVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlStatisticsSemiVariance"),
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
            TempStrNoSize("\x54""Returns the variance of observations below the mean for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlStatisticsSemiVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlStatisticsShortfall"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x15""qlStatisticsShortfall"),
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
            TempStrNoSize("\x54""Returns the probability of missing the given target for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0B""the target."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlStatisticsShortfall"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlStatisticsSkewness"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlStatisticsSkewness"),
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
            TempStrNoSize("\x35""Returns the skewness for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlStatisticsSkewness"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlStatisticsStandardDeviation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlStatisticsStandardDeviation"),
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
            TempStrNoSize("\x43""Returns the the standard deviation for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlStatisticsStandardDeviation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x19""qlStatisticsTopPercentile"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x19""qlStatisticsTopPercentile"),
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
            TempStrNoSize("\x40""Returns the x-th top percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1B""Must be in the range (0,1]."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlStatisticsTopPercentile"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlStatisticsValueAtRisk"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x17""qlStatisticsValueAtRisk"),
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
            TempStrNoSize("\x50""Returns the value-at-risk at a given percentile for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x0F""the percentile."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlStatisticsValueAtRisk"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlStatisticsVariance"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlStatisticsVariance"),
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
            TempStrNoSize("\x35""Returns the variance for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlStatisticsVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlStatisticsWeightSum"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlStatisticsWeightSum"),
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
            TempStrNoSize("\x40""Returns the sum of data weights for the given Statistics object."),
            // parameter descriptions
            TempStrNoSize("\x2A""id of existing QuantLib::Statistics object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlStatisticsWeightSum"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

