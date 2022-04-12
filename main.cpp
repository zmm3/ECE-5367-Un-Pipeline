#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

//Op code Macro
// R-type instruction
#define RTypeOpCode 0   //R-type inst Opp code
#define addFunCode 32   //Add function code
#define subFunCode 34   //Sub function code
#define sltFunCode 42   //Set less than function code
// I-type instruction
#define ldrWOpCode 35   //Load word Opp Code
#define strWOpCode 43   //Store word Opp Code
#define addImdOpCode 8  //Add immediate Opp code
#define beOpCode 4      //Branch in equal Opp Code
#define bneOpCode 5     //Branch not equal Opp Code

///Global Variable
int R[32];
int Mem[249];
vector <int> MemSloc;

/// Variable explanation
// inFile -> input file pointer object
// array R[32] -> stores the value of each register from 0 to 31
// array Mem[249] -> stores the memory value for each memory location
// vector MemSloc -> stores the memory location index

/// function decleration
void RegMemCodeReading(vector<string> s);   //INPUT: gets sting vector as argument
                                            //OUTPUT: value inserted to the corresponding memory location index in
                                                    //R[#], Mem[#}, and MemSloc<intVec>


/// delete only for testing function

///
int main()
{
    ifstream inFile("input.txt");   //

    if(inFile.fail()){  //file open test
                       //if the file fail to open then exit the program with the message
        cout << "file failed to open, EXITING program" << endl;
        exit(1);
    }

    //flashing out the register values and memory location value
    for(int i =0; i < 32; i++){
        R[i] = 0;
    }

    for(int k=0; k<249; k++){
        Mem[k] = 0;
    }

    //Reading from the file
    string tempStr;
    vector<string> str;
    int numberofvec = 0;
    while(inFile >> tempStr){
        str.push_back(tempStr);
        numberofvec++;
    }

    ///printing out the values stored in the vector
    for(vector<string>::iterator it = str.begin(); it != str.end(); ++it){
        cout << *it << endl;
    }

    RegMemCodeReading(str);

    inFile.close();

    return 0;
}

void RegMemCodeReading(vector<string> str){
    string tempStr;    //temp place input string holder
    string tempstr1;
    //finding the indexes of the following location
    int regloc; //index of location "REGISTERS" in vector
    int memloc; //index of location "MEMORY" in vector
    int codeloc;    //index of location "CODE" in vector
    int i;
    for(i=0;i<str.size();i++){
        if(str[i]=="REGISTERS"){
            regloc = i;
        }
        else if(str[i]=="MEMORY"){
            memloc = i;
        }
        else if(str[i]=="CODE"){
            codeloc = i;
        }
    }

    int regMemNum; //stores the register memory loc number

    int regMemVal; //stores the register memory value

    ///getting the register value
    ///format style
    ///R#   #!#
    ///str[i] = R#  1st vector
    ///str[++i] = #!#   2nd vector
    for(i=regloc+1; i<memloc; i++){   //finds the regloc and goes through till memloc
        tempStr = str[i];   //storing in a temp string
                            //first vector stores the R#
        size_t locR = tempStr.find('R');    //finding the location of R in the string
        size_t locSpace = tempStr.size();   //finding the end of the string
        regMemNum = stoi(tempStr.substr(++locR,locSpace)); //separating the # from R# and converting to int
        tempstr1 = str[++i];    //loading the value in another temp string4
                                //2nd vector stores the # to be stored in the register
        regMemVal = stoi(tempstr1,0);    //getting the register value and converting to int
        R[regMemNum] = regMemVal;    //storing the value to the register #
    }
    ///Printing out the register value
    for(i=0;i<32;i++){
        cout << "R[" << i << "] = " << R[i] << endl;
    }


    ///getting the memory location value
    for(i=memloc+1; i<codeloc; i++){
        tempStr = str[i];   //storing in temp string
        regMemNum = stoi(tempStr);
        MemSloc.push_back(regMemNum);   //storing the memory location # in MemSloc vector
        tempstr1 = str[++i];
        regMemVal = stoi(tempstr1);
        Mem[regMemNum/4] = regMemVal;   //memory index is memory location/4; as int_32 requires 4 byte(8 bit)
    }
    ///printing out the memory value
    for(vector<int>::iterator in = MemSloc.begin(); in != MemSloc.end(); ++in){
        int value = *in;
        cout << "Memory location " << value << " holds the value = " << Mem[value/4] << endl;
    }
    string oppStr;
    string funStr;
    ///reading in code
<<<<<<< Updated upstream
=======
    int instrNum = 1; // Instruction number increments by 1 for each operation
    int cycleNum = 1; // Will increment by one for each cycle e.g. C#1 I1-IF
    int opCdInt;
    int funcodeint;
>>>>>>> Stashed changes
    for(i=codeloc+1; i<str.size(); ++i){
        tempStr = str[i];
        cout << i << endl;
        //cout << tempStr << endl;
        oppStr = tempStr.substr(0,6);   //reading the  1st 6 bit oppcode
        opCdInt = stoi(oppStr,nullptr,2);
        //cout << "op code: " << oppStr << ":" <<opCdInt << endl;
        funStr = tempStr.substr(25,31);
        funcodeint = stoi(funStr,nullptr,2);
        string retStr;
        switch(opCdInt){
            case RTypeOpCode:
                //cout << "R-type instruction. " << endl;
                switch(funcodeint){
                    case addFunCode:
                        cout << "R-Type Add function" << endl;
                        retStr = OpCodeAdd(tempStr,&i, &cycleNum, &instrNum);
                        cout << retStr << endl;
                        break;
                    case subFunCode:
                        cout << "R-Type Sub function" << endl;
                        break;
                    case sltFunCode:
                        cout << "R-Type Shift Logic Left function" << endl;
                        break;
                }
                break;
            case ldrWOpCode:
                cout << "Load word instruction " << endl;
                break;
            case strWOpCode:
                cout << "Store word instruction " << endl;
                break;
            case addImdOpCode:
                cout << "Add immediate instruction " << endl;
                break;
            case beOpCode:
                cout << "Branch if equal instruction " << endl;
                break;
            case bneOpCode:
                cout << "Branch if not equal instruction " << endl;
                break;
        }

    }
}
<<<<<<< Updated upstream
=======

string OpCodeAdd(string codeLine, int& PCaddr, int& cycleNum, int&instrNum)
{
    int rs = stoi(codeLine.substr(6, 5), 0, 2);
    int rt = stoi(codeLine.substr(11, 5), 0, 2);
    int rd = stoi(codeLine.substr(16, 5), 0, 2);
    ostringstream  outSS;

    R[rd] = R[rs] + R[rt];

    outSS << "C#" << cycleNum++ << " " << "I" << instrNum << "-IF" << endl;
    outSS << "C#" << cycleNum++ << " " << "I" << instrNum << "-ID" << endl;
    outSS << "C#" << cycleNum++ << " " << "I" << instrNum << "-EX" << endl;
    outSS << "C#" << cycleNum++ << " " << "I" << instrNum << "-WB" << endl;
    *instrNum++;

    return outSS.str();
}
>>>>>>> Stashed changes
