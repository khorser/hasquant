
/*  
 Copyright (C) 2006, 2007, 2009, 2010, 2011 Ferdinando Ametrano
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti
 Copyright (C) 2005 Aurelien Chanudet
 
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
#include <qlo/couponvectors.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/capfloor.hpp>
#include <qlo/swap.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/instruments/swap.hpp>
#include <qlo/valueobjects/vo_leg.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlInterestRate(
            const std::string &ObjectId,
            const double &Rate,
            const std::string &DayCounter,
            const std::string &Compounding,
            const ObjectHandler::property_t &Frequency,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string FrequencyCpp = ObjectHandler::convert2<std::string>(
            Frequency, "Frequency", "Annual");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        QuantLib::Compounding CompoundingEnum =
            ObjectHandler::Create<QuantLib::Compounding>()(Compounding);

        QuantLib::Frequency FrequencyEnum =
            ObjectHandler::Create<QuantLib::Frequency>()(FrequencyCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterestRate(
                ObjectId,
                Rate,
                DayCounter,
                Compounding,
                FrequencyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterestRate(
                valueObject,
                Rate,
                DayCounterEnum,
                CompoundingEnum,
                FrequencyEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInterestRate : " << e.what());
        }
    }


    std::string qlLeg(
            const std::string &ObjectId,
            const std::vector<double>& Amounts,
            const std::vector<ObjectHandler::property_t>& Dates,
            const ObjectHandler::property_t &ToBeSorted,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool ToBeSortedCpp = ObjectHandler::convert2<bool>(
            ToBeSorted, "ToBeSorted", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DatesLib = 
            ObjectHandler::vector::convert2<QuantLib::Date>(Dates, "Dates");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLeg(
                ObjectId,
                Amounts,
                Dates,
                ToBeSortedCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                Amounts,
                DatesLib,
                ToBeSortedCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLeg : " << e.what());
        }
    }


    std::string qlLegFromCapFloor(
            const std::string &ObjectId,
            const std::string &CapFloor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CapFloorLibObjPtr, CapFloor,
            QuantLibAddin::CapFloor, QuantLib::CapFloor)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLegFromCapFloor(
                ObjectId,
                CapFloor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                CapFloorLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLegFromCapFloor : " << e.what());
        }
    }


    std::string qlLegFromSwap(
            const std::string &ObjectId,
            const std::string &Swap,
            const long &LegNumber,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapLibObjPtr, Swap,
            QuantLibAddin::Swap, QuantLib::Swap)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLegFromSwap(
                ObjectId,
                Swap,
                LegNumber,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Leg(
                valueObject,
                SwapLibObjPtr,
                LegNumber,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLegFromSwap : " << e.what());
        }
    }


    bool qlLegSetCouponPricers(
            const std::string &ObjectId,
            const std::vector<std::string>& FloatingRateCouponPricer,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdObjPtr, ObjectId, QuantLibAddin::Leg)

        std::vector<boost::shared_ptr<QuantLibAddin::FloatingRateCouponPricer> > FloatingRateCouponPricerObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::FloatingRateCouponPricer>(FloatingRateCouponPricer);

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->setCouponPricers(
                FloatingRateCouponPricerObjPtr);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLegSetCouponPricers : " << e.what());
        }
    }


    std::string qlMultiPhaseLeg(
            const std::string &ObjectId,
            const std::vector<std::string>& LegIDs,
            const ObjectHandler::property_t &ToBeSorted,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool ToBeSortedCpp = ObjectHandler::convert2<bool>(
            ToBeSorted, "ToBeSorted", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<QuantLibAddin::Leg> > LegIDsObjPtr =
            ObjectHandler::getObjectVector<QuantLibAddin::Leg>(LegIDs);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMultiPhaseLeg(
                ObjectId,
                LegIDs,
                ToBeSortedCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiPhaseLeg(
                valueObject,
                LegIDsObjPtr,
                ToBeSortedCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMultiPhaseLeg : " << e.what());
        }
    }

}

