/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ditch
*/

import java.io.*;
import java.util.*;

class ditch {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("ditch.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ditch.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int m = Integer.parseInt(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        HashMap<Integer, HashMap<Integer, Integer>> capacities = new HashMap<Integer, HashMap<Integer, Integer>>();
        for (int i = 0; i < m; i++) {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken());
            int b = Integer.parseInt(line.nextToken());
            int c = Integer.parseInt(line.nextToken());
            if (!capacities.containsKey(a))
                capacities.put(a, new HashMap<Integer, Integer>());
            if (!capacities.containsKey(b))
                capacities.put(b, new HashMap<Integer, Integer>());
            if (capacities.get(a).containsKey(b))
                capacities.get(a).put(b, capacities.get(a).get(b) + c);
            else
                capacities.get(a).put(b, c);
        }
        in.close();
        if (m == 0 || n == 0)
            out.println("0");
        else
            out.println(dinic(capacities, 1, n));
        out.close();
        System.exit(0);
    }

    public static int dinic(HashMap<Integer, HashMap<Integer, Integer>> c, int s, int t) {
        if (s == t)
            return 0;
        //initialize flow array with flow equal to zero for each edge
        HashMap<Integer, HashMap<Integer, Integer>> f = new HashMap<Integer, HashMap<Integer, Integer>>(c.size());
        //initialize residual graph
        HashMap<Integer, HashMap<Integer, Integer>> r = new HashMap<Integer, HashMap<Integer, Integer>>(c.size());
        for (int node : c.keySet()) {
            f.put(node, new HashMap<Integer, Integer>());
            r.put(node, new HashMap<Integer, Integer>());
        }
        for (int node : c.keySet()) {
            for (int neighbor : c.get(node).keySet()) {
                f.get(node).put(neighbor, 0);
                r.get(node).put(neighbor, c.get(node).get(neighbor));
                if (!r.containsKey(neighbor))
                    r.put(neighbor, new HashMap<Integer, Integer>());
                if (!r.get(neighbor).containsKey(node))
                    r.get(neighbor).put(node, 0);
            }
        }
        int maxFlow = 0;
        HashMap<Integer, Integer> prev = new HashMap<Integer, Integer>();
        HashMap<Integer, Integer> levels;
        while ((levels = levelGraph(r, s, t)).containsKey(t)) {
            Stack<Integer> nodes = new Stack<Integer>();
            HashSet<Integer> visited = new HashSet<Integer>(c.size());
            nodes.push(s);
            while (!nodes.isEmpty()) {
                int node = nodes.peek();
                if (node == t) {
                    int flow = Integer.MAX_VALUE;
                    int bottleneck = -1;
                    for (int i = t; i != s; i = prev.get(i)) {
                        flow = Math.min(flow, r.get(prev.get(i)).get(i));
                    }
                    for (int i = t; i != s; i = prev.get(i)) {
                        if (c.get(prev.get(i)).containsKey(i)) {
                            f.get(prev.get(i)).put(i, f.get(prev.get(i)).get(i) + flow);
                            if (f.get(prev.get(i)).get(i).equals(c.get(prev.get(i)).get(i)))
                                bottleneck = prev.get(i);
                        } else {
                            f.get(i).put(prev.get(i), f.get(i).get(prev.get(i)) - flow);
                            if (f.get(i).get(prev.get(i)).equals(0))
                                bottleneck = prev.get(i);
                        }
                    }
                    while (!nodes.isEmpty() && nodes.peek() != bottleneck)
                        nodes.pop();
                    maxFlow += flow;
                    for (int a : r.keySet())
                        for (int b : r.get(a).keySet()) {
                            r.get(a).put(b, 0);
                        }
                    for (int a : r.keySet()) {
                        for (int b : r.get(a).keySet()) {
                            if (c.get(a).containsKey(b)) {
                                r.get(a).put(b, r.get(a).get(b) + c.get(a).get(b) - f.get(a).get(b));
                                r.get(b).put(a, r.get(b).get(a) + f.get(a).get(b));
                            }
                        }
                    }
                } else {
                    boolean found = false;
                    for (int neighbor : r.get(node).keySet()) {
                        if (visited.contains(neighbor) || !levels.containsKey(neighbor)
                                || levels.get(neighbor) != levels.get(node) + 1)
                            continue;
                        if (r.get(node).get(neighbor) > 0) {
                            nodes.push(neighbor);
                            prev.put(neighbor, node);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        nodes.pop();
                        visited.add(node);
                    }
                }
            }
        }
        return maxFlow;
    }

    public static HashMap<Integer, Integer> levelGraph(HashMap<Integer, HashMap<Integer, Integer>> r
            , int s, int t) {
        HashMap<Integer, Integer> levels = new HashMap<Integer, Integer>(r.size());
        LinkedList<Integer> nodes = new LinkedList<Integer>();
        levels.put(s, 0);
        nodes.add(s);
        while (!nodes.isEmpty()) {
            int node = nodes.pollFirst();
            for (int neighbor : r.get(node).keySet()) {
                if (!levels.containsKey(neighbor) && r.get(node).get(neighbor) > 0) {
                    levels.put(neighbor, levels.get(node) + 1);
                    nodes.add(neighbor);
                }
            }
        }
        return levels;
    }
}
