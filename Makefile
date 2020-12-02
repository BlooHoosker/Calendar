DIR=src/

all: compile doc

compile: main.o ccalendar.o cevent.o clongevent.o crepeatingevent.o cdate.o ctime.o mylib.o
	g++ main.o ccalendar.o cevent.o clongevent.o crepeatingevent.o cdate.o ctime.o mylib.o -o stahlmar

main.o: $(DIR)main.cpp
	g++ -c $(DIR)main.cpp -o main.o

ccalendar.o: $(DIR)ccalendar.cpp $(DIR)ccalendar.h
	g++ -c $(DIR)ccalendar.cpp -o ccalendar.o

cevent.o: $(DIR)cevent.cpp $(DIR)cevent.h
	g++ -c $(DIR)cevent.cpp -o cevent.o

clongevent.o: $(DIR)clongevent.cpp $(DIR)clongevent.h
	g++ -c $(DIR)clongevent.cpp -o clongevent.o

crepeatingevent.o: $(DIR)crepeatingevent.cpp $(DIR)crepeatingevent.h
	g++ -c $(DIR)crepeatingevent.cpp -o crepeatingevent.o

cdate.o: $(DIR)cdate.cpp $(DIR)cdate.h
	g++ -c $(DIR)cdate.cpp -o cdate.o

ctime.o: $(DIR)ctime.cpp $(DIR)ctime.h
	g++ -c $(DIR)ctime.cpp -o ctime.o

mylib.o: $(DIR)mylib.cpp $(DIR)mylib.h
	g++ -c $(DIR)mylib.cpp -o mylib.o

run: stahlmar
	./stahlmar

clean:
	rm -rf *.o stahlmar

doc:
	doxygen src/doc_config