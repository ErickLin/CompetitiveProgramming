/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: palsquare
*/
import java.io.*;
import java.util.*;

class palsquare
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("palsquare.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("palsquare.out")));
        int base = Integer.parseInt(in.readLine());
        in.close();
        for (int i = 1; i <= 300; i++)
        {
            String num = toBase(i, base);
            String numSquared = toBase(i * i, base);
            if (isPalindrome(numSquared))
                out.println(num + " " + numSquared);
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
            if (placeValue <= 9)
                str.append(placeValue);
            else if (placeValue == 10)
                str.append("A");
            else if (placeValue == 11)
                str.append("B");
            else if (placeValue == 12)
                str.append("C");
            else if (placeValue == 13)
                str.append("D");
            else if (placeValue == 14)
                str.append("E");
            else if (placeValue == 15)
                str.append("F");
            else if (placeValue == 16)
                str.append("G");
            else if (placeValue == 17)
                str.append("H");
            else if (placeValue == 18)
                str.append("I");
            else if (placeValue == 19)
                str.append("J");
            num -= (int)Math.pow(base, place) * placeValue;
        }
        return str.toString();
    }
}