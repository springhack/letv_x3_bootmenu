/**
        Author: SpringHack - springhack@live.cn
        Last modified: 2016-02-18 14:06:56
        Filename: main.cpp
        Description: Created by SpringHack using vim automatically.
**/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <errno.h>

#include "ui.cpp"
#include "touch.cpp"

int main()
{
	TouchInit();
	UIInit();
	return 0;
}
