#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <utility>
#include <iterator>
#include <string>

using namespace std;

int mapping(int i1, int i2, int numPhoneUsers){
    return (i1-1)*numPhoneUsers + i2;
}

int main(int argc, char* argv[]){
    clock_t start, mainStart, end;
    double msecs;

    start = clock();
    mainStart = clock();

    int maxPhoneUsers = -1;
    int maxEmailUsers = -1;
    int numPhoneEdges = 0;
    int numEmailEdges = 0;

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
        // Gphone.insert(make_pair(make_pair(edgeFrom,edgeTo), true));
        numPhoneEdges++;
        maxPhoneUsers = max(maxPhoneUsers, max(edgeFrom, edgeTo));

    }
    while(!infile.eof()){
        infile>>edgeFrom>>edgeTo;
        // Gemail.insert(make_pair(make_pair(edgeFrom,edgeTo), true));
        numEmailEdges++;
        // cout<<edgeFrom<<" "<<edgeTo<<endl;
        maxEmailUsers = max(maxEmailUsers, max(edgeFrom, edgeTo));
    }
    numEmailEdges--;
    infile.close();













    pair<int,int> emailEdges[numEmailEdges];
    pair<int,int> phoneEdges[numPhoneEdges];
    int emailEdgeIndex=0, phoneEdgeIndex=0;

    int numPhoneUsers = maxPhoneUsers;
    int numEmailUsers = maxEmailUsers;
    bool GphoneArr[numPhoneUsers+1][numPhoneUsers+1];
    bool GemailArr[numEmailUsers+1][numEmailUsers+1];
    for (int i=0; i<=numPhoneUsers; i++){
        for (int j=0; j<=numPhoneUsers; j++)
            GphoneArr[i][j]=false;
    }

    for (int i=0; i<=numEmailUsers; i++){
        for (int j=0; j<=numEmailUsers; j++)
            GemailArr[i][j]=false;
    }
    end = clock();
    msecs = ( (double) (end - start)) * 1000.0 / CLOCKS_PER_SEC;
    start = clock();
    cout<<"time before reading file again: "<<msecs<<endl;
    
    infile.open("test.graphs");
    if(!infile.is_open()){
        cout<< "Error opening file"<< endl;
    }

    while(!infile.eof()){
        infile>>edgeFrom>>edgeTo;
        if (edgeFrom==0 && edgeTo==0)
            break;
        GphoneArr[edgeFrom][edgeTo] = true;
        phoneEdges[phoneEdgeIndex++] = make_pair(edgeFrom, edgeTo);
    }
    while(!infile.eof()){
        infile>>edgeFrom>>edgeTo;
        GemailArr[edgeFrom][edgeTo] = true;
        emailEdges[emailEdgeIndex++] = make_pair(edgeFrom, edgeTo);

    }
    infile.close();

    end = clock(); msecs = ( (double) (end - start)) * 1000.0 / CLOCKS_PER_SEC; start = clock(); cout<<"🕑 Read file twice and construct bool arrays: "<<msecs<<endl;


    ofstream tempOutfile;
    tempOutfile.open("setSizes.txt");
    tempOutfile<<numPhoneUsers<<" "<<numEmailUsers<<"\n";
    tempOutfile.close();

    cout<<"# of phone users: "<<numPhoneUsers<<endl<<"# of email users: "<<numEmailUsers<<endl<<"# of phone edges: "<<numPhoneEdges<<endl<<"# of email edges: "<<numEmailEdges<<endl<<endl;

    end = clock(); msecs = ( (double) (end - start)) * 1000.0 / CLOCKS_PER_SEC; start = clock(); cout<<"🕑 n2m2 loop: "<<msecs<<endl;

    string out = "";

    int numCalculatedMainClauses = (numEmailEdges*( numPhoneUsers*(numPhoneUsers -1) - numPhoneEdges) ) + ( numPhoneEdges*(numEmailUsers*(numEmailUsers -1) - numEmailEdges));
    int numFinalClauses = numCalculatedMainClauses + numEmailUsers + numEmailUsers*(numPhoneUsers - 1)*numPhoneUsers + numPhoneUsers*numEmailUsers*(numEmailUsers - 1);

    cout<<"CALC_MAIN_CLAUSES: "<<numCalculatedMainClauses<<endl;
    cout<<"NUM_CLAUSES: "<<numFinalClauses<<endl;
    
    ofstream outfile;
    outfile.open("test.satinput");
    outfile<<"p cnf "<<numEmailUsers*numPhoneUsers<<" "<<numFinalClauses<<"\n";


    // for(int i=1; i <= numEmailUsers; i++){
    //     for(int j=1; j <= numEmailUsers; j++){
    //         if(i==j)
    //             continue;
    //         for(int p=1; p <= numPhoneUsers; p++){
    //             for(int q=1; q <= numPhoneUsers; q++){
    //                 if (p==q)
    //                     continue;
    //                 if(GemailArr[i][j]){
    //                     if(!GphoneArr[p][q]){
    //                         outfile<< -1 * mapping(i,p,numPhoneUsers)<<" "<< -1 * mapping(j,q,numPhoneUsers)<<" "<<0<<"\n";
    //                         // out += "-"+to_string(mapping(i,p,numPhoneUsers))+" -"+to_string(mapping(j,q,numPhoneUsers))+" 0\n";
    //                     }
    //                 }
    //                 else{
    //                     if(GphoneArr[p][q]){
    //                         outfile<< -1 * mapping(i,p,numPhoneUsers)<<" "<< -1 * mapping(j,q,numPhoneUsers)<<" "<<0<<"\n";
    //                         // out += "-"+to_string(mapping(i,p,numPhoneUsers))+" -"+to_string(mapping(j,q,numPhoneUsers))+" 0\n";
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    int a,b;
    for (int i=0; i<numEmailEdges; i++){
        a=emailEdges[i].first; b=emailEdges[i].second;
        for(int p=1; p <= numPhoneUsers; p++){
            for(int q=1; q <= numPhoneUsers; q++){
                if (p==q)
                    continue;
                if(!GphoneArr[p][q]){
                    outfile<< -1 * mapping(a,p,numPhoneUsers)<<" "<< -1 * mapping(b,q,numPhoneUsers)<<" "<<0<<"\n";
                    // out += "-"+to_string(mapping(i,p,numPhoneUsers))+" -"+to_string(mapping(j,q,numPhoneUsers))+" 0\n";
                }
            }
        }

    }
    for (int i=0; i<numPhoneEdges; i++){
        a=phoneEdges[i].first; b=phoneEdges[i].second;
        for(int p=1; p <= numEmailUsers; p++){
            for(int q=1; q <= numEmailUsers; q++){
                if (p==q)
                    continue;
                if(!GemailArr[p][q]){
                    outfile<< -1 * mapping(p,a,numPhoneUsers)<<" "<< -1 * mapping(q,b,numPhoneUsers)<<" "<<0<<"\n";
                    // out += "-"+to_string(mapping(i,p,numPhoneUsers))+" -"+to_string(mapping(j,q,numPhoneUsers))+" 0\n";
                }
            }
        }
    }
    
    end = clock(); msecs = ( (double) (end - start)) * 1000.0 / CLOCKS_PER_SEC; start = clock(); cout<<"🕑 Calculating main clauses: "<<msecs<<endl;

    for(int i=1; i <= numEmailUsers; i++){
        for(int j=1; j <= numPhoneUsers; j++){
            // out += to_string(mapping(i,j,numPhoneUsers)) + " ";
            outfile<<mapping(i,j,numPhoneUsers)<<" ";

        }
        // out += "0\n";
        outfile<<"0\n";
    }

    end = clock(); msecs = ( (double) (end - start)) * 1000.0 / CLOCKS_PER_SEC; start = clock(); cout<<"🕑 All ORs loop: "<<msecs<<endl;

    for(int i=1; i <= numEmailUsers; i++){
        for(int p=1; p <= numPhoneUsers; p++){
            for (int q=1; q <= numPhoneUsers; q++){
                if(p!=q){
                    // out += "-" + to_string(mapping(i,p,numPhoneUsers)) + " -" + to_string(mapping(i,q,numPhoneUsers)) + " 0\n";
                    outfile<< -1 * mapping(i,p,numPhoneUsers)<<" "<< -1 * mapping(i,q,numPhoneUsers)<<" 0\n";
                }
            }
        }
    }

    end = clock(); msecs = ( (double) (end - start)) * 1000.0 / CLOCKS_PER_SEC; start = clock(); cout<<"🕑 nm2 loop: "<<msecs<<endl;

    for(int i=1; i <= numEmailUsers; i++){
        for(int j=1; j <= numEmailUsers; j++){
            for (int p=1; p <= numPhoneUsers; p++){
                if(i!=j){
                    // out += "-" + to_string(mapping(i,p,numPhoneUsers)) + " -" + to_string(mapping(j,p,numPhoneUsers)) + " 0\n";
                    outfile<< -1 * mapping(i,p,numPhoneUsers)<<" "<< -1 * mapping(j,p,numPhoneUsers)<<" 0\n";
                }
            }
        }
    }
    
    // outfile<<out;

    outfile.close();
    end = clock();
    msecs = ( (double) (end - mainStart)) * 1000.0 / CLOCKS_PER_SEC;
    start = clock();
    cout<<"🕑 Generate SAT input (n2m): "<<msecs<<endl;
    return 0;
}
