#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <stdint.h>
#include <unistd.h>
 #include<sys/stat.h>

#define UV_POSIX_DEV_SIZE   32

enum DEV_TYPE {
    DEV_TYPE_UNKOWN = 0,
    DEV_TYPE_ADC,
    DEV_TYPE_DAC,
    DEV_TYPE_SPI,
    DEV_TYPE_I2C,
    DEV_TYPE_UART,
    DEV_TYPE_GPIO,
    DEV_TYPE_PWM,
    DEV_TYPE_FS,
};

typedef struct uv_posix_dev_t {
    const char *name;
    int type;
    intptr_t dev;
} uv_posix_dev_t;

static uv_posix_dev_t g_devs[UV_POSIX_DEV_SIZE];
static int init = 0;
int uv_posix_open (const char *__file, int __oflag, int mode){
    int dev_type = DEV_TYPE_UNKOWN;
    int ret = -1;
    void *dev = NULL;
    if( !strncmp(__file, "/dev/adc/", strlen("/dev/adc/")) ){
        dev_type = DEV_TYPE_ADC;
    } else if( !strncmp(__file, "/dev/dac/", strlen("/dev/dac/")) ){
        dev_type = DEV_TYPE_DAC;
    } else if( !strncmp(__file, "/dev/spi/", strlen("/dev/spi/")) ){
        dev_type = DEV_TYPE_SPI;
    } else if( !strncmp(__file, "/dev/i2c/", strlen("/dev/i2c/")) ){
        dev_type = DEV_TYPE_I2C;
    } else if( !strncmp(__file, "/dev/uart/", strlen("/dev/uart/")) ){
        dev_type = DEV_TYPE_UART;
    } else if( !strncmp(__file, "/dev/gpio/", strlen("/dev/gpio/")) ){
        dev_type = DEV_TYPE_GPIO;
    } else if( !strncmp(__file, "/dev/pwm/", strlen("/dev/pwm/")) ){
        dev_type = DEV_TYPE_PWM;
    } else {
        const char *smode = "r";
        switch (mode) {
        case O_RDONLY: smode = "r";
        case O_RDWR: smode = "rw";
        case O_WRONLY:smode = "w";
        }
        dev = fopen(__file, smode);
        if( !dev )
            return -1;
        dev_type = DEV_TYPE_FS;
    }
    if( dev_type == DEV_TYPE_UNKOWN )
        return -1;
    if( init == 0 ){
       memset(g_devs, 0, sizeof (uv_posix_dev_t) * UV_POSIX_DEV_SIZE);
       init = 1;
    }

    for(int i = 0; i < UV_POSIX_DEV_SIZE; i++) {
        if( g_devs[i].type == DEV_TYPE_UNKOWN ){
            ret = i;
            break;
        }
    }

    if( ret == -1 )
        return -1;

    switch (dev_type) {
    case DEV_TYPE_ADC:
    case DEV_TYPE_DAC:
    case DEV_TYPE_SPI:
    case DEV_TYPE_I2C:
    case DEV_TYPE_UART:
    case DEV_TYPE_GPIO:
    case DEV_TYPE_PWM:{
        int fd = open(__file, __oflag, mode);
        if( fd < 0 )
            return -1;
        g_devs[ret].dev = fd;
        g_devs[ret].name = __file;
        g_devs[ret].type = dev_type;
    }break;
    case DEV_TYPE_FS:{
        g_devs[ret].dev = (intptr_t)dev;
        g_devs[ret].name = __file;
        g_devs[ret].type = dev_type;
    }break;
    }

    return ret;
}

static int check_fd(int fd){
    if( fd < 0 || fd >= UV_POSIX_DEV_SIZE )
        return 0;
    return 1;
}

static int check_fd_is_fs(int fd){
    if( fd < 0 || fd >= UV_POSIX_DEV_SIZE )
        return 0;
    if( g_devs[fd].type != DEV_TYPE_FS)
        return 0;
    return 1;
}

int uv_posix_write (int __fd, const void *__buf, size_t __n){
    if( !check_fd(__fd) )
        return -1;
    uv_posix_dev_t *dev = g_devs + __fd;
    switch (dev->type) {
    case DEV_TYPE_ADC:
    case DEV_TYPE_DAC:
    case DEV_TYPE_SPI:
    case DEV_TYPE_I2C:
    case DEV_TYPE_UART:
    case DEV_TYPE_GPIO:
    case DEV_TYPE_PWM:{
        return (int)write(dev->dev, __buf, __n);
    }
    case DEV_TYPE_FS:{
        return (int)fwrite(__buf, 1, __n, (FILE*)dev->dev);
    }
    }
    return 0;
}

int uv_posix_read (int __fd, void *__buf, size_t __nbytes){
    if( !check_fd(__fd) )
        return -1;
    uv_posix_dev_t *dev = g_devs + __fd;
    switch (dev->type) {
    case DEV_TYPE_ADC:
    case DEV_TYPE_DAC:
    case DEV_TYPE_SPI:
    case DEV_TYPE_I2C:
    case DEV_TYPE_UART:
    case DEV_TYPE_GPIO:
    case DEV_TYPE_PWM:{
        return (int)read(dev->dev, __buf, __nbytes);
    }
    case DEV_TYPE_FS:{
        return (int)fread(__buf, 1, __nbytes, (FILE*)dev->dev);
    }
    }
    return 0;
}

int uv_posix_close (int __fd){
    if( !check_fd(__fd) )
        return -1;
    uv_posix_dev_t *dev = g_devs + __fd;
    switch (dev->type) {
    case DEV_TYPE_ADC:
    case DEV_TYPE_DAC:
    case DEV_TYPE_SPI:
    case DEV_TYPE_I2C:
    case DEV_TYPE_UART:
    case DEV_TYPE_GPIO:
    case DEV_TYPE_PWM:{
        return close(dev->dev);
    }
    case DEV_TYPE_FS:{
        return fclose((FILE*)dev->dev);
    }
    }
    return -1;
}

int uv_posix_fsync (int __fd){
    if( !check_fd_is_fs(__fd) )
        return -1;
}

int uv_posix_fdatasync (int __fildes){
    if( !check_fd_is_fs(__fildes) )
        return -1;
}

int uv_posix_stat(const char *path, struct stat *buf){
    return stat(path, buf);
}

int uv_posix_fstat (int __fd, struct stat *__buf){
    if( !check_fd_is_fs(__fd) )
        return -1;
    uv_posix_dev_t *dev = g_devs + __fd;
    return fstat(dev->dev, __buf);
}

int uv_posix_rename(char *oldname, char *newname){
    rename(oldname, newname);
}

