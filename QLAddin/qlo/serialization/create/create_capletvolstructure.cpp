
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

#include <qlo/serialization/create/create_capletvolstructure.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/capletvolstructure.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/quote.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/volatility/optionlet/optionletvolatilitystructure.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper1.hpp>
#include <ql/termstructures/volatility/optionlet/optionletstripper2.hpp>
#include <ql/termstructures/volatility/capfloor/capfloortermvolcurve.hpp>
#include <ql/termstructures/volatility/capfloor/capfloortermvolsurface.hpp>
#include <ql/indexes/iborindex.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlCapFloorTermVolCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BusinessDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BusinessDayConvention"));

        std::vector<ObjectHandler::property_t> OptionTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenors"), "OptionTenors");

        std::vector<ObjectHandler::property_t> Volatilities =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitiesLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // update value object precedent IDs (if any)

        valueObject->processVariant(Volatilities);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CapFloorTermVolCurve(
                valueObject,
                SettlementDays,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                VolatilitiesLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCapFloorTermVolSurface(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BusinessDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BusinessDayConvention"));

        std::vector<ObjectHandler::property_t> OptionTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenors"), "OptionTenors");

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        std::vector<std::vector<ObjectHandler::property_t> > Volatilities =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

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
            new QuantLibAddin::CapFloorTermVolSurface(
                valueObject,
                SettlementDays,
                CalendarEnum,
                BusinessDayConventionEnum,
                OptionTenorsLib,
                Strikes,
                VolatilitiesLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlConstantOptionletVolatility(
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
            new QuantLibAddin::ConstantOptionletVolatility(
                valueObject,
                NDays,
                CalendarEnum,
                BusinessDayConventionEnum,
                VolatilityLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlOptionletStripper1(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string TermVolSurface =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("TermVolSurface"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        double SwitchStrike =
            ObjectHandler::convert2<double>(valueObject->getProperty("SwitchStrike"));

        ObjectHandler::property_t Accuracy =
            valueObject->getProperty("Accuracy");

        long MaxIter =
            ObjectHandler::convert2<long>(valueObject->getProperty("MaxIter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real AccuracyLib = Accuracy;

        // convert object IDs into library objects

        OH_GET_REFERENCE(TermVolSurfaceLibObjPtr, TermVolSurface,
            QuantLibAddin::CapFloorTermVolSurface, QuantLib::CapFloorTermVolSurface)

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(TermVolSurface);
        valueObject->processPrecedentID(IborIndex);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OptionletStripper1(
                valueObject,
                TermVolSurfaceLibObjPtr,
                IborIndexLibObjPtr,
                SwitchStrike,
                AccuracyLib,
                MaxIter,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlOptionletStripper2(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string OptionletStripper1 =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionletStripper1"));

        std::string TermVolCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("TermVolCurve"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(OptionletStripper1LibObjPtr, OptionletStripper1,
            QuantLibAddin::OptionletStripper1, QuantLib::OptionletStripper1)

        OH_GET_OBJECT(TermVolCurveCoerce, TermVolCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::CapFloorTermVolCurve> TermVolCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::CapFloorTermVolCurve,
                QuantLib::CapFloorTermVolCurve>()(
                    TermVolCurveCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(OptionletStripper1);
        valueObject->processPrecedentID(TermVolCurve);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::OptionletStripper2(
                valueObject,
                OptionletStripper1LibObjPtr,
                TermVolCurveLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRelinkableHandleOptionletVolatilityStructure(
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
            new QuantLibAddin::RelinkableHandleImpl<QuantLibAddin::OptionletVolatilityStructure, QuantLib::OptionletVolatilityStructure>(
                valueObject,
                CurrentLink,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSpreadedOptionletVolatility(
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
        QuantLib::Handle<QuantLib::OptionletVolatilityStructure> BaseVolStructureLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::OptionletVolatilityStructure,
                QuantLib::OptionletVolatilityStructure>()(
                    BaseVolStructureCoerce);

        QuantLib::Handle<QuantLib::Quote> SpreadLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Spread, "Spread");

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(BaseVolStructure);
        valueObject->processVariant(Spread);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SpreadedOptionletVolatility(
                valueObject,
                BaseVolStructureLibObj,
                SpreadLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlStrippedOptionlet(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::string BusinessDayConvention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BusinessDayConvention"));

        std::string IborIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("IborIndex"));

        std::vector<ObjectHandler::property_t> OptionletDates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionletDates"), "OptionletDates");

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        std::vector<std::vector<ObjectHandler::property_t> > Volatilities =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Date> OptionletDatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(OptionletDates, "OptionletDates");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::BusinessDayConvention BusinessDayConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(BusinessDayConvention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(Volatilities, "Volatilities");

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(IborIndex);
        valueObject->processVariant(Volatilities);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StrippedOptionlet(
                valueObject,
                SettlementDays,
                CalendarEnum,
                BusinessDayConventionEnum,
                IborIndexLibObjPtr,
                OptionletDatesLib,
                Strikes,
                VolatilitiesLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlStrippedOptionletAdapter(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string StrippedOptionletBase =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("StrippedOptionletBase"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_REFERENCE(StrippedOptionletBaseLibObjPtr, StrippedOptionletBase,
            QuantLibAddin::StrippedOptionletBase, QuantLib::StrippedOptionletBase)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(StrippedOptionletBase);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StrippedOptionletAdapter(
                valueObject,
                StrippedOptionletBaseLibObjPtr,
                Permanent));
        return object;
    }

}
