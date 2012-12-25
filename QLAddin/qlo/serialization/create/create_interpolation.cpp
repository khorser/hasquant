
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

#include <qlo/serialization/create/create_interpolation.hpp>
#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <qlo/interpolation.hpp>
#include <qlo/interpolation2D.hpp>
#include <qlo/optimization.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlAbcdInterpolation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> XArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("XArray"), "XArray");

        std::vector<ObjectHandler::property_t> YArray =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("YArray"), "YArray");

        ObjectHandler::property_t A =
            valueObject->getProperty("A");

        ObjectHandler::property_t B =
            valueObject->getProperty("B");

        ObjectHandler::property_t C =
            valueObject->getProperty("C");

        ObjectHandler::property_t D =
            valueObject->getProperty("D");

        bool AIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("AIsFixed"));

        bool BIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("BIsFixed"));

        bool CIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("CIsFixed"));

        bool DIsFixed =
            ObjectHandler::convert2<bool>(valueObject->getProperty("DIsFixed"));

        bool VegaWeighted =
            ObjectHandler::convert2<bool>(valueObject->getProperty("VegaWeighted"));

        std::string EndCriteria =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("EndCriteria"));

        std::string OptimizationMeth =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptimizationMeth"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real ALib = A;

        QuantLib::Real BLib = B;

        QuantLib::Real CLib = C;

        QuantLib::Real DLib = D;

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteria,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptimizationMethLibObjPtr, OptimizationMeth,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // update value object precedent IDs (if any)

        valueObject->processVariant(YArray);
        valueObject->processPrecedentID(EndCriteria);
        valueObject->processPrecedentID(OptimizationMeth);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::AbcdInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                ALib,
                BLib,
                CLib,
                DLib,
                AIsFixed,
                BIsFixed,
                CIsFixed,
                DIsFixed,
                VegaWeighted,
                EndCriteriaLibObjPtr,
                OptimizationMethLibObjPtr,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlCubicInterpolation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> XArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("XArray"), "XArray");

        std::vector<ObjectHandler::property_t> YArray =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("YArray"), "YArray");

        std::string DerApprox =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DerApprox"));

        bool Monotonic =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Monotonic"));

        std::string LeftConditionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LeftConditionType"));

        ObjectHandler::property_t LeftConditionValue =
            valueObject->getProperty("LeftConditionValue");

        std::string RightConditionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("RightConditionType"));

        ObjectHandler::property_t RightConditionValue =
            valueObject->getProperty("RightConditionValue");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real LeftConditionValueLib = LeftConditionValue;

        QuantLib::Real RightConditionValueLib = RightConditionValue;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CubicInterpolation::DerivativeApprox DerApproxEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox>()(DerApprox);

        QuantLib::CubicInterpolation::BoundaryCondition LeftConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(LeftConditionType);

        QuantLib::CubicInterpolation::BoundaryCondition RightConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(RightConditionType);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        // update value object precedent IDs (if any)

        valueObject->processVariant(YArray);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CubicInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                DerApproxEnum,
                Monotonic,
                LeftConditionTypeEnum,
                LeftConditionValueLib,
                RightConditionTypeEnum,
                RightConditionValueLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlInterpolation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string InterpolationType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterpolationType"));

        std::vector<double> XArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("XArray"), "XArray");

        std::vector<ObjectHandler::property_t> YArray =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("YArray"), "YArray");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        // update value object precedent IDs (if any)

        valueObject->processVariant(YArray);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::GenericInterp(
                valueObject,
                InterpolationType,
                XArrayLib,
                YArrayLibObj,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlInterpolation2D(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::string InterpolationType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("InterpolationType"));

        std::vector<double> XArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("XArray"), "XArray");

        std::vector<double> YArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("YArray"), "YArray");

        std::vector<std::vector<double> > ZMatrix =
            ObjectHandler::matrix::convert2<double>(valueObject->getProperty("ZMatrix"), "ZMatrix");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        std::vector<QuantLib::Real> YArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(YArray);

        QuantLib::Matrix ZMatrixLib =
            QuantLibAddin::vvToQlMatrix(ZMatrix);

        // update value object precedent IDs (if any)



        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::Interpolation2D(
                valueObject,
                InterpolationType,
                XArrayLib,
                YArrayLib,
                ZMatrixLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlMixedLinearCubicInterpolation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> XArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("XArray"), "XArray");

        std::vector<ObjectHandler::property_t> YArray =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("YArray"), "YArray");

        long SwitchIndex =
            ObjectHandler::convert2<long>(valueObject->getProperty("SwitchIndex"));

        std::string DerApprox =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("DerApprox"));

        bool Monotonic =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Monotonic"));

        std::string LeftConditionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("LeftConditionType"));

        ObjectHandler::property_t LeftConditionValue =
            valueObject->getProperty("LeftConditionValue");

        std::string RightConditionType =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("RightConditionType"));

        ObjectHandler::property_t RightConditionValue =
            valueObject->getProperty("RightConditionValue");

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real LeftConditionValueLib = LeftConditionValue;

        QuantLib::Real RightConditionValueLib = RightConditionValue;

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::CubicInterpolation::DerivativeApprox DerApproxEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox>()(DerApprox);

        QuantLib::CubicInterpolation::BoundaryCondition LeftConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(LeftConditionType);

        QuantLib::CubicInterpolation::BoundaryCondition RightConditionTypeEnum =
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition>()(RightConditionType);

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        // update value object precedent IDs (if any)

        valueObject->processVariant(YArray);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::MixedLinearCubicInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                SwitchIndex,
                DerApproxEnum,
                Monotonic,
                LeftConditionTypeEnum,
                LeftConditionValueLib,
                RightConditionTypeEnum,
                RightConditionValueLib,
                Permanent));
        return object;
    }

    boost::shared_ptr<ObjectHandler::Object> create_qlSABRInterpolation(
        const boost::shared_ptr<ObjectHandler::ValueObject> &valueObject) {

        // convert input datatypes to C++ datatypes

        std::vector<double> XArray =
            ObjectHandler::vector::convert2<double>(valueObject->getProperty("XArray"), "XArray");

        std::vector<ObjectHandler::property_t> YArray =
            ObjectHandler::vector::convert2<ObjectHandler::property_t>(valueObject->getProperty("YArray"), "YArray");

        double Expiry =
            ObjectHandler::convert2<double>(valueObject->getProperty("Expiry"));

        ObjectHandler::property_t Forward =
            valueObject->getProperty("Forward");

        ObjectHandler::property_t Alpha =
            valueObject->getProperty("Alpha");

        ObjectHandler::property_t Beta =
            valueObject->getProperty("Beta");

        ObjectHandler::property_t Nu =
            valueObject->getProperty("Nu");

        ObjectHandler::property_t Rho =
            valueObject->getProperty("Rho");

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

        std::string OptimizationMeth =
            ObjectHandler::convert2<std::string>(valueObject->getProperty("OptimizationMeth"));

        bool Permanent =
            ObjectHandler::convert2<bool>(valueObject->getProperty("Permanent"));

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Real> XArrayLib = 
            QuantLibAddin::convertVector<double, QuantLib::Real>(XArray);

        QuantLib::Real AlphaLib = Alpha;

        QuantLib::Real BetaLib = Beta;

        QuantLib::Real NuLib = Nu;

        QuantLib::Real RhoLib = Rho;

        // convert object IDs into library objects

        std::vector<QuantLib::Handle<QuantLib::Quote> > YArrayLibObj =
            ObjectHandler::vector::convert2<QuantLib::Handle<QuantLib::Quote> >(YArray, "YArray");

        QuantLib::Handle<QuantLib::Quote> ForwardLibObj = 
            ObjectHandler::convert2<QuantLib::Handle<QuantLib::Quote> >(
                Forward, "Forward");

        OH_GET_REFERENCE_DEFAULT(EndCriteriaLibObjPtr, EndCriteria,
            QuantLibAddin::EndCriteria, QuantLib::EndCriteria)

        OH_GET_REFERENCE_DEFAULT(OptimizationMethLibObjPtr, OptimizationMeth,
            QuantLibAddin::OptimizationMethod, QuantLib::OptimizationMethod)

        // update value object precedent IDs (if any)

        valueObject->processVariant(YArray);
        valueObject->processVariant(Forward);
        valueObject->processPrecedentID(EndCriteria);
        valueObject->processPrecedentID(OptimizationMeth);

        // construct and return the object

        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SABRInterpolation(
                valueObject,
                XArrayLib,
                YArrayLibObj,
                Expiry,
                ForwardLibObj,
                AlphaLib,
                BetaLib,
                NuLib,
                RhoLib,
                AlphaIsFixed,
                BetaIsFixed,
                NuIsFixed,
                RhoIsFixed,
                VegaWeighted,
                EndCriteriaLibObjPtr,
                OptimizationMethLibObjPtr,
                Permanent));
        return object;
    }

}
