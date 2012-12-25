
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

#include <qlo/serialization/create/create_correlation.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/correlation.hpp>
#include <qlo/sequencestatistics.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/models/marketmodels/correlations/expcorrelations.hpp>
#include <ql/models/marketmodels/historicalforwardratesanalysis.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCotSwapFromFwdCorrelation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string FwdCorr =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FwdCorr"));

        std::string CurveState =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurveState"));

        double Displacement =
            ObjectHandler::convert2<double>(valueObject->getProperty("Displacement"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(FwdCorrLibObjPtr, FwdCorr,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(CurveStateLibObj, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FwdCorr);
        valueObject->processPrecedentID(CurveState);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CotSwapFromFwdCorrelation(
                valueObject,
                FwdCorrLibObjPtr,
                CurveStateLibObj,
                Displacement,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlExponentialForwardCorrelation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> RateTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RateTimes"), "RateTimes");

        double LongTermCorr =
            ObjectHandler::convert2<double>(valueObject->getProperty("LongTermCorr"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        double Gamma =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gamma"));

        std::vector<double> Times =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Times"), "Times");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real LongTermCorrLib = LongTermCorr;

        QuantLib::Real BetaLib = Beta;

        QuantLib::Real GammaLib = Gamma;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ExponentialForwardCorrelation(
                valueObject,
                RateTimes,
                LongTermCorrLib,
                BetaLib,
                GammaLib,
                Times,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlHistoricalForwardRatesAnalysis(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SequenceStats =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SequenceStats"));

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t EndDate =
            valueObject->getProperty("EndDate");

        std::string Step =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Step"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::string InitialGap =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InitialGap"));

        std::string Horizon =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Horizon"));

        std::vector<std::string> IborIndexes =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("IborIndexes"), "IborIndexes");

        std::vector<std::string> SwapIndexes =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("SwapIndexes"), "SwapIndexes");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string TraitsID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("TraitsID"));

        std::string InterpolatorID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterpolatorID"));

        ObjectHandler::property_t BootstrapAccuracy =
            valueObject->getProperty("BootstrapAccuracy");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EndDate"), "EndDate");

        QuantLib::Period StepLib;
        QuantLibAddin::cppToLibrary(Step, StepLib);

        QuantLib::Period InitialGapLib;
        QuantLibAddin::cppToLibrary(InitialGap, InitialGapLib);

        QuantLib::Period HorizonLib;
        QuantLibAddin::cppToLibrary(Horizon, HorizonLib);

        QuantLib::Real BootstrapAccuracyLib = BootstrapAccuracy;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SequenceStatsLibObjPtr, SequenceStats,
            QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<boost::shared_ptr<QuantLib::IborIndex> > IborIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::IborIndex, QuantLib::IborIndex>(IborIndexes);

        std::vector<boost::shared_ptr<QuantLib::SwapIndex> > SwapIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::SwapIndex, QuantLib::SwapIndex>(SwapIndexes);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SequenceStats);
        valueObject->processPrecedentID(IborIndex);
        for (std::vector<std::string>::const_iterator i = IborIndexes.begin();
                i != IborIndexes.end(); ++i)
            valueObject->processPrecedentID(*i);
        for (std::vector<std::string>::const_iterator i = SwapIndexes.begin();
                i != SwapIndexes.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

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
                TraitsID,
                InterpolatorID,
                BootstrapAccuracyLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlHistoricalRatesAnalysis(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SequenceStats =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SequenceStats"));

        ObjectHandler::property_t StartDate =
            valueObject->getProperty("StartDate");

        ObjectHandler::property_t EndDate =
            valueObject->getProperty("EndDate");

        std::string Step =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Step"));

        std::vector<std::string> InterestRateIndexes =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("InterestRateIndexes"), "InterestRateIndexes");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("StartDate"), "StartDate");

        QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("EndDate"), "EndDate");

        QuantLib::Period StepLib;
        QuantLibAddin::cppToLibrary(Step, StepLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(SequenceStatsLibObjPtr, SequenceStats,
            QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)

        std::vector<boost::shared_ptr<QuantLib::InterestRateIndex> > InterestRateIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex>(InterestRateIndexes);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SequenceStats);
        for (std::vector<std::string>::const_iterator i = InterestRateIndexes.begin();
                i != InterestRateIndexes.end(); ++i)
            valueObject->processPrecedentID(*i);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::HistoricalRatesAnalysis(
                valueObject,
                SequenceStatsLibObjPtr,
                StartDateLib,
                EndDateLib,
                StepLib,
                InterestRateIndexesLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMarketModelLmLinearExponentialCorrelationModel(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long Size =
            ObjectHandler::convert2<long>(valueObject->getProperty("Size"));

        double Rho =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rho"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        long Factors =
            ObjectHandler::convert2<long>(valueObject->getProperty("Factors"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LmLinearExponentialCorrelationModel(
                valueObject,
                Size,
                Rho,
                Beta,
                Factors,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlTimeHomogeneousForwardCorrelation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > FwdCorrMatrix =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("FwdCorrMatrix"), "FwdCorrMatrix");

        std::vector<double> RateTimes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("RateTimes"), "RateTimes");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix FwdCorrMatrixLib =
            QuantLibAddin::vvToQlMatrix(FwdCorrMatrix);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::TimeHomogeneousForwardCorrelation(
                valueObject,
                FwdCorrMatrixLib,
                RateTimes,
                Permanent));
        return object;
    }

}
