package fall_10_05_14;

import java.io.*;
import java.util.*;

public class D {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int b;
        while ((b = Integer.parseInt(line.nextToken())) != 0) {
            int n = Integer.parseInt(line.nextToken());
            int A = b;
            int B = -2 * b * n;
            int B2 = (int) (Math.pow(B, 2));
            ArrayList<Fraction> fracs = new ArrayList<Fraction>();
            //the formula is (b)m^2 - (2bn)m + (an^2) = 0
            //bounds: b - a >= 0, so a <= b
            fracs.add(new Fraction(0, 2 * n)); //comes from solving quadratic equation when a = 0
            for (int a = 1; a < b; a++) {
                int C = a * n * n;
                int det = B2 - 4 * A * C;
                //check for integral roots
                if (isPerfectSquare(det) && ((-B + (int) (Math.sqrt(det))) % (2 * A) == 0)) {
                    int m = (-B + (int) (Math.sqrt(det))) / (2 * A);
                    if (m != 0 && m != n)
                        fracs.add(new Fraction(a, m));
                    if (det > 0) {
                        m = (-B - (int) (Math.sqrt(det))) / (2 * A);
                        if (m != 0 && m != n)
                            fracs.add(new Fraction(a, m));
                    }
                }
            }
            Collections.sort(fracs);
            System.out.print(fracs.get(0));
            for (int i = 1; i < fracs.size(); i++) {
                System.out.print(" " + fracs.get(i));
            }
            System.out.println();
            line = new StringTokenizer(in.readLine());
        }
        in.close();
        System.exit(0);
    }
    
    public static boolean isPerfectSquare(int num) {
        int sqrt = (int) Math.sqrt(num);
        return (sqrt * sqrt == num);
    } 
    
    public static class Fraction implements Comparable<Fraction>
    {
        private final int num, denom;
        
        public Fraction(int n, int d)
        {
            num = n;
            denom = d;
        }
        
        @Override
        public int compareTo(Fraction other)
        {
            int c = new Integer(getNum() * other.getDenom()).compareTo(other.getNum() * getDenom());
            if (c == 0)
                c = new Integer(getNum()).compareTo(other.getNum());
            return c;
        }
        
        public int getNum()
        {
            return num;
        }
        
        public int getDenom()
        {
            return denom;
        }
        
        @Override
        public String toString()
        {
            return num + "/" + denom;
        }
    }
}
