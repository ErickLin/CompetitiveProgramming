/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: holstein
*/
import java.io.*;
import java.util.*;

class holstein
{
    static int numVTypes, reqs[], numFTypes, feedTypes[][], minScoops, bestSeq;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("holstein.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("holstein.out")));
        numVTypes = Integer.parseInt(in.readLine());
        reqs = new int[numVTypes];
        StringTokenizer line = new StringTokenizer(in.readLine());
        for (int i = 0; i < numVTypes; i++)
            reqs[i] = Integer.parseInt(line.nextToken());
        numFTypes = Integer.parseInt(in.readLine());
        feedTypes = new int[numFTypes][numVTypes];
        for (int j = 0; j < numFTypes; j++)
        {
            line = new StringTokenizer(in.readLine());
            for (int i = 0; i < numVTypes; i++)
                feedTypes[j][i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        /*for (int i = 0; i < numVTypes; i++)
            System.out.print(reqs[i] + " ");
        System.out.println();
        for (int i = 0; i < numFTypes; i++)
        {
            for (int j = 0; j < numVTypes; j++)
                System.out.print(feedTypes[i][j] + " ");
            System.out.println();
        }*/
        minScoops = numFTypes + 1;
        bestSeq = 0;
        /*int[] cumulative = new int[numVTypes];
        for (int i = 0; i < numVTypes; i++)
            cumulative[i] = 0;
        getBestFeed(cumulative, 0, 0);*/
        //System.out.println(Integer.toBinaryString(bestSeq));
        enumerate(0, 0);
        out.print(minScoops);
        for (int i = 0; i < numFTypes; i++)
            if (((1 << i) & bestSeq) > 0)
                out.print(" " + (i + 1));
        out.println();
        out.close();
        System.exit(0);
    }
    
    public static void enumerate(int pos, int feedsUsed)
    {
        if (pos == numFTypes)
        {
            //System.out.println(Integer.toBinaryString(feedsUsed));
            //remaining vitamins needed
            int[] remaining = new int[numVTypes];
            for (int i = 0; i < numVTypes; i++)
                remaining[i] = new Integer(reqs[i]);
            int scoops = 0;
            for (int i = 0; i < numFTypes; i++)
                if (((1 << i) & feedsUsed) > 0)
                {
                    for (int j = 0; j < numVTypes; j++)
                        remaining[j] -= feedTypes[i][j];
                    scoops++;
                }
            /*for (int i = 0; i < numVTypes; i++)
                System.out.print(remaining[i] + " ");
            System.out.println();*/
            for (int j = 0; j < numVTypes; j++)
                if (remaining[j] > 0)
                    return;
            if (scoops < minScoops)
            {
                minScoops = scoops;
                bestSeq = feedsUsed;
            }
        }
        else
        {
            enumerate(pos + 1, feedsUsed);
            enumerate(pos + 1, feedsUsed | 1 << pos);
        }
    }
    
    /*public static void getBestFeed(int[] cumulative, int feedsUsed, int scoops)
    {
        for (int i = 0; i < numFTypes; i++)
            if (((1 << i) & feedsUsed) == 0)
            {
                feedsUsed |= 1 << i;
                scoops++;
                if (scoops >= minScoops)
                    break;
                //System.out.println("added: " + seq + " " + Integer.toBinaryString(feedsUsed));
                boolean fulfilled = true;
                for (int j = 0; j < numVTypes; j++)
                {
                    cumulative[j] += feedTypes[i][j];
                    //System.out.print(cumulative[j] + " ");
                    if (cumulative[j] < reqs[j])
                        fulfilled = false;
                }
                //System.out.println(fulfilled);
                if (fulfilled == true)
                {
                    if (scoops < minScoops)
                    {
                        minScoops = scoops;
                        bestSeq = feedsUsed;
                    }
                }
                else
                    getBestFeed(cumulative, feedsUsed, scoops);
                //return variables to original values
                feedsUsed ^= 1 << i;
                scoops--;
                for (int j = 0; j < numVTypes; j++)
                    cumulative[j] -= feedTypes[i][j];
                //System.out.println("after: " + seq + " " + Integer.toBinaryString(feedsUsed));
            }
    }*/
}