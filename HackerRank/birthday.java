import java.io.*;
import java.util.*;

public class birthday {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            long b = Integer.parseInt(line.nextToken());
            long w = Integer.parseInt(line.nextToken());
            line = new StringTokenizer(in.readLine());
            long x = Integer.parseInt(line.nextToken());
            long y = Integer.parseInt(line.nextToken());
            long z = Integer.parseInt(line.nextToken());
            if (Math.min(x, y) + z < Math.max(x, y)) {
                if (x < y) {
                    System.out.println(b * x + w * (x + z));
                } else {
                    System.out.println(b * (y + z) + w * y);
                }
            } else {
                System.out.println(b * x + w * y);
            }
        }
        in.close();
        System.exit(0);
    }
}
