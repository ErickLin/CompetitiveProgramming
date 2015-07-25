/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: spin
*/

import java.io.*;
import java.util.*;

class spin {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("spin.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("spin.out")));
        int[] spds = new int[5];
        int[] numWedges = new int[5];
        int[][] starts = new int[5][5];
        int[][] angles = new int[5][5];
        for (int i = 0; i < 5; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            spds[i] = Integer.parseInt(line.nextToken());
            numWedges[i] = Integer.parseInt(line.nextToken());
            for (int j = 0; j < numWedges[i]; j++) {
                /*
                if (j >= numWedges) {
                    starts[i][j] = -1;
                    ends[i][j] = -1;
                }
                */
                starts[i][j] = Integer.parseInt(line.nextToken());
                angles[i][j] = Integer.parseInt(line.nextToken());
            }
        }
        in.close();
        boolean found = false;
        for (int t = 0; t <= 360; t++) {
            if (t > 0)
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < numWedges[i]; j++) {
                        starts[i][j] = (starts[i][j] + spds[i]) % 360;
                        //System.out.println(i + " " + j + " " + starts[i][j]);
                    }
            if (isValid(starts, angles, numWedges)) {
                found = true;
                out.println(t);
                break;
            }
        }
        if (!found)
            out.println("none");
        out.close();
        System.exit(0);
    }
    
    public static boolean isValid(int[][] starts, int[][] angles, int[] numWedges) {
        int[] j = new int[5];
        for (j[0] = 0; j[0] < numWedges[0]; j[0]++)
            for (j[1] = 0; j[1] < numWedges[1]; j[1]++)
                for (j[2] = 0; j[2] < numWedges[2]; j[2]++)
                    for (j[3] = 0; j[3] < numWedges[3]; j[3]++)
                        loop: for (j[4] = 0; j[4] < numWedges[4]; j[4]++) {
                            int start = 0;
                            int end = 720;
                            for (int i = 0; i < 5; i++) {
                                int _start = starts[i][j[i]];
                                int _end = starts[i][j[i]] + angles[i][j[i]];
                                if (_end < start) {
                                    _start += 360;
                                    _end += 360;
                                }
                                if (_start > end) {
                                    _start -= 360;
                                    _end -= 360;
                                }
                                if (_start > end)
                                    continue loop;
                                if (_end < start)
                                    continue loop;
                                if (_start > start)
                                    start = _start;
                                if (_end < end)
                                    end = _end;
                            }
                            return true;
                        }
        return false;
    }
}
