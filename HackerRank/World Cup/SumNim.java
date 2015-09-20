import java.io.*;
import java.util.*;

public class SumNim {
    static boolean isWin(ArrayList<Integer> game) {
        int nimSum = 0;
        for (int i = 0; i < game.size(); i++) {
            nimSum ^= game.get(i);
        }
        return nimSum == 0;
    }

    static void enumerate(ArrayList<Integer> game, Set<ArrayList<Integer>> win
            , Set<ArrayList<Integer>> lose) {
        /*
        for (int i = 0; i < game.size(); i++) {
            System.out.print(game.get(i) + " ");
        }
        System.out.println();
        */
        if (win.contains(game) || lose.contains(game)) {
            return;
        }
        if (isWin(game)) {
            win.add(game);
        } else {
            lose.add(game);
        }
        for (int i = 0; i < game.size() - 1; i++) {
            if (game.get(i) != 0 && game.get(i + 1) != 0) {
                int first = game.get(i);
                int second = game.get(i + 1);
                int sum = first + second;
                game.set(i, 0);
                game.set(i + 1, sum);
                enumerate(game, win, lose);
                game.set(i, first);
                game.set(i + 1, second);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringTokenizer line = new StringTokenizer(in.readLine());
        ArrayList<Integer> a = new ArrayList<Integer>(n);
        for (int i = 0; i < n; i++) {
            a.add(Integer.parseInt(line.nextToken()));
        }
        Set<ArrayList<Integer> > win = new HashSet<ArrayList<Integer>>();
        Set<ArrayList<Integer> > lose = new HashSet<ArrayList<Integer>>();
        enumerate(a, win, lose);
        System.out.println(win.size());
    }
}
