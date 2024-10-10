#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"
using namespace std;




void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms) {
    ifstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string ISBN, tensach, tacgia, theloai, vitri;
        int sotrang,namsx;

        // tach thong tin tung dong
        size_t pos = 0; 
        pos = line.find('|');
        ISBN = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        tensach = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        sotrang = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        pos = line.find('|');
        tacgia = line.substr(0, pos); line.erase(0, pos + 1);
        
        pos = line.find('|');
        namsx = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        pos = line.find('|');
        theloai = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        vitri = line.substr(0, pos); line.erase(0, pos + 1);

        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue; 
        }

        

        ThemDauSach(danh_sach_dau_sach, ISBN, tensach, sotrang, tacgia,namsx, theloai, head_dms, 0,vitri);
    }

    file.close();
}



int main() {
    enum dayofWeeks{Monday = 0, Tweday};
    

    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach = nullptr;

    DocTuFile(danh_sach_dau_sach,danh_muc_sach);

    InTheoTungTheLoai(danh_sach_dau_sach);
}