import java.util.ArrayList;
import java.util.TreeMap;

public class Eulerian {
    static int[] circuit;
    static int pos;

    public static void eulerian(int start, int n, ArrayList<TreeMap<Integer, Integer>> neighbors) {
        circuit = new int[n + 1];
        pos = n;
        ArrayList<TreeMap<Integer, Integer>> neighborsTemp = new ArrayList<TreeMap<Integer, Integer>>(n);
        for (int i = 0; i < n; i++)
            neighborsTemp.add(new TreeMap<Integer, Integer>(neighbors.get(i)));
        boolean foundOddStart = false;
        int oddCount = 0;
        for (int i = 0; i < n; i++) {
            int numEdges = 0;
            for (int neighbor : neighbors.get(i).keySet())
                numEdges += neighbors.get(i).get(neighbor);
            if (numEdges % 2 == 1) {
                if (!foundOddStart) {
                    start = i;
                    foundOddStart = true;
                }
                oddCount++;
            }
        }
        assert(oddCount == 0 || oddCount == 2);
        eulerianHelper(start, neighborsTemp);
    }

    public static void eulerianHelper(int node, ArrayList<TreeMap<Integer, Integer>> neighborsTemp) {
        while (!neighborsTemp.get(node).isEmpty()) {
            int neighbor = neighborsTemp.get(node).firstKey();
            if (neighborsTemp.get(node).get(neighbor) > 1)
                neighborsTemp.get(node).put(neighbor, neighborsTemp.get(node).get(neighbor) - 1);
            else
                neighborsTemp.get(node).remove(neighbor);
            if (neighborsTemp.get(neighbor).get(node) > 1)
                neighborsTemp.get(neighbor).put(node, neighborsTemp.get(neighbor).get(node) - 1);
            else
                neighborsTemp.get(neighbor).remove(node);
            eulerianHelper(neighbor, neighborsTemp);
        }
        circuit[pos] = node;
        pos--;
    }
}