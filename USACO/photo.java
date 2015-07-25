/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: photo
*/
import java.io.*;
import java.util.*;

class photo
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("photo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("photo.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(line.nextToken());
        int numPairs = Integer.parseInt(line.nextToken());
        int[] cows1 = new int[1000];
        int[] cows2 = new int[1000];
        //Map<Integer, ArrayList<Integer>> pairs = new HashMap<Integer, ArrayList<Integer>>();
        for (int p = 0; p < numPairs; p++)
        {
            line = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(line.nextToken());
            int b = Integer.parseInt(line.nextToken());
            if (b > a)
            {
                cows1[p] = a;
                cows2[p] = b;
                /*if (pairs.get(a) == null)
                    pairs.put(a, new ArrayList<Integer>());
                pairs.get(a).add(b);*/
            }
            else
            {
                cows1[p] = b;
                cows2[p] = a;
                /*if (pairs.get(b) == null)
                    pairs.put(b, new ArrayList<Integer>());
                pairs.get(b).add(a);*/
            }
        }
        in.close();
        //ArrayList<Integer> incompatible = new ArrayList<Integer>();
        int photos = 0, left = 1, right;
        do
        {
            right = numCows;
            for (int n = 0; n < numPairs; n++)
                if (cows1[n] >= left && cows2[n] <= right)
                    right = cows2[n] - 1;
            /*if (incompatible.contains(n))
            {
                photos++;
                incompatible.clear();
            }
            if (pairs.get(n) != null)
                incompatible.addAll(pairs.get(n));*/
            photos++;
            left = right + 1;
        }
        while (left <= numCows);
        out.println(photos);
        out.close();
        System.exit(0);
    }
}