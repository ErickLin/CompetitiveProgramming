/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: optmilk
*/
import java.io.*;
import java.util.*;

class optmilk
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("optmilk.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("optmilk.out")));
        StringTokenizer firstLine = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(firstLine.nextToken());
        int d = Integer.parseInt(firstLine.nextToken());
        int outputs[] = new int[n];
        for (int i = 0; i < n; i++)
            outputs[i] = Integer.parseInt(in.readLine());
        int total = 0;
        for (int j = 0; j < d; j++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            outputs[Integer.parseInt(line.nextToken()) - 1] = Integer.parseInt(line.nextToken());
            int oddSum = 0, evenSum = 0;
            for (int i = 0; i < n; i += 2)
                oddSum += outputs[i];
            for (int i = 1; i < n; i += 2)
                evenSum += outputs[i];
            //System.out.println(oddSum > evenSum ? oddSum : evenSum);
            total += oddSum > evenSum ? oddSum : evenSum;
        }
        in.close();
        out.println(total);
        out.close();
        System.exit(0);
    }
}