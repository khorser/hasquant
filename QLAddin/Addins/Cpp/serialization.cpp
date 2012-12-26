
/*  
 Copyright (C) 2007 Eric Ehlers
 Copyright (C) 2006 Plamen Neykov
 
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
//      QuantLibAddin/gensrc/stubs/stub.cpp.body

#include <qlo/qladdindefines.hpp>
#include <qlo/handle.hpp>
#include <oh/serializationfactory.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::vector<std::string> ohObjectLoad(
            const std::string &Directory,
            const ObjectHandler::property_t &Pattern,
            const ObjectHandler::property_t &Recurse,
            const ObjectHandler::property_t &Overwrite,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        std::string PatternCpp = ObjectHandler::convert2<std::string>(
            Pattern, "Pattern", ".*\\.xml");

        bool RecurseCpp = ObjectHandler::convert2<bool>(
            Recurse, "Recurse", false);

        bool OverwriteCpp = ObjectHandler::convert2<bool>(
            Overwrite, "Overwrite", false);

        // invoke the utility function

        std::vector<std::string> returnValue = ObjectHandler::SerializationFactory::instance().loadObject(
                Directory,
                PatternCpp,
                RecurseCpp,
                OverwriteCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohObjectLoad : " << e.what());
        }
    }


    std::vector<std::string> ohObjectLoadString(
            const std::string &Xml,
            const ObjectHandler::property_t &Overwrite,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        bool OverwriteCpp = ObjectHandler::convert2<bool>(
            Overwrite, "Overwrite", false);

        // invoke the utility function

        std::vector<std::string> returnValue = ObjectHandler::SerializationFactory::instance().loadObjectString(
                Xml,
                OverwriteCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohObjectLoadString : " << e.what());
        }
    }


    long ohObjectSave(
            const std::vector<std::string>& ObjectList,
            const std::string &Filename,
            const ObjectHandler::property_t &Overwrite,
            const ObjectHandler::property_t &IncludeGroups,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        bool OverwriteCpp = ObjectHandler::convert2<bool>(
            Overwrite, "Overwrite", false);

        bool IncludeGroupsCpp = ObjectHandler::convert2<bool>(
            IncludeGroups, "IncludeGroups", true);

        // invoke the utility function

        long returnValue = ObjectHandler::SerializationFactory::instance().saveObject(
                ObjectList,
                Filename,
                OverwriteCpp,
                IncludeGroupsCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohObjectSave : " << e.what());
        }
    }


    std::string ohObjectSaveString(
            const std::vector<std::string>& ObjectList,
            const ObjectHandler::property_t &Overwrite,
            const ObjectHandler::property_t &Trigger) {

        try {

        // convert input datatypes to C++ datatypes

        bool OverwriteCpp = ObjectHandler::convert2<bool>(
            Overwrite, "Overwrite", false);

        // convert input datatypes to Object references

        std::vector<boost::shared_ptr<ObjectHandler::Object> > ObjectListObjPtr =
            ObjectHandler::getObjectVector<ObjectHandler::Object>(ObjectList);

        // invoke the utility function

        std::string returnValue = ObjectHandler::SerializationFactory::instance().saveObjectString(
                ObjectListObjPtr,
                OverwriteCpp);

        // convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function ohObjectSaveString : " << e.what());
        }
    }

}

