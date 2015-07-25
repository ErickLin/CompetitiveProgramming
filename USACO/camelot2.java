/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: camelot
*/

import java.io.*;
import java.util.*;

class camelot2 {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("camelot2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("camelot2.out")));
        int r = Integer.parseInt(in.next());
        int c = Integer.parseInt(in.next());

        int col = in.next().charAt(0) - 65;
        int row = Integer.parseInt(in.next()) - 1;
        Pair king = new Pair(row, col);

        TreeSet<Pair> knights = new TreeSet<Pair>();
        while (in.hasNext()) {
            col = in.next().charAt(0) - 65;
            row = Integer.parseInt(in.next()) - 1;
            knights.add(new Pair(row, col));
        }
        in.close();

        Pair[] knightMoveset = new Pair[8];
        knightMoveset[0] = new Pair(-2, 1);
        knightMoveset[1] = new Pair(-1, 2);
        knightMoveset[2] = new Pair(1, 2);
        knightMoveset[3] = new Pair(2, 1);
        knightMoveset[4] = new Pair(2, -1);
        knightMoveset[5] = new Pair(1, -2);
        knightMoveset[6] = new Pair(-1, -2);
        knightMoveset[7] = new Pair(-2, -1);

        int[][][][] dists = new int[r][c][r][c];
        int[][] moves = new int[r][c];
        int[][] pickupCost = new int[r][c];
        Pair[][] pickupKnight = new Pair[r][c];
        for (row = 0; row < r; row++) {
            for (col = 0; col < c; col++) {
                LinkedList<Pair> q = new LinkedList<Pair>();
                boolean[][] visited = new boolean[r][c];
                q.push(new Pair(row, col));
                dists[row][col][row][col] = 0;
                visited[row][col] = true;
                while (!q.isEmpty()) {
                    Pair square = q.pop();
                    for (int i = 0; i < 8; i++) {
                        int a = square.a + knightMoveset[i].a;
                        int b = square.b + knightMoveset[i].b;
                        if (a >= 0 && b >= 0 && a < r && b < c && !visited[a][b]) {
                            q.add(new Pair(a, b));
                            dists[row][col][a][b] = dists[row][col][square.a][square.b] + 1;
                            visited[a][b] = true;
                        }
                    }
                }
                //King's distance
                pickupCost[row][col] = Math.max(Math.abs(king.a - row), Math.abs(king.b - col));
                int min = Integer.MAX_VALUE;
                for (Pair knight : knights) {
                    moves[row][col] += dists[row][col][knight.a][knight.b];
                    if (moves[row][col] < min) {
                        min = moves[row][col];
                        pickupKnight[row][col] = knight;
                    }
                }
                pickupCost[row][col] += min;
            }
        }
        
        int minMoves = Integer.MAX_VALUE;
        for (int destRow = 0; destRow < r; destRow++)
            for (int destCol = 0; destCol < c; destCol++)
                for (int pickupRow = 0; pickupRow < r; pickupRow++)
                    for (int pickupCol = 0; pickupCol < c; pickupCol++) {
                        minMoves = Math.min(minMoves, moves[destRow][destCol]
                                + pickupCost[pickupRow][pickupCol]
                                + dists[pickupRow][pickupCol][destRow][destCol]);
                    }
        out.println(minMoves);
        out.close();
        System.exit(0);
    }
    
    private static class Pair implements Comparable<Pair>{
        int a;
        int b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public boolean equals(Object other) {
            if (other == null)
                return false;
            if (other instanceof Pair) {
                return a == ((Pair) other).a && b == ((Pair) other).b;
            }
            return false;
        }

        @Override
        public int hashCode() {
            int hash = 7;
            hash = 29 * hash + this.a;
            hash = 29 * hash + this.b;
            return hash;
        }

        @Override
        public int compareTo(Pair other) {
            if (a == other.a) {
                return Integer.compare(b, other.b);
            } else {
                return Integer.compare(a, other.a);
            }
        }

        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }
}
