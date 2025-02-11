// Uses a 2D array and nested loops for updates.

#include <stdio.h>

#define INF 99999
#define V 4

void floydWarshall( int graph[V][V] ){
    int dist[V][V];

    for( int i = 0 ; i < V ; i++ )
        for( int j = 0 ; j < V ; j++ )
            dist[i][j] = graph[i][j];

    for( int k = 0 ; k < V ; k++ )
        for( int i = 0 ; i < V ; i++ )
            for( int j = 0 ; j < V ; j++ )
                if( dist[i][k] + dist[k][j] < dist[i][j] )
                    dist[i][j] = dist[i][k] + dist[k][j];

    for( int i = 0 ; i < V ; i++ ){
        for( int j = 0 ; j < V ; j++ )
            printf( "%4d ", ( dist[i][j] == INF ) ? INF : dist[i][j] );
        printf( "\n" );
    }
}

int main(){
    int graph[V][V] = {
        { 0, 3, INF, 5 },
        { 2, 0, INF, 4 },
        { INF, 1, 0, INF },
        { INF, INF, 2, 0 }
    };

    floydWarshall( graph );
    return 0;
}
