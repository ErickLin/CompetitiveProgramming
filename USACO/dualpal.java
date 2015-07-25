/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: dualpal
*/
import java.io.*;
import java.util.*;

class dualpal
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("dualpal.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("dualpal.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int N = Integer.parseInt(line.nextToken());
        int lowerBound = Integer.parseInt(line.nextToken());
        in.close();
        int currentNum = lowerBound + 1;
        while (N > 0)
        {
            int numBases = 0;
            for (int base = 2; base <= 10; base++)
                if (isPalindrome(toBase(currentNum, base)))
                {
                    numBases++;
                    if (numBases >= 2)
                    {
                        out.println(currentNum);
                        N--;
                        break;
                    }
                }
            currentNum++;
        }
        out.close();
        System.exit(0);
    }
    
    public static boolean isPalindrome(String str)
    {
        if (str.equals(new StringBuilder(str).reverse().toString()))
            return true;
        return false;
    }
    
    public static String toBase(int num, int base)
    {
        StringBuilder str = new StringBuilder();
        int highestPlace = 0;
        while ((int)Math.pow(base, highestPlace + 1) <= num)
            highestPlace++;
        for (int place = highestPlace; place >= 0; place--)
        {
            int placeValue = num / (int)Math.pow(base, place);
            str.append(placeValue);
            num -= (int)Math.pow(base, place) * placeValue;
        }
        return str.toString();
    }
}