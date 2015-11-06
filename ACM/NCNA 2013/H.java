package Fall_09_21_14;

/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: H
*/

import java.io.*;
import java.util.*;

class H {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("H.out")));
        int input = 1;
        while (true) {
            String s1 = in.readLine();
            String s2 = in.readLine();
            if (s1.equals("END"))
                break;
            System.out.println("Case " + input + ": " + comp(s1, s2));
            input++;
        }
        in.close();
        //out.close();
        System.exit(0);
    }
    
    public static String comp(String s1, String s2) {
        if (s1.length() != s2.length())
            return "different";
        char[] c1 = new char[s1.length()];
        char[] c2 = new char[s2.length()];
        for (int i = 0; i < s1.length(); i++) {
            c1[i] = s1.charAt(i);
            c2[i] = s2.charAt(i);
        }
        Arrays.sort(c1);
        Arrays.sort(c2);
        //System.out.println(Arrays.toString(c1));
        //System.out.println(Arrays.toString(c2));
        for (int i = 0; i < s1.length(); i++)
            if (c1[i] != c2[i])
                return "different";
        return "same";
    }
}
