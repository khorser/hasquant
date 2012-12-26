
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

// register functions in category Correlation with Excel

void registerCorrelation(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCotSwapFromFwdCorrelation"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlCotSwapFromFwdCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,FwdCorr,CurveState,Displacement,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class CotSwapFromFwdCorrelation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x48""Forward rates correlation (i.e. PiecewiseConstantCorrelation object ID)."),
            TempStrNoSize("\x0B""curveState."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x19""qlExponentialCorrelations"),
            // parameter codes
            TempStrNoSize("\x08""PPPPPEP#"),
            // function display name
            TempStrNoSize("\x19""qlExponentialCorrelations"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""RateTimes,LongTermCorr,Beta,Gamma,Time,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x65""Returns the correlation matrix (time dependent long term + beta + gamma exponential functional form)."),
            // parameter descriptions
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x2C""Long term correlation . Default value = 0.0."),
            TempStrNoSize("\x2F""exponential decay factor. Default value = 0.24."),
            TempStrNoSize("\x2F""exponent for time to go. Default value = 0.333."),
            TempStrNoSize("\x08""time t ."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlExponentialForwardCorrelation"),
            // parameter codes
            TempStrNoSize("\x0B""CCPEEEPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlExponentialForwardCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,RateTimes,LongTermCorr,Beta,Gamma,Times,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Construct an object of class ExponentialForwardCorrelation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""rate times."),
            TempStrNoSize("\x17""Long term correlation ."),
            TempStrNoSize("\x19""exponential decay factor."),
            TempStrNoSize("\x18""exponent for time to go."),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 27, &xDll,
            // function code name
            TempStrNoSize("\x20""qlHistoricalForwardRatesAnalysis"),
            // parameter codes
            TempStrNoSize("\x13""CCCPPCCCCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x20""qlHistoricalForwardRatesAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB3""ObjectId,SequenceStats,StartDate,EndDate,Step,IborIndex,InitialGap,Horizon,IborIndexes,SwapIndexes,DayCounter,TraitsID,InterpolatorID,BootstrapAccuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class HistoricalForwardRatesAnalysis and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Sequence Statistics object ID."),
            TempStrNoSize("\x1D""beginning of the time series."),
            TempStrNoSize("\x17""end of the time series."),
            TempStrNoSize("\x17""time series' time step."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x0B""initialGap."),
            TempStrNoSize("\x12""bootstrap horizon."),
            TempStrNoSize("\x0D""Ibor indexes."),
            TempStrNoSize("\x0D""Swap indexes."),
            TempStrNoSize("\x3E""yield curve DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x3D""Discount, ZeroRate, or ForwardRate. Default value = Discount."),
            TempStrNoSize("\x3F""Linear, LogLinear, or CubicSpline. Default value = CubicSpline."),
            TempStrNoSize("\x2B""boostrap accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlHistoricalForwardRatesAnalysisFailedDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlHistoricalForwardRatesAnalysisFailedDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns vector of dates for which forward rates could not be calculated."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x37""qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x37""qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5A""Returns vector of error messages for dates on which forward rates could not be calculated."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2D""qlHistoricalForwardRatesAnalysisFixingPeriods"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2D""qlHistoricalForwardRatesAnalysisFixingPeriods"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""Returns the forward rates time grid."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlHistoricalForwardRatesAnalysisSkippedDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlHistoricalForwardRatesAnalysisSkippedDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns vector of historic dates for which some fixing is missing."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x38""qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x38""qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns vector of error messages for historic dates with missing fixing."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlHistoricalRatesAnalysis"),
            // parameter codes
            TempStrNoSize("\x0B""CCCPPCPPPL#"),
            // function display name
            TempStrNoSize("\x19""qlHistoricalRatesAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5D""ObjectId,SequenceStats,StartDate,EndDate,Step,InterestRateIndexes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class HistoricalRatesAnalysis and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Sequence Statistics object ID."),
            TempStrNoSize("\x1D""beginning of the time series."),
            TempStrNoSize("\x17""end of the time series."),
            TempStrNoSize("\x17""time series' time step."),
            TempStrNoSize("\x21""interest rate indexes object IDs."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlHistoricalRatesAnalysisSkippedDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlHistoricalRatesAnalysisSkippedDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns vector of historic dates for which some fixing is missing."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::HistoricalRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x31""qlHistoricalRatesAnalysisSkippedDatesErrorMessage"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x31""qlHistoricalRatesAnalysisSkippedDatesErrorMessage"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns vector of error messages for historic dates with missing fixing."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::HistoricalRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x30""qlMarketModelLmLinearExponentialCorrelationModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCNEEPPPL#"),
            // function display name
            TempStrNoSize("\x30""qlMarketModelLmLinearExponentialCorrelationModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3A""ObjectId,Size,Rho,Beta,Factors,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""Construct an object of class LmLinearExponentialCorrelationModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x05""size."),
            TempStrNoSize("\x04""rho."),
            TempStrNoSize("\x05""beta."),
            TempStrNoSize("\x3A""factors. Default value = QuantLib::Null<QuantLib::Size>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x29""qlPiecewiseConstantCorrelationCorrelation"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x29""qlPiecewiseConstantCorrelationCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,TimeIndex,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the pseudo-root of the equivalent covariance swap rates matrix."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::PiecewiseConstantCorrelation object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlPiecewiseConstantCorrelationNumberOfRates"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x2B""qlPiecewiseConstantCorrelationNumberOfRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""Piecewise Constant Correlation Number of Rates."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::PiecewiseConstantCorrelation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlPiecewiseConstantCorrelationTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x23""qlPiecewiseConstantCorrelationTimes"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x25""Piecewise Constant Correlation Times."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::PiecewiseConstantCorrelation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x23""qlTimeHomogeneousForwardCorrelation"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x23""qlTimeHomogeneousForwardCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""ObjectId,FwdCorrMatrix,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Construct an object of class TimeHomogeneousForwardCorrelation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1B""forward correlation matrix."),
            TempStrNoSize("\x0B""rate times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Correlation with Excel

void unregisterCorrelation(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlCotSwapFromFwdCorrelation"),
            // parameter codes
            TempStrNoSize("\x09""CCCCPPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlCotSwapFromFwdCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,FwdCorr,CurveState,Displacement,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class CotSwapFromFwdCorrelation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x48""Forward rates correlation (i.e. PiecewiseConstantCorrelation object ID)."),
            TempStrNoSize("\x0B""curveState."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlCotSwapFromFwdCorrelation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x19""qlExponentialCorrelations"),
            // parameter codes
            TempStrNoSize("\x08""PPPPPEP#"),
            // function display name
            TempStrNoSize("\x19""qlExponentialCorrelations"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""RateTimes,LongTermCorr,Beta,Gamma,Time,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x65""Returns the correlation matrix (time dependent long term + beta + gamma exponential functional form)."),
            // parameter descriptions
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x2C""Long term correlation . Default value = 0.0."),
            TempStrNoSize("\x2F""exponential decay factor. Default value = 0.24."),
            TempStrNoSize("\x2F""exponent for time to go. Default value = 0.333."),
            TempStrNoSize("\x08""time t ."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlExponentialCorrelations"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlExponentialForwardCorrelation"),
            // parameter codes
            TempStrNoSize("\x0B""CCPEEEPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlExponentialForwardCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,RateTimes,LongTermCorr,Beta,Gamma,Times,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Construct an object of class ExponentialForwardCorrelation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0B""rate times."),
            TempStrNoSize("\x17""Long term correlation ."),
            TempStrNoSize("\x19""exponential decay factor."),
            TempStrNoSize("\x18""exponent for time to go."),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlExponentialForwardCorrelation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 27, &xDll,
            // function code name
            TempStrNoSize("\x20""qlHistoricalForwardRatesAnalysis"),
            // parameter codes
            TempStrNoSize("\x13""CCCPPCCCCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x20""qlHistoricalForwardRatesAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB3""ObjectId,SequenceStats,StartDate,EndDate,Step,IborIndex,InitialGap,Horizon,IborIndexes,SwapIndexes,DayCounter,TraitsID,InterpolatorID,BootstrapAccuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class HistoricalForwardRatesAnalysis and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Sequence Statistics object ID."),
            TempStrNoSize("\x1D""beginning of the time series."),
            TempStrNoSize("\x17""end of the time series."),
            TempStrNoSize("\x17""time series' time step."),
            TempStrNoSize("\x14""floating rate index."),
            TempStrNoSize("\x0B""initialGap."),
            TempStrNoSize("\x12""bootstrap horizon."),
            TempStrNoSize("\x0D""Ibor indexes."),
            TempStrNoSize("\x0D""Swap indexes."),
            TempStrNoSize("\x3E""yield curve DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x3D""Discount, ZeroRate, or ForwardRate. Default value = Discount."),
            TempStrNoSize("\x3F""Linear, LogLinear, or CubicSpline. Default value = CubicSpline."),
            TempStrNoSize("\x2B""boostrap accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlHistoricalForwardRatesAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlHistoricalForwardRatesAnalysisFailedDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlHistoricalForwardRatesAnalysisFailedDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns vector of dates for which forward rates could not be calculated."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlHistoricalForwardRatesAnalysisFailedDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x37""qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x37""qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5A""Returns vector of error messages for dates on which forward rates could not be calculated."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x37""qlHistoricalForwardRatesAnalysisFailedDatesErrorMessage"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2D""qlHistoricalForwardRatesAnalysisFixingPeriods"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2D""qlHistoricalForwardRatesAnalysisFixingPeriods"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""Returns the forward rates time grid."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2D""qlHistoricalForwardRatesAnalysisFixingPeriods"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlHistoricalForwardRatesAnalysisSkippedDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlHistoricalForwardRatesAnalysisSkippedDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns vector of historic dates for which some fixing is missing."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlHistoricalForwardRatesAnalysisSkippedDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x38""qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x38""qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns vector of error messages for historic dates with missing fixing."),
            // parameter descriptions
            TempStrNoSize("\x3E""id of existing QuantLib::HistoricalForwardRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x38""qlHistoricalForwardRatesAnalysisSkippedDatesErrorMessage"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlHistoricalRatesAnalysis"),
            // parameter codes
            TempStrNoSize("\x0B""CCCPPCPPPL#"),
            // function display name
            TempStrNoSize("\x19""qlHistoricalRatesAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5D""ObjectId,SequenceStats,StartDate,EndDate,Step,InterestRateIndexes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class HistoricalRatesAnalysis and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""Sequence Statistics object ID."),
            TempStrNoSize("\x1D""beginning of the time series."),
            TempStrNoSize("\x17""end of the time series."),
            TempStrNoSize("\x17""time series' time step."),
            TempStrNoSize("\x21""interest rate indexes object IDs."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlHistoricalRatesAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x25""qlHistoricalRatesAnalysisSkippedDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x25""qlHistoricalRatesAnalysisSkippedDates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns vector of historic dates for which some fixing is missing."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::HistoricalRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlHistoricalRatesAnalysisSkippedDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x31""qlHistoricalRatesAnalysisSkippedDatesErrorMessage"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x31""qlHistoricalRatesAnalysisSkippedDatesErrorMessage"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns vector of error messages for historic dates with missing fixing."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::HistoricalRatesAnalysis object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x31""qlHistoricalRatesAnalysisSkippedDatesErrorMessage"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x30""qlMarketModelLmLinearExponentialCorrelationModel"),
            // parameter codes
            TempStrNoSize("\x0A""CCNEEPPPL#"),
            // function display name
            TempStrNoSize("\x30""qlMarketModelLmLinearExponentialCorrelationModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3A""ObjectId,Size,Rho,Beta,Factors,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""Construct an object of class LmLinearExponentialCorrelationModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x05""size."),
            TempStrNoSize("\x04""rho."),
            TempStrNoSize("\x05""beta."),
            TempStrNoSize("\x3A""factors. Default value = QuantLib::Null<QuantLib::Size>()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x30""qlMarketModelLmLinearExponentialCorrelationModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x29""qlPiecewiseConstantCorrelationCorrelation"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x29""qlPiecewiseConstantCorrelationCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,TimeIndex,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the pseudo-root of the equivalent covariance swap rates matrix."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::PiecewiseConstantCorrelation object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlPiecewiseConstantCorrelationCorrelation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlPiecewiseConstantCorrelationNumberOfRates"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x2B""qlPiecewiseConstantCorrelationNumberOfRates"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""Piecewise Constant Correlation Number of Rates."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::PiecewiseConstantCorrelation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlPiecewiseConstantCorrelationNumberOfRates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlPiecewiseConstantCorrelationTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x23""qlPiecewiseConstantCorrelationTimes"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x25""Piecewise Constant Correlation Times."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::PiecewiseConstantCorrelation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlPiecewiseConstantCorrelationTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x23""qlTimeHomogeneousForwardCorrelation"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x23""qlTimeHomogeneousForwardCorrelation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3C""ObjectId,FwdCorrMatrix,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Construct an object of class TimeHomogeneousForwardCorrelation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1B""forward correlation matrix."),
            TempStrNoSize("\x0B""rate times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlTimeHomogeneousForwardCorrelation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

