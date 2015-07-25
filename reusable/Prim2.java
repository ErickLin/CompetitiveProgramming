import java.util.PriorityQueue;
import java.util.Comparator;

public class Prim2 {
    static final int MAX = 99999999;
    static int[] cost;
    
    public static int prim(int n, boolean[][] isNeighbor, int[][] weight) {
        cost = new int[n];
        int[] prev = new int[n];
        for (int i = 0; i < n; i++) {
            cost[i] = MAX;
            prev[i] = -1;
        }
        //initialize starting vertex (field)
        cost[0] = 0;
        PriorityQueue<Integer> worlds = new PriorityQueue<Integer>(n, new Comparator<Integer>() {
            @Override
            public int compare(Integer a, Integer b) {
                return new Integer(cost[a]).compareTo(cost[b]);
            }
        });
        for (int vertex = 0; vertex < n; vertex++)
            worlds.add(vertex);
        while (worlds.size() > 0)  {
            int vertex = worlds.poll();
            boolean isEmpty = true;
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (isNeighbor[vertex][neighbor]) {
                    isEmpty = false;
                    if (worlds.contains(neighbor) && cost[neighbor] > weight[vertex][neighbor]) {
                        cost[neighbor] = weight[vertex][neighbor];
                        prev[neighbor] = vertex;
                        //decrease-key
                        worlds.remove(neighbor);
                        worlds.add(neighbor);
                    }
                }
            }
            if (isEmpty) //has no neighbor
                return -1;
        }
        /*for (int i = 0; i < n; i++)
            System.out.print(prev[i] + " ");*/
        int totalCost = 0;
        for (int vertex = 1; vertex < n; vertex++) {
            //System.out.println("(" + (vertex + 1) + ", " + (prev[vertex] + 1) + ")" + " " + weight[vertex][prev[vertex]]);
            totalCost += weight[vertex][prev[vertex]];
        }
        return totalCost;
    }
}