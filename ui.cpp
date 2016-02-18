/**
        Author: SpringHack - springhack@live.cn
        Last modified: 2016-02-18 14:38:23
        Filename: ui.cpp
        Description: Created by SpringHack using vim automatically.
**/

static char *fbp = 0;
static int xres = 0;
static int yres = 0;
static int bits_per_pixel = 0;

int fbfd = 0;
long int screensize = 0;
struct fb_var_screeninfo vinfo;

static void fb_update(struct fb_var_screeninfo *vi) //将要渲染的图形缓冲区的内容绘制到设备显示屏来
{ 
    vi->yoffset = 1; 
    ioctl(fbfd, FBIOPUT_VSCREENINFO, vi); 
    vi->yoffset = 0; 
    ioctl(fbfd, FBIOPUT_VSCREENINFO, vi); 
} 

int init_screen(int fd)
{
    
    struct fb_fix_screeninfo finfo;
    struct fb_bitfield red;
    struct fb_bitfield green;
    struct fb_bitfield blue;
    retry1:
    fbfd = fd;
    if (fbfd == -1)
    {
        goto retry1;
    }

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
    {
        return -1;
    }

    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
    {
        return -1;
    }
    xres = vinfo.xres;
    yres = vinfo.yres;
	printf("Screen: x = %d\ty = %d\n", xres, yres);
    bits_per_pixel = vinfo.bits_per_pixel;

    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1)
    {
        printf("Error: failed to map framebuffer device to memory.\n");
        return -1;
    }
	return 0;
}

int fill_screen()
{
	fb_update(&vinfo);
    munmap(fbp, screensize);
	return 0;
}

void UIInit()
{
	int fd = open("/dev/graphics/fb0", O_RDWR);

	//Just a sample yo show sth in screen...
	while (true)
	{
		init_screen(fd);
		char *p = fbp;
		for (int i=0;i<vinfo.xres;++i)
			for (int j=0;j<vinfo.yres;++j)
			{
				p[0] = (i + j)%256;
				p[1] = (i + j)%256;
				p[2] = (i + j)%256;
				p[3] = 0x00;
				p += 4;
			}
		fill_screen();
	}

}
