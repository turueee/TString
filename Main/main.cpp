#include <iostream>
#include "TString.h"

using namespace std;

int main()
{
	TString s("Apple"), r("aAppledd");
	s.Swap(r);
	cout << s << r;
}