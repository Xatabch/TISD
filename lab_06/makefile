ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o createnode.o insert.o applypre.o
	gcc -o main.exe createnode.o insert.o applypre.o main.o
main.o: main.c main.h createnode.h insert.h applypre.h
	gcc -std=c99 -Wall -Werror -c main.c
applypre.o: applypre.c applypre.h main.h
	gcc -std=c99 -Wall -Werror -c applypre.c
insert.o: insert.c insert.h main.h
	gcc -std=c99 -Wall -Werror -c insert.c
createnode.o: createnode.c createnode.h main.h
	gcc -std=c99 -Wall -Werror -c createnode.c

clean:
	rm *.o *.exe