/**
 * Implementation of a queue of integers
 * using only primitives and arrays of primitives
 *
 * @author Erick Lin
 */

public class Queue {
    private final int size;
    private int tail;
    private int head;
    private int count;
    private final int[] queue;
    
    /**
     * Creates a queue with a specific size
     * @param capacity  The size of the queue to be initialized
     */
    public Queue(int capacity) {
        size = capacity;
        tail = 0;
        head = 0;
        queue = new int[capacity];
    }
    
    /**
     * Adds an integer to the back of the queue
     * @param element  An integer to be added to the back of the queue
     * @throws IllegalStateException  Attempting when queue is full
     */
    public void enqueue(int element) throws IllegalStateException {
        if (count >= size)
            throw new IllegalStateException();
        queue[tail] = element;
        tail++;
        if (tail >= size)
            tail = 0;
        count++;
    }
    
    /**
     * Removes an integer from the front of the queue and returns it
     * @return  The integer that is removed from the front of the queue
     * @throws IllegalStateException  Attempting when queue is empty
     */
    public int dequeue() throws IllegalStateException {
        if (count <= 0)
            throw new IllegalStateException();
        int element = queue[head];
        queue[head] = 0;
        head++;
        if (head >= size)
            head = 0;
        count--;
        return element;
    }
}