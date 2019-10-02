#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	ofstream outfile;
	outfile.open("test.graphs");

	string line;
	while(getline(cin, line)){
		if(line == "")
			break;
		outfile<<line<<"\n";
	}

	outfile.close();

	return 0;
}