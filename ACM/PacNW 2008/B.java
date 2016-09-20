import java.io.*;
import java.lang.*;
import java.util.*;

public class B {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int j = 1; j <= t; j++) {
            int n = Integer.parseInt(in.readLine());
            ArrayList<String> names = new ArrayList<>(n);
            for (int i = 0; i < n; i++) {
                names.add(in.readLine());
            }
            int d = Integer.parseInt(in.readLine());
            ArrayList<String> data = new ArrayList<>();
            for (int i = 0; i < d; i++) {
                StringTokenizer line = new StringTokenizer(in.readLine());
                while (line.hasMoreTokens()) {
                    data.add(line.nextToken());
                }
            }
            System.out.println("Test set " + j + ":");
            for (int i = 0; i < n; i++) {
                System.out.println(names.get(i) + " is " + (data.contains(names.get(i)) ? "present" : "absent"));
            }
            if (j < t) {
                System.out.println();
            }
        }
    }
}
