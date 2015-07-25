/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: irrigation
*/
import java.io.*;
import java.util.*;

class irrigation
{
    static int n, minDist;
    static final int maxDist = 10000000, maxN = 2000;
    static int[][] weight;
    static int[] cost, prev, parents, ranks;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("irrigation.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("irrigation.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        minDist = Integer.parseInt(line.nextToken());
        int[] x = new int[n];
        int[] y = new int[n];
        weight = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                weight[i][j] = -1;
        for (int i = 0; i < n; i++)
        {
            line = new StringTokenizer(in.readLine());
            x[i] = Integer.parseInt(line.nextToken());
            y[i] = Integer.parseInt(line.nextToken());
            //compare this field to every other field
            for (int j = 0; j < i; j++)
            {
                int dist = (x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]);
                if (dist >= minDist)
                {
                    weight[i][j] = dist;
                    weight[j][i] = dist;
                }
            }
        }
        in.close();
        /*for (int i = 0; i < n; i++)
            System.out.println(i + ": " + connections.get(i));*/
        /*connected = new boolean[n];
        for (int f = 0; f < n; f++)
            connected[f] = false;
        int minDist = 0;
        for (int f1 = 0; f1 < n; f1++)
        {
            if (connected[f1])
                continue;
            int minDist = 99999999;
            int f2 = f1;
            for (int i = 0; i < connections.get(f1).size(); i++)
            {
                int fTemp = connections.get(f1).get(i);
                if (weight[f1][fTemp] < minDist)
                {
                    minDist = weight[f1][fTemp];
                    f2 = fTemp;
                }
            }
            System.out.println(f1 + " " + f2 + " " + weight[f1][f2]);
            if (f1 == 0)
                connected[f1] = true;
            if (connected[f1])
                connected[f2] = true;
            minDist += minDist;
        }*/
        out.println(kruskal());
        out.close();
        System.exit(0);
    }
    
    public static int prim()
    {
        cost = new int[n];
        prev = new int[n];
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
                    //System.out.println(cost[neighbor] - weight[vertex][neighbor]);
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
        //ArrayList<HashSet<Integer>> sets = new ArrayList<HashSet<Integer>>(n);
        ArrayList<Edge> edges = new ArrayList<Edge>();
        parents = new int[n];
        ranks = new int[n];
        for (int vertex = 0; vertex < n; vertex++)
        {
            //create a new set
            //sets.add(new HashSet<Integer>());
            //add the vertex to the set
            //sets.get(vertex).add(vertex);
            parents[vertex] = vertex;
            ranks[vertex] = 0;
            boolean isEmpty = true;
            for (int neighbor = 0; neighbor < n; neighbor++)
                if (weight[vertex][neighbor] != -1)
                {
                    isEmpty = false;
                    //System.out.println(vertex + " " + neighbor + " " + weight[vertex][neighbor]);
                    edges.add(new Edge(vertex, neighbor, weight[vertex][neighbor]));
                }
            if (isEmpty)
                return -1;
        }
        Collections.sort(edges);
        //System.out.println(edges);
        int totalCost = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            int v1 = edges.get(i).get1();
            int v2 = edges.get(i).get2();
            int r1 = find(v1);
            int r2 = find(v2);
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
        /*for (int j = 0; j < n; j++)
            System.out.print(parents[j] + " ");
        System.out.println();
        for (int j = 0; j < n; j++)
            System.out.print(ranks[j] + " ");
        System.out.println();*/
        return totalCost;
    }
    
    private static int find(int vertex)
    {
        if (vertex != parents[vertex])
            parents[vertex] = find(parents[vertex]);
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
    
    /*public static class Vertex
    {
        int x, y;
        
        public Vertex(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
        
        public int getDist(Vertex other)
        {
            return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
        }
    }*/
}