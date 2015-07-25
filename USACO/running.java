/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: running
*/
import java.io.*;
import java.util.*;

class running
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("running.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("running.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(line.nextToken());
        int laps = Integer.parseInt(line.nextToken());
        int lapLength = Integer.parseInt(line.nextToken());
        int dist = laps * lapLength;
        int[] spds = new int[numCows];
        int maxSpd = 0;
        for (int i = 0; i < numCows; i++)
        {
            spds[i] = Integer.parseInt(in.readLine());
            if (spds[i] > maxSpd)
                maxSpd = spds[i];
        }
        in.close();
        Arrays.sort(spds);
        double time = (double)dist / maxSpd;
        long overtakes = 0;
        for (int i = 1; i < spds.length; i++)
            for (int j = 0; j < i; j++)
                overtakes += (int)((spds[i] - spds[j]) * time) / lapLength;
        out.println(overtakes);
        out.close();
        System.exit(0);
    }
}