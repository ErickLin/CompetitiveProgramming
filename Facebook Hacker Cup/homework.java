import java.io.*;
import java.util.*;

class homework {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("homework.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("homework.out")));
        boolean[] isPrime = new boolean[10000001];
        HashSet<Integer> primes = new HashSet<Integer>();
        for (int i = 2; i <= 10000000; i++)
            isPrime[i] = true;
        for (int i = 2; i < 3163; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= 10000000; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        for (int i = 2; i <= 10000000; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
        int[] omega = new int[10000001];
        for (int p : primes) {
            omega[p] = 1;
            for (long j = ((long) p) * p; j <= 10000000; j *= p) {
                omega[(int) j] = 1;
            }
        }
        for (int p : primes) {
            for (int i = 10000000 / p; i >= 0; i--) {
                if (omega[i] != 0) {
                    for (long j = ((long) i) * p; j <= 10000000; j *= p) {
                        if (omega[(int) j] == 0 || omega[i] + 1 < omega[(int) j])
                            omega[(int) j] = omega[i] + 1;
                    }
                }
            }
        }
        int[][] prefix = new int[10000001][9];
        int[] count = new int[9];
        for (int i = 2; i <= 10000000; i++) {
            count[omega[i]]++;
            for (int j = 0; j <= 8; j++) {
                prefix[i][j] = count[j];
            }
        }
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken());
            int b = Integer.parseInt(line.nextToken());
            int k = Integer.parseInt(line.nextToken());
            if (a == 2) {
                out.println("Case #" + i + ": " + prefix[b][k]);
            } else {
                out.println("Case #" + i + ": " + (prefix[b][k] - prefix[a - 1][k]));
            }
        }
        in.close();
        out.close();
        System.exit(0);
    }
}
