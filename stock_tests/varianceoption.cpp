void VarianceOptionTest::testIntegralHeston() {

    BOOST_TEST_MESSAGE("Testing variance option with integral Heston engine...");

    DayCounter dc = Actual360();
    Date today = Settings::instance().evaluationDate();

    Handle<Quote> s0(boost::shared_ptr<SimpleQuote>(new SimpleQuote(1.0)));
    Handle<YieldTermStructure> qTS;
    boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.0));
    Handle<YieldTermStructure> rTS(flatRate(today, rRate, dc));

    Real v0 = 2.0;
    Real kappa = 2.0;
    Real theta = 0.01;
    Real sigma = 0.1;
    Real rho = -0.5;

    boost::shared_ptr<HestonProcess> process(new HestonProcess(rTS, qTS, s0,
                                                               v0, kappa, theta,
                                                               sigma, rho));
    boost::shared_ptr<PricingEngine> engine(
                               new IntegralHestonVarianceOptionEngine(process));

    Real strike = 0.05;
    Real nominal = 1.0;
    Time T = 1.5;
    Date exDate = today + int(360*T);

    boost::shared_ptr<Payoff> payoff(new PlainVanillaPayoff(Option::Call,
                                                            strike));

    VarianceOption varianceOption1(payoff, nominal, today, exDate);
    varianceOption1.setPricingEngine(engine);

    Real calculated = varianceOption1.NPV();
    Real expected = 0.9104619;
    Real error = std::fabs(calculated-expected);
    if (error>1.0e-7) {
        BOOST_ERROR(
                 "Failed to reproduce variance-option price:"
                 << "\n    expected:   " << std::setprecision(7) << expected
                 << "\n    calculated: " << std::setprecision(7) << calculated
                 << "\n    error:      " << error);
    }


    v0 = 1.5;
    kappa = 2.0;
    theta = 0.01;
    sigma = 0.1;
    rho = -0.5;

    process = boost::shared_ptr<HestonProcess>(
               new HestonProcess(rTS, qTS, s0, v0, kappa, theta, sigma, rho));
    engine = boost::shared_ptr<PricingEngine>(
                               new IntegralHestonVarianceOptionEngine(process));

    strike = 0.7;
    nominal = 1.0;
    T = 1.0;
    exDate = today + int(360*T);

    payoff = boost::shared_ptr<Payoff>(new PlainVanillaPayoff(Option::Put,
                                                              strike));

    VarianceOption varianceOption2(payoff, nominal, today, exDate);
    varianceOption2.setPricingEngine(engine);

    calculated = varianceOption2.NPV();
    expected = 0.0466796;
    error = std::fabs(calculated-expected);
    if (error>1.0e-7) {
        BOOST_ERROR(
                 "Failed to reproduce variance-option price:"
                 << "\n    expected:   " << std::setprecision(7) << expected
                 << "\n    calculated: " << std::setprecision(7) << calculated
                 << "\n    error:      " << error);
    }

}

test_suite* VarianceOptionTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Variance option tests");

    suite->add(QUANTLIB_TEST_CASE(&VarianceOptionTest::testIntegralHeston));
    return suite;
}

