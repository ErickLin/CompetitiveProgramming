/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: butter
*/

import java.io.*;
import java.util.*;

class butter2 {
    static final int MAX = 99999999;
    static int n, v, e;
    static int[] numCows;
    static boolean[][] isNeighbor;
    static int[][] edgeLens, dists;
    
    public static void main(String[] args) throws IOException {
        long time = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("butter.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("butter.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        v = Integer.parseInt(line.nextToken());
        e = Integer.parseInt(line.nextToken());
        numCows = new int[v];
        for (int i = 0; i < v; i++)
            numCows[i] = 0;
        for (int i = 0; i < n; i++) {
            line = new StringTokenizer(in.readLine());
            numCows[Integer.parseInt(line.nextToken()) - 1]++;
        }
        isNeighbor = new boolean[v][v];
        edgeLens = new int[v][v];
        dists = new int[v][v];
        for (int i = 0; i < v; i++) {
            edgeLens[i][i] = 0;
            for (int j = 0; j < v; j++)
                if (i != j) {
                    dists[i][j] = MAX;
                    dists[j][i] = MAX;
                }
            dists[i][i] = 0;
        }
        for (int i = 0; i < e; i++) {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            int cost = Integer.parseInt(line.nextToken());
            isNeighbor[a][b] = true;
            isNeighbor[b][a] = true;
            edgeLens[a][b] = cost;
            edgeLens[b][a] = cost;
        }
        in.close();
        int min = MAX;
        setDists();
        //System.out.println(System.currentTimeMillis() - time);
        for (int cubeLoc = 0; cubeLoc < v; cubeLoc++) {
            int totalDist = distSum(cubeLoc, min);
            if (totalDist < min)
                min = totalDist;
        }
        out.println(min);
        out.close();
        System.exit(0);
    }
    
    public static int distSum(int dest, int limit) {
        int sum = 0;
        for (int i = 0; i < v; i++)
            if (numCows[i] > 0) {
                sum += (dists[i][dest] * numCows[i]);
                if (sum > limit)
                    return sum;
            }
        return sum;
    }
    
    //Floyd-Warshall
    /*
    public static void setDists() {
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++) {
                if (i == j || isNeighbor[i][j])
                    dists[i][j] = edgeLens[i][j];
                else
                    dists[i][j] = MAX;
            }
        for (int k = 0; k < v; k++)
            for (int i = 0; i < v; i++)
                for (int j = 0; j < v; j++)
                    if (dists[i][j] > dists[i][k] + dists[k][j])
                        dists[i][j] = dists[i][k] + dists[k][j];
    }
    */
    
    //Dijkstra
    public static void setDists() {
        for (int i = 0; i < v; i++)
            if (numCows[i] > 0) {
                boolean[] visited = new boolean[v];
                for (int j = 0; j < v; j++) 
                    visited[j] = false;
                visited[i] = true;
                int current = i;
                while (current != -1) {
                    int nearest = -1;
                    int nearestDist = MAX;
                    for (int j = 0; j < v; j++) {
                        if (!visited[j]) {
                            if (isNeighbor[current][j] && dists[i][j] > dists[i][current] + edgeLens[current][j]) {
                                dists[i][j] = dists[i][current] + edgeLens[current][j];
                                dists[j][i] = dists[i][current] + edgeLens[current][j];
                            }
                            if (dists[i][j] < nearestDist) {
                                nearestDist = dists[i][j];
                                nearest = j;
                            }
                        }
                    }
                    visited[current] = true;
                    current = nearest;
                }
            }
        }
    }