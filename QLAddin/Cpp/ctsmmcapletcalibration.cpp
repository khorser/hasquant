
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
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
#include <qlo/ctsmmcapletcalibration.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/correlation.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/volatility.hpp>
#include <qlo/alphaform.hpp>
#include <ql/models/marketmodels/models/capletcoterminalalphacalibration.hpp>
#include <qlo/valueobjects/vo_ctsmmcapletcalibration.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCTSMMCapletAlphaFormCalibration(
            const std::string &ObjectId,
            const std::string &Evolution,
            const std::string &Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string &CurveState,
            const ObjectHandler::property_t &Displacement,
            const std::vector<double>& AlphaInitial,
            const std::vector<double>& AlphaMax,
            const std::vector<double>& AlphaMin,
            const ObjectHandler::property_t &MaximizeHomogeneity,
            const ObjectHandler::property_t &AlphaForm,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            Displacement, "Displacement", 0.0);

        bool MaximizeHomogeneityCpp = ObjectHandler::convert2<bool>(
            MaximizeHomogeneity, "MaximizeHomogeneity", true);

        std::string AlphaFormCpp = ObjectHandler::convert2<std::string>(
            AlphaForm, "AlphaForm", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        OH_GET_REFERENCE_DEFAULT(AlphaFormLibObjPtr, AlphaFormCpp,
            QuantLibAddin::AlphaForm, QuantLib::AlphaForm)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCTSMMCapletAlphaFormCalibration(
                ObjectId,
                Evolution,
                Correlations,
                SwapPiecewiseConstantVariances,
                CapletVols,
                CurveState,
                DisplacementCpp,
                AlphaInitial,
                AlphaMax,
                AlphaMin,
                MaximizeHomogeneityCpp,
                AlphaFormCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletAlphaFormCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVols,
                CurveStateLibObjPtr,
                DisplacementCpp,
                AlphaInitialLib,
                AlphaMaxLib,
                AlphaMinLib,
                MaximizeHomogeneityCpp,
                AlphaFormLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCTSMMCapletAlphaFormCalibration : " << e.what());
        }
    }


    std::string qlCTSMMCapletMaxHomogeneityCalibration(
            const std::string &ObjectId,
            const std::string &Evolution,
            const std::string &Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string &CurveState,
            const ObjectHandler::property_t &Displacement,
            const ObjectHandler::property_t &Caplet0Swaption1Priority,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            Displacement, "Displacement", 0.0);

        double Caplet0Swaption1PriorityCpp = ObjectHandler::convert2<double>(
            Caplet0Swaption1Priority, "Caplet0Swaption1Priority", 1.0);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Caplet0Swaption1PriorityLib = ObjectHandler::convert2<QuantLib::Real>(
            Caplet0Swaption1Priority, "Caplet0Swaption1Priority", 1.0);

        // convert object IDs into library objects

        OH_GET_UNDERLYING(EvolutionLibObj, Evolution,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        std::vector<boost::shared_ptr<QuantLib::PiecewiseConstantVariance> > SwapPiecewiseConstantVariancesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance>(SwapPiecewiseConstantVariances);

        OH_GET_REFERENCE(CurveStateLibObjPtr, CurveState,
            QuantLibAddin::CurveState, QuantLib::CurveState)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCTSMMCapletMaxHomogeneityCalibration(
                ObjectId,
                Evolution,
                Correlations,
                SwapPiecewiseConstantVariances,
                CapletVols,
                CurveState,
                DisplacementCpp,
                Caplet0Swaption1PriorityCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletMaxHomogeneityCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVols,
                CurveStateLibObjPtr,
                DisplacementCpp,
                Caplet0Swaption1PriorityLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCTSMMCapletMaxHomogeneityCalibration : " << e.what());
        }
    }


    std::string qlCTSMMCapletOriginalCalibration(
            const std::string &ObjectId,
            const std::string &Evolution,
            const std::string &Correlations,
            const std::vector<std::string>& SwapPiecewiseConstantVariances,
            const std::vector<double>& CapletVols,
            const std::string &CurveState,
            const ObjectHandler::property_t &Displacement,
            const std::vector<double>& Alphas,
            const ObjectHandler::property_t &LowestRoot,
            const bool &UseFullApprox,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        double DisplacementCpp = ObjectHandler::convert2<double>(
            Displacement, "Displacement", 0.0);

        bool LowestRootCpp = ObjectHandler::convert2<bool>(
            LowestRoot, "LowestRoot", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

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

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCTSMMCapletOriginalCalibration(
                ObjectId,
                Evolution,
                Correlations,
                SwapPiecewiseConstantVariances,
                CapletVols,
                CurveState,
                DisplacementCpp,
                Alphas,
                LowestRootCpp,
                UseFullApprox,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CTSMMCapletOriginalCalibration(
                valueObject,
                EvolutionLibObj,
                CorrelationsLibObjPtr,
                SwapPiecewiseConstantVariancesLibObjPtr,
                CapletVols,
                CurveStateLibObjPtr,
                DisplacementCpp,
                AlphasLib,
                LowestRootCpp,
                UseFullApprox,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCTSMMCapletOriginalCalibration : " << e.what());
        }
    }

}

