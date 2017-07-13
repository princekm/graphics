cc=cc
libs=-lgraph -lm
exes= car cyc clock fan
all:
	$(cc) -o car car.c $(libs)
	$(cc) -o cyc cyc.c $(libs)
	$(cc) -o clock clock.c $(libs)
	$(cc) -o fan fan.c $(libs)
clean:
	rm $(exes)
