
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

// register functions in category Volatilities with Excel

void registerVolatilities(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x11""qlAbcdAtmVolCurve"),
            // parameter codes
            TempStrNoSize("\x0D""CCNCPPPCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlAbcdAtmVolCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8B""ObjectId,SettlementDays,Calendar,OptionTenors,VolatilitiesQuotes,InclusionInInterpolation,Convention,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class AbcdAtmVolCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""settlement days."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x0F""options tenors."),
            TempStrNoSize("\x14""volatilities quotes."),
            TempStrNoSize("\x3F""inclusion flags. If omitted, all volatilities are interpolated."),
            TempStrNoSize("\x29""business day convention (e.g. Following)."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveA"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveA"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveB"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveB"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveC"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveC"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveD"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveD"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveK"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveK"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Time,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x57""Returns the k adjustments factors needed to match the input Black vols at a given time."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x05""time."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlAbcdAtmVolCurveKatOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x20""qlAbcdAtmVolCurveKatOptionTenors"),
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
            TempStrNoSize("\x47""Returns the k adjustments factors needed to match the input Black vols."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveMaxError"),
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
            TempStrNoSize("\x5A""Returns the max error between the abcd implied Black vols and the given Black vols vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionDates"),
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
            TempStrNoSize("\x36""Returns the options dates of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlAbcdAtmVolCurveOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlAbcdAtmVolCurveOptionTenors"),
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
            TempStrNoSize("\x37""Returns the options tenors of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlAbcdAtmVolCurveOptionTenorsInInterpolation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlAbcdAtmVolCurveOptionTenorsInInterpolation"),
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
            TempStrNoSize("\x4B""Returns the options tenors used in the fitting of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionTimes"),
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
            TempStrNoSize("\x42""Returns the options times to maturity of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveRmsError"),
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
            TempStrNoSize("\x68""Returns the root mean squared error between the abcd implied Black vols and the given Black vols vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlAtmCurve"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0A""qlAtmCurve"),
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
            TempStrNoSize("\x21""Returns the Atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x33""id of existing QuantLibAddin::SabrVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackAtmVolCurveAtmVariance"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackAtmVolCurveAtmVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionDate,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the spot at-the-money (no-smile) variance at a given option date."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance2"),
            // parameter codes
            TempStrNoSize("\x06""ECCPP#"),
            // function display name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,OptionTenor,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Returns the spot at-the-money (no-smile) variance at a given option tenor."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2F""The tenor at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance3"),
            // parameter codes
            TempStrNoSize("\x06""ECEPP#"),
            // function display name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance3"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionTime,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the spot at-the-money (no-smile) variance at a given option time."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The time at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlBlackAtmVolCurveAtmVol"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x18""qlBlackAtmVolCurveAtmVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionDate,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the spot at-the-money (no-smile) volatility at a given option date."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol2"),
            // parameter codes
            TempStrNoSize("\x06""ECCPP#"),
            // function display name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,OptionTenor,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the spot at-the-money (no-smile) volatility at a given option tenor."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The time at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol3"),
            // parameter codes
            TempStrNoSize("\x06""ECEPP#"),
            // function display name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol3"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionTime,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the spot at-the-money (no-smile) volatility at a given option time."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The time at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x12""qlBlackConstantVol"),
            // parameter codes
            TempStrNoSize("\x0A""CCPCEPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlBlackConstantVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,SettlementDate,Calendar,Volatility,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class BlackConstantVol and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""settlement date."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x0B""volatility."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackVarianceSurface"),
            // parameter codes
            TempStrNoSize("\x0C""CCPCPPKPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackVarianceSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x62""ObjectId,SettlementDate,Calendar,Dates,Strikes,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class BlackVarianceSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""settlement date."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x06""dates."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlBlackVolTermStructureBlackForwardVariance"),
            // parameter codes
            TempStrNoSize("\x08""PCPPEPP#"),
            // function display name
            TempStrNoSize("\x2B""qlBlackVolTermStructureBlackForwardVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,ForwardDate,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x54""Returns the black forward (at-the-money) variance at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x36""The forward date at which the volatility is evaluated."),
            TempStrNoSize("\x2C""The date at which the variance is evaluated."),
            TempStrNoSize("\x2E""The strike at which the variance is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x26""qlBlackVolTermStructureBlackForwardVol"),
            // parameter codes
            TempStrNoSize("\x08""ECPPEPP#"),
            // function display name
            TempStrNoSize("\x26""qlBlackVolTermStructureBlackForwardVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,ForwardDate,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x56""Returns the black forward (at-the-money) volatility at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x36""The forward date at which the volatility is evaluated."),
            TempStrNoSize("\x35""The option date at which the volatility is evaluated."),
            TempStrNoSize("\x30""The strike at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x24""qlBlackVolTermStructureBlackVariance"),
            // parameter codes
            TempStrNoSize("\x07""PCPEPP#"),
            // function display name
            TempStrNoSize("\x24""qlBlackVolTermStructureBlackVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns the black spot variance at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x2C""The date at which the variance is evaluated."),
            TempStrNoSize("\x2E""The strike at which the variance is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlBlackVolTermStructureBlackVol"),
            // parameter codes
            TempStrNoSize("\x07""ECPEPP#"),
            // function display name
            TempStrNoSize("\x1F""qlBlackVolTermStructureBlackVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the black spot volatility at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x30""The strike at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSabrVolSurface"),
            // parameter codes
            TempStrNoSize("\x0B""CCCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlSabrVolSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x76""ObjectId,InterestRateIndex,BlackAtmVolCurve,OptionTenors,AtmRateSpreads,VolatilitiesQuotes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class SabrVolSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""interest rate index object ID."),
            TempStrNoSize("\x19""the atm volatility curve."),
            TempStrNoSize("\x0F""options tenors."),
            TempStrNoSize("\x08""spreads."),
            TempStrNoSize("\x14""volatilities quotes."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSabrVolatility"),
            // parameter codes
            TempStrNoSize("\x0A""EEEEEEEEP#"),
            // function display name
            TempStrNoSize("\x10""qlSabrVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""Strike,Forward,ExpTime,Alpha,Beta,Nu,Rho,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x22""Sabr formula for smile volatility."),
            // parameter descriptions
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x19""underlying forward value."),
            TempStrNoSize("\x17""expiry time (in years)."),
            TempStrNoSize("\x06""alpha."),
            TempStrNoSize("\x05""beta."),
            TempStrNoSize("\x03""nu."),
            TempStrNoSize("\x04""rho."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlVolatilitySpreads"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x13""qlVolatilitySpreads"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,OptionDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the volatilities spread at a given date."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SabrVolSurface object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlVolatilitySpreads2"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x14""qlVolatilitySpreads2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,OptionTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the volatilities spread at a given date."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SabrVolSurface object"),
            TempStrNoSize("\x2F""The tenor at which the volatility is evaluated."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2E""qlVolatilityTermStructureBusinessDayConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x2E""qlVolatilityTermStructureBusinessDayConvention"),
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
            TempStrNoSize("\x45""Returns the business day convention used in tenor to date conversion."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlVolatilityTermStructureMaxStrike"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlVolatilityTermStructureMaxStrike"),
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
            TempStrNoSize("\x57""Returns the maximum strike for which the given VolatilityTermStructure can return vols."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlVolatilityTermStructureMinStrike"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlVolatilityTermStructureMinStrike"),
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
            TempStrNoSize("\x57""Returns the minimum strike for which the given VolatilityTermStructure can return vols."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlVolatilityTermStructureOptionDateFromTenor"),
            // parameter codes
            TempStrNoSize("\x05""NCCP#"),
            // function display name
            TempStrNoSize("\x2C""qlVolatilityTermStructureOptionDateFromTenor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Tenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the option date corrisponding to a given option tenor."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x0D""option tenor."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Volatilities with Excel

void unregisterVolatilities(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x11""qlAbcdAtmVolCurve"),
            // parameter codes
            TempStrNoSize("\x0D""CCNCPPPCPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlAbcdAtmVolCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8B""ObjectId,SettlementDays,Calendar,OptionTenors,VolatilitiesQuotes,InclusionInInterpolation,Convention,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class AbcdAtmVolCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""settlement days."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x0F""options tenors."),
            TempStrNoSize("\x14""volatilities quotes."),
            TempStrNoSize("\x3F""inclusion flags. If omitted, all volatilities are interpolated."),
            TempStrNoSize("\x29""business day convention (e.g. Following)."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlAbcdAtmVolCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveA"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveA"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdAtmVolCurveA"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveB"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveB"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdAtmVolCurveB"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveC"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveC"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdAtmVolCurveC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveD"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveD"),
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
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdAtmVolCurveD"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveK"),
            // parameter codes
            TempStrNoSize("\x05""PCEP#"),
            // function display name
            TempStrNoSize("\x12""qlAbcdAtmVolCurveK"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x15""ObjectId,Time,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x57""Returns the k adjustments factors needed to match the input Black vols at a given time."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x05""time."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAbcdAtmVolCurveK"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlAbcdAtmVolCurveKatOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x20""qlAbcdAtmVolCurveKatOptionTenors"),
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
            TempStrNoSize("\x47""Returns the k adjustments factors needed to match the input Black vols."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlAbcdAtmVolCurveKatOptionTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveMaxError"),
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
            TempStrNoSize("\x5A""Returns the max error between the abcd implied Black vols and the given Black vols vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlAbcdAtmVolCurveMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionDates"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionDates"),
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
            TempStrNoSize("\x36""Returns the options dates of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionDates"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlAbcdAtmVolCurveOptionTenors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1D""qlAbcdAtmVolCurveOptionTenors"),
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
            TempStrNoSize("\x37""Returns the options tenors of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlAbcdAtmVolCurveOptionTenors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlAbcdAtmVolCurveOptionTenorsInInterpolation"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlAbcdAtmVolCurveOptionTenorsInInterpolation"),
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
            TempStrNoSize("\x4B""Returns the options tenors used in the fitting of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlAbcdAtmVolCurveOptionTenorsInInterpolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionTimes"),
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
            TempStrNoSize("\x42""Returns the options times to maturity of the atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlAbcdAtmVolCurveOptionTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlAbcdAtmVolCurveRmsError"),
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
            TempStrNoSize("\x68""Returns the root mean squared error between the abcd implied Black vols and the given Black vols vector."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::AbcdAtmVolCurve object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlAbcdAtmVolCurveRmsError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlAtmCurve"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x0A""qlAtmCurve"),
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
            TempStrNoSize("\x21""Returns the Atm volatility curve."),
            // parameter descriptions
            TempStrNoSize("\x33""id of existing QuantLibAddin::SabrVolSurface object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlAtmCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlBlackAtmVolCurveAtmVariance"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x1D""qlBlackAtmVolCurveAtmVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionDate,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the spot at-the-money (no-smile) variance at a given option date."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlBlackAtmVolCurveAtmVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance2"),
            // parameter codes
            TempStrNoSize("\x06""ECCPP#"),
            // function display name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,OptionTenor,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Returns the spot at-the-money (no-smile) variance at a given option tenor."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2F""The tenor at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance3"),
            // parameter codes
            TempStrNoSize("\x06""ECEPP#"),
            // function display name
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance3"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionTime,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the spot at-the-money (no-smile) variance at a given option time."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The time at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlBlackAtmVolCurveAtmVariance3"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlBlackAtmVolCurveAtmVol"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x18""qlBlackAtmVolCurveAtmVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionDate,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the spot at-the-money (no-smile) volatility at a given option date."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlBlackAtmVolCurveAtmVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol2"),
            // parameter codes
            TempStrNoSize("\x06""ECCPP#"),
            // function display name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2F""ObjectId,OptionTenor,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the spot at-the-money (no-smile) volatility at a given option tenor."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The time at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol3"),
            // parameter codes
            TempStrNoSize("\x06""ECEPP#"),
            // function display name
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol3"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2E""ObjectId,OptionTime,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the spot at-the-money (no-smile) volatility at a given option time."),
            // parameter descriptions
            TempStrNoSize("\x30""id of existing QuantLib::BlackAtmVolCurve object"),
            TempStrNoSize("\x2E""The time at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlBlackAtmVolCurveAtmVol3"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x12""qlBlackConstantVol"),
            // parameter codes
            TempStrNoSize("\x0A""CCPCEPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlBlackConstantVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,SettlementDate,Calendar,Volatility,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class BlackConstantVol and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""settlement date."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x0B""volatility."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlBlackConstantVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x16""qlBlackVarianceSurface"),
            // parameter codes
            TempStrNoSize("\x0C""CCPCPPKPPPL#"),
            // function display name
            TempStrNoSize("\x16""qlBlackVarianceSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x62""ObjectId,SettlementDate,Calendar,Dates,Strikes,Volatilities,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class BlackVarianceSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x10""settlement date."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x06""dates."),
            TempStrNoSize("\x08""strikes."),
            TempStrNoSize("\x0D""volatilities."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlBlackVarianceSurface"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlBlackVolTermStructureBlackForwardVariance"),
            // parameter codes
            TempStrNoSize("\x08""PCPPEPP#"),
            // function display name
            TempStrNoSize("\x2B""qlBlackVolTermStructureBlackForwardVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,ForwardDate,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x54""Returns the black forward (at-the-money) variance at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x36""The forward date at which the volatility is evaluated."),
            TempStrNoSize("\x2C""The date at which the variance is evaluated."),
            TempStrNoSize("\x2E""The strike at which the variance is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlBlackVolTermStructureBlackForwardVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x26""qlBlackVolTermStructureBlackForwardVol"),
            // parameter codes
            TempStrNoSize("\x08""ECPPEPP#"),
            // function display name
            TempStrNoSize("\x26""qlBlackVolTermStructureBlackForwardVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x41""ObjectId,ForwardDate,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x56""Returns the black forward (at-the-money) volatility at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x36""The forward date at which the volatility is evaluated."),
            TempStrNoSize("\x35""The option date at which the volatility is evaluated."),
            TempStrNoSize("\x30""The strike at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlBlackVolTermStructureBlackForwardVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x24""qlBlackVolTermStructureBlackVariance"),
            // parameter codes
            TempStrNoSize("\x07""PCPEPP#"),
            // function display name
            TempStrNoSize("\x24""qlBlackVolTermStructureBlackVariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns the black spot variance at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x2C""The date at which the variance is evaluated."),
            TempStrNoSize("\x2E""The strike at which the variance is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x24""qlBlackVolTermStructureBlackVariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlBlackVolTermStructureBlackVol"),
            // parameter codes
            TempStrNoSize("\x07""ECPEPP#"),
            // function display name
            TempStrNoSize("\x1F""qlBlackVolTermStructureBlackVol"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x35""ObjectId,OptionDate,Strike,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the black spot volatility at a given option date and strike."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::BlackVolTermStructure object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x30""The strike at which the volatility is evaluated."),
            TempStrNoSize("\x46""Extrapolation Flag (TRUE allows extrapolation). Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlBlackVolTermStructureBlackVol"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSabrVolSurface"),
            // parameter codes
            TempStrNoSize("\x0B""CCCCPPPPPL#"),
            // function display name
            TempStrNoSize("\x10""qlSabrVolSurface"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x76""ObjectId,InterestRateIndex,BlackAtmVolCurve,OptionTenors,AtmRateSpreads,VolatilitiesQuotes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Construct an object of class SabrVolSurface and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1E""interest rate index object ID."),
            TempStrNoSize("\x19""the atm volatility curve."),
            TempStrNoSize("\x0F""options tenors."),
            TempStrNoSize("\x08""spreads."),
            TempStrNoSize("\x14""volatilities quotes."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlSabrVolSurface"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x10""qlSabrVolatility"),
            // parameter codes
            TempStrNoSize("\x0A""EEEEEEEEP#"),
            // function display name
            TempStrNoSize("\x10""qlSabrVolatility"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""Strike,Forward,ExpTime,Alpha,Beta,Nu,Rho,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x22""Sabr formula for smile volatility."),
            // parameter descriptions
            TempStrNoSize("\x0E""option strike."),
            TempStrNoSize("\x19""underlying forward value."),
            TempStrNoSize("\x17""expiry time (in years)."),
            TempStrNoSize("\x06""alpha."),
            TempStrNoSize("\x05""beta."),
            TempStrNoSize("\x03""nu."),
            TempStrNoSize("\x04""rho."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlSabrVolatility"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x13""qlVolatilitySpreads"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x13""qlVolatilitySpreads"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,OptionDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the volatilities spread at a given date."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SabrVolSurface object"),
            TempStrNoSize("\x2E""The date at which the volatility is evaluated."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlVolatilitySpreads"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x14""qlVolatilitySpreads2"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x14""qlVolatilitySpreads2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1C""ObjectId,OptionTenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x30""Returns the volatilities spread at a given date."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLib::SabrVolSurface object"),
            TempStrNoSize("\x2F""The tenor at which the volatility is evaluated."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlVolatilitySpreads2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2E""qlVolatilityTermStructureBusinessDayConvention"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x2E""qlVolatilityTermStructureBusinessDayConvention"),
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
            TempStrNoSize("\x45""Returns the business day convention used in tenor to date conversion."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2E""qlVolatilityTermStructureBusinessDayConvention"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlVolatilityTermStructureMaxStrike"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlVolatilityTermStructureMaxStrike"),
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
            TempStrNoSize("\x57""Returns the maximum strike for which the given VolatilityTermStructure can return vols."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlVolatilityTermStructureMaxStrike"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlVolatilityTermStructureMinStrike"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x22""qlVolatilityTermStructureMinStrike"),
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
            TempStrNoSize("\x57""Returns the minimum strike for which the given VolatilityTermStructure can return vols."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlVolatilityTermStructureMinStrike"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlVolatilityTermStructureOptionDateFromTenor"),
            // parameter codes
            TempStrNoSize("\x05""NCCP#"),
            // function display name
            TempStrNoSize("\x2C""qlVolatilityTermStructureOptionDateFromTenor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Tenor,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the option date corrisponding to a given option tenor."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::VolatilityTermStructure object"),
            TempStrNoSize("\x0D""option tenor."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlVolatilityTermStructureOptionDateFromTenor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

