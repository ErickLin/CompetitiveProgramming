package hackerrank;

import java.io.*;
import java.util.*;

public class upvotes {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int k = Integer.parseInt(line.nextToken());
        int[] upvotes = new int[n];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < n; i++) {
            upvotes[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        boolean[] start = new boolean[n];
        boolean[] end = new boolean[n];
        int length;
        int endpos;
        for (int i = 0; i < k; i++) {
            
        }
        for (int i = k - 1; i < n; i++) {
            System.out.println(subSizeND[i] + " " + subSizeNI[i] + " " + (subSizeND[i] - subSizeNI[i]));
            /*
            long nonDec = 0;
            int start = i;
            for (int j = i + 1; j < i + k; j++) {
                if (upvotes[j] < upvotes[j - 1]) {
                    int len = j - start;
                    nonDec += len * (len - 1) / 2;
                    start = j;
                } else if (j == i + k - 1) {
                    int len = j - start + 1;
                    nonDec += len * (len - 1) / 2;
                }
            }
            long nonInc = 0;
            start = i;
            for (int j = i + 1; j < i + k; j++) {
                if (upvotes[j] > upvotes[j - 1]) {
                    int len = j - start;
                    nonInc += len * (len - 1) / 2;
                    start = j;
                } else if (j == i + k - 1) {
                    int len = j - start + 1;
                    nonInc += len * (len - 1) / 2;
                }
            }
            System.out.println(nonDec - nonInc);
            */
        }
        System.exit(0);
    }
}
