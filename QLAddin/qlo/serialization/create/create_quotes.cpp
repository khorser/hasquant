
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

#include <qlo/serialization/create/create_quotes.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/quotes.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/capletvolstructure.hpp>
#include <qlo/conversions/coercequote.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/quotes/derivedquote.hpp>
#include <ql/quotes/eurodollarfuturesquote.hpp>
#include <ql/quotes/forwardvaluequote.hpp>
#include <ql/quotes/futuresconvadjustmentquote.hpp>
#include <ql/quotes/impliedstddevquote.hpp>
#include <ql/indexes/swapindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCompositeQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Element1 =
            valueObject->getProperty("Element1");

        ObjectHandler::property_t Element2 =
            valueObject->getProperty("Element2");

        std::string Operator =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Operator"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> Element1LibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Element1, "Element1");

        QuantLib::Handle<QuantLib::Quote> Element2LibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Element2, "Element2");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Element1);
        valueObject->processVariant(Element2);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CompositeQuote(
                valueObject,
                Element1LibObj,
                Element2LibObj,
                Operator,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEurodollarFuturesImpliedStdDevQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t AtmForwardValue =
            valueObject->getProperty("AtmForwardValue");

        ObjectHandler::property_t CallPrice =
            valueObject->getProperty("CallPrice");

        ObjectHandler::property_t PutPrice =
            valueObject->getProperty("PutPrice");

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        ObjectHandler::property_t Guess =
            valueObject->getProperty("Guess");

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real StrikeLib = Strike;

        QuantLib::Real GuessLib = Guess;

        QuantLib::Real AccuracyLib = Accuracy;

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

        // update value object precedent IDs (if any)

        valueObject->processVariant(AtmForwardValue);
        valueObject->processVariant(CallPrice);
        valueObject->processVariant(PutPrice);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EurodollarFuturesImpliedStdDevQuote(
                valueObject,
                AtmForwardValueLibObj,
                CallPriceLibObj,
                PutPriceLibObj,
                StrikeLib,
                GuessLib,
                AccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardSwapQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SwapIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndex"));

        ObjectHandler::property_t Spread =
            valueObject->getProperty("Spread");

        std::string ForwardStart =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardStart"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SwapIndex);
        valueObject->processVariant(Spread);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardSwapQuote(
                valueObject,
                SwapIndexLibObjPtr,
                SpreadLibObj,
                ForwardStartLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardValueQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        ObjectHandler::property_t FixingDate =
            valueObject->getProperty("FixingDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("FixingDate"), "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardValueQuote(
                valueObject,
                IborIndexLibObjPtr,
                FixingDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFuturesConvAdjustmentQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::string ImmCode =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ImmCode"));

        ObjectHandler::property_t FuturesQuote =
            valueObject->getProperty("FuturesQuote");

        ObjectHandler::property_t Volatility =
            valueObject->getProperty("Volatility");

        ObjectHandler::property_t MeanReversion =
            valueObject->getProperty("MeanReversion");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processVariant(FuturesQuote);
        valueObject->processVariant(Volatility);
        valueObject->processVariant(MeanReversion);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FuturesConvAdjustmentQuote(
                valueObject,
                IborIndexLibObjPtr,
                ImmCode,
                FuturesQuoteLibObj,
                VolatilityLibObj,
                MeanReversionLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlImpliedStdDevQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OptionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionType"));

        ObjectHandler::property_t AtmForwardValue =
            valueObject->getProperty("AtmForwardValue");

        ObjectHandler::property_t OptionPrice =
            valueObject->getProperty("OptionPrice");

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        ObjectHandler::property_t Guess =
            valueObject->getProperty("Guess");

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real StrikeLib = Strike;

        QuantLib::Real GuessLib = Guess;

        QuantLib::Real AccuracyLib = Accuracy;

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

        // update value object precedent IDs (if any)

        valueObject->processVariant(AtmForwardValue);
        valueObject->processVariant(OptionPrice);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ImpliedStdDevQuote(
                valueObject,
                OptionTypeEnum,
                AtmForwardValueLibObj,
                OptionPriceLibObj,
                StrikeLib,
                GuessLib,
                AccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLastFixingQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Index =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Index"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(IndexLibObjPtr, Index,
            QuantLibAddin::Index, QuantLib::Index)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Index);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LastFixingQuote(
                valueObject,
                IndexLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRelinkableHandleQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string CurrentLink =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurrentLink"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(CurrentLink);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::Quote, QuantLib::Quote>(
                valueObject,
                CurrentLink,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSimpleQuote(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Value =
            valueObject->getProperty("Value");

        double TickValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("TickValue"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ValueLib = Value;

        QuantLib::Real TickValueLib = TickValue;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SimpleQuote(
                valueObject,
                ValueLib,
                TickValueLib,
                Permanent));
        return object;
    }

}
