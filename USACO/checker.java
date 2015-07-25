/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: checker
*/
import java.io.*;
import java.util.*;

class checker
{
    static PrintWriter out;
    static int solutions;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("checker.in"));
        out = new PrintWriter(new BufferedWriter(new FileWriter("checker.out")));
        int N = Integer.parseInt(in.readLine());
        in.close();
        ArrayList<Integer> choices = new ArrayList<Integer>(N);
        for (int i = 1; i <= N; i++)
            choices.add(i);
        solutions = 0;
        arrange("", choices);
        out.println(solutions);
        out.close();
        System.exit(0);
    }
    
    public static void arrange(String order, ArrayList<Integer> c)
    {
        if (c.isEmpty())
        {
            out.println(order.trim());
            solutions++;
        }
        ArrayList<Integer> choices = new ArrayList<Integer>(c.size());
        for (int j = 0; j < c.size(); j++)
            choices.add(new Integer(c.get(j)));
        for (int i = 0; i < choices.size(); i++)
        {
            
            order += choices.get(i) + " ";
            choices.remove(new Integer(choices.get(i)));
            arrange(order, choices);
        }
    }
}