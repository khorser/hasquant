
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

#include <qlo/serialization/create/create_payoffs.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/payoffs.hpp>
#include <qlo/stickyratchet.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlDoubleStickyRatchetPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Type1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Type1"));

        double Type2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Type2"));

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Gearing3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing3"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double Spread3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread3"));

        double InitialValue1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue1"));

        double InitialValue2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue2"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Type1Lib = Type1;

        QuantLib::Real Type2Lib = Type2;

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Gearing3Lib = Gearing3;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real Spread3Lib = Spread3;

        QuantLib::Real InitialValue1Lib = InitialValue1;

        QuantLib::Real InitialValue2Lib = InitialValue2;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::DoubleStickyRatchetPayoff(
                valueObject,
                Type1Lib,
                Type2Lib,
                Gearing1Lib,
                Gearing2Lib,
                Gearing3Lib,
                Spread1Lib,
                Spread2Lib,
                Spread3Lib,
                InitialValue1Lib,
                InitialValue2Lib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRatchetMaxPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Gearing3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing3"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double Spread3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread3"));

        double InitialValue1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue1"));

        double InitialValue2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue2"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Gearing3Lib = Gearing3;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real Spread3Lib = Spread3;

        QuantLib::Real InitialValue1Lib = InitialValue1;

        QuantLib::Real InitialValue2Lib = InitialValue2;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RatchetMaxPayoff(
                valueObject,
                Gearing1Lib,
                Gearing2Lib,
                Gearing3Lib,
                Spread1Lib,
                Spread2Lib,
                Spread3Lib,
                InitialValue1Lib,
                InitialValue2Lib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRatchetMinPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Gearing3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing3"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double Spread3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread3"));

        double InitialValue1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue1"));

        double InitialValue2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue2"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Gearing3Lib = Gearing3;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real Spread3Lib = Spread3;

        QuantLib::Real InitialValue1Lib = InitialValue1;

        QuantLib::Real InitialValue2Lib = InitialValue2;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RatchetMinPayoff(
                valueObject,
                Gearing1Lib,
                Gearing2Lib,
                Gearing3Lib,
                Spread1Lib,
                Spread2Lib,
                Spread3Lib,
                InitialValue1Lib,
                InitialValue2Lib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlRatchetPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double InitialValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real InitialValueLib = InitialValue;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::RatchetPayoff(
                valueObject,
                Gearing1Lib,
                Gearing2Lib,
                Spread1Lib,
                Spread2Lib,
                InitialValueLib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlStickyMaxPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Gearing3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing3"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double Spread3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread3"));

        double InitialValue1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue1"));

        double InitialValue2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue2"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Gearing3Lib = Gearing3;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real Spread3Lib = Spread3;

        QuantLib::Real InitialValue1Lib = InitialValue1;

        QuantLib::Real InitialValue2Lib = InitialValue2;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StickyMaxPayoff(
                valueObject,
                Gearing1Lib,
                Gearing2Lib,
                Gearing3Lib,
                Spread1Lib,
                Spread2Lib,
                Spread3Lib,
                InitialValue1Lib,
                InitialValue2Lib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlStickyMinPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Gearing3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing3"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double Spread3 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread3"));

        double InitialValue1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue1"));

        double InitialValue2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue2"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Gearing3Lib = Gearing3;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real Spread3Lib = Spread3;

        QuantLib::Real InitialValue1Lib = InitialValue1;

        QuantLib::Real InitialValue2Lib = InitialValue2;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StickyMinPayoff(
                valueObject,
                Gearing1Lib,
                Gearing2Lib,
                Gearing3Lib,
                Spread1Lib,
                Spread2Lib,
                Spread3Lib,
                InitialValue1Lib,
                InitialValue2Lib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlStickyPayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        double Gearing1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing1"));

        double Gearing2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Gearing2"));

        double Spread1 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread1"));

        double Spread2 =
            ObjectHandler::convert2<double>(valueObject->getProperty("Spread2"));

        double InitialValue =
            ObjectHandler::convert2<double>(valueObject->getProperty("InitialValue"));

        double AccrualFactor =
            ObjectHandler::convert2<double>(valueObject->getProperty("AccrualFactor"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real Gearing1Lib = Gearing1;

        QuantLib::Real Gearing2Lib = Gearing2;

        QuantLib::Real Spread1Lib = Spread1;

        QuantLib::Real Spread2Lib = Spread2;

        QuantLib::Real InitialValueLib = InitialValue;

        QuantLib::Real AccrualFactorLib = AccrualFactor;

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StickyPayoff(
                valueObject,
                Gearing1Lib,
                Gearing2Lib,
                Spread1Lib,
                Spread2Lib,
                InitialValueLib,
                AccrualFactorLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlStrikedTypePayoff(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string PayoffID =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("PayoffID"));

        std::string OptionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptionType"));

        double Strike =
            ObjectHandler::convert2<double>(valueObject->getProperty("Strike"));

        double ThirdParameter =
            ObjectHandler::convert2<double>(valueObject->getProperty("ThirdParameter"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        QuantLib::Real StrikeLib = Strike;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::Option::Type OptionTypeEnum =
            ObjectHandler::Create<QuantLib::Option::Type>()(OptionType);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::StrikedTypePayoff(
                valueObject,
                PayoffID,
                OptionTypeEnum,
                StrikeLib,
                ThirdParameter,
                Permanent));
        return object;
    }

}
