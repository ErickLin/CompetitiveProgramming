/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: prefix
*/
import java.io.*;
import java.util.*;

class prefix
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("prefix.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("prefix.out")));
        ArrayList<String> primitives = new ArrayList<String>(200);
        StringTokenizer line = new StringTokenizer(in.readLine());
        //read all primitives to the array
        boolean end = false;
        do
        {
            do
            {
                primitives.add(line.nextToken());
            }
            while (line.hasMoreTokens());
            //check the first part of the next line
            line = new StringTokenizer(in.readLine());
            String first = line.nextToken();
            if (first.equals("."))
                end = true;
            else
                primitives.add(first);
        }
        while (!end);
        StringBuilder s = new StringBuilder(in.readLine());
        String ln;
        while ((ln = in.readLine()) != null)
            s.append(ln);
        in.close();
        String seq = s.toString();
        //whether a prefix of each length can be made
        boolean[] possible = new boolean[seq.length() + 1];
        int maxLen = 0;
        for (int i = 0; i < primitives.size(); i++)
        {
            int len = primitives.get(i).length();
            if (primitives.get(i).equals(seq.substring(0, len))
                    && !possible[len])
            {
                possible[len] = true;
                if (len > maxLen)
                    maxLen = len;
            }
        }
        //k is the length of the prefix
        for (int k = 1; k < seq.length(); k++)
            if (possible[k])
                for (int i = 0; i < primitives.size(); i++)
                {
                    int len = primitives.get(i).length();
                    if (k + len <= seq.length() && primitives.get(i).equals(seq.substring(k, k + len))
                            && !possible[k + len])
                    {
                        possible[k + len] = true;
                        if (k + len > maxLen)
                            maxLen = k + len;
                    }
                }
        out.println(maxLen);
        out.close();
        System.exit(0);
    }
}