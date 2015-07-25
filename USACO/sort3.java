/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: sort3
*/
import java.io.*;
import java.util.*;

class sort3
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("sort3.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sort3.out")));
        int size = Integer.parseInt(in.readLine());
        int[] records = new int[size];
        int numGold = 0, numSilver = 0, numBronze = 0;
        for (int i = 0; i < size; i++)
        {
            int num = Integer.parseInt(in.readLine());
            records[i] = num;
            if (num == 1)
                numGold++;
            if (num == 2)
                numSilver++;
            if (num == 3)
                numBronze++;
        }
        in.close();
        int[][] mappings = new int[3][3];
        for (int i = 0; i < numGold; i++)
            mappings[0][records[i]-1]++;
        for (int i = numGold; i < numGold + numSilver; i++)
            mappings[1][records[i]-1]++;
        for (int i = numGold + numSilver; i < size; i++)
            mappings[2][records[i]-1]++;
        int numSwaps = 0;
        numSwaps += Math.min(mappings[0][1], mappings[1][0]);
        numSwaps += 2 * Math.abs(mappings[1][0] - mappings[0][1]);
        numSwaps += Math.min(mappings[1][2], mappings[2][1]);
        numSwaps += Math.min(mappings[0][2], mappings[2][0]);
        /*for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                System.out.print(numMappings[i][j] + " ");
            System.out.println();
        }*/
        out.println(numSwaps);
        out.close();
        System.exit(0);
    }
    
    /*public static void swap(ArrayList<Integer> array1, int i1, ArrayList<Integer> array2, int i2)
    {
        int temp = array1.get(i1);
        array1.set(i1, array2.get(i2));
        array2.set(i2, temp);
    }*/
}