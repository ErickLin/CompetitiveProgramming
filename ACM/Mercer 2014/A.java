import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class prob1 {
	public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String n;
        while (!(n = in.readLine()).equals("0")) {
        	BigInteger f = new BigInteger(n.substring(0, 1));
        	for (int i = 1; i < n.length(); i++) {
        		f = f.add(BigInteger.valueOf((int) Math.pow(Long.parseLong(n.substring(i, i + 1)), i + 1)));
        	}
        	if (f.toString().equals(n)) {
        		System.out.println(n + " is a powerful number.");
        	} else {
        		System.out.println(n + " is not a powerful number.");
        	}
        }
	}
}