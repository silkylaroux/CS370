/*
 * Damian Armijo 
 * If you see the word data, it is short hand for turnaround time,
 * wait time, and throughput.
 */
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*
 * This is a helper method which checks if the values
 * in burstTime up until count are empty or not.
 * returns 1 if not empty, 0 if empty
 */
int all_zero(int burstTime[],int processNum){
    for(int x = 0; x < processNum; x++){
        if(burstTime[x]!=0){
            return 1;
        }
    }
    return 0;
}

/*
 *  This is a void Helper method which takes in an arrival time array
 *  and a burst time array, and sorts both by the smallest arrival time
 *  first.
 *  EX: before: arrT = {3,2,5} burT = {4,2,0}
 *      after:  arrT = {2,3,5} burT = {2,4,0}
 */
void sort_by_arrive(int processesNum,int arrivalTime[], int burstTime[]){
    int holder;    

    for(int x = 0; x < processesNum; x++){
        for(int y = x+1; y < processesNum; y++){
            if(arrivalTime[x] > arrivalTime[y]){
                holder = arrivalTime[x];
                arrivalTime[x] = arrivalTime[y];
                arrivalTime[y] = holder;

                holder = burstTime[x];
                burstTime[x] = burstTime[y];
                burstTime[y] = holder;
            }
        }
    }
}

/*
 * This void function takes in 1 int and two int arrays.
 * proccessesNum is the total num of proccesses to be executed.
 * arrivalTime[] is a list of ints (sorted) by the arrival time
 * burstTime[] is a list of ints(sorted) by the arrival time.
 * The function takes the information in the two arrays, and gets the data
 * from First Come First Serve scheduling on it, and prints out this data.
 */ 
void run_FCFS(int processesNum, int arrivalTime[], int burstTime[]){
    int idl =0;
    double waitTime=0;
    double throughPut =0;
    double turnaround = 0;
    for(int x = 0; x < processesNum; x++){
        if((arrivalTime[x] - idl) > 0) {
            printf("[%d]---IDLE---[%d]\n",idl,arrivalTime[x]);
            idl = arrivalTime[x];
            waitTime += (arrivalTime[x] - idl);

        }else{
            waitTime += (idl - arrivalTime[x]);
        }
        printf("[%d]---P%d---[%d]\n",(idl),(x+1),(idl+burstTime[x]));
        idl += (burstTime[x]);
        turnaround +=(idl- arrivalTime[x]);
    }
    printf("%f",turnaround);
    throughPut = processesNum/(double)idl;

    printf("Average Turnaround time for First Come First Serve is %f\n", (turnaround/processesNum));
    printf("Average Wait time For First Come First Serve is %f\n",waitTime/processesNum);
    printf("Average Throughput For First Come First Serve is %f\n",throughPut);
}

/*
 * This void function takes in 1 int and two int arrays.
 * proccessesNum is the total num of proccesses to be executed.
 * arrivalTime[] is a list of ints (sorted) by the arrival time
 * burstTime[] is a list of ints(sorted) by the arrival time.
 * The function takes the information in the two arrays, and gets the data
 * from round robin scheduling on it, and prints out this data.
 */ 
void run_SJF(int processesNum, int arrivalTime[], int burstTime[]){

    int used[10] = {1,1,1,1,1,1,1,1,1,1};
    int count = 0;
    int time = 0;
    double throughPut = 0;
    double waitTime = 0;
    double turnaround = 0;
    
    while(count<processesNum){
        int final = count;
        for(int x =count+1; x <processesNum; x++){
            // If It has arrived & has a lower burst time & and hasn't been used
            if(arrivalTime[x] <time && burstTime[x] < burstTime[final] && arrivalTime[final]< time){
                final = x;
            }
        }
        if(arrivalTime[final] > time){
            printf("[%d]---IDLE---[%d]\n",time,arrivalTime[count]);
            time = arrivalTime[final];

        }else if(final != count){
            printf("[%d]---P%d---[%d]\n",(time),(final+1),(time+burstTime[final]));
            waitTime += (time - arrivalTime[final]);                                // for waitTime
            time += burstTime[final];
            turnaround += (time - arrivalTime[final]);
            used[final] =0;
            count--;

        }else{
            printf("[%d]---P%d---[%d]\n",(time),(final+1),(time+burstTime[final]));
            waitTime += (time - arrivalTime[final]);                                // for waitTime
            time += burstTime[final];
            turnaround += (time - arrivalTime[final]);
            used[final] =0;
            count++;
            
        }
    }
    throughPut = processesNum/(double)time;
    // printing out info from SJF scheduling.
    printf("\nAverage Turnaround time for Shortest Job First - Non Preemptive is %f\n", (turnaround/processesNum));
    printf("Average Wait time For Shortest Job First - Non Preemptive is %f\n",waitTime/processesNum);
    printf("Average Throughput For Shortest Job First - Non Preemptive is %f\n",throughPut);
}

/*
 *  This is suppose to order the proccess' by the shortest burst time
 *  It is not yet implemented.
 */
void run_SJF_preemp(int processesNum, int arrivalTime[], int burstTime[]){
 
    printf("doesn't work\n");

}

/*
 *  This void function takes in two arrays, and two ints.
 *  proccessesNum is the total num of proccesses to be executed
 *  timeQuantum is the time quantum for the number. 
 *  arrivalTime[] is a list of ints (sorted) by the arrival time
 *  bTime[] is a list of ints(sorted) by the arrival time.
 *  The function takes the information in the two arrays, and gets the data
 *  from round robin scheduling on it, and prints out this data.
 */
