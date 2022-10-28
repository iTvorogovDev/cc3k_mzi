#include "display/display.h"
#include "controller/controller.h"
#include "race/race.h"
#include "actor/actor.h"
#include "dungeon/dungeon.h"
#include "display/subject.h"
#include "display/observer.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string mapFile{"input.txt"};
	shared_ptr<Dungeon> gameState = make_shared<Dungeon>(mapFile , make_shared<Player>(make_shared<Shade>()));
	shared_ptr<Display> output = make_shared<Display>(cout, gameState);
	gameState->attach(output.get());
	shared_ptr<Controller> inputAndRules = make_shared<Controller>(gameState);
	
	do {
		cout << string(100, '\n');//clears screen
		
		//start game
		char raceSym;
		char raceSymbols[5] = {'s', 'd', 'g', 'v', 't'};
		
		output->startMessage();
		bool acceptable = false;
		while (!acceptable) {
			cin >> raceSym;
			if (find(begin(raceSymbols), end(raceSymbols), raceSym) != end(raceSymbols)) {
				inputAndRules->raceCommands(raceSym);
				acceptable = true;
			} else {
				cout << raceSym << " is not a valid choice for race, please try again" << endl;
			}
		}

		//play section
		string acceptableCommands[8] = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};
		string commands;
		string secondWord;
                inputAndRules->notifyDungeon();
		while (!inputAndRules->isDone()) {
                    inputAndRules->notifyDungeon();
			cin >> commands;
			if (commands == "a" || commands == "u") {
				inputAndRules->gameCommands(commands);
			} else if (commands == "f" || commands == "r" || commands == "q") {
				inputAndRules->changeStateCommands(commands);
			} else if (find(begin(acceptableCommands), end(acceptableCommands), commands) != end(acceptableCommands)) {
				inputAndRules->moveCommands(commands);
			}
		}
		output->endMessage();
	} while (inputAndRules->doRestart());
        return 0;
}
