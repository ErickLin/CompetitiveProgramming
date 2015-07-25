/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: D
*/

package Fall_09_27_14;

import java.io.*;
import java.util.*;

class D {
    static int MAX = 99999999;
    static int[][] dists;
    static ArrayList<ArrayList<Integer>> neighbors;
    
    public static void main(String[] args) throws IOException {
        dists = new int[1 << 9][1 << 9];
        neighbors = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < 1 << 9; i++) {
            neighbors.add(new ArrayList<Integer>());
            for (int j = 0; j < 1 << 9; j++) {
                if (i == j)
                    dists[i][j] = 0;
                else
                    dists[i][j] = MAX;
            }
        }
        gen(0, 0);
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int trials = new Integer(in.readLine());
        for (int i = 0; i < trials; i++) {
            int initState = 0;
            for (int row = 0; row < 3; row++) {
                String line = in.readLine();
                for (int col = 0; col < 3; col++) {
                    if (line.substring(col, col + 1).equals("*"))
                        initState |= 1 << (row * 3 + col);
                }
            }
            bfs();
            System.out.println(dists[initState][0]);
        }
        in.close();
        System.exit(0);
    }
    
    public static void gen(int cell, int state) {
        if (cell >= 9)
            return;
        for (int cellTog = 0; cellTog < 9; cellTog++) {
            dists[state][toggle(state, cellTog)] = 1;
            neighbors.get(state).add(toggle(state, cellTog));
        }
        gen(cell + 1, state);
        int newState = state | (1 << cell);
        for (int cellTog = 0; cellTog < 9; cellTog++) {
            dists[newState][toggle(newState, cellTog)] = 1;
            neighbors.get(newState).add(toggle(newState, cellTog));
        }
        gen(cell + 1, newState);
    }
    
    public static int toggle(int state, int cell) {
        state ^= 1 << cell;
        if (cell != 0 && cell != 3 && cell != 6)
            state ^= 1 << (cell - 1);
        if (cell - 3 >= 0)
            state ^= 1 << (cell - 3);
        if (cell != 2 && cell != 5 && cell != 8)
            state ^= 1 << (cell + 1);
        if (cell + 3 < 9)
            state ^= 1 << (cell + 3);
        return state;
    }
    
    public static void bfs()
    {
        PriorityQueue<Integer> worlds = new PriorityQueue<Integer>(1 << 9, new Comparator<Integer>(){
            @Override
            public int compare(Integer a, Integer b)
            {
                return new Integer(dists[a][0]).compareTo(dists[b][0]);
            }
        });
        for (int state = 0; state < 1 << 9; state++)
            worlds.add(state);
        while (worlds.size() > 0)
        {
            int state = worlds.poll();
            //System.out.println((vertex + 1) + " " + neighbors.get(vertex));
            //update distances for all states that are one move away from the current state
            for (int neighbor : neighbors.get(state))
                if (dists[neighbor][0] > dists[state][0] + dists[neighbor][state])
                {
                    dists[neighbor][0] = dists[state][0] + dists[neighbor][state];
                    //decrease-key
                    worlds.remove(neighbor);
                    worlds.add(neighbor);
                }
        }
    }
}
