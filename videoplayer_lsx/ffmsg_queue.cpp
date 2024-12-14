#include "ffmsg_queue.h"
#include "mem.h"
void msg_free_res(AVMessage *msg)
{
    if (!msg || !msg->obj)
    {
        return;
    }
    msg->free_l(msg->obj);
    msg->obj = NULL;
}

int msg_queue_put_private(MessageQueue *q, AVMessage *msg)
{
    AVMessage *msg1 = NULL;
    //判断是否禁止
    if (q->abort_request)
    {
        return -1;
    }
    //申请空间 存放消息  先从回收池中拿
    msg1 = q->recycle_msg;
    if (msg1)
    {
        q->recycle_msg = msg1->next;
        q->recycle_count++;
    }
    else
    {
        q->alloc_count++;
        msg1 = (AVMessage *)av_malloc(sizeof(AVMessage));
    }
    if (!msg1)
        return -1;
    *msg1 = *msg;
    //申请空间 存放消息  先从回收池中拿 将新消息链接到尾部
    msg1->next = NULL;
    if (!q->last_msg){
        q->first_msg = msg1;
    }else{
        q->last_msg->next = msg1;
    }
    q->last_msg = msg1;
    q->nb_messages++;
    SDL_CondSignal(q->cond);
    return 0;
}

int msg_queue_put(MessageQueue *q, AVMessage *msg)
{
    int ret;

    SDL_LockMutex(q->mutex);
    ret = msg_queue_put_private(q, msg);
    SDL_UnlockMutex(q->mutex);

    return ret;
}

void msg_init_msg(AVMessage *msg)
{
   memset(msg, 0, sizeof(AVMessage));
}

void msg_queue_put_simple1(MessageQueue *q, int what)
{
    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = what;
    msg_queue_put(q, &msg);
}

void msg_queue_put_simple2(MessageQueue *q, int what, int arg1)
{
    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = what;
    msg.arg1 = arg1;
    msg_queue_put(q, &msg);
}

void msg_queue_put_simple3(MessageQueue *q, int what, int arg1, int arg2)
{
    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = what;
    msg.arg1 = arg1;
    msg.arg2 = arg2;
    msg_queue_put(q, &msg);
}
void msg_obj_free_l(void *obj)
{
    av_free(obj);
}
void msg_queue_put_simple4(MessageQueue *q, int what, int arg1, int arg2, void *obj, int obj_len){
    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = what;
    msg.arg1 = arg1;
    msg.arg2 = arg2;
    msg.obj = av_malloc(obj_len);
    memcpy(msg.obj, obj, obj_len);
    msg.free_l = msg_obj_free_l;
    msg_queue_put(q, &msg);
}
void msg_queue_init(MessageQueue *q)
{
    memset(q, 0, sizeof(MessageQueue));
    q->mutex = SDL_CreateMutex();
    q->cond = SDL_CreateCond();
    q->abort_request = 1;
}
int msg_queue_get(MessageQueue *q, AVMessage *msg, int block)
{
    AVMessage *msg1 = NULL;
    int ret = 0;
    SDL_LockMutex(q->mutex);
    for (;;)
    {
        if (q->abort_request)
        {
            ret = -1;
            break;
        }
        msg1 = q->first_msg;
        if (msg1)
        {
            q->first_msg = msg1->next;
            if (q->first_msg == NULL)
            {
                q->last_msg = NULL;
            }
            q->nb_messages--;
            *msg = *msg1;
            msg1->obj = NULL;
            msg1->next = q->recycle_msg;
            q->recycle_msg = msg1;
            ret = 1;
            break;
        }
        else if (!block)
        {
            ret = 0;
            break;
        }
        else
        {
            SDL_CondWait(q->cond, q->mutex);
        }
    }
    SDL_UnlockMutex(q->mutex);
    return ret;
}
//把现有消息都塞入缓冲区
void msg_queue_flush(MessageQueue *q)
{
    AVMessage *msg, *msg1;
    SDL_LockMutex(q->mutex);
    for (msg = q->first_msg; msg != NULL; msg = msg1) {
        msg1 = msg->next;
        msg->next = q->recycle_msg;
        q->recycle_msg = msg;
    }
    q->last_msg = NULL;
    q->first_msg = NULL;
    q->nb_messages = 0;
    SDL_UnlockMutex(q->mutex);
}
void msg_queue_destroy(MessageQueue *q)
{
    msg_queue_flush(q);

    SDL_LockMutex(q->mutex);
    while(q->recycle_msg) {
        AVMessage *msg = q->recycle_msg;
        if (msg)
            q->recycle_msg = msg->next;
        msg_free_res(msg);
        av_free(&msg);
    }
    SDL_UnlockMutex(q->mutex);

    SDL_DestroyMutex(q->mutex);
    SDL_DestroyCond(q->cond);
}
void msg_queue_abort(MessageQueue *q)
{
    SDL_LockMutex(q->mutex);

    q->abort_request = 1;

    SDL_CondSignal(q->cond);

    SDL_UnlockMutex(q->mutex);
}

void msg_queue_start(MessageQueue *q)
{
    SDL_LockMutex(q->mutex);
    q->abort_request = 0;

    AVMessage msg;
    msg_init_msg(&msg);
    msg.what = FFP_MSG_FLUSH;
    msg_queue_put_private(q, &msg);
    SDL_UnlockMutex(q->mutex);
}
void msg_queue_remove(MessageQueue *q, int what)
{
    AVMessage **p_msg, *msg, *last_msg;
    SDL_LockMutex(q->mutex);
    last_msg = q->first_msg;
    if (!q->abort_request && q->first_msg) {
        p_msg = &q->first_msg;
        while (*p_msg) {
            msg = *p_msg;
            if (msg->what == what) {
                *p_msg = msg->next;
                msg_free_res(msg);
                msg->next = q->recycle_msg;
                q->recycle_msg = msg;
                q->nb_messages--;
            } else {
                last_msg = msg;
                p_msg = &msg->next;
            }
        }
        if(q->first_msg){
            q->last_msg = last_msg;
        } else {
            q->last_msg = NULL;
        }
    }
    SDL_UnlockMutex(q->mutex);
}
