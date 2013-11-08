namespace {

    struct LookbackOptionData {
        Option::Type type;
        Real strike;
        Real minmax;
        Real s;        // spot
        Rate q;        // dividend
        Rate r;        // risk-free rate
        Time t;        // time to maturity
        Volatility v;  // volatility
        Real result;   // result
        Real tol;      // tolerance
    };

}


void LookbackOptionTest::testAnalyticContinuousFloatingLookback() {

    BOOST_TEST_MESSAGE(
           "Testing analytic continuous floating-strike lookback options...");


    LookbackOptionData values[] = {

        // data from "Option Pricing Formulas", Haug, 1998, pg.61-62

        //    type, strike, minmax,     s,    q,    r,    t,    v,  result, tol
        { Option::Call,      0,    100, 120.0, 0.06, 0.10, 0.50, 0.30, 25.3533, 1.0e-4},

        // data from "Connecting discrete and continuous path-dependent options",
        // Broadie, Glasserman & Kou, 1999, pg.70-74

        //    type, strike, minmax,     s,    q,    r,    t,    v,  result, tol
        { Option::Call,      0,    100, 100.0, 0.00, 0.05, 1.00, 0.30, 23.7884, 1.0e-4},
        { Option::Call,      0,    100, 100.0, 0.00, 0.05, 0.20, 0.30, 10.7190, 1.0e-4},
        { Option::Call,      0,    100, 110.0, 0.00, 0.05, 0.20, 0.30, 14.4597, 1.0e-4},
        {  Option::Put,      0,    100, 100.0, 0.00, 0.10, 0.50, 0.30, 15.3526, 1.0e-4},
        {  Option::Put,      0,    110, 100.0, 0.00, 0.10, 0.50, 0.30, 16.8468, 1.0e-4},
        {  Option::Put,      0,    120, 100.0, 0.00, 0.10, 0.50, 0.30, 21.0645, 1.0e-4}

    };

    DayCounter dc = Actual360();
    Date today = Date::todaysDate();

    boost::shared_ptr<SimpleQuote> spot(new SimpleQuote(0.0));
    boost::shared_ptr<SimpleQuote> qRate(new SimpleQuote(0.0));
    boost::shared_ptr<YieldTermStructure> qTS = flatRate(today, qRate, dc);
    boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.0));
    boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);
    boost::shared_ptr<SimpleQuote> vol(new SimpleQuote(0.0));
    boost::shared_ptr<BlackVolTermStructure> volTS = flatVol(today, vol, dc);

    for (Size i=0; i<LENGTH(values); i++) {
        Date exDate = today + Integer(values[i].t*360+0.5);
        boost::shared_ptr<Exercise> exercise(new EuropeanExercise(exDate));

        spot ->setValue(values[i].s);
        qRate->setValue(values[i].q);
        rRate->setValue(values[i].r);
        vol  ->setValue(values[i].v);

        boost::shared_ptr<FloatingTypePayoff> payoff(
                                      new FloatingTypePayoff(values[i].type));

        boost::shared_ptr<BlackScholesMertonProcess> stochProcess(
                            new BlackScholesMertonProcess(
                                       Handle<Quote>(spot),
                                       Handle<YieldTermStructure>(qTS),
                                       Handle<YieldTermStructure>(rTS),
                                       Handle<BlackVolTermStructure>(volTS)));

        boost::shared_ptr<PricingEngine> engine(
                  new AnalyticContinuousFloatingLookbackEngine(stochProcess));

        ContinuousFloatingLookbackOption option(values[i].minmax,
                                                payoff,
                                                exercise);
        option.setPricingEngine(engine);

        Real calculated = option.NPV();
        Real expected = values[i].result;
        Real error = std::fabs(calculated-expected);
        if (error>values[i].tol) {
            REPORT_FAILURE_FLOATING("value", values[i].minmax, payoff,
                                    exercise, values[i].s, values[i].q,
                                    values[i].r, today, values[i].v,
                                    expected, calculated, error,
                                    values[i].tol);
        }
    }
}


