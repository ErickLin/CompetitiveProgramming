package fall_11_02_14;

import java.io.*;
import java.util.*;

public class B {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int n1, n2, m, caseNum = 1;
        while ((n1 = Integer.parseInt(in.next())) != 0) {
            n2 = Integer.parseInt(in.next());
            m = Integer.parseInt(in.next());
            int[] t1 = new int[n1];
            int[] t2 = new int[n2];
            for (int i = 0; i < n1; i++) {
                t1[i] = -1;
            }
            for (int i = 0; i < n2; i++) {
                t2[i] = -1;
            }
            for (int i = 0; i < m; i++) {
                int v = Integer.parseInt(in.next());
                int x = t1[v % n1];
                t1[v % n1] = v;
                while (x != -1) {
                    v = t2[x % n2];
                    t2[x % n2] = x;
                    if (v != -1 && t1[v % n1] != -1) {
                        x = t1[v % n1];
                        t1[v % n1] = v;
                    } else {
                        x = -1;
                    }
                }
            }
            System.out.println("Case " + caseNum + ":");
            for (int i = 0; i < n1; i++)
                if (t1[i] != -1) {
                    System.out.println("Table 1");
                    break;
                }
            for (int i = 0; i < n1; i++)
                if (t1[i] != -1)
                    System.out.println(i + ":" + t1[i]);
            for (int i = 0; i < n2; i++)
                if (t2[i] != -1) {
                    System.out.println("Table 2");
                    break;
                }
            for (int i = 0; i < n2; i++)
                if (t2[i] != -1)
                    System.out.println(i + ":" + t2[i]);
            caseNum++;
        }
        in.close();
        System.exit(0);
    }
}
