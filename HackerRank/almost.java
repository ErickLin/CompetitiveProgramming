package hackerrank;

import java.util.*;

public class almost {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] array = new int[n];
        for (int i = 0; i < n; i++)
            array[i] = in.nextInt();
        if (!checkSwap(array) && !checkReverse(array))
            System.out.println("no");
    }
    
    public static boolean checkSwap(int[] a) {
        int n = a.length;
        ArrayList<Integer> peaks = new ArrayList<Integer>();
        ArrayList<Integer> troughs = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            if (i < n - 1 && (a[i] > a[i + 1]
                              || (i > 0 && a[i] == a[i + 1] && a[i] > a[i - 1]))) {
                peaks.add(i);
            }
            if (i > 0 && (a[i] < a[i - 1]
                          || (i < n - 1 && a[i] == a[i - 1] && a[i] < a[i + 1]))) {
                troughs.add(i);
            }
        }
        //System.out.println(peaks);
        //System.out.println(troughs);
        //System.out.println(Arrays.toString(a));
        if (peaks.size() > 2 || peaks.isEmpty() || troughs.size() > 2 || troughs.isEmpty())
            return false;
        for (int i = 0; i < peaks.size(); i++) {
            for (int j = 0; j < troughs.size(); j++) {
                int peakInd = peaks.get(i);
                int troughInd = troughs.get(j);
                //swap positions
                int temp = a[peakInd];
                a[peakInd] = a[troughInd];
                a[troughInd] = temp;
                //System.out.println(Arrays.toString(a));
                if (isSorted(a)) {
                    System.out.println("yes");
                    System.out.println("swap " + (Math.min(peakInd, troughInd) + 1) + " "
                                       + (Math.max(peakInd, troughInd) + 1));
                    return true;
                }
                //swap back
                temp = a[peakInd];
                a[peakInd] = a[troughInd];
                a[troughInd] = temp;
            }
        }
        return false;
    }
    
    public static boolean checkReverse(int[] a) {
        int n = a.length;
        int start = -1;
        int end = -1;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                start = i;
                break;
            }
        }
        if (start == -1)
            return false;
        for (int i = start; i < n - 1; i++) {
            if (a[i + 1] > a[i]) {
                end = i;
                break;
            }
        }
        if (end == -1)
            end = n - 1;
        for (int j = start - 1; j >= 0; j--) {
            if (a[j] == a[j + 1]) {
                start = j;
            } else {
                break;
            }
        }
        for (int j = end + 1; j < n; j++) {
            if (a[j] == a[j - 1]) {
                end = j;
            } else {
                break;
            }
        }
        for (int j = end; j < n - 1; j++) {
            if (a[j] > a[j + 1])
                return false;
        }
        if ((start == 0 || a[end] > a[start - 1]) && (end == n - 1 || a[start] < a[end + 1])) {
            System.out.println("yes");
            System.out.println("reverse " + (start + 1) + " " + (end + 1));
            return true;
        }
        return false;
    }
    
    public static boolean isSorted(int[] a) {
        for (int i = 0; i < a.length - 1; i++) {
            if (a[i] > a[i + 1]) {
                return false;
            }
        }
        return true;
    }
}