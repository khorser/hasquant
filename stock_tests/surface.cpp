void SurfaceTest::testOutput() {

    BOOST_TEST_MESSAGE("Testing surface...");
    Real tolerance = 1e-5;

    TestSurface st;
    Real out = st(0, 0);
    Real expected = 0.0;
    if (std::fabs(out - expected) > tolerance)
        BOOST_FAIL("test surface incorrect value");

    RectangularDomain rect(0.0, 0.0, 1.0, 1.0);
    if (!rect.includes(0.5, 0.5))
        BOOST_FAIL("RectangularDomain fails 0.5 0.5");
    if (rect.includes(1.5, 0.5))
        BOOST_FAIL("RectangularDomain fails 1.5 0.5");
}


test_suite* SurfaceTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Surface tests");

    suite->add(QUANTLIB_TEST_CASE(&SurfaceTest::testOutput));
    return suite;
}

