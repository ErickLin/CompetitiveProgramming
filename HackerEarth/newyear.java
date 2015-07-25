import java.io.*;
import java.util.*;

public class newyear {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int k = Integer.parseInt(line.nextToken());
        int[][] matrix = new int[n][n];
        for (int row = 0; row < n; row++) {
            line = new StringTokenizer(in.readLine());
            for (int col = 0; col < n; col++) {
                matrix[row][col] = Integer.parseInt(line.nextToken());
            }
        }
        in.close();
        boolean[] isPrime = new boolean[10202];
        Arrays.fill(isPrime, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (int i = 2; i <= 101; i++)
            for (int j = 2; i * j <= 10201; j++) {
                isPrime[i * j] = false;
            }
        int[] operations = new int[10001];
        if (k == 1) {
            int nextPrime = 10007;
            for (int i = 10000; i >= 0; i--) {
                if (isPrime[i])
                    nextPrime = i;
                operations[i] = nextPrime - i;
            }
        } else {
            for (int i = 1; i <= 10000; i++) {
                if (isPrime[i])
                    operations[i] = 0;
                else if (gcd(i, k) != 1)
                    operations[i] = -1;
                else {
                    for (int j = 1; i + j * k <= 10201; j++) {
                        if (isPrime[i + j * k]) {
                            operations[i] = j;
                            break;
                        }
                    }
                }
            }
        }
        int min = Integer.MAX_VALUE;
        int r = -1;
        int c = -1;
        for (int row = 1; row < n - 1; row++)
            for (int col = 1; col < n - 1; col++) {
                int count = 0;
                if (operations[matrix[row][col]] == -1)
                    continue;
                else
                    count += operations[matrix[row][col]];
                if (operations[matrix[row - 1][col - 1]] == -1)
                    continue;
                else
                    count += operations[matrix[row - 1][col - 1]];
                if (operations[matrix[row - 1][col + 1]] == -1)
                    continue;
                else
                    count += operations[matrix[row - 1][col + 1]];
                if (operations[matrix[row + 1][col - 1]] == -1)
                    continue;
                else
                    count += operations[matrix[row + 1][col - 1]];
                if (operations[matrix[row + 1][col + 1]] == -1)
                    continue;
                else
                    count += operations[matrix[row + 1][col + 1]];
                if (count < min) {
                    min = count;
                    r = row;
                    c = col;
                }
            }
        if (min == Integer.MAX_VALUE)
            System.out.println("no");
        else {
            System.out.println("yes");
            System.out.println(min);
            System.out.println((r + 1) + " " + (c + 1));
        }
        System.exit(0);
    }

    public static int gcd(int k, int m) {
        while (k != m) {
            if (k > m) {
                k -= m;
            } else {
                m -= k;
            }
        }
        return k;
    }
}
