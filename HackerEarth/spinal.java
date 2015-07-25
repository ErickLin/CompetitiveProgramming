package hackerearth;

import java.io.*;
import java.util.*;

class spinal {
    public static ArrayList<ArrayList<Integer>> neighbors;
    public static int[] levels, maxNeighbors;
    public static int rootNode, maxLevel;
    public static HashSet<Integer> spine;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            int n = Integer.parseInt(in.readLine());
            neighbors = new ArrayList<ArrayList<Integer>>();
            levels = new int[n];
            maxNeighbors = new int[n];
            spine = new HashSet<Integer>();
            rootNode = -1;
            maxLevel = 0;
            for (int j = 0; j < n; j++) {
                neighbors.add(new ArrayList<Integer>());
            }
            for (int j = 0; j < n - 1; j++) {
                StringTokenizer line = new StringTokenizer(in.readLine());
                int a = Integer.parseInt(line.nextToken()) - 1;
                int b = Integer.parseInt(line.nextToken()) - 1;
                neighbors.get(a).add(b);
                neighbors.get(b).add(a);
            }
            level(0, -1);
            addToSpine(rootNode);
            System.out.println(spine);
            boolean spinal = true;
            for (int j = 0; j < n; j++) {
                if (!spine.contains(j)) {
                    if (neighbors.get(j).size() > 1) {
                        System.out.println("NO");
                        spinal = false;
                        break;
                    }
                }
            }
            if (spinal)
                System.out.println("YES");
        }
        in.close();
        System.exit(0);
    }
    
    public static void level(int node, int prev) {
        if (levels[node] > 0)
            return;
        else if (neighbors.get(node).isEmpty()
                || (neighbors.get(node).size() == 1 && neighbors.get(node).get(0) == prev)) {
            levels[node] = 1;
            maxNeighbors[node] = -1;
            if (maxLevel < 1)
                maxLevel = 1;
        } else {
            int maxNeighborLevel = 0;
            for (int neighbor : neighbors.get(node))
                if (neighbor != prev) {
                    level(neighbor, node);
                    if (levels[neighbor] > maxNeighborLevel) {
                        maxNeighborLevel = levels[neighbor];
                        maxNeighbors[node] = neighbor;
                    }
                }
            levels[node] = 1 + maxNeighborLevel;
            if (levels[node] > maxLevel) {
                maxLevel = levels[node];
                rootNode = node;
            }
        }
    }
    
    public static void addToSpine(int node) {
        spine.add(node);
        if (maxNeighbors[node] != -1)
            addToSpine(maxNeighbors[node]);
    }
}
