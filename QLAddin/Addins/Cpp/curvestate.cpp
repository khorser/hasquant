
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
#include <ql/models/marketmodels/swapforwardmappings.hpp>
#include <ql/models/marketmodels/curvestates/cmswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/coterminalswapcurvestate.hpp>
#include <ql/models/marketmodels/curvestates/lmmcurvestate.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/valueobjects/vo_curvestate.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCMSwapCurveState(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const long &SpanningForwards,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size SpanningForwardsLib;
        QuantLibAddin::cppToLibrary(SpanningForwards, SpanningForwardsLib);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCMSwapCurveState(
                ObjectId,
                RateTimes,
                SpanningForwards,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CMSwapCurveState(
                valueObject,
                RateTimes,
                SpanningForwardsLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCMSwapCurveState : " << e.what());
        }
    }


    std::string qlCoterminalSwapCurveState(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCoterminalSwapCurveState(
                ObjectId,
                RateTimes,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CoterminalSwapCurveState(
                valueObject,
                RateTimes,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCoterminalSwapCurveState : " << e.what());
        }
    }


    std::string qlLMMCurveState(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLMMCurveState(
                ObjectId,
                RateTimes,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LMMCurveState(
                valueObject,
                RateTimes,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLMMCurveState : " << e.what());
        }
    }

}

