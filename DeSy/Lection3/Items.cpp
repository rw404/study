#include <iostream>

producer()
{
  int item;
  while(true) {
    produce_item(&item);
    P(empty);
    P(mutex);
    enter_item(item);
    V(mutex);
    V(full);
  }
}

consumer()
{
  int item;
  while(true)
    P(full);
    P(mutex);
    remove_item(&item);
    V(mutex);
    V(empty);
    consume_item(&item);
}
