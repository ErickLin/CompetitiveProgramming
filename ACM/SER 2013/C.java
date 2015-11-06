import java.io.*;
import java.util.*;

public class C {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String input;
        while (!(input = in.readLine()).equals("0")) {
            int n = input.length();
            boolean[] isSatelliteInterval = new boolean[1000];
            int numSatellites = 0;
            for (int i = 1; i < n; i++) {
                int numPingsExpected = 0;
                for (int j = 1; j <= i / 2; j++) {
                    if (isSatelliteInterval[j] && i % j == 0) {
                        numPingsExpected++;
                    }
                }
                int expected = (numPingsExpected == 0 || numPingsExpected % 2 == 0) ? 0 : 1;
                if (Integer.parseInt(input.substring(i, i + 1)) != expected) {
                    isSatelliteInterval[i] = true;
                    numSatellites++;
                    if (numSatellites >= 2)
                        System.out.print(" ");
                    System.out.print(i);
                }
            }
            System.out.println();
        }
        in.close();
        System.exit(0);
    }
}
