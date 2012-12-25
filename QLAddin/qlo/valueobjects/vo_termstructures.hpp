
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

#ifndef qlo_vo_termstructures_hpp
#define qlo_vo_termstructures_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlDiscountCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlDiscountCurve() {}
        qlDiscountCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveDiscounts,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<ObjectHandler::property_t> CurveDates_;
        std::vector<double> CurveDiscounts_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlDiscountCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurveDates", CurveDates_)
                & boost::serialization::make_nvp("CurveDiscounts", CurveDiscounts_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlFlatForward : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlFlatForward() {}
        qlFlatForward(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const ObjectHandler::property_t& Rate,
            const std::string& DayCounter,
            const std::string& Compounding,
            const std::string& Frequency,
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
        ObjectHandler::property_t Rate_;
        std::string DayCounter_;
        std::string Compounding_;
        std::string Frequency_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlFlatForward, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("NDays", NDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("Rate", Rate_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Compounding", Compounding_)
                & boost::serialization::make_nvp("Frequency", Frequency_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlForwardCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlForwardCurve() {}
        qlForwardCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& ForwardYields,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<ObjectHandler::property_t> CurveDates_;
        std::vector<double> ForwardYields_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlForwardCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurveDates", CurveDates_)
                & boost::serialization::make_nvp("ForwardYields", ForwardYields_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlForwardSpreadedTermStructure : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlForwardSpreadedTermStructure() {}
        qlForwardSpreadedTermStructure(
            const std::string& ObjectId,
            const std::string& BaseYieldCurve,
            const ObjectHandler::property_t& Spread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string BaseYieldCurve_;
        ObjectHandler::property_t Spread_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlForwardSpreadedTermStructure, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BaseYieldCurve", BaseYieldCurve_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlImpliedTermStructure : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlImpliedTermStructure() {}
        qlImpliedTermStructure(
            const std::string& ObjectId,
            const std::string& BaseYieldCurve,
            const ObjectHandler::property_t& ReferenceDate,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string BaseYieldCurve_;
        ObjectHandler::property_t ReferenceDate_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlImpliedTermStructure, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BaseYieldCurve", BaseYieldCurve_)
                & boost::serialization::make_nvp("ReferenceDate", ReferenceDate_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlInterpolatedYieldCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlInterpolatedYieldCurve() {}
        qlInterpolatedYieldCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& Dates,
            const std::vector<double>& Data,
            const std::string& Calendar,
            const std::string& DayCounter,
            const std::vector<ObjectHandler::property_t>& Jumps,
            const std::vector<ObjectHandler::property_t>& JumpDates,
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

        std::vector<ObjectHandler::property_t> Dates_;
        std::vector<double> Data_;
        std::string Calendar_;
        std::string DayCounter_;
        std::vector<ObjectHandler::property_t> Jumps_;
        std::vector<ObjectHandler::property_t> JumpDates_;
        std::string TraitsID_;
        std::string InterpolatorID_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlInterpolatedYieldCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Dates", Dates_)
                & boost::serialization::make_nvp("Data", Data_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Jumps", Jumps_)
                & boost::serialization::make_nvp("JumpDates", JumpDates_)
                & boost::serialization::make_nvp("TraitsID", TraitsID_)
                & boost::serialization::make_nvp("InterpolatorID", InterpolatorID_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRelinkableHandleYieldTermStructure : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRelinkableHandleYieldTermStructure() {}
        qlRelinkableHandleYieldTermStructure(
            const std::string& ObjectId,
            const std::string& CurrentLink,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string CurrentLink_;
        bool Permanent_;
        virtual std::string processorName() { return "RelinkableHandleProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlRelinkableHandleYieldTermStructure, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurrentLink", CurrentLink_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlZeroCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlZeroCurve() {}
        qlZeroCurve(
            const std::string& ObjectId,
            const std::vector<ObjectHandler::property_t>& CurveDates,
            const std::vector<double>& CurveYields,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<ObjectHandler::property_t> CurveDates_;
        std::vector<double> CurveYields_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlZeroCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurveDates", CurveDates_)
                & boost::serialization::make_nvp("CurveYields", CurveYields_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

