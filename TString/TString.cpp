#include "TString.h"

TString::TString()
{
  str = new char[1] {0};
  len = 1;
}


TString::TString(const TString& p)
{
  len = p.len;
  if (p.str != nullptr)
  {
    str = new char[len + 1];
    for (int i = 0; i < len; ++i)
    {
      str[i] = p.str[i];
    }
    str[len] = '\0';
  }
  else
    throw "p.str == nullptr";
}


TString::TString(TString&& p) noexcept
{
  len = p.len;
  str = p.str;

  p.str = nullptr;
  len = 0;
}


TString::TString(char* str_, int len_)
{
  if (len_ <= 0)
    throw "len_ <= 0";
  if (strlen(str_) < len)
    throw "strlen(str_) < len_";
  len = len_;
  str = new char[len + 1];
  for (int i = 0; i < len; ++i)
    str[i] = str_[i];
  str[len] = '\0';
}


TString::TString(const char* str_)
{
  if (str_ == nullptr)
    throw "str_ == nullptr";
  len = cstrlen(str_);
  str = new char[len + 1];
  for (int i = 0; i < len; ++i)
    str[i] = str_[i];
  str[len] = '\0';
}


TString::~TString()
{
  if (str != nullptr)
    delete[]str;
  str = nullptr;
}


void TString::GetStr(char** line)
{
  if (str != nullptr)
  {
    (*line) = new char[len + 1];
    for (int i = 0; i < len; ++i)
      (*line)[i] = str[i];
    (*line)[len] = '\0';
  }
  else
    line = nullptr;
}


int TString::GetLen()
{
  return len;
}


void TString::SetStr(char* str_)
{
  if (str_ == nullptr)
    throw "str_==nullptr";
  delete[] str;
  len = strlen(str_);
  str = new char[len + 1];
  for (int i = 0; i < len; ++i)
    str[i] = str_[i];
  str[len] = '\0';
}


void TString::SetLen(int len_)
{
  if (len_ <= 0)
    throw "ken_ <= 0";
  if (len == len_)
    return;
  len = len_;
  char* str_;
  this->GetStr(&str_);
  str = new char[len + 1];
  for (int i = 0; i < len; ++i)
    str[i] = str_[i];
  delete[] str_;
}


TString TString::operator+(const TString& line)
{
  char* nstr = new char[len + line.len + 1];
  for (int i = 0; i < len; ++i)
    nstr[i] = str[i];
  for (int i = 0; i < line.len; ++i)
    nstr[i + len] = line.str[i];
  nstr[len + line.len] = '\0';
  return TString(nstr);
}


TString TString::operator*(int repeat)
{
  if (repeat <= 0)
    throw "rep <= 0";
  char* buf = new char[len * repeat + 1];
  for (int i = 0; i < repeat; ++i)
  {
    for (int j = 0; j < len; ++j)
      buf[len * i + j] = str[j];
  }
  buf[len * repeat] = '\0';
  return TString(buf);
}


void TString::Split(const TString& line, char*** split, int* outCount)
{
  // Получаем позиции разделителей
  int* indexes = nullptr;
  int wordCount = this->AllWordSearch(line.str);
  this->AllIndexWordSearch(line.str, &indexes);

  // Первый проход: подсчет непустых подстрок
  int realCount = 0;
  int prevPos = 0;

  for (int i = 0; i <= wordCount; i++) {
    int currentPos = (i < wordCount) ? indexes[i] : len;
    if (currentPos > prevPos) {
      realCount++;
    }
    prevPos = currentPos + line.len;
  }

  *outCount = realCount;
  *split = realCount ? new char* [realCount] : nullptr;

  // Второй проход: заполнение подстрок
  int strIndex = 0;
  prevPos = 0;

  for (int i = 0; i <= wordCount; i++) {
    int currentPos = (i < wordCount) ? indexes[i] : len;

    if (currentPos > prevPos) {
      int substrLen = currentPos - prevPos;
      (*split)[strIndex] = new char[substrLen + 1];

      // Ручное копирование символов
      for (int j = 0; j < substrLen; j++) {
        (*split)[strIndex][j] = str[prevPos + j];
      }
      (*split)[strIndex][substrLen] = '\0';

      strIndex++;
    }

    prevPos = currentPos + line.len;
  }

  delete[] indexes;
}



