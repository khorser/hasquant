
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

    // qlCapFloorTermVTSVolatility

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::CapFloorTermVolatilityStructure,
                    const QuantLib::Date&,
                    double,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::CapFloorTermVolatilityStructure> >,
                    boost::_bi::value<QuantLib::Date>,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlCapFloorTermVTSVolatilityBind;

    typedef     double 
                (QuantLib::CapFloorTermVolatilityStructure::* qlCapFloorTermVTSVolatilitySignature)(
                    const QuantLib::Date&,
                    double,
                    bool) const;

    // qlCapFloorTermVTSVolatility2

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::CapFloorTermVolatilityStructure,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::CapFloorTermVolatilityStructure> >,
                    boost::_bi::value<QuantLib::Period>,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlCapFloorTermVTSVolatility2Bind;

    typedef     double 
                (QuantLib::CapFloorTermVolatilityStructure::* qlCapFloorTermVTSVolatility2Signature)(
                    const QuantLib::Period&,
                    double,
                    bool) const;

    // qlOptionletVTSBlackVariance

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf3<
                    QuantLib::Real,
                    QuantLib::OptionletVolatilityStructure,
                    const QuantLib::Date&,
                    double,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::OptionletVolatilityStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<double>,
                    boost::_bi::value<bool> > >
                qlOptionletVTSBlackVarianceBind;

    typedef     QuantLib::Real 
                (QuantLib::OptionletVolatilityStructure::* qlOptionletVTSBlackVarianceSignature)(
                    const QuantLib::Date&,
                    double,
                    bool) const;

    // qlOptionletVTSBlackVariance2

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf3<
                    QuantLib::Real,
                    QuantLib::OptionletVolatilityStructure,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::OptionletVolatilityStructure> >,
                    boost::arg<1>,
                    boost::_bi::value<double>,
                    boost::_bi::value<bool> > >
                qlOptionletVTSBlackVariance2Bind;

    typedef     QuantLib::Real 
                (QuantLib::OptionletVolatilityStructure::* qlOptionletVTSBlackVariance2Signature)(
                    const QuantLib::Period&,
                    double,
                    bool) const;

    // qlOptionletVTSVolatility

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::OptionletVolatilityStructure,
                    const QuantLib::Date&,
                    double,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::OptionletVolatilityStructure> >,
                    boost::_bi::value<QuantLib::Date>,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlOptionletVTSVolatilityBind;

    typedef     double 
                (QuantLib::OptionletVolatilityStructure::* qlOptionletVTSVolatilitySignature)(
                    const QuantLib::Date&,
                    double,
                    bool) const;

    // qlOptionletVTSVolatility2

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::OptionletVolatilityStructure,
                    const QuantLib::Period&,
                    double,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::OptionletVolatilityStructure> >,
                    boost::_bi::value<QuantLib::Period>,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlOptionletVTSVolatility2Bind;

    typedef     double 
                (QuantLib::OptionletVolatilityStructure::* qlOptionletVTSVolatility2Signature)(
                    const QuantLib::Period&,
                    double,
                    bool) const;

}

