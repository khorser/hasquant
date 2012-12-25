
/*  
 Copyright (C) 2006, 2007 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.loop.file


#include <boost/bind.hpp>

namespace QuantLibAddin {

    // qlTermStructureTimeFromReference

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf1<
                    double,
                    QuantLib::TermStructure,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::TermStructure> >,
                    boost::arg<1> > >
                qlTermStructureTimeFromReferenceBind;

    typedef     double 
                (QuantLib::TermStructure::* qlTermStructureTimeFromReferenceSignature)(
                    const QuantLib::Date&) const;

    // qlYieldTSDiscount

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf2<
                    double,
                    QuantLib::YieldTermStructure,
                    const QuantLib::Date&,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::YieldTermStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlYieldTSDiscountBind;

    typedef     double 
                (QuantLib::YieldTermStructure::* qlYieldTSDiscountSignature)(
                    const QuantLib::Date&,
                    bool) const;

    // qlYieldTSForwardRate

    typedef     boost::_bi::bind_t<
                QuantLib::InterestRate,
                boost::_mfi::cmf6<
                    QuantLib::InterestRate,
                    QuantLib::YieldTermStructure,
                    const QuantLib::Date&,
                    const QuantLib::Date&,
                    const QuantLib::DayCounter&,
                    QuantLib::Compounding,
                    QuantLib::Frequency,
                    bool>,
                boost::_bi::list7<
                    boost::_bi::value<boost::shared_ptr<QuantLib::YieldTermStructure> >,
                    boost::_bi::value<QuantLib::Date>,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::DayCounter>,
                    boost::_bi::value<QuantLib::Compounding>,
                    boost::_bi::value<QuantLib::Frequency>,
                    boost::_bi::value<bool> > >
                qlYieldTSForwardRateBind;

    typedef     QuantLib::InterestRate 
                (QuantLib::YieldTermStructure::* qlYieldTSForwardRateSignature)(
                    const QuantLib::Date&,
                    const QuantLib::Date&,
                    const QuantLib::DayCounter&,
                    QuantLib::Compounding,
                    QuantLib::Frequency,
                    bool) const;

    // qlYieldTSForwardRate2

    typedef     boost::_bi::bind_t<
                QuantLib::InterestRate,
                boost::_mfi::cmf6<
                    QuantLib::InterestRate,
                    QuantLib::YieldTermStructure,
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    const QuantLib::DayCounter&,
                    QuantLib::Compounding,
                    QuantLib::Frequency,
                    bool>,
                boost::_bi::list7<
                    boost::_bi::value<boost::shared_ptr<QuantLib::YieldTermStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Period>,
                    boost::_bi::value<QuantLib::DayCounter>,
                    boost::_bi::value<QuantLib::Compounding>,
                    boost::_bi::value<QuantLib::Frequency>,
                    boost::_bi::value<bool> > >
                qlYieldTSForwardRate2Bind;

    typedef     QuantLib::InterestRate 
                (QuantLib::YieldTermStructure::* qlYieldTSForwardRate2Signature)(
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    const QuantLib::DayCounter&,
                    QuantLib::Compounding,
                    QuantLib::Frequency,
                    bool) const;

    // qlYieldTSZeroRate

    typedef     boost::_bi::bind_t<
                QuantLib::InterestRate,
                boost::_mfi::cmf5<
                    QuantLib::InterestRate,
                    QuantLib::YieldTermStructure,
                    const QuantLib::Date&,
                    const QuantLib::DayCounter&,
                    QuantLib::Compounding,
                    QuantLib::Frequency,
                    bool>,
                boost::_bi::list6<
                    boost::_bi::value<boost::shared_ptr<QuantLib::YieldTermStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::DayCounter>,
                    boost::_bi::value<QuantLib::Compounding>,
                    boost::_bi::value<QuantLib::Frequency>,
                    boost::_bi::value<bool> > >
                qlYieldTSZeroRateBind;

    typedef     QuantLib::InterestRate 
                (QuantLib::YieldTermStructure::* qlYieldTSZeroRateSignature)(
                    const QuantLib::Date&,
                    const QuantLib::DayCounter&,
                    QuantLib::Compounding,
                    QuantLib::Frequency,
                    bool) const;

}

