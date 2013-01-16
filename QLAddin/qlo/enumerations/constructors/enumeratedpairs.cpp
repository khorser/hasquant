/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2006 Marco Bianchetti
 Copyright (C) 2006, 2007 Eric Ehlers
 Copyright (C) 2006 Giorgio Facchinetti
 Copyright (C) 2006 Chiara Fornarola
 Copyright (C) 2007 Katiuscia Manzoni
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

#include <qlo/enumerations/constructors/enumeratedpairs.hpp>
#include <qlo/conversions/conversions.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/math/interpolations/forwardflatinterpolation.hpp>
#include <ql/math/interpolations/backwardflatinterpolation.hpp>

namespace QuantLibAddin {

    /* *** YieldTermStructures *** */

    boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> DISCOUNT_BACKWARDFLAT_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy){
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::Discount,
                                                             QuantLib::BackwardFlat>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

    boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> DISCOUNT_FORWARDFLAT_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::Discount,
                                                            QuantLib::ForwardFlat>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

    boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> DISCOUNT_LINEAR_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::Discount,
                                                            QuantLib::Linear>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

    boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> DISCOUNT_LOGLINEAR_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::Discount,
                                                            QuantLib::LogLinear>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

        boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> ZEROYIELD_BACKWARDFLAT_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ZeroYield,
                                                             QuantLib::BackwardFlat>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

        boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> ZEROYIELD_FORWARDFLAT_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ZeroYield,
                                                             QuantLib::ForwardFlat>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

   boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> ZEROYIELD_LINEAR_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ZeroYield,
                                                             QuantLib::Linear>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

   boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> ZEROYIELD_LOGLINEAR_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ZeroYield,
                                                             QuantLib::LogLinear>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

       boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> FORWARDRATE_BACKWARDFLAT_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ForwardRate,
                                                             QuantLib::BackwardFlat>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

       boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> FORWARDRATE_FORWARDFLAT_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ForwardRate,
                                                             QuantLib::ForwardFlat>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

       boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> FORWARDRATE_LINEAR_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ForwardRate,
                                                             QuantLib::Linear>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }

       boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis> FORWARDRATE_LOGLINEAR_HistoricalForwardRatesAnalysis(
        const boost::shared_ptr<QuantLib::SequenceStatistics>& stats,
        const QuantLib::Date& startDate,
        const QuantLib::Date& endDate,
        const QuantLib::Period& step,
        const boost::shared_ptr<QuantLib::InterestRateIndex>& fwdIndex,
        const QuantLib::Period& initialGap,
        const QuantLib::Period& horizon,
        const std::vector<boost::shared_ptr<QuantLib::IborIndex> >& iborIndexes,
        const std::vector<boost::shared_ptr<QuantLib::SwapIndex> >& swapIndexes,
        const QuantLib::DayCounter& yieldCurveDayCounter,
        QuantLib::Real yieldCurveAccuracy) {
            return boost::shared_ptr<QuantLib::HistoricalForwardRatesAnalysis>(new
                QuantLib::HistoricalForwardRatesAnalysisImpl<QuantLib::ForwardRate,
                                                             QuantLib::LogLinear>(
                stats,
                startDate,
                endDate,
                step,
                fwdIndex,
                initialGap,
                horizon,
                iborIndexes,
                swapIndexes,
                yieldCurveDayCounter,
                yieldCurveAccuracy));

    }
