import java.util.*;
import java.math.*;
import java.io.*;

public class prob16 {
    public static void main(String[] args) throws IOException {
        BigInteger a = new BigInteger("1");
        for (int i = 1; i <= 1000; i++) {
            a = a.multiply(new BigInteger("2"));
        }
        String s = a.toString();
        long ans = 0;
        for (int i = 0; i < s.length(); i++) {
            ans += s.charAt(i) - '0';
        }
        System.out.println(ans);
    }
}