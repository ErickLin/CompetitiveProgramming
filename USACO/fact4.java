/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fact4
*/

import java.io.*;

class fact4 {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("fact4.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fact4.out")));
        int n = Integer.parseInt(in.readLine());
        in.close();
        int rtDig = 1;
        int n2 = 0;
        int n5 = 0;
        for (int i = 2; i <= n; i++) {
            int num = i;
            while (num % 2 == 0) {
                n2++;
                num /= 2;
            }
            while (num % 5 == 0) {
                n5++;
                num /= 5;
            }
            rtDig = (rtDig * (num % 10)) % 10;
        }
        //System.out.println(n2 + " " + n5);
        for (int i = 0; i < n2 - n5; i++)
            rtDig = (rtDig * 2) % 10;
        out.println(rtDig);
        out.close();
        System.exit(0);
    }
}
