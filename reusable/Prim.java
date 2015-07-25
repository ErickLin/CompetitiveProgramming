public class Prim {
    static final int MAX = 99999999;
    
    public static int prim(int n, boolean[][] isNeighbor, int[][] weight) {
        int[] cost = new int[n];
        int[] prev = new int[n];
        boolean[] visited = new boolean[n];
        //initialize starting vertex (field)
        cost[0] = 0;
        visited[0] = true;
        for (int i = 1; i < n; i++) {
            cost[i] = MAX;
            prev[i] = -1;
        }
        int current = 0;
        while (current != -1) {
            int nearest = -1;
            int minCost = MAX;
            boolean isEmpty = true;
            for (int neighbor = 0; neighbor < n; neighbor++) {
                if (isNeighbor[current][neighbor] && !visited[neighbor]) {
                    isEmpty = false;
                    if (cost[neighbor] > weight[current][neighbor]) {
                        cost[neighbor] = weight[current][neighbor];
                        prev[neighbor] = current;
                    }
                    if (cost[neighbor] < minCost) {
                        minCost = cost[neighbor];
                        nearest = neighbor;
                    }
                }
            }
            if (isEmpty) //has no neighbor
                return -1;
            visited[current] = true;
            current = nearest;
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