
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

    // qlCalendarAdjust

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf2<
                    QuantLib::Date,
                    QuantLib::Calendar,
                    const QuantLib::Date&,
                    QuantLib::BusinessDayConvention>,
                boost::_bi::list3<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::BusinessDayConvention> > >
                qlCalendarAdjustBind;

    typedef     QuantLib::Date 
                (QuantLib::Calendar::* qlCalendarAdjustSignature)(
                    const QuantLib::Date&,
                    QuantLib::BusinessDayConvention) const;

    // qlCalendarAdvance

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf4<
                    QuantLib::Date,
                    QuantLib::Calendar,
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    QuantLib::BusinessDayConvention,
                    bool>,
                boost::_bi::list5<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::_bi::value<QuantLib::Date>,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::BusinessDayConvention>,
                    boost::_bi::value<bool> > >
                qlCalendarAdvanceBind;

    typedef     QuantLib::Date 
                (QuantLib::Calendar::* qlCalendarAdvanceSignature)(
                    const QuantLib::Date&,
                    const QuantLib::Period&,
                    QuantLib::BusinessDayConvention,
                    bool) const;

    // qlCalendarBusinessDaysBetween

    typedef     boost::_bi::bind_t<
                long,
                boost::_mfi::cmf4<
                    long,
                    QuantLib::Calendar,
                    const QuantLib::Date&,
                    const QuantLib::Date&,
                    const bool&,
                    const bool&>,
                boost::_bi::list5<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::arg<1>,
                    boost::_bi::value<QuantLib::Date>,
                    boost::_bi::value<bool>,
                    boost::_bi::value<bool> > >
                qlCalendarBusinessDaysBetweenBind;

    typedef     long 
                (QuantLib::Calendar::* qlCalendarBusinessDaysBetweenSignature)(
                    const QuantLib::Date&,
                    const QuantLib::Date&,
                    const bool&,
                    const bool&) const;

    // qlCalendarEndOfMonth

    typedef     boost::_bi::bind_t<
                QuantLib::Date,
                boost::_mfi::cmf1<
                    QuantLib::Date,
                    QuantLib::Calendar,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::arg<1> > >
                qlCalendarEndOfMonthBind;

    typedef     QuantLib::Date 
                (QuantLib::Calendar::* qlCalendarEndOfMonthSignature)(
                    const QuantLib::Date&) const;

    // qlCalendarIsBusinessDay

    typedef     boost::_bi::bind_t<
                bool,
                boost::_mfi::cmf1<
                    bool,
                    QuantLib::Calendar,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::arg<1> > >
                qlCalendarIsBusinessDayBind;

    typedef     bool 
                (QuantLib::Calendar::* qlCalendarIsBusinessDaySignature)(
                    const QuantLib::Date&) const;

    // qlCalendarIsEndOfMonth

    typedef     boost::_bi::bind_t<
                bool,
                boost::_mfi::cmf1<
                    bool,
                    QuantLib::Calendar,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::arg<1> > >
                qlCalendarIsEndOfMonthBind;

    typedef     bool 
                (QuantLib::Calendar::* qlCalendarIsEndOfMonthSignature)(
                    const QuantLib::Date&) const;

    // qlCalendarIsHoliday

    typedef     boost::_bi::bind_t<
                bool,
                boost::_mfi::cmf1<
                    bool,
                    QuantLib::Calendar,
                    const QuantLib::Date&>,
                boost::_bi::list2<
                    boost::_bi::value<QuantLib::Calendar >,
                    boost::arg<1> > >
                qlCalendarIsHolidayBind;

    typedef     bool 
                (QuantLib::Calendar::* qlCalendarIsHolidaySignature)(
                    const QuantLib::Date&) const;

}

