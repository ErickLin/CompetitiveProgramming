/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: rblock
*/
import java.io.*;
import java.util.*;

class rblock
{
    static final int maxDist = 9999999;
    static int n, weight[][], dist[], prev[];
    static ArrayList<ArrayList<Integer>> neighbors;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("rblock.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rblock.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        n = Integer.parseInt(line.nextToken());
        int numPathways = Integer.parseInt(line.nextToken());
        neighbors = new ArrayList<ArrayList<Integer>>(n);
        for (int i = 0; i < n; i++)
            neighbors.add(new ArrayList<Integer>());
        weight = new int[n][n];
        for (int i = 0; i < numPathways; i++)
        {
            line = new StringTokenizer(in.readLine());
            int field1 = Integer.parseInt(line.nextToken()) - 1;
            int field2 = Integer.parseInt(line.nextToken()) - 1;
            int length = Integer.parseInt(line.nextToken());
            neighbors.get(field1).add(field2);
            neighbors.get(field2).add(field1);
            weight[field1][field2] = length;
            weight[field2][field1] = length;
        }
        in.close();
        dijkstra();
        int distI = dist[n - 1];
        int distF = doubleEdges();
        out.println(distF - distI);
        out.close();
        System.exit(0);
    }
    
    public static void dijkstra()
    {
        //the shortest distance from the starting point to each field
        dist = new int[n];
        prev = new int[n];
        for (int i = 0; i < n; i++)
        {
            dist[i] = maxDist - 1;
            prev[i] = -1;
        }
        //initialize starting vertex (field)
        dist[0] = 0;
        PriorityQueue<Integer> worlds = new PriorityQueue<Integer>(n, new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b)
            {
                return new Integer(dist[a]).compareTo(dist[b]);
            }
        });
        for (int vertex = 0; vertex < n; vertex++)
            worlds.add(vertex);
        while (worlds.size() > 0)
        {
            int vertex = worlds.poll();
            //System.out.println((vertex + 1) + " " + neighbors.get(vertex));
            //update distances for all fields that are connected to the current field
            for (int neighbor : neighbors.get(vertex))
                if (dist[vertex] + weight[vertex][neighbor] < dist[neighbor])
                {
                    dist[neighbor] = dist[vertex] + weight[vertex][neighbor];
                    prev[neighbor] = vertex;
                    //decrease-key
                    worlds.remove(neighbor);
                    worlds.add(neighbor);
                }
            /*//mark the current field as visited
            visited[vertex] = true;
            if (vertex == n - 1)
                return;
            //choose the neighbor with the shortest distance from the starting point
            //for the next iteration
            int minNextDist = maxDist;
            nextVertex = -1;
            for (int i = 0; i < neighbors.get(vertex).size(); i++)
            {
                int neighbor = neighbors.get(vertex).get(i);
                if (!visited[neighbor] && dist[neighbor] < minNextDist)
                {
                    minNextDist = dist[neighbor];
                    nextVertex = neighbor;
                }
            }
            vertex = nextVertex;*/
        }
    }
    
    //this method also shows how to get the path
    public static int doubleEdges()
    {
        //maximize the new minimum distance
        int distF = 0;
        //start at the destination
        int vertex = n - 1;
        while (vertex > 0)
        {
            int nextVertex = prev[vertex];
            //System.out.println("(" + (vertex + 1) + ", " + (nextVertex + 1) + ")" + " " + weight[vertex][nextVertex]);
            weight[vertex][nextVertex] *= 2;
            weight[nextVertex][vertex] *= 2;
            dijkstra();
            if (dist[n - 1] > distF)
                distF = dist[n - 1];
            weight[vertex][nextVertex] /= 2;
            weight[nextVertex][vertex] /= 2;
            vertex = nextVertex;
        }
        return distF;
    }
}