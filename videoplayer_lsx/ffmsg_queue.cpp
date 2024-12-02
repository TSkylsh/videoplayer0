#include "ffmsg_queue.h"

void msg_free_res(AVMessage *msg)
{
    if(!msg||!msg->obj){
        return;
    }
    msg->free_l(msg->obj);
    msg->obj=NULL;
}

int msg_queue_put_private(MessageQueue *q, AVMessage *msg)
{

}
