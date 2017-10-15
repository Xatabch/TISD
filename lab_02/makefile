ifeq ($(mode), debug)
    # Отладочная сборка: добавим генерацию отладочной информации
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    # Финальная сборка: исключим отладочную информацию и утверждения (asserts)
    CFLAGS += -DNDEBUG -g0
endif

main.exe: main.o kindbook.o decidepole.o getnewparam.o getrecords.o sorttable.o sortnottable.o writefile.o readline.o tick.o
	gcc -o main.exe kindbook.o decidepole.o getnewparam.o getrecords.o sorttable.o sortnottable.o writefile.o readline.o tick.o main.o
main.o: main.c decidepole.h kindbook.h main.h getnewparam.h getrecords.h sorttable.h sortnottable.h writefile.h readline.h tick.h
	gcc -std=c99 -Wall -Werror -c main.c
tick.o: tick.c tick.h
	gcc -std=c99 -Wall -Werror -c tick.c
readline.o: readline.c readline.h
	gcc -std=c99 -Wall -Werror -c readline.c
writefile.o: writefile.c writefile.h
	gcc -std=c99 -Wall -Werror -c writefile.c
sortnottable.o: sortnottable.c sortnottable.h
	gcc -std=c99 -Wall -Werror -c sortnottable.c
sorttable.o: sorttable.c sorttable.h
	gcc -std=c99 -Wall -Werror -c sorttable.c
getrecords.o: getrecords.c getrecords.h
	gcc -std=c99 -Wall -Werror -c getrecords.c
getnewparam.o: getnewparam.c getnewparam.h
	gcc -std=c99 -Wall -Werror -c getnewparam.c
decidepole.o: decidepole.c decidepole.h
	gcc -std=c99 -Wall -Werror -c decidepole.c
kindbook.o: kindbook.c kindbook.h
	gcc -std=c99 -Wall -Werror -c kindbook.c

clean:
	rm *.o *.exe