TString TString::operator=(const TString& line)
{
  len = line.len;
  str = new char[len + 1];
  for (int i = 0; i < len; ++i)
    str[i] = line.str[i];
  str[len] = '\0';
  return *this;
}


bool TString::operator==(const TString& line)
{
  if (len != line.len)
    return false;
  bool f = true;
  for (int i = 0; i < len; ++i)
  {
    if (str[i] != line.str[i])
      f = false;
  }
  return f;
}


bool TString::operator!=(const TString& line)
{
  if (len != line.len)
    return true;
  bool f = false;
  for (int i = 0; i < len; ++i)
  {
    if (str[i] != line.str[i])
      f = true;
  }
  return f;
}


bool TString::operator<(const TString& line)
{
  return len < line.len;
}


bool TString::operator>(const TString& line)
{
  return len > line.len;
}


TString TString::operator[](int index)
{
  if (index >= len)
    throw "size";
  TString a;
  char res[2];
  res[0] = str[index];
  res[1] = '\0';
  return TString(res);
}


int TString::WordSearch(char* word)
{
  int l = strlen(word);
  if (l > len)
    throw "l > len";
  for (int i = 0; i < len - l + 1; ++i)
  {
    if (str[i] == word[0])
    {
      bool log = true;
      for (int j = 1; j < l; ++j)
      {
        if (str[i + j] != word[j])
        {
          log = false;
        }
      }
      if (log == true)
        return i;
    }
  }
  cout << "Not founded\n";
  return -1;
}


int TString::AllWordSearch(char* word)
{
  int l = strlen(word);
  int count = 0;
  if (l > len)
    throw "l > len";
  for (int i = 0; i < len - l + 1; ++i)
  {
    if (str[i] == word[0])
    {
      bool log = true;
      for (int j = 1; j < l; ++j)
      {
        if (str[i + j] != word[j])
        {
          log = false;
        }
      }
      if (log == true)
      {
        count++;
        i += l - 1;
      }
    }
  }
  return count;
}


void TString::AllIndexWordSearch(char* word, int** indexes)
{
  *indexes = new int[this->AllWordSearch(word) + 1];
  int l = strlen(word);
  int count = 0;

  if (l > len)
    throw "l > len";

  for (int i = 0; i < len - l + 1; ++i) {
    if (str[i] == word[0]) {
      bool log = true;
      for (int j = 1; j < l; ++j) {
        if (str[i + j] != word[j]) {
          log = false;
          break;
        }
      }
      if (log) {
        (*indexes)[count++] = i;
        i += l - 1;
      }
    }
  }
}


int TString::LetterSearch(char letter)
{
  for (int i = 0; i < len; ++i)
  {
    if (str[i] == letter)
      return i;
  }
  return -1;
}

int TString::CountOfIncludes(char letter)
{
  int count = 0;
  for (int i = 0; i < len; ++i)
  {
    if (str[i] == letter)
      ++count;
  }
  return count;
}


char TString::MostPopularLetter()
{
  char* set;
  int* setcount;
  this->SetOfLetters(&set);
  this->CountsOfLetters(&setcount);
  char mp;
  int max = 0;
  for (int i = 0; i < strlen(set); ++i)
  {
    if (max < setcount[i])
    {
      max = setcount[i];
      mp = set[i];
    }
  }
  delete[] set;
  delete[] setcount;
  return mp;
}


