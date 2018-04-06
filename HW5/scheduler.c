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
int all_zero(int burstTime[],int processNum){
    for(int x = 0; x < processNum; x++){
        if(burstTime[x]!=0){
            return 1;
        }
    }
    return 0;
}
int check_prev(int burstTime[],int count){
    for (int x =0; x < count; x++){
        if(burstTime[x]!=0){
            return 1;
        }
    }
    return 0;
}
void run_RR(int processesNum, int arrivalTime[], int burstTime[], int timeQuantum){
    int count =0;
    int remain =1;
    int waitTime[processesNum];
    int time = 0;

   if( arrivalTime[0]>0){
       printf("[%d]---IDLE---[%d]\n",0,arrivalTime[0]);
       time = arrivalTime[0];
   }

    count=0; 
    int flag=0;
    while(remain!=0) { 
printf("\narrive: %d\ntime: %d\ncount: %d\nburst: %d\narrive: %d\n",
arrivalTime[count],time,count+1,burstTime[count],arrivalTime[count +1]);

        if(burstTime[count]<=timeQuantum && burstTime[count]>0) { 
            printf("[%d]---P%d---[",time,count+1);
            time+=burstTime[count]; 
            printf("%d]\n",time);
            if(count ==2){
                printf("\n:%d\n",burstTime[count]);
            }
            burstTime[count]-=burstTime[count]; 
            if(count ==2){
                printf("\n:%d\n",burstTime[count]);
            }
            flag=1; 
        } 
        else if(burstTime[count]>0 ) { 
            if((count ==processesNum-1) || (time + burstTime[count])<= arrivalTime[count+1]){
//printf("\ntime: %d\ncount: %d\nburst: %d\narrive: %d\n",time,count+1,burstTime[count],arrivalTime[count +1]);

                printf("[%d]---P%d---[",time,count+1);
                time+=burstTime[count]; 
                printf("%d]\n",time);
                burstTime[count]=0; 
                flag=1;
            }else{
                printf("[%d]---P%d---[",time,count+1);
                if(count ==2){
                    printf("\n%d:%d\n",timeQuantum,burstTime[count]);
                }
                burstTime[count]-=timeQuantum+1; 
//printf("\ncheck%d:%d\n",count+1,burstTime[count]);
                if(count ==2){
                    printf("\n:%d\n",burstTime[count]);
                }
                time+=timeQuantum+1; 
                printf("%d]\n",time);
            }
        }

        if( burstTime[count] == 0 && flag==1){
            flag = 0;
        }
        if(count == processesNum-1) {
            count=0; 
        }
 
        else if(arrivalTime[count+1]<=time) {
            count++; 
        }else if(check_prev(burstTime,count)==0){
            printf("[%d]---IDLE---[%d]\n",time,arrivalTime[count+1]);
            time = arrivalTime[count+1];
            //count = ;
            //count = 0;
        }else{
            // printf("[%d]---IDLE---[%d]\n",time,arrivalTime[count+1]);
            // time = arrivalTime[count+1];
            // count = count;
            count = 0;
        }
        if(all_zero(burstTime,processesNum)==0){
            remain = 0;
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

    printf("\nIn Round Robin\n");
    printf("\nGantt chart is :\n");
    int arrivalTime2[] = {1,18,22,25,46};
    int burstTime2[] = {5,1,7,1,6};
    run_RR(processesNum, arrivalTime2, burstTime2, timeQuantum);
    

    return 0;
}