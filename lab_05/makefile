ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o pushpop.o getkeybarr.o transp.o mult1.o alloc.o getfilearr.o mult2.o tick.o transpgust.o
	gcc -o main.exe pushpop.o getkeybarr.o transp.o mult1.o alloc.o getfilearr.o mult2.o tick.o transpgust.o main.o
main.o: main.c pushpop.h getkeybarr.h main.h transp.h mult1.h alloc.h getfilearr.h mult2.h tick.h transpgust.h
	gcc -std=c99 -Wall -Werror -c main.c
transpgust.o: transpgust.c transpgust.h pushpop.h main.h
	gcc -std=c99 -Wall -Werror -c transpgust.c
tick.o: tick.c tick.h
	gcc -std=c99 -Wall -Werror -c tick.c
mult2.o: mult2.c mult2.h
	gcc -std=c99 -Wall -Werror -c mult2.c
getfilearr.o: getfilearr.c getfilearr.h
	gcc -std=c99 -Wall -Werror -c getfilearr.c
alloc.o: alloc.c alloc.h
	gcc -std=c99 -Wall -Werror -c alloc.c
mult1.o: mult1.c mult1.h main.h pushpop.h tick.h
	gcc -std=c99 -Wall -Werror -c mult1.c
transp.o: transp.c transp.h main.h pushpop.h
	gcc -std=c99 -Wall -Werror -c transp.c
getkeybarr.o: getkeybarr.c getkeybarr.h main.h getfilearr.h alloc.h pushpop.h
	gcc -std=c99 -Wall -Werror -c getkeybarr.c
pushpop.o: pushpop.c pushpop.h main.h
	gcc -std=c99 -Wall -Werror -c pushpop.c

clean:
	rm *.o *.exe