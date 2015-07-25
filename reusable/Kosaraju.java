import java.util.*;

public class Kosaraju {
    public static void main(String[] args) {
        int n = 5;
        boolean[][] isNeighbor = new boolean[n][n];
        isNeighbor[1][0] = true;
        isNeighbor[0][2] = true;
        isNeighbor[2][1] = true;
        isNeighbor[0][3] = true;
        isNeighbor[3][4] = true;
        System.out.println(Arrays.toString(kosaraju(n, isNeighbor)));
    }
    
    public static int[] kosaraju(int n, boolean[][] isNeighbor)
        throws NoSuchElementException {
        HashSet<Integer> remaining = new HashSet<Integer>(n);
        for (int i = 0; i < n; i++)
            remaining.add(i);
        Stack<Integer> s = new Stack<Integer>();
        while (s.size() < n) {
            dfs(remaining.iterator().next(), isNeighbor, s, remaining);
        }
        boolean[][] isPrev = transpose(isNeighbor);
        for (int i = 0; i < n; i++)
            remaining.add(i);
        int[] components = new int[n];
        int component = 0;
        while (!s.isEmpty()) {
            int v = s.pop();
            if (remaining.contains(v)) {
                dfs2(v, isPrev, s, remaining, components, component);
            }
            component++;
        }
        return components;
    }
    
    private static void dfs(int v, boolean[][] isNeighbor, Stack<Integer> s,
            HashSet<Integer> remaining) {
        int n = isNeighbor.length;
        remaining.remove(v);
        for (int i = 0; i < n; i++)
            if (isNeighbor[v][i] && remaining.contains(i))
                dfs(i, isNeighbor, s, remaining);
        s.push(v);
    }
    
    private static void dfs2(int v, boolean[][] isPrev, Stack<Integer> s,
            HashSet<Integer> remaining, int[] components, int component) {
        int n = isPrev.length;
        components[v] = component;
        remaining.remove(v);
        for (int i = 0; i < n; i++)
            if (isPrev[v][i] && remaining.contains(i))
                dfs2(i, isPrev, s, remaining, components, component);
    }
    
    public static boolean[][] transpose(boolean[][] matrix) {
        int n = matrix.length;
        boolean[][] ret = new boolean[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                ret[i][j] = matrix[j][i];
            }
        return ret;
    }
}