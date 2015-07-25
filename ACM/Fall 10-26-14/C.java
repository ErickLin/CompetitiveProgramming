package fall_10_26_14;

import java.io.*;
import java.util.*;

public class C {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        if (n % 2 == 0) {
            System.out.println("NOT POSSIBLE");
        } else {
            String u = in.readLine();
            String s = "";
            int counter = 0;
            int pos = u.length() / 2;
            for (int i = 0; i < u.length() / 2; i++) {
                int pos2 = pos;
                if (!u.substring(i, i + 1).equals(u.substring(pos2 + i, pos2 + i + 1))) {
                    pos2++;
                    if (!u.substring(i, i + 1).equals(u.substring(pos2 + i, pos2 + i + 1)))
                        break;
                }
                if (i == u.length() / 2 - 1) {
                    counter++;
                    s = u.substring(0, (u.length() - 1) / 2);
                }
            }
            pos = u.length() / 2 + 1;
            for (int i = 0; i < u.length() / 2; i++) {
                int pos2 = 0;
                if (!u.substring(pos2 + i, pos2 + i + 1).equals(u.substring(pos + i, pos + i + 1))) {
                    pos2++;
                    if (!u.substring(pos2 + i, pos2 + i + 1).equals(u.substring(pos + i, pos + i + 1)))
                        break;
                }
                if (i == u.length() / 2 - 1) {
                    counter++;
                    s = u.substring((u.length() - 1) / 2 + 1, u.length());
                }
            }
            /*
            for (int i = 0; i < n; i++) {
                String t = u.substring(0, i) + u.substring(i + 1);
                //System.out.println(t);
                if (t.substring(0, (n - 1) / 2).equals(t.substring((n - 1) / 2, n - 1))) {
                    counter++;
                    s = t.substring(0, (n - 1) / 2);
                }
            }
            */
            if (counter == 0) {
                System.out.println("NOT POSSIBLE");
            } else if (counter == 1) {
                System.out.println(s);
            } else {
                System.out.println("NOT UNIQUE");
            }
        }
        in.close();
        System.exit(0);
    }
}
