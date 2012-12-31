
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
#include <qlo/valueobjects/vo_marketmodels.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlAbcdVol(
            const std::string &ObjectId,
            const double &A,
            const double &B,
            const double &C,
            const double &D,
            const std::vector<double>& Ks,
            const std::string &Correlations,
            const std::string &EvolutionDescription,
            const long &Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(EvolutionDescriptionLibObj, EvolutionDescription,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlAbcdVol(
                ObjectId,
                A,
                B,
                C,
                D,
                Ks,
                Correlations,
                EvolutionDescription,
                Factors,
                InitialRates,
                Displacements,
                PermanentCpp));

        // Construct the Object
        
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
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlAbcdVol : " << e.what());
        }
    }


    std::string qlCotSwapToFwdAdapter(
            const std::string &ObjectId,
            const std::string &CoterminalModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CoterminalModelLibObjPtr, CoterminalModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCotSwapToFwdAdapter(
                ObjectId,
                CoterminalModel,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CotSwapToFwdAdapter(
                valueObject,
                CoterminalModelLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCotSwapToFwdAdapter : " << e.what());
        }
    }


    std::string qlFlatVol(
            const std::string &ObjectId,
            const std::vector<double>& Volatilities,
            const std::string &Correlations,
            const std::string &EvolutionDescription,
            const long &Factors,
            const std::vector<double>& InitialRates,
            const std::vector<double>& Displacements,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CorrelationsLibObjPtr, Correlations,
            QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

        OH_GET_UNDERLYING(EvolutionDescriptionLibObj, EvolutionDescription,
            QuantLibAddin::EvolutionDescription, QuantLib::EvolutionDescription)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatVol(
                ObjectId,
                Volatilities,
                Correlations,
                EvolutionDescription,
                Factors,
                InitialRates,
                Displacements,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatVol(
                valueObject,
                Volatilities,
                CorrelationsLibObjPtr,
                EvolutionDescriptionLibObj,
                Factors,
                InitialRates,
                Displacements,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFlatVol : " << e.what());
        }
    }


    std::string qlFlatVolFactory(
            const std::string &ObjectId,
            const double &LongTermCorr,
            const double &Beta,
            const std::vector<double>& Times,
            const std::vector<double>& Volatilities,
            const std::string &YieldCurve,
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

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFlatVolFactory(
                ObjectId,
                LongTermCorr,
                Beta,
                Times,
                Volatilities,
                YieldCurve,
                DisplacementCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatVolFactory(
                valueObject,
                LongTermCorr,
                Beta,
                Times,
                Volatilities,
                YieldCurveLibObj,
                DisplacementCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFlatVolFactory : " << e.what());
        }
    }


    std::string qlFwdPeriodAdapter(
            const std::string &ObjectId,
            const std::string &LargeModel,
            const long &Period,
            const long &Offset,
            const std::vector<double>& Displacements,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size PeriodLib;
        QuantLibAddin::cppToLibrary(Period, PeriodLib);

        QuantLib::Size OffsetLib;
        QuantLibAddin::cppToLibrary(Offset, OffsetLib);

        // convert object IDs into library objects

        OH_GET_REFERENCE(LargeModelLibObjPtr, LargeModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFwdPeriodAdapter(
                ObjectId,
                LargeModel,
                Period,
                Offset,
                Displacements,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FwdPeriodAdapter(
                valueObject,
                LargeModelLibObjPtr,
                PeriodLib,
                OffsetLib,
                Displacements,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFwdPeriodAdapter : " << e.what());
        }
    }


    std::string qlFwdToCotSwapAdapter(
            const std::string &ObjectId,
            const std::string &ForwardModel,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(ForwardModelLibObjPtr, ForwardModel,
            QuantLibAddin::MarketModel, QuantLib::MarketModel)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlFwdToCotSwapAdapter(
                ObjectId,
                ForwardModel,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FwdToCotSwapAdapter(
                valueObject,
                ForwardModelLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlFwdToCotSwapAdapter : " << e.what());
        }
    }


    std::string qlPseudoRootFacade(
            const std::string &ObjectId,
            const std::string &Calibrator,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_REFERENCE(CalibratorLibObjPtr, Calibrator,
            QuantLibAddin::CTSMMCapletCalibration, QuantLib::CTSMMCapletCalibration)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlPseudoRootFacade(
                ObjectId,
                Calibrator,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::PseudoRootFacade(
                valueObject,
                CalibratorLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlPseudoRootFacade : " << e.what());
        }
    }

}

