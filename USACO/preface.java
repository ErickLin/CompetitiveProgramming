/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: preface
*/
import java.io.*;
import java.util.*;

class preface
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("preface.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("preface.out")));
        int n = Integer.parseInt(in.readLine());
        in.close();
        /*int[] I = new int[n + 1];
        int[] V = new int[n + 1];
        int[] X = new int[n + 1];
        int[] L = new int[n + 1];
        int[] C = new int[n + 1];
        int[] D = new int[n + 1];
        int[] M = new int[n + 1];*/
        int countI = 0, countV = 0, countX = 0, countL = 0, countC = 0, countD = 0, countM = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i % 5 >= 1 && i % 5 <= 3)
                countI += i % 5;
            else if (i % 5 == 4)
                countI++;
            if (i % 10 >= 4 && i % 10 <= 8)
                countV++;
            if (i % 10 == 9)
                countX++;
            
            if ((i % 50)/10 >= 1 && (i % 50)/10 <= 3)
                countX += (i % 50)/10;
            else if ((i % 50)/10 == 4)
                countX++;
            if ((i % 100)/10 >= 4 && (i % 100)/10 <= 8)
                countL++;
            if ((i % 100)/10 == 9)
                countC++;
            
            if ((i % 500)/100 >= 1 && (i % 500)/100 <= 3)
                countC += (i % 500)/100;
            else if ((i % 500)/100 == 4)
                countC++;
            if ((i % 1000)/100 >= 4 && (i % 1000)/100 <= 8)
                countD++;
            if ((i % 1000)/100 == 9)
                countM++;
            
            if ((i % 5000)/1000 >= 1 && (i % 5000)/1000 <= 3)
                countM += (i % 5000)/1000;
        }
        out.println("I " + countI);
        if (countV > 0)
            out.println("V " + countV);
        if (countX > 0)
            out.println("X " + countX);
        if (countL > 0)
            out.println("L " + countL);
        if (countC > 0)
            out.println("C " + countC);
        if (countD > 0)
            out.println("D " + countD);
        if (countM > 0)
            out.println("M " + countM);
        out.close();
        System.exit(0);
    }
}