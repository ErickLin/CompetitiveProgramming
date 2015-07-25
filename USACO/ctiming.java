/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ctiming
*/
import java.io.*;
import java.util.*;

class ctiming
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("ctiming.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ctiming.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int day = Integer.parseInt(line.nextToken());
        int hour = Integer.parseInt(line.nextToken());
        int minute = Integer.parseInt(line.nextToken());
        in.close();
        int timeElapsed = (day*60*24 + hour*60 +minute) - (11*60*24 + 11*60 + 11);
        if (timeElapsed < -1)
            timeElapsed = -1;
        out.println(timeElapsed);
        out.close();
        System.exit(0);
    }
}