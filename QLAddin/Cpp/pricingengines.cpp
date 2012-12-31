
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 
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
#include <qlo/pricingengines.hpp>
#include <qlo/termstructures.hpp>
#include <qlo/shortratemodels.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/marketmodels.hpp>
#include <qlo/processes.hpp>
#include <ql/pricingengines/blackformula.hpp>
#include <ql/pricingengines/blackscholescalculator.hpp>
#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolstructure.hpp>
#include <qlo/valueobjects/vo_pricingengines.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAnalyticCapFloorEngine(
            const std::string &ObjectId,
            const std::string &HandleModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(HandleModelLibObjPtr, HandleModel,
            QuantLibAddin::AffineModel, QuantLib::AffineModel)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAnalyticCapFloorEngine(
                ObjectId,
                HandleModel,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AnalyticCapFloorEngine(
                valueObject,
                HandleModelLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAnalyticCapFloorEngine : " << e.what());
        }
    }


    std::string qlBinomialPricingEngine(
            const std::string &ObjectId,
            const std::string &EngineID,
            const std::string &ProcessID,
            const long &TimeSteps,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ProcessIDLibObjPtr, ProcessID,
            QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBinomialPricingEngine(
                ObjectId,
                EngineID,
                ProcessID,
                TimeSteps,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PricingEngine(
                valueObject,
                EngineID,
                ProcessIDLibObjPtr,
                TimeSteps,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBinomialPricingEngine : " << e.what());
        }
    }


    std::string qlBlackCalculator(
            const std::string &ObjectId,
            const std::string &OptionType,
            const double &Strike,
            const double &AtmForwardValue,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            Deflator, "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            Deflator, "Deflator", 1.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCalculator(
                ObjectId,
                OptionType,
                Strike,
                AtmForwardValue,
                StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCalculator(
                valueObject,
                OptionTypeEnum,
                Strike,
                AtmForwardValue,
                StdDev,
                DeflatorLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackCalculator : " << e.what());
        }
    }


    std::string qlBlackCalculator2(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const double &AtmForwardValue,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double DeflatorCpp = ObjectHandler::convert2<double>(
            Deflator, "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            Deflator, "Deflator", 1.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCalculator2(
                ObjectId,
                PayoffID,
                AtmForwardValue,
                StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCalculator(
                valueObject,
                PayoffIDLibObjPtr,
                AtmForwardValue,
                StdDev,
                DeflatorLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackCalculator2 : " << e.what());
        }
    }


    std::string qlBlackCapFloorEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const std::string &VolTS,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        OH_GET_OBJECT(VolTSCoerce, VolTS, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> VolTSLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    VolTSCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCapFloorEngine(
                ObjectId,
                YieldCurve,
                VolTS,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCapFloorEngine(
                valueObject,
                YieldCurveLibObj,
                VolTSLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackCapFloorEngine : " << e.what());
        }
    }


    std::string qlBlackCapFloorEngine2(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Vol,
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

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> VolLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Vol, "Vol");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackCapFloorEngine2(
                ObjectId,
                YieldCurve,
                Vol,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCapFloorEngine(
                valueObject,
                YieldCurveLibObj,
                VolLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackCapFloorEngine2 : " << e.what());
        }
    }


    std::string qlBlackScholesCalculator(
            const std::string &ObjectId,
            const std::string &OptionType,
            const double &Strike,
            const double &Spot,
            const ObjectHandler::property_t &Growth,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double GrowthCpp = ObjectHandler::convert2<double>(
            Growth, "Growth", 1.0);

        double DeflatorCpp = ObjectHandler::convert2<double>(
            Deflator, "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            Deflator, "Deflator", 1.0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackScholesCalculator(
                ObjectId,
                OptionType,
                Strike,
                Spot,
                GrowthCpp,
                StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackScholesCalculator(
                valueObject,
                OptionTypeEnum,
                Strike,
                Spot,
                GrowthCpp,
                StdDev,
                DeflatorLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackScholesCalculator : " << e.what());
        }
    }


    std::string qlBlackScholesCalculator2(
            const std::string &ObjectId,
            const std::string &PayoffID,
            const double &Spot,
            const ObjectHandler::property_t &Growth,
            const double &StdDev,
            const ObjectHandler::property_t &Deflator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double GrowthCpp = ObjectHandler::convert2<double>(
            Growth, "Growth", 1.0);

        double DeflatorCpp = ObjectHandler::convert2<double>(
            Deflator, "Deflator", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real DeflatorLib = ObjectHandler::convert2<QuantLib::Real>(
            Deflator, "Deflator", 1.0);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackScholesCalculator2(
                ObjectId,
                PayoffID,
                Spot,
                GrowthCpp,
                StdDev,
                DeflatorCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackScholesCalculator(
                valueObject,
                PayoffIDLibObjPtr,
                Spot,
                GrowthCpp,
                StdDev,
                DeflatorLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackScholesCalculator2 : " << e.what());
        }
    }


    std::string qlBlackSwaptionEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const std::string &VolTS,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        OH_GET_OBJECT(VolTSCoerce, VolTS, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> VolTSLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    VolTSCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackSwaptionEngine(
                ObjectId,
                YieldCurve,
                VolTS,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackSwaptionEngine(
                valueObject,
                YieldCurveLibObj,
                VolTSLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackSwaptionEngine : " << e.what());
        }
    }


    std::string qlBlackSwaptionEngine2(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Vol,
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

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        QuantLib::Handle<QuantLib::Quote> VolLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Vol, "Vol");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBlackSwaptionEngine2(
                ObjectId,
                YieldCurve,
                Vol,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackSwaptionEngine(
                valueObject,
                YieldCurveLibObj,
                VolLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBlackSwaptionEngine2 : " << e.what());
        }
    }


    std::string qlBondEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlBondEngine(
                ObjectId,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BondEngine(
                valueObject,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlBondEngine : " << e.what());
        }
    }


    std::string qlDiscountingSwapEngine(
            const std::string &ObjectId,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &IncludeSettlDate,
            const ObjectHandler::property_t &SettlementDate,
            const ObjectHandler::property_t &NpvDate,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool IncludeSettlDateCpp = ObjectHandler::convert2<bool>(
            IncludeSettlDate, "IncludeSettlDate", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            SettlementDate, "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            NpvDate, "NpvDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlDiscountingSwapEngine(
                ObjectId,
                YieldCurve,
                IncludeSettlDateCpp,
                SettlementDate,
                NpvDate,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscountingSwapEngine(
                valueObject,
                YieldCurveLibObj,
                IncludeSettlDateCpp,
                SettlementDateLib,
                NpvDateLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlDiscountingSwapEngine : " << e.what());
        }
    }


    std::string qlPricingEngine(
            const std::string &ObjectId,
            const std::string &EngineID,
            const std::string &ProcessID,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ProcessIDLibObjPtr, ProcessID,
            QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPricingEngine(
                ObjectId,
                EngineID,
                ProcessID,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PricingEngine(
                valueObject,
                EngineID,
                ProcessIDLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPricingEngine : " << e.what());
        }
    }

}

