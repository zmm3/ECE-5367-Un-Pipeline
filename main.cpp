#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;
///
/// inFile -> input file pointer object
/// array R[32] -> stores the value of each register from 0 to 31
/// array Mem[249] -> stores the memory value for each memory location


///Global Variable
int R[32];
int Mem[249];
/// delete only for testing function
void printl(const string str)
{
    int regNum;
    int regVal;
    int c = 0;
    if((!str.find("REGISTERS"))||(!str.find("MEMORY"))||(!str.find("CODE"))){

    }
    else{
        cout << str << endl;
        if(str.at(0)=='R'){
            size_t locR = str.find('R');
            size_t locSpace = str.find(' ');
            regNum = stoi(str.substr(++locR,--locSpace));
            cout << regNum << endl;
            size_t locNxtL = str.find('\n');
            locSpace += 1;
            regVal = stoi(str.substr(++locSpace,--locNxtL));
            cout << regVal << endl;
            R[regNum] = regVal;
        }
    }
}

///
int main()
{
    ifstream inFile("input.txt");   //

    if(inFile.fail())  //file open test
                       //if the file fail to open then exit the program with the message
    {
        cout << "file failed to open, EXITING program" << endl;
        exit(1);
    }

    //flashing out the register values and memory location value
    for(int i =0; i < 32; i++)
    {
        R[i] = 0;
    }

    for(int k=0; k<249; k++)
    {
        Mem[k] = 0;
    }

    //Reading from the file
    string tempStr;    //temp place input string holder
    vector <string> str;
    char val = 0;
    char comp;
    int j = 0;
    while(inFile >> tempStr)
    {
        str.push_back(tempStr);
        j++;
    }

    for(int i =0; i < j; i++){
        cout << str[i] << endl;
    }



    inFile.close();

    return 0;
}
