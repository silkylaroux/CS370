import java.util.Date;
import java.util.LinkedList;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Random;
import java.io.LineNumberReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

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
            

            int x =0;
            while (!Thread.currentThread().isInterrupted() && x < max_num){
                Thread.sleep((long)(Math.random()*max_wait));
                int c = (int)(Math.random() * 100);
                
                buffer.insert(c);  
                x++;                
            }
        } catch (InterruptedException e) {}
    }
}