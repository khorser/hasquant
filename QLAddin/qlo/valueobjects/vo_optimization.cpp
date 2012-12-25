
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
#include <qlo/optimization.hpp>
#include <qlo/valueobjects/vo_optimization.hpp>
#include <string>

namespace QuantLibAddin { namespace ValueObjects {

    const char* qlArmijoLineSearch::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Epsilon",
        "Alpha",
        "Beta",
        "Permanent"
    };

    std::set<std::string> qlArmijoLineSearch::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlArmijoLineSearch::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlArmijoLineSearch::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlArmijoLineSearch::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EPSILON")==0)
            return Epsilon_;
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            return Alpha_;
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            return Beta_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlArmijoLineSearch::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EPSILON")==0)
            Epsilon_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "ALPHA")==0)
            Alpha_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "BETA")==0)
            Beta_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlArmijoLineSearch::qlArmijoLineSearch(
            const std::string& ObjectId,
            double Epsilon,
            double Alpha,
            double Beta,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlArmijoLineSearch", Permanent),
        Epsilon_(Epsilon),
        Alpha_(Alpha),
        Beta_(Beta),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlConjugateGradient::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "LineSearch",
        "Permanent"
    };

    std::set<std::string> qlConjugateGradient::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlConjugateGradient::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlConjugateGradient::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlConjugateGradient::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "LINESEARCH")==0)
            return LineSearch_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlConjugateGradient::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LINESEARCH")==0)
            LineSearch_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlConjugateGradient::qlConjugateGradient(
            const std::string& ObjectId,
            const std::string& LineSearch,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlConjugateGradient", Permanent),
        LineSearch_(LineSearch),
        Permanent_(Permanent) {
                  
            processPrecedentID(LineSearch);
            
    }

    const char* qlEndCriteria::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "MaxIterations",
        "MaxStationaryStateIterations",
        "RootEpsilon",
        "FunctionEpsilon",
        "GradientNormEpsilon",
        "Permanent"
    };

    std::set<std::string> qlEndCriteria::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlEndCriteria::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlEndCriteria::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlEndCriteria::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "MAXITERATIONS")==0)
            return MaxIterations_;
        else if(strcmp(nameUpper.c_str(), "MAXSTATIONARYSTATEITERATIONS")==0)
            return MaxStationaryStateIterations_;
        else if(strcmp(nameUpper.c_str(), "ROOTEPSILON")==0)
            return RootEpsilon_;
        else if(strcmp(nameUpper.c_str(), "FUNCTIONEPSILON")==0)
            return FunctionEpsilon_;
        else if(strcmp(nameUpper.c_str(), "GRADIENTNORMEPSILON")==0)
            return GradientNormEpsilon_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlEndCriteria::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "MAXITERATIONS")==0)
            MaxIterations_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "MAXSTATIONARYSTATEITERATIONS")==0)
            MaxStationaryStateIterations_ = ObjectHandler::convert2<long>(value);
        else if(strcmp(nameUpper.c_str(), "ROOTEPSILON")==0)
            RootEpsilon_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "FUNCTIONEPSILON")==0)
            FunctionEpsilon_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GRADIENTNORMEPSILON")==0)
            GradientNormEpsilon_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlEndCriteria::qlEndCriteria(
            const std::string& ObjectId,
            long MaxIterations,
            long MaxStationaryStateIterations,
            double RootEpsilon,
            double FunctionEpsilon,
            double GradientNormEpsilon,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlEndCriteria", Permanent),
        MaxIterations_(MaxIterations),
        MaxStationaryStateIterations_(MaxStationaryStateIterations),
        RootEpsilon_(RootEpsilon),
        FunctionEpsilon_(FunctionEpsilon),
        GradientNormEpsilon_(GradientNormEpsilon),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlLevenbergMarquardt::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Epsfcn",
        "Xtol",
        "Gtol",
        "Permanent"
    };

    std::set<std::string> qlLevenbergMarquardt::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlLevenbergMarquardt::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlLevenbergMarquardt::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlLevenbergMarquardt::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "EPSFCN")==0)
            return Epsfcn_;
        else if(strcmp(nameUpper.c_str(), "XTOL")==0)
            return Xtol_;
        else if(strcmp(nameUpper.c_str(), "GTOL")==0)
            return Gtol_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlLevenbergMarquardt::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "EPSFCN")==0)
            Epsfcn_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "XTOL")==0)
            Xtol_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "GTOL")==0)
            Gtol_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlLevenbergMarquardt::qlLevenbergMarquardt(
            const std::string& ObjectId,
            double Epsfcn,
            double Xtol,
            double Gtol,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlLevenbergMarquardt", Permanent),
        Epsfcn_(Epsfcn),
        Xtol_(Xtol),
        Gtol_(Gtol),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlSimplex::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "Lambda",
        "Permanent"
    };

    std::set<std::string> qlSimplex::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSimplex::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSimplex::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSimplex::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "LAMBDA")==0)
            return Lambda_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSimplex::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LAMBDA")==0)
            Lambda_ = ObjectHandler::convert2<double>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSimplex::qlSimplex(
            const std::string& ObjectId,
            double Lambda,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSimplex", Permanent),
        Lambda_(Lambda),
        Permanent_(Permanent) {
                  

            
    }

    const char* qlSteepestDescent::mPropertyNames[] = {
        // The two values below are not desired in the return value of ohObjectPropertyNames().
        // For now we just comment them out as this seems not to break anything.
        //"ClassName",
        //"ObjectId",
        "LineSearch",
        "Permanent"
    };

    std::set<std::string> qlSteepestDescent::mSystemPropertyNames(
        mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));

    const std::set<std::string>& qlSteepestDescent::getSystemPropertyNames() const {
        return mSystemPropertyNames;
    }

    std::vector<std::string> qlSteepestDescent::getPropertyNamesVector() const {
        std::vector<std::string> ret(
            mPropertyNames, mPropertyNames + sizeof(mPropertyNames) / sizeof(const char*));
        for (std::map<std::string, ObjectHandler::property_t>::const_iterator i = userProperties.begin();
            i != userProperties.end(); ++i)
            ret.push_back(i->first);
        return ret;
    }

    ObjectHandler::property_t qlSteepestDescent::getSystemProperty(const std::string& name) const {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            return objectId_;
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            return className_;
        else if(strcmp(nameUpper.c_str(), "LINESEARCH")==0)
            return LineSearch_;
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            return Permanent_;
        else
            OH_FAIL("Error: attempt to retrieve non-existent Property: '" + name + "'");
    }

    void qlSteepestDescent::setSystemProperty(const std::string& name, const ObjectHandler::property_t& value) {
        std::string nameUpper = boost::algorithm::to_upper_copy(name);
        if(strcmp(nameUpper.c_str(), "OBJECTID")==0)
            objectId_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "CLASSNAME")==0)
            className_ = boost::get<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "LINESEARCH")==0)
            LineSearch_ = ObjectHandler::convert2<std::string>(value);
        else if(strcmp(nameUpper.c_str(), "PERMANENT")==0)
            Permanent_ = ObjectHandler::convert2<bool>(value);
        else
            OH_FAIL("Error: attempt to set non-existent Property: '" + name + "'");
    }

    qlSteepestDescent::qlSteepestDescent(
            const std::string& ObjectId,
            const std::string& LineSearch,
            bool Permanent) :
        ObjectHandler::ValueObject(ObjectId, "qlSteepestDescent", Permanent),
        LineSearch_(LineSearch),
        Permanent_(Permanent) {
                  
            processPrecedentID(LineSearch);
            
    }

 } }
