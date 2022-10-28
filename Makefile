
CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -g
OBJECTS = master.o actor/actor.o controller/controller.o display/display.o display/subject.o display/observer.o dungeon/dungeon.o dungeon/floor.o dungeon/chamber.o dungeon/cell.o dungeon/coordinate.o item/item.o item/potion.o item/gold.o race/race.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = master
${EXEC}:${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
