//
//  main.c
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#include <stdio.h>
#include "readingTime.h"
#include "ranking.h"

int main(int argc, const char * argv[]) {
    
    printf("Inicio do programa \n\n");
    queue Q = queueInit();
    
    int result;
    do{
        printf("Entre com uma linha : ");
        result = readLine();
        int rank = queueInclude(Q, result);
        printf(" Rank = %d \n\n", rank);

    }while(result != -1);
    
    freeQueue(Q);
    
    return 0;
}
