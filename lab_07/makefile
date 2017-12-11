ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o createnode.o insert.o apply.o getnum.o createdot.o tick.o rotateright.o helpfunc.o rotateleft.o balance.o insertavl.o balancetree.o openhash.o closehash.o find.o delete.o
	gcc -o main.exe createnode.o insert.o apply.o getnum.o createdot.o tick.o rotateright.o helpfunc.o rotateleft.o balance.o insertavl.o balancetree.o openhash.o closehash.o find.o delete.o main.o
main.o: main.c main.h createnode.h insert.h apply.h getnum.h createdot.h tick.h rotateright.h helpfunc.h rotateleft.h balance.h insertavl.h balancetree.h openhash.h closehash.h find.h delete.h
	gcc -std=c99 -Wall -Werror -c main.c
delete.o: delete.c delete.h main.h balancetree.h
	gcc -std=c99 -Wall -Werror -c delete.c
find.o: find.c find.h main.h
	gcc -std=c99 -Wall -Werror -c find.c
closehash.o: closehash.c closehash.h main.h tick.h
	gcc -std=c99 -Wall -Werror -c closehash.c
openhash.o: openhash.c openhash.h main.h tick.h
	gcc -std=c99 -Wall -Werror -c openhash.c
balancetree.o: balancetree.c balancetree.h main.h balance.h
	gcc -std=c99 -Wall -Werror -c balancetree.c
insertavl.o: insertavl.c insertavl.h main.h insert.h balance.h balancetree.h
	gcc -std=c99 -Wall -Werror -c insertavl.c
balance.o: balance.c balance.h main.h helpfunc.h rotateleft.h rotateright.h
	gcc -std=c99 -Wall -Werror -c balance.c
rotateleft.o: rotateleft.c rotateleft.h main.h helpfunc.h
	gcc -std=c99 -Wall -Werror -c rotateleft.c
rotateright.o: rotateright.c rotateright.h main.h helpfunc.h
	gcc -std=c99 -Wall -Werror -c rotateright.c
helpfunc.o: helpfunc.c helpfunc.h main.h
	gcc -std=c99 -Wall -Werror -c helpfunc.c
tick.o: tick.c tick.h
	gcc -std=c99 -Wall -Werror -c tick.c
createdot.o: createdot.c createdot.h apply.h main.h
	gcc -std=c99 -Wall -Werror -c createdot.c
getnum.o: getnum.c getnum.h createnode.h insert.h main.h helpfunc.h balance.h balancetree.h find.h apply.h find.h tick.h
	gcc -std=c99 -Wall -Werror -c getnum.c 
apply.o: apply.c apply.h main.h helpfunc.h
	gcc -std=c99 -Wall -Werror -c apply.c
insert.o: insert.c insert.h main.h createnode.h
	gcc -std=c99 -Wall -Werror -c insert.c
createnode.o: createnode.c createnode.h main.h
	gcc -std=c99 -Wall -Werror -c createnode.c

clean:
	rm *.o *.exe *.gv *.png