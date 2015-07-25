/*
ID: Jugglebrosjr2
LANG: JAVA
TASK: fence6
*/

import java.io.*;
import java.util.*;

class fence6 {
    static int[] dists;

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("fence6.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence6.out")));
        int n = Integer.parseInt(in.readLine());
        HashMap<Integer, Integer> nums = new HashMap<Integer, Integer>();
        HashMap<Integer, Integer> indices = new HashMap<Integer, Integer>();
        ArrayList<Line> lines = new ArrayList<Line>();
        for (int i = 0; i < n; i++) {
            StringTokenizer line = new StringTokenizer(in.readLine());
            int s = Integer.parseInt(line.nextToken());
            nums.put(lines.size(), s);
            indices.put(s, lines.size());
            int l = Integer.parseInt(line.nextToken());
            int n1 = Integer.parseInt(line.nextToken());
            int n2 = Integer.parseInt(line.nextToken());
            line = new StringTokenizer(in.readLine());
            HashSet<Integer> neighbors1 = new HashSet<Integer>();
            for (int j = 0; j < n1; j++) {
                neighbors1.add(Integer.parseInt(line.nextToken()));
            }
            line = new StringTokenizer(in.readLine());
            HashSet<Integer> neighbors2 = new HashSet<Integer>();
            for (int j = 0; j < n2; j++) {
                neighbors2.add(Integer.parseInt(line.nextToken()));
            }
            lines.add(new Line(s, l, neighbors1, neighbors2));
        }
        in.close();
        int minPerimeter = Integer.MAX_VALUE;
        for (int numLines = n; numLines > 0; numLines--) {
            ArrayList<Line> tempLines = new ArrayList<Line>(numLines);
            for (int i = 0; i < numLines; i++)
                tempLines.add(new Line(lines.get(i)));
            dists = new int[numLines];
            PriorityQueue<Integer> q = new PriorityQueue<Integer>(numLines, new Comparator<Integer>() {
                @Override
                public int compare(Integer n1, Integer n2) {
                    if (dists[n1] == 0)
                        return 1;
                    else if (dists[n2] == 0)
                        return -1;
                    else return new Integer(dists[n1]).compareTo(dists[n2]);
                }
            });
            int nodeIndex = numLines - 1;
            int node = nums.get(nodeIndex);
            for (int neighbor : tempLines.get(nodeIndex).neighbors1) {
                int neighborIndex = indices.get(neighbor);
                if (neighborIndex < numLines) {
                    dists[neighborIndex] = tempLines.get(neighborIndex).length;
                    q.add(neighborIndex);
                    tempLines.get(nodeIndex).neighbors.remove(neighbor);
                    tempLines.get(neighborIndex).neighbors.remove(node);
                }
            }
            while (!q.isEmpty()) {
                nodeIndex = q.poll();
                node = nums.get(nodeIndex);
                for (int neighbor : tempLines.get(nodeIndex).neighbors1) {
                    int neighborIndex = indices.get(neighbor);
                    if (neighborIndex < numLines && tempLines.get(nodeIndex).neighbors.contains(neighbor)) {
                        if (dists[neighborIndex] > dists[nodeIndex] + tempLines.get(neighborIndex).length
                                || dists[neighborIndex] == 0) {
                            dists[neighborIndex] = dists[nodeIndex] + tempLines.get(neighborIndex).length;
                            q.remove(neighborIndex);
                            q.add(neighborIndex);
                        }
                        tempLines.get(nodeIndex).neighbors.remove(neighbor);
                        tempLines.get(neighborIndex).neighbors.remove(node);
                    }
                }
                for (int neighbor : tempLines.get(nodeIndex).neighbors2) {
                    int neighborIndex = indices.get(neighbor);
                    if (neighborIndex < numLines && tempLines.get(nodeIndex).neighbors.contains(neighbor)) {
                        q.add(neighborIndex);
                        if (dists[neighborIndex] > dists[nodeIndex] + tempLines.get(neighborIndex).length
                                || dists[neighborIndex] == 0) {
                            dists[neighborIndex] = dists[nodeIndex] + tempLines.get(neighborIndex).length;
                        }
                        tempLines.get(nodeIndex).neighbors.remove(neighbor);
                        tempLines.get(neighborIndex).neighbors.remove(node);
                    }
                }
            }
            //System.out.println(nums.get(numLines - 1) + " " + dists[numLines - 1]);
            if (dists[numLines - 1] != 0 && dists[numLines - 1] < minPerimeter) {
                minPerimeter = dists[numLines - 1];
            }
        }
        out.println(minPerimeter);
        out.close();
        System.exit(0);
    }

    private static class Line {
        int length;
        HashSet<Integer> neighbors1;
        HashSet<Integer> neighbors2;
        HashSet<Integer> neighbors;

        public Line(int s, int l, HashSet<Integer> n1, HashSet<Integer> n2) {
            length = l;
            neighbors1 = n1;
            neighbors2 = n2;
            neighbors = new HashSet<Integer>(n1);
            neighbors.addAll(n2);
        }

        public Line(Line other) {
            length = other.length;
            neighbors1 = new HashSet<Integer>(other.neighbors1);
            neighbors2 = new HashSet<Integer>(other.neighbors2);
            neighbors = new HashSet<Integer>(other.neighbors);
        }
    }
}
