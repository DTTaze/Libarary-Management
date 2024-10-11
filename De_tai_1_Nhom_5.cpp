#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"
using namespace std;




void DocTuFile(DanhSachDauSach &danh_sach_dau_sach,DanhMucSach* &danh_muc_sach) {
    ifstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string ISBN, tensach, tacgia, theloai, vitri, hoten, ho, ten, ngaymuon, ngaytra, test, phai;
        int sotrang, namsx, trangthaithe, trangthaimuontra, trangthaidms, den;
        unsigned int mathe;

        // Tach thong tin tung dong
        size_t pos = 0; 
        // ISBN
        pos = line.find('|');
        ISBN = line.substr(0, pos); line.erase(0, pos + 1);
        cout << ISBN << "|";
        
        // Ten sach
        pos = line.find('|');
        tensach = line.substr(0, pos); line.erase(0, pos + 1);
        cout << tensach << "|";
        
        // So trang
        pos = line.find('|');
        sotrang = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        cout << sotrang << "|";

        // Tac gia
        pos = line.find('|');
        tacgia = line.substr(0, pos); line.erase(0, pos + 1);
        cout << tacgia << "|";

        // Nam san xuat
        pos = line.find('|');
        namsx = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        cout << namsx << "|";

        // The loai
        pos = line.find('|');
        theloai = line.substr(0, pos); line.erase(0, pos + 1);
        cout << theloai << "|";

        // Vi tri
        pos = line.find('|');
        vitri = line.substr(0, pos); line.erase(0, pos + 1);
        cout << vitri << "|";

        // Thieu 1 trong 5 thi bo qua dong
        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue; 
        }

        // Mathe
        pos = line.find('|');
        if (pos != string::npos) {    
            mathe = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
            cout << mathe << "|";
            
            // Ho và tên
            pos = line.find('|');
            hoten = line.substr(0, pos); line.erase(0, pos + 1);
            cout << hoten << "|";

            size_t spacepos = hoten.find(' ');
            if (spacepos != string::npos) {
                ho = hoten.substr(0, spacepos);
                ten = hoten.substr(spacepos + 1);
            } else {
                continue;
            }

            // Ngay muon sach
            pos = line.find('|');
            ngaymuon = line.substr(0, pos); line.erase(0, pos + 1);
            cout << ngaymuon << "|";

            // Ngay tra sach (neu co)
            pos = line.find('|');
            test = line.substr(0, pos); line.erase(0, pos + 1);
            ngaytra = test.empty() ? " " : test;
            cout << ngaytra << "|";

            // Trang thai muon tra
            pos = line.find('|');
            test = line.substr(0, pos); line.erase(0, pos + 1);
            trangthaimuontra = test.empty() ? -1 : stoi(test);
            cout << trangthaimuontra << "|";

            // Den
            pos = line.find('|');
            test = line.substr(0, pos); line.erase(0, pos + 1);
            den = test.empty() ? -1 : stoi(test);
            cout << den << "|";

            // Trang thai cua sach
            pos = line.find('|');
            test = line.substr(0, pos); line.erase(0, pos + 1);
            trangthaidms = test.empty() ? -1 : stoi(test);
            cout << trangthaidms << "|";

            // Phai
            pos = line.find('|');
            phai = (pos != string::npos) ? line.substr(0, pos) : " ";
            cout << phai << "|\n";
        }
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