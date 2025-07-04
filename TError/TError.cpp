#include "TError.h"


TError::TError(char* error,
  char* function,
  char* file,
  int line)
{
  err.SetStr(error);
  func.SetStr(function);
  fil.SetStr(file);
  lin = line;
  //cout << "\nError: " << er << "Function: " << func << "File: " << fi <<"Line:"<<line<< endl;
}

void TError::what()
{
  cout << "\nError: " << err << "Function: " << func << "File: " << fil << "Line:" << lin << endl;
}