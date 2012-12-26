
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

// register functions in category Leg with Excel

void registerLeg(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlInterestRate"),
            // parameter codes
            TempStrNoSize("\x0A""CCECCPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlInterestRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4A""ObjectId,Rate,DayCounter,Compounding,Frequency,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class InterestRate and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x05""rate."),
            TempStrNoSize("\x12""Irr DayCounter ID."),
            TempStrNoSize("\x55""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt})."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateCompoundFactor"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateCompoundFactor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the compound factor between two dates based on the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInterestRateCompounding"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x19""qlInterestRateCompounding"),
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
            TempStrNoSize("\x39""Returns the Compounding in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterestRateDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterestRateDayCounter"),
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
            TempStrNoSize("\x38""Returns the DayCounter in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateDiscountFactor"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateDiscountFactor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the discount factor between two dates based on the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateEquivalentRate"),
            // parameter codes
            TempStrNoSize("\x0B""PCCCPPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateEquivalentRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,DayCounter,Compounding,Frequency,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6E""Returns the equivalent rate for a compounding period between two dates based on the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x13""rate DayCounter ID."),
            TempStrNoSize("\x55""interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt})."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlInterestRateFrequency"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x17""qlInterestRateFrequency"),
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
            TempStrNoSize("\x37""Returns the Frequency in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInterestRateImpliedRate"),
            // parameter codes
            TempStrNoSize("\x0B""PECCPPPPPP#"),
            // function display name
            TempStrNoSize("\x19""qlInterestRateImpliedRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""Compound,DayCounter,Compounding,Frequency,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the implied rate between two dates based on the given a compound factor."),
            // parameter descriptions
            TempStrNoSize("\x34""compound factor used to calculate the implicit rate."),
            TempStrNoSize("\x13""rate DayCounter ID."),
            TempStrNoSize("\x55""interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt})."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlInterestRateRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlInterestRateRate"),
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
            TempStrNoSize("\x32""Returns the rate in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x05""qlLeg"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x05""qlLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Amounts,Dates,ToBeSorted,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Construct an object of class Leg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""list of cash to be received/paid."),
            TempStrNoSize("\x27""payment dates corresponding to amounts."),
            TempStrNoSize("\x4E""TRUE if the CashFlows must be sorted by ascending dates. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlLegAccrualDays"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x10""qlLegAccrualDays"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""Returns the total number of accrual days for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x13""qlLegAccrualEndDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x13""qlLegAccrualEndDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns the accrual end date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlLegAccrualPeriod"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x12""qlLegAccrualPeriod"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the total accrual period for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlLegAccrualStartDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x15""qlLegAccrualStartDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the accrual start date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlLegAccruedAmount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x12""qlLegAccruedAmount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2D""Returns the accrued amount for the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlLegAccruedDays"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x10""qlLegAccruedDays"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Returns the accrued days for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlLegAccruedPeriod"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x12""qlLegAccruedPeriod"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns the accrued period for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlLegAtmRate"),
            // parameter codes
            TempStrNoSize("\x09""ECCPPPPP#"),
            // function display name
            TempStrNoSize("\x0C""qlLegAtmRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4A""ObjectId,DiscountCurve,IncludeSettlDate,SettlementDate,NpvDate,NPV,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x9C""Returns the at-the-money rate for the given Leg object, i.e. the fixed rate for which an equivalent vector of fixed-rate cash flows would have the same NPV."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x8E""target net present value. If missing the NPV is calculated using the provided discount curve Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x08""qlLegBPS"),
            // parameter codes
            TempStrNoSize("\x08""ECCPPPP#"),
            // function display name
            TempStrNoSize("\x08""qlLegBPS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,DiscountCurve,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the basis point sensitivity for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegBPSFromYield"),
            // parameter codes
            TempStrNoSize("\x0B""ECEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlLegBPSFromYield"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the basis point sensitivity for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlLegBasisPointValue"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x14""qlLegBasisPointValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Returns the basisPointValue for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlLegConvexity"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlLegConvexity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns the Cash-flow convexity for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlLegDuration"),
            // parameter codes
            TempStrNoSize("\x0C""ECEPPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlLegDuration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6C""ObjectId,Yield,DayCounter,Compounding,Frequency,DurationType,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Returns the Cash-flow duration for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x48""Duration type (Simple, Macaulay, or Modified). Default value = Modified."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegFlowAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x11""qlLegFlowAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,AfterDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""Returns the flow analysis for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLibAddin::Leg object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegFromCapFloor"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x11""qlLegFromCapFloor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2D""ObjectId,CapFloor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Construct an object of class Leg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""CapFloor object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlLegFromSwap"),
            // parameter codes
            TempStrNoSize("\x08""CCCNPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlLegFromSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Swap,LegNumber,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Construct an object of class Leg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0F""Swap object ID."),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlLegIsExpired"),
            // parameter codes
            TempStrNoSize("\x06""LCPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlLegIsExpired"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x22""Returns TRUE is the Leg is expired"),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegMaturityDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x11""qlLegMaturityDate"),
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
            TempStrNoSize("\x47""Returns the maturity (i.e. last payment) date for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x08""qlLegNPV"),
            // parameter codes
            TempStrNoSize("\x08""ECCPPPP#"),
            // function display name
            TempStrNoSize("\x08""qlLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,DiscountCurve,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Returns the net present value for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegNPVFromYield"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlLegNPVFromYield"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Returns the net present value for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x13""qlLegNPVFromZSpread"),
            // parameter codes
            TempStrNoSize("\x0C""PCCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x13""qlLegNPVFromZSpread"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6F""ObjectId,DiscountCurve,ZSpread,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Returns the net present value for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x09""Z-spread."),
            TempStrNoSize("\x56""Not Used: DiscountCurve's DayCounter used instead. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlLegNextCashFlowAmount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x17""qlLegNextCashFlowAmount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x22""Returns the next cash flow amount."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlLegNextCashFlowDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x15""qlLegNextCashFlowDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Returns the next cash flow date."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x13""qlLegNextCouponRate"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x13""qlLegNextCouponRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xDC""Returns the next coupon rate. Depending on (the Leg and) the given date it can be historic, deterministic or expected in a stochastic sense. When the current date is used the coupon is the already-fixed not-yet-paid one."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlLegNominal"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x0C""qlLegNominal"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the nominal for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlLegPreviousCashFlowAmount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlLegPreviousCashFlowAmount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""Returns the previous cash flow amount."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlLegPreviousCashFlowDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlLegPreviousCashFlowDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""Returns the previous cash flow date."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlLegPreviousCouponRate"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x17""qlLegPreviousCouponRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xCF""Returns the previous coupon rate. Depending on (the Leg and) the given date it can be historic, deterministic or expected in a stochastic sense. When the current date is used the coupon is the last paid one."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlLegReferencePeriodEnd"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x17""qlLegReferencePeriodEnd"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the reference period end date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlLegReferencePeriodStart"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlLegReferencePeriodStart"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the reference period start date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlLegSetCouponPricers"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x15""qlLegSetCouponPricers"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,FloatingRateCouponPricer,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""Set the coupon pricer at the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLibAddin::Leg object"),
            TempStrNoSize("\x25""FloatingRate coupon pricer object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlLegStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0E""qlLegStartDate"),
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
            TempStrNoSize("\x45""Returns the start (i.e. first accrual) date for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlLegYield"),
            // parameter codes
            TempStrNoSize("\x0E""ECECPPPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0A""qlLegYield"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7A""ObjectId,NPV,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Accuracy,MaxIterations,Guess,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the Internal rate of return for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1A""Net present (dirty) value."),
            TempStrNoSize("\x12""Irr DayCounter ID."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x23""tolerance. Default value = 1.0e-10."),
            TempStrNoSize("\x2E""max number of iterations. Default value = 100."),
            TempStrNoSize("\x1C""guess. Default value = 0.05."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlLegYieldValueBasisPoint"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x19""qlLegYieldValueBasisPoint"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns the yieldValueBasisPoint for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlLegZSpread"),
            // parameter codes
            TempStrNoSize("\x0F""ECECPPPPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0C""qlLegZSpread"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x88""ObjectId,NPV,DiscountCurve,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Accuracy,MaxIterations,Guess,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""Returns the z-spread for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1A""Net present (dirty) value."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x56""Not Used: DiscountCurve's DayCounter used instead. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x8F""cashflows before this date are not taken into account. If missing it defaults to the current evaluation date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x23""tolerance. Default value = 1.0e-10."),
            TempStrNoSize("\x2E""max number of iterations. Default value = 100."),
            TempStrNoSize("\x1B""guess. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlMultiPhaseLeg"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlMultiPhaseLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,LegIDs,ToBeSorted,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class MultiPhaseLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x23""leg object IDs, one for each phase."),
            TempStrNoSize("\x4E""TRUE if the CashFlows must be sorted by ascending dates. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Leg with Excel

void unregisterLeg(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlInterestRate"),
            // parameter codes
            TempStrNoSize("\x0A""CCECCPPPL#"),
            // function display name
            TempStrNoSize("\x0E""qlInterestRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4A""ObjectId,Rate,DayCounter,Compounding,Frequency,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3B""Construct an object of class InterestRate and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x05""rate."),
            TempStrNoSize("\x12""Irr DayCounter ID."),
            TempStrNoSize("\x55""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt})."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlInterestRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateCompoundFactor"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateCompoundFactor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the compound factor between two dates based on the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInterestRateCompoundFactor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInterestRateCompounding"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x19""qlInterestRateCompounding"),
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
            TempStrNoSize("\x39""Returns the Compounding in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlInterestRateCompounding"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterestRateDayCounter"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterestRateDayCounter"),
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
            TempStrNoSize("\x38""Returns the DayCounter in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterestRateDayCounter"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateDiscountFactor"),
            // parameter codes
            TempStrNoSize("\x08""PCPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateDiscountFactor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns the discount factor between two dates based on the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInterestRateDiscountFactor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterestRateEquivalentRate"),
            // parameter codes
            TempStrNoSize("\x0B""PCCCPPPPPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterestRateEquivalentRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,DayCounter,Compounding,Frequency,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x6E""Returns the equivalent rate for a compounding period between two dates based on the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x13""rate DayCounter ID."),
            TempStrNoSize("\x55""interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt})."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInterestRateEquivalentRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlInterestRateFrequency"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x17""qlInterestRateFrequency"),
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
            TempStrNoSize("\x37""Returns the Frequency in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlInterestRateFrequency"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInterestRateImpliedRate"),
            // parameter codes
            TempStrNoSize("\x0B""PECCPPPPPP#"),
            // function display name
            TempStrNoSize("\x19""qlInterestRateImpliedRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""Compound,DayCounter,Compounding,Frequency,StartDate,EndDate,RefPeriodStart,RefPeriodEnd,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the implied rate between two dates based on the given a compound factor."),
            // parameter descriptions
            TempStrNoSize("\x34""compound factor used to calculate the implicit rate."),
            TempStrNoSize("\x13""rate DayCounter ID."),
            TempStrNoSize("\x55""interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt})."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x19""compounding period start."),
            TempStrNoSize("\x17""compounding period end."),
            TempStrNoSize("\x58""reference period start date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x56""reference period end date needed by some daycounter. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlInterestRateImpliedRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlInterestRateRate"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x12""qlInterestRateRate"),
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
            TempStrNoSize("\x32""Returns the rate in the given InterestRate object."),
            // parameter descriptions
            TempStrNoSize("\x2C""id of existing QuantLib::InterestRate object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlInterestRateRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x05""qlLeg"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x05""qlLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""ObjectId,Amounts,Dates,ToBeSorted,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Construct an object of class Leg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""list of cash to be received/paid."),
            TempStrNoSize("\x27""payment dates corresponding to amounts."),
            TempStrNoSize("\x4E""TRUE if the CashFlows must be sorted by ascending dates. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x05""qlLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlLegAccrualDays"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x10""qlLegAccrualDays"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x51""Returns the total number of accrual days for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlLegAccrualDays"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x13""qlLegAccrualEndDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x13""qlLegAccrualEndDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x45""Returns the accrual end date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlLegAccrualEndDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlLegAccrualPeriod"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x12""qlLegAccrualPeriod"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the total accrual period for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlLegAccrualPeriod"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlLegAccrualStartDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x15""qlLegAccrualStartDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the accrual start date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlLegAccrualStartDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlLegAccruedAmount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x12""qlLegAccruedAmount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2D""Returns the accrued amount for the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlLegAccruedAmount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x10""qlLegAccruedDays"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x10""qlLegAccruedDays"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Returns the accrued days for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x10""qlLegAccruedDays"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x12""qlLegAccruedPeriod"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x12""qlLegAccruedPeriod"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Returns the accrued period for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlLegAccruedPeriod"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlLegAtmRate"),
            // parameter codes
            TempStrNoSize("\x09""ECCPPPPP#"),
            // function display name
            TempStrNoSize("\x0C""qlLegAtmRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4A""ObjectId,DiscountCurve,IncludeSettlDate,SettlementDate,NpvDate,NPV,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x9C""Returns the at-the-money rate for the given Leg object, i.e. the fixed rate for which an equivalent vector of fixed-rate cash flows would have the same NPV."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x8E""target net present value. If missing the NPV is calculated using the provided discount curve Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlLegAtmRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x08""qlLegBPS"),
            // parameter codes
            TempStrNoSize("\x08""ECCPPPP#"),
            // function display name
            TempStrNoSize("\x08""qlLegBPS"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,DiscountCurve,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the basis point sensitivity for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x08""qlLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegBPSFromYield"),
            // parameter codes
            TempStrNoSize("\x0B""ECEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlLegBPSFromYield"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the basis point sensitivity for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlLegBPSFromYield"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlLegBasisPointValue"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x14""qlLegBasisPointValue"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x35""Returns the basisPointValue for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlLegBasisPointValue"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlLegConvexity"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlLegConvexity"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x39""Returns the Cash-flow convexity for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlLegConvexity"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlLegDuration"),
            // parameter codes
            TempStrNoSize("\x0C""ECEPPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0D""qlLegDuration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6C""ObjectId,Yield,DayCounter,Compounding,Frequency,DurationType,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Returns the Cash-flow duration for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x48""Duration type (Simple, Macaulay, or Modified). Default value = Modified."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlLegDuration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegFlowAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x11""qlLegFlowAnalysis"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1A""ObjectId,AfterDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x33""Returns the flow analysis for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLibAddin::Leg object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlLegFlowAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegFromCapFloor"),
            // parameter codes
            TempStrNoSize("\x07""CCCPPL#"),
            // function display name
            TempStrNoSize("\x11""qlLegFromCapFloor"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2D""ObjectId,CapFloor,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Construct an object of class Leg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""CapFloor object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlLegFromCapFloor"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlLegFromSwap"),
            // parameter codes
            TempStrNoSize("\x08""CCCNPPL#"),
            // function display name
            TempStrNoSize("\x0D""qlLegFromSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x33""ObjectId,Swap,LegNumber,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x32""Construct an object of class Leg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x0F""Swap object ID."),
            TempStrNoSize("\x51""Zero based leg number (e.g. use 0 for the first leg, 1 for the second leg, etc.)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlLegFromSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlLegIsExpired"),
            // parameter codes
            TempStrNoSize("\x06""LCPPP#"),
            // function display name
            TempStrNoSize("\x0E""qlLegIsExpired"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x22""Returns TRUE is the Leg is expired"),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlLegIsExpired"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegMaturityDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x11""qlLegMaturityDate"),
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
            TempStrNoSize("\x47""Returns the maturity (i.e. last payment) date for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlLegMaturityDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x08""qlLegNPV"),
            // parameter codes
            TempStrNoSize("\x08""ECCPPPP#"),
            // function display name
            TempStrNoSize("\x08""qlLegNPV"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x46""ObjectId,DiscountCurve,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Returns the net present value for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x08""qlLegNPV"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x11""qlLegNPVFromYield"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x11""qlLegNPVFromYield"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Returns the net present value for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlLegNPVFromYield"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x13""qlLegNPVFromZSpread"),
            // parameter codes
            TempStrNoSize("\x0C""PCCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x13""qlLegNPVFromZSpread"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x6F""ObjectId,DiscountCurve,ZSpread,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x37""Returns the net present value for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x09""Z-spread."),
            TempStrNoSize("\x56""Not Used: DiscountCurve's DayCounter used instead. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlLegNPVFromZSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlLegNextCashFlowAmount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x17""qlLegNextCashFlowAmount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x22""Returns the next cash flow amount."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlLegNextCashFlowAmount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x15""qlLegNextCashFlowDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x15""qlLegNextCashFlowDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x20""Returns the next cash flow date."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlLegNextCashFlowDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x13""qlLegNextCouponRate"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x13""qlLegNextCouponRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xDC""Returns the next coupon rate. Depending on (the Leg and) the given date it can be historic, deterministic or expected in a stochastic sense. When the current date is used the coupon is the already-fixed not-yet-paid one."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlLegNextCouponRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlLegNominal"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x0C""qlLegNominal"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the nominal for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlLegNominal"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlLegPreviousCashFlowAmount"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1B""qlLegPreviousCashFlowAmount"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""Returns the previous cash flow amount."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlLegPreviousCashFlowAmount"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlLegPreviousCashFlowDate"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlLegPreviousCashFlowDate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""Returns the previous cash flow date."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlLegPreviousCashFlowDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlLegPreviousCouponRate"),
            // parameter codes
            TempStrNoSize("\x06""ECPPP#"),
            // function display name
            TempStrNoSize("\x17""qlLegPreviousCouponRate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\xCF""Returns the previous coupon rate. Depending on (the Leg and) the given date it can be historic, deterministic or expected in a stochastic sense. When the current date is used the coupon is the last paid one."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlLegPreviousCouponRate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x17""qlLegReferencePeriodEnd"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x17""qlLegReferencePeriodEnd"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the reference period end date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlLegReferencePeriodEnd"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlLegReferencePeriodStart"),
            // parameter codes
            TempStrNoSize("\x06""NCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlLegReferencePeriodStart"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x30""ObjectId,IncludeSettlDate,SettlementDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x50""Returns the reference period start date for the current coupon of the given Leg."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlLegReferencePeriodStart"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x15""qlLegSetCouponPricers"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x15""qlLegSetCouponPricers"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x29""ObjectId,FloatingRateCouponPricer,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""Set the coupon pricer at the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x28""id of existing QuantLibAddin::Leg object"),
            TempStrNoSize("\x25""FloatingRate coupon pricer object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlLegSetCouponPricers"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0E""qlLegStartDate"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x0E""qlLegStartDate"),
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
            TempStrNoSize("\x45""Returns the start (i.e. first accrual) date for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0E""qlLegStartDate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlLegYield"),
            // parameter codes
            TempStrNoSize("\x0E""ECECPPPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0A""qlLegYield"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x7A""ObjectId,NPV,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Accuracy,MaxIterations,Guess,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3D""Returns the Internal rate of return for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1A""Net present (dirty) value."),
            TempStrNoSize("\x12""Irr DayCounter ID."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x23""tolerance. Default value = 1.0e-10."),
            TempStrNoSize("\x2E""max number of iterations. Default value = 100."),
            TempStrNoSize("\x1C""guess. Default value = 0.05."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlLegYield"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x19""qlLegYieldValueBasisPoint"),
            // parameter codes
            TempStrNoSize("\x0B""PCEPPPPPPP#"),
            // function display name
            TempStrNoSize("\x19""qlLegYieldValueBasisPoint"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5F""ObjectId,Yield,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns the yieldValueBasisPoint for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x13""Yield (a.k.a. IRR)."),
            TempStrNoSize("\x3A""Yield DayCounter ID. Default value = Actual/Actual (ISDA)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Compounded."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x87""cashflows before this date are not taken into account. If missing the current EvaluationDate is used. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlLegYieldValueBasisPoint"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlLegZSpread"),
            // parameter codes
            TempStrNoSize("\x0F""ECECPPPPPPPPPP#"),
            // function display name
            TempStrNoSize("\x0C""qlLegZSpread"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x88""ObjectId,NPV,DiscountCurve,DayCounter,Compounding,Frequency,IncludeSettlDate,SettlementDate,NpvDate,Accuracy,MaxIterations,Guess,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2E""Returns the z-spread for the given Leg object."),
            // parameter descriptions
            TempStrNoSize("\x23""id of existing QuantLib::Leg object"),
            TempStrNoSize("\x1A""Net present (dirty) value."),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x56""Not Used: DiscountCurve's DayCounter used instead. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x71""Interest rate coumpounding rule (Simple:1+rt, Compounded:(1+r)^t, Continuous:e^{rt}). Default value = Continuous."),
            TempStrNoSize("\x68""frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly). Default value = Annual."),
            TempStrNoSize("\x5F""TRUE if cashflows paid at the settlement date must be taken into account. Default value = true."),
            TempStrNoSize("\x8F""cashflows before this date are not taken into account. If missing it defaults to the current evaluation date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x82""all cashflows are discounted to this date. If missing it is assumed equal to the settlement date Default value = QuantLib::Date()."),
            TempStrNoSize("\x23""tolerance. Default value = 1.0e-10."),
            TempStrNoSize("\x2E""max number of iterations. Default value = 100."),
            TempStrNoSize("\x1B""guess. Default value = 0.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlLegZSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlMultiPhaseLeg"),
            // parameter codes
            TempStrNoSize("\x08""CCPPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlMultiPhaseLeg"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x36""ObjectId,LegIDs,ToBeSorted,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class MultiPhaseLeg and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x23""leg object IDs, one for each phase."),
            TempStrNoSize("\x4E""TRUE if the CashFlows must be sorted by ascending dates. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlMultiPhaseLeg"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

