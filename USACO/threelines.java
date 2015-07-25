/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: threelines
*/
import java.io.*;
import java.util.*;

class threelines
{
    static int num;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("threelines.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("threelines.out")));
        num = Integer.parseInt(in.readLine());
        int[] x = new int[num];
        int[] y = new int[num];
        for (int i = 0; i < num; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            x[i] = Integer.parseInt(line.nextToken());
            y[i] = Integer.parseInt(line.nextToken());
        }
        in.close();
        //arrays of unique values
        Set<Integer> xVal = new HashSet<Integer>(x.length);
        Set<Integer> yVal = new HashSet<Integer>(y.length);
        for (int i = 0; i < num; i++)
        {
            if (!xVal.contains(x[i]))
                xVal.add(x[i]);
            if (!yVal.contains(y[i]))
                yVal.add(y[i]);
        }
        /*for (int i = 0; i < xVal.size(); i++)
            System.out.println(xVal.get(i));
        for (int i = 0; i < yVal.size(); i++)
            System.out.println(yVal.get(i));*/
        if (isCovered(x, y, xVal, yVal))
            out.println("1");
        else
            out.println("0");
        out.close();
        System.exit(0);
    }
    
    public static boolean isCovered(int[] x, int[] y, Set<Integer> xVal, Set<Integer> yVal)
    {
        if (xVal.size() <= 3 || yVal.size() <= 3)
            return true;
        Set<Integer> distinct = new HashSet<Integer>();
        //2 vert. and 1 hor.
        loop: for (int c : yVal)
        {
            distinct.clear();
            for (int i = 0; i < num; i++)
                if (!distinct.contains(x[i]) && y[i] != c)
                {
                    if (distinct.size() < 2)
                        distinct.add(x[i]);
                    else
                        continue loop;
                }
            return true;
        }
        //2 hor. and 1 vert.
        loop: for (int c : xVal)
        {
            distinct.clear();
            for (int i = 0; i < num; i++)
                if (!distinct.contains(y[i]) && x[i] != c)
                {
                    if (distinct.size() < 2)
                        distinct.add(y[i]);
                    else
                        continue loop;
                }
            return true;
        }
        /*//2 vert. and 1 hor.
        for (int a = 0; a < xVal.size() - 1; a++)
            for (int b = 1; b < xVal.size(); b++)
                loop: for (int c = 0; c < yVal.size(); c++)
                {
                    for (int i = 0; i < num; i++)
                        if (!xVal.get(a).equals(x[i]) && !xVal.get(b).equals(x[i]) && !yVal.get(c).equals(y[i]))
                            continue loop;
                    return true;
                }
        //2 hor. and 1 vert.
        for (int a = 0; a < yVal.size() - 1; a++)
            for (int b = 1; b < yVal.size(); b++)
                loop: for (int c = 0; c < xVal.size(); c++)
                {
                    for (int i = 0; i < num; i++)
                        if (!yVal.get(a).equals(y[i]) && !yVal.get(b).equals(y[i]) && !xVal.get(c).equals(x[i]))
                            continue loop;
                    return true;
                }*/
        return false;
    }
}