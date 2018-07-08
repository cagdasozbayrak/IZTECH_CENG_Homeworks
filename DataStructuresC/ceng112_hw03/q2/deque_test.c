#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "deque.h"

#define SIM_DURATION 30

int main(int argc, char **argv)
{
        srand(time(0));

        struct Deque *deq = deque_new(sizeof(int));

        int t = 0;
        while (t++ < SIM_DURATION) {
                int action = rand() % 5;
                int r;

                switch (action) {
                case 0: // add random number to the front of the deque
                        r = rand() % 10;
                        put_front(deq, &r);
                        printf("t = %d: Adding %d to the front of the deque, deque size = %d\n",
                               t, r, deque_size(deq));
                        break;
                case 1: // add random number to the back of the deque
			r = rand() % 10;
                        put_back(deq, &r);
                        printf("t = %d: Adding %d to the back of the deque, deque size = %d\n",
                               t, r, deque_size(deq));
                        break;
                case 2: // get the first item
                        if (!deque_is_empty(deq)) {
                                get_front(deq, &r);
                                printf("t = %d: Took %d from the front of the deque, deque size = %d\n",
                                       t, r, deque_size(deq));
                        } else {
                                printf("t = %d:\n", t);
                        }
                        break;
                case 3: // get the last item
                        if (!deque_is_empty(deq)) {
                                get_back(deq, &r);
                                printf("t = %d: Took %d from the end of the deque, deque size = %d\n",
                                       t, r, deque_size(deq));
                        } else {
                                printf("t = %d:\n", t);
                        }
                        break;
                default:
                case 4: // do nothing
                        printf("t = %d:\n", t);
                        break;
                }

                fflush(stdout);
                sleep(1);
        }

        deque_free(deq);

        return EXIT_SUCCESS;
}

/* Local Variables: */
/* mode: c          */
/* compile-command: "make queue-test" */
/* End:             */
