#include "brick.h"
#include "board.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string file1 = "../test1";

int main(int argc, char* argv[]) {
	cout << "Reading from file: " << file1 << endl;

	string inputString;
	ifstream input(file1+".txt");
	if(input.is_open()){
		while(getline (input, inputString))
		{
			//inputString.append(inputString);
			
			cout << "I read this line: " << inputString << endl;

			Board *board = new Board(inputString);
			board->currentOutputFile = file1 + "OUTPUT.txt";
			ofstream output(board->currentOutputFile);
			board->drawBoard();
			board->writeToOutput(output);
			input.close();//Force close reading so we only read first line.. for now.
			output.close();
		}
		
	}else{
		cout << "Unable to open file." << endl;
	}

	system("pause");
	return 0;
}


