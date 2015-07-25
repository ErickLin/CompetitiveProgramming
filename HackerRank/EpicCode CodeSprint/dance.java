import java.io.*;
import java.util.*;

class Dance {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int k = Integer.parseInt(line.nextToken());
        line = new StringTokenizer(in.readLine());
        ArrayList<Integer> boys = new ArrayList<Integer>(n);
        for (int i = 0; i < n; i++) {
            boys.add(i, Integer.parseInt(line.nextToken()));
        }
        line = new StringTokenizer(in.readLine());
        ArrayList<Integer> girls = new ArrayList<Integer>(n);
        for (int i = 0; i < n; i++) {
            girls.add(i, Integer.parseInt(line.nextToken()));
        }
        in.close();

        Collections.sort(boys);
        Collections.sort(girls);
        HashMap<Integer, HashMap<Integer, Integer>> capacities = new HashMap<Integer, HashMap<Integer, Integer>>();
        //initialize all nodes
        for (int i = 0; i <= (n << 1) + 1; i++) {
            capacities.put(i, new HashMap<Integer, Integer>());
        }
        //initialize all edges from source to boys
        for (int i = 1; i <= n; i++) {
            capacities.get(0).put(i, 1);
        }
        //initialize all edges from boys to girls
        for (int i = 0; i < n; i++) {
            int lower = searchLeast(girls, boys.get(i) - k);
            int upper = searchGreatest(girls, boys.get(i) + k);
            for (int j = lower; j <= upper; j++) {
                capacities.get(i + 1).put(j + n + 1, 1);
            }
        }
        //initialize all edges from girls to sink
        for (int i = 0; i < n; i++) {
            capacities.get(i + n + 1).put((n << 1) + 1, 1);
        }
        System.out.println(fordFulkerson(capacities, 0, (n << 1) + 1));
        System.exit(0);
    }

    public static int searchLeast(ArrayList<Integer> arr, int elem) {
        int n = arr.size();
        if (arr.get(n - 1) < elem) {
            return -1;
        }
        if (arr.get(0) >= elem) {
            return 0;
        }
        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (arr.get(mid) >= elem) {
                if (mid == 0 || arr.get(mid - 1) < elem) {
                    return mid;
                } else {
                    hi = mid - 1;
                }
            } else {
                lo = mid + 1;
            }
        }
        return -1;
    }

    public static int searchGreatest(ArrayList<Integer> arr, int elem) {
        int n = arr.size();
        if (arr.get(n - 1) <= elem) {
            return n - 1;
        }
        if (arr.get(0) > elem) {
            return -1;
        }
        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (arr.get(mid) <= elem) {
                if (mid == n - 1 || arr.get(mid + 1) > elem) {
                    return mid;
                } else {
                    lo = mid + 1;
                }
            } else {
                hi = mid - 1;
            }
        }
        return -1;
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
