
/*  
 Copyright (C) 2006, 2007, 2008 Ferdinando Ametrano
 Copyright (C) 2007 Marco Bianchetti
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
//      QuantLibAddin/gensrc/stubs/stub.enum.types

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif

#include <qlo/qladdindefines.hpp>
#include <qlo/interpolation.hpp>
#include <qlo/interpolation2D.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/piecewiseyieldcurve.hpp>
#include <qlo/indexes/swapindex.hpp>

#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/conundrumpricer.hpp>
#include <ql/cashflows/digitalcoupon.hpp>
#include <ql/currencies/all.hpp>
#include <ql/experimental/risk/sensitivityanalysis.hpp>
#include <ql/instruments/asianoption.hpp>
#include <ql/instruments/barrieroption.hpp>
#include <ql/instruments/capfloor.hpp>
#include <ql/instruments/forward.hpp>
#include <ql/instruments/overnightindexedswap.hpp>
#include <ql/instruments/swaption.hpp>
#include <ql/math/interpolations/cubicinterpolation.hpp>
#include <ql/math/matrixutilities/pseudosqrt.hpp>
#include <ql/math/optimization/endcriteria.hpp>
#include <ql/termstructures/volatility/swaption/cmsmarketcalibration.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/daycounters/all.hpp>
#include <ql/prices.hpp>
#include <ql/default.hpp> // RL ADD 2010-07-15

#include <oh/enumerations/typefactory.hpp>

namespace QuantLibAddin {

    void registerEnumeratedTypes() {
    
        {
            ObjectHandler::Create<QuantLib::Average::Type> create;
            create.registerType("Arithmetic", new QuantLib::Average::Type(QuantLib::Average::Arithmetic));
            create.registerType("Geometric", new QuantLib::Average::Type(QuantLib::Average::Geometric));
        }

        {
            ObjectHandler::Create<QuantLib::Barrier::Type> create;
            create.registerType("DownIn", new QuantLib::Barrier::Type(QuantLib::Barrier::DownIn));
            create.registerType("DownOut", new QuantLib::Barrier::Type(QuantLib::Barrier::DownOut));
            create.registerType("UpIn", new QuantLib::Barrier::Type(QuantLib::Barrier::UpIn));
            create.registerType("UpOut", new QuantLib::Barrier::Type(QuantLib::Barrier::UpOut));
        }

        {
            ObjectHandler::Create<QuantLib::CapFloor::Type> create;
            create.registerType("Cap", new QuantLib::CapFloor::Type(QuantLib::CapFloor::Cap));
            create.registerType("Collar", new QuantLib::CapFloor::Type(QuantLib::CapFloor::Collar));
            create.registerType("Floor", new QuantLib::CapFloor::Type(QuantLib::CapFloor::Floor));
        }

        {
            ObjectHandler::Create<QuantLib::CmsMarketCalibration::CalibrationType> create;
            create.registerType("OnForwardPrice", new QuantLib::CmsMarketCalibration::CalibrationType(QuantLib::CmsMarketCalibration::OnForwardCmsPrice));
            create.registerType("OnPrice", new QuantLib::CmsMarketCalibration::CalibrationType(QuantLib::CmsMarketCalibration::OnPrice));
            create.registerType("OnSpread", new QuantLib::CmsMarketCalibration::CalibrationType(QuantLib::CmsMarketCalibration::OnSpread));
        }

        {
            ObjectHandler::Create<QuantLib::Compounding> create;
            create.registerType("Compounded", new QuantLib::Compounding(QuantLib::Compounded));
            create.registerType("Continuous", new QuantLib::Compounding(QuantLib::Continuous));
            create.registerType("Simple", new QuantLib::Compounding(QuantLib::Simple));
            create.registerType("SimpleThenCompounded", new QuantLib::Compounding(QuantLib::SimpleThenCompounded));
        }

        {
            ObjectHandler::Create<QuantLib::CubicInterpolation::BoundaryCondition> create;
            create.registerType("FirstDerivative", new QuantLib::CubicInterpolation::BoundaryCondition(QuantLib::CubicInterpolation::FirstDerivative));
            create.registerType("Lagrange", new QuantLib::CubicInterpolation::BoundaryCondition(QuantLib::CubicInterpolation::Lagrange));
            create.registerType("NotAKnot", new QuantLib::CubicInterpolation::BoundaryCondition(QuantLib::CubicInterpolation::NotAKnot));
            create.registerType("Periodic", new QuantLib::CubicInterpolation::BoundaryCondition(QuantLib::CubicInterpolation::Periodic));
            create.registerType("SecondDerivative", new QuantLib::CubicInterpolation::BoundaryCondition(QuantLib::CubicInterpolation::SecondDerivative));
        }

        {
            ObjectHandler::Create<QuantLib::CubicInterpolation::DerivativeApprox> create;
            create.registerType("Akima", new QuantLib::CubicInterpolation::DerivativeApprox(QuantLib::CubicInterpolation::Akima));
            create.registerType("FourthOrder", new QuantLib::CubicInterpolation::DerivativeApprox(QuantLib::CubicInterpolation::FourthOrder));
            create.registerType("FritschButland", new QuantLib::CubicInterpolation::DerivativeApprox(QuantLib::CubicInterpolation::FritschButland));
            create.registerType("Kruger", new QuantLib::CubicInterpolation::DerivativeApprox(QuantLib::CubicInterpolation::Kruger));
            create.registerType("Parabolic", new QuantLib::CubicInterpolation::DerivativeApprox(QuantLib::CubicInterpolation::Parabolic));
            create.registerType("Spline", new QuantLib::CubicInterpolation::DerivativeApprox(QuantLib::CubicInterpolation::Spline));
        }

        {
            ObjectHandler::Create<QuantLib::Duration::Type> create;
            create.registerType("Macaulay", new QuantLib::Duration::Type(QuantLib::Duration::Macaulay));
            create.registerType("Modified", new QuantLib::Duration::Type(QuantLib::Duration::Modified));
            create.registerType("Simple", new QuantLib::Duration::Type(QuantLib::Duration::Simple));
        }

        {
            ObjectHandler::Create<QuantLib::EndCriteria::Type> create;
            create.registerType("MaxIterations", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::MaxIterations));
            create.registerType("None", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::None));
            create.registerType("StationaryFunctionAccuracy", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::StationaryFunctionAccuracy));
            create.registerType("StationaryFunctionValue", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::StationaryFunctionValue));
            create.registerType("StationaryPoint", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::StationaryPoint));
            create.registerType("Unknown", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::Unknown));
            create.registerType("ZeroGradientNorm", new QuantLib::EndCriteria::Type(QuantLib::EndCriteria::ZeroGradientNorm));
        }

        {
            ObjectHandler::Create<QuantLib::GFunctionFactory::YieldCurveModel> create;
            create.registerType("ExactYield", new QuantLib::GFunctionFactory::YieldCurveModel(QuantLib::GFunctionFactory::ExactYield));
            create.registerType("NonParallelShifts", new QuantLib::GFunctionFactory::YieldCurveModel(QuantLib::GFunctionFactory::NonParallelShifts));
            create.registerType("ParallelShifts", new QuantLib::GFunctionFactory::YieldCurveModel(QuantLib::GFunctionFactory::ParallelShifts));
            create.registerType("Standard", new QuantLib::GFunctionFactory::YieldCurveModel(QuantLib::GFunctionFactory::Standard));
        }

        {
            ObjectHandler::Create<QuantLib::Option::Type> create;
            create.registerType("Call", new QuantLib::Option::Type(QuantLib::Option::Call));
            create.registerType("Put", new QuantLib::Option::Type(QuantLib::Option::Put));
        }

        {
            ObjectHandler::Create<QuantLib::OvernightIndexedSwap::Type> create;
            create.registerType("Payer", new QuantLib::OvernightIndexedSwap::Type(QuantLib::OvernightIndexedSwap::Payer));
            create.registerType("Receiver", new QuantLib::OvernightIndexedSwap::Type(QuantLib::OvernightIndexedSwap::Receiver));
        }

        {
            ObjectHandler::Create<QuantLib::Position::Type> create;
            create.registerType("Long", new QuantLib::Position::Type(QuantLib::Position::Long));
            create.registerType("Short", new QuantLib::Position::Type(QuantLib::Position::Short));
        }

        {
            ObjectHandler::Create<QuantLib::PriceType> create;
            create.registerType("Ask", new QuantLib::PriceType(QuantLib::Ask));
            create.registerType("Bid", new QuantLib::PriceType(QuantLib::Bid));
            create.registerType("Close", new QuantLib::PriceType(QuantLib::Close));
            create.registerType("Last", new QuantLib::PriceType(QuantLib::Last));
            create.registerType("Mid", new QuantLib::PriceType(QuantLib::Mid));
            create.registerType("Mid Equivalent", new QuantLib::PriceType(QuantLib::MidEquivalent));
            create.registerType("Mid Safe", new QuantLib::PriceType(QuantLib::MidSafe));
        }

        {
            ObjectHandler::Create<QuantLib::Protection::Side> create;
            create.registerType("Buyer", new QuantLib::Protection::Side(QuantLib::Protection::Buyer));
            create.registerType("Seller", new QuantLib::Protection::Side(QuantLib::Protection::Seller));
        }

        {
            ObjectHandler::Create<QuantLib::Replication::Type> create;
            create.registerType("Central", new QuantLib::Replication::Type(QuantLib::Replication::Central));
            create.registerType("Sub", new QuantLib::Replication::Type(QuantLib::Replication::Sub));
            create.registerType("Super", new QuantLib::Replication::Type(QuantLib::Replication::Super));
        }

        {
            ObjectHandler::Create<QuantLib::SalvagingAlgorithm::Type> create;
            create.registerType("Higham", new QuantLib::SalvagingAlgorithm::Type(QuantLib::SalvagingAlgorithm::Higham));
            create.registerType("Hypersphere", new QuantLib::SalvagingAlgorithm::Type(QuantLib::SalvagingAlgorithm::Hypersphere));
            create.registerType("LowerDiagonal", new QuantLib::SalvagingAlgorithm::Type(QuantLib::SalvagingAlgorithm::LowerDiagonal));
            create.registerType("None", new QuantLib::SalvagingAlgorithm::Type(QuantLib::SalvagingAlgorithm::None));
            create.registerType("Spectral", new QuantLib::SalvagingAlgorithm::Type(QuantLib::SalvagingAlgorithm::Spectral));
        }

        {
            ObjectHandler::Create<QuantLib::SensitivityAnalysis> create;
            create.registerType("Centered", new QuantLib::SensitivityAnalysis(QuantLib::Centered));
            create.registerType("OneSide", new QuantLib::SensitivityAnalysis(QuantLib::OneSide));
        }

        {
            ObjectHandler::Create<QuantLib::Settlement::Type> create;
            create.registerType("Cash", new QuantLib::Settlement::Type(QuantLib::Settlement::Cash));
            create.registerType("Physical", new QuantLib::Settlement::Type(QuantLib::Settlement::Physical));
        }

        {
            ObjectHandler::Create<QuantLib::VanillaSwap::Type> create;
            create.registerType("Payer", new QuantLib::VanillaSwap::Type(QuantLib::VanillaSwap::Payer));
            create.registerType("Receiver", new QuantLib::VanillaSwap::Type(QuantLib::VanillaSwap::Receiver));
        }

        {
            ObjectHandler::Create<QuantLibAddin::RateHelper::DepoInclusionCriteria> create;
            create.registerType("AllDepos", new QuantLibAddin::RateHelper::DepoInclusionCriteria(QuantLibAddin::RateHelper::AllDepos));
            create.registerType("DeposBeforeFirstFuturesExpiryDate", new QuantLibAddin::RateHelper::DepoInclusionCriteria(QuantLibAddin::RateHelper::DeposBeforeFirstFuturesExpiryDate));
            create.registerType("DeposBeforeFirstFuturesStartDate", new QuantLibAddin::RateHelper::DepoInclusionCriteria(QuantLibAddin::RateHelper::DeposBeforeFirstFuturesStartDate));
            create.registerType("DeposBeforeFirstFuturesStartDatePlusOne", new QuantLibAddin::RateHelper::DepoInclusionCriteria(QuantLibAddin::RateHelper::DeposBeforeFirstFuturesStartDatePlusOne));
        }

        {
            ObjectHandler::Create<QuantLibAddin::SwapIndex::FixingType> create;
            create.registerType("IfrFix", new QuantLibAddin::SwapIndex::FixingType(QuantLibAddin::SwapIndex::IfrFix));
            create.registerType("Isda", new QuantLibAddin::SwapIndex::FixingType(QuantLibAddin::SwapIndex::Isda));
            create.registerType("IsdaFixA", new QuantLibAddin::SwapIndex::FixingType(QuantLibAddin::SwapIndex::IsdaFixA));
            create.registerType("IsdaFixAm", new QuantLibAddin::SwapIndex::FixingType(QuantLibAddin::SwapIndex::IsdaFixAm));
            create.registerType("IsdaFixB", new QuantLibAddin::SwapIndex::FixingType(QuantLibAddin::SwapIndex::IsdaFixB));
            create.registerType("IsdaFixPm", new QuantLibAddin::SwapIndex::FixingType(QuantLibAddin::SwapIndex::IsdaFixPm));
        }

    }
}

