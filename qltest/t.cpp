#include <ql/settings.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
#include <ql/time/calendars/all.hpp>
#include <ql/time/schedule.hpp>

#include <boost/shared_ptr.hpp>

#include <iostream>

using namespace QuantLib;
using namespace std;
using namespace boost;

int main1()
{
    cout << Settings::instance().evaluationDate() << endl;
    try {
         Date d0 = Date(0);
     } catch (Error& e) {
         cout << e.what() << endl;
    }
    Settings::instance().evaluationDate() = Date(500);
    cout << Settings::instance().evaluationDate() << endl;
    Settings::instance().evaluationDate() = Date();
    cout << Settings::instance().evaluationDate() << endl;
    return 0;
}

int main2()
{
  Leg *leg = new Leg();
  leg->push_back(shared_ptr<CashFlow>(new SimpleCashFlow(0, Date())));
  return 0;
}

template <class T>
void catchAndHandle(char **e, T *t)
{
    delete t;
}

int main3()
{
    char *p;
    Leg *l;
    catchAndHandle(&p, l);
}

int main4()
{
    Calendar c = Russia();
    Calendar c3 = Russia();
    Date d(28, Dec, 2012);
    cout << c.isHoliday(d) << endl;
    c.addHoliday(d);
    cout << "c:" << c.isHoliday(d) << endl;
    Calendar c2 = Russia();
    cout << "c2:" << c2.isHoliday(d) << endl;
    cout << "c3:" << c3.isHoliday(d) << endl;
}

int main5()
{
    Calendar c = JointCalendar(Russia(), Ukraine());
    Calendar c3 = JointCalendar(Russia(), Ukraine());
    Date d(28, Dec, 2012);
    cout << c.isHoliday(d) << endl;
    c.addHoliday(d);
    cout << "c:" << c.isHoliday(d) << c.name() << endl;
    Calendar c2 = JointCalendar(Russia(), Ukraine());
    cout << "c2:" << c2.isHoliday(d) << c2.name() << endl;
    cout << "c3:" << c3.isHoliday(d) << c3.name() << endl;
    cout << "c3==c:" << (c3 == c) << endl;
}

void *sfun1()
{
    std::vector<Date> dates;
    dates.push_back(Date(20, Dec, 2012));
    dates.push_back(Date(20, May, 2013));
    return new Schedule(dates , Russia(), Following);
}

void *sfun2(void *s1)
{
    return new Schedule(static_cast<Schedule *>(s1)->until(Date(15, Apr, 2013)));
}

int main()
{
    void *s1 = sfun1();
    void *s2 = sfun2(s1);
    delete static_cast<Schedule *>(s1);
    delete static_cast<Schedule *>(s2);
}
