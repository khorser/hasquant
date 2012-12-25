
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

    // qlDateEndOfMonth

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                QuantLib::Date (__cdecl*)(
                    const QuantLib::Date&),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlDateEndOfMonthBind;



    // qlDateIsEndOfMonth

    typedef     boost::_bi::bind_t<
                bool,
                bool (__cdecl*)(
                    const QuantLib::Date&),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlDateIsEndOfMonthBind;



    // qlDateIsLeap

    typedef     boost::_bi::bind_t<
                bool,
                bool (__cdecl*)(
                    int),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlDateIsLeapBind;



    // qlDateNextWeekday

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                QuantLib::Date (__cdecl*)(
                    const QuantLib::Date&,
                    QuantLib::Weekday),
                boost::_bi::list2<
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Weekday> > >
                qlDateNextWeekdayBind;



    // qlECBIsECBcode

    typedef     boost::_bi::bind_t<
                bool,
                bool (__cdecl*)(
                    const std::string&),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlECBIsECBcodeBind;



    // qlECBIsECBdate

    typedef     boost::_bi::bind_t<
                bool,
                bool (__cdecl*)(
                    const QuantLib::Date&),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlECBIsECBdateBind;



    // qlFrequencyFromPeriod

    typedef     boost::_bi::bind_t<
                QuantLib::Frequency,
                QuantLib::Frequency (__cdecl*)(
                    const QuantLib::Period&),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlFrequencyFromPeriodBind;



    // qlIMMIsIMMcode

    typedef     boost::_bi::bind_t<
                bool,
                bool (__cdecl*)(
                    const std::string&,
                    bool),
                boost::_bi::list2<
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlIMMIsIMMcodeBind;



    // qlIMMIsIMMdate

    typedef     boost::_bi::bind_t<
                bool,
                bool (__cdecl*)(
                    const QuantLib::Date&,
                    bool),
                boost::_bi::list2<
                    boost::arg<1>,
                    boost::_bi::value<bool> > >
                qlIMMIsIMMdateBind;



    // qlIMMcode

    typedef     boost::_bi::bind_t<
                std::string,
                std::string (__cdecl*)(
                    const QuantLib::Date&),
                boost::_bi::list1<
                    boost::arg<1> > >
                qlIMMcodeBind;



    // qlIMMdate

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                QuantLib::Date (__cdecl*)(
                    const std::string&,
                    const QuantLib::Date&),
                boost::_bi::list2<
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Date> > >
                qlIMMdateBind;



}

