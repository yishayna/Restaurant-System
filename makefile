#All Targets
all : rest

rest : bin/Customer.o bin/Action.o bin/Dish.o bin/Table.o bin/Restaurant.o bin/Main.o
	g++ -o bin/rest bin/Customer.o bin/Action.o bin/Dish.o bin/Table.o bin/Restaurant.o bin/Main.o

bin/Customer.o : src/Customer.cpp include/Customer.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Customer.o src/Customer.cpp
	
bin/Action.o : src/Action.cpp include/Action.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp
	
bin/Dish.o : include/Dish.h src/Dish.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Dish.o src/Dish.cpp
	
bin/Table.o : include/Table.h src/Table.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Table.o src/Table.cpp
	
bin/Restaurant.o : src/Restaurant.cpp include/Restaurant.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Restaurant.o src/Restaurant.cpp
	
bin/Main.o : src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp

clean: 
	rm -f bin/*
