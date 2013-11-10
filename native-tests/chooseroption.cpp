void ChooserOptionTest::testAnalyticSimpleChooserEngine(){

    BOOST_TEST_MESSAGE("Testing analytic simple chooser option...");

    /* The data below are from
       "Complete Guide to Option Pricing Formulas", Espen Gaarder Haug
       pages 39-40
    */
    DayCounter dc = Actual360();
    Date today = Date::todaysDate();

    boost::shared_ptr<SimpleQuote> spot(new SimpleQuote(50.0));
    boost::shared_ptr<SimpleQuote> qRate(new SimpleQuote(0.0));
    boost::shared_ptr<YieldTermStructure> qTS = flatRate(today, qRate, dc);
    boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.08));
    boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);
    boost::shared_ptr<SimpleQuote> vol(new SimpleQuote(0.25));
    boost::shared_ptr<BlackVolTermStructure> volTS = flatVol(today, vol, dc);

    boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new
        BlackScholesMertonProcess(Handle<Quote>(spot),
                                  Handle<YieldTermStructure>(qTS),
                                  Handle<YieldTermStructure>(rTS),
                                  Handle<BlackVolTermStructure>(volTS)));

    boost::shared_ptr<PricingEngine> engine(
        new AnalyticSimpleChooserEngine(stochProcess));

    Real strike = 50.0;

    Date exerciseDate = today + 180;
    boost::shared_ptr<Exercise> exercise(new EuropeanExercise(exerciseDate));

    Date choosingDate = today + 90;
    SimpleChooserOption option(choosingDate,strike,exercise);
    option.setPricingEngine(engine);

    Real calculated = option.NPV();
     Real expected = 6.1071;
    Real tolerance = 3e-5;
    if (std::fabs(calculated-expected) > tolerance) {
        REPORT_FAILURE("value", choosingDate,
                       exercise, spot->value(),
                       qRate->value(), rRate->value(), today,
                       vol->value(), expected, calculated, tolerance);
    }

}

test_suite* ChooserOptionTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Chooser option tests");

    suite->add(QUANTLIB_TEST_CASE(
        &ChooserOptionTest::testAnalyticSimpleChooserEngine));

    return suite;
}
