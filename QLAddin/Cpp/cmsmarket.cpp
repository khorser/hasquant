
/*  
 Copyright (C) 2007 Ferdinando Ametrano
 Copyright (C) 2006 Giorgio Facchinetti
 
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
#include <qlo/quote.hpp>
#include <qlo/cmsmarket.hpp>
#include <qlo/conundrumpricer.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/termstructures.hpp>
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/indexes/iborindex.hpp>
#include <ql/indexes/swapindex.hpp>
#include <qlo/valueobjects/vo_cmsmarket.hpp>

#include <qlo/conversions/all.hpp>
#include <oh/property.hpp>

namespace QuantLibAddinCpp {

    std::string qlCmsMarket(
            const std::string &ObjectId,
            const std::vector<ObjectHandler::property_t>& SwapLengths,
            const std::vector<std::string>& SwapIndexes,
            const std::string &IborIndex,
            const std::vector<std::vector <ObjectHandler::property_t> >& BidAskSpreads,
            const std::vector<std::string>& CmsCouponPricers,
            const std::string &YieldCurve,
            const ObjectHandler::property_t &Permanent,
            const ObjectHandler::property_t &Trigger,
            const bool &Overwrite) {

        try {

        // convert input datatypes to C++ datatypes

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            Permanent, "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        std::vector<QuantLib::Period> SwapLengthsLib =
            ObjectHandler::vector::convert2<QuantLib::Period>(SwapLengths, "SwapLengths");

        // convert object IDs into library objects

        std::vector<boost::shared_ptr<QuantLib::SwapIndex> > SwapIndexesLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::SwapIndex, QuantLib::SwapIndex>(SwapIndexes);

        OH_GET_REFERENCE(IborIndexLibObjPtr, IborIndex,
            QuantLibAddin::IborIndex, QuantLib::IborIndex)

        std::vector<std::vector<QuantLib::Handle<QuantLib::Quote> > > BidAskSpreadsLibObj =
            ObjectHandler::matrix::convert2<QuantLib::Handle<QuantLib::Quote> >(BidAskSpreads, "BidAskSpreads");

        std::vector<boost::shared_ptr<QuantLib::CmsCouponPricer> > CmsCouponPricersLibObjPtr =
            ObjectHandler::getLibraryObjectVector<QuantLibAddin::CmsCouponPricer, QuantLib::CmsCouponPricer>(CmsCouponPricers);

        OH_GET_OBJECT(YieldCurveCoerce, YieldCurve, ObjectHandler::Object)
        QuantLib::Handle<QuantLib::YieldTermStructure> YieldCurveLibObj =
            QuantLibAddin::CoerceHandle<
                QuantLibAddin::YieldTermStructure,
                QuantLib::YieldTermStructure>()(
                    YieldCurveCoerce);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCmsMarket(
                ObjectId,
                SwapLengths,
                SwapIndexes,
                IborIndex,
                BidAskSpreads,
                CmsCouponPricers,
                YieldCurve,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CmsMarket(
                valueObject,
                SwapLengthsLib,
                SwapIndexesLibObjPtr,
                IborIndexLibObjPtr,
                BidAskSpreadsLibObj,
                CmsCouponPricersLibObjPtr,
                YieldCurveLibObj,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::Repository::instance().storeObject(ObjectId, object, Overwrite);

        // Convert and return the return value

        return returnValue;

        } catch (const std::exception &e) {
            OH_FAIL("Error in function qlCmsMarket : " << e.what());
        }
    }

}

