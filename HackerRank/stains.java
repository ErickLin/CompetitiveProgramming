package hackerrank;

import java.util.*;
import java.math.*;

public class stains {
    static final int MAX = 100000;
    static final int DIV = 1000000007;
    static int[][][][][][] memo;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int k = in.nextInt();
        int[] x = new int[n];
        int[] y = new int[n];
        int xMin = MAX;
        int xMax = -1;
        int yMin = MAX;
        int yMax = -1;
        HashMap<String, Integer> freqs = new HashMap<String, Integer>();
        for (int i = 0; i < n; i++) {
            x[i] = in.nextInt();
            y[i] = in.nextInt();
            if (x[i] == xMin)
                freqs.put("xMin", freqs.get("xMin") + 1);
            if (x[i] < xMin) {
                xMin = x[i];
                freqs.put("xMin", 1);
            }
            if (x[i] == xMax)
                freqs.put("xMax", freqs.get("xMax") + 1);
            if (x[i] > xMax) {
                xMax = x[i];
                freqs.put("xMax", 1);
            }
            if (y[i] == yMin)
                freqs.put("yMin", freqs.get("yMin") + 1);
            if (y[i] < yMin) {
                yMin = y[i];
                freqs.put("yMin", 1);
            }
            if (y[i] == yMax)
                freqs.put("yMax", freqs.get("yMax") + 1);
            if (y[i] > yMax) {
                yMax = y[i];
                freqs.put("yMax", 1);
            }
        }
        memo = new int[n + 1][k + 1][freqs.get("xMin") + 1][freqs.get("xMax") + 1][freqs.get("yMin") + 1][freqs.get("yMax") + 1];
        for (int pos = 0; pos <= n; pos++)
            for (int rem = 0; rem <= k; rem++)
                for (int xm = 0; xm <= freqs.get("xMin"); xm++)
                    for (int xM = 0; xM <= freqs.get("xMax"); xM++)
                        for (int ym = 0; ym <= freqs.get("yMin"); ym++)
                            for (int yM = 0; yM <= freqs.get("yMax"); yM++)
                                memo[pos][rem][xm][xM][ym][yM] = -1;
        System.out.println(gen(n, k, x, y, xMin, xMax, yMin, yMax, 
                freqs.get("xMin"), freqs.get("xMax"), freqs.get("yMin"), freqs.get("yMax"), 
                0, k));
    }
    
    public static int gen(int n, int k, int[] x, int[] y, 
            int xMin, int xMax, int yMin, int yMax, 
            int xMinReq, int xMaxReq, int yMinReq, int yMaxReq, 
            int pos, int remaining) {
        if (memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq] != -1)
            return memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq];
        if (remaining == 0) {
            if (xMinReq <= 0 || xMaxReq <= 0 || yMinReq <= 0 || yMaxReq <= 0)
                memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq] = 1;
            else
                memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq] = 0;
        }
        else if (n - pos < remaining)
            memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq] = 0;
        //cleaning solution still remaining at the end
        else if (pos == n)
            memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq] = 0;
        if (memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq] != -1)
            return memo[pos][remaining][xMinReq][xMaxReq][yMinReq][yMaxReq];
        int xMinR = xMinReq;
        int xMaxR = xMaxReq;
        int yMinR = yMinReq;
        int yMaxR = yMaxReq;
        if (xMinReq > 0 && x[pos] == xMin)
            xMinReq--;
        if (xMaxReq > 0 && x[pos] == xMax)
            xMaxReq--;
        if (yMinReq > 0 && y[pos] == yMin)
            yMinReq--;
        if (yMaxReq > 0 && y[pos] == yMax)
            yMaxReq--;
        memo[pos][remaining][xMinR][xMaxR][yMinR][yMaxR] = ((gen(n, k, x, y, xMin, xMax, yMin, yMax, xMinR, xMaxR, yMinR, yMaxR, pos + 1, remaining) % DIV)
                + (gen(n, k, x, y, xMin, xMax, yMin, yMax, xMinReq, xMaxReq, yMinReq, yMaxReq, 
                        pos + 1, remaining - 1)) % DIV) % DIV;
        return memo[pos][remaining][xMinR][xMaxR][yMinR][yMaxR];
    }
}