#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <iterator>
#include <string>

using namespace std;


    // return (i1-1)*numEmailUsers + (i2-1) +1;

string mapping(int i1, int numEmailUsers){
    return to_string(i1/numEmailUsers + 1) + " " + to_string(((i1-1) % numEmailUsers) + 1) + "\n";
    // return make_pair(i1/numEmailUsers + 1, ((i1-1) % numEmailUsers) + 1 );
}

int main(int argc, char* argv[]){

    ifstream sizeInfile;
    sizeInfile.open("setSizes.txt");
    if(!sizeInfile.is_open()){
        cout<< "Error opening file"<< endl;
    }

    int numPhoneUsers, numEmailUsers;
    sizeInfile>>numPhoneUsers>>numEmailUsers;

    ifstream infile;
    infile.open("test.satoutput");
    if(!infile.is_open()){
        cout<< "Error opening file"<< endl;
    }
    string sat, out = "";
    infile>>sat;
    int literal;

    ofstream outfile;
    outfile.open("test.mapping");

    if (sat=="UNSAT"){
        outfile<<"0\n";
        return 0;
    }
    for(int i=0; i<numEmailUsers*numPhoneUsers; i++){
        infile>>literal;
        if(literal > 0)
            outfile<<mapping(literal, numEmailUsers);
    }
    return 0;
}