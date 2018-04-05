/*
 *
 * 
 * 
 * 
 * 
 * 
 */
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

void run_FIFO(int processesNum, int arrivalTime[], int burstTime[]){
    int idl =0;
    int waitTime[processesNum];
    for(int x = 0; x < processesNum; x++){
//printf("wait:%d\n",waitTime[x]);
        if((arrivalTime[x] - idl) > 0) {
//printf("check: %d\n",arrivalTime[x]);
            printf("[%d]---IDLE---[%d]\n",idl,arrivalTime[x]);
            idl = arrivalTime[x];
            waitTime[x] = (arrivalTime[x] - idl);

        }else{
            waitTime[x] = 0;
        }
//printf("wait:%d\narrive:%d\nburst:%d\n",waitTime[x],arrivalTime[x],burstTime[x]);
        printf("[%d]---P%d---[%d]\n",(idl),(x+1),(idl+burstTime[x]));
        idl += (burstTime[x]);
    }
}

void run_RR(int processesNum, int arrivalTime[], int burstTime[], int timeQuantum){
    int idl =0;
    int count =0;
    int remain;
    remain = processesNum;
    int waitTime[processesNum];
    int empty = 0;
    int time = 0;
    int flag = 0;
    // while(empty != 1){
    //     for(int x = 0; x < processesNum; x++){
    //         if((arrivalTime[x] - idl) > 0) {
    //             if(burstTime[x] > timeQuantum){
    //                 printf("[%d]---IDLE---[%d]\n",idl,idl+timeQuantum);
    //                 burstTime[x] -= timeQuantum;
    //             }else{
    //                 printf("[%d]---IDLE---[%d]\n",idl,arrivalTime[x]);
    //             }
    //         }
            
    //     }
    //     empty = 1;
    // }
    printf("%d\n",remain);
    while(remain!=0) { 
        time=0; count=0;
//printf("%d\n",burstTime[count]);
        if(burstTime[count]<=timeQuantum && burstTime[count]>0) { 
            time+=burstTime[count]; 
            printf("%d\n",time);
            burstTime[count]=0; 
            flag=1; 
        } 
        else if(burstTime[count]>0) { 
            burstTime[count]-=timeQuantum; 
            time+=timeQuantum; 
            printf("%d\n",time);
            remain--;
        } 
        if(burstTime[count]==0 && flag==1) 
        { 
            remain--; 
        //printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
        //waitTime+=time-at[count]-bt[count]; 
        //turnaround_time+=time-at[count]; 
            flag=0; 
        } 
        if(count== processesNum-1) {
            count=0; 
        }
        else if(arrivalTime[count+1]<=time) {
            count++; 
        }
        else{ 
            count=0;
        } 
    } 
}

int main(int argc, char **argv){
    unsigned int seed = atoi(argv[1]);
    int processesNum = atoi(argv[2]);
    int timeQuantum = atoi(argv[3]);

    int arrivalTime[10];
    int burstTime[10];

    srand(seed); // initialize random number
    for( int i = 0; i< processesNum ; i++){
        arrivalTime[i] = rand() % 50; // generate arrival time in range [0-49]
        burstTime[i] = (rand() %10) +1; // generate burst time in range [1-10]
        printf("rand:%d\n",(rand()%50));
    
    }

    printf("Before sort:\n");
    for(int x = 0; x < processesNum; x++){
        printf("Arrival: %d\t|\tBurst: %d\n",arrivalTime[x],burstTime[x]);
    }
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
    printf("\nAfter sort:\n");
    for(int x = 0; x < processesNum; x++){
        printf("Arrival: %d\t|\tBurst: %d\n",arrivalTime[x],burstTime[x]);
    }
    

    int waitTime[processesNum];
 
    printf("\nIn First Come First Serve\n");
    printf("\nGantt chart is :\n");
    run_FIFO(processesNum,arrivalTime,burstTime);

    run_RR(processesNum, arrivalTime, burstTime, timeQuantum);
    

    return 0;
}