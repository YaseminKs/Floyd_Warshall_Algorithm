# Uses a list of lists with min() for updates.

INF = float( 'inf' )

def floyd_warshall( graph ):
    V = len( graph )
    dist = [ row[:] for row in graph ]  

    for k in range( V ):
        for i in range( V ):
            for j in range( V ):
                dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] )

    print_solution( dist )

def print_solution( dist ):
    for row in dist:
        print( " ".join( "INF" if x == INF else str( x ) for x in row ) )

graph = [
    [ 0, 3, INF, 5 ],
    [ 2, 0, INF, 4 ],
    [ INF, 1, 0, INF ],
    [ INF, INF, 2, 0 ]
]

floyd_warshall( graph )
