/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: photo
*/
import java.io.*;
import java.util.*;

class photo0
{
    static ArrayList<ArrayList<Integer>> allIDs;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("photo0.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("photo0.out")));
        int numCows = Integer.parseInt(in.readLine());
        allIDs = new ArrayList<ArrayList<Integer>>(5);
        for (int photo = 0; photo < 5; photo++)
        {
            ArrayList<Integer> IDsInPhoto = new ArrayList<Integer>(numCows);
            for (int pos = 0; pos < numCows; pos++)
                IDsInPhoto.add(Integer.parseInt(in.readLine()));
            allIDs.add(IDsInPhoto);
        }
        in.close();
        ArrayList<Integer> IDs = new ArrayList<Integer>(numCows);
        for (int i = 0; i < allIDs.get(0).size(); i++)
            IDs.add(new Integer(allIDs.get(0).get(i)));
        /*for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < numCows; j++)
                System.out.print(allIDs.get(i).get(j) + " ");
            System.out.println();
        }*/
        Collections.sort(IDs, new Comparator<Integer>()
        {
            @Override
            public int compare(Integer a, Integer b)
            {
                int compareNum = 0;
                for (int i = 0; i < 5; i++)
                {
                    compareNum += new Integer(allIDs.get(i).indexOf(a)).compareTo(allIDs.get(i).indexOf(b));
                    if (Math.abs(compareNum) >= 3)
                        break;
                }
                return new Integer(compareNum).compareTo(0);
            }
        });
        for (int i = 0; i < IDs.size(); i++)
            out.println(IDs.get(i));
        out.close();
        System.exit(0);
    }
}