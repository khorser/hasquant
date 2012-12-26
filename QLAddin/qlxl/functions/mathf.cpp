
/*  
 Copyright (C) 2006 Ferdinando Ametrano
 
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
//      QuantLibAddin/gensrc/stubs/stub.excel.includes

#include <qlo/qladdindefines.hpp>
#include <oh/enumerations/typefactory.hpp>
#include <ql/math/primenumbers.hpp>
#include <ql/math/matrixutilities/pseudosqrt.hpp>
#include <ql/math/matrixutilities/choleskydecomposition.hpp>
#include <qlo/symmetricschurdecomposition.hpp>
#include <qlo/getcovariance.hpp>
#include <qlo/mathf.hpp>
#include <qlo/valueobjects/vo_mathf.hpp>

#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/callingrange.hpp>
#include <qlxl/session.hpp>
#include <qlxl/conversions/all.hpp>

#define XLL_DEC DLLEXPORT

XLL_DEC OPER *qlCholeskyDecomposition(
        FP *Matrix,
        OPER *Flexible,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCholeskyDecomposition"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > MatrixCpp =
            ObjectHandler::fpToMatrix<double>(*Matrix);

        bool FlexibleCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Flexible), "Flexible", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix MatrixLib =
            QuantLibXL::operToQlMatrix(*Matrix);

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::CholeskyDecomposition(
                MatrixLib,
                FlexibleCpp);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlCovarianceDecomposition(
        char *ObjectId,
        FP *SymmetricMatrix,
        OPER *Tolerance,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCovarianceDecomposition"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > SymmetricMatrixCpp =
            ObjectHandler::fpToMatrix<double>(*SymmetricMatrix);

        double ToleranceCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Tolerance), "Tolerance", 1.0e12);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix SymmetricMatrixLib =
            QuantLibXL::operToQlMatrix(*SymmetricMatrix);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlCovarianceDecomposition(
                ObjectIdStrip,
                SymmetricMatrixCpp,
                ToleranceCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::CovarianceDecomposition(
                valueObject,
                SymmetricMatrixLib,
                ToleranceCpp,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCovarianceDecompositionCorrelationMatrix(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCovarianceDecompositionCorrelationMatrix"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CovarianceDecomposition, QuantLib::CovarianceDecomposition)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->correlationMatrix();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCovarianceDecompositionStandardDeviations(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCovarianceDecompositionStandardDeviations"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CovarianceDecomposition, QuantLib::CovarianceDecomposition)

        // invoke the member function

        QuantLib::Array returnValue = ObjectIdLibObjPtr->standardDeviations();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::vectorToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlCovarianceDecompositionVariances(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlCovarianceDecompositionVariances"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::CovarianceDecomposition, QuantLib::CovarianceDecomposition)

        // invoke the member function

        QuantLib::Array returnValue = ObjectIdLibObjPtr->variances();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::vectorToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlGetCovariance(
        OPER *Vols,
        FP *Matrix,
        OPER *Tolerance,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlGetCovariance"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<double> VolsCpp =
            ObjectHandler::operToVector<double>(*Vols, "Vols");

        std::vector<std::vector<double> > MatrixCpp =
            ObjectHandler::fpToMatrix<double>(*Matrix);

        double ToleranceCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Tolerance), "Tolerance", 1.0e12);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix MatrixLib =
            QuantLibXL::operToQlMatrix(*Matrix);

        // invoke the utility function

        QuantLib::Matrix returnValue = getCovariance(
            VolsCpp.begin(),
            VolsCpp.end(),
                MatrixLib,
                ToleranceCpp);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlNormDist(
        double *X,
        OPER *Mean,
        OPER *Standard_dev,
        OPER *Cumulative,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlNormDist"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double MeanCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Mean), "Mean", 0.0);

        double Standard_devCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Standard_dev), "Standard_dev", 1.0);

        bool CumulativeCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Cumulative), "Cumulative", TRUE);

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLibAddin::normDist(
                *X,
                MeanCpp,
                Standard_devCpp,
                CumulativeCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlNormInv(
        double *Probability,
        OPER *Mean,
        OPER *Standard_dev,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlNormInv"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        double MeanCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Mean), "Mean", 0.0);

        double Standard_devCpp = ObjectHandler::convert2<double>(
            ObjectHandler::ConvertOper(*Standard_dev), "Standard_dev", 1.0);

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLibAddin::normInv(
                *Probability,
                MeanCpp,
                Standard_devCpp);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlNormSDist(
        double *Z,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlNormSDist"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLibAddin::normSDist(
                *Z);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC double *qlNormSInv(
        double *Probability,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlNormSInv"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        static double returnValue;
        returnValue = QuantLibAddin::normSInv(
                *Probability);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC long *qlPrimeNumber(
        long *N,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPrimeNumber"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // invoke the utility function

        static long returnValue;
        returnValue = QuantLib::PrimeNumbers::get(
                *N);

        // convert and return the return value

        return &returnValue;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlPseudoSqrt(
        FP *Matrix,
        char *SalvagingAlgorithm,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlPseudoSqrt"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > MatrixCpp =
            ObjectHandler::fpToMatrix<double>(*Matrix);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix MatrixLib =
            QuantLibXL::operToQlMatrix(*Matrix);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::SalvagingAlgorithm::Type SalvagingAlgorithmEnum =
            ObjectHandler::Create<QuantLib::SalvagingAlgorithm::Type>()(SalvagingAlgorithm);

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::pseudoSqrt(
                MatrixLib,
                SalvagingAlgorithmEnum);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlRankReducedSqrt(
        FP *Matrix,
        long *MaxRank,
        double *ComponentPercentage,
        char *SalvagingAlgorithm,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlRankReducedSqrt"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > MatrixCpp =
            ObjectHandler::fpToMatrix<double>(*Matrix);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix MatrixLib =
            QuantLibXL::operToQlMatrix(*Matrix);

        // convert input datatypes to QuantLib enumerated datatypes

        QuantLib::SalvagingAlgorithm::Type SalvagingAlgorithmEnum =
            ObjectHandler::Create<QuantLib::SalvagingAlgorithm::Type>()(SalvagingAlgorithm);

        // invoke the utility function

        QuantLib::Matrix returnValue = QuantLib::rankReducedSqrt(
                MatrixLib,
                *MaxRank,
                *ComponentPercentage,
                SalvagingAlgorithmEnum);

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC char *qlSymmetricSchurDecomposition(
        char *ObjectId,
        FP *SymmetricMatrix,
        OPER *Permanent,
        OPER *Trigger,
        bool *Overwrite) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSymmetricSchurDecomposition"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert input datatypes to C++ datatypes

        std::vector<std::vector<double> > SymmetricMatrixCpp =
            ObjectHandler::fpToMatrix<double>(*SymmetricMatrix);

        bool PermanentCpp = ObjectHandler::convert2<bool>(
            ObjectHandler::ConvertOper(*Permanent), "Permanent", false);

        // convert input datatypes to QuantLib datatypes

        QuantLib::Matrix SymmetricMatrixLib =
            QuantLibXL::operToQlMatrix(*SymmetricMatrix);

        // Strip the Excel cell update counter suffix from Object IDs
        
        std::string ObjectIdStrip = ObjectHandler::CallingRange::getStub(ObjectId);

        // Construct the Value Object

        boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
            new QuantLibAddin::ValueObjects::qlSymmetricSchurDecomposition(
                ObjectIdStrip,
                SymmetricMatrixCpp,
                PermanentCpp));

        // Construct the Object
        
        boost::shared_ptr<ObjectHandler::Object> object(
            new QuantLibAddin::SymmetricSchurDecomposition(
                valueObject,
                SymmetricMatrixLib,
                PermanentCpp));

        // Store the Object in the Repository

        std::string returnValue =
            ObjectHandler::RepositoryXL::instance().storeObject(ObjectIdStrip, object, *Overwrite);

        // Convert and return the return value

        static char ret[XL_MAX_STR_LEN];
        ObjectHandler::stringToChar(returnValue, ret);
        return ret;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSymmetricSchurDecompositionEigenvalues(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSymmetricSchurDecompositionEigenvalues"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SymmetricSchurDecomposition, QuantLib::SymmetricSchurDecomposition)

        // invoke the member function

        QuantLib::Array returnValue = ObjectIdLibObjPtr->eigenvalues();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::vectorToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
XLL_DEC OPER *qlSymmetricSchurDecompositionEigenvectors(
        char *ObjectId,
        OPER *Trigger) {

    // declare a shared pointer to the Function Call object

    boost::shared_ptr<ObjectHandler::FunctionCall> functionCall;

    try {

        // instantiate the Function Call object

        functionCall = boost::shared_ptr<ObjectHandler::FunctionCall>(
            new ObjectHandler::FunctionCall("qlSymmetricSchurDecompositionEigenvectors"));

        ObjectHandler::validateRange(Trigger, "Trigger");

        // initialize the session ID (if enabled)

        SET_SESSION_ID

        // convert object IDs into library objects

        OH_GET_REFERENCE(ObjectIdLibObjPtr, ObjectId,
            QuantLibAddin::SymmetricSchurDecomposition, QuantLib::SymmetricSchurDecomposition)

        // invoke the member function

        QuantLib::Matrix returnValue = ObjectIdLibObjPtr->eigenvectors();

        // convert and return the return value

        static OPER xRet;
        ObjectHandler::matrixToOper(returnValue, xRet);
        return &xRet;

    } catch (const std::exception &e) {
        ObjectHandler::RepositoryXL::instance().logError(e.what(), functionCall);
        return 0;
    } catch (...) {
        ObjectHandler::RepositoryXL::instance().logError("unkown error type", functionCall);
        return 0;
    }

}
