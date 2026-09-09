-- Matrix decompositions: eigenvalues/eigenvectors, the salvaging pseudo square roots and
-- Cholesky, checked against upstream's matrices.cpp and covariance.cpp fixtures.
module QuantLib.Spec.Matrix (spec) where

import Test.Hspec

import QuantLib.Math

spec :: Spec
spec = describe "matrix decompositions (ql/math/matrixutilities)" $ do
  eigenSpec
  pseudoSqrtSpec
  rankReducedSqrtSpec
  choleskySpec

-- Small dense helpers over the boxed 'Matrix' 'Double' the bindings exchange.

-- |Build a matrix from its row count and row-major data.
matrix :: Word -> [Double] -> Matrix Double
matrix n xs = either error id $ boxedRealMatrix n (fromIntegral (length xs) `div` n) xs

colVector :: [Double] -> Matrix Double
colVector xs = matrix (fromIntegral (length xs)) xs

at :: Matrix Double -> Word -> Word -> Double
at m i j = matrixData m !! fromIntegral (i * matrixColumns m + j)

mmul :: Matrix Double -> Matrix Double -> Matrix Double
mmul a b = matrix rows
  [ sum [at a i k * at b k j | k <- [0 .. matrixColumns a - 1]]
  | i <- [0 .. rows - 1], j <- [0 .. cols - 1] ]
  where rows = matrixRows a
        cols = matrixColumns b

transposeM :: Matrix Double -> Matrix Double
transposeM m = matrix (matrixColumns m)
  [at m i j | j <- [0 .. matrixColumns m - 1], i <- [0 .. matrixRows m - 1]]

-- |Frobenius norm of the elementwise difference, upstream's @norm(a-b)@.
normDiff :: Matrix Double -> Matrix Double -> Double
normDiff a b = sqrt . sum $ zipWith (\x y -> (x - y) * (x - y)) (matrixData a) (matrixData b)

identity :: Word -> Matrix Double
identity n = matrix n [if i == j then 1.0 else 0.0 | i <- [1 .. n], j <- [1 .. n]]

-- matrices.cpp::setup. m2 is also covariance.cpp::testRankReduction's badCorr: a plausible
-- empirical correlation matrix that is not positive semi-definite.
m1, m2, m5, m6 :: Matrix Double
m1 = matrix 3 [1.0, 0.9, 0.7, 0.9, 1.0, 0.4, 0.7, 0.4, 1.0]
m2 = matrix 3 [1.0, 0.9, 0.7, 0.9, 1.0, 0.3, 0.7, 0.3, 1.0]
-- Higham's example: m6 is the nearest correlation matrix to m5.
m5 = matrix 4 [  2.0, -1.0,  0.0,  0.0
              , -1.0,  2.0, -1.0,  0.0
              ,  0.0, -1.0,  2.0, -1.0
              ,  0.0,  0.0, -1.0,  2.0 ]
m6 = matrix 4 [  1.0,          -0.8084124981,  0.1915875019,  0.106775049
              , -0.8084124981,  1.0,          -0.6562326948,  0.1915875019
              ,  0.1915875019, -0.6562326948,  1.0,          -0.8084124981
              ,  0.106775049,   0.1915875019, -0.8084124981,  1.0 ]

-- covariance.cpp::testRankReduction
goodCorr, badCov :: Matrix Double
goodCorr = matrix 3 [ 1.0,               0.894024408508599, 0.696319066114392
                    , 0.894024408508599, 1.0,               0.300969036104592
                    , 0.696319066114392, 0.300969036104592, 1.0 ]
badCov = matrix 3 [0.04, 0.0324, 0.0224, 0.0324, 0.0324, 0.00864, 0.0224, 0.00864, 0.0256]

-- |matrices.cpp::createTestCorrelationMatrix.
testCorrelation :: Word -> Matrix Double
testCorrelation n = matrix n
  [ exp (-0.1 * abs (fromIntegral i - fromIntegral j)
         - (if i /= j then 0.02 * fromIntegral (i + j) else 0.0))
  | i <- [0 .. n - 1], j <- [0 .. n - 1] ]

eigenSpec :: Spec
eigenSpec = describe "symmetricSchurDecomposition" $ do
  it "satisfies the eigenvector definition, decreasing order and orthonormality (matrices.cpp::testEigenvectors)" $
    mapM_ checkEigen [m1, m2]

  it "reconstructs the original matrix as U*D*transpose U, negative eigenvalue included" $ do
    (values, vectors) <- symmetricSchurDecomposition m2
    -- The reason the salvaging pseudo square roots exist: an empirical correlation matrix is
    -- routinely not positive semi-definite.
    minimum values `shouldSatisfy` (< 0.0)
    let d = matrix 3 [ if i == j then values !! fromIntegral i else 0.0
                     | i <- [0 :: Word .. 2], j <- [0 :: Word .. 2] ]
    normDiff (vectors `mmul` d `mmul` transposeM vectors) m2 `shouldSatisfy` (< 1.0e-14)

  it "rejects a non-square matrix" $
    symmetricSchurDecomposition (matrix 2 [1.0, 0.0, 0.0, 1.0, 0.0, 0.0]) `shouldThrow` anyException

