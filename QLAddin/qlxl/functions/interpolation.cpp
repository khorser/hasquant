
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
//      QuantLibAddin/gensrc/stubs/stub.excel.includes

#include <qlo/qladdindefines.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/interpolation.hpp>
#include <qlo/interpolation2D.hpp>
#include <qlo/optimization.hpp>
#include <ql/math/interpolations/sabrinterpolation.hpp>
#include <ql/math/interpolations/abcdinterpolation.hpp>
#include <ql/math/interpolations/interpolation2d.hpp>
#include <qlo/valueobjects/vo_interpolation.hpp>
#include <qlo/loop/loop_interpolation.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlAbcdInterpolation(
        char *ObjectId,
        OPER *XArray,
        OPER *YArray,
        OPER *A,
        OPER *B,
        OPER *C,
        OPER *D,
        OPER *AIsFixed,
        OPER *BIsFixed,
        OPER *CIsFixed,
        OPER *DIsFixed,
        OPER *VegaWeighted,
        OPER *EndCriteria,
        OPER *OptimizationMeth,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> XArrayCpp =
            ObjectHandler::operToVector<double>(*XArray, "XArray");

        std::vector<ObjectHandler::property_t> YArrayCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*YArray, "YArray");

        double ACpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*A), "A", QuantLib::Null<QuantLib::Real>());

        double BCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*B), "B", QuantLib::Null<QuantLib::Real>());

        double CCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*C), "C", QuantLib::Null<QuantLib::Real>());

        double DCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*D), "D", QuantLib::Null<QuantLib::Real>());

        bool AIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AIsFixed), "AIsFixed", false);

        bool BIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*BIsFixed), "BIsFixed", false);

        bool CIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*CIsFixed), "CIsFixed", false);

        bool DIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*DIsFixed), "DIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeighted), "VegaWeighted", true);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        std::string OptimizationMethCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*OptimizationMeth), "OptimizationMeth", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XArray, "XArray");

        QuantLib::Real ALib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*A), "A", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real BLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*B), "B", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real CLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*C), "C", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real DLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*D), "D", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*YArray, "YArray");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptimizationMethLibObjPtr, OptimizationMethCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string OptimizationMethStrip = ObjectHandler::CallingRange::getStub(OptimizationMethCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdInterpolation(
                ObjectIdStrip,
                XArrayCpp,
                YArrayCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdInterpolationA(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationA"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->a();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdInterpolationB(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationB"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->b();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdInterpolationC(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationC"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->c();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdInterpolationD(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationD"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->d();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlAbcdInterpolationEndCriteria(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationEndCriteria"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::EndCriteria::Type returnValue = ObjectIdObjPtr->endCriteria();

        // convert and return the return value

        std::ostringstream os;
        os << returnValue;
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(os.str(), ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdInterpolationMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationMaxError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->maxError();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlAbcdInterpolationRmsError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlAbcdInterpolationRmsError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::AbcdInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->rmsError();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlCubicInterpolation(
        char *ObjectId,
        OPER *XArray,
        OPER *YArray,
        OPER *DerApprox,
        OPER *Monotonic,
        OPER *LeftConditionType,
        OPER *LeftConditionValue,
        OPER *RightConditionType,
        OPER *RightConditionValue,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCubicInterpolation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> XArrayCpp =
            ObjectHandler::operToVector<double>(*XArray, "XArray");

        std::vector<ObjectHandler::property_t> YArrayCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*YArray, "YArray");

        std::string DerApproxCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DerApprox), "DerApprox", "Kruger");

        bool MonotonicCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Monotonic), "Monotonic", true);

        std::string LeftConditionTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*LeftConditionType), "LeftConditionType", "SecondDerivative");

        double LeftConditionValueCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*LeftConditionValue), "LeftConditionValue", 0.0);

        std::string RightConditionTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*RightConditionType), "RightConditionType", "SecondDerivative");

        double RightConditionValueCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*RightConditionValue), "RightConditionValue", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XArray, "XArray");

        QuantLib::Real LeftConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*LeftConditionValue), "LeftConditionValue", 0.0);

        QuantLib::Real RightConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*RightConditionValue), "RightConditionValue", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CubicInterpolation::DerivativeApprox DerApproxEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox>()(DerApproxCpp);

        QuantLib::CubicInterpolation::BoundaryCondition LeftConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(LeftConditionTypeCpp);

        QuantLib::CubicInterpolation::BoundaryCondition RightConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(RightConditionTypeCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*YArray, "YArray");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCubicInterpolation(
                ObjectIdStrip,
                XArrayCpp,
                YArrayCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCubicInterpolationACoefficients(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCubicInterpolationACoefficients"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::CubicInterpolation)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdObjPtr->aCoefficients();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCubicInterpolationBCoefficients(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCubicInterpolationBCoefficients"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::CubicInterpolation)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdObjPtr->bCoefficients();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCubicInterpolationCCoefficients(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCubicInterpolationCCoefficients"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::CubicInterpolation)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdObjPtr->cCoefficients();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCubicInterpolationMonotonicityAdjustments(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCubicInterpolationMonotonicityAdjustments"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::CubicInterpolation)

        // invoke the member function

        std::vector<bool> returnValue = ObjectIdObjPtr->monotonicityAdjustments();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::vectorToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCubicInterpolationPrimitiveConstants(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCubicInterpolationPrimitiveConstants"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::CubicInterpolation)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdObjPtr->primitiveConstants();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC bool *qlExtrapolatorEnableExtrapolation(
        char *ObjectId,
        OPER *ExtrapolationFlag,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlExtrapolatorEnableExtrapolation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool ExtrapolationFlagCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*ExtrapolationFlag), "ExtrapolationFlag", true);

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Extrapolator)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->enableExtrapolation(
                ExtrapolationFlagCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlInterpolation(
        char *ObjectId,
        OPER *InterpolationType,
        OPER *XArray,
        OPER *YArray,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string InterpolationTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*InterpolationType), "InterpolationType", "MonotonicNaturalCubicSpline");

        std::vector<double> XArrayCpp =
            ObjectHandler::operToVector<double>(*XArray, "XArray");

        std::vector<ObjectHandler::property_t> YArrayCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*YArray, "YArray");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XArray, "XArray");

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*YArray, "YArray");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolation(
                ObjectIdStrip,
                InterpolationTypeCpp,
                XArrayCpp,
                YArrayCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlInterpolation2D(
        char *ObjectId,
        OPER *InterpolationType,
        OPER *XArray,
        OPER *YArray,
        FP *ZMatrix,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2D"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string InterpolationTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*InterpolationType), "InterpolationType", "BiLinear");

        std::vector<double> XArrayCpp =
            ObjectHandler::operToVector<double>(*XArray, "XArray");

        std::vector<double> YArrayCpp =
            ObjectHandler::operToVector<double>(*YArray, "YArray");

        std::vector<std::vector<double> > ZMatrixCpp =
            ObjectHandler::fpToMatrix<double>(*ZMatrix);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XArray, "XArray");

        std::vector<QuantLib::Real> YArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*YArray, "YArray");

        QuantLib::Matrix ZMatrixLib =
            QuantLibXL::operToQlMatrix(*ZMatrix);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolation2D(
                ObjectIdStrip,
                InterpolationTypeCpp,
                XArrayCpp,
                YArrayCpp,
                ZMatrixCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Interpolation2D(
                valueObject,
                InterpolationTypeCpp,
                XArrayLib,
                YArrayLib,
                ZMatrixLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DInterpolate(
        char *ObjectId,
        OPER *XValue,
        double *YValue,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DInterpolate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValueLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValue, "XValue");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolation2DInterpolateBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolation2DInterpolateSignature)
                &QuantLib::Interpolation2D::operator(),
                ObjectIdLibObjPtr,
                _1,
                *YValue,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolation2DInterpolateBind, QuantLib::Real, QuantLib::Real>
            (functionCall, bindObject, XValue, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DIsInRange(
        char *ObjectId,
        OPER *XValues,
        double *YValue,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DIsInRange"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValues, "XValues");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolation2DIsInRangeBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolation2DIsInRangeSignature)
                &QuantLib::Interpolation2D::isInRange,
                ObjectIdLibObjPtr,
                _1,
                *YValue);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolation2DIsInRangeBind, QuantLib::Real, bool>
            (functionCall, bindObject, XValues, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DXmax(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DXmax"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->xMax();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DXmin(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DXmin"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->xMin();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DXvalues(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DXvalues"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->xValues();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DYmax(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DYmax"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->yMax();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DYmin(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DYmin"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->yMin();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DYvalues(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DYvalues"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdLibObjPtr->yValues();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolation2DzData(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolation2DzData"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation2D, QuantLib::Interpolation2D)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->zData();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationDerivative(
        char *ObjectId,
        OPER *XValues,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationDerivative"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValues, "XValues");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Interpolation)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolationDerivativeBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolationDerivativeSignature)
                &QuantLibAddin::Interpolation::derivative,
                ObjectIdObjPtr,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolationDerivativeBind, QuantLib::Real, QuantLib::Real>
            (functionCall, bindObject, XValues, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationInterpolate(
        char *ObjectId,
        OPER *XValues,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationInterpolate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValues, "XValues");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Interpolation)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolationInterpolateBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolationInterpolateSignature)
                &QuantLibAddin::Interpolation::operator(),
                ObjectIdObjPtr,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolationInterpolateBind, QuantLib::Real, QuantLib::Real>
            (functionCall, bindObject, XValues, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationIsInRange(
        char *ObjectId,
        OPER *XValues,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationIsInRange"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValues, "XValues");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation, QuantLib::Interpolation)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolationIsInRangeBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolationIsInRangeSignature)
                &QuantLib::Interpolation::isInRange,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolationIsInRangeBind, QuantLib::Real, bool>
            (functionCall, bindObject, XValues, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationPrimitive(
        char *ObjectId,
        OPER *XValues,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationPrimitive"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValues, "XValues");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Interpolation)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolationPrimitiveBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolationPrimitiveSignature)
                &QuantLibAddin::Interpolation::primitive,
                ObjectIdObjPtr,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolationPrimitiveBind, QuantLib::Real, QuantLib::Real>
            (functionCall, bindObject, XValues, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationSecondDerivative(
        char *ObjectId,
        OPER *XValues,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationSecondDerivative"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XValues, "XValues");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Interpolation)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterpolationSecondDerivativeBind bindObject = 
            boost::bind((QuantLibAddin::qlInterpolationSecondDerivativeSignature)
                &QuantLibAddin::Interpolation::secondDerivative,
                ObjectIdObjPtr,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlInterpolationSecondDerivativeBind, QuantLib::Real, QuantLib::Real>
            (functionCall, bindObject, XValues, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationXmax(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationXmax"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation, QuantLib::Interpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->xMax();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterpolationXmin(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolationXmin"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Interpolation, QuantLib::Interpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->xMin();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlMixedLinearCubicInterpolation(
        char *ObjectId,
        OPER *XArray,
        OPER *YArray,
        long *SwitchIndex,
        OPER *DerApprox,
        OPER *Monotonic,
        OPER *LeftConditionType,
        OPER *LeftConditionValue,
        OPER *RightConditionType,
        OPER *RightConditionValue,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMixedLinearCubicInterpolation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> XArrayCpp =
            ObjectHandler::operToVector<double>(*XArray, "XArray");

        std::vector<ObjectHandler::property_t> YArrayCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*YArray, "YArray");

        std::string DerApproxCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DerApprox), "DerApprox", "Kruger");

        bool MonotonicCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Monotonic), "Monotonic", true);

        std::string LeftConditionTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*LeftConditionType), "LeftConditionType", "SecondDerivative");

        double LeftConditionValueCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*LeftConditionValue), "LeftConditionValue", 0.0);

        std::string RightConditionTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*RightConditionType), "RightConditionType", "SecondDerivative");

        double RightConditionValueCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*RightConditionValue), "RightConditionValue", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XArray, "XArray");

        QuantLib::Size SwitchIndexLib;
        QuantLibAddin::cppToLibrary(*SwitchIndex, SwitchIndexLib);

        QuantLib::Real LeftConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*LeftConditionValue), "LeftConditionValue", 0.0);

        QuantLib::Real RightConditionValueLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*RightConditionValue), "RightConditionValue", 0.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CubicInterpolation::DerivativeApprox DerApproxEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox>()(DerApproxCpp);

        QuantLib::CubicInterpolation::BoundaryCondition LeftConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(LeftConditionTypeCpp);

        QuantLib::CubicInterpolation::BoundaryCondition RightConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(RightConditionTypeCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*YArray, "YArray");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMixedLinearCubicInterpolation(
                ObjectIdStrip,
                XArrayCpp,
                YArrayCpp,
                *SwitchIndex,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSABRInterpolation(
        char *ObjectId,
        OPER *XArray,
        OPER *YArray,
        double *Expiry,
        OPER *Forward,
        OPER *Alpha,
        OPER *Beta,
        OPER *Nu,
        OPER *Rho,
        OPER *AlphaIsFixed,
        OPER *BetaIsFixed,
        OPER *NuIsFixed,
        OPER *RhoIsFixed,
        OPER *VegaWeighted,
        OPER *EndCriteria,
        OPER *OptimizationMeth,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolation"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> XArrayCpp =
            ObjectHandler::operToVector<double>(*XArray, "XArray");

        std::vector<ObjectHandler::property_t> YArrayCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*YArray, "YArray");

        ObjectHandler::property_t ForwardCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Forward));

        double AlphaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Alpha), "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Beta), "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Nu), "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Rho), "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AlphaIsFixed), "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*BetaIsFixed), "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*NuIsFixed), "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*RhoIsFixed), "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeighted), "VegaWeighted", true);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        std::string OptimizationMethCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*OptimizationMeth), "OptimizationMeth", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib =
            ObjectHandler::operToVector<QuantLib::Real>(*XArray, "XArray");

        QuantLib::Real AlphaLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Alpha), "Alpha", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real BetaLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Beta), "Beta", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real NuLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Nu), "Nu", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real RhoLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Rho), "Rho", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*YArray, "YArray");

        QuantLib::Handle<QuantLib::Quote> ForwardLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Forward), "Forward");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptimizationMethLibObjPtr, OptimizationMethCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string OptimizationMethStrip = ObjectHandler::CallingRange::getStub(OptimizationMethCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSABRInterpolation(
                ObjectIdStrip,
                XArrayCpp,
                YArrayCpp,
                *Expiry,
                ForwardCpp,
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
                *Expiry,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationAlpha(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationAlpha"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->alpha();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationBeta(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationBeta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->beta();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSABRInterpolationEndCriteria(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationEndCriteria"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::EndCriteria::Type returnValue = ObjectIdObjPtr->endCriteria();

        // convert and return the return value

        std::ostringstream os;
        os << returnValue;
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(os.str(), ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlSABRInterpolationExpiry(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationExpiry"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SABRInterpolation, QuantLib::SABRInterpolation)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->expiry();

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationForward(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationForward"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SABRInterpolation, QuantLib::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->forward();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationMaxError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->maxError();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationNu(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationNu"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->nu();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationRho(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationRho"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->rho();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationRmsError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationRmsError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->rmsError();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSABRInterpolationWeights(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSABRInterpolationWeights"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::SABRInterpolation)

        // invoke the member function

        std::vector<QuantLib::Real> returnValue = ObjectIdObjPtr->interpolationWeights();

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
