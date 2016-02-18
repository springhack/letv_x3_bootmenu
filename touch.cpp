/**
        Author: SpringHack - springhack@live.cn
        Last modified: 2016-02-18 13:34:28
        Filename: touch.cpp
        Description: Created by SpringHack using vim automatically.
**/
#include <pthread.h>
#include "events.cpp"

pthread_t input_t;

int complete_once = false;
int once_x = -1;
int once_y = -1;

void make_callback(int x, int y)
{
	printf("TouchEvent: x = %d,\ty = %d\n", x, y);
	return;
}

void process_touch(int code, int value)
{
	if (code == 53)
		once_x = value;
	if (code == 54)
		once_y = value;
	if (once_x != -1 && once_y != -1)
		complete_once = true;
	if (complete_once)
	{
		make_callback(once_x, once_y);
		once_x = once_y = -1;
		complete_once = false;
	}
}

int input_callback(int fd, short revents, void*data)
{
	struct input_event ev;
	int ret;
	ret = ev_get_input(fd, revents, &ev);//读取输入消息
	if(ret)
		return -1;
	if (ev.type == 3)
		process_touch(ev.code, ev.value);
	return 0;
}

void* input_thread(void *cookie)
{
	for(;;)
	{
		if(!ev_wait(-1)) //查看是否有输入事件
		ev_dispatch();//有输入事件，那么将派发输入事件
	}
	return NULL;
}

void TouchInit(){
	ev_init(input_callback, NULL); //输入事件初始化，并注册回调函数
	pthread_create(&input_t, NULL, input_thread, NULL);//创建新的线程读取输入事件
}

