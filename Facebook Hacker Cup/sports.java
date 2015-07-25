import java.io.*;
import java.util.*;

class sports {
    public static int mod = 1000000007;

    public static void main(String[] args) throws IOException {
        //Segner's recurrence relation for Catalan numbers
        long[] c = new long[2001];
        c[0] = 1;
        for (int i = 1; i <= 2000; i++) {
            int sum = 0;
            for (int j = 0; j <= i - 1; j++) {
                sum += (c[j] * c[i - 1 - j]) % mod;
                sum %= mod;
            }
            c[i] = sum;
        }
        BufferedReader in = new BufferedReader(new FileReader("winning_at_sports.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sports.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine(), "-");
            int score1 = Integer.parseInt(line.nextToken());
            int score2 = Integer.parseInt(line.nextToken());
            int[][] dists = new int[score1 + 1][score2 + 1];
            dists[score1][score2] = 0;
            for (int x = score1; x > score2; x--) {
                dists[x][score2] = 1;
            }
            for (int y = score2; y >= 0; y--) {
                dists[score1][y] = 1;
            }
            for (int y = score2 - 1; y >= 0; y--) {
                for (int x = score1 - 1; x > y; x--) {
                    dists[x][y] = (dists[x + 1][y] + dists[x][y + 1]) % mod;
                }
            }
            dists[0][0] = dists[1][0];
            out.println("Case #" + i + ": " + dists[0][0] + " " + c[score2]);
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    public static class Pair {
        int a;
        int b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public boolean equals(Object other) {
            return (other != null && a == ((Pair) other).a && b == ((Pair) other).b);
        }

        @Override
        public int hashCode() {
            int hash = 5;
            hash = 59 * hash + this.a;
            hash = 59 * hash + this.b;
            return hash;
        }
    }
}
