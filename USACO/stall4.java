/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: stall4
*/

import java.io.*;
import java.util.*;

class stall4 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("stall4.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("stall4.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        HashMap<Integer, HashMap<Integer, Integer>> adjacencies = new HashMap<Integer, HashMap<Integer, Integer>>();
        //s = 0
        //cows = 1 : n
        //stalls = n + 1 : n + m
        //t = n + m + 1
        for (int i = 0; i <= n + m + 1; i++) {
            adjacencies.put(i, new HashMap<Integer, Integer>());
        }
        for (int i = 1; i <= n; i++) {
            adjacencies.get(0).put(i, 1);
            line = new StringTokenizer(in.readLine());
            int k = Integer.parseInt(line.nextToken());
            for (int j = 0; j < k; j++) {
                int a = Integer.parseInt(line.nextToken());
                adjacencies.get(i).put(n + a, 1);
            }
        }
        in.close();
        for (int i = n + 1; i <= n + m; i++) {
            adjacencies.get(i).put(n + m + 1, 1);
        }
        if (m == 0 || n == 0)
            out.println("0");
        else
            out.println(fordFulkerson(adjacencies, 0, n + m + 1));
        out.close();
        System.exit(0);
    }

    public static int fordFulkerson(HashMap<Integer, HashMap<Integer, Integer>> c, int s, int t) {
        if (s == t)
            return 0;
        //initialize flow array with flow equal to zero for each edge
        HashMap<Integer, HashMap<Integer, Integer>> f = new HashMap<Integer, HashMap<Integer, Integer>>(c.size());
        for (int node : c.keySet()) {
            f.put(node, new HashMap<Integer, Integer>());
        }
        for (int node : c.keySet()) {
            for (int neighbor : c.get(node).keySet()) {
                if (!c.get(neighbor).containsKey(node)) {
                    c.get(neighbor).put(node, -c.get(node).get(neighbor));
                }
                f.get(node).put(neighbor, 0);
                f.get(neighbor).put(node, 0);
            }
        }
        //repeat process of finding path and adding a flow to each edge along path
        boolean hasPath = true;
        loop : do {
            HashSet<Integer> visited = new HashSet<Integer>();
            HashMap<Integer, Integer> prevs = new HashMap<Integer, Integer>();
            Stack<Integer> nodes = new Stack<Integer>();
            nodes.add(s);
            while (!nodes.isEmpty()) {
                int node = nodes.pop();
                //if a path is found
                if (node == t) {
                    Stack<Integer> path = new Stack<Integer>();
                    int currentNode = t;
                    int flow = Integer.MAX_VALUE;
                    //determine the path and the maximum flow that can be sent along path
                    while (currentNode != s) {
                        path.add(currentNode);
                        int prev = prevs.get(currentNode);
                        if (c.get(prev).get(currentNode) > 0) {
                            if (c.get(prev).get(currentNode) - f.get(prev).get(currentNode) < flow)
                                flow = c.get(prev).get(currentNode) - f.get(prev).get(currentNode);
                        } else {
                            if (-1 * f.get(prev).get(currentNode) < flow)
                                flow = -1 * f.get(prev).get(currentNode);
                        }
                        currentNode = prev;
                    }
                    currentNode = s;
                    //increment each edge by flow
                    while (!path.isEmpty()) {
                        int prev = currentNode;
                        currentNode = path.pop();
                        f.get(prev).put(currentNode, f.get(prev).get(currentNode) + flow);
                        f.get(currentNode).put(prev, f.get(currentNode).get(prev) - flow);
                        //System.out.println(prev + " " + currentNode + " " + flow + " " + f.get(prev).get(currentNode));
                    }
                    continue loop;
                }
                visited.add(node);
                for (int neighbor : c.get(node).keySet()) {
                    if (!visited.contains(neighbor)) {
                        //test cases depending on whether increasing or decreasing flow
                        if ((c.get(node).get(neighbor) > 0 && f.get(node).get(neighbor) < c.get(node).get(neighbor))
                                || f.get(node).get(neighbor) < 0) {
                            nodes.add(neighbor);
                            prevs.put(neighbor, node);
                        }
                    }
                }
            }
            hasPath = false;
        } while (hasPath);
        int maxFlow = 0;
        for (int flowPart : f.get(s).values()) {
            maxFlow += flowPart;
        }
        return maxFlow;
    }
}
