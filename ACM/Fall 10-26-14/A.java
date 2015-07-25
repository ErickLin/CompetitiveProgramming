package fall_10_26_14;

import java.io.*;
import java.util.*;

public class A {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int q = Integer.parseInt(line.nextToken());
        int l = 0;
        int r = 0;
        int a = 0;
        int b = 0;
        for (int i = 0; i < q; i++) {
            line = new StringTokenizer(in.readLine());
            int action = Integer.parseInt(line.nextToken());
            if (action == 1) {
                l = Integer.parseInt(line.nextToken());
                r = Integer.parseInt(line.nextToken());
                a = Integer.parseInt(line.nextToken());
                b = Integer.parseInt(line.nextToken());
            } else {
                
            }
        }
        in.close();
        
        System.exit(0);
    }
}
