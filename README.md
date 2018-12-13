协程库

example C

```c
#include <stdio.h>
#include "coroutine.h"

struct args {
	int n;
};

static void
foo(comng_t schedule, void *ud) {
	struct args* arg = (struct args*)ud;
	int start = arg->n;
	int i;
	for (i = 0; i < 5; i++) {
		printf("coroutine %d : %d\n", coroutine_running(schedule), start + i);
		coroutine_yield(schedule);
	}
}

static void
test(comng_t schedule) {
	struct args arg1 = { 0 };
	struct args arg2 = { 100 };

	int co1 = coroutine_create(schedule, foo, &arg1);
	int co2 = coroutine_create(schedule, foo, &arg2);
	printf("main start\n");
	while (coroutine_status(schedule, co1) && coroutine_status(schedule, co2)) {
		coroutine_resume(schedule, co1);
		coroutine_resume(schedule, co2);
	}
	printf("main end\n");
}

int main(int argc, char *argv[])
{
	comng_t schedule = coroutine_start();
	test(schedule);
	coroutine_close(schedule);
	return 0;
}
```

