/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: ride
*/
import java.io.*;

class ride
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("ride.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("ride.out")));
        String cometName = in.readLine();
        String groupName = in.readLine();
        in.close();
        if (isMatching(cometName, groupName))
            out.println("GO");
        else
            out.println("STAY");
        out.close();
        System.exit(0);
    }
    
    public static boolean isMatching(String str1, String str2)
    {
        int value1 = 1, value2 = 1;
        for (int i = 0; i < str1.length(); i++)
        {
            value1 *= (int)(str1.charAt(i))-64;
        }
        for (int i = 0; i < str2.length(); i++)
        {
            value2 *= (int)(str2.charAt(i))-64;
        }
        return (value1 % 47) == (value2 % 47);
    }
}
