#include "TString.h"

int main()
{
  char d[256] = "w";
  char c[256] = "aba";
  TString b(d),t(c),re;

  b.IntToString(2345);

}