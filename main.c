#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "sandwich_shop.h"

void order_complete_cb(order_t *order, void *context)
{
  order_t *completed_order;

  /* Copy over order */
  completed_order = (order_t *)malloc(sizeof(order_t));
  completed_order->sandwiches = (sandwich_t *)malloc(sizeof(sandwich_t)*(order->sandwich_count));
  completed_order->sandwich_count = order->sandwich_count;

  for (int i = 0; i < completed_order->sandwich_count; i++){
    completed_order->sandwiches[i].bread = order->sandwiches[i].bread;
    completed_order->sandwiches[i].cheese = order->sandwiches[i].cheese;
    completed_order->sandwiches[i].condiment = order->sandwiches[i].condiment;
    completed_order->sandwiches[i].error = order->sandwiches[i].error;
    completed_order->sandwiches[i].lettuce = order->sandwiches[i].lettuce;
    completed_order->sandwiches[i].meat = order->sandwiches[i].meat;
    completed_order->sandwiches[i].name = (char *)malloc(strlen(order->sandwiches[i].name));
    completed_order->sandwiches[i].name = order->sandwiches[i].name;
    completed_order->sandwiches[i].pickles = order->sandwiches[i].pickles;
    completed_order->sandwiches[i].time_in_toaster_s = order->sandwiches[i].time_in_toaster_s;
    completed_order->sandwiches[i].toasted = order->sandwiches[i].toasted;
    completed_order->sandwiches[i].tomato = order->sandwiches[i].tomato;
  }

  printf("\n\nOrder #%d Complete:", order->order_number);

  for (uint8_t i = 0; i < completed_order->sandwich_count; i++)
  {
    if ((completed_order->sandwiches[i]).error){
      print_sandwich(&completed_order->sandwiches[i]); 
    } else {
      printf("\n%s, \n\tError: %s", completed_order->sandwiches[i].name, completed_order->sandwiches[i].error);
    }
  }
  printf("\n\n");
}

int main()
{
  srand(time(NULL));

  uint8_t available_sandwiches_count = 0;
  char *sandwich_names = get_menu(&available_sandwiches_count);

  uint8_t x = 3;

  // Infinite sandwiches
  while (x--)
  {
    // How many sandwiches to order
    int sw_count = (((uint16_t)rand()) % 11) + 1;
    char *sandwiches[sw_count];

    for (uint8_t i = 0; i < sw_count; i++)
    {
      int sw_index = ((uint16_t)rand()) % available_sandwiches_count;
      sandwiches[i] = sandwich_names[sw_index];
    }
    submit_order(sandwiches, sw_count, order_complete_cb);
    //++x;
  }
  return 0;
}