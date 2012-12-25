
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

#ifndef qlo_vo_overnightindexedswap_hpp
#define qlo_vo_overnightindexedswap_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlMakeDatedOIS : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMakeDatedOIS() {}
        qlMakeDatedOIS(
            const std::string& ObjectId,
            const ObjectHandler::property_t& StartDate,
            const ObjectHandler::property_t& EndDate,
            const std::string& OvernightIndex,
            double FixedRate,
            const std::string& FixDayCounter,
            double Spread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t StartDate_;
        ObjectHandler::property_t EndDate_;
        std::string OvernightIndex_;
        double FixedRate_;
        std::string FixDayCounter_;
        double Spread_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMakeDatedOIS, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("StartDate", StartDate_)
                & boost::serialization::make_nvp("EndDate", EndDate_)
                & boost::serialization::make_nvp("OvernightIndex", OvernightIndex_)
                & boost::serialization::make_nvp("FixedRate", FixedRate_)
                & boost::serialization::make_nvp("FixDayCounter", FixDayCounter_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlMakeOIS : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlMakeOIS() {}
        qlMakeOIS(
            const std::string& ObjectId,
            const std::string& SwapTenor,
            const std::string& OvernightIndex,
            double FixedRate,
            const std::string& ForwardStart,
            const std::string& FixDayCounter,
            double Spread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string SwapTenor_;
        std::string OvernightIndex_;
        double FixedRate_;
        std::string ForwardStart_;
        std::string FixDayCounter_;
        double Spread_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlMakeOIS, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("OvernightIndex", OvernightIndex_)
                & boost::serialization::make_nvp("FixedRate", FixedRate_)
                & boost::serialization::make_nvp("ForwardStart", ForwardStart_)
                & boost::serialization::make_nvp("FixDayCounter", FixDayCounter_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlOvernightIndexedSwap : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlOvernightIndexedSwap() {}
        qlOvernightIndexedSwap(
            const std::string& ObjectId,
            const std::string& PayerReceiver,
            const std::vector<double>& Nominal,
            const std::string& Schedule,
            double FixedRate,
            const std::string& FixDayCounter,
            const std::string& OvernightIndex,
            double Spread,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string PayerReceiver_;
        std::vector<double> Nominal_;
        std::string Schedule_;
        double FixedRate_;
        std::string FixDayCounter_;
        std::string OvernightIndex_;
        double Spread_;
        bool Permanent_;
        virtual std::string processorName() { return "InstrumentProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlOvernightIndexedSwap, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("PayerReceiver", PayerReceiver_)
                & boost::serialization::make_nvp("Nominal", Nominal_)
                & boost::serialization::make_nvp("Schedule", Schedule_)
                & boost::serialization::make_nvp("FixedRate", FixedRate_)
                & boost::serialization::make_nvp("FixDayCounter", FixDayCounter_)
                & boost::serialization::make_nvp("OvernightIndex", OvernightIndex_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlOvernightIndexedSwapFromOISRateHelper : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlOvernightIndexedSwapFromOISRateHelper() {}
        qlOvernightIndexedSwapFromOISRateHelper(
            const std::string& ObjectId,
            const std::string& OISRateHelper,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string OISRateHelper_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlOvernightIndexedSwapFromOISRateHelper, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("OISRateHelper", OISRateHelper_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

