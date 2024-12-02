#include "ffmsg_queue.h"

void msg_free_res(AVMessage *msg){
    if(!msg||!msg->obj){
        return;
    }
    msg->free_l(msg->obj);
    msg->obj=NULL;
}

int msg_queue_put_private(MessageQueue *q, AVMessage *msg)
{
    AVMessage *msg1=NULL;
    if(q->abort_request){
        returen -1;
    }
    msg1=q->recycle_msg;
    if(msg1){
       q->recycle_msg=msg1->next;
       q->recycle_count++;
    }else{
        q->alloc_count++;
        msg1=(AVMessage*)av_malloc(sizeof(AVMessage));
    }
    *msg1=*msg;
    msg1->next=NUL;
    if(!q->last_msg){
        q->first_msg=msg1;
    }else{
        q->last_msg->next=msg1
    }
    q->last_msg=msg1;
    q->nb_messages++;
    SDL_CondSignal(q->cond);
    return 0;
}

void msg_queue_get(MessageQueue *q, AVMessage *msg, int block)
{

}
