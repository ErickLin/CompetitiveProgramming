/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: comehome
*/
import java.io.*;
import java.util.*;

class comehome
{
    static final int maxN = 52, maxDist = 9999999;
    static int[] dist;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("comehome.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("comehome.out")));
        int p = Integer.parseInt(in.readLine());
        ArrayList<String> labels = new ArrayList<String>();
        labels.add("Z");
        int[][] weight = new int[maxN][maxN];
        for (int i = 0; i < maxN; i++)
            Arrays.fill(weight[i], maxDist);
        boolean[] hasCow = new boolean[maxN];
        ArrayList<ArrayList<Integer>> 
        neighbors = new ArrayList<ArrayList<Integer>>(maxN);
        for (int i = 0; i < maxN; i++)
            neighbors.add(new ArrayList<Integer>());
        for (int i = 0; i < p; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int n1, n2;
            String v1 = line.nextToken();
            if (labels.contains(v1))
                n1 = labels.indexOf(v1);
            else
            {
                //position for the next vertex
                n1 = labels.size();
                labels.add(v1);
                if (Character.isUpperCase(v1.charAt(0)))
                    hasCow[n1] = true;
            }
            String v2 = line.nextToken();
            if (labels.contains(v2))
                n2 = labels.indexOf(v2);
            else
            {
                //position for the next vertex
                n2 = labels.size();
                labels.add(v2);
                if (Character.isUpperCase(v2.charAt(0)))
                    hasCow[n2] = true;
            }
            neighbors.get(n1).add(n2);
            neighbors.get(n2).add(n1);
            int wt = Integer.parseInt(line.nextToken());
            if (wt < weight[n1][n2])
            {
                weight[n1][n2] = wt;
                weight[n2][n1] = wt;
            }
        }
        in.close();
        /*for (int i = 0; i < labels.size(); i++)
            if (hasCow[i])
                System.out.println(i);*/
        int v = labels.size();
        dist = new int[v];
        Arrays.fill(dist, maxDist);
        dist[0] = 0;
        PriorityQueue<Integer> worlds = new PriorityQueue<Integer>(v, new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b)
            {
                return new Integer(dist[a]).compareTo(dist[b]);
            }
        });
        /*for (int vertex = 0; vertex < v; vertex++)
            worlds.add(vertex);*/
        worlds.add(0);
        int nearest = 0, nearestDist = maxDist;
        while (worlds.size() > 0)
        {
            int vertex = worlds.poll();
            //update distances for all fields that are connected to the current field
            for (int neighbor : neighbors.get(vertex))
                if (dist[vertex] + weight[vertex][neighbor] < dist[neighbor])
                {
                    dist[neighbor] = dist[vertex] + weight[vertex][neighbor];
                    if (dist[neighbor] < nearestDist)
                    {
                        if (hasCow[neighbor])
                        {
                            nearest = neighbor;
                            nearestDist = dist[neighbor];
                        }
                        //decrease-key
                        if (worlds.contains(neighbor))
                            worlds.remove(neighbor);
                        worlds.add(neighbor);
                    }
                }
        }
        /*for (int i = 0; i < v; i++)
            System.out.println(labels.get(i) + " " + dist[i]);*/
        out.println(labels.get(nearest) + " " + nearestDist);
        out.close();
        System.exit(0);
    }
}