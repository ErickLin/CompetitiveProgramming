/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: odometer
*/
import java.io.*;
import java.util.*;

class odometer
{
    public static int[][] combs;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("odometer.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("odometer.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        String n1 = line.nextToken();
        String n2 = line.nextToken();
        in.close();
        combs = new int[19][19];
        for (int i = 0; i < combs.length; i++)
            Arrays.fill(combs[i], -1);
        int shortest = n1.length();
        int longest = n2.length();
        long moos = 0;
        /*if (shortest == longest)
        {
            long num1 = Long.parseLong(n1), num2 = Long.parseLong(n2);
            for (long j = num1; j <= num2; j++)
            {
                String num = Long.toString(j);
                int[] digs = new int[10];
                for (int i = 0; i < num.length(); i++)
                {
                    int dig = Integer.parseInt(num.substring(i, i + 1));
                    digs[dig]++;
                    if (digs[dig] >= (shortest + 1) / 2)
                    {
                        moos++;
                        break;
                    }
                }
            }
        }*/
        for (int len = shortest; len <= longest; len++)
            for (int dig = 0; dig <= 9; dig++)
            {
                int places = len, req = (len + 1)/2;
                if (len == shortest)
                    for (int i = 0; i < shortest; i++)
                        if (dig < Integer.parseInt(n1.substring(i, i + 1)))
                            places--;
                if (len == longest)
                    for (int i = 0; i < longest; i++)
                        if (dig > Integer.parseInt(n2.substring(i, i + 1)))
                            places--;
                //remaining places
                int rem = places - req;
                System.out.println(places + " " + req + " " + rem);
                //does not include leading digit
                int mult = 9 + (rem - 1) * 10;
                if (len == shortest);
                moos += combinations(places - 1, req) * mult;
                //includes leading digit
                mult = rem * 10;
                if (len == longest);
                if (dig > 0)
                    moos += combinations(places - 1, req - 1) * mult;
            }
        out.println(moos);
        out.close();
        System.exit(0);
    }
    
    public static int combinations(int n, int k)
    {
        if (n < k)
            return 0;
        if (combs[n][k] != -1)
            return combs[n][k];
        if (k > n / 2)
            k = n - k;
        double comb = 1.0;
        if (k == 1)
            comb = n;
        else if (k != 0)
        {
            ArrayList<Integer> numerator = new ArrayList<Integer>(k);
            ArrayList<Integer> denominator = new ArrayList<Integer>(k - 1);
            for (int i = 0; i < k; i++)
                numerator.add(n - i);
            loop: for (int i = 2; i <= k; i++)
            {
                for (int j = 0; j < numerator.size(); j++)
                    //cancel out terms
                    if (numerator.get(j) % i == 0)
                    {
                        if (numerator.get(j).equals(i))
                            numerator.remove(j);
                        else
                            numerator.set(j, numerator.get(j) / i);
                        continue loop;
                    }
                denominator.add(i);
            }
            //terms in numerator outnumber those in denominator
            for (int i = 0; i < denominator.size(); i++)
            {
                comb *= numerator.get(numerator.size() - 1 - i);
                comb /= denominator.get(i);
            }
            for (int j = numerator.size() - 1 - denominator.size(); j >= 0; j--)
                comb *= numerator.get(j);
            comb = (int)Math.round(comb);
            if (comb < 1.0)
                comb = 1.0;
        }
        combs[n][k] = (int)comb;
        combs[n][n - k] = (int)comb;
        return (int)comb;
    }
}