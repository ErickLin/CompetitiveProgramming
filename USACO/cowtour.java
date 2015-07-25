/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: cowtour
*/
import java.io.*;
import java.util.*;
import java.text.DecimalFormat;

class cowtour
{
    static final int maxDist = 150000, trunc = 1000000;
    static int[] x, y;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("cowtour.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowtour.out")));
        int n = Integer.parseInt(in.readLine());
        x = new int[n];
        y = new int[n];
        LinkedList<Integer> unassigned = new LinkedList<Integer>();
        for (int i = 0; i < n; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            x[i] = Integer.parseInt(line.nextToken());
            y[i] = Integer.parseInt(line.nextToken());
            unassigned.add(i);
        }
        boolean[][] adj = new boolean[n][n];
        double[][] dist = new double[n][n];
        for (int i = 0; i < n; i++)
        {
            Arrays.fill(dist[i], maxDist);
            String line = in.readLine();
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    dist[i][j] = 0;
                    dist[j][i] = 0;
                }
                if (line.substring(j, j + 1).equals("1"))
                {
                    adj[i][j] = true;
                    dist[i][j] = distance(i, j);
                }
            }
        }
        in.close();
        int[] fieldNum = new int[n];
        int numFields = 0;
        for (int index = 1; !unassigned.isEmpty(); index++)
        {
            LinkedList<Integer> queue = new LinkedList<Integer>();
            int pasture = unassigned.poll();
            queue.add(pasture);
            while (!queue.isEmpty())
            {
                pasture = queue.poll();
                fieldNum[pasture] = index;
                for (int other = 0; other < n; other++)
                    if (fieldNum[other] == 0 && adj[pasture][other])
                    {
                        fieldNum[other] = index;
                        unassigned.remove(new Integer(other));
                        queue.add(other);
                    }
            }
            if (unassigned.isEmpty())
                numFields = index;
        }
        /*for (int i = 0; i < n; i++)
            System.out.println(fieldNum[i]);*/
        //Floyd-Warshall
        //intermediate vertex
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = i; j < n; j++)
                    //if i and j are connected
                    if (fieldNum[i] == fieldNum[j])
                        if (k != i && k != j)
                            if (dist[i][k] + dist[k][j] < dist[i][j])
                            {
                                dist[i][j] = dist[i][k] + dist[k][j];
                                dist[j][i] = dist[i][k] + dist[k][j];
                            }
        //diameter of each field
        double[] diameter = new double[numFields];
        //maximum distance from each pasture to a connected pasture
        double[] radius = new double[n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && fieldNum[i] == fieldNum[j])
                {
                    if (dist[i][j] > diameter[fieldNum[i] - 1])
                        diameter[fieldNum[i] - 1] = dist[i][j];
                    if (dist[i][j] > radius[i])
                        radius[i] = dist[i][j];
                }
        /*for (int i = 0; i < numFields; i++)
            System.out.println(diameter[i]);
        for (int i = 0; i < n; i++)
            System.out.println(fieldNum[i] + " " + radius[i]);*/
        double minDiameter = maxDist;
        //choose 2 points from different fields to connect
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && fieldNum[i] != fieldNum[j])
                {
                    double newDiameter = Math.max(Math.max(diameter[fieldNum[i] - 1], diameter[fieldNum[j] - 1]), radius[i] + radius[j] + distance(i, j));
                    if (newDiameter < minDiameter)
                        minDiameter = newDiameter;
                }
        String ans = new DecimalFormat("#.######").format(minDiameter);
        if (!ans.contains("."))
            ans += ".";
        while (ans.length() - ans.indexOf(".") <= 6)
            ans += "0";
        out.println(ans);
        out.close();
        System.exit(0);
    }
    
    public static double distance(int i, int j)
    {
        return Math.sqrt((x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]));
    }
}