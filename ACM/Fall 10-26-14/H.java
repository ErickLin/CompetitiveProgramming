package fall_10_26_14;

import java.io.*;
import java.util.*;

public class H {
    static int[][] objs, distsToWall, nWalls, sWalls, wWalls, eWalls, dists;
    static boolean[][] distsToWallVisited, distsVisited;
    static final int iMultiplier = 1002;
    
    public static void main(String[] args) throws IOException {
        /*
        for (int i = 0; i < 750; i++) {
            for (int j = 0; j < 750; j++) {
                System.out.print(".");
            }
            System.out.println();
        }
        */
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer line = new StringTokenizer(in.readLine());
        int r = Integer.parseInt(line.nextToken()) + 2;
        int c = Integer.parseInt(line.nextToken()) + 2;
        double t = System.currentTimeMillis();
        int startRow = 0;
        int startCol = 0;
        int endRow = 0;
        int endCol = 0;
        objs = new int[r][c];
        distsToWall = new int[r][c];
        nWalls = new int[r][c];
        sWalls = new int[r][c];
        wWalls = new int[r][c];
        eWalls = new int[r][c];
        dists = new int[r][c];
        distsToWallVisited = new boolean[r][c];
        distsVisited = new boolean[r][c];
        LinkedList<Integer> squaresByDistToWall = new LinkedList<Integer>();
        //read input and initialize arrays
        for (int i = 0; i < r; i++) {
            //double t2 = System.currentTimeMillis();
            for (int j = 0; j < c; j++) {
                if (i != 0 && j != 0 && i != r - 1 && j != c - 1) {
                    char obj = (char) in.read();
                    if (obj == 'S') {
                        objs[i][j] = 2;
                        startRow = i;
                        startCol = j;
                    }
                    else if (obj == 'C') {
                        objs[i][j] = 3;
                        endRow = i;
                        endCol = j;
                    } else if (obj != '#')
                        objs[i][j] = 1;
                }
                if (objs[i][j] == 0) {
                    distsToWallVisited[i][j] = true;
                    squaresByDistToWall.add(i * iMultiplier + j);
                } else {
                    distsToWall[i][j] = 99999999;
                }
                if (objs[i][j] != 2) {
                    dists[i][j] = 999999999;
                }
            }
            if (i != 0 && i != r - 1)
                //skip the \n symbol
                in.skip(1);
            //System.out.println(i + " " + (System.currentTimeMillis() - t2));
        }
        //flood-fill distance to nearest wall for every square, starting with walls
        while (!squaresByDistToWall.isEmpty()) {
            int next = squaresByDistToWall.poll();
            //read from hash function
            int row = next / iMultiplier;
            int col = next % iMultiplier;
            if (row > 0 && !distsToWallVisited[row - 1][col]) {
                distsToWall[row - 1][col] = distsToWall[row][col] + 1;
                distsToWallVisited[row - 1][col] = true;
                squaresByDistToWall.add((row - 1) * iMultiplier + col);
            }
            if (col > 0 && !distsToWallVisited[row][col - 1]) {
                distsToWall[row][col - 1] = distsToWall[row][col] + 1;
                distsToWallVisited[row][col - 1] = true;
                squaresByDistToWall.add(row * iMultiplier + col - 1);
            }
            if (row < r - 1 && !distsToWallVisited[row + 1][col]) {
                distsToWall[row + 1][col] = distsToWall[row][col] + 1;
                distsToWallVisited[row + 1][col] = true;
                squaresByDistToWall.add((row + 1) * iMultiplier + col);
            }
            if (col < r - 1 && !distsToWallVisited[row][col + 1]) {
                distsToWall[row][col + 1] = distsToWall[row][col] + 1;
                distsToWallVisited[row][col + 1] = true;
                squaresByDistToWall.add(row * iMultiplier + col + 1);
            }
        }
        //set row/column of most immediate wall in all four cardinal directions for each square
        for (int i = 0; i < r; i++) {
            int wWall = 0;
            for (int j = 0; j < c; j++) {
                if (objs[i][j] == 0)
                    wWall = j;
                wWalls[i][j] = wWall;
            }
            int eWall = c - 1;
            for (int j = c - 1; j >= 0; j--) {
                if (objs[i][j] == 0)
                    eWall = j;
                eWalls[i][j] = eWall;
            }
        }
        for (int j = 0; j < c; j++) {
            int nWall = 0;
            for (int i = 0; i < r; i++) {
                if (objs[i][j] == 0)
                    nWall = i;
                nWalls[i][j] = nWall;
            }
            int sWall = r - 1;
            for (int i = r - 1; i >= 0; i--) {
                if (objs[i][j] == 0)
                    sWall = i;
                sWalls[i][j] = sWall;
            }
        }
        in.close();
        PriorityQueue<Integer> squaresByDist = new PriorityQueue<Integer>(r * c, new Comparator<Integer>() {
            @Override
            public int compare(Integer s1, Integer s2) {
                int row1 = s1 / iMultiplier;
                int col1 = s1 % iMultiplier;
                int row2 = s2 / iMultiplier;
                int col2 = s2 % iMultiplier;
                return new Integer(dists[row1][col1]).compareTo(dists[row2][col2]);
            }
        });
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (objs[i][j] != 0)
                    squaresByDist.add(i * iMultiplier + j);
        //Dijkstra for all non-wall squares
        while (!distsVisited[endRow][endCol]) {
            int next = squaresByDist.poll();
            //read from hash function
            int row = next / iMultiplier;
            int col = next % iMultiplier;
            if (row > 0 && objs[row - 1][col] != 0 && dists[row][col] + 1 < dists[row - 1][col]) {
                dists[row - 1][col] = dists[row][col] + 1;
                squaresByDist.remove((row - 1) * iMultiplier + col);
                squaresByDist.add((row - 1) * iMultiplier + col);
            }
            if (col > 0 && objs[row][col - 1] != 0 && dists[row][col] + 1 < dists[row][col - 1]) {
                dists[row][col - 1] = dists[row][col] + 1;
                squaresByDist.remove(row * iMultiplier + col - 1);
                squaresByDist.add(row * iMultiplier + col - 1);
            }
            if (row < r - 1 && objs[row + 1][col] != 0 && dists[row][col] + 1 < dists[row + 1][col]) {
                dists[row + 1][col] = dists[row][col] + 1;
                squaresByDist.remove((row + 1) * iMultiplier + col);
                squaresByDist.add((row + 1) * iMultiplier + col);
            }
            if (col < r - 1 && objs[row][col + 1] != 0 && dists[row][col] + 1 < dists[row][col + 1]) {
                dists[row][col + 1] = dists[row][col] + 1;
                squaresByDist.remove(row * iMultiplier + col + 1);
                squaresByDist.add(row * iMultiplier + col + 1);
            }
            if (dists[row][col] + distsToWall[row][col] < dists[nWalls[row][col] + 1][col]) {
                dists[nWalls[row][col] + 1][col] = dists[row][col] + distsToWall[row][col];
                squaresByDist.remove((nWalls[row][col] + 1) * iMultiplier + col);
                squaresByDist.add((nWalls[row][col] + 1) * iMultiplier + col);
            }
            if (dists[row][col] + distsToWall[row][col] < dists[sWalls[row][col] - 1][col]) {
                dists[sWalls[row][col] - 1][col] = dists[row][col] + distsToWall[row][col];
                squaresByDist.remove((sWalls[row][col] - 1) * iMultiplier + col);
                squaresByDist.add((sWalls[row][col] - 1) * iMultiplier + col);
            }
            if (dists[row][col] + distsToWall[row][col] < dists[row][wWalls[row][col] + 1]) {
                dists[row][wWalls[row][col] + 1] = dists[row][col] + distsToWall[row][col];
                squaresByDist.remove(row * iMultiplier + wWalls[row][col] + 1);
                squaresByDist.add(row * iMultiplier + wWalls[row][col] + 1);
            }
            if (dists[row][col] + distsToWall[row][col] < dists[row][eWalls[row][col] - 1]) {
                dists[row][eWalls[row][col] - 1] = dists[row][col] + distsToWall[row][col];
                squaresByDist.remove(row * iMultiplier + eWalls[row][col] - 1);
                squaresByDist.add(row * iMultiplier + eWalls[row][col] - 1);
            }
            distsVisited[row][col] = true;
        }
        System.out.println(dists[endRow][endCol]);
        System.exit(0);
    }
    
    /*
    public static class Square {// implements Comparable<Square> {
        int row, col, type, distToWall, nWall, sWall, wWall, eWall, dist;
        boolean distToWallVisited, distVisited;
        
        public Square(int x, int y, int type) {
            this.row = x;
            this.col = y;
            this.type = type;
            if (type == 0) {
                distToWall = 0;
                distToWallVisited = true;
            }
            else {
                distToWall = 99999999;
                distToWallVisited = false;
            }
            //starting square
            if (type == 2)
                dist = 0;
            else
                dist = 99999999;
            distVisited = false;
        }
        
        /*
        @Override
        public int compareTo(Square other) {
            return new Integer(distToWall).compareTo(other.distToWall);
        }
        
        @Override
        public String toString() {
            return "(" + row + "," + col + ") " + type + " " + distToWall
                    + " [" + nWall + " " + sWall + " " + wWall + " " + eWall
                    + "] " + dist;
        }
    }
    */
}