checkEigen :: Matrix Double -> Expectation
checkEigen m = do
  (values, vectors) <- symmetricSchurDecomposition m
  let n = matrixRows m
  length values `shouldBe` fromIntegral n
  (matrixRows vectors, matrixColumns vectors) `shouldBe` (n, n)
  -- eigenvectors are the columns of the result
  mapM_ (\(i, lambda) ->
          let v = colVector [at vectors j i | j <- [0 .. n - 1]]
          in normDiff (m `mmul` v) (colVector (map (* lambda) (matrixData v)))
               `shouldSatisfy` (< 1.0e-15))
        (zip [0 ..] values)
  values `shouldSatisfy` \vs -> and (zipWith (>) vs (drop 1 vs))
  normDiff (vectors `mmul` transposeM vectors) (identity n) `shouldSatisfy` (< 1.0e-15)

pseudoSqrtSpec :: Spec
pseudoSqrtSpec = describe "pseudoSqrt" $ do
  it "reproduces a positive-definite matrix as S*transpose S (matrices.cpp::testSqrt)" $ do
    s <- pseudoSqrt m1 SalvagingNone
    normDiff (s `mmul` transposeM s) m1 `shouldSatisfy` (< 1.0e-12)

  it "salvages with Higham to the nearest correlation matrix (matrices.cpp::testHighamSqrt)" $ do
    salvaged <- pseudoSqrt m5 Higham
    expected <- pseudoSqrt m6 SalvagingNone
    normDiff salvaged expected `shouldSatisfy` (< 1.0e-4)

  it "gives a symmetric square root under Principal (matrices.cpp::testPrincipalMatrixSqrt)" $
    mapM_ (\n -> do
            let rho = testCorrelation n
            s <- pseudoSqrt rho Principal
            normDiff s (transposeM s) `shouldSatisfy` (< 1.0e-12)
            normDiff (s `mmul` s) rho `shouldSatisfy` (< 1.0e-10))
          [1, 4, 10]

  it "rejects a matrix that is not positive semi-definite without salvaging" $
    pseudoSqrt m2 SalvagingNone `shouldThrow` anyException

rankReducedSqrtSpec :: Spec
rankReducedSqrtSpec = describe "rankReducedSqrt" $ do
  it "salvages a correlation matrix with the spectral algorithm (covariance.cpp::testRankReduction)" $ do
    b <- rankReducedSqrt m2 3 1.0 Spectral
    normDiff (b `mmul` transposeM b) goodCorr `shouldSatisfy` (< 1.0e-10)

  it "salvages a covariance matrix with the spectral algorithm (covariance.cpp::testRankReduction)" $ do
    b <- rankReducedSqrt badCov 3 1.0 Spectral
    normDiff (b `mmul` transposeM b) badCov `shouldSatisfy` (< 4.0e-4)

  it "caps the number of retained factors at maxRank" $ do
    b <- rankReducedSqrt m2 2 1.0 Spectral
    (matrixRows b, matrixColumns b) `shouldBe` (3, 2)

  it "rejects a retained percentage outside (0, 1]" $
    rankReducedSqrt m2 3 0.0 Spectral `shouldThrow` anyException

choleskySpec :: Spec
choleskySpec = describe "choleskyDecomposition" $ do
  it "factors a positive-definite matrix as L*transpose L" $ do
    let rho = testCorrelation 10
    l <- choleskyDecomposition rho False
    normDiff (l `mmul` transposeM l) rho `shouldSatisfy` (< 1.0e-14)

  it "completes a rank-deficient matrix when flexible (matrices.cpp::testCholeskySolverForIncomplete)" $ do
    let rho = matrix 4 [ 1.0, 0.9, 0.0, 0.0
                       , 0.9, 1.0, 0.0, 0.0
                       , 0.0, 0.0, 0.0, 0.0
                       , 0.0, 0.0, 0.0, 0.0 ]
    l <- choleskyDecomposition rho True
    matrixData l `shouldSatisfy` (not . any isNaN)
    normDiff (l `mmul` transposeM l) rho `shouldSatisfy` (< 1.0e-14)

  it "solves M*x == b through its factor (matrices.cpp::testCholeskySolverFor)" $
    mapM_ (\n -> do
            let rho = testCorrelation n
                b = [1.0 / (1.0 + fromIntegral k) | k <- [1 .. n]]
            l <- choleskyDecomposition rho False
            x <- choleskySolveFor l b
            length x `shouldBe` fromIntegral n
            normDiff (rho `mmul` colVector x) (colVector b) `shouldSatisfy` (< 1.0e-13))
          [1, 4, 10]

-- vim: set ff=unix ts=8 sts=2 sw=2 et:
