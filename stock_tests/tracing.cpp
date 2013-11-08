namespace {

    class TestCaseCleaner {
      public:
        TestCaseCleaner() {}
        ~TestCaseCleaner() {
            QL_TRACE_ON(std::cerr);
        }
    };

    void testTraceOutput(bool enable,
#if defined(QL_ENABLE_TRACING)
                         const std::string& result) {
#else
                         const std::string&) {
#endif

        TestCaseCleaner cleaner;

        std::ostringstream output;
        if (enable)
            QL_TRACE_ENABLE;
        else
            QL_TRACE_DISABLE;
        QL_TRACE_ON(output);
        int i = 42;
        QL_TRACE_VARIABLE(i);
        i++;

        #if defined(QL_ENABLE_TRACING)
        std::string expected = result;
        #else
        std::string expected = "";
        #endif
        if (output.str() != expected) {
            BOOST_FAIL("wrong trace:\n"
                       "    expected:\n"
                       "\""+ expected + "\"\n"
                       "    written:\n"
                       "\""+ output.str() + "\"");
        }
    }

}


void TracingTest::testOutput() {

    BOOST_TEST_MESSAGE("Testing tracing...");

    testTraceOutput(false, "");
    testTraceOutput(true,  "trace[0]: i = 42\n");
}


test_suite* TracingTest::suite() {
    test_suite* suite = BOOST_TEST_SUITE("Tracing tests");

    suite->add(QUANTLIB_TEST_CASE(&TracingTest::testOutput));
    return suite;
}

