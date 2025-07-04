#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "TString.h"


class TError
{
protected:
  TString err;
  TString func;
  TString fil;
  int lin;
public:
  TError(char* error,
    char* function,
    char* file,
    int line);
  void what();
};

#define THROW_ERROR(err,...) throw TError(err, __func__, __FILE__, __LINE__)


