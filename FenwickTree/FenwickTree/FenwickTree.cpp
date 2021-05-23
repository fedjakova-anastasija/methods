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

int rsq(int indexBegin) {
    int result = 0;
    for (indexBegin; indexBegin >= 0; indexBegin = (indexBegin & (indexBegin + 1)) - 1) {
        result += fenwickTree[indexBegin];
    }

    return result;
}

void rsq(int indexBegin, int indexEnd) {
    cout << " " << indexBegin << " " << indexEnd << " " << rsq(indexEnd) - rsq(indexBegin - 1) << endl;
}

void add(int index, int value) {
    for (index; index < n; index |= index + 1)
        fenwickTree[index] += value;
}

Commands convert(const string& str)
{
    if(str == "add") return COMMAND_ADD;
    else if(str == "rsq") return COMMAND_RSQ;
    else return COMMAND_UNKNOWN;
}

int main() {
    string inputFileName = "input.txt";
	ifstream input(inputFileName);

    input >> n;

    for (int i = 0; i < n; i++) {
        int number;
        input >> number;
        arr.push_back(number);
    }

	fenwickTree.assign(n, 0);
	for (int i = 0; i < arr.size(); i++)
		add(i, arr[i]);

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
		    std::cout << "add";
            cout << " " << arr[firstArg] + secondArg << endl;
            add(firstArg, secondArg);
		    break;
	    case COMMAND_RSQ:
		    std::cout << "rsq";
            rsq(firstArg, secondArg);
		    break;
	    default:
		    std::cout << "Unknown command.";
		    break;
	    }
        
    }
}