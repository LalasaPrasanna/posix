#include <stdio.h>
#include <mqueue.h>
#include <string.h>
int main(){
    char buf[100];
    mqd_t mq =  mq_open("/mq1", O_RDONLY);
    mq_receive(mq, buf,sizeof(buf),NULL);
    printf("Received:%s\n",buf);
    mq_close(mq);
    mq_unlink("/mq1");
}