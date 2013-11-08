void VolatilityModelsTest::testConstruction() {

    BOOST_TEST_MESSAGE("Testing volatility model construction...");

    TimeSeries<Real> ts;
    ts[Date(25, March, 2005)] = 1.2;
    ts[Date(29, March, 2005)] = 2.3;
    ts[Date(15, March, 2005)] = 0.3;

    SimpleLocalEstimator sle(1/360.0);
    TimeSeries<Volatility> locale = sle.calculate(ts);

    ConstantEstimator ce(1);
    TimeSeries<Volatility> sv = ce.calculate(locale);
    sv.begin();
}

test_suite* VolatilityModelsTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("volatility models tests");
    suite->add(QUANTLIB_TEST_CASE(&VolatilityModelsTest::testConstruction));
    return suite;
}

