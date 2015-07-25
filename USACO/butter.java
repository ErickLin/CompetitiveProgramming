/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: butter
*/

import java.io.*;
import java.util.*;

class butter {
    static int[][] dists;

    public static void main(String[] args) throws IOException {
        double start = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("butter.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("butter.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(line.nextToken());
        int numNodes = Integer.parseInt(line.nextToken());
        int numEdges = Integer.parseInt(line.nextToken());
        HashSet<Integer> cowFields = new HashSet<Integer>(numNodes);
        int[] numCowsInField = new int[numNodes];
        for (int i = 0; i < numCows; i++) {
            int cowField = Integer.parseInt(in.readLine()) - 1;
            cowFields.add(cowField);
            numCowsInField[cowField]++;
        }
        int[][] edges = new int[numNodes][numNodes];
        HashSet[] neighbors = new HashSet[numNodes];
        for (int i = 0; i < numNodes; i++) {
            neighbors[i] = new HashSet<Integer>(numNodes);
        }
        for (int i = 0; i < numEdges; i++) {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            int len = Integer.parseInt(line.nextToken());
            edges[a][b] = len;
            edges[b][a] = len;
            neighbors[a].add(b);
            neighbors[b].add(a);
        }
        in.close();
        int[] totalDists = new int[numNodes];
        dists = new int[numNodes][numNodes];
        for (int i = 0; i < numNodes; i++)
            for (int j = 0; j < numNodes; j++) {
                if (i == j)
                    dists[i][j] = 0;
                else
                    dists[i][j] = Integer.MAX_VALUE;
            }
        int[] visited = new int[numNodes];
        Arrays.fill(visited, -1);
        int count = 0;
        for (final int cowField : cowFields) {
            PriorityQueue<Integer> nodes = new PriorityQueue<Integer>(numNodes, new Comparator<Integer>() {
                @Override
                public int compare(Integer a, Integer b) {
                    return new Integer(dists[cowField][a]).compareTo(dists[cowField][b]);
                }
            });
            nodes.add(cowField);
            for (int i = 0; i < numNodes; i++) {
                count++;
                int node = nodes.poll();
                if (visited[node] == cowField) {
                    i--;
                    continue;
                }
                visited[node] = cowField;
                totalDists[node] += dists[cowField][node] * numCowsInField[cowField];
                for (int neighbor : (HashSet<Integer>) (neighbors[node])) {
                    if (visited[neighbor] != cowField && dists[cowField][neighbor] > dists[cowField][node] + edges[node][neighbor]) {
                        dists[cowField][neighbor] = dists[cowField][node] + edges[node][neighbor];
                        nodes.add(neighbor);
                    }
                }
            }
            System.out.println(cowField + " " + (System.currentTimeMillis() - start));
        }
        System.out.println(count);
        int minTotalDist = Integer.MAX_VALUE;
        for (int i = 0; i < numNodes; i++) {
            if (totalDists[i] < minTotalDist)
                minTotalDist = totalDists[i];
        }
        out.println(minTotalDist);
        out.close();
        System.exit(0);
    }
}
