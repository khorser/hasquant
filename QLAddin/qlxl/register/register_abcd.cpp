
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

// register functions in category Abcd with Excel

void registerAbcd(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 27, &xDll,
            // function code name
            TempStrNoSize("\x11""qlAbcdCalibration"),
            // parameter codes
            TempStrNoSize("\x13""CCPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlAbcdCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x80""ObjectId,Times,BlackVols,A,B,C,D,AIsFixed,BIsFixed,CIsFixed,DIsFixed,VegaWeighted,EndCriteria,Method,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class AbcdCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x13""Black Volatilities."),
            TempStrNoSize("\x7A""the a coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = -0.06."),
            TempStrNoSize("\x79""the b coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x79""the c coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.54."),
            TempStrNoSize("\x79""the d coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationA"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationA"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationB"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationB"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationC"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationC"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAbcdCalibrationCompute"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x18""qlAbcdCalibrationCompute"),
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
            TempStrNoSize("\x14""compute calibration."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationD"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationD"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlAbcdCalibrationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1C""qlAbcdCalibrationEndCriteria"),
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
            TempStrNoSize("\x40""Calibrates the a, b, c, d parameters of the vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlAbcdCalibrationError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlAbcdCalibrationError"),
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
            TempStrNoSize("\x65""Returns the root mean squared error between the abdc implied Black vols and a given Black vol vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationK"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationK"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x20""ObjectId,Times,BlackVols,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the 'k' adjustment factors needed to match Black vols."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x13""Black Volatilities."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAbcdCalibrationMaxError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlAbcdCalibrationMaxError"),
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
            TempStrNoSize("\x56""Returs the max error between the abdc implied Black vols and a given Black vol vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdDFunction"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdDFunction"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlAbcdFunction"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlAbcdFunction"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,A,B,C,D,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class AbcdFunction and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x7A""the a coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = -0.06."),
            TempStrNoSize("\x79""the b coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x79""the c coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.54."),
            TempStrNoSize("\x79""the d coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionA"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionA"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionB"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionB"),
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
            TempStrNoSize("\x3A""Returns the b coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionC"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionC"),
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
            TempStrNoSize("\x3A""Returns the c coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAbcdFunctionCovariance"),
            // parameter codes
            TempStrNoSize("\x08""PCEPEEP#"),
            // function display name
            TempStrNoSize("\x18""qlAbcdFunctionCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1E""ObjectId,TMin,TMax,T,S,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns covariance(s) in [tMin,tMax] between T and S rate fixing times."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x27""lower bound of the covariance integral."),
            TempStrNoSize("\x2D""upper bound(s) of the covariance integral(s)."),
            TempStrNoSize("\x23""fixing calendar time of first rate."),
            TempStrNoSize("\x24""fixing calendar time of second rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionD"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionD"),
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
            TempStrNoSize("\x3A""Returns the d coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousCovariance"),
            // parameter codes
            TempStrNoSize("\x07""PCPEEP#"),
            // function display name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,U,T,S,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns covariance at calendar time u between T and S rates fixing times."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x11""calendar time(s)."),
            TempStrNoSize("\x1A""fixing time of first rate."),
            TempStrNoSize("\x1B""fixing time of second rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlAbcdFunctionInstantaneousValue"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlAbcdFunctionInstantaneousValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""ObjectId,U,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6E""Returns the instantaneous volatility as function of residual time to maturity u=T-t: [a + b*u] * e^{-c*u} + d."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""residual time(s) to maturity."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x23""qlAbcdFunctionInstantaneousVariance"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x23""qlAbcdFunctionInstantaneousVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x14""ObjectId,U,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Returns variance at calendar time(s) u of T-fixing rate."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x11""calendar time(s)."),
            TempStrNoSize("\x18""fixing time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousVolatility"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x14""ObjectId,U,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns volatility/ies at calendar time(s) u of T-fixing rate."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x11""calendar time(s)."),
            TempStrNoSize("\x21""fixing calendar time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlAbcdFunctionLongTermVolatility"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlAbcdFunctionLongTermVolatility"),
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
            TempStrNoSize("\x3C""Returns the long term volatility implied by Abcd volatility."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlAbcdFunctionMaximumLocation"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlAbcdFunctionMaximumLocation"),
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
            TempStrNoSize("\x47""Returns, if b is positive, the location of the Abcd volatility maximum."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlAbcdFunctionMaximumVolatility"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1F""qlAbcdFunctionMaximumVolatility"),
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
            TempStrNoSize("\x3E""Returns, if b is positive, the maximum of the Abcd volatility."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlAbcdFunctionShortTermVolatility"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlAbcdFunctionShortTermVolatility"),
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
            TempStrNoSize("\x3D""Returns the short term volatility implied by Abcd volatility."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x16""qlAbcdFunctionVariance"),
            // parameter codes
            TempStrNoSize("\x07""PCEPEP#"),
            // function display name
            TempStrNoSize("\x16""qlAbcdFunctionVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,TMin,TMax,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns variance(s) in [tMin,tMax] of T rate fixing time."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x27""lower bound of the covariance integral."),
            TempStrNoSize("\x27""upper bound of the covariance integral."),
            TempStrNoSize("\x21""fixing calendar time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAbcdFunctionVolatility"),
            // parameter codes
            TempStrNoSize("\x07""PCEPEP#"),
            // function display name
            TempStrNoSize("\x18""qlAbcdFunctionVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,TMin,TMax,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns volatility/ies in [tMin,tMax] of T rate fixing time."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x27""lower bound of the covariance integral."),
            TempStrNoSize("\x2D""upper bound(s) of the covariance integral(s)."),
            TempStrNoSize("\x21""fixing calendar time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Abcd with Excel

void unregisterAbcd(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 27, &xDll,
            // function code name
            TempStrNoSize("\x11""qlAbcdCalibration"),
            // parameter codes
            TempStrNoSize("\x13""CCPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlAbcdCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x80""ObjectId,Times,BlackVols,A,B,C,D,AIsFixed,BIsFixed,CIsFixed,DIsFixed,VegaWeighted,EndCriteria,Method,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class AbcdCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x13""Black Volatilities."),
            TempStrNoSize("\x7A""the a coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = -0.06."),
            TempStrNoSize("\x79""the b coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x79""the c coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.54."),
            TempStrNoSize("\x79""the d coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x5A""TRUE if the a coefficient must be kept fixed in later calibrations. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlAbcdCalibration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationA"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationA"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdCalibrationA"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationB"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationB"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdCalibrationB"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationC"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationC"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdCalibrationC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAbcdCalibrationCompute"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x18""qlAbcdCalibrationCompute"),
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
            TempStrNoSize("\x14""compute calibration."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlAbcdCalibrationCompute"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationD"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationD"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdCalibrationD"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlAbcdCalibrationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1C""qlAbcdCalibrationEndCriteria"),
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
            TempStrNoSize("\x40""Calibrates the a, b, c, d parameters of the vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlAbcdCalibrationEndCriteria"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlAbcdCalibrationError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlAbcdCalibrationError"),
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
            TempStrNoSize("\x65""Returns the root mean squared error between the abdc implied Black vols and a given Black vol vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlAbcdCalibrationError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdCalibrationK"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdCalibrationK"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x20""ObjectId,Times,BlackVols,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the 'k' adjustment factors needed to match Black vols."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x06""times."),
            TempStrNoSize("\x13""Black Volatilities."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdCalibrationK"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAbcdCalibrationMaxError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlAbcdCalibrationMaxError"),
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
            TempStrNoSize("\x56""Returs the max error between the abdc implied Black vols and a given Black vol vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlAbcdCalibrationMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdDFunction"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdDFunction"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlAbcdDFunction"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlAbcdFunction"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlAbcdFunction"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2C""ObjectId,A,B,C,D,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class AbcdFunction and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x7A""the a coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = -0.06."),
            TempStrNoSize("\x79""the b coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x79""the c coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.54."),
            TempStrNoSize("\x79""the d coefficient in the abcd vol parametrization. Used as guess if the object is later calibrated. Default value = 0.17."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlAbcdFunction"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionA"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionA"),
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
            TempStrNoSize("\x3A""Returns the a coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlAbcdFunctionA"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionB"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionB"),
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
            TempStrNoSize("\x3A""Returns the b coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlAbcdFunctionB"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionC"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionC"),
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
            TempStrNoSize("\x3A""Returns the c coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlAbcdFunctionC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAbcdFunctionCovariance"),
            // parameter codes
            TempStrNoSize("\x08""PCEPEEP#"),
            // function display name
            TempStrNoSize("\x18""qlAbcdFunctionCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1E""ObjectId,TMin,TMax,T,S,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns covariance(s) in [tMin,tMax] between T and S rate fixing times."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x27""lower bound of the covariance integral."),
            TempStrNoSize("\x2D""upper bound(s) of the covariance integral(s)."),
            TempStrNoSize("\x23""fixing calendar time of first rate."),
            TempStrNoSize("\x24""fixing calendar time of second rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlAbcdFunctionCovariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlAbcdFunctionD"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x0F""qlAbcdFunctionD"),
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
            TempStrNoSize("\x3A""Returns the d coefficient in the abcd vol parametrization."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlAbcdFunctionD"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousCovariance"),
            // parameter codes
            TempStrNoSize("\x07""PCPEEP#"),
            // function display name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,U,T,S,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns covariance at calendar time u between T and S rates fixing times."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x11""calendar time(s)."),
            TempStrNoSize("\x1A""fixing time of first rate."),
            TempStrNoSize("\x1B""fixing time of second rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousCovariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlAbcdFunctionInstantaneousValue"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x20""qlAbcdFunctionInstantaneousValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x12""ObjectId,U,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6E""Returns the instantaneous volatility as function of residual time to maturity u=T-t: [a + b*u] * e^{-c*u} + d."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""residual time(s) to maturity."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlAbcdFunctionInstantaneousValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x23""qlAbcdFunctionInstantaneousVariance"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x23""qlAbcdFunctionInstantaneousVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x14""ObjectId,U,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Returns variance at calendar time(s) u of T-fixing rate."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x11""calendar time(s)."),
            TempStrNoSize("\x18""fixing time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlAbcdFunctionInstantaneousVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousVolatility"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x14""ObjectId,U,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns volatility/ies at calendar time(s) u of T-fixing rate."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x11""calendar time(s)."),
            TempStrNoSize("\x21""fixing calendar time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlAbcdFunctionInstantaneousVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlAbcdFunctionLongTermVolatility"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlAbcdFunctionLongTermVolatility"),
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
            TempStrNoSize("\x3C""Returns the long term volatility implied by Abcd volatility."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlAbcdFunctionLongTermVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlAbcdFunctionMaximumLocation"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1D""qlAbcdFunctionMaximumLocation"),
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
            TempStrNoSize("\x47""Returns, if b is positive, the location of the Abcd volatility maximum."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlAbcdFunctionMaximumLocation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlAbcdFunctionMaximumVolatility"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x1F""qlAbcdFunctionMaximumVolatility"),
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
            TempStrNoSize("\x3E""Returns, if b is positive, the maximum of the Abcd volatility."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlAbcdFunctionMaximumVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlAbcdFunctionShortTermVolatility"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlAbcdFunctionShortTermVolatility"),
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
            TempStrNoSize("\x3D""Returns the short term volatility implied by Abcd volatility."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlAbcdFunctionShortTermVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x16""qlAbcdFunctionVariance"),
            // parameter codes
            TempStrNoSize("\x07""PCEPEP#"),
            // function display name
            TempStrNoSize("\x16""qlAbcdFunctionVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,TMin,TMax,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns variance(s) in [tMin,tMax] of T rate fixing time."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x27""lower bound of the covariance integral."),
            TempStrNoSize("\x27""upper bound of the covariance integral."),
            TempStrNoSize("\x21""fixing calendar time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlAbcdFunctionVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAbcdFunctionVolatility"),
            // parameter codes
            TempStrNoSize("\x07""PCEPEP#"),
            // function display name
            TempStrNoSize("\x18""qlAbcdFunctionVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,TMin,TMax,T,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns volatility/ies in [tMin,tMax] of T rate fixing time."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::AbcdFunction object"),
            TempStrNoSize("\x27""lower bound of the covariance integral."),
            TempStrNoSize("\x2D""upper bound(s) of the covariance integral(s)."),
            TempStrNoSize("\x21""fixing calendar time of the rate."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlAbcdFunctionVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

