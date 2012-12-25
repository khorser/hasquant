
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

#include <qlo/serialization/create/create_products.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/products.hpp>
#include <qlo/payoffs.hpp>
#include <ql/models/marketmodels/products/onestep/onestepforwards.hpp>
#include <ql/models/marketmodels/products/onestep/onestepoptionlets.hpp>
#include <ql/models/marketmodels/products/multistep/multistepratchet.hpp>
#include <ql/models/marketmodels/products/multiproductcomposite.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlMarketModelMultiProductComposite(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiProductComposite(
                valueObject,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMarketModelMultiStepRatchet(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RateTimes"), "RateTimes");

        std::vector<double> Accruals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Accruals"), "Accruals");

        std::vector<double> PaymentTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PaymentTimes"), "PaymentTimes");

        double GearingOfFloor =
            ObjectHandler::convert2<double>(valueObject->getProperty("GearingOfFloor"));

        double GearingOfFixing =
            ObjectHandler::convert2<double>(valueObject->getProperty("GearingOfFixing"));

        double SpreadOfFloor =
            ObjectHandler::convert2<double>(valueObject->getProperty("SpreadOfFloor"));

        double SpreadOfFixing =
            ObjectHandler::convert2<double>(valueObject->getProperty("SpreadOfFixing"));

        double InitialFloor =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialFloor"));

        bool Payer =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Payer"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GearingOfFloorLib = GearingOfFloor;

        QuantLib::Real GearingOfFixingLib = GearingOfFixing;

        QuantLib::Real SpreadOfFloorLib = SpreadOfFloor;

        QuantLib::Real SpreadOfFixingLib = SpreadOfFixing;

        QuantLib::Real InitialFloorLib = InitialFloor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MultiStepRatchet(
                valueObject,
                RateTimes,
                Accruals,
                PaymentTimes,
                GearingOfFloorLib,
                GearingOfFixingLib,
                SpreadOfFloorLib,
                SpreadOfFixingLib,
                InitialFloorLib,
                Payer,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMarketModelOneStepForwards(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RateTimes"), "RateTimes");

        std::vector<double> Accruals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Accruals"), "Accruals");

        std::vector<double> PaymentTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PaymentTimes"), "PaymentTimes");

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OneStepForwards(
                valueObject,
                RateTimes,
                Accruals,
                PaymentTimes,
                Strikes,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMarketModelOneStepOptionlets(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RateTimes"), "RateTimes");

        std::vector<double> Accruals =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Accruals"), "Accruals");

        std::vector<double> PaymentTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("PaymentTimes"), "PaymentTimes");

        std::vector<std::string> Payoffs =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("Payoffs"), "Payoffs");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::Payoff> > PayoffsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::Payoff, QuantLib::Payoff>(Payoffs);

        // update value object precedent IDs (if any)

        for (std::vector<std::string>::const_iterator i = Payoffs.begin();
                i != Payoffs.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OneStepOptionlets(
                valueObject,
                RateTimes,
                Accruals,
                PaymentTimes,
                PayoffsLibObjPtr,
                Permanent));
        return object;
    }

}
