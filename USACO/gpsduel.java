/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: gpsduel
*/
import java.io.*;
import java.util.*;

public class gpsduel {

    public static int[] dists;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("gpsduel.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gpsduel.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        final int n = Integer.parseInt(line.nextToken());
        final int m = Integer.parseInt(line.nextToken());
        int[][] p = new int[n][n];
        int[][] q = new int[n][n];
        //ArrayList<HashSet<Integer>> neighbors = new ArrayList<HashSet<Integer>>();
        ArrayList<HashSet<Integer>> backNeighbors = new ArrayList<HashSet<Integer>>();
        for (int i = 0; i < n; i++) {
            //neighbors.add(new HashSet<Integer>());
            backNeighbors.add(new HashSet<Integer>());
        }
        for (int i = 0; i < m; i++) {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            int c = Integer.parseInt(line.nextToken());
            int d = Integer.parseInt(line.nextToken());
            if (p[a][b] == 0 || c < p[a][b])
                p[a][b] = c;
            if (q[a][b] == 0 || d < q[a][b])
                q[a][b] = d;
            //neighbors.get(a).add(b);
            if (!backNeighbors.get(b).contains(a)) {
                backNeighbors.get(b).add(a);
            }
        }
        int[] pNext = new int[n];
        int[] qNext = new int[n];
        final int[] pDistsToN = new int[n];
        final int[] qDistsToN = new int[n];
        for (int i = 0; i < n; i++) {
            pNext[i] = -1;
            qNext[i] = -1;
            pDistsToN[i] = Integer.MAX_VALUE;
            qDistsToN[i] = Integer.MAX_VALUE;
        }
        pDistsToN[n - 1] = 0;
        qDistsToN[n - 1] = 0;
//        System.out.println(Arrays.toString(pNext));
//        System.out.println(Arrays.toString(qNext));
        PriorityQueue<Integer> nodesP = new PriorityQueue<Integer>(n, new Comparator<Integer>() {
            @Override
            public int compare(Integer a, Integer b) {
                return new Integer(pDistsToN[a]).compareTo(pDistsToN[b]);
            }
        });
        nodesP.add(n - 1);
        while (!nodesP.isEmpty()) {
            int node = nodesP.poll();
            for (int backNeighbor : backNeighbors.get(node)) {
                if (p[backNeighbor][node] > 0 && p[backNeighbor][node] + pDistsToN[node] < pDistsToN[backNeighbor]) {
                    pNext[backNeighbor] = node;
                    pDistsToN[backNeighbor] = p[backNeighbor][node] + pDistsToN[node];
                    if (nodesP.contains(backNeighbor))
                        nodesP.remove(backNeighbor);
                    nodesP.add(backNeighbor);
                }
            }
        }
    
        PriorityQueue<Integer> nodesQ = new PriorityQueue<Integer>(n, new Comparator<Integer>() {
            @Override
            public int compare(Integer a, Integer b) {
                return new Integer(qDistsToN[a]).compareTo(qDistsToN[b]);
            }
        });
        nodesQ.add(n - 1);
        while (!nodesQ.isEmpty()) {
            int node = nodesQ.poll();
            for (int backNeighbor : backNeighbors.get(node)) {
                if (q[backNeighbor][node] > 0 && q[backNeighbor][node] + qDistsToN[node] < qDistsToN[backNeighbor]) {
                    qNext[backNeighbor] = node;
                    qDistsToN[backNeighbor] = q[backNeighbor][node] + qDistsToN[node];
                    if (nodesQ.contains(backNeighbor))
                        nodesQ.remove(backNeighbor);
                    nodesQ.add(backNeighbor);
                }
            }
        }
    
        dists = new int[n];
        for (int i = 0; i < n - 1; i++) {
            dists[i] = Integer.MAX_VALUE;
        }
        dists[n - 1] = 0;
        PriorityQueue<Integer> nodes = new PriorityQueue<Integer>(n, new Comparator<Integer>() {
            @Override
            public int compare(Integer a, Integer b) {
                return new Integer(dists[a]).compareTo(dists[b]);
            }
        });
        nodes.add(n - 1);
        while (!nodes.isEmpty()) {
            int node = nodes.poll();
            for (int backNeighbor : backNeighbors.get(node)) {
                if (dists[node] + (pNext[backNeighbor] == node ? 0 : 1)
                       + (qNext[backNeighbor] == node ? 0 : 1) < dists[backNeighbor]) {
                    dists[backNeighbor] = dists[node] + (pNext[backNeighbor] == node ? 0 : 1)
                            + (qNext[backNeighbor] == node ? 0 : 1);
                    if (nodes.contains(backNeighbor))
                        nodes.remove(backNeighbor);
                    nodes.add(backNeighbor);
                }
            }
        }
        out.println(dists[0]);
        out.close();
        System.exit(0);
    }
}