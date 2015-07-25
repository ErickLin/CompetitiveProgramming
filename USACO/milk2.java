/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: milk2
*/
import java.io.*;
import java.util.*;

class milk2
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("milk2.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
        int num = Integer.parseInt(in.readLine());
        HashMap<Integer,Integer> times = new HashMap<Integer,Integer>(num * 2);
        int startTime = 1000000, endTime = 0;
        //ArrayList<Integer> duplicates = new ArrayList<Integer>();
        for (int i = 0; i < num; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int s = Integer.parseInt(line.nextToken());
            if (times.containsKey(s))
                times.put(s, times.get(s) + 1);
            else
                times.put(s, 1);
            if (s < startTime) startTime = s;
            int e = Integer.parseInt(line.nextToken());
            if (times.containsKey(e))
                times.put(e,times.get(e) - 1);
            else
                times.put(e, -1);
            if (e > endTime) endTime = e;
        }
        in.close();
        /*for (int i = 0; i < duplicates.size(); i++)
            times.remove(duplicates.get(i));*/
        //System.out.println(startTime + " " + endTime);
        int starts = 0, ends = 0, milkTime = 0, idleTime = 0,
                maxMilkTime = 0, maxIdleTime = 0;
        for (int t = startTime; t < endTime; t++)
        {
            if (times.containsKey(t))
            {
                if (times.get(t) > 0)
                {
                    starts += times.get(t);
                }
                if (times.get(t) < 0)
                {
                    ends -= times.get(t);
                }
                //System.out.println(t + " " + times.get(t));
            }
            if (starts > ends)
            {
                milkTime++;
                if (milkTime > maxMilkTime)
                    maxMilkTime = milkTime;
                if (idleTime != 0)
                    idleTime = 0;
            }
            else
            {
                idleTime++;
                if (idleTime > maxIdleTime)
                    maxIdleTime = idleTime;
                if (milkTime != 0)
                    milkTime = 0;
            }
        }
        //System.out.println(starts + " " + ends);
        out.println(maxMilkTime + " " + maxIdleTime);
        out.close();
        System.exit(0);
    }
}