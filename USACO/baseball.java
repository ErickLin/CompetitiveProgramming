/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: baseball
*/
import java.io.*;
import java.util.*;

class baseball
{
    static int[] locs;
    static int numTriples;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("baseball.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("baseball.out")));
        int numCows = Integer.parseInt(in.readLine());
        locs = new int[numCows];
        for (int i = 0; i < numCows; i++)
        {
            locs[i] = Integer.parseInt(in.readLine());
        }
        //System.out.println(Arrays.toString(locs));
        sort();
        //System.out.println(Arrays.toString(locs));
        numTriples = 0;
        for (int i = 0; i < numCows - 2; i++)
            for (int j = i + 1; j < numCows - 1; j++)
                for (int k = j + 1; k < numCows; k++)
                {
                    if (locs[k] - locs[j] >= locs[j] - locs[i] &&
                            locs[k] - locs[j] <= 2 * (locs[j] - locs[i])){
                        //System.out.println(locs[i]+" "+locs[j]+" "+locs[k]);
                        numTriples++;}
                }
        in.close();
        out.println(numTriples);
        out.close();
        System.exit(0);
    }
    
    public static void sort()
    {
        sort(0, locs.length - 1);
    }
    
    public static void sort(int low, int high)
    {
        int i = low, j = high, pivot = locs[low + (high - low) / 2];
        while (i <= j)
        {
            while (locs[i] < pivot)
                i++;
            while (locs[j] > pivot)
                j--;
            if (i <= j)
            {
                int temp = locs[i];
                locs[i] = locs[j];
                locs[j] = temp;
                i++;
                j--;
            }
        }
        if (low < j)
            sort(low, j);
        if (i < high)
            sort(i, high);
    }
}