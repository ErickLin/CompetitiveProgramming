package Fall_09_27_14;

import java.io.*;
import java.util.*;

class A {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        boolean[][] hasQueen = new boolean[8][8];
        HashSet<Integer> rows = new HashSet<Integer>();
        HashSet<Integer> cols = new HashSet<Integer>();
        boolean valid = true;
        loop: for (int i = 0; i < 8; i++) {
            String line = in.readLine();
            for (int j = 0; j < 8; j++)
                if (line.substring(j, j + 1).equals("*")) {
                    if (rows.contains(i)) {
                        valid = false;
                        System.out.println("invalid");
                        break loop;
                    }
                    if (cols.contains(j)) {
                        valid = false;
                        System.out.println("invalid");
                        break loop;
                    }
                    hasQueen[i][j] = true;
                    rows.add(i);
                    cols.add(j);
                }
        }
        in.close();
        if (valid) {
            for (int r = 0; r < 8; r++) {
                int row = r;
                int col = 0;
                boolean found = false;
                while (row < 8) {
                    if (hasQueen[row][col]) {
                        if (found) {
                            valid = false;
                            System.out.println("invalid");
                            break;
                        }
                        else {
                            found = true;
                        }
                    }
                    row++;
                    col++;
                }
            }
        }
        if (valid) {
            for (int c = 0; c < 8; c++) {
                int row = 0;
                int col = c;
                boolean found = false;
                while (col < 8) {
                    if (hasQueen[row][col]) {
                        if (found) {
                            valid = false;
                            System.out.println("invalid");
                            break;
                        }
                        else {
                            found = true;
                        }
                    }
                    row++;
                    col++;
                }
            }
        }
        if (valid) {
            for (int r = 0; r < 8; r++) {
                int row = r;
                int col = 7;
                boolean found = false;
                while (row < 8 && col >= 0) {
                    if (hasQueen[row][col]) {
                        if (found) {
                            valid = false;
                            System.out.println("invalid");
                            break;
                        }
                        else {
                            found = true;
                        }
                    }
                    row++;
                    col--;
                }
            }
        }
        if (valid) {
            for (int c = 0; c < 8; c++) {
                int row = 0;
                int col = c;
                boolean found = false;
                while (row < 8 && col >= 0) {
                    if (hasQueen[row][col]) {
                        if (found) {
                            valid = false;
                            System.out.println("invalid");
                            break;
                        }
                        else {
                            found = true;
                        }
                    }
                    row++;
                    col--;
                }
            }
        }
        if (valid)
            System.out.println("valid");
        System.exit(0);
    }
}
