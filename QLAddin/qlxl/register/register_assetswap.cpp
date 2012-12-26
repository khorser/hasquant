
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

// register functions in category Assetswap with Excel

void registerAssetswap(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlAssetSwap"),
            // parameter codes
            TempStrNoSize("\x0E""CCPCECPPCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlAssetSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8A""ObjectId,PayBondCoupon,Bond,CleanPrice,IborIndex,Spread,FloatingLegSchedule,FloatingLegDayCounter,ParAssetSwap,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class AssetSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""TRUE to pay the bond's coupons and receive floating. Default value = false."),
            TempStrNoSize("\x1A""underlying bond object ID."),
            TempStrNoSize("\x24""market price of the underlying bond."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x29""Floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x32""floating leg schedule object ID. Default value = ."),
            TempStrNoSize("\x27""floating day counter (e.g. Actual/360)."),
            TempStrNoSize("\x4B""TRUE for par asset swap, FALSE for market asset swap. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlAssetSwap2"),
            // parameter codes
            TempStrNoSize("\x10""CCPCEEPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlAssetSwap2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9B""ObjectId,ParAssetSwap,Bond,CleanPrice,NonParRepayment,Gearing,IborIndex,Spread,FloatingLegDayCounter,DealMaturity,PayBondCoupon,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class AssetSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""TRUE for par asset swap, FALSE for market asset swap. Default value = true."),
            TempStrNoSize("\x1A""underlying bond object ID."),
            TempStrNoSize("\x24""market price of the underlying bond."),
            TempStrNoSize("\x28""non par repayment on deal maturity date."),
            TempStrNoSize("\x1D""gearing. Default value = 1.0."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x29""Floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x4F""floating day counter (e.g. Actual/360). Default value = QuantLib::DayCounter()."),
            TempStrNoSize("\x4B""deal maturity (bond maturity if missing). Default value = QuantLib::Date()."),
            TempStrNoSize("\x4B""TRUE to pay the bond's coupons and receive floating. Default value = false."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlAssetSwapBondLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1A""qlAssetSwapBondLegAnalysis"),
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
            TempStrNoSize("\x20""The bond leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLibAddin::AssetSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAssetSwapFairCleanPrice"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlAssetSwapFairCleanPrice"),
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
            TempStrNoSize("\x2D""the fair price of the bond in the asset swap."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlAssetSwapFairNonParRepayment"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlAssetSwapFairNonParRepayment"),
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
            TempStrNoSize("\x39""the fair non par repayment of the bond in the asset swap."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlAssetSwapFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x15""qlAssetSwapFairSpread"),
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
            TempStrNoSize("\x3C""the fair rate of the asset swap, i.e. the asset swap spread."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlAssetSwapFloatingLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1E""qlAssetSwapFloatingLegAnalysis"),
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
            TempStrNoSize("\x24""The floating leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLibAddin::AssetSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAssetSwapFloatingLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlAssetSwapFloatingLegBPS"),
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
            TempStrNoSize("\x1C""the BPS of the floating leg."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAssetSwapParSwap"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x12""qlAssetSwapParSwap"),
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
            TempStrNoSize("\x18""Returns TRUE if par swap"),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAssetSwapPayBondCoupon"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x18""qlAssetSwapPayBondCoupon"),
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
            TempStrNoSize("\x2E""Returns TRUE if it is a bond coupon payer swap"),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Assetswap with Excel

void unregisterAssetswap(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlAssetSwap"),
            // parameter codes
            TempStrNoSize("\x0E""CCPCECPPCPPPL#"),
            // function display name
            TempStrNoSize("\x0B""qlAssetSwap"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x8A""ObjectId,PayBondCoupon,Bond,CleanPrice,IborIndex,Spread,FloatingLegSchedule,FloatingLegDayCounter,ParAssetSwap,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class AssetSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""TRUE to pay the bond's coupons and receive floating. Default value = false."),
            TempStrNoSize("\x1A""underlying bond object ID."),
            TempStrNoSize("\x24""market price of the underlying bond."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x29""Floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x32""floating leg schedule object ID. Default value = ."),
            TempStrNoSize("\x27""floating day counter (e.g. Actual/360)."),
            TempStrNoSize("\x4B""TRUE for par asset swap, FALSE for market asset swap. Default value = true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlAssetSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 24, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlAssetSwap2"),
            // parameter codes
            TempStrNoSize("\x10""CCPCEEPCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x0C""qlAssetSwap2"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9B""ObjectId,ParAssetSwap,Bond,CleanPrice,NonParRepayment,Gearing,IborIndex,Spread,FloatingLegDayCounter,DealMaturity,PayBondCoupon,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x38""Construct an object of class AssetSwap and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x4B""TRUE for par asset swap, FALSE for market asset swap. Default value = true."),
            TempStrNoSize("\x1A""underlying bond object ID."),
            TempStrNoSize("\x24""market price of the underlying bond."),
            TempStrNoSize("\x28""non par repayment on deal maturity date."),
            TempStrNoSize("\x1D""gearing. Default value = 1.0."),
            TempStrNoSize("\x21""floating leg IborIndex object ID."),
            TempStrNoSize("\x29""Floating leg spread. Default value = 0.0."),
            TempStrNoSize("\x4F""floating day counter (e.g. Actual/360). Default value = QuantLib::DayCounter()."),
            TempStrNoSize("\x4B""deal maturity (bond maturity if missing). Default value = QuantLib::Date()."),
            TempStrNoSize("\x4B""TRUE to pay the bond's coupons and receive floating. Default value = false."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlAssetSwap2"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlAssetSwapBondLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1A""qlAssetSwapBondLegAnalysis"),
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
            TempStrNoSize("\x20""The bond leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLibAddin::AssetSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlAssetSwapBondLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAssetSwapFairCleanPrice"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x19""qlAssetSwapFairCleanPrice"),
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
            TempStrNoSize("\x2D""the fair price of the bond in the asset swap."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlAssetSwapFairCleanPrice"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlAssetSwapFairNonParRepayment"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1E""qlAssetSwapFairNonParRepayment"),
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
            TempStrNoSize("\x39""the fair non par repayment of the bond in the asset swap."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlAssetSwapFairNonParRepayment"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlAssetSwapFairSpread"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x15""qlAssetSwapFairSpread"),
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
            TempStrNoSize("\x3C""the fair rate of the asset swap, i.e. the asset swap spread."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlAssetSwapFairSpread"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlAssetSwapFloatingLegAnalysis"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x1E""qlAssetSwapFloatingLegAnalysis"),
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
            TempStrNoSize("\x24""The floating leg cash flow analysis."),
            // parameter descriptions
            TempStrNoSize("\x2E""id of existing QuantLibAddin::AssetSwap object"),
            TempStrNoSize("\x47""Shows only cashflows after given date Default value = QuantLib::Date()."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlAssetSwapFloatingLegAnalysis"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlAssetSwapFloatingLegBPS"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlAssetSwapFloatingLegBPS"),
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
            TempStrNoSize("\x1C""the BPS of the floating leg."),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlAssetSwapFloatingLegBPS"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x12""qlAssetSwapParSwap"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x12""qlAssetSwapParSwap"),
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
            TempStrNoSize("\x18""Returns TRUE if par swap"),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x12""qlAssetSwapParSwap"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlAssetSwapPayBondCoupon"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x18""qlAssetSwapPayBondCoupon"),
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
            TempStrNoSize("\x2E""Returns TRUE if it is a bond coupon payer swap"),
            // parameter descriptions
            TempStrNoSize("\x29""id of existing QuantLib::AssetSwap object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlAssetSwapPayBondCoupon"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

