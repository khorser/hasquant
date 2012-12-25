
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
//      gensrc/gensrc/stubs/stub.serialization.register

#ifndef qlo_serialization_register_hpp
#define qlo_serialization_register_hpp

#include <qlo/serialization/register/serialization_all.hpp>

namespace QuantLibAddin {

    template<class Archive>
    void tpl_register_classes(Archive& ar) {
    
        // ObjectHandler

        register_oh(ar);
    
        // Abcd

        register_abcd(ar);

        // Accounting Engines

        register_accountingengines(ar);

        // AlphaForm

        register_alphaform(ar);

        // Asset Swap

        register_assetswap(ar);

        // Bonds

        register_bonds(ar);

        // Brownian Generator

        register_browniangenerators(ar);

        // BTP

        register_btp(ar);

        // Caps/Floors

        register_capfloor(ar);

        // Caplet Volatility Term Structures

        register_capletvolstructure(ar);

        // Cms Market

        register_cmsmarket(ar);

        // Cms Market Calibration

        register_cmsmarketcalibration(ar);

        // Correlation

        register_correlation(ar);

        // Coupon Vectors

        register_couponvectors(ar);

        // QuantLib Credit

        register_credit(ar);

        // Ctsmmcapletcalibration

        register_ctsmmcapletcalibration(ar);

        // CurveState

        register_curvestate(ar);

        // Default Probability Term Structures

        register_defaulttermstructures(ar);

        // Driftcalculators

        register_driftcalculators(ar);

        // Evolution Description

        register_evolutiondescription(ar);

        // Exercise

        register_exercise(ar);

        // Forward Rate Agreement

        register_forwardrateagreement(ar);

        // Indices

        register_index(ar);

        // Interpolation

        register_interpolation(ar);

        // Leg

        register_leg(ar);

        // Market Model Evolvers

        register_marketmodelevolvers(ar);

        // MarketModels

        register_marketmodels(ar);

        // Math

        register_mathf(ar);

        // Optimization

        register_optimization(ar);

        // Options

        register_options(ar);

        // Overnight Indexed Swap

        register_overnightindexedswap(ar);

        // Payoffs

        register_payoffs(ar);

        // Piecewise Yield Curves

        register_piecewiseyieldcurve(ar);

        // Pricing Engines

        register_pricingengines(ar);

        // Processes

        register_processes(ar);

        // Products

        register_products(ar);

        // Quotes

        register_quotes(ar);

        // Random Sequence Generator

        register_randomsequencegenerator(ar);

        // Range Accrual

        register_rangeaccrual(ar);

        // RateHelper

        register_ratehelpers(ar);

        // Schedules

        register_schedule(ar);

        // SequenceStatistics

        register_sequencestatistics(ar);

        // Short Rate Models

        register_shortratemodels(ar);

        // Smile Section Structures

        register_smilesection(ar);

        // Statistics

        register_statistics(ar);

        // Swap

        register_swap(ar);

        // Swaption

        register_swaption(ar);

        // Swaption Volatility Term Structures

        register_swaptionvolstructure(ar);

        // Yield Term Structures

        register_termstructures(ar);

        // TimeSeries

        register_timeseries(ar);

        // Vanilla Swap

        register_vanillaswap(ar);

        // Volatilities

        register_volatilities(ar);

        // Market Model Volatility

        register_volatility(ar);

    }

}

#endif
