/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: humble
*/

import java.io.*;
import java.util.*;

class humbleOld {
    static HashSet<Long> memo = new HashSet<Long>();
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("humble.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("humble.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int k = Integer.parseInt(line.nextToken());
        int n = Integer.parseInt(line.nextToken());
        int[] primes = new int[k];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < k; i++)
            primes[i] = Integer.parseInt(line.nextToken());
        in.close();
        int maxC = n / k;
        int maxNum = (int)Math.pow(2, 31);
        for (int i = 0; i < k; i++) {
            gen(k, primes, i, primes[i], 1, maxNum, maxC);
        }
        //System.out.println(memo);
        ArrayList<Long> humbleNums = new ArrayList<Long>(memo);
        Collections.sort(humbleNums);
        //System.out.println(humbleNums);
        //System.out.println(humbleNums.size());
        out.println(humbleNums.get(n - 1));
        out.close();
        System.exit(0);
    }
    
    //i = index of prime, num = number, c = current factor
    public static void gen(int k, int[] primes, int i, long num, int c, int maxNum, int maxC) {
        if (num > 0 && num < maxNum && c <= maxC && !memo.contains(num)) {
            //System.out.println(num);
            memo.add(num);
            for (int j = i; j < k; j++) {
                gen(k, primes, j, num * primes[j], c + 1, maxNum, maxC);
            }
        }
    }
}
