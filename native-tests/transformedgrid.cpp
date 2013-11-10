class PlusOne : std::unary_function<Real,Real> {
public:
    Real operator()(Real x) const { return x+1;};
};

void TransformedGridTest::testConstruction() {

    BOOST_TEST_MESSAGE("Testing transformed grid construction...");

    PlusOne p1;
    Array grid = BoundedGrid(0, 100, 100);
    TransformedGrid tg(grid, p1);
    if (std::fabs(tg.grid(0) - 0.0) > 1e-5) {
        BOOST_ERROR("grid creation failed");
    }

    if (std::fabs(tg.transformedGrid(0) - 1.0) > 1e-5)
        BOOST_ERROR("grid transformation failed");
}

test_suite* TransformedGridTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("transformed grid");
    suite->add(QUANTLIB_TEST_CASE(&TransformedGridTest::testConstruction));
    return suite;
}

