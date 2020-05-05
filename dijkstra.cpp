void dijkstra(int s) {
  const i64 inf = 1e16;
  fill(dist.begin(), dist.end(), inf);
  using data = array<i64, 2>;
  auto comp = [](data &x, data &y) { return x[0] > y[0]; };
  priority_queue<data, vector<data>, decltype(comp)> q(comp);
  q.push({dist[s] = 0, s});
  while (q.size()) {
    auto u = q.top(); q.pop();
    if (u[0] > dist[u[1]]) continue;
    for (auto e : adj[u[1]])
      if (dist[e[0]] > u[0] + e[1]) 
        q.push({dist[e[0]] = u[0] + e[1], e[0]});
  }
}
