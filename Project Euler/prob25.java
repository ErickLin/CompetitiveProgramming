import java.io.*;
import java.math.*;
import java.util.*;

public class prob25 {
    public static void main(String[] args) {
        BigInteger a = BigInteger.valueOf(1);
        BigInteger b = BigInteger.valueOf(1);
        int ind = -1;
        for (int i = 3; ind == -1; i++) {
            BigInteger c = a.add(b);
            if (c.toString().length() >= 1000) {
                ind = i;
            }
            a = b;
            b = c;
        }
        System.out.println(ind);
    }
}