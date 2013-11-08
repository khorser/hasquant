void InstrumentTest::testObservable() {

    BOOST_TEST_MESSAGE("Testing observability of instruments...");

    boost::shared_ptr<SimpleQuote> me1(new SimpleQuote(0.0));
    RelinkableHandle<Quote> h(me1);
    boost::shared_ptr<Instrument> s(new Stock(h));

    Flag f;
    f.registerWith(s);
    
    s->NPV();
    me1->setValue(3.14);
    if (!f.isUp())
        BOOST_FAIL("Observer was not notified of instrument change");
    
    s->NPV();
    f.lower();
    boost::shared_ptr<SimpleQuote> me2(new SimpleQuote(0.0));
    h.linkTo(me2);
    if (!f.isUp())
        BOOST_FAIL("Observer was not notified of instrument change");

    f.lower();
    s->freeze();
    s->NPV();
    me2->setValue(2.71);
    if (f.isUp())
        BOOST_FAIL("Observer was notified of frozen instrument change");
    s->NPV();
    s->unfreeze();
    if (!f.isUp())
        BOOST_FAIL("Observer was not notified of instrument change");
}


test_suite* InstrumentTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Instrument tests");
    suite->add(QUANTLIB_TEST_CASE(&InstrumentTest::testObservable));
    return suite;
}

