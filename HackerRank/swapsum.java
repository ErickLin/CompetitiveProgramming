import java.io.*;
import java.util.*;

public class swapsum {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int q = Integer.parseInt(line.nextToken());
        int[] a = new int[n];
        int[] prefix = new int[n];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line.nextToken());
            if (i == 0)
                prefix[i] = a[i];
            else
                prefix[i] = prefix[i - 1] + a[i];
        }
        for (int i = 0; i < q; i++) {
            line = new StringTokenizer(in.readLine());
            int t = Integer.parseInt(line.nextToken());
            int l = Integer.parseInt(line.nextToken()) - 1;
            int r = Integer.parseInt(line.nextToken()) - 1;
            if (t == 1) {
                for (int j = l; j <= r; j += 2) {
                    prefix[j] += a[j + 1] - a[j];
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                }
            } else {
                if (l == 0)
                    System.out.println(prefix[r]);
                else
                    System.out.println(prefix[r] - prefix[l - 1]);
            }
        }
        in.close();
        System.exit(0);
    }
}
