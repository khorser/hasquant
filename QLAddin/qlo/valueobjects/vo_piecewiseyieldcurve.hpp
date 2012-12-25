
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
//      gensrc/gensrc/stubs/stub.vo.includes.decl

#ifndef qlo_vo_piecewiseyieldcurve_hpp
#define qlo_vo_piecewiseyieldcurve_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlPiecewiseYieldCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlPiecewiseYieldCurve() {}
        qlPiecewiseYieldCurve(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const std::vector<std::string>& RateHelpers,
            const std::string& DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
            double Accuracy,
            const std::string& TraitsID,
            const std::string& InterpolatorID,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        long NDays_;
        std::string Calendar_;
        std::vector<std::string> RateHelpers_;
        std::string DayCounter_;
        std::vector<ObjectHandler::property_t> Jumps_;
        std::vector<ObjectHandler::property_t> JumpDates_;
        double Accuracy_;
        std::string TraitsID_;
        std::string InterpolatorID_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlPiecewiseYieldCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("NDays", NDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("RateHelpers", RateHelpers_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Jumps", Jumps_)
                & boost::serialization::make_nvp("JumpDates", JumpDates_)
                & boost::serialization::make_nvp("Accuracy", Accuracy_)
                & boost::serialization::make_nvp("TraitsID", TraitsID_)
                & boost::serialization::make_nvp("InterpolatorID", InterpolatorID_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

