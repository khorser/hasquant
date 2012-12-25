
/*  
 Copyright (C) 2005, 2006 Plamen Neykov
 Copyright (C) 2007 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.vo.includes.body

#include <oh/ohdefines.hpp>
#include <qlo/schedule.hpp>
#include <qlo/valueobjects/vo_schedule.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlSchedule::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "EffectiveDate",
        "TerminationDate",
        "Tenor",
        "Calendar",
        "Convention",
        "TermDateConv",
        "GenRule",
        "EndOfMonth",
        "FirstDate",
        "NextToLastDate",
        "Permanent"
    };

    std::set<std::string> qlSchedule::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSchedule::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSchedule::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSchedule::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EFFECTIVEDATE")==0)
            return EffectiveDate_;
        else if(strcmp(nameUpper.c_str(), "TERMINATIONDATE")==0)
            return TerminationDate_;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            return Tenor_;
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            return Calendar_;
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            return Convention_;
        else if(strcmp(nameUpper.c_str(), "TERMDATECONV")==0)
            return TermDateConv_;
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            return GenRule_;
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            return EndOfMonth_;
        else if(strcmp(nameUpper.c_str(), "FIRSTDATE")==0)
            return FirstDate_;
        else if(strcmp(nameUpper.c_str(), "NEXTTOLASTDATE")==0)
            return NextToLastDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSchedule::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EFFECTIVEDATE")==0)
            EffectiveDate_ = value;
        else if(strcmp(nameUpper.c_str(), "TERMINATIONDATE")==0)
            TerminationDate_ = value;
        else if(strcmp(nameUpper.c_str(), "TENOR")==0)
            Tenor_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CALENDAR")==0)
            Calendar_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CONVENTION")==0)
            Convention_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TERMDATECONV")==0)
            TermDateConv_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "GENRULE")==0)
            GenRule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ENDOFMONTH")==0)
            EndOfMonth_ = ObjectHandler::convert2<bool>(value);
        else if(strcmp(nameUpper.c_str(), "FIRSTDATE")==0)
            FirstDate_ = value;
        else if(strcmp(nameUpper.c_str(), "NEXTTOLASTDATE")==0)
            NextToLastDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSchedule::qlSchedule(
            const std::string& ObjectId,
            const ObjectHandler::property_t& EffectiveDate,
            const ObjectHandler::property_t& TerminationDate,
            const std::string& Tenor,
            const std::string& Calendar,
            const std::string& Convention,
            const std::string& TermDateConv,
            const std::string& GenRule,
            bool EndOfMonth,
            const ObjectHandler::property_t& FirstDate,
            const ObjectHandler::property_t& NextToLastDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSchedule", Permanent),
        EffectiveDate_(EffectiveDate),
        TerminationDate_(TerminationDate),
        Tenor_(Tenor),
        Calendar_(Calendar),
        Convention_(Convention),
        TermDateConv_(TermDateConv),
        GenRule_(GenRule),
        EndOfMonth_(EndOfMonth),
        FirstDate_(FirstDate),
        NextToLastDate_(NextToLastDate),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlScheduleFromDateVector::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "EffectiveDate",
        "Permanent"
    };

    std::set<std::string> qlScheduleFromDateVector::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlScheduleFromDateVector::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlScheduleFromDateVector::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlScheduleFromDateVector::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EFFECTIVEDATE")==0)
            return EffectiveDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlScheduleFromDateVector::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EFFECTIVEDATE")==0)
            EffectiveDate_ = ObjectHandler::vector::convert2<ObjectHandler::property_t>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlScheduleFromDateVector::qlScheduleFromDateVector(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& EffectiveDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlScheduleFromDateVector", Permanent),
        EffectiveDate_(EffectiveDate),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlScheduleTruncated::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "OriginalSchedule",
        "TruncationDate",
        "Permanent"
    };

    std::set<std::string> qlScheduleTruncated::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlScheduleTruncated::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlScheduleTruncated::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlScheduleTruncated::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "ORIGINALSCHEDULE")==0)
            return OriginalSchedule_;
        else if(strcmp(nameUpper.c_str(), "TRUNCATIONDATE")==0)
            return TruncationDate_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlScheduleTruncated::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "ORIGINALSCHEDULE")==0)
            OriginalSchedule_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "TRUNCATIONDATE")==0)
            TruncationDate_ = value;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlScheduleTruncated::qlScheduleTruncated(
            const std::string& ObjectId,
            const std::string& OriginalSchedule,
            const ObjectHandler::property_t& TruncationDate,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlScheduleTruncated", Permanent),
        OriginalSchedule_(OriginalSchedule),
        TruncationDate_(TruncationDate),
        Permanent_(Permanent) {
                  
            processPrecedentID(OriginalSchedule);
            
    }

 } }
