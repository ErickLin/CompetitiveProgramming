import java.util.*;

public class Tarjan {
    static final int MAX = 99999999;
    static int counter, component;
    
    public static void main(String[] args) {
        int n = 5;
        boolean[][] isNeighbor = new boolean[n][n];
        isNeighbor[1][0] = true;
        isNeighbor[0][2] = true;
        isNeighbor[2][1] = true;
        isNeighbor[0][3] = true;
        isNeighbor[3][4] = true;
        System.out.println(Arrays.toString(tarjan(n, isNeighbor)));
    }
    
    public static int[] tarjan(int n, boolean[][] isNeighbor) {
        int[] discovered = new int[n];
        int[] lowestLink = new int[n];
        for (int i = 0; i < n; i++) {
            discovered[i] = MAX;
            lowestLink[i] = MAX;
        }
        counter = 0;
        component = 0;
        Stack<Integer> s = new Stack<Integer>();
        int[] components = new int[n];
        for (int v = 0; v < n; v++)
            if (discovered[v] == MAX)
                strongConnect(v, isNeighbor, discovered, lowestLink, s,
                        components);
        return components;
    }
    
    public static void strongConnect(int v, boolean[][] isNeighbor,
            int[] discovered, int[] lowestLink, Stack<Integer> s,
            int[] components) {
        discovered[v] = counter;
        lowestLink[v] = counter;
        counter++;
        s.push(v);
        int n = discovered.length;
        for (int w = 0; w < n; w++) {
            if (isNeighbor[v][w]) {
                if (discovered[w] == MAX) {
                    strongConnect(w, isNeighbor, discovered, lowestLink, s, components);
                }
                lowestLink[v] = Math.min(lowestLink[v], lowestLink[w]);
            }
        }
        //if root node
        if (lowestLink[v] == discovered[v]) {
            int w;
            do {
                w = s.pop();
                components[w] = component;
            } while (w != v);
            component++;
            counter = discovered[v];
        }
    }
}