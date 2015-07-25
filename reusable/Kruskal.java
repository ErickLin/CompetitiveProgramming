import java.util.ArrayList;
import java.util.Collections;

public class Kruskal {
    public static int kruskal(int n, int[][] weight, ArrayList<Edge> edges) {
        int[] parents = new int[n];
        int[] ranks = new int[n];
        for (int vertex = 0; vertex < n; vertex++) {
            parents[vertex] = vertex;
            ranks[vertex] = 0;
        }
        Collections.sort(edges);
        //System.out.println(edges);
        int totalCost = 0;
        for (Edge edge : edges) {
            int v1 = edge.get1();
            int v2 = edge.get2();
            int r1 = findParent(v1, parents);
            int r2 = findParent(v2, parents);
            if (r1 != r2) {
                //System.out.println(v1 + " " + v2 + " " + weight[v1][v2]);
                totalCost += weight[v1][v2];
                if (ranks[r1] > ranks[r2])
                    parents[r2] = r1;
                else {
                    if (ranks[r1] == ranks[r2])
                        ranks[r2]++;
                    parents[r1] = r2;
                }
            }
        }
        return totalCost;
    }
    
    private static int findParent(int vertex, int[] parents) {
        if (vertex != parents[vertex])
            parents[vertex] = findParent(parents[vertex], parents);
        return parents[vertex];
    }
    
    public static class Edge implements Comparable<Edge> {
        int vertex1, vertex2, weight;
        
        public Edge(int v1, int v2, int wt) {
            vertex1 = v1;
            vertex2 = v2;
            weight = wt;
        }
        
        public int get1() {
            return vertex1;
        }
        
        public int get2() {
            return vertex2;
        }
        
        public int getWeight() {
            return weight;
        }
        
        @Override
        public String toString() {
            return "(" + vertex1 + ", " + vertex2 + ") " + weight;
        }
        
        @Override
        public int compareTo(Edge other) {
            return new Integer(weight).compareTo(other.weight);
        }
    }
}