
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

#ifndef qlo_vo_driftcalculators_hpp
#define qlo_vo_driftcalculators_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlCMSMMDriftCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlCMSMMDriftCalculator() {}
        qlCMSMMDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Displacements,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            long SpanningFwds,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Pseudo_square_root_;
        std::vector<double> Displacements_;
        std::vector<double> Taus_;
        long Numeraire_;
        long Alive_;
        long SpanningFwds_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlCMSMMDriftCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Pseudo_square_root", Pseudo_square_root_)
                & boost::serialization::make_nvp("Displacements", Displacements_)
                & boost::serialization::make_nvp("Taus", Taus_)
                & boost::serialization::make_nvp("Numeraire", Numeraire_)
                & boost::serialization::make_nvp("Alive", Alive_)
                & boost::serialization::make_nvp("SpanningFwds", SpanningFwds_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLMMDriftCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLMMDriftCalculator() {}
        qlLMMDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Displacements,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Pseudo_square_root_;
        std::vector<double> Displacements_;
        std::vector<double> Taus_;
        long Numeraire_;
        long Alive_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLMMDriftCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Pseudo_square_root", Pseudo_square_root_)
                & boost::serialization::make_nvp("Displacements", Displacements_)
                & boost::serialization::make_nvp("Taus", Taus_)
                & boost::serialization::make_nvp("Numeraire", Numeraire_)
                & boost::serialization::make_nvp("Alive", Alive_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlLMMNormalDriftCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlLMMNormalDriftCalculator() {}
        qlLMMNormalDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Pseudo_square_root_;
        std::vector<double> Taus_;
        long Numeraire_;
        long Alive_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlLMMNormalDriftCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Pseudo_square_root", Pseudo_square_root_)
                & boost::serialization::make_nvp("Taus", Taus_)
                & boost::serialization::make_nvp("Numeraire", Numeraire_)
                & boost::serialization::make_nvp("Alive", Alive_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSMMDriftCalculator : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSMMDriftCalculator() {}
        qlSMMDriftCalculator(
            const std::string& ObjectId,
            const std::vector<std::vector<double> >& Pseudo_square_root,
            const std::vector<double>& Displacements,
            const std::vector<double>& Taus,
            long Numeraire,
            long Alive,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::vector<std::vector <double> > Pseudo_square_root_;
        std::vector<double> Displacements_;
        std::vector<double> Taus_;
        long Numeraire_;
        long Alive_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSMMDriftCalculator, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Pseudo_square_root", Pseudo_square_root_)
                & boost::serialization::make_nvp("Displacements", Displacements_)
                & boost::serialization::make_nvp("Taus", Taus_)
                & boost::serialization::make_nvp("Numeraire", Numeraire_)
                & boost::serialization::make_nvp("Alive", Alive_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

