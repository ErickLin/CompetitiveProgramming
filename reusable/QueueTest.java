/**
 * Test for Queue class that takes user input
 *
 * @author Erick Lin
 */
import java.util.Scanner;

public class QueueTest {    
    /**
     * Allows user to test Queue constructor and methods
     * @param args
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size = -1;
        do {
            try {
                System.out.print("Enter the size of the queue: ");
                size = Integer.parseInt(sc.nextLine());
                
            } catch (NumberFormatException ex) {
            } finally {
                if (size < 0) {
                    System.out.println("Please enter a nonnegative integer.");
                }
            }
        } while (size < 0);
        Queue q = new Queue(size);
        System.out.println();
        System.out.println("Enter an integer to enqueue.");
        System.out.println("Otherwise, enter a blank input to dequeue.");
        System.out.println("Enter any other type of input to exit.");
        System.out.println();
        boolean running = true;
        do {
            try {
                System.out.print("User input: ");
                String input = sc.nextLine();
                if (input.equals("")) {
                    System.out.println("Dequeued: " + q.dequeue());
                    System.out.println();
                }
                else {
                    int element = Integer.parseInt(input);
                    q.enqueue(element);
                    System.out.println("Enqueued: " + element);
                    System.out.println();
                }
            } catch (NumberFormatException ex) {
                System.out.println("Exited program.");
                running = false;
            } catch (IllegalStateException ex) {
                System.out.println("Illegal action: queue is full/empty.");
                System.out.println();
            }
        } while (running);
    }
}