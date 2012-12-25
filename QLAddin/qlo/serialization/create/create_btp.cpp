
/*  
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov
 
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
//      QuantLibAddin/gensrc/stubs/stub.serialization.includes

#include <qlo/serialization/create/create_btp.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/btp.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/termstructures.hpp>
#include <ql/instruments/bonds/btp.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBTP(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        ObjectHandler::property_t MaturityDate =
            valueObject->getProperty("MaturityDate");

        double Coupon =
            ObjectHandler::convert2<double>(valueObject->getProperty("Coupon"));

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("MaturityDate"), "MaturityDate");

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BTP(
                valueObject,
                Description,
                MaturityDateLib,
                Coupon,
                StartDateLib,
                IssueDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBTP2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        ObjectHandler::property_t MaturityDate =
            valueObject->getProperty("MaturityDate");

        double Coupon =
            ObjectHandler::convert2<double>(valueObject->getProperty("Coupon"));

        ObjectHandler::property_t Redemption =
            valueObject->getProperty("Redemption");

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("MaturityDate"), "MaturityDate");

        QuantLib::Real RedemptionLib = Redemption;

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BTP(
                valueObject,
                Description,
                MaturityDateLib,
                Coupon,
                RedemptionLib,
                StartDateLib,
                IssueDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCCTEU(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Description =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Description"));

        ObjectHandler::property_t MaturityDate =
            valueObject->getProperty("MaturityDate");

        double Spread =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread"));

        std::string FwdCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FwdCurve"));

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t IssueDate =
            valueObject->getProperty("IssueDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date MaturityDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("MaturityDate"), "MaturityDate");

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate", QuantLib::Date());

        QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("IssueDate"), "IssueDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_OBJECT(FwdCurveCoerce, FwdCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FwdCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CCTEU(
                valueObject,
                Description,
                MaturityDateLib,
                Spread,
                FwdCurveLibObj,
                StartDateLib,
                IssueDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRendistatoBasket(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::string> BTPs =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("BTPs"), "BTPs");

        std::vector<double> Outstandings =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Outstandings"), "Outstandings");

        std::vector<ObjectHandler::property_t> Prices =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Prices"), "Prices");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> OutstandingsLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Outstandings);

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::BTP> > BTPsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::BTP, QuantLib::BTP>(BTPs);

        std::vector<QuantLib::Handle<QuantLib::Quote> > PricesLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Prices, "Prices");

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = BTPs.begin();
                i != BTPs.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processVariant(Prices);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoBasket(
                valueObject,
                BTPsLibObjPtr,
                OutstandingsLib,
                PricesLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRendistatoCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string RendistatoBasket =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("RendistatoBasket"));

        std::string Euribor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Euribor"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(RendistatoBasket);
        valueObject->processPrecedentID(Euribor);
        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoCalculator(
                valueObject,
                RendistatoBasketLibObjPtr,
                EuriborLibObjPtr,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRendistatoEquivalentSwapLengthQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string RendistatoCalculator =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("RendistatoCalculator"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(RendistatoCalculatorLibObjPtr, RendistatoCalculator,
            QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(RendistatoCalculator);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoEquivalentSwapLengthQuote(
                valueObject,
                RendistatoCalculatorLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRendistatoEquivalentSwapSpreadQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string RendistatoCalculator =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("RendistatoCalculator"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(RendistatoCalculatorLibObjPtr, RendistatoCalculator,
            QuantLibAddin::RendistatoCalculator, QuantLib::RendistatoCalculator)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(RendistatoCalculator);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RendistatoEquivalentSwapSpreadQuote(
                valueObject,
                RendistatoCalculatorLibObjPtr,
                Permanent));
        return object;
    }

}
