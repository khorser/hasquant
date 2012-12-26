
/*  
 Copyright (C) 2004, 2005, 2006, 2007, 2008 Eric Ehlers
 
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
//      gensrc/gensrc/stubs/stub.excel.register.file

#include <xlsdk/xlsdkdefines.hpp>

// register functions in category Mathf with Excel

void registerMathf(const XLOPER &xDll) {

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCholeskyDecomposition"),
            // parameter codes
            TempStrNoSize("\x05""PKPP#"),
            // function display name
            TempStrNoSize("\x17""qlCholeskyDecomposition"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""Matrix,Flexible,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the Cholesky decomposition of a real symmetric matrix."),
            // parameter descriptions
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x5A""If TRUE it returns a result also for positive semi-definite matrix. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x19""qlCovarianceDecomposition"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x19""qlCovarianceDecomposition"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,SymmetricMatrix,Tolerance,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class CovarianceDecomposition and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2D""Symmetrix covariance matrix to be decomposed."),
            TempStrNoSize("\x45""numerical tolerance for non symmetric matrix. Default value = 1.0e12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlCovarianceDecompositionCorrelationMatrix"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlCovarianceDecompositionCorrelationMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the correlation matrix for the given CovarianceDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::CovarianceDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlCovarianceDecompositionStandardDeviations"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlCovarianceDecompositionStandardDeviations"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7F""Returns the standard deviation (i.e. volatility times square root of time) vector for the given CovarianceDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::CovarianceDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlCovarianceDecompositionVariances"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x22""qlCovarianceDecompositionVariances"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the variance vector for the given CovarianceDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::CovarianceDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlGetCovariance"),
            // parameter codes
            TempStrNoSize("\x06""PPKPP#"),
            // function display name
            TempStrNoSize("\x0F""qlGetCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1D""Vols,Matrix,Tolerance,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x92""Returns the covariance matrix generated using the correlation matrix and the standard deviation (i.e. volatility times square root of time) array."),
            // parameter descriptions
            TempStrNoSize("\x12""volatility vector."),
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x45""numerical tolerance for non symmetric matrix. Default value = 1.0e12."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlNormDist"),
            // parameter codes
            TempStrNoSize("\x07""EEPPPP#"),
            // function display name
            TempStrNoSize("\x0A""qlNormDist"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""X,Mean,Standard_dev,Cumulative,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""Returns the normal cumulative distribution for the specified mean and standard deviation."),
            // parameter descriptions
            TempStrNoSize("\x31""is the value for which you want the distribution."),
            TempStrNoSize("\x40""is the arithmetic mean of the distribution. Default value = 0.0."),
            TempStrNoSize("\x56""is the standard deviation of the distribution, a positive number. Default value = 1.0."),
            TempStrNoSize("\x8B""is a logical value: for the cumulative distribution function, use TRUE; for the probability mass function, use FALSE. Default value = TRUE."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x09""qlNormInv"),
            // parameter codes
            TempStrNoSize("\x06""EEPPP#"),
            // function display name
            TempStrNoSize("\x09""qlNormInv"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x25""Probability,Mean,Standard_dev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x68""Returns the inverse of the normal cumulative distribution for the specified mean and standard deviation."),
            // parameter descriptions
            TempStrNoSize("\x5E""is a probability corresponding to the normal distribution, a number between 0 and 1 inclusive."),
            TempStrNoSize("\x40""is the arithmetic mean of the distribution. Default value = 0.0."),
            TempStrNoSize("\x56""is the standard deviation of the distribution, a positive number. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlNormSDist"),
            // parameter codes
            TempStrNoSize("\x04""EEP#"),
            // function display name
            TempStrNoSize("\x0B""qlNormSDist"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x09""Z,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x67""Returns the standard normal cumulative distribution (has a mean of zero and standard deviation of one)."),
            // parameter descriptions
            TempStrNoSize("\x31""is the value for which you want the distribution."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlNormSInv"),
            // parameter codes
            TempStrNoSize("\x04""EEP#"),
            // function display name
            TempStrNoSize("\x0A""qlNormSInv"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x13""Probability,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x76""Returns the inverse of the standard normal cumulative distribution (has a mean of zero and standard deviation of one)."),
            // parameter descriptions
            TempStrNoSize("\x5E""is a probability corresponding to the normal distribution, a number between 0 and 1 inclusive."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlPrimeNumber"),
            // parameter codes
            TempStrNoSize("\x04""NNP#"),
            // function display name
            TempStrNoSize("\x0D""qlPrimeNumber"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x09""N,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1E""returns the N-th prime number."),
            // parameter descriptions
            TempStrNoSize("\x2E""index of the prime number (e.g N=2 returns 3)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlPseudoSqrt"),
            // parameter codes
            TempStrNoSize("\x05""PKCP#"),
            // function display name
            TempStrNoSize("\x0C""qlPseudoSqrt"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""Matrix,SalvagingAlgorithm,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns the pseudo square root of a real symmetric matrix."),
            // parameter descriptions
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x55""Salvaging algorithm for symmetric matrix not positive semi-definite (None, Spectral)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlRankReducedSqrt"),
            // parameter codes
            TempStrNoSize("\x07""PKNECP#"),
            // function display name
            TempStrNoSize("\x11""qlRankReducedSqrt"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""Matrix,MaxRank,ComponentPercentage,SalvagingAlgorithm,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the rank reduced pseudo square root of a real symmetric matrix."),
            // parameter descriptions
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x4D""number of principal components retained, i.e. max rank for the result matrix."),
            TempStrNoSize("\x40""principal components retained as percentage of eigenvalues' sum."),
            TempStrNoSize("\x55""Salvaging algorithm for symmetric matrix not positive semi-definite (None, Spectral)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSymmetricSchurDecomposition"),
            // parameter codes
            TempStrNoSize("\x07""CCKPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlSymmetricSchurDecomposition"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,SymmetricMatrix,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Construct an object of class SymmetricSchurDecomposition and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Symmetrix matrix to be decomposed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlSymmetricSchurDecompositionEigenvalues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlSymmetricSchurDecompositionEigenvalues"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the eigenvalues for the given SymmetricSchurDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SymmetricSchurDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlSymmetricSchurDecompositionEigenvectors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlSymmetricSchurDecompositionEigenvectors"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""1"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns the eigenvectors  for the given SymmetricSchurDecomposition object. Eigenvectors are returned columnwise."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SymmetricSchurDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));



}

// unregister functions in category Mathf with Excel

void unregisterMathf(const XLOPER &xDll) {

    XLOPER xlRegID;

    // Unregister each function.  Due to a bug in Excel's C API this is a
    // two-step process.  Thanks to Laurent Longre for discovering the
    // workaround implemented here.

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x17""qlCholeskyDecomposition"),
            // parameter codes
            TempStrNoSize("\x05""PKPP#"),
            // function display name
            TempStrNoSize("\x17""qlCholeskyDecomposition"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x17""Matrix,Flexible,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3E""Returns the Cholesky decomposition of a real symmetric matrix."),
            // parameter descriptions
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x5A""If TRUE it returns a result also for positive semi-definite matrix. Default value = false."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x17""qlCholeskyDecomposition"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 16, &xDll,
            // function code name
            TempStrNoSize("\x19""qlCovarianceDecomposition"),
            // parameter codes
            TempStrNoSize("\x08""CCKPPPL#"),
            // function display name
            TempStrNoSize("\x19""qlCovarianceDecomposition"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3E""ObjectId,SymmetricMatrix,Tolerance,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x46""Construct an object of class CovarianceDecomposition and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x2D""Symmetrix covariance matrix to be decomposed."),
            TempStrNoSize("\x45""numerical tolerance for non symmetric matrix. Default value = 1.0e12."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x19""qlCovarianceDecomposition"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2A""qlCovarianceDecompositionCorrelationMatrix"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2A""qlCovarianceDecompositionCorrelationMatrix"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4C""Returns the correlation matrix for the given CovarianceDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::CovarianceDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2A""qlCovarianceDecompositionCorrelationMatrix"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x2B""qlCovarianceDecompositionStandardDeviations"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x2B""qlCovarianceDecompositionStandardDeviations"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x7F""Returns the standard deviation (i.e. volatility times square root of time) vector for the given CovarianceDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::CovarianceDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x2B""qlCovarianceDecompositionStandardDeviations"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x22""qlCovarianceDecompositionVariances"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x22""qlCovarianceDecompositionVariances"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the variance vector for the given CovarianceDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x37""id of existing QuantLib::CovarianceDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x22""qlCovarianceDecompositionVariances"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x0F""qlGetCovariance"),
            // parameter codes
            TempStrNoSize("\x06""PPKPP#"),
            // function display name
            TempStrNoSize("\x0F""qlGetCovariance"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x1D""Vols,Matrix,Tolerance,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x92""Returns the covariance matrix generated using the correlation matrix and the standard deviation (i.e. volatility times square root of time) array."),
            // parameter descriptions
            TempStrNoSize("\x12""volatility vector."),
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x45""numerical tolerance for non symmetric matrix. Default value = 1.0e12."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0F""qlGetCovariance"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlNormDist"),
            // parameter codes
            TempStrNoSize("\x07""EEPPPP#"),
            // function display name
            TempStrNoSize("\x0A""qlNormDist"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x26""X,Mean,Standard_dev,Cumulative,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x59""Returns the normal cumulative distribution for the specified mean and standard deviation."),
            // parameter descriptions
            TempStrNoSize("\x31""is the value for which you want the distribution."),
            TempStrNoSize("\x40""is the arithmetic mean of the distribution. Default value = 0.0."),
            TempStrNoSize("\x56""is the standard deviation of the distribution, a positive number. Default value = 1.0."),
            TempStrNoSize("\x8B""is a logical value: for the cumulative distribution function, use TRUE; for the probability mass function, use FALSE. Default value = TRUE."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlNormDist"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 14, &xDll,
            // function code name
            TempStrNoSize("\x09""qlNormInv"),
            // parameter codes
            TempStrNoSize("\x06""EEPPP#"),
            // function display name
            TempStrNoSize("\x09""qlNormInv"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x25""Probability,Mean,Standard_dev,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x68""Returns the inverse of the normal cumulative distribution for the specified mean and standard deviation."),
            // parameter descriptions
            TempStrNoSize("\x5E""is a probability corresponding to the normal distribution, a number between 0 and 1 inclusive."),
            TempStrNoSize("\x40""is the arithmetic mean of the distribution. Default value = 0.0."),
            TempStrNoSize("\x56""is the standard deviation of the distribution, a positive number. Default value = 1.0."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x09""qlNormInv"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0B""qlNormSDist"),
            // parameter codes
            TempStrNoSize("\x04""EEP#"),
            // function display name
            TempStrNoSize("\x0B""qlNormSDist"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x09""Z,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x67""Returns the standard normal cumulative distribution (has a mean of zero and standard deviation of one)."),
            // parameter descriptions
            TempStrNoSize("\x31""is the value for which you want the distribution."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0B""qlNormSDist"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0A""qlNormSInv"),
            // parameter codes
            TempStrNoSize("\x04""EEP#"),
            // function display name
            TempStrNoSize("\x0A""qlNormSInv"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x13""Probability,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x76""Returns the inverse of the standard normal cumulative distribution (has a mean of zero and standard deviation of one)."),
            // parameter descriptions
            TempStrNoSize("\x5E""is a probability corresponding to the normal distribution, a number between 0 and 1 inclusive."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0A""qlNormSInv"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x0D""qlPrimeNumber"),
            // parameter codes
            TempStrNoSize("\x04""NNP#"),
            // function display name
            TempStrNoSize("\x0D""qlPrimeNumber"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x09""N,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x1E""returns the N-th prime number."),
            // parameter descriptions
            TempStrNoSize("\x2E""index of the prime number (e.g N=2 returns 3)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0D""qlPrimeNumber"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 13, &xDll,
            // function code name
            TempStrNoSize("\x0C""qlPseudoSqrt"),
            // parameter codes
            TempStrNoSize("\x05""PKCP#"),
            // function display name
            TempStrNoSize("\x0C""qlPseudoSqrt"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x21""Matrix,SalvagingAlgorithm,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x3A""Returns the pseudo square root of a real symmetric matrix."),
            // parameter descriptions
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x55""Salvaging algorithm for symmetric matrix not positive semi-definite (None, Spectral)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x0C""qlPseudoSqrt"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x11""qlRankReducedSqrt"),
            // parameter codes
            TempStrNoSize("\x07""PKNECP#"),
            // function display name
            TempStrNoSize("\x11""qlRankReducedSqrt"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x3D""Matrix,MaxRank,ComponentPercentage,SalvagingAlgorithm,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x47""Returns the rank reduced pseudo square root of a real symmetric matrix."),
            // parameter descriptions
            TempStrNoSize("\x3D""symmetric matrix (hopefully positive semi-definite at least)."),
            TempStrNoSize("\x4D""number of principal components retained, i.e. max rank for the result matrix."),
            TempStrNoSize("\x40""principal components retained as percentage of eigenvalues' sum."),
            TempStrNoSize("\x55""Salvaging algorithm for symmetric matrix not positive semi-definite (None, Spectral)."),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x11""qlRankReducedSqrt"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 15, &xDll,
            // function code name
            TempStrNoSize("\x1D""qlSymmetricSchurDecomposition"),
            // parameter codes
            TempStrNoSize("\x07""CCKPPL#"),
            // function display name
            TempStrNoSize("\x1D""qlSymmetricSchurDecomposition"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x34""ObjectId,SymmetricMatrix,Permanent,Trigger,Overwrite"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x4A""Construct an object of class SymmetricSchurDecomposition and return its id"),
            // parameter descriptions
            TempStrNoSize("\x1A""id of object to be created"),
            TempStrNoSize("\x22""Symmetrix matrix to be decomposed."),
            TempStrNoSize("\x1D""object permanent/nonpermanent"),
            TempStrNoSize("\x1B""dependency tracking trigger"),
            TempStrNoSize("\x10""overwrite flag  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x1D""qlSymmetricSchurDecomposition"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x28""qlSymmetricSchurDecompositionEigenvalues"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x28""qlSymmetricSchurDecompositionEigenvalues"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x49""Returns the eigenvalues for the given SymmetricSchurDecomposition object."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SymmetricSchurDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x28""qlSymmetricSchurDecompositionEigenvalues"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);

        Excel(xlfRegister, 0, 12, &xDll,
            // function code name
            TempStrNoSize("\x29""qlSymmetricSchurDecompositionEigenvectors"),
            // parameter codes
            TempStrNoSize("\x04""PCP#"),
            // function display name
            TempStrNoSize("\x29""qlSymmetricSchurDecompositionEigenvectors"),
            // comma-delimited list of parameter names
            TempStrNoSize("\x10""ObjectId,Trigger"),
            // function type (0 = hidden, 1 = worksheet)
            TempStrNoSize("\x01""0"),
            // function category
            TempStrNoSize("\x0F""QuantLib - Math"),
            // shortcut text (command macros only)
            TempStrNoSize("\x00"""),
            // path to help file
            TempStrNoSize("\x00"""),
            // function description
            TempStrNoSize("\x71""Returns the eigenvectors  for the given SymmetricSchurDecomposition object. Eigenvectors are returned columnwise."),
            // parameter descriptions
            TempStrNoSize("\x3B""id of existing QuantLib::SymmetricSchurDecomposition object"),
            TempStrNoSize("\x1D""dependency tracking trigger  "));

        Excel4(xlfRegisterId, &xlRegID, 2, &xDll,
            TempStrNoSize("\x29""qlSymmetricSchurDecompositionEigenvectors"));
        Excel4(xlfUnregister, 0, 1, &xlRegID);



}

