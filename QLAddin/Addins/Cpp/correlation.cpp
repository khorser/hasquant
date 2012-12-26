
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2007 Katiuscia Manzoni
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
#include <oh/enumerations/typefactory.hpp>
#include <qlo/sequencestatistics.hpp>
#include <qlo/correlation.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/models/marketmodels/correlations/expcorrelations.hpp>
#include <ql/models/marketmodels/historicalforwardratesanalysis.hpp>
#include <ql/models/marketmodels/historicalratesanalysis.hpp>
#include <qlo/valueobjects/vo_correlation.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCotSwapFromFwdCorrelation(
            const std::string &ObjectId,
            const std::string &FwdCorr,
            const std::string &CurveState,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            Displacement, "Displacement", 0.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(FwdCorrLibObjPtr, FwdCorr,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCotSwapFromFwdCorrelation(
                ObjectId,
                FwdCorr,
                CurveState,
                DisplacementCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CotSwapFromFwdCorrelation(
                valueObject,
                FwdCorrLibObjPtr,
                CurveStateLibObj,
                DisplacementCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCotSwapFromFwdCorrelation : " << e.what());
        }
    }


    std::string qlExponentialForwardCorrelation(
            const std::string &ObjectId,
            const std::vector<double>& RateTimes,
            const double &LongTermCorr,
            const double &Beta,
            const double &Gamma,
            const std::vector<double>& Times,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlExponentialForwardCorrelation(
                ObjectId,
                RateTimes,
                LongTermCorr,
                Beta,
                Gamma,
                Times,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ExponentialForwardCorrelation(
                valueObject,
                RateTimes,
                LongTermCorr,
                Beta,
                Gamma,
                Times,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlExponentialForwardCorrelation : " << e.what());
        }
    }


    std::string qlHistoricalForwardRatesAnalysis(
            const std::string &ObjectId,
            const std::string &SequenceStats,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const std::string &Step,
            const std::string &IborIndex,
            const std::string &InitialGap,
            const std::string &Horizon,
            const std::vector<std::string>& IborIndexes,
            const std::vector<std::string>& SwapIndexes,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &TraitsID,
            const ObjectHandler::property_t &InterpolatorID,
            const ObjectHandler::property_t &BootstrapAccuracy,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        std::string TraitsIDCpp = ObjectHandler::convert2<std::string>(
            TraitsID, "TraitsID", "Discount");

        std::string InterpolatorIDCpp = ObjectHandler::convert2<std::string>(
            InterpolatorID, "InterpolatorID", "CubicSpline");

        double BootstrapAccuracyCpp = ObjectHandler::convert2<double>(
            BootstrapAccuracy, "BootstrapAccuracy", 1.0e-12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EndDate, "EndDate");

        QuantLib::Period StepLib;
        QuantLibAddin::cppToLibrary(Step, StepLib);

        QuantLib::Period InitialGapLib;
        QuantLibAddin::cppToLibrary(InitialGap, InitialGapLib);

        QuantLib::Period HorizonLib;
        QuantLibAddin::cppToLibrary(Horizon, HorizonLib);

        QuantLib::Real BootstrapAccuracyLib = ObjectHandler::convert2<QuantLib::Real>(
            BootstrapAccuracy, "BootstrapAccuracy", 1.0e-12);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SequenceStatsLibObjPtr, SequenceStats,
            QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<boost::shared_ptr<QuantLib::IborIndex> > IborIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::IborIndex, QuantLib::IborIndex>(IborIndexes);

        std::vector<boost::shared_ptr<QuantLib::SwapIndex> > SwapIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::SwapIndex, QuantLib::SwapIndex>(SwapIndexes);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHistoricalForwardRatesAnalysis(
                ObjectId,
                SequenceStats,
                StartDate,
                EndDate,
                Step,
                IborIndex,
                InitialGap,
                Horizon,
                IborIndexes,
                SwapIndexes,
                DayCounterCpp,
                TraitsIDCpp,
                InterpolatorIDCpp,
                BootstrapAccuracyCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HistoricalForwardRatesAnalysis(
                valueObject,
                SequenceStatsLibObjPtr,
                StartDateLib,
                EndDateLib,
                StepLib,
                IborIndexLibObjPtr,
                InitialGapLib,
                HorizonLib,
                IborIndexesLibObjPtr,
                SwapIndexesLibObjPtr,
                DayCounterEnum,
                TraitsIDCpp,
                InterpolatorIDCpp,
                BootstrapAccuracyLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlHistoricalForwardRatesAnalysis : " << e.what());
        }
    }


    std::string qlHistoricalRatesAnalysis(
            const std::string &ObjectId,
            const std::string &SequenceStats,
            const ObjectHandler::property_t &StartDate,
            const ObjectHandler::property_t &EndDate,
            const std::string &Step,
            const std::vector<std::string>& InterestRateIndexes,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            StartDate, "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            EndDate, "EndDate");

        QuantLib::Period StepLib;
        QuantLibAddin::cppToLibrary(Step, StepLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SequenceStatsLibObjPtr, SequenceStats,
            QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)

        std::vector<boost::shared_ptr<QuantLib::InterestRateIndex> > InterestRateIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex>(InterestRateIndexes);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlHistoricalRatesAnalysis(
                ObjectId,
                SequenceStats,
                StartDate,
                EndDate,
                Step,
                InterestRateIndexes,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HistoricalRatesAnalysis(
                valueObject,
                SequenceStatsLibObjPtr,
                StartDateLib,
                EndDateLib,
                StepLib,
                InterestRateIndexesLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlHistoricalRatesAnalysis : " << e.what());
        }
    }


    std::string qlMarketModelLmLinearExponentialCorrelationModel(
            const std::string &ObjectId,
            const long &Size,
            const double &Rho,
            const double &Beta,
            const ObjectHandler::property_t &Factors,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long FactorsCpp = ObjectHandler::convert2<long>(
            Factors, "Factors", QuantLib::Null<QuantLib::Size>());

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlMarketModelLmLinearExponentialCorrelationModel(
                ObjectId,
                Size,
                Rho,
                Beta,
                FactorsCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LmLinearExponentialCorrelationModel(
                valueObject,
                Size,
                Rho,
                Beta,
                FactorsCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlMarketModelLmLinearExponentialCorrelationModel : " << e.what());
        }
    }

}

