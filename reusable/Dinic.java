import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Stack;

public class Dinic {

    /**
     * Maximum flow algorithm (O(V^2 * E))
     * @param c an adjacency list of dictionaries that map neighboring nodes to capacities
     * @param s the source
     * @param t the sink
     * @return the maximum flow f
     */
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

    public static void main(String[] args) {
        HashMap<Integer, HashMap<Integer, Integer>> g = new HashMap<Integer, HashMap<Integer, Integer>>();
        for (int i = 0; i < 10; i++)
            g.put(i, new HashMap<Integer, Integer>());
        /*
        g.get(0).put(1, 1000);
        g.get(0).put(2, 1000);
        g.get(1).put(2, 1);
        g.get(1).put(3, 1000);
        g.get(2).put(3, 1000);
        */
        g.get(0).put(1, 30);
        g.get(0).put(2, 10);
        g.get(1).put(3, 15);
        g.get(1).put(4, 5);
        g.get(2).put(4, 5);
        g.get(2).put(5, 5);
        g.get(3).put(6, 10);
        g.get(3).put(7, 10);
        g.get(4).put(7, 5);
        g.get(4).put(8, 5);
        g.get(5).put(8, 6);
        g.get(6).put(9, 15);
        g.get(7).put(9, 7);
        g.get(8).put(9, 10);
        System.out.println(dinic(g, 0, 9));
    }
}