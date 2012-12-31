
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/products.hpp>
#include <qlo/payoffs.hpp>
#include <ql/models/marketmodels/products/onestep/onestepforwards.hpp>
#include <ql/models/marketmodels/products/onestep/onestepoptionlets.hpp>
#include <ql/models/marketmodels/products/multistep/multistepratchet.hpp>
#include <ql/models/marketmodels/products/multiproductcomposite.hpp>
#include <qlo/valueobjects/vo_products.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlMarketModelMultiProductComposite(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelMultiProductComposite(
                ObjectId,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiProductComposite(
                valueObject,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMarketModelMultiProductComposite : " << e.what());
        }
    }


    std::string qlMarketModelMultiStepRatchet(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const double &GearingOfFloor,
            const double &GearingOfFixing,
            const double &SpreadOfFloor,
            const double &SpreadOfFixing,
            const double &InitialFloor,
            const bool &Payer,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelMultiStepRatchet(
                ObjectId,
                RateTimes,
                Accruals,
                PaymentTimes,
                GearingOfFloor,
                GearingOfFixing,
                SpreadOfFloor,
                SpreadOfFixing,
                InitialFloor,
                Payer,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiStepRatchet(
                valueObject,
                RateTimes,
                Accruals,
                PaymentTimes,
                GearingOfFloor,
                GearingOfFixing,
                SpreadOfFloor,
                SpreadOfFixing,
                InitialFloor,
                Payer,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMarketModelMultiStepRatchet : " << e.what());
        }
    }


    std::string qlMarketModelOneStepForwards(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<double>& Strikes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelOneStepForwards(
                ObjectId,
                RateTimes,
                Accruals,
                PaymentTimes,
                Strikes,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OneStepForwards(
                valueObject,
                RateTimes,
                Accruals,
                PaymentTimes,
                Strikes,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMarketModelOneStepForwards : " << e.what());
        }
    }


    std::string qlMarketModelOneStepOptionlets(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const std::vector<double>& Accruals,
            const std::vector<double>& PaymentTimes,
            const std::vector<std::string>& Payoffs,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::Payoff> > PayoffsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::Payoff, QuantLib::Payoff>(Payoffs);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelOneStepOptionlets(
                ObjectId,
                RateTimes,
                Accruals,
                PaymentTimes,
                Payoffs,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OneStepOptionlets(
                valueObject,
                RateTimes,
                Accruals,
                PaymentTimes,
                PayoffsLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMarketModelOneStepOptionlets : " << e.what());
        }
    }

}

