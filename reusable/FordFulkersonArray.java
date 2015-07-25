import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Stack;

public class FordFulkersonArray {
    /**
     * Maximum flow algorithm (O(E * f))
     * @param c an adjacency list of dictionaries that map neighboring nodes to capacities
     * @param s the source
     * @param t the sink
     * @return the maximum flow f
     */
    public static int fordFulkerson(ArrayList<HashMap<Integer, Integer>> c, int s, int t) {
        if (s == t)
            return 0;
        //initialize flow array with flow equal to zero for each edge
        ArrayList<HashMap<Integer, Integer>> f = new ArrayList<HashMap<Integer, Integer>>(c.size());
        for (int i = 0; i < c.size(); i++) {
            f.add(new HashMap<Integer, Integer>());
        }
        for (int i = 0; i < c.size(); i++) {
            for (int neighbor : c.get(i).keySet()) {
                if (!c.get(neighbor).containsKey(i)) {
                    c.get(neighbor).put(i, -c.get(i).get(neighbor));
                }
                f.get(i).put(neighbor, 0);
                f.get(neighbor).put(i, 0);
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

    public static void main(String[] args) {
        ArrayList<HashMap<Integer, Integer>> g = new ArrayList<HashMap<Integer, Integer>>();
        for (int i = 0; i < 10; i++)
            g.add(new HashMap<Integer, Integer>());
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
        System.out.println(fordFulkerson(g, 0, 9));
    }
}