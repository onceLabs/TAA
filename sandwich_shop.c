#include "sandwich_shop.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *sandwich_names[] = {
  "Ham",
  "Cuban",
  "Chicken",
  "Tofu",
  "Grilled Cheese",
  "BLT",
  "Lobster Roll",
  "Manwich",
  "Sloppy Joe",
  "Monte Cristo",
  "Nutella",
  "PBJ"
};

void print_sandwich(sandwich_t *sandwich)
{
  printf("\n%c,\n\tBread: %02x\n\tMeat: %02x\n\tCheese: %02x,\n\tCondiments: %02x",
    sandwich->name,
    sandwich->bread,
    sandwich->meat,
    sandwich->cheese,
    sandwich->condiment);
}

char **get_menu(uint8_t *count)
{
    *count = sizeof(sandwich_names) / sizeof(sandwich_names[0]);
    return sandwich_names;
}

void submit_order(char *sandwiches[], uint8_t count, order_complete_cb_t cb)
{

  char order_error[] = "Sorry, this is not available";
  static int order_number = 0;
  order_number++;

  order_t *order        = (order_t *)malloc(sizeof(uint8_t));
  order->sandwiches     = (sandwich_t *)malloc(count * sizeof(sandwich_t));
  order->sandwich_count = count;
  order->order_number   = order_number;
  sandwich_t *current_sandwitch;

  for (uint8_t i = 0; i < count; i++)
  {
    if (strcmp(sandwiches[i], "Ham") == 0)
    {
      order->sandwiches[i].bread     = BREAD_TYPE_WHEAT;
      order->sandwiches[i].meat      = MEAT_TYPE_HAM;
      order->sandwiches[i].cheese    = CHEESE_TYPE_AMERICAN;
      order->sandwiches[i].condiment = CONDIMENT_TYPE_HORSERADISH | CONDIMENT_TYPE_MUSTARD;
    }
    else if (strcmp(sandwiches[i], "Cuban") == 0)
    {
      order->sandwiches[i].bread              = BREAD_TYPE_WHITE;
      order->sandwiches[i].meat               = MEAT_TYPE_HAM;
      order->sandwiches[i].cheese             = CHEESE_TYPE_SWISS;
      order->sandwiches[i].condiment          = CONDIMENT_TYPE_MAYONNAISE | CONDIMENT_TYPE_MUSTARD | CONDIMENT_TYPE_HORSERADISH;
      order->sandwiches[i].pickles            = true;
      order->sandwiches[i].time_in_toaster_s  = 120;
    }
    else if (strcmp(sandwiches[i], "Chicken") == 0)
    {
      order->sandwiches[i].bread     = BREAD_TYPE_WHITE;
      order->sandwiches[i].meat      = MEAT_TYPE_CHICKEN;
      order->sandwiches[i].cheese    = CHEESE_TYPE_BLUE | CHEESE_TYPE_PEPPER_JACK;
      order->sandwiches[i].condiment = CONDIMENT_TYPE_MAYONNAISE | CONDIMENT_TYPE_MUSTARD;
    }
    else if (strcmp(sandwiches[i], "Grilled Cheese") == 0)
    {
      order->sandwiches[i].bread             = BREAD_TYPE_WHITE;
      order->sandwiches[i].meat              = MEAT_TYPE_NONE;
      order->sandwiches[i].condiment         = CONDIMENT_TYPE_MAYONNAISE | CONDIMENT_TYPE_MUSTARD;
      order->sandwiches[i].toasted           = true;
      order->sandwiches[i].time_in_toaster_s = 90;
      order->sandwiches[i].cheese = 
        CHEESE_TYPE_BLUE 
        | CHEESE_TYPE_SWISS 
        | CHEESE_TYPE_CHEDDAR 
        | CHEESE_TYPE_AMERICAN 
        | CHEESE_TYPE_PEPPER_JACK;
    }
    else if (strcmp(sandwiches[i], "BLT") == 0)
    {
      order->sandwiches[i].bread     = BREAD_TYPE_WHEAT;
      order->sandwiches[i].meat      = MEAT_TYPE_BACON;
      order->sandwiches[i].cheese    = CHEESE_TYPE_BLUE;
      order->sandwiches[i].condiment = CONDIMENT_TYPE_MAYONNAISE | CONDIMENT_TYPE_MUSTARD;
      order->sandwiches[i].lettuce   = true;
      order->sandwiches[i].tomato    = true;
    }
    else
    {
      order->sandwiches[i].error = (char*)malloc(strlen(order_error)*sizeof(char));
      order->sandwiches[i].error = order_error;
    }
    order->sandwiches[i].name = (char *)malloc(strlen(sandwiches[i]));
    memcpy(order->sandwiches[i].name, sandwiches[i], strlen(sandwiches[i]));
  }
  cb(order, NULL);
  free(order);
}