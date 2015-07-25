import java.io.*;
import java.util.*;

public class insanedfs {
    static int mod = 1000000007;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer line = new StringTokenizer(in.readLine());
        int[] order = new int[n];
        for (int i = 0; i < n; i++) {
            String s = line.nextToken();
            if (s.equals("?"))
                order[i] = -1;
            else
                order[i] = Integer.parseInt(s);
        }
        in.close();
        if (order[0] > 0) {
            System.out.println("0");
        } else {
            boolean possible = true;
            int currentMaxLvl = 0;
            for (int i = 0; i < n; i++) {
                if ((order[i] != -1 && order[i] > currentMaxLvl)
                        || (i > 0 && order[i] == 0)) {
                    possible = false;
                    break;
                } else {
                    if (order[i] != -1 && currentMaxLvl > order[i])
                        currentMaxLvl = order[i];
                    currentMaxLvl++;
                }
            }
            if (possible) {
                long numSuitable = 1;
                int streak = 0;
                int maxStartingDigit = 1;
                for (int i = 1; i < n; i++) {
                    if (order[i] == -1) {
                        streak++;
                    } else {
                        if (streak > 0) {
                            //Take streak of "?" into account, as well as the minimum
                            //value for the last digit in the streak
                            numSuitable *= possibilities(streak, Math.max(order[i] - 1, 1), maxStartingDigit);
                            numSuitable %= mod;
                            streak = 0;
                            maxStartingDigit = order[i] + 1;
                        }
                    }
                }
                if (streak > 0) {
                    numSuitable *= possibilities(streak, 1, maxStartingDigit);
                    numSuitable %= mod;
                }
                System.out.println(numSuitable);
            } else
                System.out.println("0");
        }
        System.exit(0);
    }
    
    public static long possibilities(int streak, int minLastDigit, int maxStartingDigit) {
        long ret = pow2(streak - 1);
        //This part is wrong!
        if (minLastDigit >= 2) {
            ret -= pow2(minLastDigit - 2);
            if (ret < 0)
                ret += mod;
        }
        for (int i = 2; i <= maxStartingDigit; i++) {
            ret = (ret * 2) % mod;
            ret = (ret + possibilities(Math.max(streak - i + 1, 1), Math.max(minLastDigit - i + 1, 1), 1)) % mod;
        }
        return ret;
    }
    
    public static long pow2(int power) {
        long ret = 1;
        while (power > 10) {
            ret *= (int) Math.pow(2, 10);
            ret %= mod;
            power -= 10;
        }
        ret *= (int) Math.pow(2, power);
        ret %= mod;
        return ret;
    }
}
