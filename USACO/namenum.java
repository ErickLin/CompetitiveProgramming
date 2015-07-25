/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: namenum
*/
import java.io.*;
import java.util.*;

class namenum
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("namenum.in"));
        BufferedReader inDict = new BufferedReader(new FileReader("dict.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("namenum.out")));
        String serialNum = in.readLine();
        in.close();
        ArrayList<String> validNames = new ArrayList<String>();
        String line;
        loop1: while ((line = inDict.readLine()) != null)
            if (line.length() == serialNum.length())
            {
                loop2: for (int i = 0; i < line.length(); i++)
                    if (!equivalent(line.substring(i, i + 1), serialNum.substring(i, i + 1)))
                        continue loop1;
                validNames.add(line);
            }
        inDict.close();
        if (validNames.size() > 0)
        {
            for (int i = 0; i < validNames.size(); i++)
                out.println(validNames.get(i));
        }
        else
            out.println("NONE");
        out.close();
        System.exit(0);
    }
    
    public static boolean equivalent(String letter, String num)
    {
        if ((num.equals("2") && (letter.equals("A") || letter.equals("B") || letter.equals("C")))
                || (num.equals("3") && (letter.equals("D") || letter.equals("E") || letter.equals("F")))
                || (num.equals("4") && (letter.equals("G") || letter.equals("H") || letter.equals("I")))
                || (num.equals("5") && (letter.equals("J") || letter.equals("K") || letter.equals("L")))
                || (num.equals("6") && (letter.equals("M") || letter.equals("N") || letter.equals("O")))
                || (num.equals("7") && (letter.equals("P") || letter.equals("R") || letter.equals("S")))
                || (num.equals("8") && (letter.equals("T") || letter.equals("U") || letter.equals("V")))
                || (num.equals("9") && (letter.equals("W") || letter.equals("X") || letter.equals("Y"))))
            return true;
        return false;
    }
}