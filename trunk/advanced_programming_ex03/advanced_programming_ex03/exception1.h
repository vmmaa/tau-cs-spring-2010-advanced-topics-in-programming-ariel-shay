/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Parser Exception Header File.
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
using namespace std;

class exception1: public exception
{
  virtual const char* what() const throw()
  {
    return "Parser not initalized with file yet.";
  }
} exParse;