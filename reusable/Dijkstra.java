/**
 * Incorrect - don't use this
 * @author Erick
 */
public class Dijkstra {
    static final int MAX = 99999999;

    public static int[][] dijkstra(int n, boolean[][] isNeighbor, int[][] weights) {
        //1st dimension is starting point, 2nd is shortest distance to point of index
        int[][] dists = new int[n][n];
        int[][] prev = new int[n][n];
        //i is each new starting point
        for (int i = 0; i < n; i++) {
            boolean[] visited = new boolean[n];
            dists[i][i] = 0;
            visited[i] = true;
            for (int j = 1; j < n; j++) {
                dists[i][j] = MAX;
                visited[j] = false;
                prev[i][i] = -1;
            }
            int current = i;
            while (current != -1) {
                int nearest = -1;
                int nearestDist = MAX;
                for (int neighbor = 0; neighbor < n; neighbor++) {
                    if (isNeighbor[current][neighbor] && !visited[neighbor]) {
                        if (dists[i][neighbor] > dists[i][current] + weights[current][neighbor]) {
                            dists[i][neighbor] = dists[i][current] + weights[current][neighbor];
                            dists[neighbor][i] = dists[i][current] + weights[current][neighbor];
                            prev[i][neighbor] = current;
                        }
                        if (dists[i][neighbor] < nearestDist) {
                            nearestDist = dists[i][neighbor];
                            nearest = neighbor;
                        }
                    }
                }
                visited[current] = true;
                current = nearest;
            }
        }
        return dists;
    }
}