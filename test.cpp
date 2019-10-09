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

int main(int argc, char* argv[]){
    int a[3] = {1,2,3};
    int b=3;
    if(a[b]<3)
        cout<<true<<endl;

    cout<<a[b]<<endl;

    return 0;
}