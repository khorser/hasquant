
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

// register functions in category Volatility with Excel

void registerVolatility(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlMarketModelLmExtLinearExponentialVolModel"),
            // parameter codes
            TempStrNoSize("\x0B""CCPEEEEPPL#"),
            // function display name
            TempStrNoSize("\x2B""qlMarketModelLmExtLinearExponentialVolModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""ObjectId,FixingTimes,A,B,C,D,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class LmExtLinearExponentialVolModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x0C""a parameter."),
            TempStrNoSize("\x0C""b parameter."),
            TempStrNoSize("\x0C""c parameter."),
            TempStrNoSize("\x0C""d parameter."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlPiecewiseConstantAbcdVariance"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPPNPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlPiecewiseConstantAbcdVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,A,B,C,D,ResetIndex,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Construct an object of class PiecewiseConstantAbcdVariance and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x70""coefficient in abcd vol parametrization. Used as guess if the object is later calibrated. Default value = -0.06."),
            TempStrNoSize("\x73""coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x73""coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.54."),
            TempStrNoSize("\x73""coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x2A""Index that defines the reset time of rate."),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceRateTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceRateTimes"),
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
            TempStrNoSize("\x3E""Returns the rate time of the PiecewiseConstantVariance object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x28""qlPiecewiseConstantVarianceTotalVariance"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x28""qlPiecewiseConstantVarianceTotalVariance"),
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
            TempStrNoSize("\x59""Returns the total variance at a given time index of the PiecewiseConstantVariance object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlPiecewiseConstantVarianceTotalVolatility"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x2A""qlPiecewiseConstantVarianceTotalVolatility"),
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
            TempStrNoSize("\x59""Returns the total variance at a given time index of the PiecewiseConstantVariance object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlPiecewiseConstantVarianceVariance"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x23""qlPiecewiseConstantVarianceVariance"),
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
            TempStrNoSize("\x3E""Returns the piecewise constant variance at a given time index."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceVariances"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceVariances"),
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
            TempStrNoSize("\x29""Returns the piecewise constant variances."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x27""qlPiecewiseConstantVarianceVolatilities"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x27""qlPiecewiseConstantVarianceVolatilities"),
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
            TempStrNoSize("\x2C""Returns the piecewise constant volatilities."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlPiecewiseConstantVarianceVolatility"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x25""qlPiecewiseConstantVarianceVolatility"),
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
            TempStrNoSize("\x40""Returns the piecewise constant volatility at a given time index."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Volatility with Excel

void unregisterVolatility(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlMarketModelLmExtLinearExponentialVolModel"),
            // parameter codes
            TempStrNoSize("\x0B""CCPEEEEPPL#"),
            // function display name
            TempStrNoSize("\x2B""qlMarketModelLmExtLinearExponentialVolModel"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x38""ObjectId,FixingTimes,A,B,C,D,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class LmExtLinearExponentialVolModel and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x0C""a parameter."),
            TempStrNoSize("\x0C""b parameter."),
            TempStrNoSize("\x0C""c parameter."),
            TempStrNoSize("\x0C""d parameter."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlMarketModelLmExtLinearExponentialVolModel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlPiecewiseConstantAbcdVariance"),
            // parameter codes
            TempStrNoSize("\x0C""CCPPPPNPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlPiecewiseConstantAbcdVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,A,B,C,D,ResetIndex,RateTimes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Construct an object of class PiecewiseConstantAbcdVariance and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x70""coefficient in abcd vol parametrization. Used as guess if the object is later calibrated. Default value = -0.06."),
            TempStrNoSize("\x73""coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x73""coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.54."),
            TempStrNoSize("\x73""coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x2A""Index that defines the reset time of rate."),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlPiecewiseConstantAbcdVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceRateTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceRateTimes"),
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
            TempStrNoSize("\x3E""Returns the rate time of the PiecewiseConstantVariance object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceRateTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x28""qlPiecewiseConstantVarianceTotalVariance"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x28""qlPiecewiseConstantVarianceTotalVariance"),
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
            TempStrNoSize("\x59""Returns the total variance at a given time index of the PiecewiseConstantVariance object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlPiecewiseConstantVarianceTotalVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlPiecewiseConstantVarianceTotalVolatility"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x2A""qlPiecewiseConstantVarianceTotalVolatility"),
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
            TempStrNoSize("\x59""Returns the total variance at a given time index of the PiecewiseConstantVariance object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlPiecewiseConstantVarianceTotalVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x23""qlPiecewiseConstantVarianceVariance"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x23""qlPiecewiseConstantVarianceVariance"),
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
            TempStrNoSize("\x3E""Returns the piecewise constant variance at a given time index."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlPiecewiseConstantVarianceVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceVariances"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceVariances"),
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
            TempStrNoSize("\x29""Returns the piecewise constant variances."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlPiecewiseConstantVarianceVariances"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x27""qlPiecewiseConstantVarianceVolatilities"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x27""qlPiecewiseConstantVarianceVolatilities"),
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
            TempStrNoSize("\x2C""Returns the piecewise constant volatilities."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlPiecewiseConstantVarianceVolatilities"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlPiecewiseConstantVarianceVolatility"),
            // parameter codes
            TempStrNoSize("\x05""ECNP#"),
            // function display name
            TempStrNoSize("\x25""qlPiecewiseConstantVarianceVolatility"),
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
            TempStrNoSize("\x40""Returns the piecewise constant volatility at a given time index."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLib::PiecewiseConstantVariance object"),
            TempStrNoSize("\x0B""time index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlPiecewiseConstantVarianceVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

