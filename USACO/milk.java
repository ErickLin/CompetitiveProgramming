/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: milk
*/
import java.io.*;
import java.util.*;

class milk
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("milk.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milk.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int galsReq = Integer.parseInt(line.nextToken());
        int numSup = Integer.parseInt(line.nextToken());
        TreeMap<Integer,Integer> suppliers = new TreeMap<Integer,Integer>(new Comparator<Integer>()
        {
            @Override
            public int compare(Integer a, Integer b)
            {
                return a.compareTo(b);
            }
        });
        for (int i = 0; i < numSup; i++)
        {
            line = new StringTokenizer(in.readLine());
            int pricePerGal = Integer.parseInt(line.nextToken());
            int amt = Integer.parseInt(line.nextToken());
            if (suppliers.get(pricePerGal) == null)
                suppliers.put(pricePerGal, amt);
            else
                suppliers.put(pricePerGal, suppliers.get(pricePerGal) + amt);
        }
        in.close();
        int minPrice = 0;
        /*System.out.println(suppliers.size());
        for (Map.Entry<Integer, Integer> entry: suppliers.entrySet())
        {
            System.out.println(entry.getKey() + " " + entry.getValue());
        }*/
        outLoop: for (Map.Entry<Integer, Integer> entry: suppliers.entrySet())
        {
            for (int i = 0; i < entry.getValue(); i++)
            {
                minPrice += entry.getKey();
                galsReq--;
                if (galsReq <= 0)
                {
                    break outLoop;
                }
            }
        }
        out.println(minPrice);
        out.close();
        System.exit(0);
    }
}