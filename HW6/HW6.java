import java.util.Date;
import java.util.LinkedList;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Random;
import java.io.LineNumberReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;


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
        // Begin the Producer thread
        prod.start();
        // Begin the consumer thread
        cons.start();
        try {
            prod.join();
            cons.interrupt();
        } catch (InterruptedException e) {
            System.out.println("End of Program");
        }
        
    
    }
}