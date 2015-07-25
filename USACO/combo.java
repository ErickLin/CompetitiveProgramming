/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: combo
*/
import java.io.*;
import java.util.*;

class combo {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("combo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("combo.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int[][] keys = new int[2][3];
        for (int i = 0; i < 2; i++) {
            line = new StringTokenizer(in.readLine());
            for (int j = 0; j < 3; j++) {
                keys[i][j] = Integer.parseInt(line.nextToken());
            }
        }
        in.close();
        int combsInter = 1;
        for (int j = 0; j < 3; j++) {
            combsInter *= intersection(n, keys, j);
        }
        out.println((int) Math.pow(Math.min(n, 5), 3) * 2 - combsInter);
        out.close();
        System.exit(0);
    }
    
    public static int intersection(int n, int[][] keys, int ind) {
        int key1 = keys[0][ind];
        int key2 = keys[1][ind];
        HashSet<Integer> set1 = new HashSet<Integer>();
        set1.add((key1 - 2 + n) % n);
        set1.add((key1 - 1 + n) % n);
        set1.add(key1);
        set1.add((key1 + 1 + n) % n);
        set1.add((key1 + 2 + n) % n);
        if (set1.contains(0)) {
            set1.remove(0);
            set1.add(n);
        }
        HashSet<Integer> set2 = new HashSet<Integer>();
        set2.add((key2 - 2 + n) % n);
        set2.add((key2 - 1 + n) % n);
        set2.add(key2);
        set2.add((key2 + 1 + n) % n);
        set2.add((key2 + 2 + n) % n);
        if (set2.contains(0)) {
            set2.remove(0);
            set2.add(n);
        }
        System.out.println(set1);
        System.out.println(set2);
        //intersection of two sets
        set1.retainAll(set2);
        System.out.println(set1.size());
        return set1.size();
        /*
        if (key2 - key1 > n / 2)
            key2 -= n / 2;
        else if (key1 - key2 > n / 2)
            key1 -= n / 2;
        return (int) Math.max(Math.min(n, 5) - Math.abs(key2 - key1), 0);
        */
    }
}