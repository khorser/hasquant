
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

// register functions in category Ctsmmcapletcalibration with Excel

void registerCtsmmcapletcalibration(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCTSMMCapletAlphaFormCalibration"),
            // parameter codes
            TempStrNoSize("\x11""CCCCPPCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x21""qlCTSMMCapletAlphaFormCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xBA""ObjectId,Evolution,Correlations,SwapPiecewiseConstantVariances,CapletVols,CurveState,Displacement,AlphaInitial,AlphaMax,AlphaMin,MaximizeHomogeneity,AlphaForm,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Construct an object of class CTSMMCapletAlphaFormCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""Evolution Description."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1E""PiecewiseConstantVariance IDs."),
            TempStrNoSize("\x14""caplet volatilities."),
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x0D""alphaInitial."),
            TempStrNoSize("\x42""alphaMax. Default value = 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0."),
            TempStrNoSize("\x4C""alphaMin. Default value = -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0."),
            TempStrNoSize("\x36""TRUE for maximizing homogeneity. Default value = true."),
            TempStrNoSize("\x20""alpha form ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletAlphaFormCalibrationAlpha"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletAlphaFormCalibrationAlpha"),
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
            TempStrNoSize("\x06""alpha."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::CTSMMCapletAlphaFormCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCTSMMCapletCalibrationCalibrate"),
            // parameter codes
            TempStrNoSize("\x09""LCNPPPPP#"),
            // function display name
            TempStrNoSize("\x21""qlCTSMMCapletCalibrationCalibrate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x42""ObjectId,NumberOfFactors,MaxIter,Tol,InnerMaxIter,InnerTol,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x0A""calibrate."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x12""number of factors."),
            TempStrNoSize("\x30""maximum number of iterations. Default value = 2."),
            TempStrNoSize("\x2D""caplet vol tolerance. Default value = 0.0001."),
            TempStrNoSize("\x22""innerMaxIter. Default value = 100."),
            TempStrNoSize("\x2B""caplet vol tolerance. Default value = 1e-8."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletMaxError"),
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
            TempStrNoSize("\x0F""capletMaxError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletRmsError"),
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
            TempStrNoSize("\x0F""capletRmsError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationDeformationSize"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationDeformationSize"),
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
            TempStrNoSize("\x10""deformationSize."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlCTSMMCapletCalibrationFailures"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x20""qlCTSMMCapletCalibrationFailures"),
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
            TempStrNoSize("\x09""failures."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationMarketCapletVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationMarketCapletVols"),
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
            TempStrNoSize("\x1B""market caplet volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlCTSMMCapletCalibrationMarketSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlCTSMMCapletCalibrationMarketSwaptionVols"),
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
            TempStrNoSize("\x1D""market swaption volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationModelCapletVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationModelCapletVols"),
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
            TempStrNoSize("\x1A""model caplet volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlCTSMMCapletCalibrationModelSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlCTSMMCapletCalibrationModelSwaptionVols"),
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
            TempStrNoSize("\x1C""model swaption volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationSwapPseudoRoot"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationSwapPseudoRoot"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x0F""swapPseudoRoot."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x06""index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionMaxError"),
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
            TempStrNoSize("\x11""swaptionMaxError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionRmsError"),
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
            TempStrNoSize("\x11""swaptionRmsError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x3B""qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x3B""qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""timeDependentCalibratedSwaptionVols."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x06""index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x3D""qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x3D""qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""timeDependentUnCalibratedSwaptionVols."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x06""index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletMaxHomogeneityCalibration"),
            // parameter codes
            TempStrNoSize("\x0D""CCCCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletMaxHomogeneityCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x96""ObjectId,Evolution,Correlations,SwapPiecewiseConstantVariances,CapletVols,CurveState,Displacement,Caplet0Swaption1Priority,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x53""Construct an object of class CTSMMCapletMaxHomogeneityCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""Evolution Description."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1E""PiecewiseConstantVariance IDs."),
            TempStrNoSize("\x14""caplet volatilities."),
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x2E""caplet0Swaption1Priority. Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x20""qlCTSMMCapletOriginalCalibration"),
            // parameter codes
            TempStrNoSize("\x0F""CCCCPPCPPPLPPL#"),
            // function display name
            TempStrNoSize("\x20""qlCTSMMCapletOriginalCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9D""ObjectId,Evolution,Correlations,SwapPiecewiseConstantVariances,CapletVols,CurveState,Displacement,Alphas,LowestRoot,UseFullApprox,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class CTSMMCapletOriginalCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""Evolution Description."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1E""PiecewiseConstantVariance IDs."),
            TempStrNoSize("\x14""caplet volatilities."),
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x07""alphas."),
            TempStrNoSize("\x4E""TRUE for lowest root, FALSE for the root nearest to 1.0. Default value = true."),
            TempStrNoSize("\x22""TRUE for using Full Approximation."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));



}

// unregister functions in category Ctsmmcapletcalibration with Excel

void unregisterCtsmmcapletcalibration(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 25, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCTSMMCapletAlphaFormCalibration"),
            // parameter codes
            TempStrNoSize("\x11""CCCCPPCPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x21""qlCTSMMCapletAlphaFormCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xBA""ObjectId,Evolution,Correlations,SwapPiecewiseConstantVariances,CapletVols,CurveState,Displacement,AlphaInitial,AlphaMax,AlphaMin,MaximizeHomogeneity,AlphaForm,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Construct an object of class CTSMMCapletAlphaFormCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""Evolution Description."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1E""PiecewiseConstantVariance IDs."),
            TempStrNoSize("\x14""caplet volatilities."),
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x0D""alphaInitial."),
            TempStrNoSize("\x42""alphaMax. Default value = 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0."),
            TempStrNoSize("\x4C""alphaMin. Default value = -1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0."),
            TempStrNoSize("\x36""TRUE for maximizing homogeneity. Default value = true."),
            TempStrNoSize("\x20""alpha form ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCTSMMCapletAlphaFormCalibration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletAlphaFormCalibrationAlpha"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletAlphaFormCalibrationAlpha"),
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
            TempStrNoSize("\x06""alpha."),
            // parameter descriptions
            TempStrNoSize("\x3F""id of existing QuantLib::CTSMMCapletAlphaFormCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlCTSMMCapletAlphaFormCalibrationAlpha"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCTSMMCapletCalibrationCalibrate"),
            // parameter codes
            TempStrNoSize("\x09""LCNPPPPP#"),
            // function display name
            TempStrNoSize("\x21""qlCTSMMCapletCalibrationCalibrate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x42""ObjectId,NumberOfFactors,MaxIter,Tol,InnerMaxIter,InnerTol,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x0A""calibrate."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x12""number of factors."),
            TempStrNoSize("\x30""maximum number of iterations. Default value = 2."),
            TempStrNoSize("\x2D""caplet vol tolerance. Default value = 0.0001."),
            TempStrNoSize("\x22""innerMaxIter. Default value = 100."),
            TempStrNoSize("\x2B""caplet vol tolerance. Default value = 1e-8."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCTSMMCapletCalibrationCalibrate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletMaxError"),
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
            TempStrNoSize("\x0F""capletMaxError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletRmsError"),
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
            TempStrNoSize("\x0F""capletRmsError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationCapletRmsError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationDeformationSize"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationDeformationSize"),
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
            TempStrNoSize("\x10""deformationSize."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationDeformationSize"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x20""qlCTSMMCapletCalibrationFailures"),
            // parameter codes
            TempStrNoSize("\x04""NCP#"),
            // function display name
            TempStrNoSize("\x20""qlCTSMMCapletCalibrationFailures"),
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
            TempStrNoSize("\x09""failures."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlCTSMMCapletCalibrationFailures"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationMarketCapletVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationMarketCapletVols"),
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
            TempStrNoSize("\x1B""market caplet volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationMarketCapletVols"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlCTSMMCapletCalibrationMarketSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlCTSMMCapletCalibrationMarketSwaptionVols"),
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
            TempStrNoSize("\x1D""market swaption volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlCTSMMCapletCalibrationMarketSwaptionVols"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationModelCapletVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationModelCapletVols"),
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
            TempStrNoSize("\x1A""model caplet volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x27""qlCTSMMCapletCalibrationModelCapletVols"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlCTSMMCapletCalibrationModelSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlCTSMMCapletCalibrationModelSwaptionVols"),
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
            TempStrNoSize("\x1C""model swaption volalitilies."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlCTSMMCapletCalibrationModelSwaptionVols"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationSwapPseudoRoot"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationSwapPseudoRoot"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x0F""swapPseudoRoot."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x06""index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlCTSMMCapletCalibrationSwapPseudoRoot"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionMaxError"),
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
            TempStrNoSize("\x11""swaptionMaxError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionRmsError"),
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
            TempStrNoSize("\x11""swaptionRmsError."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlCTSMMCapletCalibrationSwaptionRmsError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x3B""qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x3B""qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x24""timeDependentCalibratedSwaptionVols."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x06""index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x3B""qlCTSMMCapletCalibrationTimeDependentCalibratedSwaptionVols"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x3D""qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols"),
            // parameter codes
            TempStrNoSize("\x05""PCNP#"),
            // function display name
            TempStrNoSize("\x3D""qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x16""ObjectId,Index,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x26""timeDependentUnCalibratedSwaptionVols."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLib::CTSMMCapletCalibration object"),
            TempStrNoSize("\x06""index."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x3D""qlCTSMMCapletCalibrationTimeDependentUnCalibratedSwaptionVols"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 21, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCTSMMCapletMaxHomogeneityCalibration"),
            // parameter codes
            TempStrNoSize("\x0D""CCCCPPCPPPPL#"),
            // function display name
            TempStrNoSize("\x26""qlCTSMMCapletMaxHomogeneityCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x96""ObjectId,Evolution,Correlations,SwapPiecewiseConstantVariances,CapletVols,CurveState,Displacement,Caplet0Swaption1Priority,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x53""Construct an object of class CTSMMCapletMaxHomogeneityCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""Evolution Description."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1E""PiecewiseConstantVariance IDs."),
            TempStrNoSize("\x14""caplet volatilities."),
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x2E""caplet0Swaption1Priority. Default value = 1.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlCTSMMCapletMaxHomogeneityCalibration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x20""qlCTSMMCapletOriginalCalibration"),
            // parameter codes
            TempStrNoSize("\x0F""CCCCPPCPPPLPPL#"),
            // function display name
            TempStrNoSize("\x20""qlCTSMMCapletOriginalCalibration"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9D""ObjectId,Evolution,Correlations,SwapPiecewiseConstantVariances,CapletVols,CurveState,Displacement,Alphas,LowestRoot,UseFullApprox,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x14""QuantLib - Financial"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4D""Construct an object of class CTSMMCapletOriginalCalibration and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x16""Evolution Description."),
            TempStrNoSize("\x27""PiecewiseConstantCorrelation object ID."),
            TempStrNoSize("\x1E""PiecewiseConstantVariance IDs."),
            TempStrNoSize("\x14""caplet volatilities."),
            TempStrNoSize("\x15""CurveState object ID."),
            TempStrNoSize("\x22""displacement. Default value = 0.0."),
            TempStrNoSize("\x07""alphas."),
            TempStrNoSize("\x4E""TRUE for lowest root, FALSE for the root nearest to 1.0. Default value = true."),
            TempStrNoSize("\x22""TRUE for using Full Approximation."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x20""qlCTSMMCapletOriginalCalibration"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

