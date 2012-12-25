
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

#ifndef qlo_vo_swaptionvolstructure_hpp
#define qlo_vo_swaptionvolstructure_hpp

#include <oh/valueobject.hpp>
#include <string>
#include <vector>
#include <set>
#include <boost/serialization/map.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace QuantLibAddin { namespace ValueObjects {

    class qlConstantSwaptionVolatility : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlConstantSwaptionVolatility() {}
        qlConstantSwaptionVolatility(
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
        boost::serialization::void_cast_register<qlConstantSwaptionVolatility, ObjectHandler::ValueObject>(this, this);
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

    class qlRelinkableHandleSwaptionVolatilityStructure : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlRelinkableHandleSwaptionVolatilityStructure() {}
        qlRelinkableHandleSwaptionVolatilityStructure(
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
        boost::serialization::void_cast_register<qlRelinkableHandleSwaptionVolatilityStructure, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("CurrentLink", CurrentLink_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSmileSectionByCube : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSmileSectionByCube() {}
        qlSmileSectionByCube(
            const std::string& ObjectId,
            const std::string& VolCube,
            const ObjectHandler::property_t& OptionDate,
            const std::string& SwapTenor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string VolCube_;
        ObjectHandler::property_t OptionDate_;
        std::string SwapTenor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSmileSectionByCube, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("VolCube", VolCube_)
                & boost::serialization::make_nvp("OptionDate", OptionDate_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSmileSectionByCube2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSmileSectionByCube2() {}
        qlSmileSectionByCube2(
            const std::string& ObjectId,
            const std::string& VolCube,
            const std::string& OptionDate,
            const std::string& SwapTenor,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string VolCube_;
        std::string OptionDate_;
        std::string SwapTenor_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSmileSectionByCube2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("VolCube", VolCube_)
                & boost::serialization::make_nvp("OptionDate", OptionDate_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSpreadedSwaptionVolatility : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSpreadedSwaptionVolatility() {}
        qlSpreadedSwaptionVolatility(
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
        boost::serialization::void_cast_register<qlSpreadedSwaptionVolatility, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("BaseVolStructure", BaseVolStructure_)
                & boost::serialization::make_nvp("Spread", Spread_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSwaptionVTSMatrix : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSwaptionVTSMatrix() {}
        qlSwaptionVTSMatrix(
            const std::string& ObjectId,
            const std::string& Calendar,
            const std::string& BusinessDayConvention,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& SwapTenors,
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

        std::string Calendar_;
        std::string BusinessDayConvention_;
        std::vector<ObjectHandler::property_t> OptionTenors_;
        std::vector<ObjectHandler::property_t> SwapTenors_;
        std::vector<std::vector<ObjectHandler::property_t> > Volatilities_;
        std::string DayCounter_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSwaptionVTSMatrix, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("Calendar", Calendar_)
                & boost::serialization::make_nvp("BusinessDayConvention", BusinessDayConvention_)
                & boost::serialization::make_nvp("OptionTenors", OptionTenors_)
                & boost::serialization::make_nvp("SwapTenors", SwapTenors_)
                & boost::serialization::make_nvp("Volatilities", Volatilities_)
                & boost::serialization::make_nvp("DayCounter", DayCounter_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSwaptionVolCube1 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSwaptionVolCube1() {}
        qlSwaptionVolCube1(
            const std::string& ObjectId,
            const std::string& AtmVolStructure,
            const std::vector<ObjectHandler::property_t>& OptionTenors,
            const std::vector<ObjectHandler::property_t>& SwapTenors,
            const std::vector<double>& StrikeSpreads,
            const std::vector<std::vector<ObjectHandler::property_t> >& SpreadVols,
            const std::string& SwapIndexBase,
            const std::string& ShortSwapIndexBase,
            bool VegaWeightedSmileFit,
            const std::vector<std::vector<ObjectHandler::property_t> >& Guess,
            const std::vector<bool>& IsFixed,
            bool IsAtmCalibrated,
            const std::string& EndCriteria,
            double MaxErrorTol,
            const std::string& OptMethod,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string AtmVolStructure_;
        std::vector<ObjectHandler::property_t> OptionTenors_;
        std::vector<ObjectHandler::property_t> SwapTenors_;
        std::vector<double> StrikeSpreads_;
        std::vector<std::vector<ObjectHandler::property_t> > SpreadVols_;
        std::string SwapIndexBase_;
        std::string ShortSwapIndexBase_;
        bool VegaWeightedSmileFit_;
        std::vector<std::vector<ObjectHandler::property_t> > Guess_;
        std::vector<bool> IsFixed_;
        bool IsAtmCalibrated_;
        std::string EndCriteria_;
        double MaxErrorTol_;
        std::string OptMethod_;
        bool Permanent_;
        virtual std::string processorName() { return "ExtrapolatorProcessor"; }

        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSwaptionVolCube1, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("AtmVolStructure", AtmVolStructure_)
                & boost::serialization::make_nvp("OptionTenors", OptionTenors_)
                & boost::serialization::make_nvp("SwapTenors", SwapTenors_)
                & boost::serialization::make_nvp("StrikeSpreads", StrikeSpreads_)
                & boost::serialization::make_nvp("SpreadVols", SpreadVols_)
                & boost::serialization::make_nvp("SwapIndexBase", SwapIndexBase_)
                & boost::serialization::make_nvp("ShortSwapIndexBase", ShortSwapIndexBase_)
                & boost::serialization::make_nvp("VegaWeightedSmileFit", VegaWeightedSmileFit_)
                & boost::serialization::make_nvp("Guess", Guess_)
                & boost::serialization::make_nvp("IsFixed", IsFixed_)
                & boost::serialization::make_nvp("IsAtmCalibrated", IsAtmCalibrated_)
                & boost::serialization::make_nvp("EndCriteria", EndCriteria_)
                & boost::serialization::make_nvp("MaxErrorTol", MaxErrorTol_)
                & boost::serialization::make_nvp("OptMethod", OptMethod_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };

    class qlSwaptionVolCube2 : public ObjectHandler::ValueObject {
        friend class boost::serialization::access;
    public:
        qlSwaptionVolCube2() {}
        qlSwaptionVolCube2(
            const std::string& ObjectId,
            const std::string& AtmVolStructure,
            const std::vector<ObjectHandler::property_t>& OptionTenor,
            const std::vector<ObjectHandler::property_t>& SwapTenor,
            const std::vector<double>& StrikeSpreads,
            const std::vector<std::vector<ObjectHandler::property_t> >& SpreadVols,
            const std::string& SwapIndexBase,
            const std::string& ShortSwapIndexBase,
            bool VegaWeightedSmileFit,
            bool Permanent);

        const std::set<std::string>& getSystemPropertyNames() const;
        std::vector<std::string> getPropertyNamesVector() const;
        ObjectHandler::property_t getSystemProperty(const std::string&) const;
        void setSystemProperty(const std::string& name, const ObjectHandler::property_t& value);

    protected:
        static const char* mPropertyNames[];
        static std::set<std::string> mSystemPropertyNames;

        std::string AtmVolStructure_;
        std::vector<ObjectHandler::property_t> OptionTenor_;
        std::vector<ObjectHandler::property_t> SwapTenor_;
        std::vector<double> StrikeSpreads_;
        std::vector<std::vector<ObjectHandler::property_t> > SpreadVols_;
        std::string SwapIndexBase_;
        std::string ShortSwapIndexBase_;
        bool VegaWeightedSmileFit_;
        bool Permanent_;


        template<class Archive>
        void serialize(Archive& ar, const unsigned int) {
        boost::serialization::void_cast_register<qlSwaptionVolCube2, ObjectHandler::ValueObject>(this, this);
            ar  & boost::serialization::make_nvp("ObjectId", objectId_)
                & boost::serialization::make_nvp("ClassName", className_)
                & boost::serialization::make_nvp("AtmVolStructure", AtmVolStructure_)
                & boost::serialization::make_nvp("OptionTenor", OptionTenor_)
                & boost::serialization::make_nvp("SwapTenor", SwapTenor_)
                & boost::serialization::make_nvp("StrikeSpreads", StrikeSpreads_)
                & boost::serialization::make_nvp("SpreadVols", SpreadVols_)
                & boost::serialization::make_nvp("SwapIndexBase", SwapIndexBase_)
                & boost::serialization::make_nvp("ShortSwapIndexBase", ShortSwapIndexBase_)
                & boost::serialization::make_nvp("VegaWeightedSmileFit", VegaWeightedSmileFit_)
                & boost::serialization::make_nvp("Permanent", Permanent_)
                & boost::serialization::make_nvp("UserProperties", userProperties);
        }
    };



} }

#endif

