/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: zerosum
*/
import java.io.*;
import java.util.*;

class zerosum
{
    static int n;
    static ArrayList<String> sols;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("zerosum.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("zerosum.out")));
        n = Integer.parseInt(in.readLine());
        in.close();
        sols = new ArrayList<String>();
        gen(new ArrayList<Integer>(), -1);
        gen(new ArrayList<Integer>(), 0);
        gen(new ArrayList<Integer>(), 1);
        Collections.sort(sols);
        for (int i = 0; i < sols.size(); i++)
            out.println(sols.get(i));
        out.close();
        System.exit(0);
    }
    
    public static void gen(ArrayList<Integer> signs, int sign)
    {
        signs.add(sign);
        if (signs.size() == n - 1)
            check(signs);
        else
        {
            gen(signs, -1);
            //can't reach a 3-digit sum
            if (sign != 0)
                gen(signs, 0);
            gen(signs, 1);
        }
        signs.remove(signs.size() - 1);
    }
    
    public static void check(ArrayList<Integer> signs)
    {
        int sum = 0;
        if (signs.get(0) == 0)
            sum = 10;
        else
            sum = 1;
        String sol = "1";
        //iterate through the digits following each sign
        for (int digit = 2; digit <= n; digit++)
        {
            //if there is not a blank after the digit
            if (digit == n || signs.get(digit - 1) != 0)
            {
                if (digit < 3 && signs.get(digit - 2) == 0)
                    sum += digit;
                else
                    sum += signs.get(digit - 2) * digit;
                if (signs.get(digit - 2) == -1)
                    sol += "-";
                if (signs.get(digit - 2) == 0)
                    sol += " ";
                if (signs.get(digit - 2) == 1)
                    sol += "+";
                sol += digit;
            }
            else
            {
                //concatenate the next 2 digits
                sum += signs.get(digit - 2) * (digit * 10 + (digit + 1));
                if (signs.get(digit - 2) == -1)
                    sol += "-";
                else
                    sol += "+";
                sol += digit + " " + (digit + 1);
                //skip the next sign, which is a blank
                digit++;
            }
        }
        //System.out.println(sol + " " + signs + " " + sum);
        if (sum == 0)
            sols.add(sol);
    }
}