// Uses a vector of vectors for flexibility.

#include <iostream>
#include <vector>

using namespace std;

const int INF = 99999;
const int V = 4;

void floydWarshall( vector<vector<int>>& graph ){
    vector<vector<int>> dist = graph;

    for( int k = 0 ; k < V ; k++ ){
        for( int i = 0 ; i < V ; i++ ){
            for( int j = 0 ; j < V ; j++ ){
                if( dist[i][k] + dist[k][j] < dist[i][j] )
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    for( const auto& row : dist ){
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
    return 0;
}
