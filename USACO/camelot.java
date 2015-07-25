/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: camelot
*/

import java.io.*;
import java.util.*;

class camelot {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("camelot.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("camelot.out")));
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

        int minMoves = Integer.MAX_VALUE;
        int[][][][] dists = new int[r][c][r][c];
        for (int destRow = 0; destRow < r; destRow++) {
            for (int destCol = 0; destCol < c; destCol++) {
                for (int i = 0; i < r; i++)
                    for (int j = 0; j < c; j++)
                        dists[destRow][destCol][i][j] = 99999999;
                LinkedList<Pair> q = new LinkedList<Pair>();
                boolean[][] visited = new boolean[r][c];
                q.push(new Pair(destRow, destCol));
                dists[destRow][destCol][destRow][destCol] = 0;
                visited[destRow][destCol] = true;
                while (!q.isEmpty()) {
                    Pair square = q.pop();
                    for (int i = 0; i < 8; i++) {
                        int a = square.a + knightMoveset[i].a;
                        int b = square.b + knightMoveset[i].b;
                        if (a >= 0 && b >= 0 && a < r && b < c && !visited[a][b]) {
                            q.add(new Pair(a, b));
                            dists[destRow][destCol][a][b] = dists[destRow][destCol][square.a][square.b] + 1;
                            visited[a][b] = true;
                        }
                    }
                }
            }
        }
        for (int destRow = 0; destRow < r; destRow++) {
            for (int destCol = 0; destCol < c; destCol++) {
                int moves = 0;
                for (Pair knight : knights) {
                    moves += dists[destRow][destCol][knight.a][knight.b];
                }
                //King moves to gathering square separately
                int minPickupCost = Math.max(Math.abs(king.a - destRow), Math.abs(king.b - destCol));
                for (Pair knight : knights) {
                    //King moves to knight
                    minPickupCost = Math.min(minPickupCost, Math.max(Math.abs(king.a - knight.a), Math.abs(king.b - knight.b)));
                    //Knight moves to king
                    minPickupCost = Math.min(minPickupCost, dists[destRow][destCol][king.a][king.b] + dists[king.a][king.b][knight.a][knight.b]
                            - dists[destRow][destCol][knight.a][knight.b]);
                }
                System.out.println(moves + " " + minPickupCost);
                moves += minPickupCost;
                if (moves < minMoves) {
                    minMoves = moves;
                }
            }
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
                return new Integer(b).compareTo(other.b);
            } else {
                return new Integer(a).compareTo(other.a);
            }
        }

        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }
}
