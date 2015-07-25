/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ariprog
*/
import java.io.*;
import java.util.*;

class ariprog
{
    static int maxNum;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("ariprog.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ariprog.out")));
        int len = Integer.parseInt(in.readLine());
        int bound = Integer.parseInt(in.readLine());
        in.close();
        maxNum = 2 * bound * bound;
        boolean[] bisquares = new boolean[maxNum + 1];
        for (int p = 0; p <= bound; p++)
            for (int q = 0; q <= bound; q++)
                bisquares[p*p + q*q] = true;
        ArrayList<AriProg> solutions = new ArrayList<AriProg>(10000);
        for (int diff = 1; diff <= maxNum / (len - 1); diff++)
            solLoop: for (int start = 0; start < maxNum; start++)
            {
                for (int i = 0; i < len; i++)
                {
                    if (start + i * diff > maxNum)
                        break solLoop;
                    if (!bisquares[start + i * diff])
                        continue solLoop;
                }
                solutions.add(new AriProg(start, diff));
            }
        if (solutions.size() > 0)
        {
            for (int i = 0; i < solutions.size(); i++)
                out.println(solutions.get(i));
        }
        else
            out.println("NONE");
        out.close();
        System.exit(0);
    }
    
    public static class AriProg
    {
        private int start, diff;
        
        public AriProg(int a, int d)
        {
            start = a;
            diff = d;
        }
        
        @Override
        public String toString()
        {
            return Integer.toString(start) + " " + Integer.toString(diff);
        }
    }
}