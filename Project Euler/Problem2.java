public class Problem2 {
    public static void main(String[] args) {
        long sum = 2;
        int[] a = new int[2];
        a[0] = 1;
        a[1] = 2;
        while (a[1] <= 4000000) {
            int b = a[0] + a[1];
            if (b % 2 == 0)
                sum += b;
            a[0] = a[1];
            a[1] = b;
        }
        System.out.println(sum);
    }
}