
/*  
 Copyright (C) 2007 Cristina Duminuco
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Francois du Vignaud
 
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
#include <qlo/smilesection.hpp>
#include <qlo/optimization.hpp>
#include <qlo/volatilities.hpp>
#include <ql/termstructures/volatility/interpolatedsmilesection.hpp>
#include <ql/termstructures/volatility/sabrinterpolatedsmilesection.hpp>
#include <ql/experimental/volatility/sabrvolsurface.hpp>
#include <ql/quote.hpp>
#include <qlo/valueobjects/vo_smilesection.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC char *qlFlatSmileSection(
        char *ObjectId,
        OPER *OptionDate,
        double *Volatility,
        OPER *DayCounter,
        OPER *RefDate,
        double *AtmValue,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlFlatSmileSection"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        ObjectHandler::property_t RefDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*RefDate));

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*RefDate), "RefDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatSmileSection(
                ObjectIdStrip,
                OptionDateCpp,
                *Volatility,
                DayCounterCpp,
                RefDateCpp,
                *AtmValue,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatSmileSection(
                valueObject,
                OptionDateLib,
                *Volatility,
                DayCounterEnum,
                RefDateLib,
                *AtmValue,
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
XLL_DEC char *qlInterpolatedSmileSection(
        char *ObjectId,
        OPER *OptionDate,
        OPER *Strikes,
        OPER *StdDevs,
        OPER *AtmLevel,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlInterpolatedSmileSection"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        std::vector<double> StrikesCpp =
            ObjectHandler::operToVector<double>(*Strikes, "Strikes");

        std::vector<ObjectHandler::property_t> StdDevsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*StdDevs, "StdDevs");

        ObjectHandler::property_t AtmLevelCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*AtmLevel));

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > StdDevsLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*StdDevs, "StdDevs");

        QuantLib::Handle<QuantLib::Quote> AtmLevelLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*AtmLevel), "AtmLevel");

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolatedSmileSection(
                ObjectIdStrip,
                OptionDateCpp,
                StrikesCpp,
                StdDevsCpp,
                AtmLevelCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                StrikesCpp,
                StdDevsLibObj,
                AtmLevelLibObj,
                DayCounterEnum,
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
XLL_DEC char *qlSabrInterpolatedSmileSection(
        char *ObjectId,
        OPER *OptionDate,
        double *ForwardRate,
        OPER *Strike,
        bool *FloatingStrike,
        double *AtmVolatility,
        OPER *VolatilitySpreads,
        OPER *Alpha,
        OPER *Beta,
        OPER *Nu,
        OPER *Rho,
        OPER *AlphaIsFixed,
        OPER *BetaIsFixed,
        OPER *NuIsFixed,
        OPER *RhoIsFixed,
        OPER *VegaWeighted,
        OPER *EndCriteria,
        OPER *Method,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSection"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        std::vector<double> StrikeCpp =
            ObjectHandler::operToVector<double>(*Strike, "Strike");

        std::vector<double> VolatilitySpreadsCpp =
            ObjectHandler::operToVector<double>(*VolatilitySpreads, "VolatilitySpreads");

        double AlphaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Alpha), "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Beta), "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Nu), "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Rho), "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AlphaIsFixed), "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*BetaIsFixed), "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*NuIsFixed), "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*RhoIsFixed), "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeighted), "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Method), "Method", "");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string MethodStrip = ObjectHandler::CallingRange::getStub(MethodCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrInterpolatedSmileSection(
                ObjectIdStrip,
                OptionDateCpp,
                *ForwardRate,
                StrikeCpp,
                *FloatingStrike,
                *AtmVolatility,
                VolatilitySpreadsCpp,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                MethodCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrInterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                *ForwardRate,
                StrikeCpp,
                *FloatingStrike,
                *AtmVolatility,
                VolatilitySpreadsCpp,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
                DayCounterEnum,
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
XLL_DEC char *qlSabrInterpolatedSmileSection1(
        char *ObjectId,
        OPER *OptionDate,
        OPER *ForwardRate,
        OPER *Strike,
        bool *FloatingStrike,
        OPER *AtmVolatility,
        OPER *VolatilitySpreads,
        OPER *Alpha,
        OPER *Beta,
        OPER *Nu,
        OPER *Rho,
        OPER *AlphaIsFixed,
        OPER *BetaIsFixed,
        OPER *NuIsFixed,
        OPER *RhoIsFixed,
        OPER *VegaWeighted,
        OPER *EndCriteria,
        OPER *Method,
        OPER *DayCounter,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSection1"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*OptionDate));

        ObjectHandler::property_t ForwardRateCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*ForwardRate));

        std::vector<double> StrikeCpp =
            ObjectHandler::operToVector<double>(*Strike, "Strike");

        ObjectHandler::property_t AtmVolatilityCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*AtmVolatility));

        std::vector<ObjectHandler::property_t> VolatilitySpreadsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*VolatilitySpreads, "VolatilitySpreads");

        double AlphaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Alpha), "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Beta), "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Nu), "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Rho), "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AlphaIsFixed), "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*BetaIsFixed), "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*NuIsFixed), "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*RhoIsFixed), "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeighted), "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Method), "Method", "");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*DayCounter), "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            ObjectHandler::ConvertOper(*OptionDate), "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> ForwardRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*ForwardRate), "ForwardRate");

        QuantLib::Handle<QuantLib::Quote> AtmVolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*AtmVolatility), "AtmVolatility");

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitySpreadsLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*VolatilitySpreads, "VolatilitySpreads");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string MethodStrip = ObjectHandler::CallingRange::getStub(MethodCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrInterpolatedSmileSection1(
                ObjectIdStrip,
                OptionDateCpp,
                ForwardRateCpp,
                StrikeCpp,
                *FloatingStrike,
                AtmVolatilityCpp,
                VolatilitySpreadsCpp,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                MethodCpp,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrInterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                ForwardRateLibObj,
                StrikeCpp,
                *FloatingStrike,
                AtmVolatilityLibObj,
                VolatilitySpreadsLibObj,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
                DayCounterEnum,
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
XLL_DEC double *qlSabrInterpolatedSmileSectionAlpha(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionAlpha"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->alpha();

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
XLL_DEC double *qlSabrInterpolatedSmileSectionBeta(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionBeta"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->beta();

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
XLL_DEC char *qlSabrInterpolatedSmileSectionEndCriteria(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionEndCriteria"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        QuantLib::EndCriteria::Type returnValue = ObjectIdLibObjPtr->endCriteria();

        // convert and return the return value

        std::ostringstream os;
        os << returnValue;
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(os.str(), ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlSabrInterpolatedSmileSectionError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->rmsError();

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
XLL_DEC double *qlSabrInterpolatedSmileSectionMaxError(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionMaxError"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->maxError();

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
XLL_DEC double *qlSabrInterpolatedSmileSectionNu(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionNu"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->nu();

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
XLL_DEC double *qlSabrInterpolatedSmileSectionRho(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrInterpolatedSmileSectionRho"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SabrInterpolatedSmileSection, QuantLib::SabrInterpolatedSmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->rho();

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
XLL_DEC char *qlSabrSmileSection(
        char *ObjectId,
        double *OptionTime,
        OPER *Strikes,
        OPER *StdDevs,
        OPER *Forward,
        OPER *Alpha,
        OPER *Beta,
        OPER *Nu,
        OPER *Rho,
        OPER *AlphaIsFixed,
        OPER *BetaIsFixed,
        OPER *NuIsFixed,
        OPER *RhoIsFixed,
        OPER *VegaWeighted,
        OPER *EndCriteria,
        OPER *Method,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSabrSmileSection"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> StrikesCpp =
            ObjectHandler::operToVector<double>(*Strikes, "Strikes");

        std::vector<ObjectHandler::property_t> StdDevsCpp =
            ObjectHandler::operToVector<ObjectHandler::property_t>(*StdDevs, "StdDevs");

        ObjectHandler::property_t ForwardCpp = ObjectHandler::convert2<ObjectHandler::property_t>(
            ObjectHandler::ConvertOper(*Forward));

        double AlphaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Alpha), "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Beta), "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Nu), "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Rho), "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*AlphaIsFixed), "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*BetaIsFixed), "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*NuIsFixed), "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*RhoIsFixed), "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*VegaWeighted), "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*EndCriteria), "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            ObjectHandler::ConvertOper(*Method), "Method", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > StdDevsLibObj =
            ObjectHandler::operToVector<QuantLib::Handle<QuantLib::Quote> >(*StdDevs, "StdDevs");

        QuantLib::Handle<QuantLib::Quote> ForwardLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ObjectHandler::ConvertOper(*Forward), "Forward");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string EndCriteriaStrip = ObjectHandler::CallingRange::getStub(EndCriteriaCpp);
        std::string MethodStrip = ObjectHandler::CallingRange::getStub(MethodCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrSmileSection(
                ObjectIdStrip,
                *OptionTime,
                StrikesCpp,
                StdDevsCpp,
                ForwardCpp,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaCpp,
                MethodCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrSmileSection(
                valueObject,
                *OptionTime,
                StrikesCpp,
                StdDevsLibObj,
                ForwardLibObj,
                AlphaCpp,
                BetaCpp,
                NuCpp,
                RhoCpp,
                AlphaIsFixedCpp,
                BetaIsFixedCpp,
                NuIsFixedCpp,
                RhoIsFixedCpp,
                VegaWeightedCpp,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
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
XLL_DEC double *qlSmileSectionAtmLevel(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionAtmLevel"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->atmLevel();

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
XLL_DEC char *qlSmileSectionDayCounter(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionDayCounter"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // invoke the member function

        QuantLib::DayCounter returnValue = ObjectIdLibObjPtr->dayCounter();

        // convert and return the return value

        std::ostringstream os;
        os << returnValue;
        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(os.str(), ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlSmileSectionExerciseDate(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionExerciseDate"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // invoke the member function

        QuantLib::Date returnValue = ObjectIdLibObjPtr->exerciseDate();

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
XLL_DEC char *qlSmileSectionFromSabrVolSurface(
        char *ObjectId,
        char *SabrVolSurface,
        double *OptionTime,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionFromSabrVolSurface"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(SabrVolSurfaceCoerce, SabrVolSurface, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SabrVolSurface> SabrVolSurfaceLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SabrVolSurface,
                QuantLib::SabrVolSurface>()(
                    SabrVolSurfaceCoerce);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);
        std::string SabrVolSurfaceStrip = ObjectHandler::CallingRange::getStub(SabrVolSurface);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSmileSectionFromSabrVolSurface(
                ObjectIdStrip,
                SabrVolSurfaceStrip,
                *OptionTime,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionFromSabrVolSurface(
                valueObject,
                SabrVolSurfaceLibObj,
                *OptionTime,
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
XLL_DEC double *qlSmileSectionVariance(
        char *ObjectId,
        OPER *Strike,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionVariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double StrikeCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Strike), "Strike", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->variance(
                StrikeCpp);

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
XLL_DEC double *qlSmileSectionVolatility(
        char *ObjectId,
        OPER *Strike,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSmileSectionVolatility"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double StrikeCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Strike), "Strike", QuantLib::Null<QuantLib::Real>());

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SmileSection, QuantLib::SmileSection)

        // invoke the member function

        static double returnValue;
        returnValue = ObjectIdLibObjPtr->volatility(
                StrikeCpp);

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
