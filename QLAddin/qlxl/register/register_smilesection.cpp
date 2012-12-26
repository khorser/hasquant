
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

// register functions in category Smilesection with Excel

void registerSmilesection(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x12""qlFlatSmileSection"),
            // parameter codes
            TempStrNoSize("\x0B""CCPEPPEPPL#"),
            // function display name
            TempStrNoSize("\x12""qlFlatSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,OptionDate,Volatility,DayCounter,RefDate,AtmValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class FlatSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x09""ref date."),
            TempStrNoSize("\x20""Current value of the underlying."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlInterpolatedSmileSection"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlInterpolatedSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x53""ObjectId,OptionDate,Strikes,StdDevs,AtmLevel,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class InterpolatedSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x53""standard deviations (i.e. volatilities times square root of time to option expiry)."),
            TempStrNoSize("\x20""Current value of the underlying."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSabrInterpolatedSmileSection"),
            // parameter codes
            TempStrNoSize("\x18""CCPEPLEPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlSabrInterpolatedSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDC""ObjectId,OptionDate,ForwardRate,Strike,FloatingStrike,AtmVolatility,VolatilitySpreads,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,Method,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class SabrInterpolatedSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as Date."),
            TempStrNoSize("\x11""Atm forward rate."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x1E""Strikes are floating or fixed."),
            TempStrNoSize("\x0F""atm volatility."),
            TempStrNoSize("\x27""volatilities spread at option expiries."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSabrInterpolatedSmileSection1"),
            // parameter codes
            TempStrNoSize("\x18""CCPPPLPPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlSabrInterpolatedSmileSection1"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDC""ObjectId,OptionDate,ForwardRate,Strike,FloatingStrike,AtmVolatility,VolatilitySpreads,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,Method,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class SabrInterpolatedSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as Date."),
            TempStrNoSize("\x17""Atm forward rate quote."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x1E""Strikes are floating or fixed."),
            TempStrNoSize("\x15""atm volatility quote."),
            TempStrNoSize("\x2E""volatilities spread quotes at option expiries."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionAlpha"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionAlpha"),
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
            TempStrNoSize("\x54""Returns the alpha of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlSabrInterpolatedSmileSectionBeta"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlSabrInterpolatedSmileSectionBeta"),
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
            TempStrNoSize("\x21""Returns the beta of the SABR fit."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlSabrInterpolatedSmileSectionEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x29""qlSabrInterpolatedSmileSectionEndCriteria"),
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
            TempStrNoSize("\x68""Returns the optimization end criteria of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionError"),
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
            TempStrNoSize("\x54""Returns the error of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlSabrInterpolatedSmileSectionMaxError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x26""qlSabrInterpolatedSmileSectionMaxError"),
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
            TempStrNoSize("\x58""Returns the max error of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSabrInterpolatedSmileSectionNu"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlSabrInterpolatedSmileSectionNu"),
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
            TempStrNoSize("\x51""Returns the nu of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlSabrInterpolatedSmileSectionRho"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlSabrInterpolatedSmileSectionRho"),
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
            TempStrNoSize("\x52""Returns the rho of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 29, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSabrSmileSection"),
            // parameter codes
            TempStrNoSize("\x15""CCEPPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlSabrSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xA7""ObjectId,OptionTime,Strikes,StdDevs,Forward,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,Method,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class SabrSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as time."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x53""standard deviations (i.e. volatilities times square root of time to option expiry)."),
            TempStrNoSize("\x09""atm rate."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x26""Optimization Method. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSmileSectionAtmLevel"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlSmileSectionAtmLevel"),
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
            TempStrNoSize("\x39""Returns the current value of the SmileSection underlying."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSmileSectionDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlSmileSectionDayCounter"),
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
            TempStrNoSize("\x32""Returns the DayCounter of the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSmileSectionExerciseDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1A""qlSmileSectionExerciseDate"),
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
            TempStrNoSize("\x35""Returns the exercise date of the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSmileSectionFromSabrVolSurface"),
            // parameter codes
            TempStrNoSize("\x08""CCCEPPL#"),
            // function display name
            TempStrNoSize("\x20""qlSmileSectionFromSabrVolSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,SabrVolSurface,OptionTime,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class SmileSectionFromSabrVolSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""SabrVolSurface object ID."),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSmileSectionVariance"),
            // parameter codes
            TempStrNoSize("\x05""ECPP#"),
            // function display name
            TempStrNoSize("\x16""qlSmileSectionVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Strike,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the variance at a given strike from the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSmileSectionVolatility"),
            // parameter codes
            TempStrNoSize("\x05""ECPP#"),
            // function display name
            TempStrNoSize("\x18""qlSmileSectionVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Strike,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns the volatility at a given strike from the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Smilesection with Excel

void unregisterSmilesection(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x12""qlFlatSmileSection"),
            // parameter codes
            TempStrNoSize("\x0B""CCPEPPEPPL#"),
            // function display name
            TempStrNoSize("\x12""qlFlatSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x56""ObjectId,OptionDate,Volatility,DayCounter,RefDate,AtmValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class FlatSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x09""ref date."),
            TempStrNoSize("\x20""Current value of the underlying."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlFlatSmileSection"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlInterpolatedSmileSection"),
            // parameter codes
            TempStrNoSize("\x0B""CCPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlInterpolatedSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x53""ObjectId,OptionDate,Strikes,StdDevs,AtmLevel,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class InterpolatedSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x53""standard deviations (i.e. volatilities times square root of time to option expiry)."),
            TempStrNoSize("\x20""Current value of the underlying."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlInterpolatedSmileSection"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSabrInterpolatedSmileSection"),
            // parameter codes
            TempStrNoSize("\x18""CCPEPLEPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlSabrInterpolatedSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDC""ObjectId,OptionDate,ForwardRate,Strike,FloatingStrike,AtmVolatility,VolatilitySpreads,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,Method,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class SabrInterpolatedSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as Date."),
            TempStrNoSize("\x11""Atm forward rate."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x1E""Strikes are floating or fixed."),
            TempStrNoSize("\x0F""atm volatility."),
            TempStrNoSize("\x27""volatilities spread at option expiries."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlSabrInterpolatedSmileSection"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 30, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlSabrInterpolatedSmileSection1"),
            // parameter codes
            TempStrNoSize("\x18""CCPPPLPPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlSabrInterpolatedSmileSection1"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDC""ObjectId,OptionDate,ForwardRate,Strike,FloatingStrike,AtmVolatility,VolatilitySpreads,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,Method,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class SabrInterpolatedSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as Date."),
            TempStrNoSize("\x17""Atm forward rate quote."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x1E""Strikes are floating or fixed."),
            TempStrNoSize("\x15""atm volatility quote."),
            TempStrNoSize("\x2E""volatilities spread quotes at option expiries."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlSabrInterpolatedSmileSection1"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionAlpha"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionAlpha"),
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
            TempStrNoSize("\x54""Returns the alpha of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionAlpha"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlSabrInterpolatedSmileSectionBeta"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlSabrInterpolatedSmileSectionBeta"),
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
            TempStrNoSize("\x21""Returns the beta of the SABR fit."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlSabrInterpolatedSmileSectionBeta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlSabrInterpolatedSmileSectionEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x29""qlSabrInterpolatedSmileSectionEndCriteria"),
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
            TempStrNoSize("\x68""Returns the optimization end criteria of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlSabrInterpolatedSmileSectionEndCriteria"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionError"),
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
            TempStrNoSize("\x54""Returns the error of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x23""qlSabrInterpolatedSmileSectionError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlSabrInterpolatedSmileSectionMaxError"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x26""qlSabrInterpolatedSmileSectionMaxError"),
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
            TempStrNoSize("\x58""Returns the max error of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlSabrInterpolatedSmileSectionMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSabrInterpolatedSmileSectionNu"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x20""qlSabrInterpolatedSmileSectionNu"),
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
            TempStrNoSize("\x51""Returns the nu of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlSabrInterpolatedSmileSectionNu"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlSabrInterpolatedSmileSectionRho"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x21""qlSabrInterpolatedSmileSectionRho"),
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
            TempStrNoSize("\x52""Returns the rho of the SABR fit for the given SabrInterpolatedSmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x3C""id of existing QuantLib::SabrInterpolatedSmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlSabrInterpolatedSmileSectionRho"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 29, &xDll,
            // function code name
            TempStrNoSize("\x12""qlSabrSmileSection"),
            // parameter codes
            TempStrNoSize("\x15""CCEPPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlSabrSmileSection"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xA7""ObjectId,OptionTime,Strikes,StdDevs,Forward,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,Method,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class SabrSmileSection and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x17""smile's expiry as time."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x53""standard deviations (i.e. volatilities times square root of time to option expiry)."),
            TempStrNoSize("\x09""atm rate."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x50""TRUE if the interpolation is weighted using options Vega. Default value = false."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x26""Optimization Method. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlSabrSmileSection"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSmileSectionAtmLevel"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x16""qlSmileSectionAtmLevel"),
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
            TempStrNoSize("\x39""Returns the current value of the SmileSection underlying."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSmileSectionAtmLevel"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSmileSectionDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlSmileSectionDayCounter"),
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
            TempStrNoSize("\x32""Returns the DayCounter of the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSmileSectionDayCounter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSmileSectionExerciseDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x1A""qlSmileSectionExerciseDate"),
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
            TempStrNoSize("\x35""Returns the exercise date of the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlSmileSectionExerciseDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x20""qlSmileSectionFromSabrVolSurface"),
            // parameter codes
            TempStrNoSize("\x08""CCCEPPL#"),
            // function display name
            TempStrNoSize("\x20""qlSmileSectionFromSabrVolSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,SabrVolSurface,OptionTime,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class SmileSectionFromSabrVolSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x19""SabrVolSurface object ID."),
            TempStrNoSize("\x17""smile's expiry as date."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlSmileSectionFromSabrVolSurface"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSmileSectionVariance"),
            // parameter codes
            TempStrNoSize("\x05""ECPP#"),
            // function display name
            TempStrNoSize("\x16""qlSmileSectionVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Strike,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the variance at a given strike from the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSmileSectionVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSmileSectionVolatility"),
            // parameter codes
            TempStrNoSize("\x05""ECPP#"),
            // function display name
            TempStrNoSize("\x18""qlSmileSectionVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""ObjectId,Strike,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns the volatility at a given strike from the SmileSection object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::SmileSection object"),
            TempStrNoSize("\x39""strike. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSmileSectionVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

