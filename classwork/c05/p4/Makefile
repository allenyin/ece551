CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
RCFLAGS=-Wall -Werror -std=gnu99 -pedantic -DREPORT_COVERAGE
OBJS=tester.o code.o
ROBJS=tester.rpt.o report.rpt.o

all: tester tester-report
tester-report: $(ROBJS)
	gcc $(CFLAGS) -o tester-report $(ROBJS)
tester: $(OBJS)
	gcc $(CFLAGS) -o tester $(OBJS)

%.o:%.c code.h
	gcc $(CFLAGS) -c $<
%.rpt.o:%.c code.h
	gcc $(RCFLAGS)  -c $< -o $@

clean: 
	rm -f tester tester-report $(OBJS) tester.rpt.o *~