
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/smilesection.hpp>
#include <qlo/optimization.hpp>
#include <qlo/volatilities.hpp>
#include <ql/termstructures/volatility/interpolatedsmilesection.hpp>
#include <ql/termstructures/volatility/sabrinterpolatedsmilesection.hpp>
#include <ql/experimental/volatility/sabrvolsurface.hpp>
#include <ql/quote.hpp>
#include <qlo/valueobjects/vo_smilesection.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlFlatSmileSection(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const double &Volatility,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &RefDate,
            const double &AtmValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            OptionDate, "OptionDate");

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            RefDate, "RefDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatSmileSection(
                ObjectId,
                OptionDate,
                Volatility,
                DayCounterCpp,
                RefDate,
                AtmValue,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatSmileSection(
                valueObject,
                OptionDateLib,
                Volatility,
                DayCounterEnum,
                RefDateLib,
                AtmValue,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFlatSmileSection : " << e.what());
        }
    }


    std::string qlInterpolatedSmileSection(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t &AtmLevel,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            OptionDate, "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > StdDevsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(StdDevs, "StdDevs");

        QuantLib::Handle<QuantLib::Quote> AtmLevelLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                AtmLevel, "AtmLevel");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlInterpolatedSmileSection(
                ObjectId,
                OptionDate,
                Strikes,
                StdDevs,
                AtmLevel,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                Strikes,
                StdDevsLibObj,
                AtmLevelLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlInterpolatedSmileSection : " << e.what());
        }
    }


    std::string qlSabrInterpolatedSmileSection(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const double &ForwardRate,
            const std::vector<double>& Strike,
            const bool &FloatingStrike,
            const double &AtmVolatility,
            const std::vector<double>& VolatilitySpreads,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double AlphaCpp = ObjectHandler::convert2<double>(
            Alpha, "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            Beta, "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            Nu, "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            Rho, "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            AlphaIsFixed, "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            BetaIsFixed, "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            NuIsFixed, "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            RhoIsFixed, "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            VegaWeighted, "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            Method, "Method", "");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            OptionDate, "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrInterpolatedSmileSection(
                ObjectId,
                OptionDate,
                ForwardRate,
                Strike,
                FloatingStrike,
                AtmVolatility,
                VolatilitySpreads,
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
                ForwardRate,
                Strike,
                FloatingStrike,
                AtmVolatility,
                VolatilitySpreads,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSabrInterpolatedSmileSection : " << e.what());
        }
    }


    std::string qlSabrInterpolatedSmileSection1(
            const std::string &ObjectId,
            const ObjectHandler::property_t &OptionDate,
            const ObjectHandler::property_t &ForwardRate,
            const std::vector<double>& Strike,
            const bool &FloatingStrike,
            const ObjectHandler::property_t &AtmVolatility,
            const std::vector<ObjectHandler::property_t>& VolatilitySpreads,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double AlphaCpp = ObjectHandler::convert2<double>(
            Alpha, "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            Beta, "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            Nu, "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            Rho, "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            AlphaIsFixed, "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            BetaIsFixed, "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            NuIsFixed, "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            RhoIsFixed, "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            VegaWeighted, "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            Method, "Method", "");

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            OptionDate, "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> ForwardRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ForwardRate, "ForwardRate");

        QuantLib::Handle<QuantLib::Quote> AtmVolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                AtmVolatility, "AtmVolatility");

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitySpreadsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(VolatilitySpreads, "VolatilitySpreads");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrInterpolatedSmileSection1(
                ObjectId,
                OptionDate,
                ForwardRate,
                Strike,
                FloatingStrike,
                AtmVolatility,
                VolatilitySpreads,
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
                Strike,
                FloatingStrike,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSabrInterpolatedSmileSection1 : " << e.what());
        }
    }


    std::string qlSabrSmileSection(
            const std::string &ObjectId,
            const double &OptionTime,
            const std::vector<double>& Strikes,
            const std::vector<ObjectHandler::property_t>& StdDevs,
            const ObjectHandler::property_t &Forward,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &Method,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double AlphaCpp = ObjectHandler::convert2<double>(
            Alpha, "Alpha", QuantLib::Null<QuantLib::Real>());

        double BetaCpp = ObjectHandler::convert2<double>(
            Beta, "Beta", QuantLib::Null<QuantLib::Real>());

        double NuCpp = ObjectHandler::convert2<double>(
            Nu, "Nu", QuantLib::Null<QuantLib::Real>());

        double RhoCpp = ObjectHandler::convert2<double>(
            Rho, "Rho", QuantLib::Null<QuantLib::Real>());

        bool AlphaIsFixedCpp = ObjectHandler::convert2<bool>(
            AlphaIsFixed, "AlphaIsFixed", false);

        bool BetaIsFixedCpp = ObjectHandler::convert2<bool>(
            BetaIsFixed, "BetaIsFixed", false);

        bool NuIsFixedCpp = ObjectHandler::convert2<bool>(
            NuIsFixed, "NuIsFixed", false);

        bool RhoIsFixedCpp = ObjectHandler::convert2<bool>(
            RhoIsFixed, "RhoIsFixed", false);

        bool VegaWeightedCpp = ObjectHandler::convert2<bool>(
            VegaWeighted, "VegaWeighted", false);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        std::string MethodCpp = ObjectHandler::convert2<std::string>(
            Method, "Method", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > StdDevsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(StdDevs, "StdDevs");

        QuantLib::Handle<QuantLib::Quote> ForwardLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Forward, "Forward");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, MethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSabrSmileSection(
                ObjectId,
                OptionTime,
                Strikes,
                StdDevs,
                Forward,
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
                OptionTime,
                Strikes,
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
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSabrSmileSection : " << e.what());
        }
    }

}

