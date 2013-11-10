void MoneyTest::testNone() {

    BOOST_TEST_MESSAGE("Testing money arithmetic without conversions...");

    Currency EUR = EURCurrency();

    Money m1 = 50000.0 * EUR;
    Money m2 = 100000.0 * EUR;
    Money m3 = 500000.0 * EUR;

    Money::conversionType = Money::NoConversion;

    Money calculated = m1*3.0 + 2.5*m2 - m3/5.0;
    Decimal x = m1.value()*3.0 + 2.5*m2.value() - m3.value()/5.0;
    Money expected(x, EUR);

    if (calculated != expected) {
        BOOST_FAIL("Wrong result: \n"
                   << "    expected:   " << expected << "\n"
                   << "    calculated: " << calculated);
    }
}


void MoneyTest::testBaseCurrency() {

    BOOST_TEST_MESSAGE("Testing money arithmetic with conversion "
                       "to base currency...");

    Currency EUR = EURCurrency(), GBP = GBPCurrency(), USD = USDCurrency();

    Money m1 = 50000.0 * GBP;
    Money m2 = 100000.0 * EUR;
    Money m3 = 500000.0 * USD;

    ExchangeRateManager::instance().clear();
    ExchangeRate eur_usd = ExchangeRate(EUR, USD, 1.2042);
    ExchangeRate eur_gbp = ExchangeRate(EUR, GBP, 0.6612);
    ExchangeRateManager::instance().add(eur_usd);
    ExchangeRateManager::instance().add(eur_gbp);

    Money::conversionType = Money::BaseCurrencyConversion;
    Money::baseCurrency = EUR;

    Money calculated = m1*3.0 + 2.5*m2 - m3/5.0;

    Rounding round = Money::baseCurrency.rounding();
    Decimal x = round(m1.value()*3.0/eur_gbp.rate()) + 2.5*m2.value()
              - round(m3.value()/(5.0*eur_usd.rate()));
    Money expected(x, EUR);

    Money::conversionType = Money::NoConversion;

    if (calculated != expected) {
        BOOST_FAIL("Wrong result: \n"
                   << "    expected:   " << expected << "\n"
                   << "    calculated: " << calculated);
    }
}


void MoneyTest::testAutomated() {

    BOOST_TEST_MESSAGE("Testing money arithmetic with automated conversion...");

    Currency EUR = EURCurrency(), GBP = GBPCurrency(), USD = USDCurrency();

    Money m1 = 50000.0 * GBP;
    Money m2 = 100000.0 * EUR;
    Money m3 = 500000.0 * USD;

    ExchangeRateManager::instance().clear();
    ExchangeRate eur_usd = ExchangeRate(EUR, USD, 1.2042);
    ExchangeRate eur_gbp = ExchangeRate(EUR, GBP, 0.6612);
    ExchangeRateManager::instance().add(eur_usd);
    ExchangeRateManager::instance().add(eur_gbp);

    Money::conversionType = Money::AutomatedConversion;

    Money calculated = (m1*3.0 + 2.5*m2) - m3/5.0;

    Rounding round = m1.currency().rounding();
    Decimal x = m1.value()*3.0 + round(2.5*m2.value()*eur_gbp.rate())
              - round((m3.value()/5.0)*eur_gbp.rate()/eur_usd.rate());
    Money expected(x, GBP);

    Money::conversionType = Money::NoConversion;

    if (calculated != expected) {
        BOOST_FAIL("Wrong result: \n"
                   << "    expected:   " << expected << "\n"
                   << "    calculated: " << calculated);
    }
}

test_suite* MoneyTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Money tests");
    suite->add(QUANTLIB_TEST_CASE(&MoneyTest::testNone));
    suite->add(QUANTLIB_TEST_CASE(&MoneyTest::testBaseCurrency));
    suite->add(QUANTLIB_TEST_CASE(&MoneyTest::testAutomated));
    return suite;
}

