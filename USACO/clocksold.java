/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: clocks
*/
import java.io.*;
import java.util.*;

class clocksold
{
    static Clock[] clocks;
    static String solution;
    
    public static class Clock
    {
        private int time;
        
        public Clock(int t)
        {
            time = t;
        }
        
        public int getTime()
        {
            return time;
        }
        
        public void turn()
        {
            time += 3;
            if (time > 12)
                time %= 12;
        }
    }
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("clocksold.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("clocksold.out")));
        clocks = new Clock[9];
        for (int i = 0; i < 9; i += 3)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            for (int j = i; j < i + 3; j++)
                clocks[j] = new Clock(Integer.parseInt(line.nextToken()));
        }
        in.close();
        /*for (int i = 0; i < 9; i++)
            System.out.print(clocks[i].getTime() + " ");
        System.out.println();*/
        solution = "";
        generate(1, "");
        /*for (int i = 0; i < clocks.length; i++)
            System.out.print(clocks[i].getTime() + " ");
        System.out.println();*/
        out.println(solution);
        out.close();
        System.exit(0);
    }
    
    public static boolean isSolved(Clock[] c)
    {
        for (int clockNum = 0; clockNum < 9; clockNum++)
            if (c[clockNum].getTime() != 12)
                return false;
        return true;
    }
    
    public static void generate(int moveNum, String oldSeq)
    {
        //each move number can be made anywhere from 1-4 times
        for (int num = 0; num < 4; num++)
        {
            String newSeq = oldSeq;
            for (int i = 0; i < num; i++)
            {
                newSeq += Integer.toString(moveNum);
                if (moveNum < 9 || i < num - 1)
                    newSeq += " ";
            }
            if (moveNum == 9)
            {
                //create a new array of clocks on which to perform all the moves
                Clock[] clocksF = new Clock[clocks.length];
                for (int clockNum = 0; clockNum < 9; clockNum++)
                    clocksF[clockNum] = new Clock(clocks[clockNum].getTime());
                StringTokenizer sol = new StringTokenizer(newSeq);
                while (sol.hasMoreTokens())
                    move(Integer.parseInt(sol.nextToken()), clocksF);
                if (isSolved(clocksF))
                {
                    /*for (int i = 0; i < clocksF.length; i++)
                        System.out.print(clocksF[i].getTime() + " ");
                    System.out.println();*/
                    solution = newSeq;
                    return;
                }
            }
            else
                generate(moveNum + 1, newSeq);
        }
    }
    
    public static void move(int index, Clock[] c)
    {
        if (index == 1)
        {
            c[0].turn();
            c[1].turn();
            c[3].turn();
            c[4].turn();
        }
        if (index == 2)
        {
            c[0].turn();
            c[1].turn();
            c[2].turn();
        }
        if (index == 3)
        {
            c[1].turn();
            c[2].turn();
            c[4].turn();
            c[5].turn();
        }
        if (index == 4)
        {
            c[0].turn();
            c[3].turn();
            c[6].turn();
        }
        if (index == 5)
        {
            c[1].turn();
            c[3].turn();
            c[4].turn();
            c[5].turn();
            c[7].turn();
        }
        if (index == 6)
        {
            c[2].turn();
            c[5].turn();
            c[8].turn();
        }
        if (index == 7)
        {
            c[3].turn();
            c[4].turn();
            c[6].turn();
            c[7].turn();
        }
        if (index == 8)
        {
            c[6].turn();
            c[7].turn();
            c[8].turn();
        }
        if (index == 9)
        {
            c[4].turn();
            c[5].turn();
            c[7].turn();
            c[8].turn();
        }
    }
}