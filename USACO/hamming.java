/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: hamming
*/
import java.io.*;
import java.util.*;

class hamming
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("hamming.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hamming.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int end = Integer.parseInt(line.nextToken());
        int length = (1 << Integer.parseInt(line.nextToken())) - 1;
        int minDist = Integer.parseInt(line.nextToken());
        in.close();
        ArrayList<Integer> codewords = new ArrayList<Integer>(end);
        codewords.add(0);
        out.print("0 ");
        int count = 1;
        //System.out.println(Integer.toBinaryString(0x554 ^ 0x234));
        //System.out.println(hammingDist(0x554, 0x234));
        //System.out.println(Integer.toBinaryString(3) + " " + Integer.toBinaryString(108) + " " + hammingDist(3, 108));
        loop: for (int currentNum = 1; currentNum <= length && count < end; currentNum++)
        {
            for (int i = 0; i < codewords.size(); i++)
            {
                //System.out.println(currentNum + " " + codewords.get(i) + " " + hammingDist(currentNum, codewords.get(i)));
                if (hammingDist(currentNum, codewords.get(i)) < minDist)
                    continue loop;
            }
            codewords.add(currentNum);
            count++;
            out.print(currentNum);
            if (count % 10 == 0 || count == end)
                out.println();
            else
                out.print(" ");
        }
        out.close();
        System.exit(0);
    }
    
    public static int hammingDist(int num1, int num2)
    {
        String diff = Integer.toBinaryString(num1 ^ num2);
        int numDiff = 0;
        for (int i = 0; i < diff.length(); i++)
            if (diff.substring(i, i + 1).equals("1"))
                numDiff++;
        return numDiff;
    }
    
    /*public static int hammingDist(String str1, String str2)
    {
        int dist = 0, pos1 = 0, pos2 = 0;
        if (str1.length() > str2.length())
        {
            dist = str1.length() - str2.length();
            pos1 = str1.length() - str2.length();
        }
        if (str2.length() > str1.length())
        {
            dist = str2.length() - str1.length();
            pos1 = str2.length() - str1.length();
        }
        while (pos1 < str1.length())
        {
            if (!str1.substring(pos1, pos1 + 1).equals(str2.substring(pos2, pos2 + 1)))
                dist++;
            pos1++;
            pos2++;
        }
        return dist;
    }*/
}