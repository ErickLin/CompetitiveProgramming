import java.io.*;
import java.util.*;

class homework2 {
    
    public static void main(String[] args) throws IOException {
        Scanner in2 = new Scanner(new FileReader("primes.in"));
        HashSet<Integer> primes = new HashSet<>();
        ArrayList<Integer> primesArray = new ArrayList<>();
        TreeSet<Integer> primacity2 = new TreeSet<>();
        TreeSet<Integer> primacity3 = new TreeSet<>();
        TreeSet<Integer> primacity4 = new TreeSet<>();
        TreeSet<Integer> primacity5 = new TreeSet<>();
        TreeSet<Integer> primacity6 = new TreeSet<>();
        TreeSet<Integer> primacity7 = new TreeSet<>();
        while (in2.hasNext()) {
            int p = Integer.parseInt(in2.next());
            primes.add(p);
            primesArray.add(p);
        }
        for (int i = 6; i <= 10000000; i++) {
            if (primes.contains(i))
                continue;
            int num = i;
            int primacity = 0;
            loop: for (int p : primesArray) {
                if (num % p == 0) {
                    primacity++;
                    do {
                        num /= p;
                    } while (num % p == 0);
                    if (num == 1) {
                        break loop;
                    }
                }
            }
            if (primacity == 2)
                primacity2.add(i);
            if (primacity == 3)
                primacity3.add(i);
            if (primacity == 4)
                primacity4.add(i);
            if (primacity == 5)
                primacity5.add(i);
            if (primacity == 6)
                primacity6.add(i);
            if (primacity == 7)
                primacity7.add(i);
        }
        PrintWriter out2 = new PrintWriter(new BufferedWriter(new FileWriter("primacity2.out")));
        PrintWriter out3 = new PrintWriter(new BufferedWriter(new FileWriter("primacity3.out")));
        PrintWriter out4 = new PrintWriter(new BufferedWriter(new FileWriter("primacity4.out")));
        PrintWriter out5 = new PrintWriter(new BufferedWriter(new FileWriter("primacity5.out")));
        PrintWriter out6 = new PrintWriter(new BufferedWriter(new FileWriter("primacity6.out")));
        PrintWriter out7 = new PrintWriter(new BufferedWriter(new FileWriter("primacity7.out")));
        for (int p : primacity2)
            out2.println(p);
        for (int p : primacity3)
            out3.println(p);
        for (int p : primacity4)
            out4.println(p);
        for (int p : primacity5)
            out5.println(p);
        for (int p : primacity6)
            out6.println(p);
        for (int p : primacity7)
            out7.println(p);
        in2.close();
        out2.close();
        out3.close();
        out4.close();
        out5.close();
        out6.close();
        out7.close();
        System.exit(0);
    }
}
