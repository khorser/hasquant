
/*  
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Francois du Vignaud
 Copyright (C) 2006 Giorgio Facchinetti
 
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
#include <qlo/quotes.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercequote.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/quotes/derivedquote.hpp>
#include <ql/quotes/eurodollarfuturesquote.hpp>
#include <ql/quotes/forwardvaluequote.hpp>
#include <ql/quotes/futuresconvadjustmentquote.hpp>
#include <ql/quotes/lastfixingquote.hpp>
#include <ql/quotes/impliedstddevquote.hpp>
#include <ql/experimental/risk/sensitivityanalysis.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/capletvolstructure.hpp>
#include <qlo/baseinstruments.hpp>
#include <qlo/valueobjects/vo_quotes.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCompositeQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Element1,
            const ObjectHandler::property_t &Element2,
            const std::string &Operator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> Element1LibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Element1, "Element1");

        QuantLib::Handle<QuantLib::Quote> Element2LibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Element2, "Element2");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCompositeQuote(
                ObjectId,
                Element1,
                Element2,
                Operator,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CompositeQuote(
                valueObject,
                Element1LibObj,
                Element2LibObj,
                Operator,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCompositeQuote : " << e.what());
        }
    }


    std::string qlEurodollarFuturesImpliedStdDevQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &AtmForwardValue,
            const ObjectHandler::property_t &CallPrice,
            const ObjectHandler::property_t &PutPrice,
            const double &Strike,
            const ObjectHandler::property_t &Guess,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double GuessCpp = ObjectHandler::convert2<double>(
            Guess, "Guess", QuantLib::Null<QuantLib::Real>());

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1e-6);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GuessLib = ObjectHandler::convert2<QuantLib::Real>(
            Guess, "Guess", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1e-6);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> AtmForwardValueLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                AtmForwardValue, "AtmForwardValue");

        QuantLib::Handle<QuantLib::Quote> CallPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                CallPrice, "CallPrice");

        QuantLib::Handle<QuantLib::Quote> PutPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                PutPrice, "PutPrice");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEurodollarFuturesImpliedStdDevQuote(
                ObjectId,
                AtmForwardValue,
                CallPrice,
                PutPrice,
                Strike,
                GuessCpp,
                AccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EurodollarFuturesImpliedStdDevQuote(
                valueObject,
                AtmForwardValueLibObj,
                CallPriceLibObj,
                PutPriceLibObj,
                Strike,
                GuessLib,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlEurodollarFuturesImpliedStdDevQuote : " << e.what());
        }
    }


    std::string qlForwardSwapQuote(
            const std::string &ObjectId,
            const std::string &SwapIndex,
            const ObjectHandler::property_t &Spread,
            const std::string &ForwardStart,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardSwapQuote(
                ObjectId,
                SwapIndex,
                Spread,
                ForwardStart,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardSwapQuote(
                valueObject,
                SwapIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlForwardSwapQuote : " << e.what());
        }
    }


    std::string qlForwardValueQuote(
            const std::string &ObjectId,
            const std::string &IborIndex,
            const ObjectHandler::property_t &FixingDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            FixingDate, "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardValueQuote(
                ObjectId,
                IborIndex,
                FixingDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardValueQuote(
                valueObject,
                IborIndexLibObjPtr,
                FixingDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlForwardValueQuote : " << e.what());
        }
    }


    std::string qlFuturesConvAdjustmentQuote(
            const std::string &ObjectId,
            const std::string &IborIndex,
            const std::string &ImmCode,
            const ObjectHandler::property_t &FuturesQuote,
            const ObjectHandler::property_t &Volatility,
            const ObjectHandler::property_t &MeanReversion,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> FuturesQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                FuturesQuote, "FuturesQuote");

        QuantLib::Handle<QuantLib::Quote> VolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Volatility, "Volatility");

        QuantLib::Handle<QuantLib::Quote> MeanReversionLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                MeanReversion, "MeanReversion");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFuturesConvAdjustmentQuote(
                ObjectId,
                IborIndex,
                ImmCode,
                FuturesQuote,
                Volatility,
                MeanReversion,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesConvAdjustmentQuote(
                valueObject,
                IborIndexLibObjPtr,
                ImmCode,
                FuturesQuoteLibObj,
                VolatilityLibObj,
                MeanReversionLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFuturesConvAdjustmentQuote : " << e.what());
        }
    }


    std::string qlImpliedStdDevQuote(
            const std::string &ObjectId,
            const std::string &OptionType,
            const ObjectHandler::property_t &AtmForwardValue,
            const ObjectHandler::property_t &OptionPrice,
            const double &Strike,
            const ObjectHandler::property_t &Guess,
            const ObjectHandler::property_t &Accuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double GuessCpp = ObjectHandler::convert2<double>(
            Guess, "Guess", QuantLib::Null<QuantLib::Real>());

        double AccuracyCpp = ObjectHandler::convert2<double>(
            Accuracy, "Accuracy", 1e-6);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GuessLib = ObjectHandler::convert2<QuantLib::Real>(
            Guess, "Guess", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            Accuracy, "Accuracy", 1e-6);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> AtmForwardValueLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                AtmForwardValue, "AtmForwardValue");

        QuantLib::Handle<QuantLib::Quote> OptionPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                OptionPrice, "OptionPrice");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlImpliedStdDevQuote(
                ObjectId,
                OptionType,
                AtmForwardValue,
                OptionPrice,
                Strike,
                GuessCpp,
                AccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ImpliedStdDevQuote(
                valueObject,
                OptionTypeEnum,
                AtmForwardValueLibObj,
                OptionPriceLibObj,
                Strike,
                GuessLib,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlImpliedStdDevQuote : " << e.what());
        }
    }


    std::string qlLastFixingQuote(
            const std::string &ObjectId,
            const std::string &Index,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IndexLibObjPtr, Index,
            QuantLibAddin::Index, QuantLib::Index)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLastFixingQuote(
                ObjectId,
                Index,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LastFixingQuote(
                valueObject,
                IndexLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlLastFixingQuote : " << e.what());
        }
    }


    std::string qlRelinkableHandleQuote(
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
            new QuantLibAddin::ValueObjects::qlRelinkableHandleQuote(
                ObjectId,
                CurrentLinkCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::Quote, QuantLib::Quote>(
                valueObject,
                CurrentLinkCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRelinkableHandleQuote : " << e.what());
        }
    }


    std::string qlSimpleQuote(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Value,
            const double &TickValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double ValueCpp = ObjectHandler::convert2<double>(
            Value, "Value", QuantLib::Null<QuantLib::Real>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ValueLib = ObjectHandler::convert2<QuantLib::Real>(
            Value, "Value", QuantLib::Null<QuantLib::Real>());

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSimpleQuote(
                ObjectId,
                ValueCpp,
                TickValue,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SimpleQuote(
                valueObject,
                ValueLib,
                TickValue,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSimpleQuote : " << e.what());
        }
    }


    double qlSimpleQuoteSetValue(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Value,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        double ValueCpp = ObjectHandler::convert2<double>(
            Value, "Value", QuantLib::Null<QuantLib::Real>());

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ValueLib = ObjectHandler::convert2<QuantLib::Real>(
            Value, "Value", QuantLib::Null<QuantLib::Real>());

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SimpleQuote> ObjectIdObjPtr =
            QuantLibAddin::CoerceQuoteObject<QuantLibAddin::SimpleQuote>()(
                ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->setValue(
                ValueLib);

        // convert and return the return value

        double returnValueLib = QuantLibAddin::libraryToScalar(returnValue);
        return returnValueLib;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSimpleQuoteSetValue : " << e.what());
        }
    }

}

