
/*  
 Copyright (C) 2007 Cristina Duminuco
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2005, 2006, 2007 Eric Ehlers
 Copyright (C) 2006 Giorgio Facchinetti
 Copyright (C) 2006 Chiara Fornarola
 Copyright (C) 2006 Katiuscia Manzoni
 Copyright (C) 2005 Plamen Neykov
 
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
//      QuantLibAddin/gensrc/stubs/stub.enum.pairs

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif

#include <oh/enumerations/registry.hpp>
#include <qlo/enumerations/constructors/enumeratedpairs.hpp>

namespace QuantLibAddin {

    void registerEnumeratedCurves() {
    
        {
            ObjectHandler::Create<boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> > create;
            create.registerType(ObjectHandler::KeyPair("Discount", "BackwardFlat"), reinterpret_cast<void*>(DISCOUNT_BACKWARDFLAT_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("Discount", "ForwardFlat"), reinterpret_cast<void*>(DISCOUNT_FORWARDFLAT_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("Discount", "Linear"), reinterpret_cast<void*>(DISCOUNT_LINEAR_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("Discount", "LogLinear"), reinterpret_cast<void*>(DISCOUNT_LOGLINEAR_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ForwardRate", "BackwardFlat"), reinterpret_cast<void*>(FORWARDRATE_BACKWARDFLAT_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ForwardRate", "ForwardFlat"), reinterpret_cast<void*>(FORWARDRATE_FORWARDFLAT_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ForwardRate", "Linear"), reinterpret_cast<void*>(FORWARDRATE_LINEAR_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ForwardRate", "LogLinear"), reinterpret_cast<void*>(FORWARDRATE_LOGLINEAR_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ZeroYield", "BackwardFlat"), reinterpret_cast<void*>(ZEROYIELD_BACKWARDFLAT_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ZeroYield", "ForwardFlat"), reinterpret_cast<void*>(ZEROYIELD_FORWARDFLAT_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ZeroYield", "Linear"), reinterpret_cast<void*>(ZEROYIELD_LINEAR_HistoricalForwardRatesAnalysis));
            create.registerType(ObjectHandler::KeyPair("ZeroYield", "LogLinear"), reinterpret_cast<void*>(ZEROYIELD_LOGLINEAR_HistoricalForwardRatesAnalysis));
        }
    }

}

