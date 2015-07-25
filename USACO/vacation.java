/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: vacation
*/
import java.io.*;
import java.util.*;

class vacation
{
    static final int maxDist = 200 * 1000000;
    static int n, wt[][], dist[][], prev[][];
    static ArrayList<ArrayList<Integer>> neighbors;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("vacation.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("vacation.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        int hubNum = Integer.parseInt(line.nextToken());
        int q = Integer.parseInt(line.nextToken());
        //edge weights between farms
        wt = new int[n][n];
        //distance between farms when passing through a hub
        dist = new int[n][n];
        prev = new int[n][n];
        for (int i = 0; i < n; i++)
        {
            Arrays.fill(wt[i], maxDist);
            Arrays.fill(dist[i], maxDist);
            Arrays.fill(prev[i], -1);
        }
        neighbors = new ArrayList<ArrayList<Integer>>(n);
        for (int i = 0; i < n; i++)
            neighbors.add(new ArrayList<Integer>());
        for (int i = 0; i < m; i++)
        {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            int d = Integer.parseInt(line.nextToken());
            if (d < wt[a][b])
            {
                wt[a][b] = d;
                //if either a or b is a hub
                if (a < hubNum || b < hubNum)
                {
                    dist[a][b] = d;
                    neighbors.get(a).add(b);
                }
            }
        }
        //Floyd-Warshall for weights
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    /*if (k >= hubNum && i >= hubNum && j >= hubNum)
                        break;*/
                    if (wt[i][k] + wt[k][j] < wt[i][j])
                    {
                        wt[i][j] = wt[i][k] + wt[k][j];
                        if (i < hubNum || k < hubNum || j < hubNum)
                        {
                            dist[i][j] = wt[i][k] + wt[k][j];
                            neighbors.get(i).add(j);
                        }
                    }
                }
        //Floyd-Warshall for distances
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        int numValid = 0;
        long sum = 0;
        for (int i = 0; i < q; i++)
        {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            if (dist[a][b] < maxDist)
            {
                numValid++;
                sum += dist[a][b];
            }
        }
        in.close();
        out.println(numValid);
        out.println(sum);
        out.close();
        System.exit(0);
    }
}