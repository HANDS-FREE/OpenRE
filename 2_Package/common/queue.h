#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 256

class Queue
{
public:
    Queue();
    unsigned char arr[QUEUE_SIZE];
    int head,tail;
    void queueInit(void);
    unsigned char getData(void);
    void putData(unsigned char ch);
    unsigned char  emptyCheck(void);
    unsigned char  fullCheck(void);
private:
};

extern Queue usart1_queue;

#endif // #ifndef QUEUE_H

