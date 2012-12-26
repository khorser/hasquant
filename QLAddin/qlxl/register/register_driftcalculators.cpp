
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

// register functions in category Driftcalculators with Excel

void registerDriftcalculators(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCMSMMDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0C""CCKPPNNNPPL#"),
            // function display name
            TempStrNoSize("\x16""qlCMSMMDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x67""ObjectId,Pseudo_square_root,Displacements,Taus,Numeraire,Alive,SpanningFwds,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class CMSMMDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x21""number of forwards to be spanned."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCMSMMDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x1D""qlCMSMMDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Full factor drift computation using the CMSMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CMSMMDriftCalculator object"),
            TempStrNoSize("\x1B""CMSwapCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlLMMDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0B""CCKPPNNPPL#"),
            // function display name
            TempStrNoSize("\x14""qlLMMDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5A""ObjectId,Pseudo_square_root,Displacements,Taus,Numeraire,Alive,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class LMMDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlLMMDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x1B""qlLMMDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x57""Reduced factor (Joshi algorithm) drift computation using the LMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::LMMDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlLMMDriftCalculatorComputePlain"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x20""qlLMMDriftCalculatorComputePlain"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Full factor drift computation using the LMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::LMMDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x22""qlLMMDriftCalculatorComputeReduced"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x22""qlLMMDriftCalculatorComputeReduced"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x57""Reduced factor (Joshi algorithm) drift computation using the LMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::LMMDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlLMMNormalDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0A""CCKPNNPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlLMMNormalDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,Pseudo_square_root,Taus,Numeraire,Alive,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class LMMNormalDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x21""qlLMMNormalDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x21""qlLMMNormalDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5D""Reduced factor (Joshi algorithm) drift computation using the LMMNormalDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::LMMNormalDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlLMMNormalDriftCalculatorComputePlain"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x26""qlLMMNormalDriftCalculatorComputePlain"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Full factor drift computation using the LMMNormalDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::LMMNormalDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x28""qlLMMNormalDriftCalculatorComputeReduced"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x28""qlLMMNormalDriftCalculatorComputeReduced"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5D""Reduced factor (Joshi algorithm) drift computation using the LMMNormalDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::LMMNormalDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSMMDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0B""CCKPPNNPPL#"),
            // function display name
            TempStrNoSize("\x14""qlSMMDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5A""ObjectId,Pseudo_square_root,Displacements,Taus,Numeraire,Alive,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SMMDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSMMDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSMMDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Full factor drift computation using the SMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::SMMDriftCalculator object"),
            TempStrNoSize("\x23""CoterminalSwapCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Driftcalculators with Excel

void unregisterDriftcalculators(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 20, &xDll,
            // function code name
            TempStrNoSize("\x16""qlCMSMMDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0C""CCKPPNNNPPL#"),
            // function display name
            TempStrNoSize("\x16""qlCMSMMDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x67""ObjectId,Pseudo_square_root,Displacements,Taus,Numeraire,Alive,SpanningFwds,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x43""Construct an object of class CMSMMDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x21""number of forwards to be spanned."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlCMSMMDriftCalculator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlCMSMMDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x1D""qlCMSMMDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Full factor drift computation using the CMSMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x39""id of existing QuantLibAddin::CMSMMDriftCalculator object"),
            TempStrNoSize("\x1B""CMSwapCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlCMSMMDriftCalculatorCompute"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlLMMDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0B""CCKPPNNPPL#"),
            // function display name
            TempStrNoSize("\x14""qlLMMDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5A""ObjectId,Pseudo_square_root,Displacements,Taus,Numeraire,Alive,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class LMMDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlLMMDriftCalculator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlLMMDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x1B""qlLMMDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x57""Reduced factor (Joshi algorithm) drift computation using the LMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::LMMDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlLMMDriftCalculatorCompute"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x20""qlLMMDriftCalculatorComputePlain"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x20""qlLMMDriftCalculatorComputePlain"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Full factor drift computation using the LMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::LMMDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlLMMDriftCalculatorComputePlain"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x22""qlLMMDriftCalculatorComputeReduced"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x22""qlLMMDriftCalculatorComputeReduced"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x57""Reduced factor (Joshi algorithm) drift computation using the LMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::LMMDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlLMMDriftCalculatorComputeReduced"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlLMMNormalDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0A""CCKPNNPPL#"),
            // function display name
            TempStrNoSize("\x1A""qlLMMNormalDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,Pseudo_square_root,Taus,Numeraire,Alive,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Construct an object of class LMMNormalDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlLMMNormalDriftCalculator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x21""qlLMMNormalDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x21""qlLMMNormalDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5D""Reduced factor (Joshi algorithm) drift computation using the LMMNormalDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::LMMNormalDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlLMMNormalDriftCalculatorCompute"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlLMMNormalDriftCalculatorComputePlain"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x26""qlLMMNormalDriftCalculatorComputePlain"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Full factor drift computation using the LMMNormalDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::LMMNormalDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlLMMNormalDriftCalculatorComputePlain"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x28""qlLMMNormalDriftCalculatorComputeReduced"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x28""qlLMMNormalDriftCalculatorComputeReduced"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5D""Reduced factor (Joshi algorithm) drift computation using the LMMNormalDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x3D""id of existing QuantLibAddin::LMMNormalDriftCalculator object"),
            TempStrNoSize("\x18""LMMCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlLMMNormalDriftCalculatorComputeReduced"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 19, &xDll,
            // function code name
            TempStrNoSize("\x14""qlSMMDriftCalculator"),
            // parameter codes
            TempStrNoSize("\x0B""CCKPPNNPPL#"),
            // function display name
            TempStrNoSize("\x14""qlSMMDriftCalculator"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x5A""ObjectId,Pseudo_square_root,Displacements,Taus,Numeraire,Alive,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class SMMDriftCalculator and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2C""Pseudo square root of the covariance matrix."),
            TempStrNoSize("\x0E""displacements."),
            TempStrNoSize("\x05""taus."),
            TempStrNoSize("\x0A""numeraire."),
            TempStrNoSize("\x25""index of the first rates still alive."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlSMMDriftCalculator"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSMMDriftCalculatorCompute"),
            // parameter codes
            TempStrNoSize("\x05""PCCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSMMDriftCalculatorCompute"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1B""ObjectId,CurveState,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Full factor drift computation using the SMMDriftCalculator object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::SMMDriftCalculator object"),
            TempStrNoSize("\x23""CoterminalSwapCurveState object ID."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSMMDriftCalculatorCompute"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

