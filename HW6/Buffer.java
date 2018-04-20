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
            while ( this.is_full()) {
                wait();
            }
            BufferEnd = (BufferEnd + 1) % MaxBuffSize;
            store[BufferEnd] = ch;
            BufferSize++;
            System.out.println("Producer added: "+ ch +" at position: "
                +BufferEnd+" at Time: "+getTime());            

            notify();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
    public synchronized void delete() {
        try {
            while (BufferSize == 0) {
                wait();
            }
            int ch = store[BufferStart];
            store[BufferStart] =-1;

            System.out.println("Consumer removed: "+ch+" at position: "+BufferStart+" at Time: "+getTime());
            
            
            BufferStart = (BufferStart + 1) % MaxBuffSize;
            BufferSize--;
            notify();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    @Override
    public String toString() {
        return Arrays.toString(store);
    }
}