
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

#include <qlo/serialization/create/create_pricingengines.hpp>
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

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlAnalyticCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string HandleModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("HandleModel"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(HandleModelLibObjPtr, HandleModel,
            QuantLibAddin::AffineModel, QuantLib::AffineModel)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(HandleModel);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AnalyticCapFloorEngine(
                valueObject,
                HandleModelLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBinomialPricingEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string EngineID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EngineID"));

        std::string ProcessID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ProcessID"));

        long TimeSteps =
            ObjectHandler::convert2<long>(valueObject->getProperty("TimeSteps"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(ProcessIDLibObjPtr, ProcessID,
            QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ProcessID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PricingEngine(
                valueObject,
                EngineID,
                ProcessIDLibObjPtr,
                TimeSteps,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OptionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionType"));

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        double AtmForwardValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("AtmForwardValue"));

        double StdDev =
            ObjectHandler::convert2<double>(valueObject->getProperty("StdDev"));

        ObjectHandler::property_t Deflator =
            valueObject->getProperty("Deflator");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real StrikeLib = Strike;

        QuantLib::Real AtmForwardValueLib = AtmForwardValue;

        QuantLib::Real StdDevLib = StdDev;

        QuantLib::Real DeflatorLib = Deflator;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCalculator(
                valueObject,
                OptionTypeEnum,
                StrikeLib,
                AtmForwardValueLib,
                StdDevLib,
                DeflatorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackCalculator2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PayoffID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PayoffID"));

        double AtmForwardValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("AtmForwardValue"));

        double StdDev =
            ObjectHandler::convert2<double>(valueObject->getProperty("StdDev"));

        ObjectHandler::property_t Deflator =
            valueObject->getProperty("Deflator");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real AtmForwardValueLib = AtmForwardValue;

        QuantLib::Real StdDevLib = StdDev;

        QuantLib::Real DeflatorLib = Deflator;

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(PayoffID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCalculator(
                valueObject,
                PayoffIDLibObjPtr,
                AtmForwardValueLib,
                StdDevLib,
                DeflatorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackCapFloorEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        std::string VolTS =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("VolTS"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);
        valueObject->processPrecedentID(VolTS);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCapFloorEngine(
                valueObject,
                YieldCurveLibObj,
                VolTSLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackCapFloorEngine2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        ObjectHandler::property_t Vol =
            valueObject->getProperty("Vol");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);
        valueObject->processVariant(Vol);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackCapFloorEngine(
                valueObject,
                YieldCurveLibObj,
                VolLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackScholesCalculator(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OptionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionType"));

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        double Spot =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spot"));

        double Growth =
            ObjectHandler::convert2<double>(valueObject->getProperty("Growth"));

        double StdDev =
            ObjectHandler::convert2<double>(valueObject->getProperty("StdDev"));

        ObjectHandler::property_t Deflator =
            valueObject->getProperty("Deflator");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real StrikeLib = Strike;

        QuantLib::Real SpotLib = Spot;

        QuantLib::Real StdDevLib = StdDev;

        QuantLib::Real DeflatorLib = Deflator;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackScholesCalculator(
                valueObject,
                OptionTypeEnum,
                StrikeLib,
                SpotLib,
                Growth,
                StdDevLib,
                DeflatorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackScholesCalculator2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PayoffID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PayoffID"));

        double Spot =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spot"));

        double Growth =
            ObjectHandler::convert2<double>(valueObject->getProperty("Growth"));

        double StdDev =
            ObjectHandler::convert2<double>(valueObject->getProperty("StdDev"));

        ObjectHandler::property_t Deflator =
            valueObject->getProperty("Deflator");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real SpotLib = Spot;

        QuantLib::Real StdDevLib = StdDev;

        QuantLib::Real DeflatorLib = Deflator;

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffIDLibObjPtr, PayoffID,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(PayoffID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackScholesCalculator(
                valueObject,
                PayoffIDLibObjPtr,
                SpotLib,
                Growth,
                StdDevLib,
                DeflatorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackSwaptionEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        std::string VolTS =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("VolTS"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);
        valueObject->processPrecedentID(VolTS);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackSwaptionEngine(
                valueObject,
                YieldCurveLibObj,
                VolTSLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackSwaptionEngine2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        ObjectHandler::property_t Vol =
            valueObject->getProperty("Vol");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);
        valueObject->processVariant(Vol);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackSwaptionEngine(
                valueObject,
                YieldCurveLibObj,
                VolLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBondEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BondEngine(
                valueObject,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDiscountingSwapEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool IncludeSettlDate =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IncludeSettlDate"));

        ObjectHandler::property_t SettlementDate =
            valueObject->getProperty("SettlementDate");

        ObjectHandler::property_t NpvDate =
            valueObject->getProperty("NpvDate");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("SettlementDate"), "SettlementDate", QuantLib::Date());

        QuantLib::Date NpvDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("NpvDate"), "NpvDate", QuantLib::Date());

        // convert object IDs into library objects

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscountingSwapEngine(
                valueObject,
                YieldCurveLibObj,
                IncludeSettlDate,
                SettlementDateLib,
                NpvDateLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlPricingEngine(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string EngineID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EngineID"));

        std::string ProcessID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ProcessID"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(ProcessIDLibObjPtr, ProcessID,
            QuantLibAddin::GeneralizedBlackScholesProcess, QuantLib::GeneralizedBlackScholesProcess)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ProcessID);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PricingEngine(
                valueObject,
                EngineID,
                ProcessIDLibObjPtr,
                Permanent));
        return object;
    }

}
