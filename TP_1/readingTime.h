//
//  readingTime.h
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#ifndef readingTime_h
#define readingTime_h

// function that takes a timeStruct variable and returns its time in miliSeconds
// char * measurement is a pointer to the mesurement string - ex : 'ms' ir 'h'
// int lengthMeasurement is the length of the mesurement string - It can either be 1 or 2
// int TimeInUnit
int getTimeInMiliSeconds(char * measurement, int lengthMeasurement, int timeInUnit );

// reads a line from stdin with function scanf(...) and returns time in miliseconds by 
// by using the function int getTimeInMiliSeconds(...)
int readLine();

#endif /* readingTime_h */
