
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

// register functions in category Credit with Excel

void registerCredit(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // parameter codes
            TempStrNoSize("\x11""CCPEEECPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAD""ObjectId,BuyerSeller,Notional,Upfront,Spread,PremiumSchedule,PaymentConvention,DayCounter,SettlesAccrual,PayAtDefault,ProtectionStart,UpfrontDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class CreditDefaultSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x0E""Nominal amount"),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x38""protection start date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x2F""upfront date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x45""ObjectId,CurveDates,CurveRates,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class HazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x21""hazard rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // parameter codes
            TempStrNoSize("\x09""CCCECPPL#"),
            // function display name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,DefaultCurve,RecoveryRate,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class MidPointCdsEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,ReferenceDate,RateHelpers,DayCounter,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class PiecewiseFlatForwardCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x40""term structure reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x17""vector of rate-helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlPiecewiseFlatHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlPiecewiseFlatHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4E""ObjectId,ReferenceDate,Helpers,DayCounter,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class PiecewiseFlatHazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x40""term structure reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x26""vector of default probability helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 26, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // parameter codes
            TempStrNoSize("\x12""CCPCPCCCCCECPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB8""ObjectId,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecoveryRate,DiscountingCurve,SettleAccrual,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class SpreadCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // parameter codes
            TempStrNoSize("\x14""CCPECPCCCCCECNPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDC""ObjectId,UpfrontSpread,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecoveryRate,DiscountingCurve,UpfrontSettlementDays,SettleAccrual,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class UpfrontCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""upfront spread quote."),
            TempStrNoSize("\x0F""running spread."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x17""upfront settlement days"),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Credit with Excel

void unregisterCredit(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // parameter codes
            TempStrNoSize("\x11""CCPEEECPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlCreditDefaultSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAD""ObjectId,BuyerSeller,Notional,Upfront,Spread,PremiumSchedule,PaymentConvention,DayCounter,SettlesAccrual,PayAtDefault,ProtectionStart,UpfrontDate,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class CreditDefaultSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x44""BUYER for bought, SELLER for sold protection. Default value = Buyer."),
            TempStrNoSize("\x0E""Nominal amount"),
            TempStrNoSize("\x1B""upfront in fractional units"),
            TempStrNoSize("\x22""running spread in fractional units"),
            TempStrNoSize("\x1F""premium leg Schedule object ID."),
            TempStrNoSize("\x42""Payment dates' business day convention. Default value = Following."),
            TempStrNoSize("\x2A""premium leg day counter (e.g. Actual/360)."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x38""protection start date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x2F""upfront date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlCreditDefaultSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x45""ObjectId,CurveDates,CurveRates,DayCounter,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class HazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x13""dates of the curve."),
            TempStrNoSize("\x21""hazard rates for the above dates."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlHazardRateCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // parameter codes
            TempStrNoSize("\x09""CCCECPPL#"),
            // function display name
            TempStrNoSize("\x13""qlMidPointCdsEngine"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x49""ObjectId,DefaultCurve,RecoveryRate,YieldCurve,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class MidPointCdsEngine and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x21""default term structure object ID."),
            TempStrNoSize("\x16""constant recovery rate"),
            TempStrNoSize("\x2B""discounting yield term structure object ID."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlMidPointCdsEngine"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x52""ObjectId,ReferenceDate,RateHelpers,DayCounter,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Construct an object of class PiecewiseFlatForwardCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x40""term structure reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x17""vector of rate-helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlPiecewiseFlatForwardCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlPiecewiseFlatHazardRateCurve"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlPiecewiseFlatHazardRateCurve"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4E""ObjectId,ReferenceDate,Helpers,DayCounter,Accuracy,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Construct an object of class PiecewiseFlatHazardRateCurve and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x40""term structure reference date. Default value = QuantLib::Date()."),
            TempStrNoSize("\x26""vector of default probability helpers."),
            TempStrNoSize("\x32""DayCounter ID. Default value = Actual/365 (Fixed)."),
            TempStrNoSize("\x30""Bootstrapping accuracy. Default value = 1.0e-12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlPiecewiseFlatHazardRateCurve"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 26, &xDll,
            // function code name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // parameter codes
            TempStrNoSize("\x12""CCPCPCCCCCECPPPPL#"),
            // function display name
            TempStrNoSize("\x11""qlSpreadCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xB8""ObjectId,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecoveryRate,DiscountingCurve,SettleAccrual,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class SpreadCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x06""quote."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlSpreadCdsHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 28, &xDll,
            // function code name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // parameter codes
            TempStrNoSize("\x14""CCPECPCCCCCECNPPPPL#"),
            // function display name
            TempStrNoSize("\x12""qlUpfrontCdsHelper"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xDC""ObjectId,UpfrontSpread,RunningSpread,Tenor,SettlementDays,Calendar,Frequency,PaymentConvention,GenRule,DayCounter,RecoveryRate,DiscountingCurve,UpfrontSettlementDays,SettleAccrual,PayAtDefault,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib Credit"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class UpfrontCdsHelper and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x15""upfront spread quote."),
            TempStrNoSize("\x0F""running spread."),
            TempStrNoSize("\x24""CDS length (e.g. 5Y for five years)."),
            TempStrNoSize("\x22""settlement days Default value = 0."),
            TempStrNoSize("\x1F""holiday calendar (e.g. TARGET)."),
            TempStrNoSize("\x58""payment frequency (e.g. Annual, Semiannual, Every4Month, Quarterly, Bimonthly, Monthly)."),
            TempStrNoSize("\x29""payment leg convention (e.g. Unadjusted)."),
            TempStrNoSize("\x58""Date generation rule (Backward, Forward, ThirdWednesday, Twentieth, TwentiethIMM, Zero)."),
            TempStrNoSize("\x1E""day counter (e.g. Actual/360)."),
            TempStrNoSize("\x0D""recovery rate"),
            TempStrNoSize("\x29""discounting YieldTermStructure object ID."),
            TempStrNoSize("\x17""upfront settlement days"),
            TempStrNoSize("\x39""TRUE ensures settlement of accural. Default value = true."),
            TempStrNoSize("\x3A""TRUE ensures payment at default time Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlUpfrontCdsHelper"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

