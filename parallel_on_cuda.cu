// Thread-based parallelism on GPU

// Each thread computes a part of the shortest path matrix.

#include <stdio.h>
#include <cuda_runtime.h>

#define INF 99999
#define V 4  // Adjust as needed

__global__ void floydWarshallKernel( int *dist, int k, int V ){
    int i = blockIdx.x;
    int j = threadIdx.x;
    
    int ij = i * V + j;
    int ik = i * V + k;
    int kj = k * V + j;

    if( dist[ik] != INF && dist[kj] != INF && dist[ik] + dist[kj] < dist[ij] ){
        dist[ij] = dist[ik] + dist[kj];
    }
}

void floydWarshall( int graph[V][V] ){
    int *d_dist;
    size_t size = V * V * sizeof( int );

    cudaMalloc( &d_dist, size );
    cudaMemcpy( d_dist, graph, size, cudaMemcpyHostToDevice );

    for( int k = 0 ; k < V ; k++ ){
        floydWarshallKernel<<<V, V>>>( d_dist, k, V );
        cudaDeviceSynchronize();
    }

    cudaMemcpy( graph, d_dist, size, cudaMemcpyDeviceToHost );
    cudaFree( d_dist );
}

void printSolution( int dist[V][V] ){
    for( int i = 0 ; i < V ; i++ ){
        for( int j = 0 ; j < V ; j++ ){
            if( dist[i][j] == INF ) printf( "INF " );
            else printf( "%d ", dist[i][j] );
        }
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
    printSolution( graph );

    return 0;
}

// Each thread computes a part of the shortest path update.
// Uses grid-stride looping to allow parallel execution.
// Synchronizes after each k iteration to ensure consistency.
