
/*  
 Copyright (C) 2006, 2007, 2008, 2010 Ferdinando Ametrano
 Copyright (C) 2007 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.cpp.header

#ifndef qlcpp_interpolation_hpp
#define qlcpp_interpolation_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlAbcdInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const ObjectHandler::property_t &A,
            const ObjectHandler::property_t &B,
            const ObjectHandler::property_t &C,
            const ObjectHandler::property_t &D,
            const ObjectHandler::property_t &AIsFixed,
            const ObjectHandler::property_t &BIsFixed,
            const ObjectHandler::property_t &CIsFixed,
            const ObjectHandler::property_t &DIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &OptimizationMeth,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlCubicInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const ObjectHandler::property_t &DerApprox,
            const ObjectHandler::property_t &Monotonic,
            const ObjectHandler::property_t &LeftConditionType,
            const ObjectHandler::property_t &LeftConditionValue,
            const ObjectHandler::property_t &RightConditionType,
            const ObjectHandler::property_t &RightConditionValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    bool qlExtrapolatorEnableExtrapolation(
            const std::string &ObjectId,
            const ObjectHandler::property_t &ExtrapolationFlag,
            const ObjectHandler::property_t &Trigger);


    std::string qlInterpolation(
            const std::string &ObjectId,
            const ObjectHandler::property_t &InterpolationType,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlMixedLinearCubicInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const long &SwitchIndex,
            const ObjectHandler::property_t &DerApprox,
            const ObjectHandler::property_t &Monotonic,
            const ObjectHandler::property_t &LeftConditionType,
            const ObjectHandler::property_t &LeftConditionValue,
            const ObjectHandler::property_t &RightConditionType,
            const ObjectHandler::property_t &RightConditionValue,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSABRInterpolation(
            const std::string &ObjectId,
            const std::vector<double>& XArray,
            const std::vector<ObjectHandler::property_t>& YArray,
            const double &Expiry,
            const ObjectHandler::property_t &Forward,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Nu,
            const ObjectHandler::property_t &Rho,
            const ObjectHandler::property_t &AlphaIsFixed,
            const ObjectHandler::property_t &BetaIsFixed,
            const ObjectHandler::property_t &NuIsFixed,
            const ObjectHandler::property_t &RhoIsFixed,
            const ObjectHandler::property_t &VegaWeighted,
            const ObjectHandler::property_t &EndCriteria,
            const ObjectHandler::property_t &OptimizationMeth,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

