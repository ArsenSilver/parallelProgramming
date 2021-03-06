#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#define divider 100

int
check_open(const char *pathname, int flags, mode_t mode)
{
    int fd = open(pathname, flags, mode);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    return fd;
}

void
read_and_write32(int fd, int32_t size, char type)
{
    size_t i;
    size_t j;
    int32_t temp;

    write(fd, &type, sizeof(char));    
    write(fd, &size, sizeof(int32_t));
    for(i = 0; i < size; ++i)
    {   
        for(j = 0; j < size; ++j)
        {
            srand(i+500*j);
            temp = rand()%divider;
            write(fd, &temp, sizeof(int32_t));
            printf("a[%ld][%ld] = %d", i, j, temp);
        }
    } 
}

void
read_and_write64(int fd, int32_t size, char type)
{
    size_t i;
    size_t j;
    int64_t temp; 

    write(fd, &type, sizeof(char));
    write(fd, &size, sizeof(int32_t));
    for(i=0; i < size; ++i)
    {
        for(j=0; j < size; ++j)
        {
            srand(i+500*j);
            temp = rand()%divider;
            write(fd, &temp, sizeof(int64_t));
             printf("a[%ld][%ld] = %ld\n", i, j, temp);
            
        }
    }
}

int
main(int argc, char **argv)
{
    int fd;
    int32_t size = 0;
    char type = 0;

    if (argc != 4)
    {
        fputs("usage: ./gen_a <pathname> <size> <type>\n", stderr);
        return 6;
    }

    fd = check_open(argv[1], O_WRONLY | O_CREAT, 0600);
    type =  argv[2][0];
    size = atoi(argv[3]);
    
    if(type == 'd')
    read_and_write32(fd, size, type);
    else if(type == 'l')
    read_and_write64(fd, size, type);
    else
    puts("wrong type\n");
    
    close(fd);
    return 0;
}
