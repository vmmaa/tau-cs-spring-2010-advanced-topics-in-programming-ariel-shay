/******************************************************************************
 * Exercise 05 - Advanced Programming 2010b, TAU.
 * Authors: Ariel Stolerman (-) and Shay Davidson (-).
 * Definitions:
 * Enumerators and constant definitions used in this exercise.
 *****************************************************************************/

#pragma once

// Enumerator to distinguish between all observers (this case: phone-owner) types
enum ObserverType {
      STATIONARY_PHONE_OWNER,
	  MOBILE_PHONE_OWNER
};

// Enumerator to distinguish between subject messages
enum SubjectMessages{
	TC_UPGRADE,
	TC_PRICE_CHANGE
};