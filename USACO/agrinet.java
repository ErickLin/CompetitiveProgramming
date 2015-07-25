/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: agrinet
*/
import java.io.*;
import java.util.*;

class agrinet
{
    static int n, minDist;
    static final int maxDist = 10000000, maxN = 2000;
    static int[][] weight;
    static int[] cost;
    static ArrayList<Edge> edges;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("agrinet.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("agrinet.out")));
        n = Integer.parseInt(in.readLine());
        weight = new int[n][n];
        edges = new ArrayList<Edge>();
        for (int i = 0; i < n; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++)
            {
                if (!line.hasMoreTokens())
                    line = new StringTokenizer(in.readLine());
                weight[i][j] = Integer.parseInt(line.nextToken());
                if (i != j)
                    edges.add(new Edge(i, j, weight[i][j]));
            }
        }
        in.close();
        out.println(prim());
        out.close();
        System.exit(0);
    }
    
    public static int prim()
    {
        cost = new int[n];
        int[] prev = new int[n];
        for (int i = 0; i < n; i++)
        {
            cost[i] = maxDist;
            prev[i] = -1;
        }
        //initialize starting vertex (field)
        cost[0] = 0;
        PriorityQueue<Integer> worlds = new PriorityQueue<Integer>(n, new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b)
            {
                return new Integer(cost[a]).compareTo(cost[b]);
            }
        });
        for (int vertex = 0; vertex < n; vertex++)
            worlds.add(vertex);
        while (worlds.size() > 0)
        {
            int vertex = worlds.poll();
            boolean isEmpty = true;
            for (int neighbor = 0; neighbor < n; neighbor++)
            {
                if (weight[vertex][neighbor] != -1)
                {
                    isEmpty = false;
                    if (worlds.contains(neighbor) && cost[neighbor] > weight[vertex][neighbor])
                    {
                        cost[neighbor] = weight[vertex][neighbor];
                        prev[neighbor] = vertex;
                        //decrease-key
                        worlds.remove(neighbor);
                        worlds.add(neighbor);
                    }
                }
            }
            if (isEmpty)
                return -1;
        }
        /*for (int i = 0; i < n; i++)
            System.out.print(prev[i] + " ");*/
        int totalCost = 0;
        for (int vertex = 1; vertex < n; vertex++)
        {
            //System.out.println("(" + (vertex + 1) + ", " + (prev[vertex] + 1) + ")" + " " + weight[vertex][prev[vertex]]);
            totalCost += weight[vertex][prev[vertex]];
        }
        return totalCost;
    }
    
    public static int kruskal()
    {
        int[] parents = new int[n];
        int[] ranks = new int[n];
        for (int vertex = 0; vertex < n; vertex++)
        {
            parents[vertex] = vertex;
            ranks[vertex] = 0;
        }
        Collections.sort(edges);
        //System.out.println(edges);
        int totalCost = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            int v1 = edges.get(i).get1();
            int v2 = edges.get(i).get2();
            int r1 = find(v1, parents);
            int r2 = find(v2, parents);
            if (r1 != r2)
            {
                //System.out.println(v1 + " " + v2 + " " + weight[v1][v2]);
                totalCost += weight[v1][v2];
                if (ranks[r1] > ranks[r2])
                    parents[r2] = r1;
                else
                {
                    if (ranks[r1] == ranks[r2])
                        ranks[r2]++;
                    parents[r1] = r2;
                }
            }
        }
        return totalCost;
    }
    
    private static int find(int vertex, int[] parents)
    {
        if (vertex != parents[vertex])
            parents[vertex] = find(parents[vertex], parents);
        return parents[vertex];
    }
    
    public static class Edge implements Comparable<Edge>
    {
        int vertex1, vertex2, weight;
        
        public Edge(int v1, int v2, int wt)
        {
            vertex1 = v1;
            vertex2 = v2;
            weight = wt;
        }
        
        public int get1()
        {
            return vertex1;
        }
        
        public int get2()
        {
            return vertex2;
        }
        
        public int getWeight()
        {
            return weight;
        }
        
        @Override
        public String toString()
        {
            return "(" + vertex1 + ", " + vertex2 + ") " + weight;
        }
        
        @Override
        public int compareTo(Edge other)
        {
            return new Integer(weight).compareTo(other.weight);
        }
    }
}