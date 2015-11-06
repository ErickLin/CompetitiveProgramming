package fall_11_02_14;

import java.io.*;
import java.util.*;

public class F {
    static ArrayList<String> employees;
    static ArrayList<HashSet<String>> isEmployeeOf;
    static ArrayList<String> removed;
    static boolean[][][] visited;
    static int[][] dists;
    
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int m, caseNum = 1;
        while ((m = Integer.parseInt(in.readLine())) > 0) {
            employees = new ArrayList<String>();
            isEmployeeOf = new ArrayList<HashSet<String>>();
            removed = new ArrayList<String>();
            dists = new int[200][200];
            visited = new boolean[200][200][200];
            StringTokenizer line;
            for (int i = 0; i < m; i++) {
                line = new StringTokenizer(in.readLine());
                String employee = line.nextToken();
                String boss = line.nextToken();
                if (!employees.contains(employee)) {
                    employees.add(employee);
                    isEmployeeOf.add(new HashSet<String>());
                }
                if (!employees.contains(boss)) {
                    employees.add(boss);
                    isEmployeeOf.add(new HashSet<String>());
                }
                int employeeNum = employees.indexOf(employee);
                int bossNum = employees.indexOf(boss);
                isEmployeeOf.get(employeeNum).add(boss);
                dists[employeeNum][bossNum] = 1;
            }
            System.out.print("Case " + caseNum + ": ");
            caseNum++;
            int n = employees.size();
            //starting point
            for (int employeeNum = 0; employeeNum < n; employeeNum++) {
                for (String boss : isEmployeeOf.get(employeeNum)) {
                    floodFill(employeeNum, employees.indexOf(boss), 1);
                }
            }
            Collections.sort(removed);
            System.out.print(removed.size());
            for (String pair : removed) {
                System.out.print(" " + pair);
            }
            System.out.println();
        }
        in.close();
        System.exit(0);
    }
    
    public static void floodFill(int startNum, int employeeNum, int dist) {
        if (dist > dists[startNum][employeeNum]) {
            dists[startNum][employeeNum] = dist;
            if (isEmployeeOf.get(startNum).contains(employees.get(employeeNum))) {
                String pair = employees.get(startNum) + "," + employees.get(employeeNum);
                if (!removed.contains(pair))
                    removed.add(pair);
            }
        }
        for (String boss : isEmployeeOf.get(employeeNum)) {
            //System.out.println(employees.get(startNum) + " " + employees.get(employees.indexOf(boss)) + " " + visited[startNum][employeeNum][employees.indexOf(boss)]);
            if (!visited[startNum][employeeNum][employees.indexOf(boss)])
                floodFill(startNum, employees.indexOf(boss), dist + 1);
            visited[startNum][employeeNum][employees.indexOf(boss)] = true;
        }
    }
}
