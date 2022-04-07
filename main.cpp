#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

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
    for(i=regloc+1; i<memloc; i++){   //finds the regloc and goes through till memloc
        tempStr = str[i];   //storing in a temp string
        size_t locR = tempStr.find('R');    //finding the location of R in the string
        size_t locSpace = tempStr.size();   //finding the end of the string
        regMemNum = stoi(tempStr.substr(++locR,locSpace)); //separating the # from R# and converting to int
        tempstr1 = str[++i];    //loading the value in another temp string
        regMemVal = stoi(tempstr1,0);    //getting the register value and converting to int
        R[regMemNum] = regMemVal;    //storing the value to the register #
    }


    ///getting the memory location value
    for(i=memloc+1; i<codeloc; i++){
        tempStr = str[i];   //storing in temp string
        regMemNum = stoi(tempstr1);
        MemSloc.push_back(regMemNum);   //storing the memory location # in MemSloc vector
        tempstr1 = str[++i];
        regMemVal = stoi(tempstr1);
        Mem[regMemNum/4] = regMemVal;   //memory index is memory location/4; as int_32 requires 4 byte(8 bit)
    }

    for(vector<int>::iterator in = MemSloc.begin(); in != MemSloc.end(); ++in){
        int value = *in;
        cout << "Memory location " << value << " holds the value = " << Mem[value/4] << endl;
    }

    for(i=0;i<32;i++){
        cout << "R[" << i << "] = " << R[i] << endl;
    }
}
