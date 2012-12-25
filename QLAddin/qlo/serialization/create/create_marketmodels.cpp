
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

#include <qlo/serialization/create/create_marketmodels.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/marketmodels.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/correlation.hpp>
#include <qlo/ctsmmcapletcalibration.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <ql/models/marketmodels/models/fwdperiodadapter.hpp>
#include <ql/models/marketmodels/swapforwardmappings.hpp>
#include <ql/models/marketmodels/models/capletcoterminalalphacalibration.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlAbcdVol(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double A =
            ObjectHandler::convert2<double>(valueObject->getProperty("A"));

        double B =
            ObjectHandler::convert2<double>(valueObject->getProperty("B"));

        double C =
            ObjectHandler::convert2<double>(valueObject->getProperty("C"));

        double D =
            ObjectHandler::convert2<double>(valueObject->getProperty("D"));

        std::vector<double> Ks =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Ks"), "Ks");

        std::string Correlations =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Correlations"));

        std::string EvolutionDescription =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EvolutionDescription"));

        long Factors =
            ObjectHandler::convert2<long>(valueObject->getProperty("Factors"));

        std::vector<double> InitialRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("InitialRates"), "InitialRates");

        std::vector<double> Displacements =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Displacements"), "Displacements");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(EvolutionDescriptionLibObj, EvolutionDescription,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Correlations);
        valueObject->processPrecedentID(EvolutionDescription);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdVol(
                valueObject,
                A,
                B,
                C,
                D,
                Ks,
                CorrelationsLibObjPtr,
                EvolutionDescriptionLibObj,
                Factors,
                InitialRates,
                Displacements,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCotSwapToFwdAdapter(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string CoterminalModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CoterminalModel"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(CoterminalModelLibObjPtr, CoterminalModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(CoterminalModel);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CotSwapToFwdAdapter(
                valueObject,
                CoterminalModelLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFlatVol(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> Volatilities =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string Correlations =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Correlations"));

        std::string EvolutionDescription =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EvolutionDescription"));

        long Factors =
            ObjectHandler::convert2<long>(valueObject->getProperty("Factors"));

        std::vector<double> InitialRates =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("InitialRates"), "InitialRates");

        std::vector<double> Displacements =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Displacements"), "Displacements");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(EvolutionDescriptionLibObj, EvolutionDescription,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Correlations);
        valueObject->processPrecedentID(EvolutionDescription);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatVol(
                valueObject,
                Volatilities,
                CorrelationsLibObjPtr,
                EvolutionDescriptionLibObj,
                Factors,
                InitialRates,
                Displacements,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFlatVolFactory(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double LongTermCorr =
            ObjectHandler::convert2<double>(valueObject->getProperty("LongTermCorr"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        std::vector<double> Times =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Times"), "Times");

        std::vector<double> Volatilities =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        double Displacement =
            ObjectHandler::convert2<double>(valueObject->getProperty("Displacement"));

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
            new QuantLibAddin::FlatVolFactory(
                valueObject,
                LongTermCorr,
                Beta,
                Times,
                Volatilities,
                YieldCurveLibObj,
                Displacement,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFwdPeriodAdapter(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string LargeModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LargeModel"));

        long Period =
            ObjectHandler::convert2<long>(valueObject->getProperty("Period"));

        long Offset =
            ObjectHandler::convert2<long>(valueObject->getProperty("Offset"));

        std::vector<double> Displacements =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Displacements"), "Displacements");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(LargeModelLibObjPtr, LargeModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(LargeModel);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FwdPeriodAdapter(
                valueObject,
                LargeModelLibObjPtr,
                Period,
                Offset,
                Displacements,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlFwdToCotSwapAdapter(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string ForwardModel =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ForwardModel"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(ForwardModelLibObjPtr, ForwardModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(ForwardModel);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FwdToCotSwapAdapter(
                valueObject,
                ForwardModelLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlPseudoRootFacade(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Calibrator =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calibrator"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(CalibratorLibObjPtr, Calibrator,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Calibrator);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PseudoRootFacade(
                valueObject,
                CalibratorLibObjPtr,
                Permanent));
        return object;
    }

}
