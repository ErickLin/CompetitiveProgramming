import java.io.*;
import java.util.*;

public class anagrams {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            String s = in.readLine();
            HashMap<String, Long> occurrences = new HashMap<String, Long>();
            for (int j = 0; j < s.length(); j++) {
                for (int k = j + 1; k <= s.length(); k++) {
                    char[] temp = s.substring(j, k).toCharArray();
                    Arrays.sort(temp);
                    String substr = String.valueOf(temp);
                    if (occurrences.containsKey(substr)) {
                        occurrences.put(substr, occurrences.get(substr) + 1);
                    } else {
                        occurrences.put(substr, new Long(1));
                    }
                }
            }
            long count = 0;
            for (String substring : occurrences.keySet()) {
                if (occurrences.get(substring) >= 2)
                    count += comb(occurrences.get(substring), 2);
            }
            System.out.println(count);
        }
        in.close();
        System.exit(0);
    }
    
    public static long comb(long n, long k) {
        long ret = 1;
        for (int i = 0; i < k; i++) {
            ret *= (n - i);
            ret /= (i + 1);
        }
        return ret;
    }
}
