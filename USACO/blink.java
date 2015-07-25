/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: blink
*/
import java.io.*;
import java.util.*;

class blink
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("blink.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("blink.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int numBulbs = Integer.parseInt(line.nextToken());
        long time = Long.parseLong(line.nextToken());
        //boolean array in bitwise form
        int lightState = 0;
        for (int i = numBulbs - 1; i >= 0; i--)
        {
            if (Integer.parseInt(in.readLine()) == 1)
                lightState |= (1 << i);
        }
        in.close();
        ArrayList<Integer> states = new ArrayList<Integer>();
        states.add(lightState);
        int start = 0;
        //this loop will stop as soon as it finds the repetition point of the states
        for (int t = 0; t < time; t++)
        {
            lightState = new Integer(lightState);
            int endState = lightState & 1;
            for (int i = 0; i < numBulbs - 1; i++)
                if ((lightState & (1 << (i + 1))) > 0)
                    lightState ^= (1 << i);
            if (endState > 0)
                lightState ^= (1 << numBulbs - 1);
            if (states.contains(lightState))
            {
                //remove all states that occur before the cycle
                start = states.indexOf(lightState);
                for (int i = 0; i < start; i++)
                    states.remove(0);
                break;
            }
            else
                states.add(lightState);
        }
        /*for (int s = 0; s < states.size(); s++)
        {
            for (int i = numBulbs - 1; i >= 0; i--)
            {
                if ((states.get(s) & (1 << i)) > 0)
                    System.out.print("1 ");
                else
                    System.out.print("0 ");
            }
            System.out.println();
        }*/
        int finalState;
        if (states.get(states.size() - 1) == 0)
            finalState = 0;
        else
        {
            //mod the time by the length of a cycle of states
            int end = new Long(time % (states.size()) - (start)).intValue();
            finalState = states.get(end % states.size());
        }
        for (int i = numBulbs - 1; i >= 0; i--)
        {
            if ((finalState & (1 << i)) > 0)
                out.println("1");
            else
                out.println("0");
        }
        out.close();
        System.exit(0);
    }
}