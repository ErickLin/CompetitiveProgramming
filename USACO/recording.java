/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: recording
*/
import java.io.*;
import java.util.*;

class recording
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("recording.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("recording.out")));
        int n = Integer.parseInt(in.readLine());
        Interval[] progs = new Interval[n];
        for (int i = 0; i < n; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            progs[i] = new Interval(Integer.parseInt(line.nextToken()), Integer.parseInt(line.nextToken()));
        }
        in.close();
        Arrays.sort(progs);
        /*out.println(n);
        for (int i = 0; i < n; i++)
            out.println(progs[i].start + " " + progs[i].end);*/
        //records the end time of the most recent program on each track
        int[] last = new int[2];
        int max = 0;
        for (int i = 0; i < n; i++)
        {
            /*System.out.println(progs[i].start + " " + progs[i].end + ":");
            for (int j = 0; j <= 1; j++)
                System.out.print(j + " " + last[j] + "  ");
            System.out.println("\n");*/
            boolean open0 = false, open1 = false;
            if (progs[i].start >= last[0])
                open0 = true;
            if (progs[i].start >= last[1])
                open1 = true;
            if (open0 || open1)
            {
                max++;
            }
            if (open0 && open1)
            {
                //put on the track whose last program ends later
                if (last[0] >= last[1])
                    last[0] = progs[i].end;
                else
                    last[1] = progs[i].end;
            }
            else if (open0)
                last[0] = progs[i].end;
            else if (open1)
                last[1] = progs[i].end;
            /*if (progs[i].start < last[0])
                continue;
            else if (progs[i].start < last[1])
            {
                max++;
                last[0] = last[1];
                last[1] = progs[i].end;
            }
            else
            {
                max++;
                last[1] = progs[i].end;
            }*/
        }
        out.println(max);
        out.close();
        System.exit(0);
    }
    
    public static class Interval implements Comparable<Interval>
    {
        int start, end;
        
        public Interval(int n1, int n2)
        {
            start = n1;
            end = n2;
        }
        
        @Override
        public int compareTo(Interval other)
        {
            if (end == other.end)
                return new Integer(start).compareTo(other.start);
            else
                return new Integer(end).compareTo(other.end);
        }
    }
}