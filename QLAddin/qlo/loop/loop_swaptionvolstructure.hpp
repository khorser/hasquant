
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

    // qlSwaptionVTSBlackVariance

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf4<
                    double,
                    QuantLib::SwaptionVolatilityStructure,
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list5<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Period>,
                    boost::_bi::value<double>,
                    boost::_bi::value<bool> > >
                qlSwaptionVTSBlackVarianceBind;

    typedef     double 
                (QuantLib::SwaptionVolatilityStructure::* qlSwaptionVTSBlackVarianceSignature)(
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    double,
                    bool) const;

    // qlSwaptionVTSBlackVariance2

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf4<
                    double,
                    QuantLib::SwaptionVolatilityStructure,
                    const QuantLib::Period&,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list5<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Period>,
                    boost::_bi::value<double>,
                    boost::_bi::value<bool> > >
                qlSwaptionVTSBlackVariance2Bind;

    typedef     double 
                (QuantLib::SwaptionVolatilityStructure::* qlSwaptionVTSBlackVariance2Signature)(
                    const QuantLib::Period&,
                    const QuantLib::Period&,
                    double,
                    bool) const;

    // qlSwaptionVTSOptionDateFromTenor

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf1<
                    QuantLib::Date,
                    QuantLib::SwaptionVolatilityStructure,
                    const QuantLib::Period&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> >,
                    boost::arg<1> > >
                qlSwaptionVTSOptionDateFromTenorBind;

    typedef     QuantLib::Date 
                (QuantLib::SwaptionVolatilityStructure::* qlSwaptionVTSOptionDateFromTenorSignature)(
                    const QuantLib::Period&) const;

    // qlSwaptionVTSSwapLength

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf1<
                    double,
                    QuantLib::SwaptionVolatilityStructure,
                    const QuantLib::Period&>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> >,
                    boost::arg<1> > >
                qlSwaptionVTSSwapLengthBind;

    typedef     double 
                (QuantLib::SwaptionVolatilityStructure::* qlSwaptionVTSSwapLengthSignature)(
                    const QuantLib::Period&) const;

    // qlSwaptionVTSVolatility

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf4<
                    double,
                    QuantLib::SwaptionVolatilityStructure,
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list5<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> >,
                    boost::_bi::value<QuantLib::Date>,
                    boost::_bi::value<QuantLib::Period>,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlSwaptionVTSVolatilityBind;

    typedef     double 
                (QuantLib::SwaptionVolatilityStructure::* qlSwaptionVTSVolatilitySignature)(
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    double,
                    bool) const;

    // qlSwaptionVTSVolatility2

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf4<
                    double,
                    QuantLib::SwaptionVolatilityStructure,
                    const QuantLib::Period&,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list5<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityStructure> >,
                    boost::_bi::value<QuantLib::Period>,
                    boost::_bi::value<QuantLib::Period>,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlSwaptionVTSVolatility2Bind;

    typedef     double 
                (QuantLib::SwaptionVolatilityStructure::* qlSwaptionVTSVolatility2Signature)(
                    const QuantLib::Period&,
                    const QuantLib::Period&,
                    double,
                    bool) const;

    // qlSwaptionVTSatmStrike

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf2<
                    double,
                    QuantLib::SwaptionVolatilityCube,
                    const QuantLib::Date&,
                    const QuantLib::Period&>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityCube> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Period> > >
                qlSwaptionVTSatmStrikeBind;

    typedef     double 
                (QuantLib::SwaptionVolatilityCube::* qlSwaptionVTSatmStrikeSignature)(
                    const QuantLib::Date&,
                    const QuantLib::Period&) const;

    // qlSwaptionVTSatmStrike2

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf2<
                    double,
                    QuantLib::SwaptionVolatilityCube,
                    const QuantLib::Period&,
                    const QuantLib::Period&>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::SwaptionVolatilityCube> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Period> > >
                qlSwaptionVTSatmStrike2Bind;

    typedef     double 
                (QuantLib::SwaptionVolatilityCube::* qlSwaptionVTSatmStrike2Signature)(
                    const QuantLib::Period&,
                    const QuantLib::Period&) const;

}

