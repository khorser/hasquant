
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

#ifndef qlo_vo_capletvolstructure_hpp
#define qlo_vo_capletvolstructure_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCapFloorTermVolCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCapFloorTermVolCurve() {}
        qlCapFloorTermVolCurve(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& Volatilities,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        long SettlementDays_;
        std::string Calendar_;
        std::string BusinessDayConvention_;
        std::vector<ObjectHandler::property_t> OptionTenors_;
        std::vector<ObjectHandler::property_t> Volatilities_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCapFloorTermVolCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BusinessDayConvention", BusinessDayConvention_)
                & boost::serialization::make_nvp("OptionTenors", OptionTenors_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlCapFloorTermVolSurface : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCapFloorTermVolSurface() {}
        qlCapFloorTermVolSurface(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<double>& Strikes,
            const std::vector<std::vector<ObjectHandler::property_t> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        long SettlementDays_;
        std::string Calendar_;
        std::string BusinessDayConvention_;
        std::vector<ObjectHandler::property_t> OptionTenors_;
        std::vector<double> Strikes_;
        std::vector<std::vector<ObjectHandler::property_t> > Volatilities_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCapFloorTermVolSurface, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BusinessDayConvention", BusinessDayConvention_)
                & boost::serialization::make_nvp("OptionTenors", OptionTenors_)
                & boost::serialization::make_nvp("Strikes", Strikes_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlConstantOptionletVolatility : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlConstantOptionletVolatility() {}
        qlConstantOptionletVolatility(
            const std::string& ObjectId,
            long NDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const ObjectHandler::property_t& Volatility,
            const std::string& DayCounter,
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
        std::string BusinessDayConvention_;
        ObjectHandler::property_t Volatility_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlConstantOptionletVolatility, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("NDays", NDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BusinessDayConvention", BusinessDayConvention_)
                & boost::serialization::make_nvp("Volatility", Volatility_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlOptionletStripper1 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlOptionletStripper1() {}
        qlOptionletStripper1(
            const std::string& ObjectId,
            const std::string& TermVolSurface,
            const std::string& IborIndex,
            double SwitchStrike,
            double Accuracy,
            long MaxIter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string TermVolSurface_;
        std::string IborIndex_;
        double SwitchStrike_;
        double Accuracy_;
        long MaxIter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlOptionletStripper1, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("TermVolSurface", TermVolSurface_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("SwitchStrike", SwitchStrike_)
                & boost::serialization::make_nvp("Accuracy", Accuracy_)
                & boost::serialization::make_nvp("MaxIter", MaxIter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlOptionletStripper2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlOptionletStripper2() {}
        qlOptionletStripper2(
            const std::string& ObjectId,
            const std::string& OptionletStripper1,
            const std::string& TermVolCurve,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string OptionletStripper1_;
        std::string TermVolCurve_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlOptionletStripper2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OptionletStripper1", OptionletStripper1_)
                & boost::serialization::make_nvp("TermVolCurve", TermVolCurve_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlRelinkableHandleOptionletVolatilityStructure : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRelinkableHandleOptionletVolatilityStructure() {}
        qlRelinkableHandleOptionletVolatilityStructure(
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
        boost::serialization::void_cast_register<qlRelinkableHandleOptionletVolatilityStructure, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurrentLink", CurrentLink_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSpreadedOptionletVolatility : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSpreadedOptionletVolatility() {}
        qlSpreadedOptionletVolatility(
            const std::string& ObjectId,
            const std::string& BaseVolStructure,
            const ObjectHandler::property_t& Spread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string BaseVolStructure_;
        ObjectHandler::property_t Spread_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSpreadedOptionletVolatility, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BaseVolStructure", BaseVolStructure_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlStrippedOptionlet : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlStrippedOptionlet() {}
        qlStrippedOptionlet(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::string& IborIndex,
            const std::vector<ObjectHandler::property_t>& OptionletDates,
            const std::vector<double>& Strikes,
            const std::vector<std::vector<ObjectHandler::property_t> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        long SettlementDays_;
        std::string Calendar_;
        std::string BusinessDayConvention_;
        std::string IborIndex_;
        std::vector<ObjectHandler::property_t> OptionletDates_;
        std::vector<double> Strikes_;
        std::vector<std::vector<ObjectHandler::property_t> > Volatilities_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlStrippedOptionlet, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BusinessDayConvention", BusinessDayConvention_)
                & boost::serialization::make_nvp("IborIndex", IborIndex_)
                & boost::serialization::make_nvp("OptionletDates", OptionletDates_)
                & boost::serialization::make_nvp("Strikes", Strikes_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlStrippedOptionletAdapter : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlStrippedOptionletAdapter() {}
        qlStrippedOptionletAdapter(
            const std::string& ObjectId,
            const std::string& StrippedOptionletBase,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string StrippedOptionletBase_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlStrippedOptionletAdapter, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("StrippedOptionletBase", StrippedOptionletBase_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

