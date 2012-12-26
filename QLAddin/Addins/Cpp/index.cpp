
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
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
#include <Addins/Cpp/loop.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlBMAIndex(
            const std::string &ObjectId,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBMAIndex(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBMAIndex : " << e.what());
        }
    }


    std::string qlEonia(
            const std::string &ObjectId,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEonia(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEonia : " << e.what());
        }
    }


    std::string qlEuribor(
            const std::string &ObjectId,
            const std::string &Tenor,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuribor(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEuribor : " << e.what());
        }
    }


    std::string qlEuribor365(
            const std::string &ObjectId,
            const std::string &Tenor,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuribor365(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEuribor365 : " << e.what());
        }
    }


    std::string qlEuriborSwap(
            const std::string &ObjectId,
            const ObjectHandler::property_t &FixingType,
            const std::string &Tenor,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string FixingTypeCpp = ObjectHandler::convert2<std::string>(
            FixingType, "FixingType", "Default");

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            FwdCurve, "FwdCurve", "");

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            DiscCurve, "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuriborSwap(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEuriborSwap : " << e.what());
        }
    }


    std::string qlEuriborSwapIsdaFixA(
            const std::string &ObjectId,
            const std::string &Tenor,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            FwdCurve, "FwdCurve", "");

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            DiscCurve, "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEuriborSwapIsdaFixA(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEuriborSwapIsdaFixA : " << e.what());
        }
    }


    std::string qlIborIndex(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &BDayConvention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            FwdCurve, "FwdCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(FixingDays, FixingDaysLib);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlIborIndex(
                ObjectId,
                FamilyName,
                Tenor,
                FixingDays,
                Currency,
                Calendar,
                BDayConvention,
                EndOfMonth,
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
                EndOfMonth,
                DayCounterEnum,
                FwdCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlIborIndex : " << e.what());
        }
    }


    bool qlIndexAddFixings(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& FixingDates,
            const std::vector<double>& FixingValues,
            const ObjectHandler::property_t &ForceOverwrite,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        bool ForceOverwriteCpp = ObjectHandler::convert2<bool>(
            ForceOverwrite, "ForceOverwrite", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> FixingDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(FixingDates, "FixingDates");

        std::vector<QuantLib::Real> FixingValuesLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(FixingValues);

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Index)

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->addFixings(
                FixingDatesLib,
                FixingValuesLib,
                ForceOverwriteCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlIndexAddFixings : " << e.what());
        }
    }


    std::string qlLibor(
            const std::string &ObjectId,
            const std::string &Currency,
            const std::string &Tenor,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLibor(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLibor : " << e.what());
        }
    }


    std::string qlLiborSwap(
            const std::string &ObjectId,
            const std::string &Currency,
            const ObjectHandler::property_t &FixingType,
            const std::string &Tenor,
            const ObjectHandler::property_t &FwdCurve,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string FixingTypeCpp = ObjectHandler::convert2<std::string>(
            FixingType, "FixingType", "Default");

        std::string FwdCurveCpp = ObjectHandler::convert2<std::string>(
            FwdCurve, "FwdCurve", "");

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            DiscCurve, "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLiborSwap(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLiborSwap : " << e.what());
        }
    }


    std::string qlOvernightIndex(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &DayCounter,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(FixingDays, FixingDaysLib);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlOvernightIndex(
                ObjectId,
                FamilyName,
                FixingDays,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlOvernightIndex : " << e.what());
        }
    }


    std::string qlProxyIbor(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &BDayConvention,
            const bool &EndOfMonth,
            const std::string &DayCounter,
            const ObjectHandler::property_t &Gearing,
            const std::string &IborIndex,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(FixingDays, FixingDaysLib);

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
                Gearing, "Gearing");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlProxyIbor(
                ObjectId,
                FamilyName,
                Tenor,
                FixingDays,
                Currency,
                Calendar,
                BDayConvention,
                EndOfMonth,
                DayCounter,
                Gearing,
                IborIndex,
                Spread,
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
                EndOfMonth,
                DayCounterEnum,
                GearingLibObj,
                IborIndexLibObjPtr,
                SpreadLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlProxyIbor : " << e.what());
        }
    }


    std::string qlSonia(
            const std::string &ObjectId,
            const ObjectHandler::property_t &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string YieldCurveCpp = ObjectHandler::convert2<std::string>(
            YieldCurve, "YieldCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurveCpp, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSonia(
                ObjectId,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSonia : " << e.what());
        }
    }


    std::string qlSwapIndex(
            const std::string &ObjectId,
            const std::string &FamilyName,
            const std::string &Tenor,
            const long &FixingDays,
            const std::string &Currency,
            const std::string &Calendar,
            const std::string &FixedLegTenor,
            const std::string &FixedLegBDC,
            const std::string &FixedLegDayCounter,
            const std::string &IborIndex,
            const ObjectHandler::property_t &DiscCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DiscCurveCpp = ObjectHandler::convert2<std::string>(
            DiscCurve, "DiscCurve", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Natural FixingDaysLib;
        QuantLibAddin::cppToLibrary(FixingDays, FixingDaysLib);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwapIndex(
                ObjectId,
                FamilyName,
                Tenor,
                FixingDays,
                Currency,
                Calendar,
                FixedLegTenor,
                FixedLegBDC,
                FixedLegDayCounter,
                IborIndex,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSwapIndex : " << e.what());
        }
    }

}

