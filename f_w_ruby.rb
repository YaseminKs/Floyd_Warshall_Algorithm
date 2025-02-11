# Uses an array of arrays with .map for elegance.

INF = Float::INFINITY

def floyd_warshall( graph )
  v = graph.length
  dist = graph.map( &:dup )

  v.times do |k|
    v.times do |i|
      v.times do |j|
        dist[i][j] = [dist[i][j], dist[i][k] + dist[k][j]].min
      end
    end
  end

  print_solution( dist )
end

def print_solution( dist )
  dist.each do |row|
    puts row.map { |x| x == INF ? "INF" : x }.join(" ")
  end
end

graph = [
  [ 0, 3, INF, 5 ],
  [ 2, 0, INF, 4 ],
  [ INF, 1, 0, INF ],
  [ INF, INF, 2, 0 ]
]

floyd_warshall( graph )
