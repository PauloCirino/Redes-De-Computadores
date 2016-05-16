//
//  ranking.c
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#include "ranking.h"
#include <stdlib.h>
#include <stdio.h>

// Inicializa com Head e Tail apontando para o mesmo endereÁo(vazia)
queue queueInit()
{
    queue Q = malloc(sizeof (struct queue_aux));
    Q->head = malloc(sizeof(struct cell_aux));
    Q->tail = malloc(sizeof(struct cell_aux));
    Q->head->next = Q->tail;
    Q->tail->prev = Q->head;
    Q->head->prev = NULL;
    Q->tail->next = NULL;
    Q->size = 0;
    
    return Q;
}


void printLeaderBoard(queue Q){
    cell auxCell = Q->head->next;
    
    int cont;
    for(cont = 1; auxCell != Q->tail; cont++)
    {
        printf("Pos = %d \t Time = %d\n", cont, auxCell->time);
        auxCell = auxCell->next;
    }
}

int queueInclude(queue Q, int time){
    if (time == -1)
    {
        return -1;
    }
    
    Q->size += 1;
    cell newCell = (cell) malloc(sizeof(struct cell_aux));
    newCell->time = time;
    
    int rank;
    int flag;
    cell oldCell = Q->head->next;
    
    //checkes all positions
    for(rank = 1, flag = 1; oldCell != Q->tail && flag; rank++)
    {
        if(oldCell->time <= newCell->time)
        {
            oldCell = oldCell->next;
        }
        else
        {
            oldCell->prev->next = newCell;
            newCell->prev = oldCell->prev;
            newCell->next = oldCell;
            oldCell->prev = newCell;
            flag = 0;
        }
    }
    
    //Means that oldCell points to tail
    if(oldCell == Q->tail)
    {
        Q->tail->prev->next = newCell;
        newCell->prev = Q->tail->prev;
        newCell->next = Q->tail;
        Q->tail->prev = newCell;
    }
    
    
    if(flag == 0)
    {
        return (rank - 1);
    }
    
    return rank;
}



void freeQueue(queue Q){
    cell auxCell = Q->head->next;
    
    do
    {
        free(auxCell->prev);
        auxCell = auxCell->next;
    } while(auxCell != Q->tail);
    free(Q->tail);
    
    free(Q);
}
