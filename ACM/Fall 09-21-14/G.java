package Fall_09_21_14;

/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: G
*/

import java.io.*;
import java.util.*;
import java.text.*;

class G {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("G.out")));
        int input = 1;
        while (true) {
            String ln = in.readLine();
            while (ln.isEmpty())
                ln = in.readLine();
            int n = Integer.parseInt(ln);
            if (n < 0)
                break;
            int xTot = 0;
            int yTot = 0;
            int mTot = 0;
            for (int i = 0; i < n; i++) {
                StringTokenizer line = new StringTokenizer(in.readLine());
                int a = Integer.parseInt(line.nextToken());
                int b = Integer.parseInt(line.nextToken());
                int m = Integer.parseInt(line.nextToken());
                xTot += a * m;
                yTot += b * m;
                mTot += m;
            }
            if (n > 0) {
                double xCent = ((double)xTot) / mTot;
                double yCent = ((double)yTot) / mTot;
                DecimalFormat df = new DecimalFormat("0.00");
                System.out.println("Case " + input + ": " + df.format(xCent) + " " + df.format(yCent));
            }
            input++;
        }
        in.close();
        //out.close();
        System.exit(0);
    }
}
