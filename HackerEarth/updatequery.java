import java.io.*;
import java.util.*;

class updatequery {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        int[] a = new int[n];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            a[i] = Integer.parseInt(line.nextToken());
        }
        for (int i = 0; i < m; i++) {
            line = new StringTokenizer(in.readLine());
            if (line.nextToken().equals("Q")) {
                int pos = Integer.parseInt(line.nextToken()) - 1;
                int c = Integer.parseInt(line.nextToken());
                if (c < 0) {
                    System.out.println("-1 -1");
                } else {
                    int length = 0;
                    int z = 0;
                    for (int j = pos; j < n && Math.abs(a[j] - a[pos]) <= c; j++) {
                        length++;
                        z = Math.max(z, Math.abs(a[j] - a[pos]));
                    }
                    System.out.println(length + " " + z);
                }
            } else {
                int pos = Integer.parseInt(line.nextToken()) - 1;
                int y = Integer.parseInt(line.nextToken());
                a[pos] = y;
            }
        }
        in.close();
        System.exit(0);
    }
}
