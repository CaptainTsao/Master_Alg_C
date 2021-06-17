/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  source code for graph
 *
 *        Version:  1.0
 *        Created:  2021年04月12日 00时54分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"
#include "set.h"



/* graph_init */
void graph_init(Graph *graph, 
                int (*match)(const void *key1, const void *key2), 
                void (*destroy)(void *data))
{
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;

    /* Initialize the list of adjacency-list structures */

    list_init(&graph->adjLists, NULL);
    return;
}

void graph_destroy(Graph *graph)
{
    AdjList *adjList;

    /* Remove each adjacenct-list structure and destroy its adacency list */
    while (list_size(&graph->adjLists) > 0) {
        if (list_rem_next(&graph->adjLists, NULL, (void **)&adjList) == 0) {
            set_destroy(&adjList->adjcent);

            if (graph->destroy != NULL) {
                graph->destroy(adjList->vertex);
            }

            free(adjList);
        }
    }
    list_destroy(&graph->adjLists);
    memset(graph, 0, sizeof(Graph));
    return;
}


/* graph insert vertex */
int graph_ins_vertex(Graph *graph, const void *data)
{
    ListElem *element;
    AdjList *adjList;
    int retVal;

    /* Do not allow the insertion of duplicate vertices */
    for (element = list_head(&graph->adjLists); 
         element != NULL; 
         element = list_next(element)) {
        if (graph->match(data, ((AdjList *)list_data(element))->vertex))
            return 1;
    }

    /* Insert vertex */
    if ((adjList = (AdjList *)malloc(sizeof(AdjList))) == NULL) {
        return -1;
    }
    adjList->vertex = (void *)data;
    set_init(&adjList->adjcent, graph->match, graph->destroy);

    if ((retVal = list_ins_next(&graph->adjLists, list_tail(&graph->adjLists), adjList)) != 0) {
        return retVal;
    }

    graph->vcount++;
    return 0;
}







