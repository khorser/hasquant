
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
//      gensrc/gensrc/stubs/stub.serialization.header

#ifndef qlo_create_smilesection_hpp
#define qlo_create_smilesection_hpp

#include <oh/ohdefines.hpp>
#include <oh/object.hpp>
#include <oh/valueobject.hpp>

namespace QuantLibAddin {

    boost::shared_ptr<ObjectHandler::Object> create_qlFlatSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject>&);

    boost::shared_ptr<ObjectHandler::Object> create_qlInterpolatedSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject>&);

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrInterpolatedSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject>&);

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrInterpolatedSmileSection1(
        const boost::shared_ptr<ObjectHandler::ValueObject>&);

    boost::shared_ptr<ObjectHandler::Object> create_qlSabrSmileSection(
        const boost::shared_ptr<ObjectHandler::ValueObject>&);

    boost::shared_ptr<ObjectHandler::Object> create_qlSmileSectionFromSabrVolSurface(
        const boost::shared_ptr<ObjectHandler::ValueObject>&);

}

#endif

