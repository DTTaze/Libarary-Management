#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"
using namespace std;








int main() {
    enum dayofWeeks{Monday = 0, Tweday};
    

    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach = nullptr;

    DocTuFile(danh_sach_dau_sach,danh_muc_sach);
}