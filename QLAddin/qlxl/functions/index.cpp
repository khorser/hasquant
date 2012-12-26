
/*  
 Copyright (C) 2006, 2007, 2008, 2009, 2010 Ferdinando Ametrano
 Copyright (C) 2006 Katiuscia Manzoni
 Copyright (C) 2005, 2007 Eric Ehlers
 Copyright (C) 2005 Plamen Neykov
 
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
#include <qlo/indexes/bmaindex.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/indexes/ibor/libor.hpp>
#include <qlo/indexes/swap/euriborswap.hpp>
#include <qlo/indexes/swap/liborswap.hpp>
#include <qlo/indexes/swap/isdafixaswap.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/timeseries.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/experimental/coupons/proxyibor.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/valueobjects/vo_index.hpp>
#include <qlo/loop/loop_index.hpp>
#include <ohxl/loop.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlBMAIndex(
        char *ObjectId,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBMAIndex"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBMAIndex(
                ObjectIdStrip,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BMAIndex(
                valueObject,
                YieldCurveLibObj,
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
XLL_DEC char *qlEonia(
        char *ObjectId,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlEonia"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEonia(
                ObjectIdStrip,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Eonia(
                valueObject,
                YieldCurveLibObj,
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
XLL_DEC char *qlEuribor(
        char *ObjectId,
        char *Tenor,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlEuribor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuribor(
                ObjectIdStrip,
                Tenor,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Euribor(
                valueObject,
                Tenor,
                YieldCurveLibObj,
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
XLL_DEC char *qlEuribor365(
        char *ObjectId,
        char *Tenor,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlEuribor365"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuribor365(
                ObjectIdStrip,
                Tenor,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Euribor365(
                valueObject,
                Tenor,
                YieldCurveLibObj,
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
XLL_DEC char *qlEuriborSwap(
        char *ObjectId,
        OPER *FixingType,
        char *Tenor,
        OPER *FwdCurve,
        OPER *DiscCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlEuriborSwap"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FixingTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FixingType), "FixingType", "Default");

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FwdCurve), "FwdCurve", "");

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DiscCurve), "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLibAddin::SwapIndex::FixingType FixingTypeEnum =
            ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType>()(FixingTypeCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string FwdCurveStrip = ObjectHandler::CallingRange::getStub(FwdCurveCpp);
        std::string DiscCurveStrip = ObjectHandler::CallingRange::getStub(DiscCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuriborSwap(
                ObjectIdStrip,
                FixingTypeCpp,
                Tenor,
                FwdCurveCpp,
                DiscCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuriborSwap(
                valueObject,
                FixingTypeEnum,
                TenorLib,
                FwdCurveLibObj,
                DiscCurveLibObj,
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
XLL_DEC char *qlEuriborSwapIsdaFixA(
        char *ObjectId,
        char *Tenor,
        OPER *FwdCurve,
        OPER *DiscCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlEuriborSwapIsdaFixA"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FwdCurve), "FwdCurve", "");

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DiscCurve), "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string FwdCurveStrip = ObjectHandler::CallingRange::getStub(FwdCurveCpp);
        std::string DiscCurveStrip = ObjectHandler::CallingRange::getStub(DiscCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuriborSwapIsdaFixA(
                ObjectIdStrip,
                Tenor,
                FwdCurveCpp,
                DiscCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuriborSwapIsdaFixA(
                valueObject,
                TenorLib,
                FwdCurveLibObj,
                DiscCurveLibObj,
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
XLL_DEC char *qlIborIndex(
        char *ObjectId,
        char *FamilyName,
        char *Tenor,
        long *FixingDays,
        char *Currency,
        char *Calendar,
        char *BDayConvention,
        bool *EndOfMonth,
        char *DayCounter,
        OPER *FwdCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIborIndex"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FwdCurve), "FwdCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(*FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string FwdCurveStrip = ObjectHandler::CallingRange::getStub(FwdCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIborIndex(
                ObjectIdStrip,
                FamilyName,
                Tenor,
                *FixingDays,
                Currency,
                Calendar,
                BDayConvention,
                *EndOfMonth,
                DayCounter,
                FwdCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IborIndex(
                valueObject,
                FamilyName,
                TenorLib,
                FixingDaysLib,
                CurrencyEnum,
                CalendarEnum,
                BDayConventionEnum,
                *EndOfMonth,
                DayCounterEnum,
                FwdCurveLibObj,
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
XLL_DEC char *qlIborIndexBusinessDayConv(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIborIndexBusinessDayConv"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

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
XLL_DEC short int *qlIborIndexEndOfMonth(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIborIndexEndOfMonth"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // invoke the member function

        static short int returnValue;
        returnValue = ObjectIdLibObjPtr->endOfMonth();

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
XLL_DEC bool *qlIndexAddFixings(
        char *ObjectId,
        OPER *FixingDates,
        OPER *FixingValues,
        OPER *ForceOverwrite,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexAddFixings"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> FixingDatesCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*FixingDates, "FixingDates");

        std::vector<double> FixingValuesCpp =
            ObjectHandler::operToVector<double>(*FixingValues, "FixingValues");

        bool ForceOverwriteCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*ForceOverwrite), "ForceOverwrite", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> FixingDatesLib =
            ObjectHandler::operToVector<QuantLib::Date>(*FixingDates, "FixingDates");

        std::vector<QuantLib::Real> FixingValuesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*FixingValues, "FixingValues");

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Index)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->addFixings(
                FixingDatesLib,
                FixingValuesLib,
                ForceOverwriteCpp);

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
XLL_DEC OPER *qlIndexAddFixings2(
        char *ObjectId,
        OPER *TimeSeriesID,
        OPER *ForceOverwrite,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexAddFixings2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool ForceOverwriteCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*ForceOverwrite), "ForceOverwrite", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Index, QuantLib::Index)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIndexAddFixings2Bind bindObject = 
            boost::bind((QuantLibAddin::qlIndexAddFixings2Signature)
                &QuantLib::Index::addFixings,
                ObjectIdLibObjPtr,
                _1,
                ForceOverwriteCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlIndexAddFixings2Bind, QuantLib::TimeSeriesDef, void>
            (functionCall, bindObject, TimeSeriesID, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC bool *qlIndexClearFixings(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexClearFixings"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Index, QuantLib::Index)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->clearFixings();

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
XLL_DEC OPER *qlIndexFixing(
        char *ObjectId,
        OPER *FixingDate,
        OPER *ForecastToday,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexFixing"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool ForecastTodayCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*ForecastToday), "ForecastToday", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> FixingDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*FixingDate, "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Index, QuantLib::Index)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIndexFixingBind bindObject = 
            boost::bind((QuantLibAddin::qlIndexFixingSignature)
                &QuantLib::Index::fixing,
                ObjectIdLibObjPtr,
                _1,
                ForecastTodayCpp);
        ObjectHandler::loop
            <QuantLibAddin::qlIndexFixingBind, QuantLib::Date, QuantLib::Real>
            (functionCall, bindObject, FixingDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlIndexFixingCalendar(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexFixingCalendar"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Index, QuantLib::Index)

        // invoke the member function

        QuantLib::Calendar returnValue = ObjectIdLibObjPtr->fixingCalendar();

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
XLL_DEC OPER *qlIndexIsValidFixingDate(
        char *ObjectId,
        OPER *FixingDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexIsValidFixingDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> FixingDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*FixingDate, "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Index, QuantLib::Index)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlIndexIsValidFixingDateBind bindObject = 
            boost::bind((QuantLibAddin::qlIndexIsValidFixingDateSignature)
                &QuantLib::Index::isValidFixingDate,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlIndexIsValidFixingDateBind, QuantLib::Date, bool>
            (functionCall, bindObject, FixingDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlIndexName(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlIndexName"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::Index, QuantLib::Index)

        // invoke the member function

        std::string returnValue = ObjectIdLibObjPtr->name();

        // convert and return the return value

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
XLL_DEC char *qlInterestRateIndexCurrency(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexCurrency"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // invoke the member function

        QuantLib::Currency returnValue = ObjectIdLibObjPtr->currency();

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
XLL_DEC char *qlInterestRateIndexDayCounter(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexDayCounter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // invoke the member function

        QuantLib::DayCounter returnValue = ObjectIdLibObjPtr->dayCounter();

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
XLL_DEC char *qlInterestRateIndexFamilyName(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexFamilyName"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // invoke the member function

        std::string returnValue = ObjectIdLibObjPtr->familyName();

        // convert and return the return value

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
XLL_DEC OPER *qlInterestRateIndexFixingDate(
        char *ObjectId,
        OPER *ValueDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexFixingDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> ValueDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*ValueDate, "ValueDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterestRateIndexFixingDateBind bindObject = 
            boost::bind((QuantLibAddin::qlInterestRateIndexFixingDateSignature)
                &QuantLib::InterestRateIndex::fixingDate,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlInterestRateIndexFixingDateBind, QuantLib::Date, QuantLib::Date>
            (functionCall, bindObject, ValueDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlInterestRateIndexFixingDays(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexFixingDays"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // invoke the member function

        QuantLib::Natural returnValue = ObjectIdLibObjPtr->fixingDays();

        // convert and return the return value

        static long returnValueXL;
        returnValueXL = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return &returnValueXL;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlInterestRateIndexMaturity(
        char *ObjectId,
        OPER *ValueDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexMaturity"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> ValueDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*ValueDate, "ValueDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterestRateIndexMaturityBind bindObject = 
            boost::bind((QuantLibAddin::qlInterestRateIndexMaturitySignature)
                &QuantLib::InterestRateIndex::maturityDate,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlInterestRateIndexMaturityBind, QuantLib::Date, QuantLib::Date>
            (functionCall, bindObject, ValueDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlInterestRateIndexTenor(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexTenor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // invoke the member function

        QuantLib::Period returnValue = ObjectIdLibObjPtr->tenor();

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
XLL_DEC OPER *qlInterestRateIndexValueDate(
        char *ObjectId,
        OPER *FixingDate,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterestRateIndexValueDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> FixingDateLib =
            ObjectHandler::operToVector<QuantLib::Date>(*FixingDate, "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        // loop on the input parameter and populate the return vector

        static XLOPER returnValue;

        QuantLibAddin::qlInterestRateIndexValueDateBind bindObject = 
            boost::bind((QuantLibAddin::qlInterestRateIndexValueDateSignature)
                &QuantLib::InterestRateIndex::valueDate,
                ObjectIdLibObjPtr,
                _1);
        ObjectHandler::loop
            <QuantLibAddin::qlInterestRateIndexValueDateBind, QuantLib::Date, QuantLib::Date>
            (functionCall, bindObject, FixingDate, returnValue);

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlLibor(
        char *ObjectId,
        char *Currency,
        char *Tenor,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLibor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLibor(
                ObjectIdStrip,
                Currency,
                Tenor,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Libor(
                valueObject,
                CurrencyEnum,
                Tenor,
                YieldCurveLibObj,
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
XLL_DEC char *qlLiborSwap(
        char *ObjectId,
        char *Currency,
        OPER *FixingType,
        char *Tenor,
        OPER *FwdCurve,
        OPER *DiscCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLiborSwap"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string FixingTypeCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FixingType), "FixingType", "Default");

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*FwdCurve), "FwdCurve", "");

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DiscCurve), "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLibAddin::SwapIndex::FixingType FixingTypeEnum =
            ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType>()(FixingTypeCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string FwdCurveStrip = ObjectHandler::CallingRange::getStub(FwdCurveCpp);
        std::string DiscCurveStrip = ObjectHandler::CallingRange::getStub(DiscCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLiborSwap(
                ObjectIdStrip,
                Currency,
                FixingTypeCpp,
                Tenor,
                FwdCurveCpp,
                DiscCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LiborSwap(
                valueObject,
                CurrencyEnum,
                FixingTypeEnum,
                TenorLib,
                FwdCurveLibObj,
                DiscCurveLibObj,
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
XLL_DEC char *qlOvernightIndex(
        char *ObjectId,
        char *FamilyName,
        long *FixingDays,
        char *Currency,
        char *Calendar,
        char *DayCounter,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlOvernightIndex"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(*FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOvernightIndex(
                ObjectIdStrip,
                FamilyName,
                *FixingDays,
                Currency,
                Calendar,
                DayCounter,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndex(
                valueObject,
                FamilyName,
                FixingDaysLib,
                CurrencyEnum,
                CalendarEnum,
                DayCounterEnum,
                YieldCurveLibObj,
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
XLL_DEC char *qlProxyIbor(
        char *ObjectId,
        char *FamilyName,
        char *Tenor,
        long *FixingDays,
        char *Currency,
        char *Calendar,
        char *BDayConvention,
        bool *EndOfMonth,
        char *DayCounter,
        OPER *Gearing,
        char *IborIndex,
        OPER *Spread,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlProxyIbor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t GearingCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Gearing));

        ObjectHandler::property_t SpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Spread));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(*FixingDays, FixingDaysLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> GearingLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Gearing), "Gearing");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Spread), "Spread");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlProxyIbor(
                ObjectIdStrip,
                FamilyName,
                Tenor,
                *FixingDays,
                Currency,
                Calendar,
                BDayConvention,
                *EndOfMonth,
                DayCounter,
                GearingCpp,
                IborIndexStrip,
                SpreadCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ProxyIbor(
                valueObject,
                FamilyName,
                TenorLib,
                FixingDaysLib,
                CurrencyEnum,
                CalendarEnum,
                BDayConventionEnum,
                *EndOfMonth,
                DayCounterEnum,
                GearingLibObj,
                IborIndexLibObjPtr,
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
XLL_DEC char *qlSonia(
        char *ObjectId,
        OPER *YieldCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSonia"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*YieldCurve), "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string YieldCurveStrip = ObjectHandler::CallingRange::getStub(YieldCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSonia(
                ObjectIdStrip,
                YieldCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Sonia(
                valueObject,
                YieldCurveLibObj,
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
XLL_DEC char *qlSwapIndex(
        char *ObjectId,
        char *FamilyName,
        char *Tenor,
        long *FixingDays,
        char *Currency,
        char *Calendar,
        char *FixedLegTenor,
        char *FixedLegBDC,
        char *FixedLegDayCounter,
        char *IborIndex,
        OPER *DiscCurve,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapIndex"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DiscCurve), "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(*FixingDays, FixingDaysLib);

        QuantLib::Period FixedLegTenorLib;
        QuantLibAddin::cppToLibrary(FixedLegTenor, FixedLegTenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention FixedLegBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(FixedLegBDC);

        QuantLib::DayCounter FixedLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixedLegDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);
        std::string DiscCurveStrip = ObjectHandler::CallingRange::getStub(DiscCurveCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwapIndex(
                ObjectIdStrip,
                FamilyName,
                Tenor,
                *FixingDays,
                Currency,
                Calendar,
                FixedLegTenor,
                FixedLegBDC,
                FixedLegDayCounter,
                IborIndexStrip,
                DiscCurveCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapIndex(
                valueObject,
                FamilyName,
                TenorLib,
                FixingDaysLib,
                CurrencyEnum,
                CalendarEnum,
                FixedLegTenorLib,
                FixedLegBDCEnum,
                FixedLegDayCounterEnum,
                IborIndexLibObjPtr,
                DiscCurveLibObj,
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
XLL_DEC char *qlSwapIndexFixedLegBDC(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapIndexFixedLegBDC"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // invoke the member function

        QuantLib::BusinessDayConvention returnValue = ObjectIdLibObjPtr->fixedLegConvention();

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
XLL_DEC char *qlSwapIndexFixedLegTenor(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSwapIndexFixedLegTenor"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // invoke the member function

        QuantLib::Period returnValue = ObjectIdLibObjPtr->fixedLegTenor();

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
