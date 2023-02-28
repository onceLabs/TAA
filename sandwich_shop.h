#include <stdint.h>
#include <stdbool.h>

typedef enum
{
  BREAD_TYPE_NONE,
  BREAD_TYPE_WHITE,
  BREAD_TYPE_WHEAT
} bread_type_t;

typedef enum
{
  CONDIMENT_TYPE_NONE,
  CONDIMENT_TYPE_KETCHUP,
  CONDIMENT_TYPE_MUSTARD,
  CONDIMENT_TYPE_HORSERADISH,
  CONDIMENT_TYPE_SAUERKRAUT,
  CONDIMENT_TYPE_MAYONNAISE,
  CONDIMENT_TYPE_BALSAMIC_VINEGAR
} condiment_type_t;

typedef enum
{
  CHEESE_TYPE_NONE,
  CHEESE_TYPE_BLUE,
  CHEESE_TYPE_SWISS,
  CHEESE_TYPE_CHEDDAR,
  CHEESE_TYPE_AMERICAN,
  CHEESE_TYPE_PEPPER_JACK
} cheese_type_t;

typedef enum
{
  MEAT_TYPE_NONE,
  MEAT_TYPE_BALOGNE,
  MEAT_TYPE_BEEF,
  MEAT_TYPE_PORK,
  MEAT_TYPE_MUTTON,
  MEAT_TYPE_HAM,
  MEAT_TYPE_TURKEY,
  MEAT_TYPE_CHICKEN,
  MEAT_TYPE_BACON
} meat_type_t;

typedef struct
{
  char              *name;
  char              *error;
  bread_type_t      bread;
  meat_type_t       meat;
  cheese_type_t     cheese;
  condiment_type_t  condiment;
  bool              lettuce;
  bool              tomato;
  bool              pickles;
  bool              toasted;
  int               time_in_toaster_s;
} sandwich_t;

typedef struct
{
  int order_number;
  int sandwich_count;
  sandwich_t *sandwiches;
} order_t;

typedef void(order_complete_cb_t)(order_t *order, void *context);

char **get_menu(uint8_t *count);

void print_sandwich(sandwich_t *sandwich);

void submit_order(char *sandwiches[], uint8_t count, order_complete_cb_t cb);