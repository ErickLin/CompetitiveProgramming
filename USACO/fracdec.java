/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fracdec
*/
import java.io.*;
import java.util.*;

class fracdec
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("fracdec.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fracdec.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int num = Integer.parseInt(line.nextToken());
        int denom = Integer.parseInt(line.nextToken());
        in.close();
        //the decimal place of the first repeating digit
        int rptPos = -1;
        //maps quotients to positions in the string
        int[] pos = new int[denom];
        Arrays.fill(pos, -1);
        StringBuilder dec = new StringBuilder(num / denom + ".");
        pos[num % denom] = dec.length() - 1;
        num = (num % denom) * 10;
        if (num == 0)
            dec.append("0");
        while (num != 0 && rptPos == -1)
        {
            if (pos[num % denom] != -1)
                rptPos = pos[num % denom];
            else
                pos[num % denom] = dec.length();
            dec.append(num / denom);
            num = (num % denom) * 10;
        }
        String dec2;
        if (rptPos == -1)
            dec2 = dec.toString();
        //insert repeating digit parentheses
        else
            dec2 = dec.substring(0, rptPos + 1) + "(" + dec.substring(rptPos + 1, dec.length()) + ")";
        //insert spaces to break up decimal string
        for (int i = 76; i < dec2.length(); i += 77)
            dec2 = dec2.substring(0, i) + " " + dec2.substring(i, dec2.length());
        line = new StringTokenizer(dec2);
        while (line.hasMoreTokens())
            out.println(line.nextToken());
        out.close();
        System.exit(0);
    }
}