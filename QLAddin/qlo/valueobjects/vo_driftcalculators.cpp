
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
#include <qlo/driftcalculators.hpp>
#include <qlo/valueobjects/vo_driftcalculators.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlCMSMMDriftCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Pseudo_square_root",
        "Displacements",
        "Taus",
        "Numeraire",
        "Alive",
        "SpanningFwds",
        "Permanent"
    };

    std::set<std::string> qlCMSMMDriftCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlCMSMMDriftCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlCMSMMDriftCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlCMSMMDriftCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            return Pseudo_square_root_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            return Displacements_;
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            return Taus_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            return Numeraire_;
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            return Alive_;
        else if(strcmp(nameUpper.c_str(), "SPANNINGFWDS")==0)
            return SpanningFwds_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlCMSMMDriftCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            Pseudo_square_root_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            Displacements_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            Taus_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            Numeraire_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            Alive_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "SPANNINGFWDS")==0)
            SpanningFwds_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlCMSMMDriftCalculator::qlCMSMMDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Displacements,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            long SpanningFwds,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlCMSMMDriftCalculator", Permanent),
        Pseudo_square_root_(Pseudo_square_root),
        Displacements_(Displacements),
        Taus_(Taus),
        Numeraire_(Numeraire),
        Alive_(Alive),
        SpanningFwds_(SpanningFwds),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlLMMDriftCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Pseudo_square_root",
        "Displacements",
        "Taus",
        "Numeraire",
        "Alive",
        "Permanent"
    };

    std::set<std::string> qlLMMDriftCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLMMDriftCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLMMDriftCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLMMDriftCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            return Pseudo_square_root_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            return Displacements_;
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            return Taus_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            return Numeraire_;
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            return Alive_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLMMDriftCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            Pseudo_square_root_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            Displacements_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            Taus_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            Numeraire_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            Alive_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLMMDriftCalculator::qlLMMDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Displacements,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLMMDriftCalculator", Permanent),
        Pseudo_square_root_(Pseudo_square_root),
        Displacements_(Displacements),
        Taus_(Taus),
        Numeraire_(Numeraire),
        Alive_(Alive),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlLMMNormalDriftCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Pseudo_square_root",
        "Taus",
        "Numeraire",
        "Alive",
        "Permanent"
    };

    std::set<std::string> qlLMMNormalDriftCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLMMNormalDriftCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLMMNormalDriftCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLMMNormalDriftCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            return Pseudo_square_root_;
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            return Taus_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            return Numeraire_;
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            return Alive_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLMMNormalDriftCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            Pseudo_square_root_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            Taus_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            Numeraire_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            Alive_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLMMNormalDriftCalculator::qlLMMNormalDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLMMNormalDriftCalculator", Permanent),
        Pseudo_square_root_(Pseudo_square_root),
        Taus_(Taus),
        Numeraire_(Numeraire),
        Alive_(Alive),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlSMMDriftCalculator::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Pseudo_square_root",
        "Displacements",
        "Taus",
        "Numeraire",
        "Alive",
        "Permanent"
    };

    std::set<std::string> qlSMMDriftCalculator::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSMMDriftCalculator::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSMMDriftCalculator::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSMMDriftCalculator::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            return Pseudo_square_root_;
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            return Displacements_;
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            return Taus_;
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            return Numeraire_;
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            return Alive_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSMMDriftCalculator::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PSEUDO_SQUARE_ROOT")==0)
            Pseudo_square_root_ = ObjectHandler::matrix::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "DISPLACEMENTS")==0)
            Displacements_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "TAUS")==0)
            Taus_ = ObjectHandler::vector::convert2<double>(value, nameUpper);
        else if(strcmp(nameUpper.c_str(), "NUMERAIRE")==0)
            Numeraire_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ALIVE")==0)
            Alive_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSMMDriftCalculator::qlSMMDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Displacements,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSMMDriftCalculator", Permanent),
        Pseudo_square_root_(Pseudo_square_root),
        Displacements_(Displacements),
        Taus_(Taus),
        Numeraire_(Numeraire),
        Alive_(Alive),
        Permanent_(Permanent) {
                  

            
    }

 } }
