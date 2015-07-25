/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: auto
*/
import java.io.*;
import java.util.*;

class auto
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("auto.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("auto.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int numWords = Integer.parseInt(line.nextToken());
        int numParts = Integer.parseInt(line.nextToken());
        ArrayList<Word> dict = new ArrayList<Word>(numWords);
        for (int i = 0; i < numWords; i++)
        {
            String word = in.readLine();
            dict.add(new Word(word, i));
        }
        Collections.sort(dict);
        /*(for (int i = 0; i < numWords; i++)
            System.out.println(i + 1 + " " + sortedDict.get(i));*/
        //stores locations of all memoized prefixes
        HashMap<String, Integer> starts = new HashMap<String, Integer>();
        for (int j = 0; j < numParts; j++)
        {
            line = new StringTokenizer(in.readLine());
            int k = Integer.parseInt(line.nextToken());
            String part = line.nextToken();
            int start = -1;
            if (starts.containsKey(part))
                start = starts.get(part);
            else
            {
                //binary search
                int lo = 0, hi = numWords;
                while (lo + 1 < hi)
                {
                    int mid = (lo + hi - 1) / 2;
                    if (dict.get(mid).str.compareTo(part) < 0)
                        lo = mid + 1;
                    else
                    {
                        //if the dictionary word is a valid autocomplete option
                        if (dict.get(mid).str.length() >= part.length() && dict.get(mid).str.substring(0, part.length()).equals(part) &&
                                //check that the preceding word in lexicographical order is not valid
                                (mid == 0 || dict.get(mid - 1).str.length() < part.length() || dict.get(mid - 1).str.compareTo(part) < 0))
                        {
                            starts.put(part, mid);
                            start = mid;
                            break;
                        }
                        else
                            hi = mid + 1;
                    }
                }
            }
            if (start == -1)
                out.println("-1");
            else
            {
                //System.out.println(start + " " + (start + k));
                Word completion;
                if (dict.size() >= start + k)
                {
                    completion = dict.get(start + k - 1);
                    if (completion.str.length() >= part.length() &&
                            completion.str.substring(0, part.length()).equals(part))
                    {
                        out.println(completion.index + 1);
                        continue;
                    }
                }
                out.println("-1");
            }
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    public static class Word implements Comparable<Word>
    {
        int index;
        String str;
        
        public Word(String s, int i)
        {
            index = i;
            str = s;
        }
        
        @Override
        public int compareTo(Word other)
        {
            return str.compareTo(other.str);
        }
    }
}