void run_RR(int processesNum, int arrivalTime[], int bTime[], int timeQuantum){
    int burstTime[10];                                  // a temp array for burstTime
    for(int x = 0; x< processesNum; x++){
        burstTime[x] = bTime[x];    
    }
    int count =0;
    int remain =1;
    int time = 0;
    double waitTime =0;
    double turnaround = 0;

   if( arrivalTime[0]>0){                                   // Handles if initial arrival is not 0.
       printf("[%d]---IDLE---[%d]\n",0,arrivalTime[0]);
       time = arrivalTime[0];
   }

    count=0; 
    while(remain!=0) { 
                    
        if(burstTime[count]<=timeQuantum && burstTime[count]>0) { 
            printf("[%d]---P%d---[",time,count+1);
            waitTime += (time - arrivalTime[count]);
            time+=burstTime[count]; 
            printf("%d]\n",time);                           // The following if's just handle the different ways in
            burstTime[count]-=burstTime[count];             // which the info about RR is calculated.
        } 
        else if(burstTime[count]>0 ) {                      // If burst is greater than time Quantum 
            if((count ==processesNum-1) ){                  // If is last value in list
                printf("[%d]---P%d---[",time,count+1);
                waitTime += (time - arrivalTime[count]);   
                time+=burstTime[count]; 
                turnaround += (time - arrivalTime[count]);
                printf("%d]\n",time);
                burstTime[count]=0; 
                                                            // Else if the time plus burst of the current value
                                                            // is less than arrival time of next in the list.
            }else if((time + burstTime[count])<= arrivalTime[count+1]){
                printf("[%d]---P%d---[",time,count+1);
                waitTime += (time - arrivalTime[count]); 
                time+=burstTime[count]; 
                turnaround += (time - arrivalTime[count]);
                printf("%d]\n",time);
                burstTime[count]=0; 
                                                            // Else if the time plus quantum is smaller in
                                                            // current than arrival of next in the list.
            }else if((time + timeQuantum)<= arrivalTime[count+1]){
                printf("[%d]---P%d---[",time,count+1);
                burstTime[count]-= arrivalTime[count+1]-time; 
                waitTime += (time - arrivalTime[count]); 
                time = arrivalTime[count+1];
                turnaround += (time - arrivalTime[count]); 
                printf("%d]\n",time);
                                                            // Else if burstTime of next is 0 ie already used
            }else if(burstTime[count+1]==0){               
                printf("[%d]---P%d---[",time,count+1);
                waitTime += (time - arrivalTime[count]); 
                time+=burstTime[count];
                turnaround += (time - arrivalTime[count]); 
                printf("%d]\n",time);
                burstTime[count]=0; 
                                                            // Else get the time updated, aswell as other info
            }else{                                          
                printf("[%d]---P%d---[",time,count+1);                
                burstTime[count]-=timeQuantum+1;
                waitTime += (time - arrivalTime[count]);  
                time+=timeQuantum+1;
                turnaround += (time - arrivalTime[count]); 
                printf("%d]\n",time);
            }
        }
        if(count == processesNum-1) {                       // if count = max restart loop
            count=0; 
        }else if(arrivalTime[count+1]<=time) {              // increases count to next value in the list 
            count++; 
        }else if(all_zero(burstTime,count)==0){             // calls all_zero()
            printf("[%d]---IDLE---[%d]\n",time,arrivalTime[count+1]);
            time = arrivalTime[count+1];
        }else{
            count = 0;
        }
        if(all_zero(burstTime,processesNum)==0){            // Calls helper method which checks if all 
            remain = 0;                                     // burst values are 0; and breaks the outer
        }                                                   // outer loop.
    }
    double throughPut = processesNum/(double)time;
    waitTime = waitTime/2;                                  // correcting the multiple additions to waitTime
    // printing out info from RR scheduling.
    printf("Average Turnaround time For Round Robin is %f\n",turnaround/processesNum); 
    printf("Average Wait time For Round Robin is %f\n",waitTime/processesNum);
    printf("Average Throughput For Round Robin is %f\n",throughPut); 
}

/*
 * This is the main function for the scheduler.c file.
 * It is meant to take in 4 arguments the seed for randomization,
 * the number of processess, and the time quantum for round robin. 
 */

int main(int argc, char **argv){
    unsigned int seed = atoi(argv[1]);
    int processesNum = atoi(argv[2]);
    int timeQuantum = atoi(argv[3]);

    int arrivalTime[10];
    int burstTime[10];

    srand(seed);                                            // initialize random number
    for( int i = 0; i< processesNum ; i++){
        arrivalTime[i] = rand() % 50;                       // generate arrival time in range [0-49]
        burstTime[i] = (rand() %10) +1;                     // generate burst time in range [1-10]    
    }

    printf("Before sort:\n");
    for(int x = 0; x < processesNum; x++){
        printf("Arrival: %d\t|\tBurst: %d\n",arrivalTime[x],burstTime[x]);
    }

    sort_by_arrive(processesNum,arrivalTime,burstTime);     // Sorts the "random" data by arrival time

    printf("\nAfter sort:\n");
    for(int x = 0; x < processesNum; x++){
        printf("Arrival: %d\t|\tBurst: %d\n",arrivalTime[x],burstTime[x]);
    }
 
    printf("\nIn First Come First Serve\n");
    printf("\nGantt chart is :\n");
    run_FCFS(processesNum,arrivalTime,burstTime);

    printf("\nIn Round Robin\n");
    printf("\nGantt chart is :\n");
    run_RR(processesNum, arrivalTime, burstTime, timeQuantum);

    printf("\nIn Shortest Job First - Non Preemptive\n");
    printf("\nGantt chart is :\n");
    run_SJF(processesNum,arrivalTime,burstTime);

    printf("\nIn Shortest Job First - Preemptive\n");
    //printf("\nGantt chart is :\n");
    run_SJF_preemp(processesNum,arrivalTime,burstTime);

    return 0;
}