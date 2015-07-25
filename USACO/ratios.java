/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ratios
*/

import java.io.*;
import java.util.*;

class ratios {
    static int MAX = 99999999;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("ratios.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ratios.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int[] goalRatio = new int[3];
        int[][] ratios = new int[3][3];
        for (int j = 0; j < 3; j++)
            goalRatio[j] = Integer.parseInt(line.nextToken());
        for (int i = 0; i < 3; i++) {
            line = new StringTokenizer(in.readLine());
            for (int j = 0; j < 3; j++)
                ratios[i][j] = Integer.parseInt(line.nextToken());
        }
        in.close();
        int minSum = MAX;
        int _a = 0, _b = 0, _c = 0, _d = 0;
        for (int a = 0; a < 100; a++)
            for (int b = 0; b < 100; b++)
                for (int c = 0; c < 100; c++) {
                    if (a == 0 && b == 0 && c == 0)
                        continue;
                    boolean equal = true;
                    int d = 0;
                    for (int j = 0; j < 3; j++) {
                        int sum = a * ratios[0][j] + b * ratios[1][j] + c * ratios[2][j];
                        if (goalRatio[j] > 0) {
                            if (sum == 0 || sum % goalRatio[j] != 0 || (d != 0 && sum / goalRatio[j] != d)) {
                                equal = false;
                                break;
                            } else
                                d = sum / goalRatio[j];
                        } else if (sum > 0) {
                            equal = false;
                            break;
                        }
                    }
                    if (equal && d != 0 && a + b + c + d < minSum) {
                        _a = a;
                        _b = b;
                        _c = c;
                        _d = d;
                        minSum = a + b + c + d;
                    }
                }
        if (minSum == MAX)
            out.println("NONE");
        else
            out.println(_a + " " + _b + " " + _c + " " + _d);
        out.close();
        System.exit(0);
    }
}
