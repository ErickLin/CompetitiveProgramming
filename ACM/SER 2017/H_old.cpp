#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

// union and intersection of unions of disjoint intervals
vii interval_union(vii& a, vii& b) {
  vii ret;
  /*
  a.pb(mp(INT_MAX, INT_MAX));
  b.pb(mp(INT_MAX, INT_MAX));
  int i = 0, j = 0;
  bool started = false, cur_on_a = false;
  int l = -1;
  while (i < a.size() - 1 || j < b.size() - 1) {
    if (!started) {
      if (a[i].first < b[j].first) {
        l = a[i].first;
        cur_on_a = true;
      } else {
        l = b[j].first;
        cur_on_a = false;
      }
      started = true;
    } else {
      if (cur_on_a) {
        if (a[i].second < b[j].first) {
          ret.pb(mp(l, a[i].second));
          started = false;
          i++;
        } else if (a[i].second >= b[j].second) {
          j++;
        } else {
          cur_on_a = false;
        }
      } else {
        if (b[j].second < a[i].first) {
          ret.pb(mp(l, b[j].second));
          started = false;
          j++;
        } else if (b[j].second >= a[i].second) {
          i++;
        } else {
          cur_on_a = true;
        }
      }
    }
    //cout << i << ' ' << j << ' ' << (started ? "started" : "notstar") << ' ' << (cur_on_a ? 'a' : 'b') << '\n';
  }
  a.pop_back();
  b.pop_back();
  */
  vector<pair<int, bool>> induced_pts;
  for (ii range : a) {
    induced_pts.pb(mp(range.first, 0));
    induced_pts.pb(mp(range.second, 1));
  }
  for (ii range : b) {
    induced_pts.pb(mp(range.first, 0));
    induced_pts.pb(mp(range.second, 1));
  }
  sort(induced_pts.begin(), induced_pts.end());

  int num_intervals_inside = 0;
  int l;
  for (int i = 0; i < induced_pts.size(); i++) {
    if (!induced_pts[i].second) {
      if (!num_intervals_inside) {
        l = induced_pts[i].first;
      }
      num_intervals_inside++;
    } else {
      num_intervals_inside--;
      if (!num_intervals_inside) {
        ret.pb(mp(l, induced_pts[i].first));
      }
    }
  }

  return ret;
}

vii interval_intersection(vii& a, vii& b) {
  vii ret;
  a.pb(mp(INT_MAX, INT_MAX));
  b.pb(mp(INT_MAX, INT_MAX));
  int i = 0, j = 0;
  bool started = false, cur_on_a = false;
  int l = -1;
  while (i < a.size() - 1 || j < b.size() - 1) {
    if (a[i].second < b[j].first) {
      i++;
    } else if (b[j].second < a[i].first) {
      j++;
    } else {
      ret.pb(mp(max(a[i].first, b[j].first), min(a[i].second, b[j].second)));
      if (a[i].second < b[j].second) {
        i++;
      } else {
        j++;
      }
    }
  }
  a.pop_back();
  b.pop_back();
  return ret;
}

// cycle_entry is the first node on which we recursed, while cycle_last is the last.
void collapse_cycle(int cycle_last, int cycle_entry, umii& node_to_cycle_id,
                    unordered_map<int, vi>& cycles,
                    umii& prev, umii& vis, int cycle_id, int k,
                    unordered_map<int, unordered_map<int, vii>>& doors,
                    unordered_map<int, usi>& rev_edges) {
  list<int> cycle;
  for (int v_out = cycle_last; ; v_out = prev[v_out]) {
    node_to_cycle_id[v_out] = cycle_id;
    cycle.push_front(v_out);
    vis[v_out] = 2;
    if (v_out == cycle_entry) break;
  }
  for (int node : cycle) {
    cycles[cycle_id].pb(node);
  }

  for (int v_out = cycle_last; ; v_out = prev[v_out]) {
    // arc is the chain consisting of vertices from v_in to v_out
    vii arc_ranges = {mp(1, k)};
    for (int v_in = v_out; ; v_in = prev[v_in]) {
      // v_in and v_out are collapsed into the same supernode.
      // First, add the edges out of v_out.
      for (auto& kv : doors[v_out]) {
        int child = kv.first;
        if (child == cycle_id || node_to_cycle_id.count(child)) continue;
        vii new_ranges = interval_intersection(arc_ranges, kv.second);
        doors[cycle_id][child] = interval_union(doors[cycle_id][child],
                                                new_ranges);
        rev_edges[child].insert(cycle_id);
      }
      // Then add the edges into v_in.
      for (int par : rev_edges[v_in]) {
        if (par == cycle_id || node_to_cycle_id.count(par)) continue;
        vii new_ranges = interval_intersection(arc_ranges, doors[par][v_in]);
        doors[par][cycle_id] = interval_union(doors[par][cycle_id],
                                              new_ranges);
        rev_edges[cycle_id].insert(par);
      }
      arc_ranges = interval_intersection(arc_ranges, doors[prev[v_in]][v_in]);
      if (v_in == cycle_entry) break;
    }

    if (v_out == cycle_entry) break;
  }

  prev[cycle_id] = prev[cycle_entry];
}

