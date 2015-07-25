/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: autotest
*/
import java.io.*;
import java.util.*;

class autotest
{
    public static void main(String[] args) throws IOException
    {
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("autotest.out")));
        out.println("1024 1000");
        Random r = new Random();
        for (int i = 0; i < 1024; i++)
        {
            out.println("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" + (char)(r.nextInt(26) + 'a'));
        }
        for (int j = 1; j <= 1000; j++)
            out.println(j + " aaaaaaaaaaaaaaaaaaaaaaaaa");
        out.println();
        out.close();
        System.exit(0);
    }
}