#include <list>
#include <string>

using namespace std;

#ifndef _ROBUTIL_H
#define _ROBUTIL_H

/* A utility library containing various, miscellaneous functions */

/*
  Splits input into tokens based on delimiter. That is:
  splitStr("Hello world, my name is Adam", " ") should return
  {"Hello", "world,", "my", "name", "is", "Adam"}

  If the string cannot be split using delimiter, it will return the input string
 */
list<string> splitStr(string input, string delimiter);
#endif