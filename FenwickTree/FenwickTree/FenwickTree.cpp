#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> fenwickTree;
vector<int> arr;

enum Commands {
	COMMAND_ADD,
	COMMAND_RSQ,
    COMMAND_UNKNOWN
};

Commands convert(const string& str)
{
    if(str == "add") return COMMAND_ADD;
    else if(str == "rsq") return COMMAND_RSQ;
    else return COMMAND_UNKNOWN;
}

int Rsq(int indexBegin);
void Rsq(int indexBegin, int indexEnd, ofstream& output);
void Add(int index, int value);

int main() {
    string inputFileName = "input.txt";
	string outputFileName = "output.txt";
	ifstream input(inputFileName);
	ofstream output(outputFileName);

    if (!output)
	{
		cerr << "Uncorrect output file." << endl;
		exit(1);
	}

    input >> n;

    for (int i = 0; i < n; i++) {
        int number;
        input >> number;
        arr.push_back(number);
    }

	fenwickTree.assign(n, 0);
	for (int i = 0; i < arr.size(); i++)
		Add(i, arr[i]);

    Commands command;
    string inputCommand;
    int firstArg;
    int secondArg;
    
    string line;
    while (getline(input,line))
    {
       input >> inputCommand >> firstArg >> secondArg;
       switch (convert(inputCommand))
	    {
	    case COMMAND_ADD:
		    output << "add";
            output << " " << arr[firstArg] + secondArg << endl;
            Add(firstArg, secondArg);
		    break;
	    case COMMAND_RSQ:
		    output << "rsq";
            Rsq(firstArg, secondArg, output);
		    break;
	    default:
		    output << "Unknown command.";
		    break;
	    }
        
    }
}

int Rsq(int indexBegin) {
    int rsq = 0;
    for (indexBegin; indexBegin >= 0; indexBegin = (indexBegin & (indexBegin + 1)) - 1)
        rsq += fenwickTree[indexBegin];

    return rsq;
}

void Rsq(int indexBegin, int indexEnd, ofstream &output) {
    output << " " << indexBegin << " " << indexEnd << " " << Rsq(indexEnd) - Rsq(indexBegin - 1) << endl;
}

void Add(int index, int value) {
    for (index; index < n; index |= index + 1)
        fenwickTree[index] += value;
}