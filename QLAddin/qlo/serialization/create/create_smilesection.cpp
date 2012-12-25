
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

#include <qlo/serialization/create/create_smilesection.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/smilesection.hpp>
#include <qlo/optimization.hpp>
#include <qlo/volatilities.hpp>
#include <ql/termstructures/volatility/interpolatedsmilesection.hpp>
#include <ql/termstructures/volatility/sabrinterpolatedsmilesection.hpp>
#include <ql/experimental/volatility/sabrvolsurface.hpp>
#include <ql/quote.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlFlatSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDate =
            valueObject->getProperty("OptionDate");

        double Volatility =
            ObjectHandler::convert2<double>(valueObject->getProperty("Volatility"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        ObjectHandler::property_t RefDate =
            valueObject->getProperty("RefDate");

        double AtmValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("AtmValue"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("OptionDate"), "OptionDate");

        QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("RefDate"), "RefDate");

        QuantLib::Real AtmValueLib = AtmValue;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::FlatSmileSection(
                valueObject,
                OptionDateLib,
                Volatility,
                DayCounterEnum,
                RefDateLib,
                AtmValueLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlInterpolatedSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDate =
            valueObject->getProperty("OptionDate");

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        std::vector<ObjectHandler::property_t> StdDevs =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("StdDevs"), "StdDevs");

        ObjectHandler::property_t AtmLevel =
            valueObject->getProperty("AtmLevel");

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("OptionDate"), "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > StdDevsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(StdDevs, "StdDevs");

        QuantLib::Handle<QuantLib::Quote> AtmLevelLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                AtmLevel, "AtmLevel");

        // update value object precedent IDs (if any)

        valueObject->processVariant(StdDevs);
        valueObject->processVariant(AtmLevel);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::InterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                Strikes,
                StdDevsLibObj,
                AtmLevelLibObj,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrInterpolatedSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDate =
            valueObject->getProperty("OptionDate");

        double ForwardRate =
            ObjectHandler::convert2<double>(valueObject->getProperty("ForwardRate"));

        std::vector<double> Strike =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strike"), "Strike");

        bool FloatingStrike =
            ObjectHandler::convert2<bool>(valueObject->getProperty("FloatingStrike"));

        double AtmVolatility =
            ObjectHandler::convert2<double>(valueObject->getProperty("AtmVolatility"));

        std::vector<double> VolatilitySpreads =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("VolatilitySpreads"), "VolatilitySpreads");

        double Alpha =
            ObjectHandler::convert2<double>(valueObject->getProperty("Alpha"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        double Nu =
            ObjectHandler::convert2<double>(valueObject->getProperty("Nu"));

        double Rho =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rho"));

        bool AlphaIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("AlphaIsFixed"));

        bool BetaIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("BetaIsFixed"));

        bool NuIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("NuIsFixed"));

        bool RhoIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("RhoIsFixed"));

        bool VegaWeighted =
            ObjectHandler::convert2<bool>(valueObject->getProperty("VegaWeighted"));

        std::string EndCriteria =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EndCriteria"));

        std::string Method =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Method"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("OptionDate"), "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteria,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, Method,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(EndCriteria);
        valueObject->processPrecedentID(Method);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrInterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                ForwardRate,
                Strike,
                FloatingStrike,
                AtmVolatility,
                VolatilitySpreads,
                Alpha,
                Beta,
                Nu,
                Rho,
                AlphaIsFixed,
                BetaIsFixed,
                NuIsFixed,
                RhoIsFixed,
                VegaWeighted,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrInterpolatedSmileSection1(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        ObjectHandler::property_t OptionDate =
            valueObject->getProperty("OptionDate");

        ObjectHandler::property_t ForwardRate =
            valueObject->getProperty("ForwardRate");

        std::vector<double> Strike =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strike"), "Strike");

        bool FloatingStrike =
            ObjectHandler::convert2<bool>(valueObject->getProperty("FloatingStrike"));

        ObjectHandler::property_t AtmVolatility =
            valueObject->getProperty("AtmVolatility");

        std::vector<ObjectHandler::property_t> VolatilitySpreads =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("VolatilitySpreads"), "VolatilitySpreads");

        double Alpha =
            ObjectHandler::convert2<double>(valueObject->getProperty("Alpha"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        double Nu =
            ObjectHandler::convert2<double>(valueObject->getProperty("Nu"));

        double Rho =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rho"));

        bool AlphaIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("AlphaIsFixed"));

        bool BetaIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("BetaIsFixed"));

        bool NuIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("NuIsFixed"));

        bool RhoIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("RhoIsFixed"));

        bool VegaWeighted =
            ObjectHandler::convert2<bool>(valueObject->getProperty("VegaWeighted"));

        std::string EndCriteria =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EndCriteria"));

        std::string Method =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Method"));

        std::string DayCounter =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DayCounter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Date OptionDateLib = ObjectHandler::convert2<QuantLib::Date>(
            valueObject->getProperty("OptionDate"), "OptionDate");

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::DayCounter DayCounterEnum =
            ObjectHandler::Create<QuantLib::DayCounter>()(DayCounter);

        // convert object IDs into library objects

        QuantLib::Handle<QuantLib::Quote> ForwardRateLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                ForwardRate, "ForwardRate");

        QuantLib::Handle<QuantLib::Quote> AtmVolatilityLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                AtmVolatility, "AtmVolatility");

        std::vector<QuantLib::Handle<QuantLib::Quote> > VolatilitySpreadsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(VolatilitySpreads, "VolatilitySpreads");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteria,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, Method,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // update value object precedent IDs (if any)

        valueObject->processVariant(ForwardRate);
        valueObject->processVariant(AtmVolatility);
        valueObject->processVariant(VolatilitySpreads);
        valueObject->processPrecedentID(EndCriteria);
        valueObject->processPrecedentID(Method);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrInterpolatedSmileSection(
                valueObject,
                OptionDateLib,
                ForwardRateLibObj,
                Strike,
                FloatingStrike,
                AtmVolatilityLibObj,
                VolatilitySpreadsLibObj,
                Alpha,
                Beta,
                Nu,
                Rho,
                AlphaIsFixed,
                BetaIsFixed,
                NuIsFixed,
                RhoIsFixed,
                VegaWeighted,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
                DayCounterEnum,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double OptionTime =
            ObjectHandler::convert2<double>(valueObject->getProperty("OptionTime"));

        std::vector<double> Strikes =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("Strikes"), "Strikes");

        std::vector<ObjectHandler::property_t> StdDevs =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("StdDevs"), "StdDevs");

        ObjectHandler::property_t Forward =
            valueObject->getProperty("Forward");

        double Alpha =
            ObjectHandler::convert2<double>(valueObject->getProperty("Alpha"));

        double Beta =
            ObjectHandler::convert2<double>(valueObject->getProperty("Beta"));

        double Nu =
            ObjectHandler::convert2<double>(valueObject->getProperty("Nu"));

        double Rho =
            ObjectHandler::convert2<double>(valueObject->getProperty("Rho"));

        bool AlphaIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("AlphaIsFixed"));

        bool BetaIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("BetaIsFixed"));

        bool NuIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("NuIsFixed"));

        bool RhoIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("RhoIsFixed"));

        bool VegaWeighted =
            ObjectHandler::convert2<bool>(valueObject->getProperty("VegaWeighted"));

        std::string EndCriteria =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EndCriteria"));

        std::string Method =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("Method"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > StdDevsLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(StdDevs, "StdDevs");

        QuantLib::Handle<QuantLib::Quote> ForwardLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Forward, "Forward");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteria,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(MethodLibObjPtr, Method,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // update value object precedent IDs (if any)

        valueObject->processVariant(StdDevs);
        valueObject->processVariant(Forward);
        valueObject->processPrecedentID(EndCriteria);
        valueObject->processPrecedentID(Method);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SabrSmileSection(
                valueObject,
                OptionTime,
                Strikes,
                StdDevsLibObj,
                ForwardLibObj,
                Alpha,
                Beta,
                Nu,
                Rho,
                AlphaIsFixed,
                BetaIsFixed,
                NuIsFixed,
                RhoIsFixed,
                VegaWeighted,
                EndCriteriaLibObjPtr,
                MethodLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSmileSectionFromSabrVolSurface(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string SabrVolSurface =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("SabrVolSurface"));

        double OptionTime =
            ObjectHandler::convert2<double>(valueObject->getProperty("OptionTime"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert object IDs into library objects

        OH_GET_OBJECT(SabrVolSurfaceCoerce, SabrVolSurface, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::SabrVolSurface> SabrVolSurfaceLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::SabrVolSurface,
                QuantLib::SabrVolSurface>()(
                    SabrVolSurfaceCoerce);

        // update value object precedent IDs (if any)

        valueObject->processPrecedentID(SabrVolSurface);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SmileSectionFromSabrVolSurface(
                valueObject,
                SabrVolSurfaceLibObj,
                OptionTime,
                Permanent));
        return object;
    }

}
