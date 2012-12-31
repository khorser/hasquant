
/*  
 Copyright (C) 2006, 2007, 2008, 2010 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/interpolation.hpp>
#include <qlo/interpolation2D.hpp>
#include <qlo/optimization.hpp>
#include <ql/math/interpolations/sabrinterpolation.hpp>
#include <ql/math/interpolations/abcdinterpolation.hpp>
#include <ql/math/interpolations/interpolation2d.hpp>
#include <qlo/valueobjects/vo_interpolation.hpp>
#include <qlo/loop/loop_interpolation.hpp>
#include <Addins/Cpp/loop.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAbcdInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const ObjectHandler::property_t &A,
            const ObjectHandler::property_t &B,
            const ObjectHandler::property_t &C,
            const ObjectHandler::property_t &D,
            const ObjectHandler::property_t &AIsFixed,
            const ObjectHandler::property_t &BIsFixed,
            const ObjectHandler::property_t &CIsFixed,
            const ObjectHandler::property_t &DIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &OptimizationMeth,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double ACpp = ObjectHandler::convert2<double>(
            A, "A", QuantLib::Null<QuantLib::Real>());

        double BCpp = ObjectHandler::convert2<double>(
            B, "B", QuantLib::Null<QuantLib::Real>());

        double CCpp = ObjectHandler::convert2<double>(
            C, "C", QuantLib::Null<QuantLib::Real>());

        double DCpp = ObjectHandler::convert2<double>(
            D, "D", QuantLib::Null<QuantLib::Real>());

        bool AIsFixedCpp = ObjectHandler::convert2<bool>(
            AIsFixed, "AIsFixed", false);

        bool BIsFixedCpp = ObjectHandler::convert2<bool>(
            BIsFixed, "BIsFixed", false);

        bool CIsFixedCpp = ObjectHandler::convert2<bool>(
            CIsFixed, "CIsFixed", false);

        bool DIsFixedCpp = ObjectHandler::convert2<bool>(
            DIsFixed, "DIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            VegaWeighted, "VegaWeighted", true);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        std::string OptimizationMethCpp = ObjectHandler::convert2<std::string>(
            OptimizationMeth, "OptimizationMeth", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real ALib = ObjectHandler::convert2<QuantLib::Real>(
            A, "A", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real BLib = ObjectHandler::convert2<QuantLib::Real>(
            B, "B", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real CLib = ObjectHandler::convert2<QuantLib::Real>(
            C, "C", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real DLib = ObjectHandler::convert2<QuantLib::Real>(
            D, "D", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptimizationMethLibObjPtr, OptimizationMethCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdInterpolation(
                ObjectId,
                XArray,
                YArray,
                ACpp,
                BCpp,
                CCpp,
                DCpp,
                AIsFixedCpp,
                BIsFixedCpp,
                CIsFixedCpp,
                DIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                OptimizationMethCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                ALib,
                BLib,
                CLib,
                DLib,
                AIsFixedCpp,
                BIsFixedCpp,
                CIsFixedCpp,
                DIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                OptimizationMethLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAbcdInterpolation : " << e.what());
        }
    }


    std::string qlCubicInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const ObjectHandler::property_t &DerApprox,
            const ObjectHandler::property_t &Monotonic,
            const ObjectHandler::property_t &LeftConditionType,
            const ObjectHandler::property_t &LeftConditionValue,
            const ObjectHandler::property_t &RightConditionType,
            const ObjectHandler::property_t &RightConditionValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DerApproxCpp = ObjectHandler::convert2<std::string>(
            DerApprox, "DerApprox", "Kruger");

        bool MonotonicCpp = ObjectHandler::convert2<bool>(
            Monotonic, "Monotonic", true);

        std::string LeftConditionTypeCpp = ObjectHandler::convert2<std::string>(
            LeftConditionType, "LeftConditionType", "SecondDerivative");

        double LeftConditionValueCpp = ObjectHandler::convert2<double>(
            LeftConditionValue, "LeftConditionValue", 0.0);

        std::string RightConditionTypeCpp = ObjectHandler::convert2<std::string>(
            RightConditionType, "RightConditionType", "SecondDerivative");

        double RightConditionValueCpp = ObjectHandler::convert2<double>(
            RightConditionValue, "RightConditionValue", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real LeftConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            LeftConditionValue, "LeftConditionValue", 0.0);

        QuantLib::Real RightConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            RightConditionValue, "RightConditionValue", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CubicInterpolation::DerivativeApprox DerApproxEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox>()(DerApproxCpp);

        QuantLib::CubicInterpolation::BoundaryCondition LeftConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(LeftConditionTypeCpp);

        QuantLib::CubicInterpolation::BoundaryCondition RightConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(RightConditionTypeCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCubicInterpolation(
                ObjectId,
                XArray,
                YArray,
                DerApproxCpp,
                MonotonicCpp,
                LeftConditionTypeCpp,
                LeftConditionValueCpp,
                RightConditionTypeCpp,
                RightConditionValueCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CubicInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                DerApproxEnum,
                MonotonicCpp,
                LeftConditionTypeEnum,
                LeftConditionValueLib,
                RightConditionTypeEnum,
                RightConditionValueLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCubicInterpolation : " << e.what());
        }
    }


    bool qlExtrapolatorEnableExtrapolation(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ExtrapolationFlag,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        bool ExtrapolationFlagCpp = ObjectHandler::convert2<bool>(
            ExtrapolationFlag, "ExtrapolationFlag", true);

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Extrapolator)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->enableExtrapolation(
                ExtrapolationFlagCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlExtrapolatorEnableExtrapolation : " << e.what());
        }
    }


    std::string qlInterpolation(
            const std::string &ObjectId,
            const ObjectHandler::property_t &InterpolationType,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string InterpolationTypeCpp = ObjectHandler::convert2<std::string>(
            InterpolationType, "InterpolationType", "MonotonicNaturalCubicSpline");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolation(
                ObjectId,
                InterpolationTypeCpp,
                XArray,
                YArray,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GenericInterp(
                valueObject,
                InterpolationTypeCpp,
                XArrayLib,
                YArrayLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInterpolation : " << e.what());
        }
    }


    std::string qlMixedLinearCubicInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const long &SwitchIndex,
            const ObjectHandler::property_t &DerApprox,
            const ObjectHandler::property_t &Monotonic,
            const ObjectHandler::property_t &LeftConditionType,
            const ObjectHandler::property_t &LeftConditionValue,
            const ObjectHandler::property_t &RightConditionType,
            const ObjectHandler::property_t &RightConditionValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DerApproxCpp = ObjectHandler::convert2<std::string>(
            DerApprox, "DerApprox", "Kruger");

        bool MonotonicCpp = ObjectHandler::convert2<bool>(
            Monotonic, "Monotonic", true);

        std::string LeftConditionTypeCpp = ObjectHandler::convert2<std::string>(
            LeftConditionType, "LeftConditionType", "SecondDerivative");

        double LeftConditionValueCpp = ObjectHandler::convert2<double>(
            LeftConditionValue, "LeftConditionValue", 0.0);

        std::string RightConditionTypeCpp = ObjectHandler::convert2<std::string>(
            RightConditionType, "RightConditionType", "SecondDerivative");

        double RightConditionValueCpp = ObjectHandler::convert2<double>(
            RightConditionValue, "RightConditionValue", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Size SwitchIndexLib;
        QuantLibAddin::cppToLibrary(SwitchIndex, SwitchIndexLib);

        QuantLib::Real LeftConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            LeftConditionValue, "LeftConditionValue", 0.0);

        QuantLib::Real RightConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            RightConditionValue, "RightConditionValue", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CubicInterpolation::DerivativeApprox DerApproxEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox>()(DerApproxCpp);

        QuantLib::CubicInterpolation::BoundaryCondition LeftConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(LeftConditionTypeCpp);

        QuantLib::CubicInterpolation::BoundaryCondition RightConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(RightConditionTypeCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMixedLinearCubicInterpolation(
                ObjectId,
                XArray,
                YArray,
                SwitchIndex,
                DerApproxCpp,
                MonotonicCpp,
                LeftConditionTypeCpp,
                LeftConditionValueCpp,
                RightConditionTypeCpp,
                RightConditionValueCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MixedLinearCubicInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                SwitchIndexLib,
                DerApproxEnum,
                MonotonicCpp,
                LeftConditionTypeEnum,
                LeftConditionValueLib,
                RightConditionTypeEnum,
                RightConditionValueLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMixedLinearCubicInterpolation : " << e.what());
        }
    }


    std::string qlSABRInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const double &Expiry,
            const ObjectHandler::property_t &Forward,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &OptimizationMeth,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double AlphaCpp = ObjectHandler::convert2<double>(
            Alpha, "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            Beta, "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            Nu, "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            Rho, "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            AlphaIsFixed, "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            BetaIsFixed, "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            NuIsFixed, "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            RhoIsFixed, "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            VegaWeighted, "VegaWeighted", true);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        std::string OptimizationMethCpp = ObjectHandler::convert2<std::string>(
            OptimizationMeth, "OptimizationMeth", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real AlphaLib = ObjectHandler::convert2<QuantLib::Real>(
            Alpha, "Alpha", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real BetaLib = ObjectHandler::convert2<QuantLib::Real>(
            Beta, "Beta", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real NuLib = ObjectHandler::convert2<QuantLib::Real>(
            Nu, "Nu", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real RhoLib = ObjectHandler::convert2<QuantLib::Real>(
            Rho, "Rho", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        QuantLib::Handle<QuantLib::Quote> ForwardLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Forward, "Forward");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptimizationMethLibObjPtr, OptimizationMethCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSABRInterpolation(
                ObjectId,
                XArray,
                YArray,
                Expiry,
                Forward,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                OptimizationMethCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SABRInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                Expiry,
                ForwardLibObj,
                AlphaLib,
                BetaLib,
                NuLib,
                RhoLib,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                OptimizationMethLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSABRInterpolation : " << e.what());
        }
    }

}

