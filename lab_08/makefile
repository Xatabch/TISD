ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o allocmtr.o getmatr.o checktree.o
	gcc -o main.exe allocmtr.o getmatr.o checktree.o main.o
main.o: main.c allocmtr.h getmatr.h main.h checktree.h
	gcc -std=c99 -Wall -Werror -c main.c
checktree.o: checktree.c checktree.h main.h allocmtr.h
	gcc -std=c99 -Wall -Werror -c checktree.c
getmatr.o: getmatr.c getmatr.h main.h
	gcc -std=c99 -Wall -Werror -c getmatr.c
allocmtr.o: allocmtr.c allocmtr.h main.h
	gcc -std=c99 -Wall -Werror -c allocmtr.c

clean:
	rm *.o *.exe