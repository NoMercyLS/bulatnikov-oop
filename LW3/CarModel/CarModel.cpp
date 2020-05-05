#include "Resources.h"
#include "CCar.h"
#include "CCarRemoteControl.h"
using namespace std;
int main()
{
    CCar myNewToyotaCamry;
    CCarRemoteControl myDriver(myNewToyotaCamry, cin, cout);
    myDriver.CarAutodrive();
}
