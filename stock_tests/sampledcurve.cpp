class FSquared : std::unary_function<Real,Real> {
public:
    Real operator()(Real x) const { return x*x;};
};

void SampledCurveTest::testConstruction() {

    BOOST_TEST_MESSAGE("Testing sampled curve construction...");

    SampledCurve curve(BoundedGrid(-10.0,10.0,100));
    FSquared f2;
    curve.sample(f2);
    Real expected = 100.0;
    if (std::fabs(curve.value(0) - expected) > 1e-5) {
        BOOST_ERROR("function sampling failed");
    }

    curve.value(0) = 2.0;
    if (std::fabs(curve.value(0) - 2.0) > 1e-5) {
        BOOST_ERROR("curve value setting failed");
    }

    Array& value = curve.values();
    value[1] = 3.0;
    if (std::fabs(curve.value(1) - 3.0) > 1e-5) {
        BOOST_ERROR("curve value grid failed");
    }

    curve.shiftGrid(10.0);
    if (std::fabs(curve.gridValue(0) - 0.0) > 1e-5) {
        BOOST_ERROR("sample curve shift grid failed");
    }
    if (std::fabs(curve.value(0) - 2.0) > 1e-5) {
        BOOST_ERROR("sample curve shift grid - value failed");
    }

    curve.sample(f2);
    curve.regrid(BoundedGrid(0.0,20.0,200));
    Real tolerance = 1.0e-2;
    for (Size i=0; i < curve.size(); i++) {
        Real grid = curve.gridValue(i);
        Real value = curve.value(i);
        Real expected = f2(grid);
        if (std::fabs(value - expected) > tolerance) {
            BOOST_ERROR("sample curve regriding failed" <<
                        "\n    at " << io::ordinal(i+1) << " point " << "(x = " << grid << ")" <<
                        "\n    grid value: " << value <<
                        "\n    expected:   " << expected);
        }
    }
}

test_suite* SampledCurveTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("sampled curve tests");
    suite->add(QUANTLIB_TEST_CASE(&SampledCurveTest::testConstruction));
    return suite;
}

