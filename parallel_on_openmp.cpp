// OpenMP for parallelization across multiple CPU threads.

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

#define INF 99999
#define V 4  // Adjust as needed

void floydWarshall( vector<vector<int>> &dist ){
    for( int k = 0 ; k < V ; k++ ){
        #pragma omp parallel for collapse( 2 )  // to parallelize the two nested loops
        for( int i = 0 ; i < V ; i++ ){
            for( int j = 0 ; j < V ; j++ ){
                if( dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j] ){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void printSolution( const vector<vector<int>> &dist ){
    for( const auto &row : dist ){
        for( int val : row ){
            cout << ( val == INF ? "INF" : to_string( val ) ) << " ";
        }
        cout << endl;
    }
}

int main(){
    vector<vector<int>> graph = {
        { 0, 3, INF, 5 },
        { 2, 0, INF, 4 },
        { INF, 1, 0, INF },
        { INF, INF, 2, 0 }
    };

    floydWarshall( graph );
    printSolution( graph );

    return 0;
}

// Each thread updates part of the distance matrix simultaneously
//Thread safety is ensured since each cell update is independent.
