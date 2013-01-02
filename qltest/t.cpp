#include <ql/settings.hpp>
#include <ql/cashflows/cashflows.hpp>
#include <ql/cashflows/simplecashflow.hpp>
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

int main()
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
