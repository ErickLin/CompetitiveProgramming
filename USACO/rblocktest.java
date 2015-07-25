/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: rblocktest
*/
import java.io.*;
import java.util.*;

class rblocktest
{
    public static void main(String[] args) throws IOException
    {
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rblocktest.out")));
        out.println("250 31125");
        int pathCount = 0;
        for (int i = 1; i <= 250; i++)
            for (int j = i + 1; j <= 250; j++)
            {
                out.println(i + " " + j + " " + 500/*(500 + (int)Math.ceil(500 * Math.random()))*/);
                pathCount++;
            }
        out.close();
        System.exit(0);
    }
}