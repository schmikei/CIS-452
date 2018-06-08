#include "memory.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <QString>

/*****************************************************************************
class that simulates main memory, gets an allocate call from the page table
class and deallocate when inputted.

******************************************************************************/
memory::memory(){
    size = 8;
    for(int i=0; i < size; ++i){
        frames.push_back(-1);
        owned_by.push_back(-1);
        DorC.push_back("");
    }
}

/***************************************************************************
 * allocate given a process and whether or not the piece of data is code or
 * data for a process
 * @return a string to be put into the qt Text object that either is a success
 * or a failure
 * ************************************************************************/
std::string memory::allocate(int process, int c_or_d){
    std::string return_statement;

    //search for hole that accomodate
    for (std::vector<int>::iterator iter = frames.begin(); iter != frames.end(); ++iter){
        if (*iter == -1){
            *iter = c_or_d;
            owned_by[iter-frames.begin()] = process;
            if (c_or_d == 0){
                DorC[iter - frames.begin()] = "Code";
            }
            else{
                DorC[iter - frames.begin()] = "Data";
            }
            return_statement = "Was placed into frame " + std::to_string(iter - frames.begin())+ "\n";
            break;
        }
        else{
            return_statement = "couldn't find an open frame\n";
        }

    }
    return return_statement;
}

/************************************************
 * remove process based off of who owns the process
 * ************************************************/
std::string memory::deallocate(int process){
    for (std::vector<int>::iterator iter = owned_by.begin(); iter != owned_by.end(); ++iter){
        if (*iter == process){
            owned_by[iter - owned_by.begin()] = -1;
            frames[iter - owned_by.begin()] = -1;
        }
    }
    return "terminated all frames owned by: " + std::to_string(process)+"\n";
}

int memory::getFrame(int index){
    return frames[index];
}

std::string memory::getFrameType(int index){
    return DorC[index];
}

int memory::getFrameSize(){
    return  frames.size();
}

void memory::setSize(int x){
    this->size = x;
    frames.clear();
    owned_by.clear();
    DorC.clear();
    for(int i=0; i < size; ++i){
        frames.push_back(-1);
        owned_by.push_back(-1);
        DorC.push_back("");
    }
}

int memory::getFrameOwner(int index){
    return owned_by[index];
}
