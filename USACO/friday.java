/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: friday
*/

import java.io.*;

class friday
{
    static int dayOfWeek, numYears;
    static int[] instPerDayOfWeek;
    
    public static void main(String[] args) throws IOException
    {
        //Monday
        dayOfWeek = 1;
        BufferedReader in = new BufferedReader(new FileReader("friday.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("friday.out")));
        numYears = Integer.parseInt(in.readLine());
        instPerDayOfWeek = new int[]{0, 0, 0, 0, 0, 0, 0};
        for (int year = 1900; year < numYears + 1900; year++)
        {
            for (int month = 1; month <= 12; month++)
            {
                int daysInMonth;
                if (month == 4 || month == 6 || month == 9 || month == 11)
                    daysInMonth = 30;
                else if (month == 2)
                {
                    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                        daysInMonth = 29;
                    else
                        daysInMonth = 28;
                }
                else
                    daysInMonth = 31;
                for (int dayOfMonth = 1; dayOfMonth <= daysInMonth; dayOfMonth++)
                {
                    if (dayOfMonth == 13)
                        instPerDayOfWeek[dayOfWeek - 1]++;
                    if (dayOfWeek < 7)
                        dayOfWeek++;
                    else
                        dayOfWeek = 1;
                }
            }
        }
        in.close();
        out.println(instPerDayOfWeek[5] + " " + instPerDayOfWeek[6] + " " + instPerDayOfWeek[0] + " " + instPerDayOfWeek[1] + " " + instPerDayOfWeek[2] + " " + instPerDayOfWeek[3] + " " + instPerDayOfWeek[4]);
        out.close();
        System.exit(0);
    }
}
