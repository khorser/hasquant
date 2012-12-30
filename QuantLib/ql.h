extern "C"
{
    const char *qlVersion();
    const char *boostVersion();
    void qlFreeString(char *p);
    int qlSettingsEvaluationDate();
    char *qlSettingsSetEvaluationDate(int x);

    int qlMinDate();
    int qlMinYear();
    int qlMinMonth();
    int qlMinDay();
}
