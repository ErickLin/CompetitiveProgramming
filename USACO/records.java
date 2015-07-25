/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: records
*/
import java.io.*;
import java.util.*;

class records
{
    static BufferedReader in;
    static PrintWriter out;
    static int hours, maxOccurrences;
    static ArrayList<Group> groups;
    
    static class Group
    {
        private ArrayList<String> names;
        private int occurrences;
        public Group(ArrayList<String> nms)
        {
            names = nms;
            occurrences = 1;
        }
        public int getOccurrences()
        {
            return occurrences;
        }
        public boolean equals(ArrayList<String> nms)
        {
            if (names.containsAll(nms) && nms.containsAll(names))
                return true;
            else
                return false;
        }
        public void increment()
        {
            occurrences += 1;
            if (occurrences > maxOccurrences)
                    maxOccurrences = occurrences;
        }
    }
    
    public static void main (String[] args) throws IOException
    {
        in = new BufferedReader(new FileReader("records.in"));
        out = new PrintWriter(new BufferedWriter(new FileWriter("records.out")));
        hours = Integer.parseInt(in.readLine());
        maxOccurrences = 0;
        groups = new ArrayList<Group>();
        for (int hour = 1; hour <= hours; hour++)
        {
            analyzeNextGroup();
        }
        in.close();
        out.println(Integer.toString(maxOccurrences));
        out.close();
        System.exit(0);
    }
    
    public static void analyzeNextGroup() throws IOException
    {
        StringTokenizer currentLine = new StringTokenizer(in.readLine());
        ArrayList<String> names = new ArrayList<String>(3);
        for (int cow = 0; cow < 3; cow++)
        {
            names.add(currentLine.nextToken());
        }
        boolean groupExists = false;
        for (Group group: groups)
        {
            if (group.equals(names))
            {
                groupExists = true;
                group.increment();
            }
        }
        if (!groupExists)
        {
            groups.add(new Group(names));
        }
    }
}

