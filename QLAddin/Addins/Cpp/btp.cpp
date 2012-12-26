
/*  
 Copyright (C) 2010, 2011 Ferdinando Ametrano
 
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
#include <qlo/btp.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/termstructures.hpp>
#include <ql/instruments/bonds/btp.hpp>
#include <qlo/valueobjects/vo_btp.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlBTP(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &MaturityDate,
            const double &Coupon,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            MaturityDate, "MaturityDate");

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBTP(
                ObjectId,
                DescriptionCpp,
                MaturityDate,
                Coupon,
                StartDate,
                IssueDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BTP(
                valueObject,
                DescriptionCpp,
                MaturityDateLib,
                Coupon,
                StartDateLib,
                IssueDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBTP : " << e.what());
        }
    }


    std::string qlBTP2(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &MaturityDate,
            const double &Coupon,
            const ObjectHandler::property_t &Redemption,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        double RedemptionCpp = ObjectHandler::convert2<double>(
            Redemption, "Redemption", 100.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            MaturityDate, "MaturityDate");

        QuantLib::Real RedemptionLib = ObjectHandler::convert2<QuantLib::Real>(
            Redemption, "Redemption", 100.0);

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBTP2(
                ObjectId,
                DescriptionCpp,
                MaturityDate,
                Coupon,
                RedemptionCpp,
                StartDate,
                IssueDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BTP(
                valueObject,
                DescriptionCpp,
                MaturityDateLib,
                Coupon,
                RedemptionLib,
                StartDateLib,
                IssueDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBTP2 : " << e.what());
        }
    }


    std::string qlCCTEU(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Description,
            const ObjectHandler::property_t &MaturityDate,
            const double &Spread,
            const std::string &FwdCurve,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &IssueDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DescriptionCpp = ObjectHandler::convert2<std::string>(
            Description, "Description", std::string());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            MaturityDate, "MaturityDate");

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            IssueDate, "IssueDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_OBJECT(FwdCurveCoerce, FwdCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCCTEU(
                ObjectId,
                DescriptionCpp,
                MaturityDate,
                Spread,
                FwdCurve,
                StartDate,
                IssueDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CCTEU(
                valueObject,
                DescriptionCpp,
                MaturityDateLib,
                Spread,
                FwdCurveLibObj,
                StartDateLib,
                IssueDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCCTEU : " << e.what());
        }
    }


    std::string qlRendistatoBasket(
            const std::string &ObjectId,
            const std::vector<std::string>& BTPs,
            const std::vector<double>& Outstandings,
            const std::vector<ObjectHandler::property_t>& Prices,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> OutstandingsLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Outstandings);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::BTP> > BTPsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::BTP, QuantLib::BTP>(BTPs);

        std::vector<QuantLib::Handle<QuantLib::Quote> > PricesLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Prices, "Prices");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRendistatoBasket(
                ObjectId,
                BTPs,
                Outstandings,
                Prices,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoBasket(
                valueObject,
                BTPsLibObjPtr,
                OutstandingsLib,
                PricesLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRendistatoBasket : " << e.what());
        }
    }


    std::string qlRendistatoCalculator(
            const std::string &ObjectId,
            const std::string &RendistatoBasket,
            const std::string &Euribor,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(RendistatoBasketLibObjPtr, RendistatoBasket,
            QuantLibAddin::RendistatoBasket, QuantLib::RendistatoBasket)

        OH_GET_REFERENCE(EuriborLibObjPtr, Euribor,
            QuantLibAddin::Euribor, QuantLib::Euribor)

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRendistatoCalculator(
                ObjectId,
                RendistatoBasket,
                Euribor,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoCalculator(
                valueObject,
                RendistatoBasketLibObjPtr,
                EuriborLibObjPtr,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRendistatoCalculator : " << e.what());
        }
    }


    std::string qlRendistatoEquivalentSwapLengthQuote(
            const std::string &ObjectId,
            const std::string &RendistatoCalculator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(RendistatoCalculatorLibObjPtr, RendistatoCalculator,
            QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRendistatoEquivalentSwapLengthQuote(
                ObjectId,
                RendistatoCalculator,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoEquivalentSwapLengthQuote(
                valueObject,
                RendistatoCalculatorLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRendistatoEquivalentSwapLengthQuote : " << e.what());
        }
    }


    std::string qlRendistatoEquivalentSwapSpreadQuote(
            const std::string &ObjectId,
            const std::string &RendistatoCalculator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(RendistatoCalculatorLibObjPtr, RendistatoCalculator,
            QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRendistatoEquivalentSwapSpreadQuote(
                ObjectId,
                RendistatoCalculator,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoEquivalentSwapSpreadQuote(
                valueObject,
                RendistatoCalculatorLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRendistatoEquivalentSwapSpreadQuote : " << e.what());
        }
    }

}

