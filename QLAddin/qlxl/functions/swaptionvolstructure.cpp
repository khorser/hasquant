
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Silvia Frasson
 Copyright (C) 2006 Mario Pucci
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 
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
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/optimization.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube.hpp>
#include <qlo/valueobjects/vo_swaptionvolstructure.hpp>
#include <qlo/loop/loop_swaptionvolstructure.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlConstantSwaptionVolatility(
        char *ObjectId,
        OPER *NDays,
        char *Calendar,
        char *BusinessDayConvention,
        OPER *Volatility,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlConstantSwaptionVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        long NDaysCpp = ObjectHandler::convert2<long>(
            ObjectHandler::ConvertOper(*NDays), "NDays", 0);

        ObjectHandler::property_t VolatilityCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Volatility));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            ObjectHandler::ConvertOper(*NDays), "NDays", 0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> VolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Volatility), "Volatility");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlConstantSwaptionVolatility(
                ObjectIdStrip,
                NDaysCpp,
                Calendar,
                BusinessDayConvention,
                VolatilityCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ConstantSwaptionVolatility(
                valueObject,
                NDaysLib,
                CalendarEnum,
                BusinessDayConventionEnum,
                VolatilityLibObj,
                DayCounterEnum,
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
XLL_DEC OPER *qlDenseSabrParameters(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlDenseSabrParameters"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SwaptionVolCube1> ObjectIdObjPtr =
            QuantLibAddin::CoerceTermStructureObject<QuantLibAddin::SwaptionVolCube1>()(
                ObjectIdTemp);

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->getDenseSabrParameters();

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
XLL_DEC OPER *qlMarketVolCube(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlMarketVolCube"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SwaptionVolCube1> ObjectIdObjPtr =
            QuantLibAddin::CoerceTermStructureObject<QuantLibAddin::SwaptionVolCube1>()(
                ObjectIdTemp);

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->getMarketVolCube();

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
XLL_DEC char *qlRelinkableHandleSwaptionVolatilityStructure(
        char *ObjectId,
        OPER *CurrentLink,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRelinkableHandleSwaptionVolatilityStructure"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string CurrentLinkCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*CurrentLink), "CurrentLink", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRelinkableHandleSwaptionVolatilityStructure(
                ObjectIdStrip,
                CurrentLinkCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::SwaptionVolatilityStructure, QuantLib::SwaptionVolatilityStructure>(
                valueObject,
                CurrentLinkCpp,
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
XLL_DEC char *qlSmileSectionByCube(
        char *ObjectId,
        char *VolCube,
        OPER *OptionDate,
        char *SwapTenor,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionByCube"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolCubeTemp, VolCube, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> VolCubeLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    VolCubeTemp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string VolCubeStrip = ObjectHandler::CallingRange::getStub(VolCube);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSmileSectionByCube(
                ObjectIdStrip,
                VolCubeStrip,
                OptionDateCpp,
                SwapTenor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionByCube(
                valueObject,
                VolCubeLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
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
XLL_DEC char *qlSmileSectionByCube2(
        char *ObjectId,
        char *VolCube,
        char *OptionDate,
        char *SwapTenor,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionByCube2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionDateLib;
        QuantLibAddin::cppToLibrary(OptionDate, OptionDateLib);

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolCubeTemp, VolCube, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> VolCubeLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    VolCubeTemp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string VolCubeStrip = ObjectHandler::CallingRange::getStub(VolCube);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSmileSectionByCube2(
                ObjectIdStrip,
                VolCubeStrip,
                OptionDate,
                SwapTenor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionByCube(
                valueObject,
                VolCubeLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
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
XLL_DEC OPER *qlSparseSabrParameters(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSparseSabrParameters"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SwaptionVolCube1> ObjectIdObjPtr =
            QuantLibAddin::CoerceTermStructureObject<QuantLibAddin::SwaptionVolCube1>()(
                ObjectIdTemp);

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->getSparseSabrParameters();

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
XLL_DEC char *qlSpreadedSwaptionVolatility(
        char *ObjectId,
        char *BaseVolStructure,
        OPER *Spread,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSpreadedSwaptionVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Spread));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseVolStructureCoerce, BaseVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> BaseVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    BaseVolStructureCoerce);

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Spread), "Spread");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string BaseVolStructureStrip = ObjectHandler::CallingRange::getStub(BaseVolStructure);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSpreadedSwaptionVolatility(
                ObjectIdStrip,
                BaseVolStructureStrip,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadedSwaptionVolatility(
                valueObject,
                BaseVolStructureLibObj,
                SpreadLibObj,
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
XLL_DEC OPER *qlSwaptionVTSBlackVariance(
        char *ObjectId,
        OPER *OptionDate,
        char *SwapTenor,
        double *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSBlackVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> OptionDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*OptionDate, "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSBlackVarianceBind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSBlackVarianceSignature)
                &QuantLib::SwaptionVolatilityStructure::blackVariance,
                ObjectIdLibObjPtr,
                _1,
                SwapTenorLib,
                *Strike,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSBlackVarianceBind, QuantLib::Date, double>
            (functionCall, bindObject, OptionDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSwaptionVTSBlackVariance2(
        char *ObjectId,
        OPER *OptionTenor,
        char *SwapTenor,
        double *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSBlackVariance2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenor, "OptionTenor");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSBlackVariance2Bind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSBlackVariance2Signature)
                &QuantLib::SwaptionVolatilityStructure::blackVariance,
                ObjectIdLibObjPtr,
                _1,
                SwapTenorLib,
                *Strike,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSBlackVariance2Bind, QuantLib::Period, double>
            (functionCall, bindObject, OptionTenor, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSwaptionVTSBusinessDayConvention(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSBusinessDayConvention"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::BusinessDayConvention returnValue = ObjectIdLibObjPtr->businessDayConvention();

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
XLL_DEC char *qlSwaptionVTSMatrix(
        char *ObjectId,
        char *Calendar,
        char *BusinessDayConvention,
        OPER *OptionTenors,
        OPER *SwapTenors,
        OPER *Volatilities,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSMatrix"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> OptionTenorsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*OptionTenors, "OptionTenors");

        std::vector<ObjectHandler::property_t> SwapTenorsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*SwapTenors, "SwapTenors");

        std::vector<std::vector<ObjectHandler::property_t> > VolatilitiesCpp =
            ObjectHandler::operToMatrix<ObjectHandler::property_t>(*Volatilities, "Volatilities");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenors, "OptionTenors");

        std::vector<QuantLib::Period> SwapTenorsLib =
            ObjectHandler::operToVector<QuantLib::Period>(*SwapTenors, "SwapTenors");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
            ObjectHandler::operToMatrix<QuantLib::Handle<QuantLib::Quote> >(*Volatilities, "Volatilities");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaptionVTSMatrix(
                ObjectIdStrip,
                Calendar,
                BusinessDayConvention,
                OptionTenorsCpp,
                SwapTenorsCpp,
                VolatilitiesCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolatilityMatrix(
                valueObject,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                SwapTenorsLib,
                VolatilitiesLibObj,
                DayCounterEnum,
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
XLL_DEC OPER *qlSwaptionVTSMatrixLocate(
        char *ObjectId,
        OPER *OptionDate,
        char *SwapTenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSMatrixLocate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SwaptionVolatilityMatrix> ObjectIdObjPtr =
            QuantLibAddin::CoerceTermStructureObject<QuantLibAddin::SwaptionVolatilityMatrix>()(
                ObjectIdTemp);

        // invoke the member function

        std::vector<long> returnValue = ObjectIdObjPtr->locate(
                OptionDateLib,
                SwapTenorLib);

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
XLL_DEC OPER *qlSwaptionVTSMatrixOptionDates(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSMatrixOptionDates"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityDiscrete> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityDiscrete,
                QuantLib::SwaptionVolatilityDiscrete>()(
                    ObjectIdTemp);

        // invoke the member function

        std::vector<QuantLib::Date> returnValue = ObjectIdLibObjPtr->optionDates();

        // convert and return the return value

        std::vector<long> returnValVec = QuantLibAddin::libraryToVector(returnValue);
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
XLL_DEC OPER *qlSwaptionVTSMatrixOptionTenors(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSMatrixOptionTenors"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityDiscrete> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityDiscrete,
                QuantLib::SwaptionVolatilityDiscrete>()(
                    ObjectIdTemp);

        // invoke the member function

        std::vector<QuantLib::Period> returnValue = ObjectIdLibObjPtr->optionTenors();

        // convert and return the return value

        std::vector<std::string> returnValVec = QuantLibAddin::libraryToVector(returnValue);
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
XLL_DEC OPER *qlSwaptionVTSMatrixSwapTenors(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSMatrixSwapTenors"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityDiscrete> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityDiscrete,
                QuantLib::SwaptionVolatilityDiscrete>()(
                    ObjectIdTemp);

        // invoke the member function

        std::vector<QuantLib::Period> returnValue = ObjectIdLibObjPtr->swapTenors();

        // convert and return the return value

        std::vector<std::string> returnValVec = QuantLibAddin::libraryToVector(returnValue);
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
XLL_DEC char *qlSwaptionVTSMaxSwapTenor(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSMaxSwapTenor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Period returnValue = ObjectIdLibObjPtr->maxSwapTenor();

        // convert and return the return value

        std::string str = QuantLibAddin::libraryToScalar(returnValue);
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(str, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSwaptionVTSOptionDateFromTenor(
        char *ObjectId,
        OPER *OptionTenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSOptionDateFromTenor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenor, "OptionTenor");

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSOptionDateFromTenorBind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSOptionDateFromTenorSignature)
                &QuantLib::SwaptionVolatilityStructure::optionDateFromTenor,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSOptionDateFromTenorBind, QuantLib::Period, QuantLib::Date>
            (functionCall, bindObject, OptionTenor, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSwaptionVTSSwapLength(
        char *ObjectId,
        OPER *SwapTenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSSwapLength"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> SwapTenorLib =
            ObjectHandler::operToVector<QuantLib::Period>(*SwapTenor, "SwapTenor");

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSSwapLengthBind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSSwapLengthSignature)
                &QuantLib::SwaptionVolatilityStructure::swapLength,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSSwapLengthBind, QuantLib::Period, double>
            (functionCall, bindObject, SwapTenor, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlSwaptionVTSSwapLength2(
        char *ObjectId,
        OPER *SwapStart,
        OPER *SwapEnd,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSSwapLength2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SwapStartCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SwapStart));

        ObjectHandler::property_t SwapEndCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*SwapEnd));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SwapStartLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SwapStart), "SwapStart");

        QuantLib::Date SwapEndLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*SwapEnd), "SwapEnd");

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->swapLength(
                SwapStartLib,
                SwapEndLib);

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
XLL_DEC OPER *qlSwaptionVTSVolatility(
        char *ObjectId,
        OPER *OptionDate,
        char *SwapTenor,
        OPER *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSVolatilityBind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSVolatilitySignature)
                &QuantLib::SwaptionVolatilityStructure::volatility,
                ObjectIdLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSVolatilityBind, double, double>
            (functionCall, bindObject, Strike, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSwaptionVTSVolatility2(
        char *ObjectId,
        char *OptionTenor,
        char *SwapTenor,
        OPER *Strike,
        OPER *AllowExtrapolation,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSVolatility2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool AllowExtrapolationCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AllowExtrapolation), "AllowExtrapolation", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionTenorLib;
        QuantLibAddin::cppToLibrary(OptionTenor, OptionTenorLib);

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSVolatility2Bind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSVolatility2Signature)
                &QuantLib::SwaptionVolatilityStructure::volatility,
                ObjectIdLibObjPtr,
                OptionTenorLib,
                SwapTenorLib,
                _1,
                AllowExtrapolationCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSVolatility2Bind, double, double>
            (functionCall, bindObject, Strike, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSwaptionVTSatmStrike(
        char *ObjectId,
        OPER *OptionDate,
        char *SwapTenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSatmStrike"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> OptionDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*OptionDate, "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSatmStrikeBind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSatmStrikeSignature)
                &QuantLib::SwaptionVolatilityCube::atmStrike,
                ObjectIdLibObjPtr,
                _1,
                SwapTenorLib);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSatmStrikeBind, QuantLib::Date, double>
            (functionCall, bindObject, OptionDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSwaptionVTSatmStrike2(
        char *ObjectId,
        OPER *OptionTenor,
        char *SwapTenor,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVTSatmStrike2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenor, "OptionTenor");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    ObjectIdTemp);

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlSwaptionVTSatmStrike2Bind bindObject = 
            boost::bind((QuantLibAddin::qlSwaptionVTSatmStrike2Signature)
                &QuantLib::SwaptionVolatilityCube::atmStrike,
                ObjectIdLibObjPtr,
                _1,
                SwapTenorLib);
        ObjectHandler::loop
            <QuantLibAddin::qlSwaptionVTSatmStrike2Bind, QuantLib::Period, double>
            (functionCall, bindObject, OptionTenor, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSwaptionVolCube1(
        char *ObjectId,
        char *AtmVolStructure,
        OPER *OptionTenors,
        OPER *SwapTenors,
        OPER *StrikeSpreads,
        OPER *SpreadVols,
        char *SwapIndexBase,
        char *ShortSwapIndexBase,
        OPER *VegaWeightedSmileFit,
        OPER *Guess,
        OPER *IsFixed,
        bool *IsAtmCalibrated,
        OPER *EndCriteria,
        OPER *MaxErrorTol,
        OPER *OptMethod,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVolCube1"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> OptionTenorsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*OptionTenors, "OptionTenors");

        std::vector<ObjectHandler::property_t> SwapTenorsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*SwapTenors, "SwapTenors");

        std::vector<double> StrikeSpreadsCpp =
            ObjectHandler::operToVector<double>(*StrikeSpreads, "StrikeSpreads");

        std::vector<std::vector<ObjectHandler::property_t> > SpreadVolsCpp =
            ObjectHandler::operToMatrix<ObjectHandler::property_t>(*SpreadVols, "SpreadVols");

        bool VegaWeightedSmileFitCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeightedSmileFit), "VegaWeightedSmileFit", true);

        std::vector<std::vector<ObjectHandler::property_t> > GuessCpp =
            ObjectHandler::operToMatrix<ObjectHandler::property_t>(*Guess, "Guess");

        std::vector<bool> IsFixedCpp =
            ObjectHandler::operToVector<bool>(*IsFixed, "IsFixed");

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        double MaxErrorTolCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*MaxErrorTol), "MaxErrorTol", QuantLib::Null<QuantLib::Real>());

        std::string OptMethodCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*OptMethod), "OptMethod", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenors, "OptionTenors");

        std::vector<QuantLib::Period> SwapTenorsLib =
            ObjectHandler::operToVector<QuantLib::Period>(*SwapTenors, "SwapTenors");

        // convert object IDs into library objects

        OH_GET_OBJECT(AtmVolStructureCoerce, AtmVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> AtmVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    AtmVolStructureCoerce);

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > SpreadVolsLibObj =
            ObjectHandler::operToMatrix<QuantLib::Handle<QuantLib::Quote> >(*SpreadVols, "SpreadVols");

        OH_GET_REFERENCE(SwapIndexBaseLibObjPtr, SwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(ShortSwapIndexBaseLibObjPtr, ShortSwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > GuessLibObj =
            ObjectHandler::operToMatrix<QuantLib::Handle<QuantLib::Quote> >(*Guess, "Guess");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptMethodLibObjPtr, OptMethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string AtmVolStructureStrip = ObjectHandler::CallingRange::getStub(AtmVolStructure);
        std::string SwapIndexBaseStrip = ObjectHandler::CallingRange::getStub(SwapIndexBase);
        std::string ShortSwapIndexBaseStrip = ObjectHandler::CallingRange::getStub(ShortSwapIndexBase);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string OptMethodStrip = ObjectHandler::CallingRange::getStub(OptMethodCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaptionVolCube1(
                ObjectIdStrip,
                AtmVolStructureStrip,
                OptionTenorsCpp,
                SwapTenorsCpp,
                StrikeSpreadsCpp,
                SpreadVolsCpp,
                SwapIndexBaseStrip,
                ShortSwapIndexBaseStrip,
                VegaWeightedSmileFitCpp,
                GuessCpp,
                IsFixedCpp,
                *IsAtmCalibrated,
                EndCriteriaCpp,
                MaxErrorTolCpp,
                OptMethodCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolCube1(
                valueObject,
                AtmVolStructureLibObj,
                OptionTenorsLib,
                SwapTenorsLib,
                StrikeSpreadsCpp,
                SpreadVolsLibObj,
                SwapIndexBaseLibObjPtr,
                ShortSwapIndexBaseLibObjPtr,
                VegaWeightedSmileFitCpp,
                GuessLibObj,
                IsFixedCpp,
                *IsAtmCalibrated,
                EndCriteriaLibObjPtr,
                MaxErrorTolCpp,
                OptMethodLibObjPtr,
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
XLL_DEC char *qlSwaptionVolCube2(
        char *ObjectId,
        char *AtmVolStructure,
        OPER *OptionTenor,
        OPER *SwapTenor,
        OPER *StrikeSpreads,
        OPER *SpreadVols,
        char *SwapIndexBase,
        char *ShortSwapIndexBase,
        OPER *VegaWeightedSmileFit,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwaptionVolCube2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> OptionTenorCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*OptionTenor, "OptionTenor");

        std::vector<ObjectHandler::property_t> SwapTenorCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*SwapTenor, "SwapTenor");

        std::vector<double> StrikeSpreadsCpp =
            ObjectHandler::operToVector<double>(*StrikeSpreads, "StrikeSpreads");

        std::vector<std::vector<ObjectHandler::property_t> > SpreadVolsCpp =
            ObjectHandler::operToMatrix<ObjectHandler::property_t>(*SpreadVols, "SpreadVols");

        bool VegaWeightedSmileFitCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeightedSmileFit), "VegaWeightedSmileFit", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorLib =
            ObjectHandler::operToVector<QuantLib::Period>(*OptionTenor, "OptionTenor");

        std::vector<QuantLib::Period> SwapTenorLib =
            ObjectHandler::operToVector<QuantLib::Period>(*SwapTenor, "SwapTenor");

        // convert object IDs into library objects

        OH_GET_OBJECT(AtmVolStructureCoerce, AtmVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> AtmVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    AtmVolStructureCoerce);

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > SpreadVolsLibObj =
            ObjectHandler::operToMatrix<QuantLib::Handle<QuantLib::Quote> >(*SpreadVols, "SpreadVols");

        OH_GET_REFERENCE(SwapIndexBaseLibObjPtr, SwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(ShortSwapIndexBaseLibObjPtr, ShortSwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string AtmVolStructureStrip = ObjectHandler::CallingRange::getStub(AtmVolStructure);
        std::string SwapIndexBaseStrip = ObjectHandler::CallingRange::getStub(SwapIndexBase);
        std::string ShortSwapIndexBaseStrip = ObjectHandler::CallingRange::getStub(ShortSwapIndexBase);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaptionVolCube2(
                ObjectIdStrip,
                AtmVolStructureStrip,
                OptionTenorCpp,
                SwapTenorCpp,
                StrikeSpreadsCpp,
                SpreadVolsCpp,
                SwapIndexBaseStrip,
                ShortSwapIndexBaseStrip,
                VegaWeightedSmileFitCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolCube2(
                valueObject,
                AtmVolStructureLibObj,
                OptionTenorLib,
                SwapTenorLib,
                StrikeSpreadsCpp,
                SpreadVolsLibObj,
                SwapIndexBaseLibObjPtr,
                ShortSwapIndexBaseLibObjPtr,
                VegaWeightedSmileFitCpp,
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
XLL_DEC OPER *qlVolCubeAtmCalibrated(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlVolCubeAtmCalibrated"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SwaptionVolCube1> ObjectIdObjPtr =
            QuantLibAddin::CoerceTermStructureObject<QuantLibAddin::SwaptionVolCube1>()(
                ObjectIdTemp);

        // invoke the member function

        std::vector<std::vector<ObjectHandler::property_t> > returnValue = ObjectIdObjPtr->getVolCubeAtmCalibrated();

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
