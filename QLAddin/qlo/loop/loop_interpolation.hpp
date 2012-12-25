
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

    // qlInterpolation2DInterpolate

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf3<
                    QuantLib::Real,
                    QuantLib::Interpolation2D,
                    QuantLib::Real,
                    QuantLib::Real,
                    bool>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::Interpolation2D> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Real>,
                    boost::_bi::value<bool> > >
                qlInterpolation2DInterpolateBind;

    typedef     QuantLib::Real 
                (QuantLib::Interpolation2D::* qlInterpolation2DInterpolateSignature)(
                    QuantLib::Real,
                    QuantLib::Real,
                    bool) const;

    // qlInterpolation2DIsInRange

    typedef     boost::_bi::bind_t<
                bool,
                boost::_mfi::cmf2<
                    bool,
                    QuantLib::Interpolation2D,
                    QuantLib::Real,
                    QuantLib::Real>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::Interpolation2D> >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Real> > >
                qlInterpolation2DIsInRangeBind;

    typedef     bool 
                (QuantLib::Interpolation2D::* qlInterpolation2DIsInRangeSignature)(
                    QuantLib::Real,
                    QuantLib::Real) const;

    // qlInterpolationDerivative

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf2<
                    QuantLib::Real,
                    QuantLibAddin::Interpolation,
                    QuantLib::Real,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLibAddin::Interpolation> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlInterpolationDerivativeBind;

    typedef     QuantLib::Real 
                (QuantLibAddin::Interpolation::* qlInterpolationDerivativeSignature)(
                    QuantLib::Real,
                    bool) const;

    // qlInterpolationInterpolate

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf2<
                    QuantLib::Real,
                    QuantLibAddin::Interpolation,
                    QuantLib::Real,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLibAddin::Interpolation> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlInterpolationInterpolateBind;

    typedef     QuantLib::Real 
                (QuantLibAddin::Interpolation::* qlInterpolationInterpolateSignature)(
                    QuantLib::Real,
                    bool) const;

    // qlInterpolationIsInRange

    typedef     boost::_bi::bind_t<
                bool,
                boost::_mfi::cmf1<
                    bool,
                    QuantLib::Interpolation,
                    QuantLib::Real>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::Interpolation> >,
                    boost::arg<1> > >
                qlInterpolationIsInRangeBind;

    typedef     bool 
                (QuantLib::Interpolation::* qlInterpolationIsInRangeSignature)(
                    QuantLib::Real) const;

    // qlInterpolationPrimitive

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf2<
                    QuantLib::Real,
                    QuantLibAddin::Interpolation,
                    QuantLib::Real,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLibAddin::Interpolation> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlInterpolationPrimitiveBind;

    typedef     QuantLib::Real 
                (QuantLibAddin::Interpolation::* qlInterpolationPrimitiveSignature)(
                    QuantLib::Real,
                    bool) const;

    // qlInterpolationSecondDerivative

    typedef     boost::_bi::bind_t<
                QuantLib::Real,
                boost::_mfi::cmf2<
                    QuantLib::Real,
                    QuantLibAddin::Interpolation,
                    QuantLib::Real,
                    bool>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLibAddin::Interpolation> >,
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlInterpolationSecondDerivativeBind;

    typedef     QuantLib::Real 
                (QuantLibAddin::Interpolation::* qlInterpolationSecondDerivativeSignature)(
                    QuantLib::Real,
                    bool) const;

}

