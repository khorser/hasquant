extern "C"
{
    const char *qlVersion();
    void qlFreeString(char *p);
    int qlSettingsEvaluationDate();
    char *qlSettingsSetEvaluationDate(int x);

    int qlMinDate();
    int qlMinYear();
    int qlMinMonth();
    int qlMinDay();
}
