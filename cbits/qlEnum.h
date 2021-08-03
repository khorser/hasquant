//ql/time/weekday.hpp
enum Weekday { Sunday    = 1,
  Monday    = 2,
  Tuesday   = 3,
  Wednesday = 4,
  Thursday  = 5,
  Friday    = 6,
  Saturday  = 7,
  Sun = 1,
  Mon = 2,
  Tue = 3,
  Wed = 4,
  Thu = 5,
  Fri = 6,
  Sat = 7
};

//ql/time/date.hpp
enum Month { January   = 1,
  February  = 2,
  March     = 3,
  April     = 4,
  May       = 5,
  June      = 6,
  July      = 7,
  August    = 8,
  September = 9,
  October   = 10,
  November  = 11,
  December  = 12,
  Jan = 1,
  Feb = 2,
  Mar = 3,
  Apr = 4,
  Jun = 6,
  Jul = 7,
  Aug = 8,
  Sep = 9,
  Oct = 10,
  Nov = 11,
  Dec = 12
};

//ql/time/businessdayconvention.hpp
enum BusinessDayConvention {
  // ISDA
  Following,                   /*!< Choose the first business day after
                                 the given holiday. */
  ModifiedFollowing,           /*!< Choose the first business day after
                                 the given holiday unless it belongs
                                 to a different month, in which case
                                 choose the first business day before
                                 the holiday. */
  Preceding,                   /*!< Choose the first business
                                 day before the given holiday. */
  // NON ISDA
  ModifiedPreceding,           /*!< Choose the first business day before
                                 the given holiday unless it belongs
                                 to a different month, in which case
                                 choose the first business day after
                                 the holiday. */
  Unadjusted,                  /*!< Do not adjust. */
  HalfMonthModifiedFollowing,  /*!< Choose the first business day after
                                 the given holiday unless that day
                                 crosses the mid-month (15th) or the
                                 end of month, in which case choose
                                 the first business day before the
                                 holiday. */
  Nearest                      /*!< Choose the nearest business day 
                                 to the given holiday. If both the
                                 preceding and following business
                                 days are equally far away, default
                                 to following business day. */
};

//ql/time/dategenerationrule.hpp
enum Rule {
  Backward,       /*!< Backward from termination date to
                    effective date. */
  Forward,        /*!< Forward from effective date to
                    termination date. */
  Zero,           /*!< No intermediate dates between effective date
                    and termination date. */
  ThirdWednesday, /*!< All dates but effective date and termination
                    date are taken to be on the third wednesday
                    of their month (with forward calculation.) */
  Twentieth,      /*!< All dates but the effective date are
                    taken to be the twentieth of their
                    month (used for CDS schedules in
                    emerging markets.)  The termination
                    date is also modified. */
  TwentiethIMM,   /*!< All dates but the effective date are
                    taken to be the twentieth of an IMM
                    month (used for CDS schedules.)  The
                    termination date is also modified. */
  OldCDS,         /*!< Same as TwentiethIMM with unrestricted date
                    ends and log/short stub coupon period (old
                    CDS convention). */
  CDS,             /*!< Credit derivatives standard rule since 'Big
                     Bang' changes in 2009.  */
  CDS2015,         /*!< Credit derivatives standard rule since
                     December 20th, 2015.  */
};

//ql/time/timeunit.hpp
enum TimeUnit { Days,
  Weeks,
  Months,
  Years,
  Hours,
  Minutes,
  Seconds,
  Milliseconds,
  Microseconds
};

//ql/time/frequency.hpp
enum Frequency { NoFrequency = -1,     //!< null frequency
  Once = 0,             //!< only once, e.g., a zero-coupon
  Annual = 1,           //!< once a year
  Semiannual = 2,       //!< twice a year
  EveryFourthMonth = 3, //!< every fourth month
  Quarterly = 4,        //!< every third month
  Bimonthly = 6,        //!< every second month
  Monthly = 12,         //!< once a month
  EveryFourthWeek = 13, //!< every fourth week
  Biweekly = 26,        //!< every second week
  Weekly = 52,          //!< once a week
  Daily = 365,          //!< once a day
  OtherFrequency = 999  //!< some other unknown frequency
};

//ql/time/imm.hpp, renamed Month to ImmMonth
enum ImmMonth { F =  1, G =  2, H =  3,
  J =  4, K =  5, M =  6,
  N =  7, Q =  8, U =  9,
  V = 10, X = 11, Z = 12 };


/* vim: set ft=cpp ff=unix ts=8 sts=2 sw=2 et: */
