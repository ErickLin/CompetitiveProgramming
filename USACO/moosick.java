/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: moosick
*/
import java.io.*;
import java.util.*;

class moosick
{
    static int songLength, chordLength, numChords;
    static int[] songNotes, chordNotes;
    static ArrayList<Integer> startLocs;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("moosick.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("moosick.out")));
        songLength = Integer.parseInt(in.readLine());
        songNotes = new int[songLength];
        for (int i = 0; i < songLength; i++)
            songNotes[i] = Integer.parseInt(in.readLine());
        chordLength = Integer.parseInt(in.readLine());
        chordNotes = new int[chordLength];
        for (int i = 0; i < chordLength; i++)
            chordNotes[i] = Integer.parseInt(in.readLine());
        in.close();
        sort(0, chordNotes.length - 1, chordNotes);
        numChords = 0;
        startLocs = new ArrayList<Integer>();
        outer: for (int songLoc = 0; songLoc <= songLength - chordLength; songLoc++)
        {
            //System.out.println("\n" + songLoc);
            int[] sectionNotes = new int[chordLength];
            for (int i = 0; i < chordLength; i++)
            {
                sectionNotes[i] = songNotes[songLoc + i];
            }
            sort(0, sectionNotes.length - 1, sectionNotes);
            /*for (int i = 0; i < chordNotes.length; i++)
                System.out.print(sectionNotes[i]);
            System.out.print(" ");
            for (int i = 0; i < chordNotes.length; i++)
                System.out.print(chordNotes[i]);*/
            for (int chordLoc = 0; chordLoc < chordLength - 1; chordLoc++)
                if (sectionNotes[chordLoc + 1] - sectionNotes[chordLoc] != chordNotes[chordLoc + 1] - chordNotes[chordLoc])
                    continue outer;
            startLocs.add(songLoc);
            numChords++;
        }
        out.println(numChords);
        for (int loc = 0; loc < startLocs.size(); loc++)
            out.println(startLocs.get(loc) + 1);
        out.close();
        System.exit(0);
    }
    
    public static void sort(int low, int high, int[] array)
    {
        int i = low, j = high, pivot = array[low + (high - low) / 2];
        while (i <= j)
        {
            while (array[i] < pivot)
                i++;
            while (array[j] > pivot)
                j--;
            if (i <= j)
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
        if (low < j)
            sort(low, j, array);
        if (i < high)
            sort(i, high, array);
    }
}