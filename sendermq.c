#include <stdio.h>
#include <mqueue.h>
#include <string.h>
int main(){
    mqd_t mq;
    struct mq_attr attr = {0,10,100,0};
    mq = mq_open("/mq1",O_CREAT | O_WRONLY, 0644,&attr);
    mq_send(mq, "Hello",6,1);
    mq_close(mq);
}
