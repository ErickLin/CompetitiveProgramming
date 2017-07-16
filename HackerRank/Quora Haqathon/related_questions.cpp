#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void add_vertices(int vertex, vector<unordered_set<int>>& edges,
                  vector<bool>& visited, list<int>& vertices_bottom_up) {
    for (int neighbor : edges[vertex]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            vertices_bottom_up.push_front(neighbor);
            add_vertices(neighbor, edges, visited, vertices_bottom_up);
        }
    }
}

void comp_init_edge_times(int vertex, vector<unordered_set<int>>& edges,
                        vector<unordered_map<int, double>>& edge_times,
                        vector<bool>& visited, vector<int>& t) {
    visited[vertex] = true;
    for (int neighbor : edges[vertex]) {
        if (visited[neighbor]) {
            if (!edge_times[neighbor].empty()) {
                for (auto&& kv : edge_times[neighbor]) {
                    double edge_time = kv.second;
                    edge_times[vertex][neighbor] += edge_time;
                }
                edge_times[vertex][neighbor] /= edge_times[neighbor].size();
            }
            edge_times[vertex][neighbor] += t[neighbor];
        }
    }
}

void comp_rem_edge_times(int vertex, vector<unordered_set<int>>& edges,
                        vector<unordered_map<int, double>>& edge_times,
                        vector<bool>& visited, vector<int>& t) {
    double vertex_edge_times_sum = 0;
    for (auto&& kv : edge_times[vertex]) {
        vertex_edge_times_sum += kv.second;
    }
    for (int neighbor : edges[vertex]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            if (edge_times[vertex].size() > 1) {
                edge_times[neighbor][vertex] = (vertex_edge_times_sum -
                        edge_times[vertex][neighbor]) /
                    (edge_times[vertex].size() - 1);
            }
            edge_times[neighbor][vertex] += t[vertex];
            comp_rem_edge_times(neighbor, edges, edge_times, visited, t);
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    for (int vertex = 0; vertex < n; vertex++) {
        cin >> t[vertex];
    }
    vector<unordered_set<int>> edges(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].insert(b);
        edges[b].insert(a);
    }

    // expected remaining time if we travel down an edge of a specific vertex
    vector<unordered_map<int, double>> edge_times(n);

    list<int> vertices_bottom_up;
    vertices_bottom_up.push_front(0);
    vector<bool> visited(n);
    visited[0] = true;
    add_vertices(0, edges, visited, vertices_bottom_up);

    fill(visited.begin(), visited.end(), false);
    for (int vertex : vertices_bottom_up) {
        comp_init_edge_times(vertex, edges, edge_times, visited, t);
    }

    fill(visited.begin(), visited.end(), false);
    visited[0] = true;
    comp_rem_edge_times(0, edges, edge_times, visited, t);

    /*
    for (int i = 0; i < n; i++) {
        for (auto& kv : edge_times[i]) {
            cout << i << ' ' << kv.first << ": " << kv.second << '\n';
        }
    }
    */

    double min_expected_time = 100000000000;
    int best_vertex = -1;
    for (int vertex = 0; vertex < n; vertex++) {
        double expected_time = 0;
        if (!edges[vertex].empty()) {
            for (int neighbor : edges[vertex]) {
                expected_time += edge_times[vertex][neighbor];
            }
            expected_time /= edges[vertex].size();
        }
        expected_time += t[vertex];

        if (expected_time < min_expected_time) {
            min_expected_time = expected_time;
            best_vertex = vertex;
        }
    }

    cout << best_vertex + 1 << '\n';
}
