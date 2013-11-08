void HimalayaOptionTest::testCached() {

    BOOST_TEST_MESSAGE("Testing Himalaya option against cached values...");

    Date today = Settings::instance().evaluationDate();

    DayCounter dc = Actual360();
    std::vector<Date> fixingDates;
    for (Size i=0; i<5; ++i)
        fixingDates.push_back(today+i*90);

    Real strike = 101.0;
    HimalayaOption option(fixingDates, strike);

    Handle<YieldTermStructure> riskFreeRate(flatRate(today, 0.05, dc));

    std::vector<boost::shared_ptr<StochasticProcess1D> > processes(4);
    processes[0] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
              Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(100.0))),
              Handle<YieldTermStructure>(flatRate(today, 0.01, dc)),
              riskFreeRate,
              Handle<BlackVolTermStructure>(flatVol(today, 0.30, dc))));
    processes[1] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
              Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(110.0))),
              Handle<YieldTermStructure>(flatRate(today, 0.05, dc)),
              riskFreeRate,
              Handle<BlackVolTermStructure>(flatVol(today, 0.35, dc))));
    processes[2] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
              Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(90.0))),
              Handle<YieldTermStructure>(flatRate(today, 0.04, dc)),
              riskFreeRate,
              Handle<BlackVolTermStructure>(flatVol(today, 0.25, dc))));
    processes[3] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
              Handle<Quote>(boost::shared_ptr<Quote>(new SimpleQuote(105.0))),
              Handle<YieldTermStructure>(flatRate(today, 0.03, dc)),
              riskFreeRate,
              Handle<BlackVolTermStructure>(flatVol(today, 0.20, dc))));

    Matrix correlation(4,4);
    correlation[0][0] = 1.00;
                    correlation[0][1] = 0.50;
                                    correlation[0][2] = 0.30;
                                                    correlation[0][3] = 0.10;
    correlation[1][0] = 0.50;
                    correlation[1][1] = 1.00;
                                    correlation[1][2] = 0.20;
                                                    correlation[1][3] = 0.40;
    correlation[2][0] = 0.30;
                    correlation[2][1] = 0.20;
                                    correlation[2][2] = 1.00;
                                                    correlation[2][3] = 0.60;
    correlation[3][0] = 0.10;
                    correlation[3][1] = 0.40;
                                    correlation[3][2] = 0.60;
                                                    correlation[3][3] = 1.00;



    BigNatural seed = 86421;
    Size fixedSamples = 1023;

    boost::shared_ptr<StochasticProcessArray> process(
                          new StochasticProcessArray(processes, correlation));

    option.setPricingEngine(MakeMCHimalayaEngine<PseudoRandom>(process)
                            .withSamples(fixedSamples)
                            .withSeed(seed));

    Real value = option.NPV();
    Real storedValue = 6.60370398;
    Real tolerance = 1.0e-8;

    if (std::fabs(value-storedValue) > tolerance)
        BOOST_FAIL(std::setprecision(10)
                   << "    calculated value: " << value << "\n"
                   << "    expected:         " << storedValue);

    Real minimumTol = 1.0e-2;
    tolerance = option.errorEstimate();
    tolerance = std::min<Real>(tolerance/2.0, minimumTol*value);

    option.setPricingEngine(MakeMCHimalayaEngine<PseudoRandom>(process)
                            .withAbsoluteTolerance(tolerance)
                            .withSeed(seed));

    value = option.NPV();
    Real accuracy = option.errorEstimate();
    if (accuracy > tolerance)
        BOOST_FAIL(std::setprecision(10)
                   << "    reached accuracy: " << accuracy << "\n"
                   << "    expected:         " << tolerance);
}


test_suite* HimalayaOptionTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Himalaya-option tests");
    suite->add(QUANTLIB_TEST_CASE(&HimalayaOptionTest::testCached));
    return suite;
}

