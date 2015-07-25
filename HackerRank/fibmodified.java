import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        BigInteger a = new BigInteger(line.nextToken());
        BigInteger b = new BigInteger(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        for (int i = 2; i < n; i++) {
            BigInteger c = a.add(b.multiply(b));
            a = b;
            b = c;
        }
        System.out.println(b);
    }
}