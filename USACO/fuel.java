/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fuel
*/
import java.io.*;
import java.util.*;

class fuel
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("fuel.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fuel.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        //number of stations
        int n = Integer.parseInt(line.nextToken());
        //tank capacity
        int cap = Integer.parseInt(line.nextToken());
        int fuel = Integer.parseInt(line.nextToken());
        //destination index
        int end = Integer.parseInt(line.nextToken());
        ArrayList<Station> stations = new ArrayList<Station>(n);
        for (int i = 0; i < n; i++)
        {
            line = new StringTokenizer(in.readLine());
            stations.add(new Station(Integer.parseInt(line.nextToken()), Integer.parseInt(line.nextToken())));
        }
        in.close();
        Collections.sort(stations);
        int[] stack = new int[n];
        //for each station, stores the index of the nearest reachable station with smaller fuel price
        int[] next = new int[n];
        int stacklen = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            //pop station indices until the one at the top has a smaller price
            while (stacklen > 0 && stations.get(stack[stacklen - 1]).price >= stations.get(i).price)
                stacklen--;
            next[i] = (stacklen == 0 ? -1 : stack[stacklen - 1]);
            //push the index of the current station onto the stack
            stack[stacklen] = i;
            stacklen++;
        }
        /*for (int i = 0; i < n; i++)
            System.out.print(next[i] + " ");
        System.out.println();*/
        long cost = 0;
        //move to the first station
        fuel -= stations.get(0).pos;
        for (int i = 0; i < n; i++)
        {
            if (fuel < 0)
            {
                cost = -1;
                break;
            }
            //minimum of the fuel capacity and the distance to the next station or destination
            int gasNeeded = Math.min(cap, (next[i] == -1 ? end : stations.get(next[i]).pos) - stations.get(i).pos);
            if (fuel < gasNeeded)
            {
                //refill the tank
                cost += (long)(gasNeeded - fuel) * (long)stations.get(i).price;
                fuel = gasNeeded;
            }
            //travel the distance to the next station or destination
            fuel -= (i == n-1 ? end : stations.get(i+1).pos) - stations.get(i).pos;
        }
        out.println(cost);
        out.close();
        System.exit(0);
    }
    
    /*public static boolean possible(ArrayList<Station> stations, int end, int cap, int fuelI)
    {
        if (stations.get(0).pos > fuelI)
            return false;
        for (int i = 0; i < stations.size() - 1; i++)
            if (stations.get(i + 1).pos - stations.get(i).pos > cap)
                return false;
        if (end - stations.get(stations.size() - 1).pos > 0)
            return false;
        return true;
    }*/
    
    public static class Station implements Comparable<Station>
    {
        int pos, price;
        
        public Station(int x, int y)
        {
            pos = x;
            price = y;
        }
        
        @Override
        public int compareTo(Station other)
        {
            return Integer.signum(pos - other.pos);
        }
    }
}