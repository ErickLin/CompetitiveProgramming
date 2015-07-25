import java.io.*;
import java.util.*;

public class byteland {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(in.readLine());
        for (int i = 0; i < t; i++) {
            String s = in.readLine();
            HashMap<Character, Integer> occurrences = new HashMap<Character, Integer>();
            for (int j = 0; j < s.length(); j++) {
                if (occurrences.containsKey(s.charAt(j)))
                    occurrences.put(s.charAt(j), occurrences.get(s.charAt(j)) + 1);
                else
                    occurrences.put(s.charAt(j), 1);
            }
            int operations = 0;
            for (char c : occurrences.keySet()) {
                operations += Math.abs(c - 'a' + 1 - occurrences.get(c));
            }
            System.out.println(operations);
        }
        in.close();
        System.exit(0);
    }
}
