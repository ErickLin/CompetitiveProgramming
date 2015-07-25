/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: money
*/
import java.io.*;
import java.util.*;

class money
{
    static int numValues, total, values[];
    static long ways[];
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("money.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("money.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        numValues = Integer.parseInt(line.nextToken());
        total = Integer.parseInt(line.nextToken());
        values = new int[numValues];
        //stores number of ways to add up money equal to index value
        ways = new long[total + 1];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < numValues; i++)
        {
            if (!line.hasMoreTokens())
                line = new StringTokenizer(in.readLine());
            values[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        Arrays.sort(values);
        //count(0, 0);
        ways[0] = 1;
        for (int i = 0; i < values.length; i++)
            for (int amt = values[i]; amt <= total; amt++)
                ways[amt] += ways[amt - values[i]];
        out.println(ways[total]);
        /*for (int i = 1; i <= total; i++)
            System.out.println(ways[i]);*/
        out.close();
        System.exit(0);
    }
    
    /*
    public static void count(int amt, int currentIndex)
    {
        for (int i = currentIndex; i < numValues; i++)
        {
            if (amt + values[i] > total)
                break;
            ways[amt + values[i]]++;
            if (amt + values[i] < total)
                count(amt + values[i], i);
        }
    }
    */
}