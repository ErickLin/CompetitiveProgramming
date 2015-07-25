/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: calfflac
*/
import java.io.*;
import java.util.*;

class calfflac
{
    static int longestLength, longestStart, longestEnd;
    static String text;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("calfflac.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("calfflac.out")));
        text = "";
        ArrayList<String> splitText = new ArrayList<String>();
        String line;
        while ((line = in.readLine()) != null)
        {
            text += line;
            splitText.add(line);
        }
        in.close();
        /*System.out.println(text);
        for (String ln : splitText)
            System.out.println(ln);*/
        longestLength = 0;
        longestStart = 0;
        longestEnd = 0;
        //find palindromes with central points at letters
        for (int i = 1; i < text.length() - 1; i++)
        {
            if (!Character.isLetter(text.charAt(i)))
                continue;
            processPalindrome(i - 1, i + 1);
        }
        //find palindromes with central points between letters
        for (int i = 0; i < text.length() - 1; i++)
        {
            if (!Character.isLetter(text.charAt(i)) || !Character.isLetter(text.charAt(i + 1)))
                continue;
            processPalindrome(i, i + 1);
        }
        //System.out.println(longestStart + " " + longestEnd);
        out.println(longestLength);
        if (longestStart / 80 == longestEnd / 80)
            out.println(text.substring(longestStart, longestEnd + 1));
        else
        {
            out.println(splitText.get(longestStart / 80).substring(longestStart % 80, 80));
            for (int i = longestStart / 80 + 1; i < longestEnd / 80; i++)
                out.println(splitText.get(i));
            if (longestEnd % 80 == 0)
                out.println(splitText.get(longestEnd / 80));
            else
                out.println(splitText.get(longestEnd / 80).substring(0, longestEnd % 80 + 1));
        }
        out.close();
        System.exit(0);
    }
    
    public static void processPalindrome(int start, int end)
    {
        int currentLength = end - start - 1;
        do
        {
            while (!Character.isLetter(text.charAt(start)))
            {
                if (start > 0)
                    start--;
                //if outside the string bounds, no palindrome can be made
                else
                    return;
            }
            while (!Character.isLetter(text.charAt(end)))
            {
                if (end < text.length() - 1)
                    end++;
                else
                    return;
            }
            if (Character.toUpperCase(text.charAt(start)) == Character.toUpperCase(text.charAt(end)))
            {
                currentLength += 2;
                if (currentLength > longestLength)
                {
                    longestLength = currentLength;
                    longestStart = start;
                    longestEnd = end;
                    //System.out.println(text.charAt(start) + " " + text.charAt(end) + " " + longestLength + " " + longestStart + " " + longestEnd);
                }
                start--;
                end++;
            }
            else
                return;
        }
        while (start >= 0 && end < text.length());
    }
}