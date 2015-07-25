package hackerrank;

import java.io.*;
import java.util.*;

public class polar {

    static int MAX = 99999999;
    
    public static void main(String[] args) throws IOException{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        //int n = 10000;
        int n = Integer.parseInt(in.readLine());
        int[][] pts = new int[n][2];
        //final double[] thetas = new double[n];
        //final double[] mags = new double[n];
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            //pts[i][0] = -100 + (int) (Math.random() * 200);
            //pts[i][1] = -100 + (int) (Math.random() * 200);
            pts[i][0] = Integer.parseInt(line.nextToken());
            pts[i][1] = Integer.parseInt(line.nextToken());
            //mags[i] = Math.sqrt(Math.pow(pts[i][0], 2) + Math.pow(pts[i][1], 2));
            //dot product
            //thetas[i] = Math.acos(pts[i][0] / mags[i]);
            //if (pts[i][1] < 0)
            //    thetas[i] = 2 * Math.PI - thetas[i];
            //System.out.println(thetas[i]);
        }
        Arrays.sort(pts, new Comparator<int[]>() {
            public int compare(int[] a, int[] b) {
                int quad1 = 0;
                int quad2 = 0;
                if (a[0] > 0 && a[1] >= 0)
                    quad1 = 1;
                if (b[0] > 0 && b[1] >= 0)
                    quad2 = 1;
                if (a[0] <= 0 && a[1] > 0)
                    quad1 = 2;
                if (b[0] <= 0 && b[1] > 0)
                    quad2 = 2;
                if (a[0] < 0 && a[1] <= 0)
                    quad1 = 3;
                if (b[0] < 0 && b[1] <= 0)
                    quad2 = 3;
                if (a[0] >= 0 && a[1] < 0)
                    quad1 = 4;
                if (b[0] >= 0 && b[1] < 0)
                    quad2 = 4;
                int c = Integer.compare(quad1, quad2);
                if (c == 0) {
                    double atan1;
                    double atan2;
                    if (a[0] == 0) {
                        atan1 = -MAX;
                    } else
                        atan1 = ((double) a[1]) / a[0];
                    if (b[0] == 0) {
                        atan2 = -MAX;
                    } else
                        atan2 = ((double) b[1]) / b[0];
                    c = Double.compare(atan1, atan2);
                }
                if (c == 0) {
                    int mag1 = a[0] * a[0] + a[1] * a[1];
                    int mag2 = b[0] * b[0] + b[1] * b[1];
                    c = Integer.compare(mag1, mag2);
                }
                return c;
                /*
                double mag1 = Math.sqrt(Math.pow(a[0], 2) + Math.pow(a[1], 2));
                double mag2 = Math.sqrt(Math.pow(b[0], 2) + Math.pow(b[1], 2));
                //dot product
                double theta1 = Math.acos(a[0] / mag1);
                if (a[1] < 0)
                    theta1 = 2 * Math.PI - theta1;
                double theta2 = Math.acos(b[0] / mag2);
                if (b[1] < 0)
                    theta2 = 2 * Math.PI - theta2;
                if (Double.compare(theta1, theta2) == 0)
                    return Double.compare(mag1, mag2);
                else
                    return Double.compare(theta1, theta2);
                */
            }
        });
        for (int i = 0; i < n; i++)
            System.out.println(pts[i][0] + " " + pts[i][1]);
    }
}