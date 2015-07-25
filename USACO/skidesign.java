/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: skidesign
*/
import java.io.*;
import java.util.*;

class skidesign
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("skidesign.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("skidesign.out")));
        int numHills = Integer.parseInt(in.readLine());
        ArrayList<Integer> elevs = new ArrayList<Integer>(numHills);
        for (int i = 0; i < numHills; i++)
            elevs.add(Integer.parseInt(in.readLine()));
        in.close();
        Collections.sort(elevs);
        int minCost = 1000000;
        for (int minHeight = elevs.get(0); minHeight <= elevs.get(numHills - 1) - 17; minHeight++)
        {
            int maxHeight = minHeight + 17;
            int cost = 0;
            for (int hillNum = 0; hillNum < numHills; hillNum++)
            {
                if (elevs.get(hillNum) < minHeight)
                    cost += Math.pow(elevs.get(hillNum) - minHeight, 2);
                if (elevs.get(hillNum) > maxHeight)
                    cost += Math.pow(maxHeight - elevs.get(hillNum), 2);
            }
            if (cost < minCost)
                minCost = cost;
        }
        out.println(minCost);
        out.close();
        System.exit(0);
    }
}