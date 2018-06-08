#include "page_table.h"
#include "memory.h"
/******************************************************************************
 * constructor for a page table that has in its parameters a reference to a mem
 * object that t will interact with.
 * ***************************************************************************/
page_table::page_table(int process, int code_size, int data_size, memory* mem, int framesize){
    my_memory = mem;
    this->process = process;
    this->code_size = code_size;
    this->data_size = data_size;
    this->PAGE_SIZE = framesize;
}

std::vector<int> *page_table::getPages(){
    return &pages;
}

bool page_table::isEmpty(){
    return (pages.size() == 0);
}

std::string page_table::allocate(int process, int code_size, int data_size){
    std::string output;
    //limit the number of code_pages
    int code_pages = code_size/PAGE_SIZE;

    for (int i = 0; i <= code_pages; ++i){
        if (code_size-PAGE_SIZE*i != 0){
            pages.push_back(code_size- PAGE_SIZE*i);
            output += "code for P" + std::to_string(process) + ": " +my_memory->allocate(process, 0)+ "\n";
        }
    }
    //limit it by the defined page code_size
    //initially 512 Kb
    int data_pages = data_size/PAGE_SIZE;
    for (int i = 0; i <= data_pages; ++i ){
        if (data_size - PAGE_SIZE*i != 0){
            pages.push_back(data_size - PAGE_SIZE*i);
            output +=  "data for P" + std::to_string(process) + ": " +my_memory->allocate(process, 1)+"\n";
        }
    }
    return output;
}


int page_table::getProcess(){
    return process;
}
void page_table::setPage(int x){
    this->PAGE_SIZE = x;
    this->my_memory->setSize(PAGE_SIZE);
}

int page_table::getPageSize(){
    return PAGE_SIZE;
}
