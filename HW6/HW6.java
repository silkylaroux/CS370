import java.util.Date;
import java.util.LinkedList;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class Producer extends Thread{
    /*
     * Override for thread class
     */
    public void run(){
        while (true)
        {
            synchronized (this)
            {
                // producer thread waits while list
                // is full
                while (list.size()==capacity)
                    wait();
    
                System.out.println("Producer produced-"
                                              + value);
    
                // to insert the jobs in the list
                list.add(value++);
    
                // notifies the consumer thread that
                // now it can start consuming
                notify();
    
                // makes the working of program easier
                // to  understand
                Thread.sleep(1000);
            }
        }
    }
    
}

public class runner{
    public static string getTime(){
        DateFormat formatedDate = new SimpleDateFormat("yyyy-MM-DD HH:mm:ss.SSSSS");
        Date date = new Date();
        return formatedDate.format(date); 
    }

    public static void main(String[] args) {
        LinkedList<Integer> buffer = new LinkedList<>();

        
    }
}