package Fall_09_21_14;

/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: B
*/

import java.io.*;
import java.util.*;

class B {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("B.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("B.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        HashMap<String, Integer> targets = new HashMap<String, Integer>();
        int targetNum = 0;
        int[][] hops = new int[100000][100000];
        while (line.hasMoreTokens()) {
            String cmd = line.nextToken();
            if (cmd.equals("add")) {
                String target1 = line.nextToken();
                if (!targets.containsKey(target1)) {
                    targets.put(target1, targetNum);
                    targetNum++;
                }
                if (line.hasMoreTokens()) {
                    String target2 = line.nextToken();
                    if (!targets.containsKey(target2)) {
                        targets.put(target2, targetNum);
                        targetNum++;
                    }
                }
            }
            line = new StringTokenizer(in.readLine());
        }
        in.close();
        
        out.close();
        System.exit(0);
    }
}
