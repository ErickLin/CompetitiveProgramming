/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: barn1
*/
import java.io.*;
import java.util.*;

class barn1
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("barn1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("barn1.out")));
        StringTokenizer firstLine = new StringTokenizer(in.readLine());
        int numBoards = Integer.parseInt(firstLine.nextToken());
        int numStalls = Integer.parseInt(firstLine.nextToken());
        int numStallsFilled = Integer.parseInt(firstLine.nextToken());
        ArrayList<Integer> filledStalls = new ArrayList<Integer>();
        for (int i = 0; i < numStallsFilled; i++)
            filledStalls.add(Integer.parseInt(in.readLine()));
        in.close();
        Collections.sort(filledStalls);
        int firstGapLength = filledStalls.get(0) - 1;
        ArrayList<Integer> midGapLengths = new ArrayList<Integer>();
        int currentGapLength = 0;
        for (int i = filledStalls.get(0); i < numStalls; i++)
        {
            if (filledStalls.contains(i + 1) && currentGapLength > 0)
            {
                midGapLengths.add(currentGapLength);
                currentGapLength = 0;
            }
            if (!filledStalls.contains(i + 1))
                currentGapLength++;
        }
        int lastGapLength = 0;
        if (currentGapLength > 0)
        {
            lastGapLength = currentGapLength;
            currentGapLength = 0;
        }
        //sort midGapLengths in descending order
        Collections.sort(midGapLengths, new Comparator<Integer>()
        {
            @Override
            public int compare(Integer a, Integer b)
            {
                return b.compareTo(a);
            }
        });
        /*for (int gap: midGapLengths)
            System.out.println(gap);*/
        int numStallsBlocked = numStalls;
        //subtract any gaps on both ends
        numStallsBlocked -= firstGapLength + lastGapLength;
        //System.out.println(firstGapLength + " " + lastGapLength + " " + numStallsBlocked);
        //subtract from numStallsBlocked the maximum lengths of a number of gaps equal to maxBoards + 1
        for (int i = 0; i < numBoards - 1 && i < midGapLengths.size(); i++)
            numStallsBlocked -= midGapLengths.get(i);
        out.println(numStallsBlocked);
        out.close();
        System.exit(0);
    }
}