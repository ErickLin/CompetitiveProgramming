/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: milk3
*/
import java.io.*;
import java.util.*;

class milk3
{
    static int[] caps;
    static ArrayList<Integer> finalValues;
    static boolean[][] visited;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("milk3.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milk3.out")));
        caps = new int[3];
        int[] amts = new int[3];
        StringTokenizer line = new StringTokenizer(in.readLine());
        caps[0] = Integer.parseInt(line.nextToken());
        caps[1] = Integer.parseInt(line.nextToken());
        caps[2] = Integer.parseInt(line.nextToken());
        in.close();
        //Bucket C starts out filled
        amts[2] = caps[2];
        visited = new boolean[caps[0] + 1][caps[1] + 1];
        finalValues = new ArrayList<Integer>(caps[2]);
        //use arbitrary ints for 2nd and 3rd parameters
        procedure(amts);
        Collections.sort(finalValues);
        String ans = "";
        for (int i = 0; i < finalValues.size(); i++)
            ans += finalValues.get(i) + " ";
        out.println(ans.trim());
        out.close();
        System.exit(0);
    }
    
    public static void procedure(int[] amts)
    {
        if (visited[amts[0]][amts[1]])
            //System.out.println(amts[0] + " " + amts[1] + " " + amts[2] + " " + "returned");
            return;
        //System.out.println(amts[0] + " " + amts[1] + " " + amts[2] + " " + "visited");
        visited[amts[0]][amts[1]] = true;
        //if the first bucket is empty, record the amount of milk in the third bucket
        if (amts[0] == 0 && !finalValues.contains(amts[2]))
            finalValues.add(amts[2]);
        for (int a = 0; a < 3; a++)
            for (int b = 0; b < 3; b++)
                if (b != a && amts[a] > 0 && amts[b] < caps[b])
                    procedure(pour(amts, a, b));
    }
    
    public static int[] pour(int[] amtsI, int a, int b)
    {
        int[] amtsF = new int[3];
        for (int i = 0; i < 3; i++)
            amtsF[i] = new Integer(amtsI[i]);
        //the second bucket is filled
        if (amtsF[a] >= caps[b] - amtsF[b])
        {
            //System.out.print("filling: (" + a + " to " + b + ") ");
            amtsF[a] -= (caps[b] - amtsF[b]);
            amtsF[b] = caps[b];
        }
        //the first bucket is emptied
        else if (amtsF[a] < caps[b] - amtsF[b])
        {
            //System.out.print("emptying: (" + a + " to " + b + ") ");
            amtsF[b] += amtsF[a];
            amtsF[a] = 0;
        }
        /*for (int i = 0; i < 3; i++)
            System.out.print(amtsF[i] + " ");
        System.out.println();*/
        return amtsF;
    }
}