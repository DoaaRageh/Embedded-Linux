#include<fcntl.h>
#include<unistd.h>
int main()
{
	int output = 0;
	int brightness = 0;
	char var;
	
	output = open("/home/doaa/output", O_RDONLY);
	read(output,&var,1);
	close(output);
	
	brightness = open("/sys/class/leds/input4::capslock/brightness", O_WRONLY);
	write(brightness,&var,1);
	close(brightness);
		
}
