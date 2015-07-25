import java.io.*;
import java.util.*;

public class streak {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int k = Integer.parseInt(line.nextToken());
        in.close();
        long combinations = 0;
        for (int a = 0; a < k; a++)
            combinations += comb(n, a);
        long total = (long) Math.pow(2, n);
        long gcd = gcd(combinations, total);
        combinations /= gcd;
        total /= gcd;
        System.out.println((total - combinations) + "/" + total);
        System.exit(0);
    }
    
    public static long comb(int n, int k) {
        if (k > n / 2)
            return comb(n, n - k);
        long ret = 1;
        for (int a = 1; a <= k; a++) {
            ret *= (n - a + 1);
            ret /= a;
        }
        return ret;
    }

    public static long gcd(long k, long m) {
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
