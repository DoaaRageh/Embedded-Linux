#include<fcntl.h>
#include<unistd.h>

int main()
{
	int brightness = 0;
	int output = 0;
	char var;
	
	brightness = open("/sys/class/leds/input4::capslock/brightness", O_RDONLY);
	read(brightness,&var,1);
	close(brightness);
	
	output = open("/home/doaa/output", O_WRONLY);
	if(var == '0')
	{
		write(output,"1",1);
	}
	else
	{
		write(output,"0",1);
	}
	close(output);
	
}




