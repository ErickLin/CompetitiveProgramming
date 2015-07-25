/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: cowrow
*/
import java.io.*;
import java.util.*;

class cowrow
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("cowrow.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowrow.out")));
        int numCows = Integer.parseInt(in.readLine());
        ArrayList<Integer> cows = new ArrayList<Integer>();
        for (int i = 0; i < numCows; i++)
            cows.add(Integer.parseInt(in.readLine()));
        in.close();
        ArrayList<Integer> ids = new ArrayList<Integer>();
        for (int i = 0; i < numCows; i++)
            if (!ids.contains(cows.get(i)))
                ids.add(cows.get(i));
        int max = 1;
        for (int j = 0; j < ids.size(); j++)
        {
            ArrayList<Integer> subset = new ArrayList<Integer>();
            for (int i = 0; i < numCows; i++)
                if (!cows.get(i).equals(ids.get(j)))
                    subset.add(new Integer(cows.get(i)));
            /*System.out.println(ids.get(j));
            for (int i = 0; i < subset.size(); i++)
                System.out.print(subset.get(i) + " ");
            System.out.println();*/
            int localMax = 1;
            for (int i = 1; i < subset.size(); i++)
            {
                if (subset.get(i).equals(subset.get(i - 1)))
                {
                    //System.out.println(subset.get(i) + " " + subset.get(i - 1));
                    localMax++;
                    if (localMax > max)
                        max = localMax;
                }
                else
                    localMax = 1;
            }
        }
        out.println(max);
        out.close();
        System.exit(0);
    }
}