/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: meeting
*/

import java.io.*;
import java.util.*;

class meeting {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("meeting.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("meeting.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        int[][] c = new int[n][n];
        int[][] d = new int[n][n];
        for (int i = 0; i < m; i++) {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            c[a][b] = Integer.parseInt(line.nextToken());
            d[a][b] = Integer.parseInt(line.nextToken());
        }
        in.close();
        boolean[][] cVisited = new boolean[n][10001];
        cVisited[0][0] = true;
        LinkedList<Pair> q = new LinkedList<Pair>();
        q.add(new Pair(0, 0));
        while (!q.isEmpty()) {
            Pair pair = q.poll();
            int node = pair.num;
            int t = pair.t;
            for (int next = 0; next < n; next++) {
                if (c[node][next] != 0 && !cVisited[next][t + c[node][next]]) {
                    q.add(new Pair(next, t + c[node][next]));
                    cVisited[next][t + c[node][next]] = true;
                }
            }
        }
        boolean[][] dVisited = new boolean[n][10001];
        dVisited[0][0] = true;
        q = new LinkedList<Pair>();
        q.add(new Pair(0, 0));
        while (!q.isEmpty()) {
            Pair pair = q.poll();
            int node = pair.num;
            int t = pair.t;
            for (int next = 0; next < n; next++) {
                if (d[node][next] != 0 && !dVisited[next][t + d[node][next]]) {
                    q.add(new Pair(next, t + d[node][next]));
                    dVisited[next][t + d[node][next]] = true;
                }
            }
        }
        boolean found = false;
        for (int t = 0; t <= 10000 && !found; t++) {
            if (cVisited[n - 1][t] && dVisited[n - 1][t]) {
                out.println(t);
                found = true;
            }
        }
        if (!found) {
            out.println("IMPOSSIBLE");
        }
        out.close();
        System.exit(0);
    }
    
    private static class Pair {
        int num;
        int t;

        public Pair(int num, int t) {
            this.num = num;
            this.t = t;
        }

        @Override
        public boolean equals(Object other) {
            return (other != null && num == ((Pair) other).num && t == ((Pair) other).t);
        }

        @Override
        public int hashCode() {
            int hash = 3;
            hash = 97 * hash + this.num;
            hash = 97 * hash + this.t;
            return hash;
        }
    }
}
