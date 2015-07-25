/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: cowroute
*/

import java.io.*;
import java.util.*;

class cowroute {
    static int a;
    static long[][] dists;
    static int[] minFlights;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cowroute.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowroute.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        a = Integer.parseInt(line.nextToken()) - 1;
        int b = Integer.parseInt(line.nextToken()) - 1;
        int numRoutes = Integer.parseInt(line.nextToken());
        int n = 1000;
        long[][] edges = new long[n][n];
        int[][] numFlights = new int[n][n];
        for (int i = 0; i < numRoutes; i++) {
            line = new StringTokenizer(in.readLine());
            long cost = Integer.parseInt(line.nextToken());
            int numCities = Integer.parseInt(line.nextToken());
            int[] route = new int[numCities];
            line = new StringTokenizer(in.readLine());
            for (int j = 0; j < numCities; j++) {
                route[j] = Integer.parseInt(line.nextToken()) - 1;
            }
            for (int j = 0; j < numCities; j++) {
                for (int k = j + 1; k < numCities; k++) {
                    if (edges[route[j]][route[k]] == 0 || cost <= edges[route[j]][route[k]]) {
                        if (cost == edges[route[j]][route[k]]) {
                            if (numFlights[route[j]][route[k]] == 0 || numFlights[route[j]][route[k]] > k - j)
                                numFlights[route[j]][route[k]] = k - j;
                        } else {
                            numFlights[route[j]][route[k]] = k - j;
                        }
                        edges[route[j]][route[k]] = cost;
                    }
                }
            }
        }
        in.close();
        dists = new long[n][n];
        minFlights = new int[n];
        for (int i = 0; i < n; i++)
            minFlights[i] = Integer.MAX_VALUE;
        minFlights[a] = 0;
        PriorityQueue<Integer> q = new PriorityQueue<Integer>(n, new Comparator<Integer>() {
            @Override
            public int compare(Integer n1, Integer n2) {
                return new Long(dists[a][n1]).compareTo(dists[a][n2]);
            }
        });
        boolean[] visited = new boolean[n];
        q.add(a);
        while (!q.isEmpty()) {
            int city = q.poll();
            if (visited[city])
                continue;
            visited[city] = true;
            for (int next = 0; next < n; next++) {
                if (!visited[next] && edges[city][next] != 0 && (dists[a][next] == 0
                        || dists[a][city] + edges[city][next] <= dists[a][next])) {
                    if (dists[a][city] + edges[city][next] < dists[a][next])
                        minFlights[next] = minFlights[city] + numFlights[city][next];
                    else
                        minFlights[next] = Math.min(minFlights[next]
                                , minFlights[city] + numFlights[city][next]);
                    dists[a][next] = dists[a][city] + edges[city][next];
                    q.add(next);
                }
            }
        }
        if (minFlights[b] == Integer.MAX_VALUE) {
            out.println("-1 -1");
        } else {
            out.println(dists[a][b] + " " + minFlights[b]);
        }
        out.close();
        System.exit(0);
    }
}