/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: mooomoo
*/
import java.io.*;
import java.util.*;

class mooomoo
{
    static ArrayList<Integer> vols;
    static int[] bVols, moos;
    static final int MAX = 99999999;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("mooomoo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mooomoo.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        //number of fields
        int nF = Integer.parseInt(line.nextToken());
        //number of breeds
        int nB = Integer.parseInt(line.nextToken());
        //volumes
        bVols = new int[nB];
        //int[] fVols = new int[nF];
        //stores possible volume values
        vols = new ArrayList<Integer>(100001);
        //stores minimum number of cows required for a certain volume
        moos = new int[100001];
        for (int vol = 1; vol <= 100000; vol++)
            moos[vol] = MAX;
        for (int i = 0; i < nB; i++)
        {
            //set breed i's volume
            bVols[i] = Integer.parseInt(in.readLine());
            vols.add(bVols[i]);
            moos[bVols[i]] = 1;
            /*//multiply volume
            for (int x = 1; bVols[i] * x < 100000; x++)
            {
                int thisVol = bVols[i] * x;
                //number of cows needed for this volume is equal to the multiplier
                moos[thisVol] = x;
                if (!vols.contains(thisVol))
                    vols.add(thisVol);
                for (int j = 0; j < vols.size(); j++)
                {
                    //combined volume of current breed and all other breeds
                    int totalVol = thisVol + vols.get(j);
                    if (totalVol > 100000)
                        break;
                    //number of cows to make the total volume
                    int numMoos = x + moos[vols.get(j)];
                    if (vols.contains(totalVol))
                    {
                        if (numMoos < moos[totalVol])
                            moos[totalVol] = numMoos;
                    }
                    if (!vols.contains(totalVol))
                    {
                        vols.add(totalVol);
                        moos[totalVol] = numMoos;
                    }
                }
            }*/
        }
        Arrays.sort(bVols);
        for (int vol = 1; vol <= 100000; vol++)
            for (int i = 0; i < nB; i++)
                if (bVols[i] <= vol && moos[vol - bVols[i]] + 1 < moos[vol])
                    moos[vol] = moos[vol - bVols[i]] + 1;
        //boolean hasCows[] = new boolean[nF];
        int minCows = 0;
        //the volume of the previous field
        int prevVol = 0;
        for (int i = 0; i < nF; i++)
        {
            //System.out.println(minCows);
            //the volume of the current field
            int thisVol = Integer.parseInt(in.readLine());
            //volume difference between previous and current field
            int dVol = thisVol;
            if (i == 0 && thisVol > 0)
                dVol = thisVol;
            //if the volume increases from the last field to this field
            else if (i > 0 && thisVol >= prevVol)
            {
                if (prevVol > 0)
                    dVol = thisVol - (prevVol - 1);
            }
            else
            {
                prevVol = thisVol;
                continue;
            }
            if (moos[dVol] == MAX)
            {
                //System.out.println(i + " " + dVol);
                minCows = -1;
                break;
            }
            else
                minCows += moos[dVol];
            prevVol = thisVol;
        }
        /*for (int i = 0; i < vols.size(); i++)
            System.out.print(moos[vols.get(i)]);
        System.out.println(" " + vols);*/
        in.close();
        out.println(minCows);
        out.close();
        System.exit(0);
    }
    
    /*public static int numMoos(int vol, int[] bVols)
    {
        if (vol < bVols[0])
            return MAX;
        else if (vols.contains(vol))
            return moos[vol];
        else
        {
            int minMoos = MAX;
            for (int i = bVols.length - 1; i >= 0; i--)
                if (bVols[i] <= vol)
                {
                    int mooValue = 1 + numMoos(vol - bVols[i], bVols);
                    if (mooValue < minMoos)
                        minMoos = mooValue;
                }
            if (minMoos != MAX)
            {
                vols.add(vol);
                moos[vol] = minMoos;
            }
            return minMoos;
        }
    }*/
}