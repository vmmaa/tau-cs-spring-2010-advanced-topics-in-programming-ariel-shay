/******************************************************************************
 * Exercise 03 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * File Exception Header File.
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
using namespace std;

class exception2: public exception
{
  virtual const char* what() const throw()
  {
    return "Cannot open file.";
  }
} exFile;