void FactorialTest::testFactorial() {

    BOOST_TEST_MESSAGE("Testing factorial numbers...");

    Real expected = 1.0;
    Real calculated = Factorial::get(0);
    if (calculated!=expected)
        BOOST_FAIL("Factorial(0) = " << calculated);

    for (Natural i=1; i<171; ++i) {
        expected *= i;
        calculated = Factorial::get(i);
        if (std::fabs(calculated-expected)/expected > 1.0e-9)
            BOOST_FAIL("Factorial(" << i << ")" <<
                       std::setprecision(16) << QL_SCIENTIFIC <<
                       "\n calculated: " << calculated <<
                       "\n   expected: " << expected <<
                       "\n rel. error: " <<
                       std::fabs(calculated-expected)/expected);
    }
}

void FactorialTest::testGammaFunction() {

    BOOST_TEST_MESSAGE("Testing Gamma function...");

    Real expected = 0.0;
    Real calculated = GammaFunction().logValue(1);
    if (std::fabs(calculated) > 1.0e-15)
        BOOST_ERROR("GammaFunction(1)\n"
                    << std::setprecision(16) << QL_SCIENTIFIC
                    << "    calculated: " << calculated << "\n"
                    << "    expected:   " << expected);

    for (Size i=2; i<9000; i++) {
        expected  += std::log(Real(i));
        calculated = GammaFunction().logValue(static_cast<Real>(i+1));
        if (std::fabs(calculated-expected)/expected > 1.0e-9)
            BOOST_ERROR("GammaFunction(" << i << ")\n"
                        << std::setprecision(16) << QL_SCIENTIFIC
                        << "    calculated: " << calculated << "\n"
                        << "    expected:   " << expected << "\n"
                        << "    rel. error: "
                        << std::fabs(calculated-expected)/expected);
    }
}


test_suite* FactorialTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Factorial tests");
    suite->add(QUANTLIB_TEST_CASE(&FactorialTest::testFactorial));
    suite->add(QUANTLIB_TEST_CASE(&FactorialTest::testGammaFunction));
    return suite;
}

