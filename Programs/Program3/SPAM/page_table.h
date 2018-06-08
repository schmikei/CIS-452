#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
#define code_bit 0;
#define data_bit 1;
#include <iostream>
#include <vector>
#include "memory.h"


class page_table{
public:
    page_table(int process, int code_size, int data_size, memory*
                mem, int framesize);
    std::string allocate(int process, int code_size, int data_size);
    std::vector<int>* getPages();
    bool isEmpty();
    int getProcess();
    void setPage(int x);
    int getPageSize();

private:
    std::vector<int> pages;
    memory* my_memory;
    int process;
    int code_size;
    int data_size;
    int PAGE_SIZE;

};

#endif // PAGE_TABLE_H
