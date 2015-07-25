/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: digits
*/
import java.io.*;
import java.util.*;

class digits
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("digits.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("digits.out")));
        String target2 = in.readLine();
        String target3 = in.readLine();
        in.close();
        int N = 0;
        outer: for (int num = 1; num <= 1000000000; num++)
        {
            char[] base2 = toBase(num, 2);
            if (target2.length() == base2.length)
            {
                int incorrect = 0;
                for (int i = 0; i < target2.length(); i++)
                    if (base2[i] != target2.charAt(i))
                    {
                        incorrect++;
                        if (incorrect > 1)
                            continue outer;
                    }
            }
            else
                continue outer;
            char[] base3 = toBase(num, 3);
            if (target3.length() == base3.length)
            {
                int incorrect = 0;
                for (int i = 0; i < target3.length(); i++)
                    if (base3[i] != target3.charAt(i))
                    {
                        incorrect++;
                        if (incorrect > 1)
                            continue outer;
                    }
            }
            else
                continue outer;
            N = num;
            break outer;
        }
        out.println(N);
        out.close();
        System.exit(0);
    }
    
    public static char[] toBase(int num, int base)
    {
        //return Integer.toString(num, base);
        int highestPlace = 0;
        while ((int)Math.pow(base, highestPlace + 1) <= num)
            highestPlace++;
        char[] output = new char[highestPlace + 1];
        for (int place = highestPlace; place >= 0; place--)
        {
            int placeValue = num / (int)Math.pow(base, place);
            output[highestPlace - place] = Character.forDigit(placeValue, 10);
            num -= (int)Math.pow(base, place) * placeValue;
        }
        return output;
    }
    
    public static int toDecimal(int base, String num)
    {
        //return Integer.parseInt(num, 10);
        int output = 0, place = 0;
        for (int i = num.length() - 1; i >= 0; i--)
        {
            output += Integer.parseInt(num.substring(i, i + 1)) * (int)Math.pow(base, place);
            place++;
        }
        return output;
    }
}