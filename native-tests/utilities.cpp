namespace QuantLib {

    std::string payoffTypeToString(const boost::shared_ptr<Payoff>& h) {

        CHECK_DOWNCAST(PlainVanillaPayoff, "plain-vanilla");
        CHECK_DOWNCAST(CashOrNothingPayoff, "cash-or-nothing");
        CHECK_DOWNCAST(AssetOrNothingPayoff, "asset-or-nothing");
        CHECK_DOWNCAST(SuperSharePayoff, "super-share");
        CHECK_DOWNCAST(GapPayoff, "gap");

        QL_FAIL("unknown payoff type");
    }


    std::string exerciseTypeToString(const boost::shared_ptr<Exercise>& h) {

        CHECK_DOWNCAST(EuropeanExercise, "European");
        CHECK_DOWNCAST(AmericanExercise, "American");
        CHECK_DOWNCAST(BermudanExercise, "Bermudan");

        QL_FAIL("unknown exercise type");
    }


    boost::shared_ptr<YieldTermStructure>
    flatRate(const Date& today,
             const boost::shared_ptr<Quote>& forward,
             const DayCounter& dc) {
        return boost::shared_ptr<YieldTermStructure>(
                          new FlatForward(today, Handle<Quote>(forward), dc));
    }

    boost::shared_ptr<YieldTermStructure>
    flatRate(const Date& today, Rate forward, const DayCounter& dc) {
        return flatRate(
               today, boost::shared_ptr<Quote>(new SimpleQuote(forward)), dc);
    }

    boost::shared_ptr<YieldTermStructure>
    flatRate(const boost::shared_ptr<Quote>& forward,
             const DayCounter& dc) {
        return boost::shared_ptr<YieldTermStructure>(
              new FlatForward(0, NullCalendar(), Handle<Quote>(forward), dc));
    }

    boost::shared_ptr<YieldTermStructure>
    flatRate(Rate forward, const DayCounter& dc) {
        return flatRate(boost::shared_ptr<Quote>(new SimpleQuote(forward)),
                        dc);
    }


    boost::shared_ptr<BlackVolTermStructure>
    flatVol(const Date& today,
            const boost::shared_ptr<Quote>& vol,
            const DayCounter& dc) {
        return boost::shared_ptr<BlackVolTermStructure>(new
            BlackConstantVol(today, NullCalendar(), Handle<Quote>(vol), dc));
    }

    boost::shared_ptr<BlackVolTermStructure>
    flatVol(const Date& today, Volatility vol,
            const DayCounter& dc) {
        return flatVol(today,
                       boost::shared_ptr<Quote>(new SimpleQuote(vol)),
                       dc);
    }

    boost::shared_ptr<BlackVolTermStructure>
    flatVol(const boost::shared_ptr<Quote>& vol,
            const DayCounter& dc) {
        return boost::shared_ptr<BlackVolTermStructure>(new
            BlackConstantVol(0, NullCalendar(), Handle<Quote>(vol), dc));
    }

    boost::shared_ptr<BlackVolTermStructure>
    flatVol(Volatility vol,
            const DayCounter& dc) {
        return flatVol(boost::shared_ptr<Quote>(new SimpleQuote(vol)), dc);
    }


    Real relativeError(Real x1, Real x2, Real reference) {
        if (reference != 0.0)
            return std::fabs(x1-x2)/reference;
        else
            // fall back to absolute error
            return std::fabs(x1-x2);
    }


    IndexHistoryCleaner::IndexHistoryCleaner() {}

    IndexHistoryCleaner::~IndexHistoryCleaner() {
        IndexManager::instance().clearHistories();
    }

}
