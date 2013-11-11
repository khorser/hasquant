void CashFlowsTest::testAccessViolation() {
    BOOST_TEST_MESSAGE("Testing dynamic cast of coupon in Black pricer...");

    SavedSettings backup;

    Date todaysDate(7, April, 2010);
    Date settlementDate(9, April, 2010);
    Settings::instance().evaluationDate() = todaysDate;
    Calendar calendar = TARGET();

    Handle<YieldTermStructure> rhTermStructure(
        flatRate(settlementDate, 0.04875825, Actual365Fixed()));

    Volatility volatility = 0.10;
    Handle<OptionletVolatilityStructure> vol;
    vol = Handle<OptionletVolatilityStructure>(
             boost::shared_ptr<OptionletVolatilityStructure>(
                 new ConstantOptionletVolatility(
                             2,
                             calendar,
                             ModifiedFollowing,
                             volatility,
                             Actual365Fixed())));

    boost::shared_ptr<IborIndex> index3m (new USDLibor(3*Months,
                                                       rhTermStructure));

    Date payDate(20, December, 2013);
    Date startDate(20, September, 2013);
    Date endDate(20, December, 2013);
    Rate spread = 0.0115;
    boost::shared_ptr<IborCouponPricer> pricer(new BlackIborCouponPricer(vol));
    boost::shared_ptr<FloatingRateCoupon> coupon(
        new FloatingRateCoupon(payDate,100, startDate, endDate, 2,
                               index3m, 1.0 , spread / 100));
    coupon->setPricer(pricer);

    try {
        // this caused an access violation in version 1.0
        coupon->amount();
    } catch (Error&) {
        // ok; proper exception thrown
    }
}

void CashFlowsTest::testDefaultSettlementDate() {
    BOOST_TEST_MESSAGE("Testing default evaluation date in cashflows methods...");
    Date today = Settings::instance().evaluationDate();
    Schedule schedule =
        MakeSchedule()
        .from(today-2*Months).to(today+4*Months)
        .withFrequency(Semiannual)
        .withCalendar(TARGET())
        .withConvention(Unadjusted)
        .backwards();

    Leg leg = FixedRateLeg(schedule)
              .withNotionals(100.0)
              .withCouponRates(0.03, Actual360())
              .withPaymentCalendar(TARGET())
              .withPaymentAdjustment(Following);

    Time accruedPeriod = CashFlows::accruedPeriod(leg, false);
    if (accruedPeriod == 0.0)
        BOOST_ERROR("null accrued period with default settlement date");

    BigInteger accruedDays = CashFlows::accruedDays(leg, false);
    if (accruedDays == 0)
        BOOST_ERROR("no accrued days with default settlement date");

    Real accruedAmount = CashFlows::accruedAmount(leg, false);
    if (accruedAmount == 0.0)
        BOOST_ERROR("null accrued amount with default settlement date");
}


test_suite* CashFlowsTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Cash flows tests");
    suite->add(QUANTLIB_TEST_CASE(&CashFlowsTest::testSettings));
    suite->add(QUANTLIB_TEST_CASE(&CashFlowsTest::testAccessViolation));
    suite->add(QUANTLIB_TEST_CASE(&CashFlowsTest::testDefaultSettlementDate));
    return suite;
}

