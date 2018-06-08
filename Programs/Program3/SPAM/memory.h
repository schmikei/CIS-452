#ifndef MEMORY_H
#define MEMORY_H
#include <vector>


class memory
{
private:
    std::vector<int> frames;
    std::vector<int> owned_by;
    std::vector<std::string> DorC;
    int size;

public:
    memory();
    std::string allocate(int process, int size);
    int allocatePage(int process, int data_size);
    int getFrame(int index);
    int getFrameSize();
    std::string deallocate(int process);
    int getFrameOwner(int index);
    std::string getFrameType(int index);
    void setSize(int x);


};

#endif // MEMORY_H