void collapse_cycles_dfs(int cur, umii& prev, umii& vis, umii& node_to_cycle_id,
                         unordered_map<int, vi>& cycles, int& next_cycle_id, int k,
                         unordered_map<int, unordered_map<int, vii>>& doors,
                         unordered_map<int, usi>& rev_edges) {
  vis[cur] = 1;
  for (const auto& kv : doors[cur]) {
    int next = kv.first;
    if (node_to_cycle_id.count(next)) continue;
    if (vis.count(next) && vis[next] == 1) {
      int cycle_id = next_cycle_id;
      collapse_cycle(cur, next, node_to_cycle_id, cycles, prev, vis, cycle_id, k, doors, rev_edges);
      collapse_cycles_dfs(cycle_id, prev, vis, node_to_cycle_id, cycles, ++next_cycle_id, k, doors, rev_edges);
      return;
    } else {
      prev[next] = cur;
      collapse_cycles_dfs(next, prev, vis, node_to_cycle_id, cycles, next_cycle_id, k, doors, rev_edges);
    }
    // This node was collapsed.
    if (vis[cur] == 2) return;
  }
  vis[cur] = 2;
}

void top_sort(int cur, list<int>& rooms_in_order, usi& vis, umii& node_to_cycle_id,
              unordered_map<int, vi>& cycles,
              unordered_map<int, unordered_map<int, vii>>& doors) {
  vis.insert(cur);
  for (const auto& kv : doors[cur]) {
    int next = kv.first;
    if (!vis.count(next) && !node_to_cycle_id.count(next)) {
      top_sort(next, rooms_in_order, vis, node_to_cycle_id, cycles, doors);
    }
  }
  rooms_in_order.push_front(cur);
}

void update_valid_ranges(int node, int next, unordered_map<int, vii>& valid_ranges,
                         unordered_map<int, unordered_map<int, vii>>& doors) {
  vii ranges_from_here = interval_intersection(doors[node][next], valid_ranges[node]);
  valid_ranges[next] = interval_union(valid_ranges[next], ranges_from_here);
}

void propagate_valid_ranges_within_cycle(
    int cycle_id, unordered_map<int, vii>& valid_ranges, unordered_map<int, vi>& cycles,
    unordered_map<int, unordered_map<int, vii>>& doors) {
  forf(j, 2) {
    bool inc = true;
    for (int i = 0; i >= 0; inc ? i++ : i--) {
      int node = cycles[cycle_id][i];
      if (cycles.count(node)) {
        propagate_valid_ranges_within_cycle(node, valid_ranges, cycles, doors);
      } else for (auto& kv : doors[node]) {
        int next = kv.first;
        if (cycles.count(next)) continue;
        //cout << node << ' ' << next << '\n';
        update_valid_ranges(node, next, valid_ranges, doors);
      }
      if (i == cycles[cycle_id].size() - 1) {
        inc = false;
      }
    }
  }
}

int main() {
  /*
  vii a = {mp(1, 5), mp(7, 10)}, b = {mp(5, 7), mp(10, 11)};
  vii c = interval_union(a, b);
  for (ii range : c) {
    cout << range.first << ' ' << range.second << '\n';
  }
  c = interval_intersection(a, b);
  for (ii range : c) {
    cout << range.first << ' ' << range.second << '\n';
  }
  */
  int n, m, k, s, d;
  cin >> n >> m >> k >> s >> d;
  unordered_map<int, unordered_map<int, vii>> doors;
  unordered_map<int, usi> rev_edges;
  forf(i, m) {
    int a, b, l, r;
    cin >> a >> b >> l >> r;
    doors[a][b].pb(mp(l, r));
    rev_edges[b].insert(a);
  }

  // Maps each vertex to a cycle containing it, if any. If it is contained in
  // multiple cycles, then every cycle is attainable by applying the map some
  // number of times.
  umii node_to_cycle_id;
  unordered_map<int, vi> cycles;
  {
    umii prev, vis;
    int starting_cycle_id = n + 1;
    collapse_cycles_dfs(s, prev, vis, node_to_cycle_id, cycles, starting_cycle_id, k, doors, rev_edges);
  }

  list<int> dag_nodes_in_order;
  {
    usi vis;
    top_sort(s, dag_nodes_in_order, vis, node_to_cycle_id, cycles, doors);
  }

  unordered_map<int, vii> valid_ranges;
  valid_ranges[s].pb(mp(1, k));
  for (int node : dag_nodes_in_order) {
    for (auto& kv : doors[node]) {
      int next = kv.first;
      update_valid_ranges(node, next, valid_ranges, doors);
    }
    if (cycles.count(node)) {
      propagate_valid_ranges_within_cycle(node, valid_ranges, cycles, doors);
    }
  }
  /*
  for (const auto& kv : cycles) {
    cout << "Cycle " << kv.first << ": ";
    for (const auto& v : kv.second) {
      cout << v << ' ';
    }
    cout << '\n';
  }
  forf3(node, n + cycles.size()) {
    cout << node << ": ";
    for (ii range : valid_ranges[node]) {
      cout << "[" << range.first << ", " << range.second << "], ";
    }
    cout << '\n';
  }
  */

  int ans = 0;
  for (ii range : valid_ranges[d]) {
    ans += range.second - range.first + 1;
  }
  cout << ans << '\n';
}
