#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

struct MUONTRA {
    int masach;
    string ngaymuon[10];
    string ngaytra[10];
    int vitri;
    MUONTRA* next = nullptr;
};
