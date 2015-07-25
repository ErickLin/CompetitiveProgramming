/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: piggyback
*/

import java.io.*;
import java.util.*;

class piggyback {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("piggyback.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("piggyback.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int b = Integer.parseInt(line.nextToken());
        int e = Integer.parseInt(line.nextToken());
        int p = Integer.parseInt(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        HashMap<Integer, HashSet<Integer>> edges = new HashMap<Integer, HashSet<Integer>>(n);
        for (int i = 0; i < n; i++)
            edges.put(i, new HashSet<Integer>());
        for (int i = 0; i < m; i++) {
            line = new StringTokenizer(in.readLine());
            int c = Integer.parseInt(line.nextToken()) - 1;
            int d = Integer.parseInt(line.nextToken()) - 1;
            edges.get(c).add(d);
            edges.get(d).add(c);
        }
        in.close();
        int[] bDists = new int[n];
        boolean[] bVisited = new boolean[n];
        bDists[0] = 0;
        LinkedList<Integer> bNodes = new LinkedList<Integer>();
        bNodes.add(0);
        bVisited[0] = true;
        while (!bNodes.isEmpty()) {
            int node = bNodes.pop();
            for (int neighbor : edges.get(node)) {
                if (!bVisited[neighbor]) {
                    bDists[neighbor] = bDists[node] + 1;
                    bNodes.add(neighbor);
                    bVisited[neighbor] = true;
                }
            }
        }
        int[] eDists = new int[n];
        boolean[] eVisited = new boolean[n];
        eDists[1] = 0;
        LinkedList<Integer> eNodes = new LinkedList<Integer>();
        eNodes.add(1);
        eVisited[1] = true;
        while (!eNodes.isEmpty()) {
            int node = eNodes.pop();
            for (int neighbor : edges.get(node)) {
                if (!eVisited[neighbor]) {
                    eDists[neighbor] = eDists[node] + 1;
                    eNodes.add(neighbor);
                    eVisited[neighbor] = true;
                }
            }
        }
        int[] dists = new int[n];
        boolean[] visited = new boolean[n];
        dists[n - 1] = 0;
        LinkedList<Integer> nodes = new LinkedList<Integer>();
        nodes.add(n - 1);
        visited[n - 1] = true;
        while (!nodes.isEmpty()) {
            int node = nodes.pop();
            visited[node] = true;
            for (int neighbor : edges.get(node)) {
                if (!visited[neighbor]) {
                    dists[neighbor] = dists[node] + 1;
                    nodes.add(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        int minEnergy = b * bDists[n - 1] + e * eDists[n - 1];
        for (int i = 0; i < n; i++) {
            int energy = b * bDists[i] + e * eDists[i] + p * dists[i];
            //System.out.println((i + 1) + " " + bDists[i] + " " + eDists[i] + " " + dists[i] + " " + energy);
            if (energy < minEnergy)
                minEnergy = energy;
        }
        out.println(minEnergy);
        out.close();
        System.exit(0);
    }
}