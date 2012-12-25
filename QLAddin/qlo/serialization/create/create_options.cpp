
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

#include <qlo/serialization/create/create_options.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/options.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/exercise.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBarrierOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BarrierType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BarrierType"));

        double Barrier =
            ObjectHandler::convert2<double>(valueObject->getProperty("Barrier"));

        double Rebate =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rebate"));

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real BarrierLib = Barrier;

        QuantLib::Real RebateLib = Rebate;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Barrier::Type BarrierTypeEnum =
            ObjectHandler::Create<QuantLib::Barrier::Type>()(BarrierType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BarrierOption(
                valueObject,
                BarrierTypeEnum,
                BarrierLib,
                RebateLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCaAsianOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string AverageType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("AverageType"));

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Average::Type AverageTypeEnum =
            ObjectHandler::Create<QuantLib::Average::Type>()(AverageType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ContinuousAveragingAsianOption(
                valueObject,
                AverageTypeEnum,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDaAsianOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string AverageType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("AverageType"));

        double RunningAccumulator =
            ObjectHandler::convert2<double>(valueObject->getProperty("RunningAccumulator"));

        long PastFixings =
            ObjectHandler::convert2<long>(valueObject->getProperty("PastFixings"));

        std::vector<ObjectHandler::property_t> FixingDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("FixingDates"), "FixingDates");

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real RunningAccumulatorLib = RunningAccumulator;

        std::vector<QuantLib::Date> FixingDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(FixingDates, "FixingDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Average::Type AverageTypeEnum =
            ObjectHandler::Create<QuantLib::Average::Type>()(AverageType);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DiscreteAveragingAsianOption(
                valueObject,
                AverageTypeEnum,
                RunningAccumulatorLib,
                PastFixings,
                FixingDatesLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlDividendVanillaOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        std::vector<ObjectHandler::property_t> DividendDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("DividendDates"), "DividendDates");

        std::vector<double> Dividends =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Dividends"), "Dividends");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> DividendDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(DividendDates, "DividendDates");

        std::vector<QuantLib::Real> DividendsLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Dividends);

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DividendVanillaOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                DividendDatesLib,
                DividendsLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEuropeanOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuropeanOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlForwardVanillaOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Moneyness =
            ObjectHandler::convert2<double>(valueObject->getProperty("Moneyness"));

        ObjectHandler::property_t ResetDate =
            valueObject->getProperty("ResetDate");

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real MoneynessLib = Moneyness;

        QuantLib::Date ResetDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ResetDate"), "ResetDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ForwardVanillaOption(
                valueObject,
                MoneynessLib,
                ResetDateLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlQuantoForwardVanillaOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Moneyness =
            ObjectHandler::convert2<double>(valueObject->getProperty("Moneyness"));

        ObjectHandler::property_t ResetDate =
            valueObject->getProperty("ResetDate");

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real MoneynessLib = Moneyness;

        QuantLib::Date ResetDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("ResetDate"), "ResetDate");

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::QuantoForwardVanillaOption(
                valueObject,
                MoneynessLib,
                ResetDateLib,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlQuantoVanillaOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::QuantoVanillaOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlVanillaOption(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Payoff =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Payoff"));

        std::string Exercise =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Exercise"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(PayoffLibObjPtr, Payoff,
            QuantLibAddin::StrikedTypePayoff, QuantLib::StrikedTypePayoff)

        OH_GET_REFERENCE(ExerciseLibObjPtr, Exercise,
            QuantLibAddin::Exercise, QuantLib::Exercise)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Payoff);
        valueObject->processPrecedentID(Exercise);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::VanillaOption(
                valueObject,
                PayoffLibObjPtr,
                ExerciseLibObjPtr,
                Permanent));
        return object;
    }

}
