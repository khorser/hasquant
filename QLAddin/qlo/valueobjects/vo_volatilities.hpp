
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

#ifndef qlo_vo_volatilities_hpp
#define qlo_vo_volatilities_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlAbcdAtmVolCurve : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlAbcdAtmVolCurve() {}
        qlAbcdAtmVolCurve(
            const std::string& ObjectId,
            long SettlementDays,
            const std::string& Calendar,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& VolatilitiesQuotes,
            const std::vector<bool>& InclusionInInterpolation,
            const std::string& Convention,
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
        std::vector<ObjectHandler::property_t> OptionTenors_;
        std::vector<ObjectHandler::property_t> VolatilitiesQuotes_;
        std::vector<bool> InclusionInInterpolation_;
        std::string Convention_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlAbcdAtmVolCurve, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SettlementDays", SettlementDays_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("OptionTenors", OptionTenors_)
                & boost::serialization::make_nvp("VolatilitiesQuotes", VolatilitiesQuotes_)
                & boost::serialization::make_nvp("InclusionInInterpolation", InclusionInInterpolation_)
                & boost::serialization::make_nvp("Convention", Convention_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackConstantVol : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackConstantVol() {}
        qlBlackConstantVol(
            const std::string& ObjectId,
            const ObjectHandler::property_t& SettlementDate,
            const std::string& Calendar,
            double Volatility,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t SettlementDate_;
        std::string Calendar_;
        double Volatility_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackConstantVol, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SettlementDate", SettlementDate_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("Volatility", Volatility_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlBlackVarianceSurface : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlBlackVarianceSurface() {}
        qlBlackVarianceSurface(
            const std::string& ObjectId,
            const ObjectHandler::property_t& SettlementDate,
            const std::string& Calendar,
            const std::vector<ObjectHandler::property_t>& Dates,
            const std::vector<double>& Strikes,
            const std::vector<std::vector<double> >& Volatilities,
            const std::string& DayCounter,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        ObjectHandler::property_t SettlementDate_;
        std::string Calendar_;
        std::vector<ObjectHandler::property_t> Dates_;
        std::vector<double> Strikes_;
        std::vector<std::vector <double> > Volatilities_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlBlackVarianceSurface, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("SettlementDate", SettlementDate_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("Dates", Dates_)
                & boost::serialization::make_nvp("Strikes", Strikes_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSabrVolSurface : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSabrVolSurface() {}
        qlSabrVolSurface(
            const std::string& ObjectId,
            const std::string& InterestRateIndex,
            const std::string& BlackAtmVolCurve,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<double>& AtmRateSpreads,
            const std::vector<std::vector<ObjectHandler::property_t> >& VolatilitiesQuotes,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string InterestRateIndex_;
        std::string BlackAtmVolCurve_;
        std::vector<ObjectHandler::property_t> OptionTenors_;
        std::vector<double> AtmRateSpreads_;
        std::vector<std::vector<ObjectHandler::property_t> > VolatilitiesQuotes_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSabrVolSurface, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("InterestRateIndex", InterestRateIndex_)
                & boost::serialization::make_nvp("BlackAtmVolCurve", BlackAtmVolCurve_)
                & boost::serialization::make_nvp("OptionTenors", OptionTenors_)
                & boost::serialization::make_nvp("AtmRateSpreads", AtmRateSpreads_)
                & boost::serialization::make_nvp("VolatilitiesQuotes", VolatilitiesQuotes_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

