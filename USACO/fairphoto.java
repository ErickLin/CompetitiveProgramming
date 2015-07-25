/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fairphoto
*/
import java.io.*;
import java.util.*;

class fairphoto
{
    static int maxN = 100000;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("fairphoto.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fairphoto.out")));
        int n = Integer.parseInt(in.readLine());
        ArrayList<Cow> cows = new ArrayList<Cow>(n);
        int numS = 0, maxPos = 0;
        for (int i = 0; i < n; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(line.nextToken());
            if (x > maxPos)
                maxPos = x;
            boolean s;
            String kind = line.nextToken();
            if (kind.equals("S"))
            {
                s = true;
                numS++;
            }
            else
                s = false;
            cows.add(new Cow(x, s));
        }
        in.close();
        Collections.sort(cows);
        /*for (int x = 1, i = 0; x <= maxPos; x++)
        {
            if (cows.get(i).pos == x)
            {
                if (cows.get(i).spotted)
                    System.out.print("S");
                else
                    System.out.print("W");
                i++;
            }
            else
                System.out.print("*");
        }
        System.out.println();*/
        int maxSize = 0, numW = n - numS;
        //if the white cows outnumber the spotted cows by an even number
        if (numW >= numS && (numW - numS) % 2 == 0)
            maxSize = cows.get(n - 1).pos - cows.get(0).pos;
        else for (int l = 0; l < n; l++)
        {
            //difference between number of white and number of spotted cows
            int diff = 0;
            for (int r = l; r < n; r++)
            {
                if (cows.get(r).spotted)
                    diff--;
                else
                    diff++;
                if (diff > 0 && diff % 2 == 0 && cows.get(r).pos - cows.get(l).pos > maxSize)
                    maxSize = cows.get(r).pos - cows.get(l).pos;
            }
            /*numS = 0;
            numW = 0;
            int left = 0, right = 1;
            //whether the cow on the left end of the range is spotted
            boolean ls = cows.get(left).spotted;
            if (ls)
                numS++;
            else
                numW++;
            while (right < n)
            {
                boolean rs = cows.get(right).spotted;
                if (rs)
                    numS++;
                else
                    numW++;
                while (numS > numW)
                {
                    if (ls)
                        numS--;
                    else
                        numW--;
                    left++;
                    ls = cows.get(left).spotted;
                }
                if ((numW - numS) % 2 == 0 && cows.get(right).pos - cows.get(left).pos > maxSize)
                    maxSize = cows.get(right).pos - cows.get(left).pos;
                right++;
            }*/
        }
        out.println(maxSize);
        out.close();
        System.exit(0);
    }
    
    public static class Cow implements Comparable<Cow>
    {
        int pos;
        boolean spotted;
        
        public Cow(int x, boolean s)
        {
            pos = x;
            spotted = s;
        }
        
        @Override
        public int compareTo(Cow other)
        {
            return new Integer(pos).compareTo(other.pos);
        }
    }
}