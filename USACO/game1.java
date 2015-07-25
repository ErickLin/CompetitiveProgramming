/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: game1
*/

import java.io.*;
import java.util.*;

class game1 {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("game1.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("game1.out")));
        int n = Integer.parseInt(in.next());
        LinkedList<Integer> board = new LinkedList<Integer>();
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int a = Integer.parseInt(in.next());
            board.add(a);
            sum += a;
        }
        in.close();
        //int diff = max(board);
        int[][] dp = new int[n + 1][n];
        for (int i = 0; i < n; i++)
            dp[1][i] = board.pollFirst();
        for (int size = 2; size <= n; size++)
            for (int i = 0; i < n - size + 1; i++) {
                dp[size][i] = Math.max(dp[1][i] - dp[size - 1][i + 1]
                        , -dp[size - 1][i] + dp[1][i + size - 1]);
            }
        int diff = dp[n][0];
        out.println(((sum + diff) / 2) + " " + ((sum + diff) / 2 - diff));
        out.close();
        System.exit(0);
    }

    /*
    public static int max(LinkedList<Integer> oldBoard) {
        LinkedList<Integer> board1 = new LinkedList<Integer>(oldBoard);
        int a = board1.pollFirst();
        if (board1.size() == 0)
            return a;
        LinkedList<Integer> board2 = new LinkedList<Integer>(oldBoard);
        int b = board2.pollLast();
        return Math.max(a - max(board1), b - max(board2));
    }
    */
}