void TString::LenWordsOfIncludes(char letter, int** wordslen)
{
  *wordslen = new int[this->CountOfIncludes(letter) + 1];
  int i = 0, t = 0, start = 0;
  for (i = 1; i < len; ++i)
  {
    if (str[i] == letter)
    {
      if (str[i - 1] != letter)
      {
        *wordslen[t] = i - start;
        start = i + 1;
        ++t;
      }
      else
      {
        start = i + 1;
      }
    }
  }
  if (str[len - 1] != letter)
  {
    *wordslen[t] = i - start;
  }
}


void TString::SetOfLetters(char** setletters)
{
  (*setletters) = new char[len + 1];
  int flag = 0;
  (*setletters)[0] = str[0];
  flag++;
  for (int i = 1; i < len; ++i)
  {
    bool log = true;
    for (int j = 0; j < flag; ++j)
    {
      if ((*setletters)[j] == str[i])
        log = false;
    }
    if (log == true)
    {
      (*setletters)[flag] = str[i];
      flag++;
    }
  }
  (*setletters)[flag] = '\0';
}


void TString::CountsOfLetters(int** setcounts)
{
  char* setletters;
  this->SetOfLetters(&setletters);
  (*setcounts) = new int[strlen(setletters)];
  for (int i = 0; i < strlen(setletters); ++i)
  {
    (*setcounts)[i] = this->CountOfIncludes(setletters[i]);
  }
  delete[] setletters;
}


int TString::Insert(int position, char* word)
{
  int l = strlen(word);
  char* newstr = new char[len + l + 1];
  int i = 0;
  while (i < position)
  {
    newstr[i] = str[i];
    ++i;
  }
  while (position <= i && i < position + l)
  {
    newstr[i] = word[i - position];
    ++i;
  }
  while (position + l <= i && i < len + l)
  {
    newstr[i] = str[i - l];
    ++i;
  }
  newstr[len + l] = '\0';
  this->SetStr(newstr);
  delete[] newstr;
  return position;
}


int TString::Insert(int position, const TString& elem)
{
  char* newstr = new char[len + elem.len + 1];
  int i = 0;
  while (i < position)
  {
    newstr[i] = str[i];
    ++i;
  }
  while (position <= i && i < position + elem.len)
  {
    newstr[i] = elem.str[i - position];
    ++i;
  }
  while (position + elem.len <= i && i < len + elem.len)
  {
    newstr[i] = str[i - elem.len];
    ++i;
  }
  newstr[len + elem.len] = '\0';
  this->SetStr(newstr);
  delete[] newstr;
  return position;
}

void TString::IntToString(int num)
{
    this->SetLen(0);
    while (num>0)
    {
        int digit = num % 10;
        char* d;
        switch (digit)
        {
        case 0:
            d = "0";
            break;
        case 1:
            d = "1";
            break;
        case 2:
            d = "2";
            break;
        case 3:
            d = "3";
            break;
        case 4:
            d = "4";
            break;
        case 5:
            d = "5";
            break;
        case 6:
            d = "6";
            break;
        case 7:
            d = "7";
            break;
        case 8:
            d = "8";
            break;
        case 9:
            d = "9";
            break;
        }

    }


}

int TString::StringToInt()
{
    return 0;
}


ostream& operator<<(ostream& o, TString& line)
{
  o << "Length of string: " << line.len << "\n" << "String: " << line.str << "\n";
  return o;
}


istream& operator>>(istream& i, TString& line)
{
  char buf[256];
  cout << "Enter a string: ";
  i >> buf;
  line.SetStr(buf);
  return i;
}


int strlen(char* str)
{
  int counter = 0;
  if (str == nullptr)
    throw "str == nullptr";
  while (str[counter] != '\0')
    counter++;
  return counter;
}


int cstrlen(const char* str)
{
  int counter = 0;
  if (str == nullptr)
    throw "str == nullptr";
  while (str[counter] != '\0')
    counter++;
  return counter;
}