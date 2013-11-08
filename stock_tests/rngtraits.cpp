void RngTraitsTest::testGaussian() {

    BOOST_TEST_MESSAGE("Testing Gaussian pseudo-random number generation...");

    PseudoRandom::rsg_type rsg =
        PseudoRandom::make_sequence_generator(100, 1234);

    const std::vector<Real>& values = rsg.nextSequence().value;
    Real sum = 0.0;
    for (Size i=0; i<values.size(); i++)
        sum += values[i];

    Real stored = 4.09916;
    Real tolerance = 1.0e-5;
    if (std::fabs(sum - stored) > tolerance)
        BOOST_FAIL("the sum of the samples does not match the stored value\n"
                   << "    calculated: " << sum << "\n"
                   << "    expected:   " << stored);
}


void RngTraitsTest::testDefaultPoisson() {

    BOOST_TEST_MESSAGE("Testing Poisson pseudo-random number generation...");

    PoissonPseudoRandom::icInstance =
        boost::shared_ptr<InverseCumulativePoisson>();
    PoissonPseudoRandom::rsg_type rsg =
        PoissonPseudoRandom::make_sequence_generator(100, 1234);

    const std::vector<Real>& values = rsg.nextSequence().value;
    Real sum = 0.0;
    for (Size i=0; i<values.size(); i++)
        sum += values[i];

    Real stored = 108.0;
    if (!close(sum, stored))
        BOOST_FAIL("the sum of the samples does not match the stored value\n"
                   << "    calculated: " << sum << "\n"
                   << "    expected:   " << stored);
}


void RngTraitsTest::testCustomPoisson() {

    BOOST_TEST_MESSAGE("Testing custom Poisson pseudo-random number generation...");

    PoissonPseudoRandom::icInstance =
        boost::shared_ptr<InverseCumulativePoisson>(
                                           new InverseCumulativePoisson(4.0));
    PoissonPseudoRandom::rsg_type rsg =
        PoissonPseudoRandom::make_sequence_generator(100, 1234);

    const std::vector<Real>& values = rsg.nextSequence().value;
    Real sum = 0.0;
    for (Size i=0; i<values.size(); i++)
        sum += values[i];

    Real stored = 409.0;
    if (!close(sum, stored))
        BOOST_FAIL("the sum of the samples does not match the stored value\n"
                   << "    calculated: " << sum << "\n"
                   << "    expected:   " << stored);
}


test_suite* RngTraitsTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("RNG traits tests");
    suite->add(QUANTLIB_TEST_CASE(&RngTraitsTest::testGaussian));
    suite->add(QUANTLIB_TEST_CASE(&RngTraitsTest::testDefaultPoisson));
    suite->add(QUANTLIB_TEST_CASE(&RngTraitsTest::testCustomPoisson));
    return suite;
}

