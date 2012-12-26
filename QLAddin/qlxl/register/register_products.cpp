
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

// register functions in category Products with Excel

void registerProducts(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x22""qlMarketModelMultiProductComposite"),
            // parameter codes
            TempStrNoSize("\x06""CCPPL#"),
            // function display name
            TempStrNoSize("\x22""qlMarketModelMultiProductComposite"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class MultiProductComposite and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlMarketModelMultiProductCompositeAdd"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x25""qlMarketModelMultiProductCompositeAdd"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,Product,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""Add new product to MarketModelComposite object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::MultiProductComposite object"),
            TempStrNoSize("\x15""ID of product object."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlMarketModelMultiProductCompositeFinalize"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x2A""qlMarketModelMultiProductCompositeFinalize"),
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
            TempStrNoSize("\x29""finalize the MarketModelComposite object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::MultiProductComposite object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x3E""qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x3E""qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep"),
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
            TempStrNoSize("\x54""Max number of cashflows per product per step for the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlMarketModelMultiProductNumberOfProducts"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x29""qlMarketModelMultiProductNumberOfProducts"),
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
            TempStrNoSize("\x39""number of products in the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2E""qlMarketModelMultiProductPossibleCashFlowTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2E""qlMarketModelMultiProductPossibleCashFlowTimes"),
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
            TempStrNoSize("\x40""possible cash flow times for the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlMarketModelMultiProductSuggestedNumeraires"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlMarketModelMultiProductSuggestedNumeraires"),
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
            TempStrNoSize("\x3C""suggested Numeraires for the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlMarketModelMultiStepRatchet"),
            // parameter codes
            TempStrNoSize("\x0F""CCPPPEEEEELPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlMarketModelMultiStepRatchet"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x93""ObjectId,RateTimes,Accruals,PaymentTimes,GearingOfFloor,GearingOfFixing,SpreadOfFloor,SpreadOfFixing,InitialFloor,Payer,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class MultiStepRatchet and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x2A""accrual factors between rate fixing times."),
            TempStrNoSize("\x1D""payment times of the product."),
            TempStrNoSize("\x11""gearing of floor."),
            TempStrNoSize("\x12""gearing of fixing."),
            TempStrNoSize("\x10""spread of floor."),
            TempStrNoSize("\x11""spread of fixing."),
            TempStrNoSize("\x0E""initial floor."),
            TempStrNoSize("\x0E""payer if true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMarketModelOneStepForwards"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlMarketModelOneStepForwards"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,RateTimes,Accruals,PaymentTimes,Strikes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class OneStepForwards and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x10""accrual factors."),
            TempStrNoSize("\x1D""payment times of the product."),
            TempStrNoSize("\x10""forward strikes."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlMarketModelOneStepOptionlets"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlMarketModelOneStepOptionlets"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,RateTimes,Accruals,PaymentTimes,Payoffs,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class OneStepOptionlets and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x10""accrual factors."),
            TempStrNoSize("\x1D""payment times of the product."),
            TempStrNoSize("\x1F""striked type payoff object IDs."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Products with Excel

void unregisterProducts(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x22""qlMarketModelMultiProductComposite"),
            // parameter codes
            TempStrNoSize("\x06""CCPPL#"),
            // function display name
            TempStrNoSize("\x22""qlMarketModelMultiProductComposite"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x24""ObjectId,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Construct an object of class MultiProductComposite and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlMarketModelMultiProductComposite"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x25""qlMarketModelMultiProductCompositeAdd"),
            // parameter codes
            TempStrNoSize("\x05""LCCP#"),
            // function display name
            TempStrNoSize("\x25""qlMarketModelMultiProductCompositeAdd"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,Product,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x2F""Add new product to MarketModelComposite object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::MultiProductComposite object"),
            TempStrNoSize("\x15""ID of product object."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x25""qlMarketModelMultiProductCompositeAdd"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlMarketModelMultiProductCompositeFinalize"),
            // parameter codes
            TempStrNoSize("\x04""LCP#"),
            // function display name
            TempStrNoSize("\x2A""qlMarketModelMultiProductCompositeFinalize"),
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
            TempStrNoSize("\x29""finalize the MarketModelComposite object."),
            // parameter descriptions
            TempStrNoSize("\x35""id of existing QuantLib::MultiProductComposite object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlMarketModelMultiProductCompositeFinalize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x3E""qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x3E""qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep"),
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
            TempStrNoSize("\x54""Max number of cashflows per product per step for the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x3E""qlMarketModelMultiProductMaxNumberOfCashFlowsPerProductPerStep"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlMarketModelMultiProductNumberOfProducts"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x29""qlMarketModelMultiProductNumberOfProducts"),
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
            TempStrNoSize("\x39""number of products in the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlMarketModelMultiProductNumberOfProducts"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2E""qlMarketModelMultiProductPossibleCashFlowTimes"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2E""qlMarketModelMultiProductPossibleCashFlowTimes"),
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
            TempStrNoSize("\x40""possible cash flow times for the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2E""qlMarketModelMultiProductPossibleCashFlowTimes"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2C""qlMarketModelMultiProductSuggestedNumeraires"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2C""qlMarketModelMultiProductSuggestedNumeraires"),
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
            TempStrNoSize("\x3C""suggested Numeraires for the MarketModelMultiProduct object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::MarketModelMultiProduct object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2C""qlMarketModelMultiProductSuggestedNumeraires"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlMarketModelMultiStepRatchet"),
            // parameter codes
            TempStrNoSize("\x0F""CCPPPEEEEELPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlMarketModelMultiStepRatchet"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x93""ObjectId,RateTimes,Accruals,PaymentTimes,GearingOfFloor,GearingOfFixing,SpreadOfFloor,SpreadOfFixing,InitialFloor,Payer,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3F""Construct an object of class MultiStepRatchet and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x2A""accrual factors between rate fixing times."),
            TempStrNoSize("\x1D""payment times of the product."),
            TempStrNoSize("\x11""gearing of floor."),
            TempStrNoSize("\x12""gearing of fixing."),
            TempStrNoSize("\x10""spread of floor."),
            TempStrNoSize("\x11""spread of fixing."),
            TempStrNoSize("\x0E""initial floor."),
            TempStrNoSize("\x0E""payer if true."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlMarketModelMultiStepRatchet"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlMarketModelOneStepForwards"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1C""qlMarketModelOneStepForwards"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,RateTimes,Accruals,PaymentTimes,Strikes,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class OneStepForwards and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x10""accrual factors."),
            TempStrNoSize("\x1D""payment times of the product."),
            TempStrNoSize("\x10""forward strikes."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlMarketModelOneStepForwards"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlMarketModelOneStepOptionlets"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1E""qlMarketModelOneStepOptionlets"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,RateTimes,Accruals,PaymentTimes,Payoffs,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class OneStepOptionlets and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x12""rate fixing times."),
            TempStrNoSize("\x10""accrual factors."),
            TempStrNoSize("\x1D""payment times of the product."),
            TempStrNoSize("\x1F""striked type payoff object IDs."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlMarketModelOneStepOptionlets"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

