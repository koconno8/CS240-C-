all: PrereqCheck ScheduleCheck Waitlist

PrereqCheck: PrereqCheck.o
	g++ -o PrereqCheck PrereqCheck.o

PrereqCheck.o: PrereqCheck.cpp
	g++ -c PrereqCheck.cpp

ScheduleCheck: ScheduleCheck.o
	g++ -o ScheduleCheck ScheduleCheck.o

ScheduleCheck.o: ScheduleCheck.cpp
	g++ -c ScheduleCheck.cpp

Waitlist: Waitlist.o
	g++ -o Waitlist Waitlist.o

Waitlist.o: Waitlist.cpp
	g++ -c Waitlist.cpp

clean:
	rm -f PrereqCheck PrereqCheck.o ScheduleCheck ScheduleCheck.o Waitlist Waitlist.o