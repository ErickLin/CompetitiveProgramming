/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: slowdown
*/
import java.io.*;
import java.util.*;

class slowdown
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("slowdown.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("slowdown.out")));
        int numEvents = Integer.parseInt(in.readLine());
        ArrayList<Integer> times =  new ArrayList<Integer>(numEvents);
        ArrayList<Integer> dists =  new ArrayList<Integer>(numEvents);
        for (int i = 0; i < numEvents; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            String eventType = line.nextToken();
            if (eventType.equals("T"))
                times.add(Integer.parseInt(line.nextToken()));
            else
                dists.add(Integer.parseInt(line.nextToken()));
        }
        in.close();
        //sort in descending order
        Comparator<Integer> descending = new Comparator<Integer>()
        {
            @Override
            public int compare(Integer a, Integer b)
            {
                return b.compareTo(a);
            }
        };
        Collections.sort(times, descending);
        Collections.sort(dists, descending);
        /*for (int i = 0; i < times.size(); i++)
            System.out.print(times.get(i) + " ");
        System.out.println();
        for (int i = 0; i < dists.size(); i++)
            System.out.print(dists.get(i) + " ");
        System.out.println();*/
        int oneOverSpd = 1;
        double time = 0.0;
        double dist = 0.0;
        while (times.size() > 0 || dists.size() > 0)
        {
            //System.out.println(times.size() + " " + dists.size());
            //System.out.println("next time: " + untilNextT + "   next distance: " + untilNextD);
            double untilNextEvent;
            int simEvents = 0;
            if (times.size() > 0 && (dists.isEmpty() || times.get(times.size() - 1) - time < (dists.get(dists.size() - 1) - dist) * oneOverSpd))
            {
                untilNextEvent = times.get(times.size() - 1) - time;
                int lastTime = times.get(times.size() - 1);
                while (times.size() > 0 && times.get(times.size() - 1).equals(lastTime))
                {
                    times.remove(times.size() - 1);
                    simEvents++;
                }
            }
            else if (dists.size() > 0 && (times.isEmpty() || times.get(times.size() - 1) - time > (dists.get(dists.size() - 1) - dist) * oneOverSpd))
            {
                untilNextEvent = (dists.get(dists.size() - 1) - dist) * oneOverSpd;
                int lastDist = dists.get(dists.size() - 1);
                while (dists.size() > 0 && dists.get(dists.size() - 1).equals(lastDist))
                {
                    dists.remove(dists.size() - 1);
                    simEvents++;
                }
            }
            else
            {
                untilNextEvent = times.get(times.size() - 1) - time;
                int lastTime = times.get(times.size() - 1);
                while (times.size() > 0 && times.get(times.size() - 1).equals(lastTime))
                {
                    times.remove(times.size() - 1);
                    simEvents++;
                }
                int lastDist = dists.get(dists.size() - 1);
                while (dists.size() > 0 && dists.get(dists.size() - 1).equals(lastDist))
                {
                    dists.remove(dists.size() - 1);
                    simEvents++;
                }
            }
            time += untilNextEvent;
            dist += 1.0 * untilNextEvent / oneOverSpd;
            //System.out.println("new time: " + time + "   new distance: " + dist);
            for (int i = 0; i < simEvents; i++)
                oneOverSpd++;
            //System.out.println("speed: 1/" + oneOverSpd);
        }
        //cover the remaining distance after all the events
        time += (1000.0 - dist) * oneOverSpd;
        out.println((int)(time + 0.5));
        out.close();
        System.exit(0);
    }
}