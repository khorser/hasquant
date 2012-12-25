
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

#include <qlo/serialization/create/create_index.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/indexes/bmaindex.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <qlo/indexes/ibor/libor.hpp>
#include <qlo/indexes/swap/euriborswap.hpp>
#include <qlo/indexes/swap/liborswap.hpp>
#include <qlo/indexes/swap/isdafixaswap.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/experimental/coupons/proxyibor.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlBMAIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BMAIndex(
                valueObject,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEonia(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Eonia(
                valueObject,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEuribor(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Euribor(
                valueObject,
                Tenor,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEuribor365(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Euribor365(
                valueObject,
                Tenor,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEuriborSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string FixingType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixingType"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string FwdCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FwdCurve"));

        std::string DiscCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLibAddin::SwapIndex::FixingType FixingTypeEnum =
            ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType>()(FixingType);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FwdCurve);
        valueObject->processPrecedentID(DiscCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuriborSwap(
                valueObject,
                FixingTypeEnum,
                TenorLib,
                FwdCurveLibObj,
                DiscCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlEuriborSwapIsdaFixA(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string FwdCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FwdCurve"));

        std::string DiscCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FwdCurve);
        valueObject->processPrecedentID(DiscCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::EuriborSwapIsdaFixA(
                valueObject,
                TenorLib,
                FwdCurveLibObj,
                DiscCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlIborIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string FamilyName =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FamilyName"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BDayConvention"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string FwdCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FwdCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FwdCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::IborIndex(
                valueObject,
                FamilyName,
                TenorLib,
                FixingDays,
                CurrencyEnum,
                CalendarEnum,
                BDayConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                FwdCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLibor(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Libor(
                valueObject,
                CurrencyEnum,
                Tenor,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlLiborSwap(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string FixingType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixingType"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        std::string FwdCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FwdCurve"));

        std::string DiscCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLibAddin::SwapIndex::FixingType FixingTypeEnum =
            ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType>()(FixingType);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(FwdCurveCoerce, FwdCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> FwdCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    FwdCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(FwdCurve);
        valueObject->processPrecedentID(DiscCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::LiborSwap(
                valueObject,
                CurrencyEnum,
                FixingTypeEnum,
                TenorLib,
                FwdCurveLibObj,
                DiscCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlOvernightIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string FamilyName =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FamilyName"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OvernightIndex(
                valueObject,
                FamilyName,
                FixingDays,
                CurrencyEnum,
                CalendarEnum,
                DayCounterEnum,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlProxyIbor(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string FamilyName =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FamilyName"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BDayConvention"));

        bool EndOfMonth =
            ObjectHandler::convert2<bool>(valueObject->getProperty("EndOfMonth"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t Gearing =
            valueObject->getProperty("Gearing");

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        ObjectHandler::property_t Spread =
            valueObject->getProperty("Spread");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> GearingLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Gearing, "Gearing");

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Gearing);
        valueObject->processPrecedentID(IborIndex);
        valueObject->processVariant(Spread);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::ProxyIbor(
                valueObject,
                FamilyName,
                TenorLib,
                FixingDays,
                CurrencyEnum,
                CalendarEnum,
                BDayConventionEnum,
                EndOfMonth,
                DayCounterEnum,
                GearingLibObj,
                IborIndexLibObjPtr,
                SpreadLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSonia(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string YieldCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("YieldCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT_DEFAULT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(YieldCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Sonia(
                valueObject,
                YieldCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSwapIndex(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string FamilyName =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FamilyName"));

        std::string Tenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Tenor"));

        long FixingDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("FixingDays"));

        std::string Currency =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Currency"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string FixedLegTenor =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixedLegTenor"));

        std::string FixedLegBDC =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixedLegBDC"));

        std::string FixedLegDayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("FixedLegDayCounter"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::string DiscCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DiscCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Period TenorLib;
        QuantLibAddin::cppToLibrary(Tenor, TenorLib);

        QuantLib::Period FixedLegTenorLib;
        QuantLibAddin::cppToLibrary(FixedLegTenor, FixedLegTenorLib);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Currency CurrencyEnum =
            ObjectHandler::Create<QuantLib::Currency>()(Currency);

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention FixedLegBDCEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(FixedLegBDC);

        QuantLib::DayCounter FixedLegDayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(FixedLegDayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        OH_GET_OBJECT_DEFAULT(DiscCurveCoerce, DiscCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> DiscCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    DiscCurveCoerce, QuantLib::Handle<QuantLib::YieldTermStructure>());

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processPrecedentID(DiscCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SwapIndex(
                valueObject,
                FamilyName,
                TenorLib,
                FixingDays,
                CurrencyEnum,
                CalendarEnum,
                FixedLegTenorLib,
                FixedLegBDCEnum,
                FixedLegDayCounterEnum,
                IborIndexLibObjPtr,
                DiscCurveLibObj,
                Permanent));
        return object;
    }

}
