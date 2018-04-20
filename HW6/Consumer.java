import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Random;



// Consumer class
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
            while (!Thread.currentThread().isInterrupted()) { 
                Thread.sleep((long)(Math.random()*max_wait));       // Added to create random time buffer
                buffer.delete();                                    // Synchronized method in buffer
            }
        } catch (InterruptedException e) {}
    }
}