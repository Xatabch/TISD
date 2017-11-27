ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o createnode.o insert.o apply.o getnum.o createdot.o find.o delete.o pointcount.o
	gcc -o main.exe createnode.o insert.o apply.o getnum.o createdot.o find.o delete.o pointcount.o main.o
main.o: main.c main.h createnode.h insert.h apply.h getnum.h createdot.h find.h delete.h pointcount.h
	gcc -std=c99 -Wall -Werror -c main.c
pointcount.o: pointcount.c pointcount.h main.h
	gcc -std=c99 -Wall -Werror -c pointcount.c
delete.o: delete.c delete.h find.h main.h apply.h
	gcc -std=c99 -Wall -Werror -c delete.c
find.o: find.c find.h main.h
	gcc -std=c99 -Wall -Werror -c find.c
createdot.o: createdot.c createdot.h apply.h main.h
	gcc -std=c99 -Wall -Werror -c createdot.c
getnum.o: getnum.c getnum.h createnode.h insert.h main.h
	gcc -std=c99 -Wall -Werror -c getnum.c
apply.o: apply.c apply.h main.h
	gcc -std=c99 -Wall -Werror -c apply.c
insert.o: insert.c insert.h main.h createnode.h
	gcc -std=c99 -Wall -Werror -c insert.c
createnode.o: createnode.c createnode.h main.h
	gcc -std=c99 -Wall -Werror -c createnode.c

clean:
	rm *.o *.exe