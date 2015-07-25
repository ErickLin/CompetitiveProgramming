/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: moo
*/
import java.io.*;
import java.util.*;

class moo
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("moo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("moo.out")));
        int n = Integer.parseInt(in.readLine());
        in.close();
        /*String sequence = moo(0);
        for (int i = 1; sequence.length() < n; i++)
            sequence = moo(i);*/
        ArrayList<Character> sequence = new ArrayList<Character>();
        loop: for (int k = 0; sequence.size() < n; k++)
        {
            ArrayList<Character> seq = (ArrayList<Character>)sequence.clone();
            sequence.add("m".charAt(0));
            if (sequence.size() == n)
                break loop;
            for (int j = 0; j < k + 2; j++)
            {
                sequence.add("o".charAt(0));
                if (sequence.size() == n)
                    break loop;
            }
            for (int a = 0; a < seq.size(); a++)
            {
                sequence.add(seq.get(a));
                if (sequence.size() == n)
                    break loop;
            }
        }
        out.println(sequence.get(n - 1));
        out.close();
        System.exit(0);
    }
    
    public static String moo(int k)
    {
        String sequence = "";
        if (k > 0)
            sequence += moo(k - 1);
        sequence += "m";
        for (int i = 0; i < k + 2; i++)
            sequence += "o";
        if (k > 0)
            sequence += moo(k - 1);
        return sequence;
    }
}