
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

// register functions in category Interpolation with Excel

void registerInterpolation(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 27, &xDll,
            // function code name
            TempStrNoSize("\x13""qlAbcdInterpolation"),
            // parameter codes
            TempStrNoSize("\x13""CCPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlAbcdInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x88""ObjectId,XArray,YArray,A,B,C,D,AIsFixed,BIsFixed,CIsFixed,DIsFixed,VegaWeighted,EndCriteria,OptimizationMeth,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class AbcdInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x83""The a in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x83""The b in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x83""The c in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x83""The d in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x65""TRUE if the A value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x65""TRUE if the B value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x65""TRUE if the C value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x65""TRUE if the D value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x4F""TRUE if the interpolation is weighted using options Vega. Default value = true."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationA"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationA"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the a in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationB"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationB"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the b in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationC"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationC"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the c in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationD"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationD"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the d in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlAbcdInterpolationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1E""qlAbcdInterpolationEndCriteria"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the optimization end criteria of the fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlAbcdInterpolationMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlAbcdInterpolationMaxError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the max error of the fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlAbcdInterpolationRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlAbcdInterpolationRmsError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the error of the fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCubicInterpolation"),
            // parameter codes
            TempStrNoSize("\x0E""CCPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlCubicInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x92""ObjectId,XArray,YArray,DerApprox,Monotonic,LeftConditionType,LeftConditionValue,RightConditionType,RightConditionValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class CubicInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x34""Derivative Approximation (). Default value = Kruger."),
            TempStrNoSize("\x33""monotonicity constraint flag. Default value = true."),
            TempStrNoSize("\x7C""left boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2A""left condition value. Default value = 0.0."),
            TempStrNoSize("\x7D""right boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2B""right condition value. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCubicInterpolationACoefficients"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCubicInterpolationACoefficients"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCubicInterpolationBCoefficients"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCubicInterpolationBCoefficients"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCubicInterpolationCCoefficients"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCubicInterpolationCCoefficients"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlCubicInterpolationMonotonicityAdjustments"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlCubicInterpolationMonotonicityAdjustments"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x60""Returns a vector of bool (one per cubic) indicating if there has been a monotonicity adjustment."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCubicInterpolationPrimitiveConstants"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCubicInterpolationPrimitiveConstants"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x21""qlExtrapolatorEnableExtrapolation"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x21""qlExtrapolatorEnableExtrapolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x22""ObjectId,ExtrapolationFlag,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Sets the enable extrapolation flag to the given Extrapolator object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLibAddin::Extrapolator object"),
            TempStrNoSize("\x30""global extrapolation flag. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlInterpolation"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,InterpolationType,XArray,YArray,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class GenericInterp and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x82""interpolation type (e.g BackwardFlat, ForwardFlat, MonotonicCubicNaturalSpline, etc.) Default value = MonotonicNaturalCubicSpline."),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x11""qlInterpolation2D"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPKPPL#"),
            // function display name
            TempStrNoSize("\x11""qlInterpolation2D"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,InterpolationType,XArray,YArray,ZMatrix,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class Interpolation2D and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x48""2D-interpolation type (e.g BiLinear, BiCubic). Default value = BiLinear."),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x10""z-matrix values."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterpolation2DInterpolate"),
            // parameter codes
            TempStrNoSize("\x07""PCPEPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterpolation2DInterpolate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,XValue,YValue,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns interpolated values for the (x,y) input for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x0B""x value(s)."),
            TempStrNoSize("\x08""y value."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlInterpolation2DIsInRange"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x1A""qlInterpolation2DIsInRange"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,XValues,YValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns TRUE if the (x,y) input value is in the allowed interpolation range for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x08""y value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DXmax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DXmax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the maximum value of the x array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DXmin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DXmin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the minimum value of the x array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolation2DXvalues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolation2DXvalues"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the x array grid for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DYmax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DYmax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the maximum value of the y array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DYmin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DYmin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the minimum value of the y array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolation2DYvalues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolation2DYvalues"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the y array grid for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlInterpolation2DzData"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlInterpolation2DzData"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the z data matrix grid for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInterpolationDerivative"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlInterpolationDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""Returns the first derivative function values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlInterpolationInterpolate"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1A""qlInterpolationInterpolate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Returns interpolated values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolationIsInRange"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolationIsInRange"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,XValues,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x69""Returns TRUE if the input value is in the allowed interpolation range for the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolationPrimitive"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolationPrimitive"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the primitive function values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlInterpolationSecondDerivative"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1F""qlInterpolationSecondDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x53""Returns the second derivative function values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlInterpolationXmax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x13""qlInterpolationXmax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the maximum value of the x array for the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::Interpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlInterpolationXmin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x13""qlInterpolationXmin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the minimum value of the x array for the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::Interpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlMixedLinearCubicInterpolation"),
            // parameter codes
            TempStrNoSize("\x0F""CCPPNPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlMixedLinearCubicInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9E""ObjectId,XArray,YArray,SwitchIndex,DerApprox,Monotonic,LeftConditionType,LeftConditionValue,RightConditionType,RightConditionValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Construct an object of class MixedLinearCubicInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x4B""zero based knot index at which interpolation switches from linear to cubic."),
            TempStrNoSize("\x34""Derivative Approximation (). Default value = Kruger."),
            TempStrNoSize("\x33""monotonicity constraint flag. Default value = true."),
            TempStrNoSize("\x7C""left boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2A""left condition value. Default value = 0.0."),
            TempStrNoSize("\x7D""right boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2B""right condition value. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 29, &xDll,
            // function code name
            TempStrNoSize("\x13""qlSABRInterpolation"),
            // parameter codes
            TempStrNoSize("\x15""CCPPEPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlSABRInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAB""ObjectId,XArray,YArray,Expiry,Forward,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,OptimizationMeth,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class SABRInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x15""expiry time in years."),
            TempStrNoSize("\x1A""at-the-money forward rate."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x4F""TRUE if the interpolation is weighted using options Vega. Default value = true."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSABRInterpolationAlpha"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlSABRInterpolationAlpha"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the alpha of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSABRInterpolationBeta"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlSABRInterpolationBeta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the alpha of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSABRInterpolationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1E""qlSABRInterpolationEndCriteria"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the optimization end criteria of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSABRInterpolationExpiry"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlSABRInterpolationExpiry"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the expiry time in years for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSABRInterpolationForward"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlSABRInterpolationForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the forward  for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSABRInterpolationMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSABRInterpolationMaxError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the max error of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSABRInterpolationNu"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlSABRInterpolationNu"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Returns the nu of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSABRInterpolationRho"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlSABRInterpolationRho"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns the rho of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSABRInterpolationRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSABRInterpolationRmsError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the error of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSABRInterpolationWeights"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlSABRInterpolationWeights"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns the weights of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Interpolation with Excel

void unregisterInterpolation(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 27, &xDll,
            // function code name
            TempStrNoSize("\x13""qlAbcdInterpolation"),
            // parameter codes
            TempStrNoSize("\x13""CCPPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlAbcdInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x88""ObjectId,XArray,YArray,A,B,C,D,AIsFixed,BIsFixed,CIsFixed,DIsFixed,VegaWeighted,EndCriteria,OptimizationMeth,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class AbcdInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x83""The a in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x83""The b in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x83""The c in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x83""The d in { y = (a + b*x) e^(-c*x) + d }. It can be a fixed value or just a guess. Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x65""TRUE if the A value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x65""TRUE if the B value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x65""TRUE if the C value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x65""TRUE if the D value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x4F""TRUE if the interpolation is weighted using options Vega. Default value = true."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlAbcdInterpolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationA"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationA"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the a in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlAbcdInterpolationA"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationB"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationB"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the b in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlAbcdInterpolationB"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationC"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationC"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the c in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlAbcdInterpolationC"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x14""qlAbcdInterpolationD"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x14""qlAbcdInterpolationD"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x5F""Returns the d in the { y = (a + b*x) e^(-c*x) + d } fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlAbcdInterpolationD"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlAbcdInterpolationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1E""qlAbcdInterpolationEndCriteria"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the optimization end criteria of the fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlAbcdInterpolationEndCriteria"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlAbcdInterpolationMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlAbcdInterpolationMaxError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the max error of the fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlAbcdInterpolationMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlAbcdInterpolationRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlAbcdInterpolationRmsError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the error of the fit for the given AbcdInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::AbcdInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlAbcdInterpolationRmsError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 22, &xDll,
            // function code name
            TempStrNoSize("\x14""qlCubicInterpolation"),
            // parameter codes
            TempStrNoSize("\x0E""CCPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x14""qlCubicInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x92""ObjectId,XArray,YArray,DerApprox,Monotonic,LeftConditionType,LeftConditionValue,RightConditionType,RightConditionValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Construct an object of class CubicInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x34""Derivative Approximation (). Default value = Kruger."),
            TempStrNoSize("\x33""monotonicity constraint flag. Default value = true."),
            TempStrNoSize("\x7C""left boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2A""left condition value. Default value = 0.0."),
            TempStrNoSize("\x7D""right boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2B""right condition value. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x14""qlCubicInterpolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCubicInterpolationACoefficients"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCubicInterpolationACoefficients"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCubicInterpolationACoefficients"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCubicInterpolationBCoefficients"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCubicInterpolationBCoefficients"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCubicInterpolationBCoefficients"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x21""qlCubicInterpolationCCoefficients"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x21""qlCubicInterpolationCCoefficients"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlCubicInterpolationCCoefficients"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlCubicInterpolationMonotonicityAdjustments"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlCubicInterpolationMonotonicityAdjustments"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x60""Returns a vector of bool (one per cubic) indicating if there has been a monotonicity adjustment."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlCubicInterpolationMonotonicityAdjustments"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x26""qlCubicInterpolationPrimitiveConstants"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x26""qlCubicInterpolationPrimitiveConstants"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x74""Returns the constant terms in the primitive of the cubic interpolants for the given CubicSplineInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLibAddin::CubicInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x26""qlCubicInterpolationPrimitiveConstants"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x21""qlExtrapolatorEnableExtrapolation"),
            // parameter codes
            TempStrNoSize("\x05""LCPP#"),
            // function display name
            TempStrNoSize("\x21""qlExtrapolatorEnableExtrapolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x22""ObjectId,ExtrapolationFlag,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Sets the enable extrapolation flag to the given Extrapolator object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLibAddin::Extrapolator object"),
            TempStrNoSize("\x30""global extrapolation flag. Default value = true."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x21""qlExtrapolatorEnableExtrapolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 17, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlInterpolation"),
            // parameter codes
            TempStrNoSize("\x09""CCPPPPPL#"),
            // function display name
            TempStrNoSize("\x0F""qlInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x44""ObjectId,InterpolationType,XArray,YArray,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Construct an object of class GenericInterp and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x82""interpolation type (e.g BackwardFlat, ForwardFlat, MonotonicCubicNaturalSpline, etc.) Default value = MonotonicNaturalCubicSpline."),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlInterpolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 18, &xDll,
            // function code name
            TempStrNoSize("\x11""qlInterpolation2D"),
            // parameter codes
            TempStrNoSize("\x0A""CCPPPKPPL#"),
            // function display name
            TempStrNoSize("\x11""qlInterpolation2D"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x4C""ObjectId,InterpolationType,XArray,YArray,ZMatrix,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Construct an object of class Interpolation2D and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x48""2D-interpolation type (e.g BiLinear, BiCubic). Default value = BiLinear."),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x10""z-matrix values."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlInterpolation2D"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1C""qlInterpolation2DInterpolate"),
            // parameter codes
            TempStrNoSize("\x07""PCPEPP#"),
            // function display name
            TempStrNoSize("\x1C""qlInterpolation2DInterpolate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x31""ObjectId,XValue,YValue,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x55""Returns interpolated values for the (x,y) input for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x0B""x value(s)."),
            TempStrNoSize("\x08""y value."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1C""qlInterpolation2DInterpolate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlInterpolation2DIsInRange"),
            // parameter codes
            TempStrNoSize("\x06""PCPEP#"),
            // function display name
            TempStrNoSize("\x1A""qlInterpolation2DIsInRange"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1F""ObjectId,XValues,YValue,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns TRUE if the (x,y) input value is in the allowed interpolation range for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x08""y value."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlInterpolation2DIsInRange"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DXmax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DXmax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the maximum value of the x array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlInterpolation2DXmax"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DXmin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DXmin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the minimum value of the x array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlInterpolation2DXmin"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolation2DXvalues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolation2DXvalues"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the x array grid for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterpolation2DXvalues"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DYmax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DYmax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the maximum value of the y array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlInterpolation2DYmax"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlInterpolation2DYmin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlInterpolation2DYmin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4E""Returns the minimum value of the y array for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlInterpolation2DYmin"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolation2DYvalues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolation2DYvalues"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the y array grid for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterpolation2DYvalues"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlInterpolation2DzData"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlInterpolation2DzData"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the z data matrix grid for the given Interpolation2D object."),
            // parameter descriptions
            TempStrNoSize("\x2F""id of existing QuantLib::Interpolation2D object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlInterpolation2DzData"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x19""qlInterpolationDerivative"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x19""qlInterpolationDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x52""Returns the first derivative function values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlInterpolationDerivative"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlInterpolationInterpolate"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1A""qlInterpolationInterpolate"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Returns interpolated values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlInterpolationInterpolate"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolationIsInRange"),
            // parameter codes
            TempStrNoSize("\x05""PCPP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolationIsInRange"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x18""ObjectId,XValues,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x69""Returns TRUE if the input value is in the allowed interpolation range for the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterpolationIsInRange"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x18""qlInterpolationPrimitive"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x18""qlInterpolationPrimitive"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4B""Returns the primitive function values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlInterpolationPrimitive"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlInterpolationSecondDerivative"),
            // parameter codes
            TempStrNoSize("\x06""PCPPP#"),
            // function display name
            TempStrNoSize("\x1F""qlInterpolationSecondDerivative"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x2B""ObjectId,XValues,AllowExtrapolation,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x53""Returns the second derivative function values using the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x32""id of existing QuantLibAddin::Interpolation object"),
            TempStrNoSize("\x09""x values."),
            TempStrNoSize("\x30""allow extrapolation flag. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlInterpolationSecondDerivative"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlInterpolationXmax"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x13""qlInterpolationXmax"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the maximum value of the x array for the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::Interpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlInterpolationXmax"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x13""qlInterpolationXmin"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x13""qlInterpolationXmin"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the minimum value of the x array for the given Interpolation object."),
            // parameter descriptions
            TempStrNoSize("\x2D""id of existing QuantLib::Interpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlInterpolationXmin"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 23, &xDll,
            // function code name
            TempStrNoSize("\x1F""qlMixedLinearCubicInterpolation"),
            // parameter codes
            TempStrNoSize("\x0F""CCPPNPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x1F""qlMixedLinearCubicInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x9E""ObjectId,XArray,YArray,SwitchIndex,DerApprox,Monotonic,LeftConditionType,LeftConditionValue,RightConditionType,RightConditionValue,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Construct an object of class MixedLinearCubicInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x4B""zero based knot index at which interpolation switches from linear to cubic."),
            TempStrNoSize("\x34""Derivative Approximation (). Default value = Kruger."),
            TempStrNoSize("\x33""monotonicity constraint flag. Default value = true."),
            TempStrNoSize("\x7C""left boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2A""left condition value. Default value = 0.0."),
            TempStrNoSize("\x7D""right boundary condition (NotAKnot, FirstDerivative, SecondDerivative, Periodic, Lagrange). Default value = SecondDerivative."),
            TempStrNoSize("\x2B""right condition value. Default value = 0.0."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1F""qlMixedLinearCubicInterpolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 29, &xDll,
            // function code name
            TempStrNoSize("\x13""qlSABRInterpolation"),
            // parameter codes
            TempStrNoSize("\x15""CCPPEPPPPPPPPPPPPPPL#"),
            // function display name
            TempStrNoSize("\x13""qlSABRInterpolation"),
            // comma-delimited list of parameter names
            TempStrNoSize("\xAB""ObjectId,XArray,YArray,Expiry,Forward,Alpha,Beta,Nu,Rho,AlphaIsFixed,BetaIsFixed,NuIsFixed,RhoIsFixed,VegaWeighted,EndCriteria,OptimizationMeth,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x40""Construct an object of class SABRInterpolation and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x08""x array."),
            TempStrNoSize("\x08""y array."),
            TempStrNoSize("\x15""expiry time in years."),
            TempStrNoSize("\x1A""at-the-money forward rate."),
            TempStrNoSize("\x4F""alpha (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4E""beta (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4C""nu (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x4D""rho (fixed value or guess). Default value = QuantLib::Null<QuantLib::Real>()."),
            TempStrNoSize("\x69""TRUE if the alpha value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x68""TRUE if the beta value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x66""TRUE if the nu value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x67""TRUE if the rho value provided is to be kept fixed, FALSE if it is just a guess. Default value = false."),
            TempStrNoSize("\x4F""TRUE if the interpolation is weighted using options Vega. Default value = true."),
            TempStrNoSize("\x28""EndCriteria object ID. Default value = ."),
            TempStrNoSize("\x2F""OptimizationMethod object ID. Default value = ."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x13""qlSABRInterpolation"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x18""qlSABRInterpolationAlpha"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x18""qlSABRInterpolationAlpha"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the alpha of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x18""qlSABRInterpolationAlpha"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x17""qlSABRInterpolationBeta"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x17""qlSABRInterpolationBeta"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the alpha of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlSABRInterpolationBeta"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1E""qlSABRInterpolationEndCriteria"),
            // parameter codes
            TempStrNoSize("\x04""CCP#"),
            // function display name
            TempStrNoSize("\x1E""qlSABRInterpolationEndCriteria"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x58""Returns the optimization end criteria of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1E""qlSABRInterpolationEndCriteria"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x19""qlSABRInterpolationExpiry"),
            // parameter codes
            TempStrNoSize("\x04""ECP#"),
            // function display name
            TempStrNoSize("\x19""qlSABRInterpolationExpiry"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the expiry time in years for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlSABRInterpolationExpiry"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSABRInterpolationForward"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlSABRInterpolationForward"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3C""Returns the forward  for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x31""id of existing QuantLib::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlSABRInterpolationForward"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSABRInterpolationMaxError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSABRInterpolationMaxError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x48""Returns the max error of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSABRInterpolationMaxError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x15""qlSABRInterpolationNu"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x15""qlSABRInterpolationNu"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x41""Returns the nu of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x15""qlSABRInterpolationNu"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x16""qlSABRInterpolationRho"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x16""qlSABRInterpolationRho"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x42""Returns the rho of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x16""qlSABRInterpolationRho"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1B""qlSABRInterpolationRmsError"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1B""qlSABRInterpolationRmsError"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x44""Returns the error of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1B""qlSABRInterpolationRmsError"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x1A""qlSABRInterpolationWeights"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x1A""qlSABRInterpolationWeights"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Returns the weights of the fit for the given SABRInterpolation object."),
            // parameter descriptions
            TempStrNoSize("\x36""id of existing QuantLibAddin::SABRInterpolation object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1A""qlSABRInterpolationWeights"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

