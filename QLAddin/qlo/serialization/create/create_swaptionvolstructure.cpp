
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

#include <qlo/serialization/create/create_swaptionvolstructure.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/conversions/coercetermstructure.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/optimization.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/termstructures/volatility/swaption/swaptionvolcube.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlConstantSwaptionVolatility(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long NDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("NDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BusinessDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BusinessDayConvention"));

        ObjectHandler::property_t Volatility =
            valueObject->getProperty("Volatility");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> VolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Volatility, "Volatility");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Volatility);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ConstantSwaptionVolatility(
                valueObject,
                NDays,
                CalendarEnum,
                BusinessDayConventionEnum,
                VolatilityLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRelinkableHandleSwaptionVolatilityStructure(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string CurrentLink =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("CurrentLink"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(CurrentLink);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::SwaptionVolatilityStructure, QuantLib::SwaptionVolatilityStructure>(
                valueObject,
                CurrentLink,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSmileSectionByCube(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string VolCube =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("VolCube"));

        ObjectHandler::property_t OptionDate =
            valueObject->getProperty("OptionDate");

        std::string SwapTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapTenor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("OptionDate"), "OptionDate");

        QuantLib::Period SwapTenorLib;
        QuantLibAddin::cppToLibrary(SwapTenor, SwapTenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT(VolCubeTemp, VolCube, ObjectHandler::Object)
        boost::shared_ptr<QuantLib::SwaptionVolatilityCube> VolCubeLibObjPtr =
            QuantLibAddin::CoerceTermStructure<
                QuantLibAddin::SwaptionVolatilityCube,
                QuantLib::SwaptionVolatilityCube>()(
                    VolCubeTemp);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(VolCube);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionByCube(
                valueObject,
                VolCubeLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSmileSectionByCube2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string VolCube =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("VolCube"));

        std::string OptionDate =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionDate"));

        std::string SwapTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapTenor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(VolCube);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionByCube(
                valueObject,
                VolCubeLibObjPtr,
                OptionDateLib,
                SwapTenorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSpreadedSwaptionVolatility(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string BaseVolStructure =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BaseVolStructure"));

        ObjectHandler::property_t Spread =
            valueObject->getProperty("Spread");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(BaseVolStructure);
        valueObject->processVariant(Spread);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadedSwaptionVolatility(
                valueObject,
                BaseVolStructureLibObj,
                SpreadLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwaptionVTSMatrix(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BusinessDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BusinessDayConvention"));

        std::vector<ObjectHandler::property_t> OptionTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenors"), "OptionTenors");

        std::vector<ObjectHandler::property_t> SwapTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("SwapTenors"), "SwapTenors");

        std::vector<std::vector<ObjectHandler::property_t> > Volatilities =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Volatilities);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwaptionVolatilityMatrix(
                valueObject,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                SwapTenorsLib,
                VolatilitiesLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwaptionVolCube1(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string AtmVolStructure =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("AtmVolStructure"));

        std::vector<ObjectHandler::property_t> OptionTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenors"), "OptionTenors");

        std::vector<ObjectHandler::property_t> SwapTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("SwapTenors"), "SwapTenors");

        std::vector<double> StrikeSpreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("StrikeSpreads"), "StrikeSpreads");

        std::vector<std::vector<ObjectHandler::property_t> > SpreadVols =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("SpreadVols"), "SpreadVols");

        std::string SwapIndexBase =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndexBase"));

        std::string ShortSwapIndexBase =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ShortSwapIndexBase"));

        bool VegaWeightedSmileFit =
            ObjectHandler::convert2<bool>(valueObject->getProperty("VegaWeightedSmileFit"));

        std::vector<std::vector<ObjectHandler::property_t> > Guess =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("Guess"), "Guess");

        std::vector<bool> IsFixed =
            ObjectHandler::vector::convert2<bool>(valueObject->getProperty("IsFixed"), "IsFixed");

        bool IsAtmCalibrated =
            ObjectHandler::convert2<bool>(valueObject->getProperty("IsAtmCalibrated"));

        std::string EndCriteria =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EndCriteria"));

        double MaxErrorTol =
            ObjectHandler::convert2<double>(valueObject->getProperty("MaxErrorTol"));

        std::string OptMethod =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptMethod"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteria,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptMethodLibObjPtr, OptMethod,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(AtmVolStructure);
        valueObject->processVariant(SpreadVols);
        valueObject->processPrecedentID(SwapIndexBase);
        valueObject->processPrecedentID(ShortSwapIndexBase);
        valueObject->processVariant(Guess);
        valueObject->processPrecedentID(EndCriteria);
        valueObject->processPrecedentID(OptMethod);

        // construct and return the object

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
                VegaWeightedSmileFit,
                GuessLibObj,
                IsFixed,
                IsAtmCalibrated,
                EndCriteriaLibObjPtr,
                MaxErrorTol,
                OptMethodLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwaptionVolCube2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string AtmVolStructure =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("AtmVolStructure"));

        std::vector<ObjectHandler::property_t> OptionTenor =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenor"), "OptionTenor");

        std::vector<ObjectHandler::property_t> SwapTenor =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("SwapTenor"), "SwapTenor");

        std::vector<double> StrikeSpreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("StrikeSpreads"), "StrikeSpreads");

        std::vector<std::vector<ObjectHandler::property_t> > SpreadVols =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("SpreadVols"), "SpreadVols");

        std::string SwapIndexBase =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SwapIndexBase"));

        std::string ShortSwapIndexBase =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("ShortSwapIndexBase"));

        bool VegaWeightedSmileFit =
            ObjectHandler::convert2<bool>(valueObject->getProperty("VegaWeightedSmileFit"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

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

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(AtmVolStructure);
        valueObject->processVariant(SpreadVols);
        valueObject->processPrecedentID(SwapIndexBase);
        valueObject->processPrecedentID(ShortSwapIndexBase);

        // construct and return the object

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
                VegaWeightedSmileFit,
                Permanent));
        return object;
    }

}
