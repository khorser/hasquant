extern "C"
{
    /* utilities */
    const char *qlVersion();
    const char *boostVersion();

    /* helpers */
    void    qlFreeString(char *p);
    int	    qlMinDate();
    int	    qlMinYear();
    int	    qlMinMonth();
    int	    qlMinDay();

    /* settings */
    int	    qlSettingsEvaluationDate();
    char *  qlSettingsSetEvaluationDate(int x);
    void    qlSettingsSetEnforceTodaysHistoricFixings(int x);
    int	    qlSettingsEnforceTodaysHistoricFixings();
}
