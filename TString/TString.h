#pragma once
#include <iostream>
using namespace std;
class TString
{
protected:
  char* str;
  int len;
public:
  TString();
  TString(const TString& p);
  TString(TString&& p) noexcept;
  TString(char* str_, int len_);
  TString(const char* str_);
  ~TString();

  void GetStr(char** line);
  int GetLen();

  void SetStr(char* str_);
  void SetLen(int i);

  TString operator+(const TString& line);
  TString operator*(int repeat);
  TString operator=(const TString& line);

  bool operator==(const TString& line);
  bool operator!=(const TString& line);
  bool operator<(const TString& line);
  bool operator>(const TString& line);

  TString operator[](int index);

  void Split(const TString& line, char*** split, int* outCount);
  int WordSearch(char* word);
  int AllWordSearch(char* word);
  void AllIndexWordSearch(char* word, int** indexes);
  int LetterSearch(char letter);
  int CountOfIncludes(char letter);
  void LenWordsOfIncludes(char letter, int** wordslen);
  void SetOfLetters(char** setletters);
  void CountsOfLetters(int** setcounts);
  char MostPopularLetter();
  int Insert(int position, char* word);
  int Insert(int position, const TString& elem);

  void IntToString(int num);
  int StringToInt();

  friend ostream& operator<<(ostream& o, TString& line);
  friend istream& operator>>(istream& i, TString& line);
};

int strlen(char* str);
int cstrlen(const char* str);