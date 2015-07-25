/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: beads
*/
import java.io.*;

class beads
{
    static int length, currentBead, currentRed, currentBlue, startPos1, startPos2, localMax1, localMax2, globalMaxPair;
    static boolean onRed;
    static String string;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("beads.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("beads.out")));
        length = Integer.parseInt(in.readLine());
        string = in.readLine();
        in.close();
        currentRed = 0;
        currentBlue = 0;
        startPos1 = 0;
        startPos2 = 0;
        localMax1 = 0;
        localMax2 = 0;
        globalMaxPair = 0;
        onRed = true;
        for (int i = 0; i < 2; i++)
            for (currentBead = 0; currentBead < length; currentBead++)
                processBead(string.substring(currentBead,currentBead + 1));
        processMax();
        if (globalMaxPair > length)
            globalMaxPair = length;
        out.println(globalMaxPair);
        out.close();
        System.exit(0);
    }
    
    public static void processBead(String color)
    {
        if (color.equals("r"))
        {
            if (!onRed)
            {
                processMax();
                currentBlue = 0;
                onRed = true;
            }
            currentRed++;
        }
        if (color.equals("b"))
        {
            if (onRed)
            {
                processMax();
                currentRed = 0;
                onRed = false;
            }
            currentBlue++;
        }
        if (color.equals("w"))
        {
            if (onRed)
            {
                currentRed++;
            }
            else
            {
                currentBlue++;
            }
        }
    }
    
    public static void processMax()
    {
        localMax1 = localMax2;
        if (currentRed != 0)
        {
            localMax2 = currentRed;
        }
        if (currentBlue != 0)
        {
            localMax2 = currentBlue;
        }
        if (localMax1 + localMax2 + gatherWhites() > globalMaxPair)
        {
            globalMaxPair = localMax1 + localMax2 + gatherWhites();
        }
        //startPos1 determines where to start searching for white beads next time
        startPos1 = startPos2;
        startPos2 = currentBead;
    }
    
    //gets all white beads to the left of the current bead
    public static int gatherWhites()
    {
        int whiteBeads = 0;
        int pos = startPos1 - 1;
        while ((pos > 0 && string.substring(pos, pos + 1).equals("w")) || (pos == 0 && string.substring(length-1,length).equals("w")))
        {
            whiteBeads++;
            pos--;
        }
        return whiteBeads;
    }
}
