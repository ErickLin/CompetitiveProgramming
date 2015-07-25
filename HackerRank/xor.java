package hackerrank;

import java.util.*;

public class xor {
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] series = new int[n];
        int highest = 0;
        for (int i = 0; i < n; i++) {
            series[i] = sc.nextInt();
            if (series[i] > highest)
                highest = series[i];
        }
        HashMap<Integer, Integer> freqs = new HashMap<Integer, Integer>();
        int freq = 0;
        for (int i = 0; i < n; i++) {
            int xor = series[i];
            if (freqs.containsKey(xor))
                freqs.put(xor, freqs.get(xor) + 1);
            else
                freqs.put(xor, 1);
            for (int j = i + 1; j < n; j++) {
                xor ^= series[j];
                if (freqs.containsKey(xor))
                    freqs.put(xor, freqs.get(xor) + 1);
                else
                    freqs.put(xor, 1);
            }
        }
        int num = 0;
        int max = 0;
        for (Map.Entry<Integer, Integer> entry : freqs.entrySet()) {
            if (entry.getValue() > max) {
                max = entry.getValue();
                num = entry.getKey();
            }
            else if (entry.getValue() == max && entry.getKey() < num) {
                num = entry.getKey();
            }
        }
        System.out.println(num + " " + max);
    }
    
    //public static int getXor(int series, int start, int end) {
    //    
    //}
}