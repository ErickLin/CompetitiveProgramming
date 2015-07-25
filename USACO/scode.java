/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: scode
*/
import java.io.*;
import java.util.*;

class scode
{
    static String msg;
    static HashMap<String, Integer> numWays;
    static int totalWays;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("scode.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("scode.out")));
        msg = in.readLine();
        in.close();
        totalWays = 0;
        numWays = new HashMap<String, Integer>();
        numWays.put(msg, 0);
        for (int len = msg.length() - 1; len >= 2; len--)
        {
            ArrayList<String> unique = new ArrayList<String>(msg.length() - len);
            for (int i = 0; i + len <= msg.length(); i++)
            {
                String part = msg.substring(i, i + len);
                if (!unique.contains(part))
                {
                    //System.out.println("new word: " + part);
                    unique.add(part);
                    totalWays += (countWays(part) % 2014);
                    if (totalWays > 2014)
                        totalWays %= 2014;
                    //System.out.println(part + " " + countWays(part));
                }
            }
        }
        out.println(totalWays);
        out.close();
        System.exit(0);
    }
    
    public static int countWays(String part)
    {
        if (part.equals(msg))
        {
            //System.out.print(part + ": ");
            //System.out.println("1 count: 1");
            return 1;
        }
        if (part.length() >= msg.length() || !msg.contains(part))
            return 0;
        if (numWays.containsKey(part))
        {
            //System.out.print(part + ": ");
            //System.out.println("2 count: " + numWays.get(part));
            return numWays.get(part);
        }
        int count = 0;
        for (int i = 1; i < part.length() && part.length() + i <= msg.length(); i++)
        {
            String op1 = part + part.substring(0, i);
            String op2 = part.substring(0, i) + part;
            String op3 = part + part.substring(part.length() - i, part.length());
            String op4 = part.substring(part.length() - i, part.length()) + part;
            count += (countWays(op1) % 2014 + countWays(op2) % 2014 + countWays(op3) % 2014 + countWays(op4) % 2014) % 2014;
            numWays.put(part, count);
            //System.out.print(part + ": ");
            //System.out.print("3 count: " + count + " | ");
            //System.out.println(op1 + " " + op2 + " " + op3 + " " + op4);
        }
        return count;
    }
}