
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

#include <qlo/serialization/create/create_volatilities.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/enumerations/factories/calendarfactory.hpp>
#include <qlo/indexes/interestrateindex.hpp>
#include <qlo/volatilities.hpp>
#include <ql/math/interpolations/sabrinterpolation.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/termstructures/volatility/equityfx/blackvariancesurface.hpp>
#include <ql/experimental/volatility/abcdatmvolcurve.hpp>
#include <ql/experimental/volatility/sabrvolsurface.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlAbcdAtmVolCurve(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        long SettlementDays =
            ObjectHandler::convert2<long>(valueObject->getProperty("SettlementDays"));

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::vector<ObjectHandler::property_t> OptionTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenors"), "OptionTenors");

        std::vector<ObjectHandler::property_t> VolatilitiesQuotes =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("VolatilitiesQuotes"), "VolatilitiesQuotes");

        std::vector<bool> InclusionInInterpolation =
            ObjectHandler::vector::convert2<bool>(valueObject->getProperty("InclusionInInterpolation"), "InclusionInInterpolation");

        std::string Convention =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Convention"));

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

        QuantLib::BusinessDayConvention ConventionEnum =
            ObjectHandler::Create<QuantLib::BusinessDayConvention>()(Convention);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitiesQuotesLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(VolatilitiesQuotes, "VolatilitiesQuotes");

        // update value object precedent IDs (if any)

        valueObject->processVariant(VolatilitiesQuotes);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdAtmVolCurve(
                valueObject,
                SettlementDays,
                CalendarEnum,
                OptionTenorsLib,
                VolatilitiesQuotesLibObj,
                InclusionInInterpolation,
                ConventionEnum,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackConstantVol(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDate =
            valueObject->getProperty("SettlementDate");

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        double Volatility =
            ObjectHandler::convert2<double>(valueObject->getProperty("Volatility"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("SettlementDate"), "SettlementDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackConstantVol(
                valueObject,
                SettlementDateLib,
                CalendarEnum,
                Volatility,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlBlackVarianceSurface(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t SettlementDate =
            valueObject->getProperty("SettlementDate");

        std::string Calendar =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Calendar"));

        std::vector<ObjectHandler::property_t> Dates =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("Dates"), "Dates");

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        std::vector<std::vector<double> > Volatilities =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("Volatilities"), "Volatilities");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date SettlementDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("SettlementDate"), "SettlementDate");

        std::vector<QuantLib::Date> DatesLib =
            ObjectHandler::vector::convert2<QuantLib::Date>(Dates, "Dates");

        QuantLib::Matrix VolatilitiesLib =
            QuantLibAddin::vvToQlMatrix(Volatilities);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Calendar CalendarEnum =
            ObjectHandler::Create<QuantLib::Calendar>()(Calendar);

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::BlackVarianceSurface(
                valueObject,
                SettlementDateLib,
                CalendarEnum,
                DatesLib,
                Strikes,
                VolatilitiesLib,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrVolSurface(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string InterestRateIndex =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterestRateIndex"));

        std::string BlackAtmVolCurve =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("BlackAtmVolCurve"));

        std::vector<ObjectHandler::property_t> OptionTenors =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("OptionTenors"), "OptionTenors");

        std::vector<double> AtmRateSpreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("AtmRateSpreads"), "AtmRateSpreads");

        std::vector<std::vector<ObjectHandler::property_t> > VolatilitiesQuotes =
            ObjectHandler::matrix::convert2<ObjectHandler::property_t>(valueObject->getProperty("VolatilitiesQuotes"), "VolatilitiesQuotes");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> OptionTenorsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(OptionTenors, "OptionTenors");

        // convert object IDs into library objects

        OH_GET_REFERENCE(InterestRateIndexLibObjPtr, InterestRateIndex,
            QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex)

        OH_GET_OBJECT(BlackAtmVolCurveCoerce, BlackAtmVolCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::BlackAtmVolCurve> BlackAtmVolCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::BlackAtmVolCurve,
                QuantLib::BlackAtmVolCurve>()(
                    BlackAtmVolCurveCoerce);

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > VolatilitiesQuotesLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(VolatilitiesQuotes, "VolatilitiesQuotes");

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(InterestRateIndex);
        valueObject->processPrecedentID(BlackAtmVolCurve);
        valueObject->processVariant(VolatilitiesQuotes);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrVolSurface(
                valueObject,
                InterestRateIndexLibObjPtr,
                BlackAtmVolCurveLibObj,
                OptionTenorsLib,
                AtmRateSpreads,
                VolatilitiesQuotesLibObj,
                Permanent));
        return object;
    }

}
