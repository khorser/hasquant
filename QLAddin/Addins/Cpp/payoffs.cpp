
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2007 Marco Bianchetti
 Copyright (C) 2006 Eric Ehlers
 
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
#include <qlo/stickyratchet.hpp>
#include <qlo/valueobjects/vo_payoffs.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlDoubleStickyRatchetPayoff(
            const std::string &ObjectId,
            const double &Type1,
            const double &Type2,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDoubleStickyRatchetPayoff(
                ObjectId,
                Type1,
                Type2,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DoubleStickyRatchetPayoff(
                valueObject,
                Type1,
                Type2,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlDoubleStickyRatchetPayoff : " << e.what());
        }
    }


    std::string qlRatchetMaxPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRatchetMaxPayoff(
                ObjectId,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RatchetMaxPayoff(
                valueObject,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRatchetMaxPayoff : " << e.what());
        }
    }


    std::string qlRatchetMinPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRatchetMinPayoff(
                ObjectId,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RatchetMinPayoff(
                valueObject,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRatchetMinPayoff : " << e.what());
        }
    }


    std::string qlRatchetPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Spread1,
            const double &Spread2,
            const double &InitialValue,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRatchetPayoff(
                ObjectId,
                Gearing1,
                Gearing2,
                Spread1,
                Spread2,
                InitialValue,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RatchetPayoff(
                valueObject,
                Gearing1,
                Gearing2,
                Spread1,
                Spread2,
                InitialValue,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRatchetPayoff : " << e.what());
        }
    }


    std::string qlStickyMaxPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlStickyMaxPayoff(
                ObjectId,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StickyMaxPayoff(
                valueObject,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStickyMaxPayoff : " << e.what());
        }
    }


    std::string qlStickyMinPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Gearing3,
            const double &Spread1,
            const double &Spread2,
            const double &Spread3,
            const double &InitialValue1,
            const double &InitialValue2,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlStickyMinPayoff(
                ObjectId,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StickyMinPayoff(
                valueObject,
                Gearing1,
                Gearing2,
                Gearing3,
                Spread1,
                Spread2,
                Spread3,
                InitialValue1,
                InitialValue2,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStickyMinPayoff : " << e.what());
        }
    }


    std::string qlStickyPayoff(
            const std::string &ObjectId,
            const double &Gearing1,
            const double &Gearing2,
            const double &Spread1,
            const double &Spread2,
            const double &InitialValue,
            const double &AccrualFactor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlStickyPayoff(
                ObjectId,
                Gearing1,
                Gearing2,
                Spread1,
                Spread2,
                InitialValue,
                AccrualFactor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StickyPayoff(
                valueObject,
                Gearing1,
                Gearing2,
                Spread1,
                Spread2,
                InitialValue,
                AccrualFactor,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStickyPayoff : " << e.what());
        }
    }


    std::string qlStrikedTypePayoff(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const std::string &OptionType,
            const double &Strike,
            const ObjectHandler::property_t &ThirdParameter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double ThirdParameterCpp = ObjectHandler::convert2<double>(
            ThirdParameter, "ThirdParameter", QuantLib::Null<QuantLib::Real>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlStrikedTypePayoff(
                ObjectId,
                PayoffID,
                OptionType,
                Strike,
                ThirdParameterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StrikedTypePayoff(
                valueObject,
                PayoffID,
                OptionTypeEnum,
                Strike,
                ThirdParameterCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlStrikedTypePayoff : " << e.what());
        }
    }

}

