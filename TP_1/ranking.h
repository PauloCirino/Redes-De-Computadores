//
//  ranking.h
//  Tp_01
//
//  Created by Paulo Cirino on 06/05/16.
//  Copyright © 2016 Paulo Cirino. All rights reserved.
//

#ifndef ranking_h
#define ranking_h

//Queue cell struct
typedef struct cell_aux * cell;
struct cell_aux
{
    int time;//Unico dado È o vertice
    cell next;
    cell prev;
};

//Queue struct
typedef struct queue_aux * queue;
struct queue_aux
{
    cell head;
    cell tail;
    int size;
};

//Initialize the queue
queue queueInit();

//Includes an athlete and returns it`s rank
int queueInclude(queue Q, int time);

//Frees queue memory
void freeQueue(queue Q);

void printLeaderBoard(queue Q);

#endif /* ranking_h */
