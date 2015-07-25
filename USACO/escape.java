/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: escape
*/
import java.io.*;
import java.util.*;

class escape
{
    static int numCows, weight[], max;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("escape.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("escape.out")));
        numCows = Integer.parseInt(in.readLine());
        weight = new int[numCows];
        for (int i = 0; i < numCows; i++)
            weight[i] = Integer.parseInt(in.readLine());
        in.close();
        max = 0;
        for (int i = 0; i < numCows - 1; i++)
        {
            if (numCows - 1 - i < max)
                break;
            recurse(i, 1, 0);
        }
        out.println(max);
        out.close();
        System.exit(0);
    }
    
    //"onboat" is a bitwise integer representing a boolean array
    public static void recurse(int index, int numOnBoat, int sum)
    {
        int newSum = new Integer(sum);
        newSum += weight[index];
        if (numOnBoat > max)
            max = numOnBoat;
        //System.out.println(index + " " + newSum + " " + numOnBoat);
        /*int newOnBoat = new Integer(onBoat);
        newOnBoat |= 1 << index;*/
        /*int numOnBoat = 0;
        for (int j = 0; j < numCows; j++)
            if ((newOnBoat & (1 << j)) != 0)
                numOnBoat++;
        if (numOnBoat > max)
            max = numOnBoat;*/
        for (int i = index + 1; i < numCows; i++)
            if (valid(newSum, weight[i]))
                recurse(i, numOnBoat + 1, newSum);
    }
    
    //returns whether the two parameters can be added together without a "carry"
    public static boolean valid(int a, int b)
    {
        for (int div = 10; div <= Math.min(a, b) * 10; div *= 10)
        {
            if (a % div + b % div >= div)
                return false;
            a -= a % div;
            b -= b % div;
        }
        return true;
    }
    
    //equivalent method
    /*public static boolean valid(int a, int b)
    {
        while (a > 0 && b > 0)
        {
            if (a % 10 + b % 10 >= 10)
                return false;
            a /= 10;
            b /= 10;
        }
        return true;
    }*/
}