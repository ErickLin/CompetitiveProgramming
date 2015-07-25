import java.io.*;
import java.math.*;
import java.util.*;

public class prob20 {
    public static void main(String[] args) throws IOException {
        BigInteger a = BigInteger.valueOf(1);
        for (int i = 2; i <= 100; i++) {
            a = a.multiply(BigInteger.valueOf(i));
        }
        String b = a.toString();
        int sum = 0;
        for (int i = 0; i < b.length(); i++) {
            sum += b.charAt(i) - '0';
        }
        System.out.println(sum);
    }
}