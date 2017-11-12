ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o pushpop.o getkeybarr.o getia.o getja.o transp.o mult1.o
	gcc -o main.exe pushpop.o getkeybarr.o getia.o getja.o transp.o mult1.o main.o
main.o: main.c pushpop.h getkeybarr.h getia.h getja.h main.h transp.h mult1.h
	gcc -std=c99 -Wall -Werror -c main.c
mult1.o: mult1.c mult1.h main.h pushpop.h
	gcc -std=c99 -Wall -Werror -c mult1.c
transp.o: transp.c transp.h main.h pushpop.h
	gcc -std=c99 -Wall -Werror -c transp.c
getja.o: getja.c getja.h pushpop.h main.h
	gcc -std=c99 -Wall -Werror -c getja.c
getia.o: getia.c getia.h main.h
	gcc -std=c99 -Wall -Werror -c getia.c
getkeybarr.o: getkeybarr.c getkeybarr.h main.h
	gcc -std=c99 -Wall -Werror -c getkeybarr.c
pushpop.o: pushpop.c pushpop.h main.h
	gcc -std=c99 -Wall -Werror -c pushpop.c

clean:
	rm *.o *.exe