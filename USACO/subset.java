/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: subset
*/
import java.io.*;
import java.util.*;

class subset
{
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new FileReader("subset.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("subset.out")));
        int n = Integer.parseInt(in.readLine());
        in.close();
        int sum = n * (n + 1) / 2;
        //if the sum of all the integers is even
        if (sum % 2 == 0)
        {
            //better way using only one dimension for state array
            long dp[] = new long[sum + 1];
            //there is 1 way to have a sum of 0, by using no numbers
            dp[0] = 1;
            //initialize all other possible sums to 0
            for (int s = 1; s <= sum; s++)
                dp[s] = 0;
            for (int k = 1; k <= n; k++)
                //work backwards from maximum sum so nothing gets counted twice
                for (int s = sum; s >= 0; s--)
                    if (dp[s] > 0 && s + k <= sum)
                        dp[s + k] += dp[s];
            //divide answer by two because possible subsets are paired up
            out.println(dp[sum / 2] / 2);
            /*
            long dp[][] = new long[n + 1][sum + 1];
            //1 way to have a set of size 1 and sum equal to 1
            dp[1][1] = 1;
            //compute for all subproblems of sets with size k
            for (int k = 2; k <= n; k++)
            {
                //number of ways to sum up to s using integers from 1 to k
                for (int s = 1; s <= k * (k + 1) / 2; s++)
                {
                    //larger set size contains all possible combinations from smaller set size
                    dp[k][s] = dp[k - 1][s];
                    //the subset contains just the number k
                    if (s == k)
                        dp[k][s]++;
                    //add up memoized ways from before k is added
                    if (s > k)
                        dp[k][s] += dp[k - 1][s - k];
                    //System.out.print(dp[k][s] + " ");
                }
                //System.out.println();
            }
            //two subsets, each with half the total sum, per solution
            out.println(dp[n][sum / 2] / 2);
            */
        }
        else
            //cannot divide an odd sum into two equal subsets!
            out.println("0");
        out.close();
        System.exit(0);
    }
}