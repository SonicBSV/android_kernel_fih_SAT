#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<errno.h>

//#include <uapi/linux/i2c.h>


/* i2c_test r addr
 * i2c_test w addr val
 */

void print_usage(char *file)
{
    printf("%s r addr\n", file);
    printf("%s w addr val\n", file);
}

//int main(int argc, char **argv)
int main()
{
    int fd;
	unsigned int buf[15][3] ={{5,2,0},{0,2,0},{1,2,0},{2,2,0},{12,2,15},{15,0,600},{17,2,5}};
	

#if 0
    if ((argc != 3) && (argc != 4))
    {
        print_usage(argv[0]);
        return -1;
    }
#endif

    fd = open("/dev/tca6416", O_RDWR);
    if (fd < 0)
    {
        printf("can't open /dev/tca6416\n");
        return -1;
    }
	#if 0
    if (strcmp(argv[1], "r") == 0)
    {
        buf[0] = strtoul(argv[2], NULL, 0);
       read(fd, buf, 1);
        printf("data: %c, %d, 0x%2x\n", buf[0], buf[0], buf[0]);
    }
    else if ((strcmp(argv[1], "w") == 0) && (argc == 4))
    {
        buf[0] = strtoul(argv[2], NULL, 0);
        buf[1] = strtoul(argv[3], NULL, 0);
        if (write(fd, buf, 2) != 2)
            printf("write err, addr = 0x%02x, data = 0x%02x\n", buf[0], buf[1]);
    }
    else
    {
        print_usage(argv[0]);
        return -1;
    }
#endif
#if 0
 if ((strcmp(argv[1], "w") == 0) && (argc == 4))
    {
        buf[0] = strtoul(argv[2], NULL, 0);
        buf[1] = strtoul(argv[3], NULL, 0);
		           printf("bf write , addr = 0x%02x, data = 0x%02x\n", buf[0], buf[1]);
        if (write(fd, buf, 2) != 2)
            printf("write err, addr = 0x%02x, data = 0x%02x\n", buf[0], buf[1]);
    }

#endif

        write(fd, buf, 2);
            printf("write err, addr = %d, data = %d\n", buf[0][0], buf[0][1]);
    return 0;
}

