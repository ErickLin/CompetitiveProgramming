/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: cruise
*/
import java.io.*;
import java.util.*;

class cruise
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("cruise.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cruise.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        int k = Integer.parseInt(line.nextToken());
        int[] left = new int[n];
        int[] right = new int[n];
        for (int i = 0; i < n; i++)
        {
            line = new StringTokenizer(in.readLine());
            left[i] = Integer.parseInt(line.nextToken()) - 1;
            right[i] = Integer.parseInt(line.nextToken()) - 1;
        }
        String[] dir = new String[m];
        line = new StringTokenizer(in.readLine());
        for (int i = 0; i < m; i++)
            dir[i] = line.nextToken();
        in.close();
        //stores neighbor of each vertex
        int[] next = new int[n];
        for (int i = 0; i < n; i++)
        {
            //start at port i + 1
            int currentPort = i;
            //apply the sequence of directions once
            for (int j = 0; j < m; j++)
            {
                if (dir[j].equals("L"))
                    currentPort = left[currentPort];
                else
                    currentPort = right[currentPort];
            }
            //set the destination of port i + 1 after one sequence
            next[i] = currentPort;
        }
        int currentPort = 0;
        //mod k by the length of the cycle containing the first port, if the latter is smaller
        for (int len = 1; len <= k; len++)
        {
            currentPort = next[currentPort];
            //if a cycle is found
            if (currentPort == 0)
            {
                k %= len;
                break;
            }
        }
        int dest = 0;
        for (int i = 0; i < k; i++)
            dest = next[dest];
        out.println(dest + 1);
        out.close();
        System.exit(0);
    }
}