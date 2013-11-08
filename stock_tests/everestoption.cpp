void EverestOptionTest::testCached() {

    BOOST_TEST_MESSAGE("Testing Everest option against cached values...");

    Date today = Settings::instance().evaluationDate();

    DayCounter dc = Actual360();
    Date exerciseDate = today+360;
    boost::shared_ptr<Exercise> exercise(new EuropeanExercise(exerciseDate));

    Real notional = 1.0;
    Rate guarantee = 0.0;
    EverestOption option(notional, guarantee, exercise);

    Handle<YieldTermStructure> riskFreeRate(flatRate(today, 0.05, dc));

    std::vector<boost::shared_ptr<StochasticProcess1D> > processes(4);
    Handle<Quote> dummyUnderlying(boost::shared_ptr<Quote>(
                                                       new SimpleQuote(1.0)));
    processes[0] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
                    dummyUnderlying,
                    Handle<YieldTermStructure>(flatRate(today, 0.01, dc)),
                    riskFreeRate,
                    Handle<BlackVolTermStructure>(flatVol(today, 0.30, dc))));
    processes[1] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
                    dummyUnderlying,
                    Handle<YieldTermStructure>(flatRate(today, 0.05, dc)),
                    riskFreeRate,
                    Handle<BlackVolTermStructure>(flatVol(today, 0.35, dc))));
    processes[2] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
                    dummyUnderlying,
                    Handle<YieldTermStructure>(flatRate(today, 0.04, dc)),
                    riskFreeRate,
                    Handle<BlackVolTermStructure>(flatVol(today, 0.25, dc))));
    processes[3] = boost::shared_ptr<StochasticProcess1D>(
        new BlackScholesMertonProcess(
                    dummyUnderlying,
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
    Real minimumTol = 1.0e-2;

    boost::shared_ptr<StochasticProcessArray> process(
                          new StochasticProcessArray(processes, correlation));

    option.setPricingEngine(MakeMCEverestEngine<PseudoRandom>(process)
                            .withStepsPerYear(1)
                            .withSamples(fixedSamples)
                            .withSeed(seed));

    Real value = option.NPV();
    Real storedValue = 0.75784944;
    Real tolerance = 1.0e-8;

    if (std::fabs(value-storedValue) > tolerance)
        BOOST_FAIL(std::setprecision(10)
                   << "    calculated value: " << value << "\n"
                   << "    expected:         " << storedValue);

    tolerance = option.errorEstimate();
    tolerance = std::min<Real>(tolerance/2.0, minimumTol*value);

    option.setPricingEngine(MakeMCEverestEngine<PseudoRandom>(process)
                            .withStepsPerYear(1)
                            .withAbsoluteTolerance(tolerance)
                            .withSeed(seed));

    value = option.NPV();
    Real accuracy = option.errorEstimate();
    if (accuracy > tolerance)
        BOOST_FAIL(std::setprecision(10)
                   << "    reached accuracy: " << accuracy << "\n"
                   << "    expected:         " << tolerance);
}


test_suite* EverestOptionTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Everest-option tests");
    suite->add(QUANTLIB_TEST_CASE(&EverestOptionTest::testCached));
    return suite;
}

