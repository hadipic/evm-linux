#ifdef CONFIG_EVM_MODULE_GPIO
#include "evm_module.h"
#include "linux_systemio.h"

#define GPIO_INTERFACE "/sys/class/gpio/"
#define GPIO_EXPORT "export"
#define GPIO_UNEXPORT "unexport"
#define GPIO_DIRECTION "direction"
#define GPIO_EDGE "edge"
#define GPIO_VALUE "value"
#define GPIO_PIN_INTERFACE "gpio%d/"
#define GPIO_PIN_FORMAT_EXPORT GPIO_INTERFACE "export"
#define GPIO_PIN_FORMAT_UNEXPORT GPIO_INTERFACE "unexport"
#define GPIO_PIN_FORMAT GPIO_INTERFACE GPIO_PIN_INTERFACE
#define GPIO_PIN_FORMAT_DIRECTION GPIO_PIN_FORMAT GPIO_DIRECTION
#define GPIO_PIN_FORMAT_EDGE GPIO_PIN_FORMAT GPIO_EDGE
#define GPIO_PIN_FORMAT_VALUE GPIO_PIN_FORMAT GPIO_VALUE

#define GPIO_PATH_BUFFER_SIZE DEVICE_IO_PATH_BUFFER_SIZE
#define GPIO_PIN_BUFFER_SIZE DEVICE_IO_PIN_BUFFER_SIZE
#define GPIO_VALUE_BUFFER_SIZE 10

static const char* gpio_edge_string[] = { "none", "rising", "falling", "both" };

typedef struct _gpio_dev_t
{
    int pin;
    int direction;
    int mode;
    int edge;
    int value_fd;
} _gpio_dev_t;

static int gpio_set_direction(int pin, int direction) {
	char direction_path[GPIO_PATH_BUFFER_SIZE];
	snprintf(direction_path, GPIO_PATH_BUFFER_SIZE, GPIO_PIN_FORMAT_DIRECTION,
			pin);
	const char* buffer = (direction == EVM_GPIO_DIRECTION_IN) ? "in" : "out";
	return systemio_open_write_close(direction_path, buffer);
}

static int gpio_set_mode(int pin, int mode) {
  	return 1;
}

static void gpio_set_value_fd(_gpio_dev_t* gpio, int fd) {
    gpio->value_fd = fd;
}

static int gpio_set_edge(_gpio_dev_t* gpio) {
	char edge_path[GPIO_PATH_BUFFER_SIZE];
	snprintf(edge_path, GPIO_PATH_BUFFER_SIZE, GPIO_PIN_FORMAT_EDGE, gpio->pin);
    systemio_open_write_close(edge_path, gpio_edge_string[gpio->edge]);

    if (gpio->direction == EVM_GPIO_DIRECTION_IN && gpio->edge != EVM_GPIO_EDGE_NONE) {
        char value_path[GPIO_PATH_BUFFER_SIZE];
        snprintf(value_path, GPIO_PATH_BUFFER_SIZE, GPIO_PIN_FORMAT_VALUE,
             gpio->pin);
        if ((gpio->value_fd = open(value_path, O_RDONLY)) < 0) {
            return 0;
        }
        return 1;
    }
    return 1;
}

void *evm_gpio_open(evm_t *e, evm_val_t v){
	_gpio_dev_t *dev = evm_malloc(sizeof(_gpio_dev_t));
    EVM_ASSERT(dev);

    evm_val_t val;
    val = evm_prop_get(e, v, "pin");
    if (!evm_is_integer(e, val))
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'pin' member"));
    }
    dev->pin = evm_2_integer(e, val);

	char exported_path[GPIO_PATH_BUFFER_SIZE];
	snprintf(exported_path, GPIO_PATH_BUFFER_SIZE, GPIO_PIN_FORMAT, dev->pin);

	const char* created_files[] = { GPIO_DIRECTION, GPIO_EDGE, GPIO_VALUE };
	int created_files_length = sizeof(created_files) / sizeof(created_files[0]);

	if (!systemio_device_open(GPIO_PIN_FORMAT_EXPORT, dev->pin,
									exported_path, created_files,
									created_files_length)) {
		evm_throw(e, evm_mk_string(e, "Failed to open gpio"));
	}

    val = evm_prop_get(e, v, "direction");
    if (!evm_is_integer(e, val))
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'direction' member"));
    }
    dev->direction = evm_2_integer(e, val);

    val = evm_prop_get(e, v, "mode");
    if (!evm_is_integer(e, val))
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'mode' member"));
    }
    dev->mode = evm_2_integer(e, val);

    // Set direction.
    if (!gpio_set_direction(dev->pin, dev->direction)) {
		evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Failed to set gpio direction"));
	}

	// Set mode.
    if (!gpio_set_mode(dev->pin, dev->mode)) {
		evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Failed to set gpio mode"));
	}

	// Set edge.
    if (!gpio_set_edge(dev)) {
		evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Failed to set gpio edge"));
	}
    return dev;
}

void evm_gpio_set_direction(evm_t *e, void *dev, int value){
    _gpio_dev_t *gpio_dev = dev;
    gpio_set_direction(gpio_dev->pin, value);
}

void evm_gpio_write(evm_t *e, void *dev, int value){
    _gpio_dev_t *gpio_dev = dev;
    char value_path[GPIO_PATH_BUFFER_SIZE];
    snprintf(value_path, GPIO_PATH_BUFFER_SIZE, GPIO_PIN_FORMAT_VALUE, gpio_dev->pin);
    const char* buffer = value ? "1" : "0";
    systemio_open_write_close(value_path, buffer);
}

int evm_gpio_read(evm_t *e, void *dev){
    _gpio_dev_t *gpio_dev = dev;
    char buffer[GPIO_VALUE_BUFFER_SIZE];
    char value_path[GPIO_PATH_BUFFER_SIZE];
    snprintf(value_path, GPIO_PATH_BUFFER_SIZE, GPIO_PIN_FORMAT_VALUE, gpio_dev->pin);

    if (!systemio_open_read_close(value_path, buffer,
                                      GPIO_VALUE_BUFFER_SIZE - 1)) {
        return 0;
    }

    return atoi(buffer);
}

void evm_gpio_close(evm_t *e, void *dev){
    _gpio_dev_t *gpio_dev = dev;
    char buff[GPIO_PIN_BUFFER_SIZE];
    snprintf(buff, GPIO_PIN_BUFFER_SIZE, "%d", gpio_dev->pin);

    gpio_set_value_fd(gpio_dev, -1);
    close(gpio_dev->value_fd);

    systemio_open_write_close(GPIO_PIN_FORMAT_UNEXPORT, buff);
}

void evm_gpio_destroy(evm_t *e, void *dev){
    evm_free(dev);
}
#endif
