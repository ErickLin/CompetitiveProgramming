/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: gpsduel
*/
import java.io.*;
import java.util.*;

class gpsduel2
{
    public static int maxWt = 100000, n, wt[][][], gpsNum, start, dist[][][], prev[][][], dist2[][], prev2[][];
    static ArrayList<ArrayList<Integer>> neighbors;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("gpsduel.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("gpsduel.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        int m = Integer.parseInt(line.nextToken());
        wt = new int[2][n][n];
        //weights based on distance
        for (int j = 0; j < 2; j++)
            for (int i = 0; i < n; i++)
                Arrays.fill(wt[j][i], maxWt);
        neighbors = new ArrayList<ArrayList<Integer>>(n);
        for (int i = 0; i < n; i++)
            neighbors.add(new ArrayList<Integer>());
        for (int i = 0; i < m; i++)
        {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            if (!neighbors.get(a).contains(b))
                neighbors.get(a).add(b);
            for (int j = 0; j < 2; j++)
            {
                int w = Integer.parseInt(line.nextToken());
                if (w < wt[j][a][b])
                    wt[j][a][b] = w;
            }
        }
        in.close();
        //the shortest distance from each starting intersection (dim 2) to each other intersection (dim 3) for each gps (dim 1)
        dist = new int[2][n][n];
        //predecessor to intersection i on shortest path
        prev = new int[2][n][n];
        for (gpsNum = 0; gpsNum < 2; gpsNum++)
            for (start = 0; start < n; start++)
                dijkstra1();
        //follow each GPS's shortest path (start can be set to any vertex number)
        /*for (int j = 0; j < 2; j++)
        {
            System.out.println("GPS #: " + (j + 1));
            int vertex = n - 1;
            int start = 1;
            while (vertex > start - 1)
            {
                int prevVertex = prev[j][start - 1][vertex];
                System.out.println("(" + (vertex + 1) + ", " + (prevVertex + 1) + ")" + " " + wt[j][prevVertex][vertex]);
                vertex = prevVertex;
            }
        }*/
        //least number of complaints to each intersection (dim 2) from each starting intersection (dim 1)
        dist2 = new int[n][n];
        prev2 = new int[n][n];
        for (start = 0; start < n; start++)
            dijkstra2();
        int vertex = n - 1;
        int shortest = 0;
        while (vertex > 0)
        {
            int prevVertex = prev2[0][vertex];
            shortest += dist2[prevVertex][vertex];
            //System.out.println("(" + (vertex + 1) + ", " + (prevVertex + 1) + ") " + dist2[prevVertex][vertex]);
            vertex = prevVertex;
        }
        out.println(shortest);
        out.close();
        System.exit(0);
    }
    
    public static void dijkstra1()
    {
        for (int i = 0; i < n; i++)
        {
            dist[gpsNum][start][i] = maxWt * (n - 1);
            prev[gpsNum][start][i] = -1;
        }
        //initialize distance from starting intersection
        dist[gpsNum][start][start] = 0;
        PriorityQueue<Integer> q = new PriorityQueue<Integer>(n, new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b)
            {
                return new Integer(dist[gpsNum][start][a]).compareTo(dist[gpsNum][start][b]);
            }
        });
        for (int vertex = 0; vertex < n; vertex++)
            q.add(vertex);
        while (q.size() > 0)
        {
            int vertex = q.poll();
            //System.out.println((vertex + 1) + " " + neighbors.get(vertex));
            for (int neighbor : neighbors.get(vertex))
                if (dist[gpsNum][start][vertex] + wt[gpsNum][vertex][neighbor] < dist[gpsNum][start][neighbor])
                {
                    dist[gpsNum][start][neighbor] = dist[gpsNum][start][vertex] + wt[gpsNum][vertex][neighbor];
                    prev[gpsNum][start][neighbor] = vertex;
                    //System.out.println(gpsNum + " " + start + " " + vertex + " " + neighbor + " " + prev[gpsNum][start][neighbor] + " " + next[gpsNum][start][vertex]);
                    //decrease-key
                    q.remove(neighbor);
                    q.add(neighbor);
                }
        }
    }
    
    public static void dijkstra2()
    {
        for (int i = 0; i < n; i++)
        {
            dist2[start][i] = 2 * (n - 1);
            prev2[start][i] = -1;
        }
        dist2[start][start] = 0;
        PriorityQueue<Integer> q = new PriorityQueue<Integer>(n, new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b)
            {
                return new Integer(dist2[start][a]).compareTo(dist2[start][b]);
            }
        });
        for (int vertex = 0; vertex < n; vertex++)
            q.add(vertex);
        while (q.size() > 0)
        {
            int vertex = q.poll();
            for (int neighbor : neighbors.get(vertex))
            {
                int wt2 = 2;
                for (int j = 0; j < 2; j++)
                {
                    //if this edge lies on one of the GPS's shortest paths
                    boolean on = false;
                    int v = n - 1;
                    while (v > start)
                    {
                        int prevVertex = prev[j][start][v];
                        if (vertex == prevVertex && neighbor == v)
                            on = true;
                        v = prevVertex;
                    }
                    if (on)
                    {
                        wt2--;
                        //System.out.println((j + 1) + " " + (start + 1) + " " + (vertex + 1) + " " + (neighbor + 1));
                    }
                }
                if (dist2[start][vertex] + wt2 < dist2[start][neighbor])
                {
                    dist2[start][neighbor] = dist2[start][vertex] + wt2;
                    prev2[start][neighbor] = vertex;
                    //decrease-key
                    q.remove(neighbor);
                    q.add(neighbor);
                }
                if (start != 0)
                    if (dist2[0][start] + dist2[start][neighbor] < dist2[0][neighbor])
                    {
                        dist2[0][neighbor] = dist2[0][start] + dist2[start][neighbor];
                        prev2[0][neighbor] = vertex;
                        //decrease-key
                        q.remove(neighbor);
                        q.add(neighbor);
                    }
            }
        }
    }
}