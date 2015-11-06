package Fall_09_21_14;

/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: A
*/

import java.io.*;
import java.util.*;

class A {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int input = 1;
        int needed;
        StringTokenizer line = new StringTokenizer(in.readLine());
        while ((needed = Integer.parseInt(line.nextToken()) + 1) > 0) {
            int score = 0;
            int[] rolls = new int[21];
            boolean[] on2 = new boolean[21];
            int[] bonus = new int[21];
            int roll = 0;
            for (roll = 0; ; roll++) {
                if (!line.hasMoreTokens())
                {
                    line = new StringTokenizer(in.readLine());
                    if (!line.hasMoreTokens())
                        break;
                }
                rolls[roll] = Integer.parseInt(line.nextToken());
                score += rolls[roll];
                if (rolls[roll] != 10)
                    on2[roll + 1] = !on2[roll];
            }
            for (int i = 0; i < roll; i++) {
                if (rolls[i] == 10) {
                    bonus[i + 1]++;
                    bonus[i + 2]++;
                }
                if (i > 0 && on2[i] && rolls[i] + rolls[i - 1] == 10)
                    bonus[i + 1]++;
            }
            for (int i = 0; i < roll; i++)
                score += rolls[i] * bonus[i];
            System.out.println(score + " " + bonus[roll] + " " + bonus[roll + 1]);
            System.out.println("Case" + input + ": " + output(needed - score, bonus[roll], bonus[roll + 1]));
            input++;
            line = new StringTokenizer(in.readLine());
            /*
            for (int i = 0; i < 8; i++)
                System.out.println(Arrays.toString(rolls[i]));
            */
        }
        in.close();
        System.exit(0);
    }
    
    static ArrayList<String> memos;
    
    /*
    input:
        remaining - score needed in last two frames
        
    */
    public static String output(int remaining, int bonus1, int bonus2) {
        memos = new ArrayList<String>();
        int[] bonus = new int[5];
        bonus[0] = bonus1;
        bonus[1] = bonus2;
        if (60 + (bonus1 + bonus2) * 10 < remaining)
            return "impossible";
        else if (remaining < 10)
            return "0 0 0 " + remaining;
        else {
            gen9(remaining, new int[5], bonus, 0);
            Collections.sort(memos);
            return memos.get(0);
        }
    }
    
    public static void gen9(int remaining, int[] rolls, int[] bonus, int roll) {
        int[] newRolls = new int[5];
        int[] newBonus = new int[5];
        System.arraycopy(rolls, 0, newRolls, 0, 5);
        System.arraycopy(bonus, 0, newBonus, 0, 5);
        for (int i = 0; i <= 10; i++) {
            newRolls[roll] = i;
            if (i == 10) {
                newBonus[1]++;
                newBonus[2]++;
                gen10(remaining, newRolls, newBonus, roll + 1);
            }
            else {
                roll++;
                for (int j = 0; j <= 10 - i; j++) {
                    newRolls[roll] = j;
                    if (i + j == 10)
                        newBonus[2]++;
                    gen10(remaining, newRolls, newBonus, roll + 2);
                }
            }
        }
    }
    
    public static void gen10(int remaining, int[] rolls, int[] bonus, int roll) {
        int[] newRolls = new int[5];
        int[] newBonus = new int[5];
        System.arraycopy(rolls, 0, newRolls, 0, 5);
        System.arraycopy(bonus, 0, newBonus, 0, 5);
        boolean extra = false;
        for (int i = 0; i <= 10; i++) {
            newRolls[roll] = i;
            if (i == 10) {
                for (int j = 0; j <= 10; j++) {
                    newRolls[roll + 1] = j;
                    if (j == 10) {
                        for (int k = 0; k <= 10; k++) {
                            newRolls[roll + 2] = k;
                            extra = true;
                            memoize(remaining, newRolls, newBonus, extra);
                        }
                    } else {
                        for (int k = 0; k <= 10 - j; j++) {
                            newRolls[roll + 2] = k;
                            extra = true;
                            memoize(remaining, newRolls, newBonus, extra);
                        }
                    }
                }
            } else {
                for (int j = 0; j <= 10 - i; j++) {
                    newRolls[roll + 1] = j;
                    if (i + j == 10) {
                        for (int k = 0; k <= 10; k++) {
                            newRolls[roll + 2] = k;
                            extra = true;
                            memoize(remaining, newRolls, newBonus, extra);
                        }
                    } else {
                        memoize(remaining, newRolls, newBonus, extra);
                    }
                }
            }
        }
    }
    
    public static void memoize(int remaining, int[] rolls, int[] bonus, boolean extra) {
        int score = 0;
        int numRolls = 4;
        if (extra)
            numRolls++;
        for (int j = 0; j < numRolls; j++)
            score += rolls[j] * bonus[j];
        if (score >= remaining) {
            StringBuilder str = new StringBuilder(rolls[0]);
            for (int j = 1; j < numRolls; j++) {
                str.append(" ");
                str.append(rolls[j]);
                memos.add(str.toString());
            }
        }
    }
}