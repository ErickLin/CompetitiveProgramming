/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fence
*/

import java.io.*;
import java.util.*;

class fence {
    static int[] circuit;
    static int pos;
    static final int MAX = 500;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("fence.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence.out")));
        int n = Integer.parseInt(in.readLine());
        ArrayList<TreeMap<Integer, Integer>> neighbors = new ArrayList<TreeMap<Integer, Integer>>(MAX);
        for (int i = 0; i < MAX; i++) {
            neighbors.add(new TreeMap<Integer, Integer>());
        }
        int start = MAX;
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            if (neighbors.get(a).containsKey(b))
                neighbors.get(a).put(b, neighbors.get(a).get(b) + 1);
            else
                neighbors.get(a).put(b, 1);
            if (neighbors.get(b).containsKey(a))
                neighbors.get(b).put(a, neighbors.get(b).get(a) + 1);
            else
                neighbors.get(b).put(a, 1);
            if (a < start)
                start = a;
            if (b < start)
                start = b;
        }
        in.close();
        for (int i = 0; i < MAX; i++) {
            int numEdges = 0;
            for (int neighbor : neighbors.get(i).keySet())
                numEdges += neighbors.get(i).get(neighbor);
            if (numEdges % 2 == 1) {
                start = i;
                break;
            }
        }
        eulerian(start, n, neighbors);
        for (int i = 0; i < n + 1; i++)
            out.println(circuit[i] + 1);
        out.close();
        System.exit(0);
    }

    public static void eulerian(int start, int n, ArrayList<TreeMap<Integer, Integer>> neighbors) {
        circuit = new int[n + 1];
        pos = n;
        ArrayList<TreeMap<Integer, Integer>> neighborsTemp = new ArrayList<TreeMap<Integer, Integer>>(n);
        for (int i = 0; i < MAX; i++)
            neighborsTemp.add(new TreeMap<Integer, Integer>(neighbors.get(i)));
        eulerianHelper(start, neighborsTemp);
    }

    public static void eulerianHelper(int node, ArrayList<TreeMap<Integer, Integer>> neighborsTemp) {
        while (!neighborsTemp.get(node).isEmpty()) {
            int neighbor = neighborsTemp.get(node).firstKey();
            if (neighborsTemp.get(node).get(neighbor) > 1)
                neighborsTemp.get(node).put(neighbor, neighborsTemp.get(node).get(neighbor) - 1);
            else
                neighborsTemp.get(node).remove(neighbor);
            if (neighborsTemp.get(neighbor).get(node) > 1)
                neighborsTemp.get(neighbor).put(node, neighborsTemp.get(neighbor).get(node) - 1);
            else
                neighborsTemp.get(neighbor).remove(node);
            eulerianHelper(neighbor, neighborsTemp);
        }
        circuit[pos] = node;
        pos--;
    }
}
