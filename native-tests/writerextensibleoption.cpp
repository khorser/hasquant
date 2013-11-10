void WriterExtensibleOptionTest::testAnalyticWriterExtensibleOptionEngine() {
    BOOST_TEST_MESSAGE("Testing analytic engine for writer-extensible option...");

    // What we need for the option (tests):
    Option::Type type = Option::Call;
    Real strike1 = 90.0;
    Real strike2 = 82.0;
    DayCounter dc = Actual360();
    Date today = Settings::instance().evaluationDate();
    Date exDate1 = today + 180;
    Date exDate2 = today + 270;

    boost::shared_ptr<SimpleQuote> spot(new SimpleQuote(80.0));
    boost::shared_ptr<SimpleQuote> qRate(new SimpleQuote(0.0));
    boost::shared_ptr<YieldTermStructure> dividendTS =
        flatRate(today, qRate, dc);
    boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.10));
    boost::shared_ptr<YieldTermStructure> riskFreeTS =
        flatRate(today, rRate, dc);
    boost::shared_ptr<SimpleQuote> vol(new SimpleQuote(0.30));
    boost::shared_ptr<BlackVolTermStructure> blackVolTS =
        flatVol(today, vol, dc);

    // B&S process (needed for the engine):
    const boost::shared_ptr<GeneralizedBlackScholesProcess> process(
        new GeneralizedBlackScholesProcess(
                    Handle<Quote>(spot),
                    Handle<YieldTermStructure>(dividendTS),
                    Handle<YieldTermStructure>(riskFreeTS),
                    Handle<BlackVolTermStructure>(blackVolTS)));

    // The engine:
    boost::shared_ptr<PricingEngine> engine(
                           new AnalyticWriterExtensibleOptionEngine(process));

    // Create the arguments:
    boost::shared_ptr<PlainVanillaPayoff> payoff1(
                                       new PlainVanillaPayoff(type, strike1));
    boost::shared_ptr<Exercise> exercise1(new EuropeanExercise(exDate1));
    boost::shared_ptr<PlainVanillaPayoff> payoff2(
                                       new PlainVanillaPayoff(type, strike2));
    boost::shared_ptr<Exercise> exercise2(new EuropeanExercise(exDate2));

    // Create the option by calling the constructor:
    WriterExtensibleOption option(payoff1, exercise1,
                                  payoff2, exercise2);

    //Set the engine of our option:
    option.setPricingEngine(engine);

    //Compare the calculated NPV value to the theoretical value:
    Real calculated = option.NPV();
    Real expected = 6.8238;

    Real tolerance = 1e-4;

    if (std::fabs(calculated-expected) > tolerance) {
        REPORT_FAILURE("value", payoff1, payoff2, exercise1, exercise2,
                       spot->value(), t1, t2, qRate->value(), rRate->value(),
                       today, vol->value(), expected, calculated, tolerance);
    }
}

test_suite* WriterExtensibleOptionTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Writer-extensible option tests");

    suite->add(QUANTLIB_TEST_CASE(
       &WriterExtensibleOptionTest::testAnalyticWriterExtensibleOptionEngine));

    return suite;
}
