
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 
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
#include <qlo/indexes/iborindex.hpp>
#include <qlo/capletvolstructure.hpp>
#include <qlo/quote.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/handleimpl.hpp>
#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper1.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper2.hpp>
#include <ql/termstructures/volatility/capfloor/capfloortermvolcurve.hpp>
#include <ql/termstructures/volatility/capfloor/capfloortermvolsurface.hpp>
#include <ql/indexes/iborindex.hpp>
#include <qlo/valueobjects/vo_capletvolstructure.hpp>
#include <qlo/loop/loop_capletvolstructure.hpp>
#include <Addins/Cpp/loop.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCapFloorTermVolCurve(
            const std::string &ObjectId,
            const long &SettlementDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& Volatilities,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitiesLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCapFloorTermVolCurve(
                ObjectId,
                SettlementDays,
                Calendar,
                BusinessDayConvention,
                OptionTenors,
                Volatilities,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CapFloorTermVolCurve(
                valueObject,
                SettlementDaysLib,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                VolatilitiesLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCapFloorTermVolCurve : " << e.what());
        }
    }


    std::string qlCapFloorTermVolSurface(
            const std::string &ObjectId,
            const long &SettlementDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<double>& Strikes,
            const std::vector<std::vector <ObjectHandler::property_t> >& Volatilities,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib;
        QuantLibAddin::cppToLibrary(SettlementDays, SettlementDaysLib);

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCapFloorTermVolSurface(
                ObjectId,
                SettlementDays,
                Calendar,
                BusinessDayConvention,
                OptionTenors,
                Strikes,
                Volatilities,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CapFloorTermVolSurface(
                valueObject,
                SettlementDaysLib,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                Strikes,
                VolatilitiesLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCapFloorTermVolSurface : " << e.what());
        }
    }


    std::string qlConstantOptionletVolatility(
            const std::string &ObjectId,
            const ObjectHandler::property_t &NDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const ObjectHandler::property_t &Volatility,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long NDaysCpp = ObjectHandler::convert2<long>(
            NDays, "NDays", 0);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            NDays, "NDays", 0);

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
                Volatility, "Volatility");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlConstantOptionletVolatility(
                ObjectId,
                NDaysCpp,
                Calendar,
                BusinessDayConvention,
                Volatility,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ConstantOptionletVolatility(
                valueObject,
                NDaysLib,
                CalendarEnum,
                BusinessDayConventionEnum,
                VolatilityLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlConstantOptionletVolatility : " << e.what());
        }
    }


    std::string qlRelinkableHandleOptionletVolatilityStructure(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string CurrentLinkCpp = ObjectHandler::convert2<std::string>(
            CurrentLink, "CurrentLink", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRelinkableHandleOptionletVolatilityStructure(
                ObjectId,
                CurrentLinkCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure>(
                valueObject,
                CurrentLinkCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRelinkableHandleOptionletVolatilityStructure : " << e.what());
        }
    }


    std::string qlSpreadedOptionletVolatility(
            const std::string &ObjectId,
            const std::string &BaseVolStructure,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseVolStructureCoerce, BaseVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> BaseVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    BaseVolStructureCoerce);

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSpreadedOptionletVolatility(
                ObjectId,
                BaseVolStructure,
                Spread,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadedOptionletVolatility(
                valueObject,
                BaseVolStructureLibObj,
                SpreadLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSpreadedOptionletVolatility : " << e.what());
        }
    }


    std::string qlStrippedOptionlet(
            const std::string &ObjectId,
            const ObjectHandler::property_t &SettlementDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::string &IborIndex,
            const std::vector<ObjectHandler::property_t>& OptionletDates,
            const std::vector<double>& Strikes,
            const std::vector<std::vector <ObjectHandler::property_t> >& Volatilities,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long SettlementDaysCpp = ObjectHandler::convert2<long>(
            SettlementDays, "SettlementDays", 0);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SettlementDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            SettlementDays, "SettlementDays", 0);

        std::vector<QuantLib::Date> OptionletDatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(OptionletDates, "OptionletDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlStrippedOptionlet(
                ObjectId,
                SettlementDaysCpp,
                Calendar,
                BusinessDayConvention,
                IborIndex,
                OptionletDates,
                Strikes,
                Volatilities,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StrippedOptionlet(
                valueObject,
                SettlementDaysLib,
                CalendarEnum,
                BusinessDayConventionEnum,
                IborIndexLibObjPtr,
                OptionletDatesLib,
                Strikes,
                VolatilitiesLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStrippedOptionlet : " << e.what());
        }
    }


    std::string qlStrippedOptionletAdapter(
            const std::string &ObjectId,
            const std::string &StrippedOptionletBase,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(StrippedOptionletBaseLibObjPtr, StrippedOptionletBase,
            QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlStrippedOptionletAdapter(
                ObjectId,
                StrippedOptionletBase,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StrippedOptionletAdapter(
                valueObject,
                StrippedOptionletBaseLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStrippedOptionletAdapter : " << e.what());
        }
    }


    long qlStrippedOptionletBaseSettlementDays(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

        // invoke the member function

        QuantLib::Natural returnValue = ObjectIdLibObjPtr->settlementDays();

        // convert and return the return value

        long returnValueLib = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return returnValueLib;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStrippedOptionletBaseSettlementDays : " << e.what());
        }
    }

}

