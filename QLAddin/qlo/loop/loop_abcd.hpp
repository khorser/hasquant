
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

    // qlAbcdFunctionCovariance

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf4<
                    double,
                    QuantLib::AbcdFunction,
                    double,
                    double,
                    double,
                    double>,
                boost::_bi::list5<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::_bi::value<double>,
                    boost::arg<1>,
                    boost::_bi::value<double>,
                    boost::_bi::value<double> > >
                qlAbcdFunctionCovarianceBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionCovarianceSignature)(
                    double,
                    double,
                    double,
                    double) const;

    // qlAbcdFunctionInstantaneousCovariance

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::AbcdFunction,
                    double,
                    double,
                    double>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::arg<1>,
                    boost::_bi::value<double>,
                    boost::_bi::value<double> > >
                qlAbcdFunctionInstantaneousCovarianceBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionInstantaneousCovarianceSignature)(
                    double,
                    double,
                    double) const;

    // qlAbcdFunctionInstantaneousValue

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf1<
                    double,
                    QuantLib::AbcdFunction,
                    double>,
                boost::_bi::list2<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::arg<1> > >
                qlAbcdFunctionInstantaneousValueBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionInstantaneousValueSignature)(
                    double) const;

    // qlAbcdFunctionInstantaneousVariance

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf2<
                    double,
                    QuantLib::AbcdFunction,
                    double,
                    double>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::arg<1>,
                    boost::_bi::value<double> > >
                qlAbcdFunctionInstantaneousVarianceBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionInstantaneousVarianceSignature)(
                    double,
                    double) const;

    // qlAbcdFunctionInstantaneousVolatility

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf2<
                    double,
                    QuantLib::AbcdFunction,
                    double,
                    double>,
                boost::_bi::list3<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::arg<1>,
                    boost::_bi::value<double> > >
                qlAbcdFunctionInstantaneousVolatilityBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionInstantaneousVolatilitySignature)(
                    double,
                    double) const;

    // qlAbcdFunctionVariance

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::AbcdFunction,
                    double,
                    double,
                    double>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::_bi::value<double>,
                    boost::arg<1>,
                    boost::_bi::value<double> > >
                qlAbcdFunctionVarianceBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionVarianceSignature)(
                    double,
                    double,
                    double) const;

    // qlAbcdFunctionVolatility

    typedef     boost::_bi::bind_t<
                double,
                boost::_mfi::cmf3<
                    double,
                    QuantLib::AbcdFunction,
                    double,
                    double,
                    double>,
                boost::_bi::list4<
                    boost::_bi::value<boost::shared_ptr<QuantLib::AbcdFunction> >,
                    boost::_bi::value<double>,
                    boost::arg<1>,
                    boost::_bi::value<double> > >
                qlAbcdFunctionVolatilityBind;

    typedef     double 
                (QuantLib::AbcdFunction::* qlAbcdFunctionVolatilitySignature)(
                    double,
                    double,
                    double) const;

}

