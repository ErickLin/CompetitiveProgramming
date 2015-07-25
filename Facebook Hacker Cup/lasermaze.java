/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: lasermaze
*/

import java.io.*;
import java.util.*;

class lasermaze {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("laser_maze.txt"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lasermaze.out")));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(line.nextToken());
            int n = Integer.parseInt(line.nextToken());
            char[][] maze = new char[m][n];
            HashSet<Character> wallChars = new HashSet<Character>();
            wallChars.add('#');
            wallChars.add('<');
            wallChars.add('>');
            wallChars.add('^');
            wallChars.add('v');
            boolean[][][] offLimits = new boolean[m][n][4];
            LinkedList<Square> q = new LinkedList<Square>();
            boolean[][][] visited = new boolean[m][n][4];
            for (int row = 0; row < m; row++) {
                String ln = in.readLine();
                for (int col = 0; col < n; col++) {
                    maze[row][col] = ln.charAt(col);
                    if (maze[row][col] == 'S') {
                        q.add(new Square(row, col, 0, 0));
                        visited[row][col][0] = true;
                    }
                }
            }
            for (int row = 0; row < m; row++) {
                for (int col = 0; col < n; col++) {
                    if (maze[row][col] == '<' || maze[row][col] == 'v'
                            || maze[row][col] == '>' || maze[row][col] == '^') {
                        for (int step = 0; step < 4; step++) {
                            if ((maze[row][col] == '<' && step == 0)
                                    || (maze[row][col] == 'v' && step == 1)
                                    || (maze[row][col] == '>' && step == 2)
                                    || (maze[row][col] == '^' && step == 3)) {
                                for (int c = col - 1; c >= 0 && !wallChars.contains(maze[row][c]); c--) {
                                    offLimits[row][c][step] = true;
                                }
                            }
                            if ((maze[row][col] == '^' && step == 0)
                                    || (maze[row][col] == '<' && step == 1)
                                    || (maze[row][col] == 'v' && step == 2)
                                    || (maze[row][col] == '>' && step == 3)) {
                                for (int r = row - 1; r >= 0 && !wallChars.contains(maze[r][col]); r--) {
                                    offLimits[r][col][step] = true;
                                }
                            }
                            if ((maze[row][col] == '>' && step == 0)
                                    || (maze[row][col] == '^' && step == 1)
                                    || (maze[row][col] == '<' && step == 2)
                                    || (maze[row][col] == 'v' && step == 3)) {
                                for (int c = col + 1; c < n && !wallChars.contains(maze[row][c]); c++) {
                                    offLimits[row][c][step] = true;
                                }
                            }
                            if ((maze[row][col] == 'v' && step == 0)
                                    || (maze[row][col] == '>' && step == 1)
                                    || (maze[row][col] == '^' && step == 2)
                                    || (maze[row][col] == '<' && step == 3)) {
                                for (int r = row + 1; r < m && !wallChars.contains(maze[r][col]); r++) {
                                    offLimits[r][col][step] = true;
                                }
                            }
                        }
                    }
                }
            }
            /*
            for (int step = 0; step < 4; step++) {
                for (int row = 0; row < m; row++) {
                    for (int col = 0; col < n; col++) {
                        if (offLimits[row][col][step])
                            System.out.print('X');
                        else
                            System.out.print(maze[row][col]);
                    }
                    System.out.println();
                }
                System.out.println();
            }
            */
            int minDist = 0;
            while (!q.isEmpty()) {
                Square sq = q.pollFirst();
                int step = (sq.step + 1) % 4;
                int row = sq.row;
                int col = sq.col;
                if (maze[row][col] == 'G') {
                    minDist = sq.dist;
                    break;
                }
                for (int dir = 0; dir < 4; dir++) {
                    if (dir == 0) {
                        row = sq.row - 1;
                        col = sq.col;
                        if (row < 0)
                            continue;
                    } else if (dir == 1) {
                        row = sq.row;
                        col = sq.col - 1;
                        if (col < 0)
                            continue;
                    } else if (dir == 2) {
                        row = sq.row + 1;
                        col = sq.col;
                        if (row >= m)
                            continue;
                    } else if (dir == 3) {
                        row = sq.row;
                        col = sq.col + 1;
                        if (col >= n)
                            continue;
                    }
                    if (!visited[row][col][step]) {
                        if (!wallChars.contains(maze[row][col]) && !offLimits[row][col][step]) {
                            q.add(new Square(row, col, step, sq.dist + 1));
                        }
                        visited[row][col][step] = true;
                    }
                }
            }
            out.println("Case #" + i + ": " + (minDist == 0 ? "impossible" : minDist));
        }
        in.close();
        out.close();
        System.exit(0);
    }
    
    public static class Square {
        int row;
        int col;
        int step;
        int dist;

        public Square(int a, int b, int c, int d) {
            this.row = a;
            this.col = b;
            this.step = c;
            this.dist = d;
        }
    }
}