void LookbackOptionTest::testAnalyticContinuousFixedLookback() {

    BOOST_TEST_MESSAGE(
              "Testing analytic continuous fixed-strike lookback options...");

    LookbackOptionData values[] = {
        // data from "Option Pricing Formulas", Haug, 1998, pg.63-64
        //    type, strike, minmax,     s,    q,    r,    t,    v,  result, tol
        { Option::Call,    95,     100, 100.0, 0.00, 0.10, 0.50, 0.10, 13.2687, 1.0e-4},
        { Option::Call,    95,     100, 100.0, 0.00, 0.10, 0.50, 0.20, 18.9263, 1.0e-4},
        { Option::Call,    95,     100, 100.0, 0.00, 0.10, 0.50, 0.30, 24.9857, 1.0e-4},
        { Option::Call,    100,    100, 100.0, 0.00, 0.10, 0.50, 0.10,  8.5126, 1.0e-4},
        { Option::Call,    100,    100, 100.0, 0.00, 0.10, 0.50, 0.20, 14.1702, 1.0e-4},
        { Option::Call,    100,    100, 100.0, 0.00, 0.10, 0.50, 0.30, 20.2296, 1.0e-4},
        { Option::Call,    105,    100, 100.0, 0.00, 0.10, 0.50, 0.10,  4.3908, 1.0e-4},
        { Option::Call,    105,    100, 100.0, 0.00, 0.10, 0.50, 0.20,  9.8905, 1.0e-4},
        { Option::Call,    105,    100, 100.0, 0.00, 0.10, 0.50, 0.30, 15.8512, 1.0e-4},
        { Option::Call,    95,     100, 100.0, 0.00, 0.10, 1.00, 0.10, 18.3241, 1.0e-4},
        { Option::Call,    95,     100, 100.0, 0.00, 0.10, 1.00, 0.20, 26.0731, 1.0e-4},
        { Option::Call,    95,     100, 100.0, 0.00, 0.10, 1.00, 0.30, 34.7116, 1.0e-4},
        { Option::Call,    100,    100, 100.0, 0.00, 0.10, 1.00, 0.10, 13.8000, 1.0e-4},
        { Option::Call,    100,    100, 100.0, 0.00, 0.10, 1.00, 0.20, 21.5489, 1.0e-4},
        { Option::Call,    100,    100, 100.0, 0.00, 0.10, 1.00, 0.30, 30.1874, 1.0e-4},
        { Option::Call,    105,    100, 100.0, 0.00, 0.10, 1.00, 0.10,  9.5445, 1.0e-4},
        { Option::Call,    105,    100, 100.0, 0.00, 0.10, 1.00, 0.20, 17.2965, 1.0e-4},
        { Option::Call,    105,    100, 100.0, 0.00, 0.10, 1.00, 0.30, 25.9002, 1.0e-4},

        {  Option::Put,    95,     100, 100.0, 0.00, 0.10, 0.50, 0.10,  0.6899, 1.0e-4},
        {  Option::Put,    95,     100, 100.0, 0.00, 0.10, 0.50, 0.20,  4.4448, 1.0e-4},
        {  Option::Put,    95,     100, 100.0, 0.00, 0.10, 0.50, 0.30,  8.9213, 1.0e-4},
        {  Option::Put,    100,    100, 100.0, 0.00, 0.10, 0.50, 0.10,  3.3917, 1.0e-4},
        {  Option::Put,    100,    100, 100.0, 0.00, 0.10, 0.50, 0.20,  8.3177, 1.0e-4},
        {  Option::Put,    100,    100, 100.0, 0.00, 0.10, 0.50, 0.30, 13.1579, 1.0e-4},
        {  Option::Put,    105,    100, 100.0, 0.00, 0.10, 0.50, 0.10,  8.1478, 1.0e-4},
        {  Option::Put,    105,    100, 100.0, 0.00, 0.10, 0.50, 0.20, 13.0739, 1.0e-4},
        {  Option::Put,    105,    100, 100.0, 0.00, 0.10, 0.50, 0.30, 17.9140, 1.0e-4},
        {  Option::Put,    95,     100, 100.0, 0.00, 0.10, 1.00, 0.10,  1.0534, 1.0e-4},
        {  Option::Put,    95,     100, 100.0, 0.00, 0.10, 1.00, 0.20,  6.2813, 1.0e-4},
        {  Option::Put,    95,     100, 100.0, 0.00, 0.10, 1.00, 0.30, 12.2376, 1.0e-4},
        {  Option::Put,    100,    100, 100.0, 0.00, 0.10, 1.00, 0.10,  3.8079, 1.0e-4},
        {  Option::Put,    100,    100, 100.0, 0.00, 0.10, 1.00, 0.20, 10.1294, 1.0e-4},
        {  Option::Put,    100,    100, 100.0, 0.00, 0.10, 1.00, 0.30, 16.3889, 1.0e-4},
        {  Option::Put,    105,    100, 100.0, 0.00, 0.10, 1.00, 0.10,  8.3321, 1.0e-4},
        {  Option::Put,    105,    100, 100.0, 0.00, 0.10, 1.00, 0.20, 14.6536, 1.0e-4},
        {  Option::Put,    105,    100, 100.0, 0.00, 0.10, 1.00, 0.30, 20.9130, 1.0e-4}

    };

    DayCounter dc = Actual360();
    Date today = Date::todaysDate();

    boost::shared_ptr<SimpleQuote> spot(new SimpleQuote(0.0));
    boost::shared_ptr<SimpleQuote> qRate(new SimpleQuote(0.0));
    boost::shared_ptr<YieldTermStructure> qTS = flatRate(today, qRate, dc);
    boost::shared_ptr<SimpleQuote> rRate(new SimpleQuote(0.0));
    boost::shared_ptr<YieldTermStructure> rTS = flatRate(today, rRate, dc);
    boost::shared_ptr<SimpleQuote> vol(new SimpleQuote(0.0));
    boost::shared_ptr<BlackVolTermStructure> volTS = flatVol(today, vol, dc);

    for (Size i=0; i<LENGTH(values); i++) {
        Date exDate = today + Integer(values[i].t*360+0.5);
        boost::shared_ptr<Exercise> exercise(new EuropeanExercise(exDate));

        spot ->setValue(values[i].s);
        qRate->setValue(values[i].q);
        rRate->setValue(values[i].r);
        vol  ->setValue(values[i].v);

        boost::shared_ptr<StrikedTypePayoff> payoff(
                     new PlainVanillaPayoff(values[i].type, values[i].strike));

        boost::shared_ptr<BlackScholesMertonProcess> stochProcess(
                            new BlackScholesMertonProcess(
                                       Handle<Quote>(spot),
                                       Handle<YieldTermStructure>(qTS),
                                       Handle<YieldTermStructure>(rTS),
                                       Handle<BlackVolTermStructure>(volTS)));

        boost::shared_ptr<PricingEngine> engine(
                     new AnalyticContinuousFixedLookbackEngine(stochProcess));

        ContinuousFixedLookbackOption option(values[i].minmax,
                                             payoff,
                                             exercise);
        option.setPricingEngine(engine);

        Real calculated = option.NPV();
        Real expected = values[i].result;
        Real error = std::fabs(calculated-expected);
        if (error>values[i].tol) {
            REPORT_FAILURE_FIXED("value", values[i].minmax, payoff, exercise,
                                 values[i].s, values[i].q, values[i].r, today,
                                 values[i].v, expected, calculated, error,
                                 values[i].tol);
        }
    }
}


test_suite* LookbackOptionTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Lookback option tests");

    suite->add(QUANTLIB_TEST_CASE(
                &LookbackOptionTest::testAnalyticContinuousFloatingLookback));
    suite->add(QUANTLIB_TEST_CASE(
                &LookbackOptionTest::testAnalyticContinuousFixedLookback));
    return suite;
}

