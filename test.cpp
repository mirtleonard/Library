#include<fstream>
#include<iostream>
using namespace std;

int main(int argc, char ** argv) {
   ifstream fin(argv[1]); 
   string test;
   fin >> test;
   cout << test;
}
