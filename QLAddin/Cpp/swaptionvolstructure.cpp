
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Silvia Frasson
 Copyright (C) 2006 Mario Pucci
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
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/handleimpl.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/optimization.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube.hpp>
#include <qlo/valueobjects/vo_swaptionvolstructure.hpp>
#include <qlo/loop/loop_swaptionvolstructure.hpp>
#include <Addins/Cpp/loop.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlConstantSwaptionVolatility(
            const std::string &ObjectId,
            const ObjectHandler::property_t &NDays,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const ObjectHandler::property_t &Volatility,
            const ObjectHandler::property_t &DayCounter,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        long NDaysCpp = ObjectHandler::convert2<long>(
            NDays, "NDays", 0);

        std::string DayCounterCpp = ObjectHandler::convert2<std::string>(
            DayCounter, "DayCounter", "Actual/365 (Fixed)");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Size NDaysLib = ObjectHandler::convert2<QuantLib::Size>(
            NDays, "NDays", 0);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> VolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Volatility, "Volatility");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlConstantSwaptionVolatility(
                ObjectId,
                NDaysCpp,
                Calendar,
                BusinessDayConvention,
                Volatility,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ConstantSwaptionVolatility(
                valueObject,
                NDaysLib,
                CalendarEnum,
                BusinessDayConventionEnum,
                VolatilityLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlConstantSwaptionVolatility : " << e.what());
        }
    }


    std::string qlRelinkableHandleSwaptionVolatilityStructure(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        std::string CurrentLinkCpp = ObjectHandler::convert2<std::string>(
            CurrentLink, "CurrentLink", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlRelinkableHandleSwaptionVolatilityStructure(
                ObjectId,
                CurrentLinkCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::SwaptionVolatilityStructure, QuantLib::SwaptionVolatilityStructure>(
                valueObject,
                CurrentLinkCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlRelinkableHandleSwaptionVolatilityStructure : " << e.what());
        }
    }


    std::string qlSmileSectionByCube(
            const std::string &ObjectId,
            const std::string &VolCube,
            const ObjectHandler::property_t &OptionDate,
            const std::string &SwapTenor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            OptionDate, "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolCubeTemp, VolCube, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> VolCubeLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    VolCubeTemp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSmileSectionByCube(
                ObjectId,
                VolCube,
                OptionDate,
                SwapTenor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionByCube(
                valueObject,
                VolCubeLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSmileSectionByCube : " << e.what());
        }
    }


    std::string qlSmileSectionByCube2(
            const std::string &ObjectId,
            const std::string &VolCube,
            const std::string &OptionDate,
            const std::string &SwapTenor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period OptionDateLib;
        QuantLibAddin::cppToLibrary(OptionDate, OptionDateLib);

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolCubeTemp, VolCube, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> VolCubeLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    VolCubeTemp);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSmileSectionByCube2(
                ObjectId,
                VolCube,
                OptionDate,
                SwapTenor,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionByCube(
                valueObject,
                VolCubeLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSmileSectionByCube2 : " << e.what());
        }
    }


    std::string qlSpreadedSwaptionVolatility(
            const std::string &ObjectId,
            const std::string &BaseVolStructure,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert object IDs into library objects

        OH_GET_OBJECT(BaseVolStructureCoerce, BaseVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> BaseVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    BaseVolStructureCoerce);

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSpreadedSwaptionVolatility(
                ObjectId,
                BaseVolStructure,
                Spread,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadedSwaptionVolatility(
                valueObject,
                BaseVolStructureLibObj,
                SpreadLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSpreadedSwaptionVolatility : " << e.what());
        }
    }


    std::string qlSwaptionVTSMatrix(
            const std::string &ObjectId,
            const std::string &Calendar,
            const std::string &BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& SwapTenors,
            const std::vector<std::vector <ObjectHandler::property_t> >& Volatilities,
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

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

        std::vector<QuantLib::Period> SwapTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(SwapTenors, "SwapTenors");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounterCpp);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaptionVTSMatrix(
                ObjectId,
                Calendar,
                BusinessDayConvention,
                OptionTenors,
                SwapTenors,
                Volatilities,
                DayCounterCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolatilityMatrix(
                valueObject,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                SwapTenorsLib,
                VolatilitiesLibObj,
                DayCounterEnum,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSwaptionVTSMatrix : " << e.what());
        }
    }


    std::string qlSwaptionVolCube1(
            const std::string &ObjectId,
            const std::string &AtmVolStructure,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& SwapTenors,
            const std::vector<double>& StrikeSpreads,
            const std::vector<std::vector <ObjectHandler::property_t> >& SpreadVols,
            const std::string &SwapIndexBase,
            const std::string &ShortSwapIndexBase,
            const ObjectHandler::property_t &VegaWeightedSmileFit,
            const std::vector<std::vector <ObjectHandler::property_t> >& Guess,
            const std::vector<bool>& IsFixed,
            const bool &IsAtmCalibrated,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &MaxErrorTol,
            const ObjectHandler::property_t &OptMethod,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool VegaWeightedSmileFitCpp = ObjectHandler::convert2<bool>(
            VegaWeightedSmileFit, "VegaWeightedSmileFit", true);

        std::string EndCriteriaCpp = ObjectHandler::convert2<std::string>(
            EndCriteria, "EndCriteria", "");

        double MaxErrorTolCpp = ObjectHandler::convert2<double>(
            MaxErrorTol, "MaxErrorTol", QuantLib::Null<QuantLib::Real>());

        std::string OptMethodCpp = ObjectHandler::convert2<std::string>(
            OptMethod, "OptMethod", "");

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

        std::vector<QuantLib::Period> SwapTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(SwapTenors, "SwapTenors");

        // convert object IDs into library objects

        OH_GET_OBJECT(AtmVolStructureCoerce, AtmVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> AtmVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    AtmVolStructureCoerce);

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > SpreadVolsLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(SpreadVols, "SpreadVols");

        OH_GET_REFERENCE(SwapIndexBaseLibObjPtr, SwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(ShortSwapIndexBaseLibObjPtr, ShortSwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > GuessLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Guess, "Guess");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteriaCpp,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptMethodLibObjPtr, OptMethodCpp,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaptionVolCube1(
                ObjectId,
                AtmVolStructure,
                OptionTenors,
                SwapTenors,
                StrikeSpreads,
                SpreadVols,
                SwapIndexBase,
                ShortSwapIndexBase,
                VegaWeightedSmileFitCpp,
                Guess,
                IsFixed,
                IsAtmCalibrated,
                EndCriteriaCpp,
                MaxErrorTolCpp,
                OptMethodCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolCube1(
                valueObject,
                AtmVolStructureLibObj,
                OptionTenorsLib,
                SwapTenorsLib,
                StrikeSpreads,
                SpreadVolsLibObj,
                SwapIndexBaseLibObjPtr,
                ShortSwapIndexBaseLibObjPtr,
                VegaWeightedSmileFitCpp,
                GuessLibObj,
                IsFixed,
                IsAtmCalibrated,
                EndCriteriaLibObjPtr,
                MaxErrorTolCpp,
                OptMethodLibObjPtr,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSwaptionVolCube1 : " << e.what());
        }
    }


    std::string qlSwaptionVolCube2(
            const std::string &ObjectId,
            const std::string &AtmVolStructure,
            const std::vector<ObjectHandler::property_t>& OptionTenor,
            const std::vector<ObjectHandler::property_t>& SwapTenor,
            const std::vector<double>& StrikeSpreads,
            const std::vector<std::vector <ObjectHandler::property_t> >& SpreadVols,
            const std::string &SwapIndexBase,
            const std::string &ShortSwapIndexBase,
            const ObjectHandler::property_t &VegaWeightedSmileFit,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool VegaWeightedSmileFitCpp = ObjectHandler::convert2<bool>(
            VegaWeightedSmileFit, "VegaWeightedSmileFit", true);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenor, "OptionTenor");

        std::vector<QuantLib::Period> SwapTenorLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(SwapTenor, "SwapTenor");

        // convert object IDs into library objects

        OH_GET_OBJECT(AtmVolStructureCoerce, AtmVolStructure, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SwaptionVolatilityStructure> AtmVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SwaptionVolatilityStructure,
                QuantLib::SwaptionVolatilityStructure>()(
                    AtmVolStructureCoerce);

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > SpreadVolsLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(SpreadVols, "SpreadVols");

        OH_GET_REFERENCE(SwapIndexBaseLibObjPtr, SwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        OH_GET_REFERENCE(ShortSwapIndexBaseLibObjPtr, ShortSwapIndexBase,
            QuantLibAddin::SwapIndex, QuantLib::SwapIndex)

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSwaptionVolCube2(
                ObjectId,
                AtmVolStructure,
                OptionTenor,
                SwapTenor,
                StrikeSpreads,
                SpreadVols,
                SwapIndexBase,
                ShortSwapIndexBase,
                VegaWeightedSmileFitCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolCube2(
                valueObject,
                AtmVolStructureLibObj,
                OptionTenorLib,
                SwapTenorLib,
                StrikeSpreads,
                SpreadVolsLibObj,
                SwapIndexBaseLibObjPtr,
                ShortSwapIndexBaseLibObjPtr,
                VegaWeightedSmileFitCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlSwaptionVolCube2 : " << e.what());
        }
    }

}

