
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

#include <qlo/serialization/create/create_ctsmmcapletcalibration.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <qlo/ctsmmcapletcalibration.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/correlation.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/volatility.hpp>
#include <qlo/alphaform.hpp>
#include <ql/models/marketmodels/models/capletcoterminalalphacalibration.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCTSMMCapletAlphaFormCalibration(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Evolution =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Evolution"));

        std::string Correlations =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Correlations"));

        std::vector<std::string> SwapPiecewiseConstantVariances =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("SwapPiecewiseConstantVariances"), "SwapPiecewiseConstantVariances");

        std::vector<double> CapletVols =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CapletVols"), "CapletVols");

        std::string CurveState =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurveState"));

        double Displacement =
            ObjectHandler::convert2<double>(valueObject->getProperty("Displacement"));

        std::vector<double> AlphaInitial =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("AlphaInitial"), "AlphaInitial");

        std::vector<double> AlphaMax =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("AlphaMax"), "AlphaMax");

        std::vector<double> AlphaMin =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("AlphaMin"), "AlphaMin");

        bool MaximizeHomogeneity =
            ObjectHandler::convert2<bool>(valueObject->getProperty("MaximizeHomogeneity"));

        std::string AlphaForm =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("AlphaForm"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> AlphaInitialLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(AlphaInitial);

        std::vector<QuantLib::Real> AlphaMaxLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(AlphaMax);

        std::vector<QuantLib::Real> AlphaMinLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(AlphaMin);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariances);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        OH_GET_REFERENCE_DEFAULT(AlphaFormLibObjPtr, AlphaForm,
            QuantLibAddin::AlphaForm, QuantLib::AlphaForm)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Evolution);
        valueObject->processPrecedentID(Correlations);
        for (std::vector<std::string>::const_iterator i = SwapPiecewiseConstantVariances.begin();
                i != SwapPiecewiseConstantVariances.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processPrecedentID(CurveState);
        valueObject->processPrecedentID(AlphaForm);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletAlphaFormCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVols,
                CurveStateLibObjPtr,
                Displacement,
                AlphaInitialLib,
                AlphaMaxLib,
                AlphaMinLib,
                MaximizeHomogeneity,
                AlphaFormLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCTSMMCapletMaxHomogeneityCalibration(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Evolution =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Evolution"));

        std::string Correlations =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Correlations"));

        std::vector<std::string> SwapPiecewiseConstantVariances =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("SwapPiecewiseConstantVariances"), "SwapPiecewiseConstantVariances");

        std::vector<double> CapletVols =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CapletVols"), "CapletVols");

        std::string CurveState =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurveState"));

        double Displacement =
            ObjectHandler::convert2<double>(valueObject->getProperty("Displacement"));

        ObjectHandler::property_t Caplet0Swaption1Priority =
            valueObject->getProperty("Caplet0Swaption1Priority");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Caplet0Swaption1PriorityLib = Caplet0Swaption1Priority;

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariances);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Evolution);
        valueObject->processPrecedentID(Correlations);
        for (std::vector<std::string>::const_iterator i = SwapPiecewiseConstantVariances.begin();
                i != SwapPiecewiseConstantVariances.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processPrecedentID(CurveState);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletMaxHomogeneityCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVols,
                CurveStateLibObjPtr,
                Displacement,
                Caplet0Swaption1PriorityLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCTSMMCapletOriginalCalibration(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Evolution =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Evolution"));

        std::string Correlations =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Correlations"));

        std::vector<std::string> SwapPiecewiseConstantVariances =
            ObjectHandler::vector::convert2<std::string>(valueObject->getProperty("SwapPiecewiseConstantVariances"), "SwapPiecewiseConstantVariances");

        std::vector<double> CapletVols =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("CapletVols"), "CapletVols");

        std::string CurveState =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurveState"));

        double Displacement =
            ObjectHandler::convert2<double>(valueObject->getProperty("Displacement"));

        std::vector<double> Alphas =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Alphas"), "Alphas");

        bool LowestRoot =
            ObjectHandler::convert2<bool>(valueObject->getProperty("LowestRoot"));

        bool UseFullApprox =
            ObjectHandler::convert2<bool>(valueObject->getProperty("UseFullApprox"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> AlphasLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(Alphas);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariances);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(Evolution);
        valueObject->processPrecedentID(Correlations);
        for (std::vector<std::string>::const_iterator i = SwapPiecewiseConstantVariances.begin();
                i != SwapPiecewiseConstantVariances.end(); ++i)
            valueObject->processPrecedentID(*i);
        valueObject->processPrecedentID(CurveState);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletOriginalCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVols,
                CurveStateLibObjPtr,
                Displacement,
                AlphasLib,
                LowestRoot,
                UseFullApprox,
                Permanent));
        return object;
    }

}
