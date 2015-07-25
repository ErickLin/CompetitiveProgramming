import java.io.*;
import java.util.*;

public class makecheck {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        HashSet<Long> make = new HashSet<>();
        StringTokenizer line = new StringTokenizer(in.readLine());
        while (line.hasMoreTokens()) {
            make.add(Long.parseLong(line.nextToken()));
        }
        HashSet<Long> check = new HashSet<>();
        line = new StringTokenizer(in.readLine());
        while (line.hasMoreTokens()) {
            check.add(Long.parseLong(line.nextToken()));
        }
        in.close();
        boolean tally1 = true, tally2 = true;
        for (long cheque : check) {
            if (!make.contains(cheque)) {
                if (tally1) {
                    tally1 = false;
                    System.out.print("Maker :");
                }
                System.out.print(" " + cheque);
            }
        }
        if (!tally1)
            System.out.println();
        for (long cheque : make) {
            if (!check.contains(cheque)) {
                if (tally2) {
                    tally2 = false;
                    System.out.print("Checker :");
                }
                System.out.print(" " + cheque);
            }
        }
        if (!tally2)
            System.out.println();
        if (tally1 && tally2)
            System.out.println("Amounts Tally");
    }
}