
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
//      gensrc/gensrc/stubs/stub.cpp.header

#ifndef qlcpp_swaptionvolstructure_hpp
#define qlcpp_swaptionvolstructure_hpp

#include <oh/property.hpp>
#include <string>
#include <vector>

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
            const bool &Overwrite);


    std::string qlRelinkableHandleSwaptionVolatilityStructure(
            const std::string &ObjectId,
            const ObjectHandler::property_t &CurrentLink,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSmileSectionByCube(
            const std::string &ObjectId,
            const std::string &VolCube,
            const ObjectHandler::property_t &OptionDate,
            const std::string &SwapTenor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSmileSectionByCube2(
            const std::string &ObjectId,
            const std::string &VolCube,
            const std::string &OptionDate,
            const std::string &SwapTenor,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


    std::string qlSpreadedSwaptionVolatility(
            const std::string &ObjectId,
            const std::string &BaseVolStructure,
            const ObjectHandler::property_t &Spread,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite);


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
            const bool &Overwrite);


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
            const bool &Overwrite);


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
            const bool &Overwrite);

}

#endif

