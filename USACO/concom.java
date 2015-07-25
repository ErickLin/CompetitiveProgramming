/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: concom
*/
import java.io.*;
import java.util.*;

class concom
{
    static final int numVertices = 100;
    static ArrayList<Integer> vertices;
    static ArrayList<ArrayList<Integer>> edges;
    static int[][] edgeLens, percents;
    static boolean[][] visited;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("concom.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("concom.out")));
        vertices = new ArrayList<Integer>();
        edges = new ArrayList<ArrayList<Integer>>(numVertices);
        for (int i = 0; i < numVertices; i++)
            edges.add(new ArrayList<Integer>());
        //direct ownership
        edgeLens = new int[numVertices][numVertices];
        //direct or indirect ownership
        percents = new int[numVertices][numVertices];
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken()) - 1;
            int b = Integer.parseInt(line.nextToken()) - 1;
            if (!vertices.contains(a))
                vertices.add(a);
            if (!vertices.contains(b))
                vertices.add(b);
            edgeLens[a][b] = Integer.parseInt(line.nextToken());
            percents[a][b] = edgeLens[a][b];
            edges.get(a).add(b);
        }
        in.close();
        Collections.sort(vertices);
        visited = new boolean[numVertices][numVertices];
        for (int a : vertices)
            for (int b : edges.get(a))
                if (a != b && edgeLens[a][b] >= 50 && !visited[a][b])
                    recurse(a, b);
        for (int a : vertices)
            for (int b : vertices)
                if (a != b && (edgeLens[a][b] > 50 || percents[a][b] > 50))
                    out.println((a + 1) + " " + (b + 1));
        //System.out.println(edgeLens[33][0] + " " + percents[33][0]);
        out.close();
        System.exit(0);
    }
    
    public static void recurse(int a, int b)
    {
        visited[a][b] = true;
        //iterates through all vertices connected to b
        for (int c : edges.get(b))
            if (a != c/* && !edges.get(a).contains(c)*/)
            {
                percents[a][c] += edgeLens[b][c];
                if (percents[a][c] > 50 && !visited[a][c])
                    recurse(a, c);
            }
    }
}