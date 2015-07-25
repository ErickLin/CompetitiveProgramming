package Fall_09_27_14;

/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: J
*/

import java.io.*;
import java.util.*;

class J {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n;
        while ((n = Integer.parseInt(in.readLine())) != 0) {
            ArrayList<String> units = new ArrayList<String>(n);
            int[][] edgeLens = new int[n][n];
            ArrayList<ArrayList<Integer>> edges = new ArrayList<ArrayList<Integer>>(n);
            for (int i = 0; i < n; i++)
                edges.add(new ArrayList<Integer>());
            for (int i = 0; i < n; i++)
                edgeLens[i][i] = 1;
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int i = 0; i < n; i++)
                units.add(line.nextToken());
            for (int i = 0; i < n - 1; i++) {
                line = new StringTokenizer(in.readLine());
                int v1 = units.indexOf(line.nextToken());
                line.nextToken();
                int multiplier = Integer.parseInt(line.nextToken());
                int v2 = units.indexOf(line.nextToken());
                edgeLens[v1][v2] = multiplier;
                edges.get(v1).add(v2);
                /*for (int j = 0; j < n; j++) {
                    if (edgeLens[v1][j] != 0) {
                        if (edgeLens[v1][j] > edgeLens[v1][v2])
                            edgeLens[v2][j] = edgeLens[v1][j] / edgeLens[v1][v2];
                        else
                            edgeLens[j][v2] = edgeLens[v1][v2] / edgeLens[v1][j];
                    }
                    if (edgeLens[v2][j] != 0)
                        edgeLens[v1][j] = edgeLens[v1][v2] * edgeLens[v2][j];
                    if (edgeLens[j][v1] != 0)
                        edgeLens[j][v2] = edgeLens[j][v1] * edgeLens[v1][v2];
                    if (edgeLens[j][v2] != 0) {
                        if (edgeLens[j][v2] > edgeLens[v1][v2])
                            edgeLens[j][v1] = edgeLens[j][v2] / edgeLens[v1][v2];
                        else
                            edgeLens[v1][j] = edgeLens[v1][v2] / edgeLens[j][v2];
                    }
                }*/
            }
            for (int i = 0; i < n; i++)
                edgeLens = bfs(n, i, edges, edgeLens);
            int root = 0;
            boolean hasRoot;
            do {
                hasRoot = false;
                for (int i = 0; i < n; i++)
                    if (edgeLens[i][root] > 1) {
                        hasRoot = true;
                        root = i;
                    }
            } while (hasRoot);
            int[] sortedUnits = new int[n];
            for (int i = 0; i < n; i++)
                sortedUnits[i] = i;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (edgeLens[root][sortedUnits[i]] < edgeLens[root][sortedUnits[j]]) {
                        int temp = sortedUnits[i];
                        sortedUnits[i] = sortedUnits[j];
                        sortedUnits[j] = temp;
                    }
                }
            }
            System.out.print("1" + units.get(root));
            for (int i = 1; i < n; i++) {
                int unit = sortedUnits[i];
                System.out.print(" = " + edgeLens[root][unit] + units.get(unit));
            }
            System.out.println();
        }
        in.close();
        System.exit(0);
    }
    
    public static int[][] bfs(int n, int root, ArrayList<ArrayList<Integer>> edges, int[][] edgeLens)
    {
        PriorityQueue<Integer> worlds = new PriorityQueue<Integer>(n, new Comparator<Integer>() {
            private int[][] edgeLens;
            private int root;
            
            @Override
            public int compare(Integer a, Integer b)
            {
                int num1 = edgeLens[root][a];
                int num2 = edgeLens[root][b];
                if (edgeLens[root][a] == 0)
                    num1 = 99999999;
                if (edgeLens[root][b] == 0)
                    num2 = 99999999;
                return new Integer(num1).compareTo(num2);
            }
            
            //Constructor to allow passing the variables into inner class
            private Comparator<Integer> init(int[][] e, int r) {
                edgeLens = e;
                root = r;
                return this;
            }
        }.init(edgeLens, root));
        for (int unit = 0; unit < n; unit++)
            worlds.add(unit);
        while (worlds.size() > 0) {
            int unit = worlds.poll();
            if (edgeLens[root][unit] > 0)
                for (int i = 0; i < n; i++)
                    if (i != unit && edgeLens[root][i] == 0) {
                        if (edgeLens[unit][i] > 0)
                            edgeLens[root][i] = edgeLens[root][unit] * edgeLens[unit][i];
                        else if (edgeLens[i][unit] > 0)
                            edgeLens[root][i] = edgeLens[root][unit] / edgeLens[i][unit];
                        //decrease-key
                        worlds.remove(i);
                        worlds.add(i);
                    }
        }
        return edgeLens;
    }
}