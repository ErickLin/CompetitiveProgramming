/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: runround
*/
import java.io.*;
import java.util.*;

class runround
{
    //static ArrayList<Integer> digits;
    
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("runround.in"));
        String m = in.readLine();
        in.close();
        int numDigits = m.length();
        ArrayList<Integer> digits = new ArrayList<Integer>(numDigits);
        for (int i = 0; i < numDigits; i++)
        {
            int digit = Integer.parseInt(m.substring(i, i + 1));
            digits.add(digit);
        }
        permute(digits, 0, true, 0);
		//if no runaround number is found, add a decimal place
		/*The lowest runaround number for a certain number of digits
		/ consists of consecutive integers starting at 1.*/
		for (int i = 0; i < numDigits; i++)
			digits.set(i, i + 1);
		digits.add(numDigits + 1);
		permute(digits, 0, true, 0);
    }
	
	//bound describes whether the digit of the given place is bounded below
	//"used" stores occupied digits
    public static void permute(ArrayList<Integer> digits, int place, boolean bound, int used) throws IOException
    {
        int start = 1;
		//attempt the digit of the given place from the input number
		//digit is unoccupied by previous places and does not equal the total number of digits
        if (bound)
        {
			//if the digit is unoccupied and does not equal the number of digits (which leads to a loop)
            if ((used & (1 << digits.get(place))) == 0 && digits.get(place) != digits.size())
            {
				int tempUsed = used;
				used |= (1 << digits.get(place));
            	if (place < digits.size() - 1)
                	permute(digits, place + 1, true, used);
				used = tempUsed;
			}
			start = digits.get(place) + 1;
        }
        for (int i = start; i <= 9; i++)
        {
            //if the digit is already occupied or equals the number of digits (which leads to a loop)
            if ((used & (1 << i)) > 0 || i == digits.size())
                continue;
            int tempDigit = digits.get(place);
            int tempUsed = used;
            digits.set(place, i);
            //System.out.println(Integer.toBinaryString(used));
            used |= (1 << i);
            //System.out.println(Integer.toBinaryString(used));
            if (place >= digits.size() - 1)
            {
                if (runAround(digits))
                    result(digits);
            }
            else
                permute(digits, place + 1, false, used);
            digits.set(place, tempDigit);
            used = tempUsed;
        }
    }
    
    public static boolean runAround(ArrayList<Integer> digits)
    {
        //System.out.println(digits);
        //boolean variable that stores visited places
        int visited = 1;
        //System.out.println(Integer.toBinaryString(visited));
        int place = 0;
        for (int i = 0; i < digits.size(); i++)
        {
            int digit = digits.get(place);
            place += digit;
            //wrapping around the number
            place %= digits.size();
            //if the place has already been visited
            if ((visited & (1 << place)) > 0)
			{
				if (i == digits.size() - 1 && place == 0)
					return true;
				else
                	return false;
			}
            visited |= (1 << place);
            //System.out.println(Integer.toBinaryString(visited));
        }
        return false;
    }
    
    public static void result(ArrayList<Integer> ans) throws IOException
    {
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("runround.out")));
        for (int i = 0; i < ans.size(); i++)
            out.print(ans.get(i));
        out.println();
        out.close();
        System.exit(0);
    }
}
