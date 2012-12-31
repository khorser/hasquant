
/*  
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 
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

#ifndef qlcpp_optimization_hpp
#define qlcpp_optimization_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

namespace QuantLibAddinCpp {

    std::string qlArmijoLineSearch(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Epsilon,
            const ObjectHandler::property_t &Alpha,
            const ObjectHandler::property_t &Beta,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlConjugateGradient(
            const std::string &ObjectId,
            const ObjectHandler::property_t &LineSearch,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlEndCriteria(
            const std::string &ObjectId,
            const long &MaxIterations,
            const long &MaxStationaryStateIterations,
            const double &RootEpsilon,
            const double &FunctionEpsilon,
            const double &GradientNormEpsilon,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlLevenbergMarquardt(
            const std::string &ObjectId,
            const ObjectHandler::property_t &Epsfcn,
            const ObjectHandler::property_t &Xtol,
            const ObjectHandler::property_t &Gtol,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSimplex(
            const std::string &ObjectId,
            const double &Lambda,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSteepestDescent(
            const std::string &ObjectId,
            const ObjectHandler::property_t &LineSearch,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);

}

#endif

