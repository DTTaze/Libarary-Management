#ifndef MUON_TRA_H
#define MUON_TRA_H

#include <iostream>
#include <ctime>
#include <fstream>
#include "ngay.cpp"
#include "The_doc_gia.h"
using namespace std;

/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, 
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách 
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

struct DanhSachTheDocGia { // danh sách các độc giả
    The_Doc_Gia docgia;
    DanhSachTheDocGia *next = nullptr;
};

int TrangThai(Date ngay_muon, Date ngay_tra) ;

struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
    string masach;
    Date NgayMuon;
    Date NgayTra;
    int trangthai;
    MUONTRA(string ma, const Date &ngayMuon, const Date &ngayTra) : masach(ma), NgayMuon(ngayMuon), NgayTra(ngayTra) 
    { trangthai = TrangThai(NgayMuon, NgayTra);}

    bool operator==(const MUONTRA &other) const {
        return masach == other.masach &&
               NgayMuon == other.NgayMuon &&
               NgayTra == other.NgayTra;
    }
};

struct DanhSachMUONTRA { // danh sach cac quyen sach da hoac dang muon
    MUONTRA data;
    DanhSachMUONTRA *next = nullptr;
    DanhSachMUONTRA(const MUONTRA &muontra) : data(muontra), next(nullptr) {}
};

struct DocGiaMuonSach { 
    The_Doc_Gia docgia;
    DanhSachMUONTRA *danhsachmuontra;

    DocGiaMuonSach(const The_Doc_Gia &thedocgia) : docgia(thedocgia), danhsachmuontra(nullptr) {}
};

int DemSoSachDangMuon(DanhSachMUONTRA *demsach) ;

void ThemSach (DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra) ;

bool Empty(DanhSachMUONTRA * First);

int XoaSachDauTien (DanhSachMUONTRA *&First);


int XoaSachSauSachP(DanhSachMUONTRA * p);

int XoaSachTheoThongTin(DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra) ;

enum DenSach {daden, chuaden};

void InManHinhDSSach(DocGiaMuonSach * head) ;

// void LuuNgayMuon(const string& fileName, const Date& ngay_muon) {
//     ofstream file(fileName);
//     if (file.is_open()) {
//         file << ngay_muon.day << "/" << ngay_muon.month << "/" << ngay_muon.year;
//         file.close();
//         cout << "Ngay muon sach da duoc luu: " << ngay_muon.day << "/" << ngay_muon.month << "/" << ngay_muon.year << endl;
//     } else {
//         cout << "Khong the mo file de ghi." << endl;
//     }
// }

void ThemSachVaoLSMS(DanhSachMUONTRA * &sach, string ma, const Date &ngayMuon, const Date &ngayTra) ;

void MuonSach (DocGiaMuonSach *doc_gia) ;


void TraSach (DocGiaMuonSach doc_gia, string ma_sach) ;

void DanhSachSachDocGiaMuon(DocGiaMuonSach doc_gia) ;

// void DocFile(const string &tenFile, DocGiaMuonSach *&doc_gia) {
//     ifstream file("Danh_sach_dau_sach.txt");
//     if (!file.is_open()) {
//         cout << "Không thể mở file." << endl;
//         return;
//     }

//     string line;
//     while (getline(file, line)) {
//         size_t pos = 0;

//         auto nextToken = [&](char delimiter) {
//             size_t newPos = line.find(delimiter, pos);
//             string token = line.substr(pos, newPos - pos);
//             pos = newPos + 1;
//             return token;
//         };

//         string isbn = nextToken('|');
//         string tensach = nextToken('|');
//         int sotrang = stoi(nextToken('|'));
//         string tacgia = nextToken('|');
//         int namsx = stoi(nextToken('|'));
//         string theloai = nextToken('|');
//         nextToken('|'); // Skip one field
//         string masach = nextToken('|');
//         string nguoiMuon = nextToken('|');

//         Date ngaymuon;
//         string ngayMuonStr = nextToken('|');
//         sscanf(ngayMuonStr.c_str(), "%d/%d/%d", &ngaymuon.day, &ngaymuon.month, &ngaymuon.year);

//         Date ngaytra;
//         string ngayTraStr = nextToken('|');
//         if (!ngayTraStr.empty()) {
//             sscanf(ngayTraStr.c_str(), "%d/%d/%d", &ngaytra.day, &ngaytra.month, &ngaytra.year);
//         } else {
//             ngaytra = {0, 0, 0}; // If no return date is provided
//         }

//         int trangthai = stoi(nextToken('|'));

//         // Add the book to the borrow list
//         ThemSach(doc_gia->danhsachmuontra, masach, tensach, ngaymuon, ngaytra);
//     }

//     file.close();
// }

// int main() {
//     DocGiaMuonSach *doc_gia = new DocGiaMuonSach(The_Doc_Gia()); // Assume constructor exists
//     DocFile("file.txt", doc_gia);

//     // Further processing with doc_gia...

//     delete doc_gia; // Clean up
//     return 0;
// }
#endif