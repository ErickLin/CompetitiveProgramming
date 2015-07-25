/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: lamps
*/
import java.io.*;
import java.util.*;

class lamps
{
    static int n, c;
    static boolean[] lampsOn, lampsOff;
    static ArrayList<String> valid;
    static PrintWriter out;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("lamps.in"));
        n = Integer.parseInt(in.readLine());
        lampsOn = new boolean[n];
        lampsOff = new boolean[n];
        c = Integer.parseInt(in.readLine());
        //read line 3
        StringTokenizer line = new StringTokenizer(in.readLine());
        int num;
        do
        {
            num = Integer.parseInt(line.nextToken());
            if (num > 0)
                lampsOn[num - 1] = true;
                //lampsOn |= 1 << (num - 1);
        }
        while (num != -1);
        //read line 4
        line = new StringTokenizer(in.readLine());
        do
        {
            num = Integer.parseInt(line.nextToken());
            if (num > 0)
                lampsOff[num - 1] = true;
                //lampsOff |= 1 << (num - 1);
        }
        while (num != -1);
        in.close();
        //System.out.println(Integer.toBinaryString(lampsOn));
        //System.out.println(Integer.toBinaryString(lampsOff));
        valid = new ArrayList<String>();
        boolean[] state = new boolean[n];
        Arrays.fill(state, true);
        iterate(state, 1, 0);
        out = new PrintWriter(new BufferedWriter(new FileWriter("lamps.out")));
        if (valid.isEmpty())
            out.println("IMPOSSIBLE");
        else
        {
            Collections.sort(valid);
            for (int i = 0; i < valid.size(); i++)
                out.println(valid.get(i));
        }
        out.close();
        System.exit(0);
    }
    
    //try all possible on/off combinations
    public static void iterate(boolean[] state, int button, int numPressed)
    {
        if (button > 4)
        {
            if (check(state, numPressed))
            {
                //reverse the String representing "state" and add to "valid"
                //valid.add(new StringBuffer(Integer.toBinaryString(state)).reverse().toString());
                StringBuffer str = new StringBuffer(n);
                for (int i = 0; i < n; i++)
                {
                    if (state[i] == true)
                        str.append(1);
                    else
                        str.append(0);
                }
                valid.add(str.toString());
            }
            return;
        }
        iterate(state, button + 1, numPressed);
        press(state, button);
        iterate(state, button + 1, numPressed + 1);
        //revert to original state
        press(state, button);
    }
    
    public static boolean check(boolean[] state, int numPressed)
    {
        //if the number of button presses don't match
        //note: the 2nd press negates the 1st for any lamp
        if (numPressed > c || (c - numPressed) % 2 == 1)
            return false;
        for (int i = 0; i < n; i++)
            if ((lampsOn[i] && !state[i]) || (lampsOff[i] && state[i]))
                return false;
        return true;
    }
    
    public static void press(boolean[] state, int button)
    {
        //binary complement
        if (button == 1)
            //state = ~state;
            for (int i = 0; i < n; i++)
                state[i] = !state[i];
        //switch all odd-numbered lamps
        if (button == 2)
            for (int i = 0; i < n; i += 2)
                state[i] = !state[i];
                //state ^= 1 << i;
        //switch all even-numbered lamps
        if (button == 3)
            for (int i = 1; i < n; i += 2)
                state[i] = !state[i];
                //state ^= 1 << i;
        //switch all lamps whose index is a multiple of 3
        if (button == 4)
            for (int i = 0; i < n; i += 3)
                state[i] = !state[i];
                //state ^= 1 << i;
    }
}