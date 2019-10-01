#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <iterator>
#include <string>

using namespace std;

int mapping(int i1, int i2, int numPhoneUsers){
    return (i1-1)*numPhoneUsers + i2;
}

int main(int argc, char* argv[]){
    map< pair<int, int>, bool >Gphone;
    map< pair<int, int>, bool >Gemail;

    set<int, greater<int> >phoneUsers;
    set<int, greater<int> >emailUsers;


    int edgeFrom, edgeTo;

    ifstream infile;
    infile.open("test.graphs");
    if(!infile.is_open()){
        cout<< "Error opening file"<< endl;
    }

    while(!infile.eof()){
        infile>>edgeFrom>>edgeTo;
        if (edgeFrom==0 && edgeTo==0)
            break;
        Gphone.insert(make_pair(make_pair(edgeFrom,edgeTo), true));
        phoneUsers.insert(edgeFrom);
        phoneUsers.insert(edgeTo);

    }
    while(!infile.eof()){
        infile>>edgeFrom>>edgeTo;
        Gemail.insert(make_pair(make_pair(edgeFrom,edgeTo), true));
        emailUsers.insert(edgeFrom);
        emailUsers.insert(edgeTo);
    }
    infile.close();

    int numPhoneUsers = phoneUsers.size();
    int numEmailUsers = emailUsers.size();

    ofstream tempOutfile;
    tempOutfile.open("setSizes.txt");
    tempOutfile<<numPhoneUsers<<" "<<numEmailUsers<<"\n";
    tempOutfile.close();

    cout<<"# of phone users: "<<numPhoneUsers<<endl<<"# of email users: "<<numEmailUsers<<endl;

    string out = "";
    int numClauses = 0;
    for(int i=1; i <= numEmailUsers; i++){
        for(int j=1; j <= numEmailUsers; j++){
            if(i==j)
                continue;
            for(int p=1; p <= numPhoneUsers; p++){
                for(int q=1; q <= numPhoneUsers; q++){
                    if(Gemail.find(make_pair(i,j)) != Gemail.end()){
                        if(Gphone.find(make_pair(p,q)) == Gphone.end() && p!=q){
                            out += "-" + to_string(mapping(i,p,numPhoneUsers)) + " -" + to_string(mapping(j,q,numPhoneUsers)) + " 0\n";
                            numClauses++;
                        }
                    }
                    else{
                        if(Gphone.find(make_pair(p,q)) != Gphone.end()){
                            out += "-" + to_string(mapping(i,p,numPhoneUsers)) + " -" + to_string(mapping(j,q,numPhoneUsers)) + " 0\n";
                            numClauses++;
                        }
                    }
                }
            }
        }
    }
    for(int i=1; i <= numEmailUsers; i++){
        for(int j=1; j <= numPhoneUsers; j++){
            out += to_string(mapping(i,j,numPhoneUsers)) + " ";
        }
        out += "0\n";
        numClauses++;
    }
    for(int i=1; i <= numEmailUsers; i++){
        for(int p=1; p <= numPhoneUsers; p++){
            for (int q=1; q <= numPhoneUsers; q++){
                if(p!=q){
                    out += "-" + to_string(mapping(i,p,numPhoneUsers)) + " -" + to_string(mapping(i,q,numPhoneUsers)) + " 0\n";
                    numClauses++;
                }
            }
        }
    }
    for(int i=1; i <= numEmailUsers; i++){
        for(int j=1; j <= numEmailUsers; j++){
            for (int p=1; p <= numPhoneUsers; p++){
                if(i!=j){
                    out += "-" + to_string(mapping(i,p,numPhoneUsers)) + " -" + to_string(mapping(j,p,numPhoneUsers)) + " 0\n";
                    numClauses++;
                }
            }
        }
    }

    ofstream outfile;
    outfile.open("test.satinput");

    outfile<<"p cnf "<<numEmailUsers*numPhoneUsers<<" "<<numClauses<<"\n";
    outfile<<out;



    outfile.close();

    return 0;
}
