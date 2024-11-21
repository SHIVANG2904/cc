#ifndef PROCESS_H
#define PROCESS_H


class Process {
public:
    int id;                
    int arrivalTime;       
    int burstTime;         
    int remainingTime;     
    int waitingTime;       
    int turnaroundTime;   
    
  
    Process(int id, int arrivalTime, int burstTime) {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->remainingTime = burstTime; 
        this->waitingTime = 0;           
        this->turnaroundTime = 0;       
    }

    
    int getProcessID() const {
        return id;
    }
    
    int getArrivalTime() const {
        return arrivalTime;
    }

    
    int getBurstTime() const {
        return burstTime;
    }

   
    int getRemainingTime() const {
        return remainingTime;
    }

    
    int getWaitingTime() const {
        return waitingTime;
    }

   
    int getTurnaroundTime() const {
        return turnaroundTime;
    }
};

#endif
