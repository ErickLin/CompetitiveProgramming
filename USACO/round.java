/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: round
*/

import java.io.*;
import java.util.*;

class round {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("round.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("round.out")));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int n;
        while ((n = Integer.parseInt(line.nextToken())) != 0) {
            int t = Integer.parseInt(line.nextToken());
            int[] output = playGame(n, t);
            out.println(output[0] + " " + output[1]);
            line = new StringTokenizer(in.readLine());
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    public static int[] playGame(int n, int t) {
        ArrayList<Integer> players = new ArrayList<Integer>(n);
        for (int i = 0; i < n; i++)
            players.add(0);
        int currentPlayer = 0;
        do {
            for (int i = 0; i < players.size(); i++) {
                players.set(i, players.get(i) + t / players.size());
            }
            currentPlayer = (currentPlayer + t % players.size() - 1) % players.size();
            if (currentPlayer < 0)
                currentPlayer += players.size();
            for (int i = currentPlayer; i > currentPlayer - t % players.size(); i--) {
                int index = i >= 0 ? i : i + players.size();
                players.set(index, players.get(index) + 1);
            }
            players.remove(players.get(currentPlayer));
        } while (!done(players));
        int[] output = new int[2];
        output[0] = players.size();
        output[1] = players.get(0);
        return output;
    }
    
    public static boolean done(ArrayList<Integer> players) {
        for (int i = 1; i < players.size(); i++)
            if (!players.get(i).equals(players.get(i - 1)))
                return false;
        return true;
    }
}
