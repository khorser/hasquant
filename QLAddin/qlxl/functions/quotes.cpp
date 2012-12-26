
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
//      QuantLibAddin/gensrc/stubs/stub.excel.includes

#include <qlo/qladdindefines.hpp>
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

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC OPER *qlBucketAnalysis(
        OPER *SimpleQuote,
        OPER *Instruments,
        OPER *Quantities,
        OPER *Shift,
        OPER *SensitivityAnalysis,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBucketAnalysis"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<ObjectHandler::property_t> > SimpleQuoteCpp =
            ObjectHandler::operToMatrix<ObjectHandler::property_t>(*SimpleQuote, "SimpleQuote");

        std::vector<std::string> InstrumentsCpp =
            ObjectHandler::operToVector<std::string>(*Instruments, "Instruments");

        std::vector<double> QuantitiesCpp =
            ObjectHandler::operToVector<double>(*Quantities, "Quantities");

        double ShiftCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Shift), "Shift", 0.0001);

        std::string SensitivityAnalysisCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*SensitivityAnalysis), "SensitivityAnalysis", "Centered");

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> QuantitiesLib =
            ObjectHandler::operToVector<QuantLib::Real>(*Quantities, "Quantities");

        QuantLib::Real ShiftLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Shift), "Shift", 0.0001);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::SensitivityAnalysis SensitivityAnalysisEnum =
            ObjectHandler::Create<QuantLib::SensitivityAnalysis>()(SensitivityAnalysisCpp);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > SimpleQuoteLibObj =
            ObjectHandler::operToMatrix<QuantLib::Handle<QuantLib::Quote> >(*SimpleQuote, "SimpleQuote");

        std::vector<boost::shared_ptr<QuantLib::Instrument> > InstrumentsLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::Instrument, QuantLib::Instrument>(InstrumentsCpp);

        // invoke the utility function

        std::vector<std::vector<QuantLib::Real> > returnValue = QuantLibAddin::bucketAnalysis(
                SimpleQuoteLibObj,
                InstrumentsLibObjPtr,
                QuantitiesLib,
                ShiftLib,
                SensitivityAnalysisEnum);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlBucketAnalysisDelta(
        char *SimpleQuote,
        OPER *Parameters,
        OPER *Shift,
        OPER *SensitivityAnalysis,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBucketAnalysisDelta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> ParametersCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*Parameters, "Parameters");

        double ShiftCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Shift), "Shift", 0.0001);

        std::string SensitivityAnalysisCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*SensitivityAnalysis), "SensitivityAnalysis", "Centered");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ShiftLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Shift), "Shift", 0.0001);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::SensitivityAnalysis SensitivityAnalysisEnum =
            ObjectHandler::Create<QuantLib::SensitivityAnalysis>()(SensitivityAnalysisCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(SimpleQuoteCoerce, SimpleQuote, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SimpleQuote> SimpleQuoteLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SimpleQuote,
                QuantLib::SimpleQuote>()(
                    SimpleQuoteCoerce);

        std::vector<QuantLib::Handle<QuantLib::Quote> > ParametersLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*Parameters, "Parameters");

        // invoke the utility function

        std::vector<QuantLib::Real> returnValue = QuantLibAddin::bucketAnalysisDelta(
                SimpleQuoteLibObj,
                ParametersLibObj,
                ShiftLib,
                SensitivityAnalysisEnum);

        // convert and return the return value

        std::vector<double> returnValVec = QuantLibAddin::libraryToVector(returnValue);
        static OPER xRet;
        ObjectHandler::vectorToOper(returnValVec, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlBucketAnalysisDelta2(
        OPER *SimpleQuote,
        OPER *Parameters,
        OPER *Shift,
        OPER *SensitivityAnalysis,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlBucketAnalysisDelta2"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<ObjectHandler::property_t> SimpleQuoteCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*SimpleQuote, "SimpleQuote");

        std::vector<ObjectHandler::property_t> ParametersCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*Parameters, "Parameters");

        double ShiftCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Shift), "Shift", 0.0001);

        std::string SensitivityAnalysisCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*SensitivityAnalysis), "SensitivityAnalysis", "Centered");

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ShiftLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Shift), "Shift", 0.0001);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::SensitivityAnalysis SensitivityAnalysisEnum =
            ObjectHandler::Create<QuantLib::SensitivityAnalysis>()(SensitivityAnalysisCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > SimpleQuoteLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*SimpleQuote, "SimpleQuote");

        std::vector<QuantLib::Handle<QuantLib::Quote> > ParametersLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*Parameters, "Parameters");

        // invoke the utility function

        std::vector<std::vector<QuantLib::Real> > returnValue = QuantLibAddin::bucketAnalysisDelta2(
                SimpleQuoteLibObj,
                ParametersLibObj,
                ShiftLib,
                SensitivityAnalysisEnum);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlCompositeQuote(
        char *ObjectId,
        OPER *Element1,
        OPER *Element2,
        char *Operator,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCompositeQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t Element1Cpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Element1));

        ObjectHandler::property_t Element2Cpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Element2));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> Element1LibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Element1), "Element1");

        QuantLib::Handle<QuantLib::Quote> Element2LibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Element2), "Element2");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCompositeQuote(
                ObjectIdStrip,
                Element1Cpp,
                Element2Cpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlEurodollarFuturesImpliedStdDevQuote(
        char *ObjectId,
        OPER *AtmForwardValue,
        OPER *CallPrice,
        OPER *PutPrice,
        double *Strike,
        OPER *Guess,
        OPER *Accuracy,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlEurodollarFuturesImpliedStdDevQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t AtmForwardValueCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*AtmForwardValue));

        ObjectHandler::property_t CallPriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*CallPrice));

        ObjectHandler::property_t PutPriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*PutPrice));

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1e-6);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GuessLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1e-6);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> AtmForwardValueLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*AtmForwardValue), "AtmForwardValue");

        QuantLib::Handle<QuantLib::Quote> CallPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*CallPrice), "CallPrice");

        QuantLib::Handle<QuantLib::Quote> PutPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*PutPrice), "PutPrice");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlEurodollarFuturesImpliedStdDevQuote(
                ObjectIdStrip,
                AtmForwardValueCpp,
                CallPriceCpp,
                PutPriceCpp,
                *Strike,
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
                *Strike,
                GuessLib,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlForwardSwapQuote(
        char *ObjectId,
        char *SwapIndex,
        OPER *Spread,
        char *ForwardStart,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardSwapQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SpreadCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Spread));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period ForwardStartLib;
        QuantLibAddin::cppToLibrary(ForwardStart, ForwardStartLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SwapIndexLibObjPtr, SwapIndex,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Spread), "Spread");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SwapIndexStrip = ObjectHandler::CallingRange::getStub(SwapIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardSwapQuote(
                ObjectIdStrip,
                SwapIndexStrip,
                SpreadCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlForwardValueQuote(
        char *ObjectId,
        char *IborIndex,
        OPER *FixingDate,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlForwardValueQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t FixingDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*FixingDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date FixingDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*FixingDate), "FixingDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlForwardValueQuote(
                ObjectIdStrip,
                IborIndexStrip,
                FixingDateCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlFuturesConvAdjustmentQuote(
        char *ObjectId,
        char *IborIndex,
        char *ImmCode,
        OPER *FuturesQuote,
        OPER *Volatility,
        OPER *MeanReversion,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesConvAdjustmentQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t FuturesQuoteCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*FuturesQuote));

        ObjectHandler::property_t VolatilityCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Volatility));

        ObjectHandler::property_t MeanReversionCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*MeanReversion));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> FuturesQuoteLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*FuturesQuote), "FuturesQuote");

        QuantLib::Handle<QuantLib::Quote> VolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Volatility), "Volatility");

        QuantLib::Handle<QuantLib::Quote> MeanReversionLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*MeanReversion), "MeanReversion");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IborIndexStrip = ObjectHandler::CallingRange::getStub(IborIndex);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFuturesConvAdjustmentQuote(
                ObjectIdStrip,
                IborIndexStrip,
                ImmCode,
                FuturesQuoteCpp,
                VolatilityCpp,
                MeanReversionCpp,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlFuturesConvAdjustmentQuoteFuturesValue(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesConvAdjustmentQuoteFuturesValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::FuturesConvAdjustmentQuote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::FuturesConvAdjustmentQuote,
                QuantLib::FuturesConvAdjustmentQuote>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->futuresValue();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlFuturesConvAdjustmentQuoteImmDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesConvAdjustmentQuoteImmDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::FuturesConvAdjustmentQuote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::FuturesConvAdjustmentQuote,
                QuantLib::FuturesConvAdjustmentQuote>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->immDate();

        // convert and return the return value

        static long returnValueXL;
        returnValueXL = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return &returnValueXL;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlFuturesConvAdjustmentQuoteMeanReversion(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesConvAdjustmentQuoteMeanReversion"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::FuturesConvAdjustmentQuote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::FuturesConvAdjustmentQuote,
                QuantLib::FuturesConvAdjustmentQuote>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->meanReversion();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlFuturesConvAdjustmentQuoteVolatility(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFuturesConvAdjustmentQuoteVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::FuturesConvAdjustmentQuote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::FuturesConvAdjustmentQuote,
                QuantLib::FuturesConvAdjustmentQuote>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->volatility();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlImpliedStdDevQuote(
        char *ObjectId,
        char *OptionType,
        OPER *AtmForwardValue,
        OPER *OptionPrice,
        double *Strike,
        OPER *Guess,
        OPER *Accuracy,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlImpliedStdDevQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t AtmForwardValueCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*AtmForwardValue));

        ObjectHandler::property_t OptionPriceCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionPrice));

        double GuessCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        double AccuracyCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1e-6);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real GuessLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Guess), "Guess", QuantLib::Null<QuantLib::Real>());

        QuantLib::Real AccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Accuracy), "Accuracy", 1e-6);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> AtmForwardValueLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*AtmForwardValue), "AtmForwardValue");

        QuantLib::Handle<QuantLib::Quote> OptionPriceLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*OptionPrice), "OptionPrice");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlImpliedStdDevQuote(
                ObjectIdStrip,
                OptionType,
                AtmForwardValueCpp,
                OptionPriceCpp,
                *Strike,
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
                *Strike,
                GuessLib,
                AccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlLastFixingQuote(
        char *ObjectId,
        char *Index,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLastFixingQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IndexLibObjPtr, Index,
            QuantLibAddin::Index, QuantLib::Index)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string IndexStrip = ObjectHandler::CallingRange::getStub(Index);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlLastFixingQuote(
                ObjectIdStrip,
                IndexStrip,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LastFixingQuote(
                valueObject,
                IndexLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlLastFixingQuoteReferenceDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlLastFixingQuoteReferenceDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::LastFixingQuote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::LastFixingQuote,
                QuantLib::LastFixingQuote>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->referenceDate();

        // convert and return the return value

        static long returnValueXL;
        returnValueXL = static_cast<long>(QuantLibAddin::libraryToScalar(returnValue));
        return &returnValueXL;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC short int *qlQuoteIsValid(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlQuoteIsValid"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::Quote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::Quote,
                QuantLib::Quote>()(
                    ObjectIdTemp);

        // invoke the member function

        static short int returnValue;
        returnValue = ObjectIdLibObjPtr->isValid();

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlQuoteValue(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlQuoteValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::Quote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::Quote,
                QuantLib::Quote>()(
                    ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdLibObjPtr->value();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlRelinkableHandleQuote(
        char *ObjectId,
        OPER *CurrentLink,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRelinkableHandleQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::string CurrentLinkCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*CurrentLink), "CurrentLink", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRelinkableHandleQuote(
                ObjectIdStrip,
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
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSimpleQuote(
        char *ObjectId,
        OPER *Value,
        double *TickValue,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSimpleQuote"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double ValueCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Value), "Value", QuantLib::Null<QuantLib::Real>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ValueLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Value), "Value", QuantLib::Null<QuantLib::Real>());

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSimpleQuote(
                ObjectIdStrip,
                ValueCpp,
                *TickValue,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SimpleQuote(
                valueObject,
                ValueLib,
                *TickValue,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC bool *qlSimpleQuoteReset(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSimpleQuoteReset"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SimpleQuote> ObjectIdLibObjPtr =
            QuantLibAddin::CoerceQuote<
                QuantLibAddin::SimpleQuote,
                QuantLib::SimpleQuote>()(
                    ObjectIdTemp);

        // invoke the member function

        static bool returnValue = true;
        ObjectIdLibObjPtr->reset();

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC bool *qlSimpleQuoteSetTickValue(
        char *ObjectId,
        double *Value,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSimpleQuoteSetTickValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SimpleQuote> ObjectIdObjPtr =
            QuantLibAddin::CoerceQuoteObject<QuantLibAddin::SimpleQuote>()(
                ObjectIdTemp);

        // invoke the member function

        static bool returnValue = true;
        ObjectIdObjPtr->setTickValue(
                *Value);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSimpleQuoteSetValue(
        char *ObjectId,
        OPER *Value,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSimpleQuoteSetValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double ValueCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Value), "Value", QuantLib::Null<QuantLib::Real>());

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real ValueLib = ObjectHandler::convert2<QuantLib::Real>(
            ObjectHandler::ConvertOper(*Value), "Value", QuantLib::Null<QuantLib::Real>(), QuantLib::Null<QuantLib::Real>());

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SimpleQuote> ObjectIdObjPtr =
            QuantLibAddin::CoerceQuoteObject<QuantLibAddin::SimpleQuote>()(
                ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->setValue(
                ValueLib);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSimpleQuoteTickValue(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSimpleQuoteTickValue"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to Object references

        OH_GET_OBJECT(ObjectIdTemp, ObjectId, ObjectHandler::Object)
        boost::shared_ptr<QuantLibAddin::SimpleQuote> ObjectIdObjPtr =
            QuantLibAddin::CoerceQuoteObject<QuantLibAddin::SimpleQuote>()(
                ObjectIdTemp);

        // invoke the member function

        QuantLib::Real returnValue = ObjectIdObjPtr->tickValue();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::scalarToOper2(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
