import java.util.Date;
import java.util.LinkedList;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Random;
import java.io.LineNumberReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

// The producer and the consumer classes should take these arguments: 1. number of items in the buffer
// (the size of the buffer) , 2. Maximum wait time (used for generating random wait time would be smaller)
// in nanoseconds, 3. The number of items to be produced (only for the producers).

class Buffer {
    private final int MaxBuffSize;
    private int[] store;
    private int BufferStart, BufferEnd, BufferSize;

    public Buffer(int size) {
        MaxBuffSize = size;
        BufferEnd = -1;
        BufferStart = 0;
        BufferSize = 0;
        store = new int[MaxBuffSize];
        this.set();
    }
    public static String getTime(){
        DateFormat formatedDate = new SimpleDateFormat("yyyy/dd/MM HH:mm:ss.SSSSS");
        Date date = new Date();
        return formatedDate.format(date); 
    }
    public void set(){
        for (int x = 0; x < this.MaxBuffSize; x++) {
            store[x] = -1;    
        }
    }
    public boolean is_full(){
        for (int x = 0; x < this.MaxBuffSize; x++) {
            if(this.store[x] == -1){
                return false;
            }
        }
        return true;   
    }
    public boolean is_empty(){
        for (int x = 0; x < this.MaxBuffSize; x++) {
            if(this.store[x] != -1){
                return false;
            }
        }
        return true;   
    }
    public synchronized void insert(int ch) {
        try {
            while (BufferSize == MaxBuffSize|| this.is_full()) {
                wait();
            }
            System.out.print("\nProducer added: ");
            System.out.print(ch);
            BufferEnd = (BufferEnd + 1) % MaxBuffSize;
            store[BufferEnd] = ch;
            BufferSize++;
            System.out.print(" at position: ");
            System.out.print(BufferEnd);
            System.out.print(" at Time: ");
            System.out.print(getTime());
            notify();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
    public synchronized int delete() {
        try {
            while (BufferSize == 0) {
                wait();
            }
            int ch = store[BufferStart];
            System.out.print("\nConsumer removed: ");  
            store[BufferStart] =-1;
            System.out.print(ch);
            System.out.print(" at position: ");
            System.out.print(BufferStart);
            System.out.print(" at Time: ");
            System.out.print(getTime());
            
            BufferStart = (BufferStart + 1) % MaxBuffSize;
            BufferSize--;
            notify();
            return ch;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            //return ch;
        }
            return store[BufferStart];
        }
    @Override
    public String toString() {
        return Arrays.toString(store);
    }
}
class Consumer extends Thread {
    public static String getTime(){
        DateFormat formatedDate = new SimpleDateFormat("yyyy/dd/MM HH:mm:ss.SSSSS");
        Date date = new Date();
        return formatedDate.format(date); 
    }
    private final int max_wait;
    private final Buffer buffer;
    public Consumer(Buffer b, int wait) {
        buffer = b;
        max_wait = wait;
    }
    public void run() {
        
        try {
            long x = (long)(Math.random()*max_wait);
            sleep(x);  
            if(!buffer.is_empty()){
            //    wait();
            }
            while (!Thread.currentThread().isInterrupted()|| !buffer.is_empty()) { 
                int c = buffer.delete();
            }
        } catch (InterruptedException e) { notify();}
    }
}

class Producer extends Thread {
    
    public static String getTime(){
        DateFormat formatedDate = new SimpleDateFormat("yyyy/dd/MM HH:mm:ss.SSSSS");
        Date date = new Date();
        return formatedDate.format(date); 
    }
    private final Buffer buffer;
    private final int max_wait;
    private final int max_num;
    public Producer(Buffer b, int wait, int num) {
        buffer = b;
        max_num = num;
        max_wait = wait;
    }
    public void run() {
        
        try {
            long y = (long)(Math.random()*max_wait);
            sleep(y);
           // if(buffer.is_full()){
           //     wait();
           //     notify();
           // }else{
            int x =0;
            while (!Thread.currentThread().isInterrupted() && x < max_num){
                int c = (int)(Math.random() * 100);
                

                buffer.insert(c);  
                x++;                
            }
        //}
        } catch (InterruptedException e) {}
    }
}
public class HW6{
    public static String getTime(){
        DateFormat formatedDate = new SimpleDateFormat("yyyy/dd/MM HH:mm:ss.SSSSS");
        Date date = new Date();
        return formatedDate.format(date); 
    }

    public static void main(String[] args) {
        int size = Integer.parseInt(args[0]);
        int max_wait = Integer.parseInt(args[1]);
        int num_items = Integer.parseInt(args[2]);

        System.out.println(getTime());
        System.out.println("program starting");
        Buffer buffer = new Buffer(size); // buffer has size 5
        Producer prod = new Producer(buffer,max_wait,num_items);
        Consumer cons = new Consumer(buffer,max_wait);
        prod.start();
        cons.start();
        try {
            prod.join();
            cons.interrupt();
        } catch (InterruptedException e) {
            System.out.println("End of Program");
        }
        
    
    }
}