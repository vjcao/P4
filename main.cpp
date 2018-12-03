#include <iostream>
#include <iomanip>
#include <getopt.h>
#include "PartA.h"

using namespace std;

void printHelp() {

	return;
}

void getOptions(int argc, char *argv[], string &mode) {
	struct option long_options[] = {
		{ "mode", required_argument, nullptr, 'm' },
		{ "help", no_argument, nullptr, 'h'},
		{ nullptr, 0, nullptr, '\0' }
	};

	int choice;
	int option_index = 0;
	while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
		switch (choice) {
			case 'm': {
				mode = optarg;
				if (mode != "MST" && mode != "FASTTSP" && mode != "OPTTSP") {
					cout << "ERROR: invalid mode specified";
				}
				break;
			}
			case 'h': {
				printHelp();
				exit(0);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	
	cout << setprecision(2);
	cout << fixed;

	string mode;

	getOptions(argc, argv, mode);

	switch (mode[0]) {
		case 'M': {
			vector<Pokemon> graph;
			readFile(graph);
			double weight = findMST(graph);
			cout << weight << "\n";
			printMST(graph);
			break;
		}
		case 'F': {
			break;
		}
		case 'O': {
			break;
		}
	}
	return 0;
}