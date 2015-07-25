/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: nuggets
*/

import java.io.*;
import java.util.*;

class nuggets {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("nuggets.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nuggets.out")));
        int n = Integer.parseInt(in.readLine());
        ArrayList<Integer> options = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            int option = Integer.parseInt(in.readLine());
            boolean add = true;
            for (int other : options)
                if (option % other == 0 || other % option == 0) {
                    add = false;
                    break;
                }
            if (add)
                options.add(option);
        }
        in.close();
        if (gcd(options) > 1)
            out.println("0");
        else {
            int largest = 0;
            TreeSet<Integer> canReach = new TreeSet<Integer>();
            int smallestOption = Integer.MAX_VALUE;
            int count = 0;
            for (int i = 0; i < options.size(); i++) {
                canReach.add(options.get(i));
                smallestOption = Math.min(smallestOption, options.get(i));
            }
            for (int size = 1; size <= 2000000000; size++) {
                if (canReach.contains(size)) {
                    for (int i = 0; i < options.size(); i++) {
                        if (canReach.size() > 256)
                            canReach.pollFirst();
                        canReach.add(size + options.get(i));
                    }
                    count++;
                    if (count >= smallestOption)
                        break;
                } else {
                    largest = size;
                    count = 0;
                }
            }
            out.println(largest);
        }
        out.close();
        System.exit(0);
    }

    public static int gcd(ArrayList<Integer> list) {
        int ret = list.get(0);
        for (int i = 1; i < list.size(); i++) {
            ret = gcd(ret, list.get(i));
        }
        return ret;
    }

    public static int gcd(int k, int m) {
        while (k != m) {
            if (k > m) {
                k -= m;
            } else {
                m -= k;
            }
        }
        return k;
    }
}
