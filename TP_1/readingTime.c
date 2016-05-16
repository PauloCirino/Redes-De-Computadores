//
//  readingTime.c
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#include "readingTime.h"
#include <stdio.h>
#include <stdlib.h>

int getTimeInMiliSeconds(char * measurement, int lengthMeasurement, int timeInUnit ){
    
    // This means the your measurement string is 'ms'
    if(lengthMeasurement == 2){
        return timeInUnit;
    }
    
    // The switch function executes all statements declares after and including it's case
    // That means that in the case where measurement is hour 
    // finalTime will be converted from hour to minutes, then from minutes to seconds, 
    // and finaly from seconds to miliSeconds
    int finalTime = timeInUnit;
    switch (measurement[0]) {
        case 'h':
            finalTime *= 60;
            
        case 'm':
            finalTime *= 60;
        
        case's':
            finalTime *= 1000;
            
        default:
            break;
    }
    
    // return the time in miliSeconds
    return finalTime;
}

int readLine(){

    // Variables that will be used through out the function
    int timeVal = 0;
    char * timeMesure = (char *) malloc( 2 * sizeof(char)); 
    int posTimeMesure = 0;
    char auxChar;
    scanf("%c", &auxChar);
    
    int totalTime = 0;
    
    // Means Client typed -1 to exit
    if(auxChar == '-'){
        return -1;
    }
    
    // \n means end of the line
    while(auxChar != '\n'){
        
        // Space mens end of the time int that specific unit
        if(auxChar == ' '){
            totalTime += getTimeInMiliSeconds(timeMesure, posTimeMesure, timeVal);
            timeVal = 0;
            posTimeMesure = 0;
        }
        
        else{
            // Means we are reading a number
            if(auxChar >= 48 && auxChar <= 57){
                timeVal = timeVal*10 + ( ( (int) auxChar) - 48);
            }
            // Means we are reading a unit
            else{
                timeMesure[posTimeMesure] = auxChar;
                posTimeMesure ++;     
            }
        }
        scanf("%c", &auxChar);
    }
    
    totalTime += getTimeInMiliSeconds(timeMesure, posTimeMesure, timeVal);
    
    // Freeing the mesurement string previosly allocated memory
    free(timeMesure);
    
    // Returns the total time in mileseconds
    return totalTime; 
}