/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: assign
*/
import java.io.*;
import java.util.*;

class assign
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("assign.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("assign.out")));
        StringTokenizer firstLine = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(firstLine.nextToken());
        int numRelationships = Integer.parseInt(firstLine.nextToken());
        HashMap<Integer,Integer> S = new HashMap<Integer,Integer>();
        HashMap<Integer,Integer> D = new HashMap<Integer,Integer>();
        int possibleAssignments = 0;
        for (int i = 0; i < numRelationships; i++)
        {
            StringTokenizer line = new StringTokenizer(in.readLine());
            String relationship = line.nextToken();
            int num1 = Integer.parseInt(line.nextToken());
            int num2 = Integer.parseInt(line.nextToken());
            if (relationship.equals("S"))
            {
                S.put(num1,num2);
                S.put(num2,num1);
            }
            if (relationship.equals("D"))
            {
                if (S.containsKey(num1) && S.get(num1)==num2)
                {
                    out.println("0");
                    out.close();
                    System.exit(0);
                }
                D.put(num1,num2);
                D.put(num2,num1);
            }
        }
        in.close();
        //for (int i = 0; i < numCows; i++)
        //out.println(possibleAssignments);
        out.close();
        System.exit(0);
    }
}