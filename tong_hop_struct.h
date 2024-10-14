// #ifndef TONG_HOP
// #define TONG_HOP
// #include <iostream> 
// #include <cstring>
// #include <string>
// #include <fstream>
// #include <conio.h>//_getch
// #include <ctime>
// #include "ngay.h"
// #define MAXRANDOM 10000 // Random tối đa 10000 số
// #define MAXRANGE 5000 // Giá trị đi từ 1->4999, bỏ qua index 0
// #define MAXSACH 10000
// using namespace std;
// struct DanhMucSach {
//     string masach;
//     int trangthai;
//     string vitri;
//     DanhMucSach* next= nullptr;
//     DanhMucSach(const string &ma_sach, int trang_thai, const string &vi_tri) 
//         : masach(ma_sach), trangthai(trang_thai), vitri(vi_tri) {}
//     DanhMucSach() : masach(""), trangthai(0), vitri("") {};
// };

// struct DauSach {
//     string ISBN;
//     string tensach;
//     int sotrang;
//     string tacgia;
//     int namsx;
//     string theloai;
//     DanhMucSach* dms = nullptr;
//     DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia,int nam_sx, const string& the_loai, DanhMucSach* ptr_dms)
//         : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia),namsx(nam_sx), theloai(the_loai), dms(ptr_dms) {}
// };

// struct DanhSachDauSach{
//     int demsach= 0;
//     DauSach* node[MAXSACH];    
//     int demsachvitri[10]={0};
// };
// //---------------------------------------------------------------------------------------------------------

// int TrangThai(Date ngay_muon, Date ngay_tra) ;

// struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
//     string masach;
//     Date NgayMuon;
//     Date NgayTra;
//     int trangthai;
//     MUONTRA(string ma, const Date &ngayMuon, const Date &ngayTra) : masach(ma), NgayMuon(ngayMuon), NgayTra(ngayTra) 
//     { trangthai = TrangThai(NgayMuon, NgayTra);}

//     bool operator==(const MUONTRA &other) const {
//         return masach == other.masach &&
//                NgayMuon == other.NgayMuon &&
//                NgayTra == other.NgayTra;
//     }
// };

// struct DanhSachMUONTRA { // danh sach cac quyen sach da hoac dang muon
//     MUONTRA data;
//     DanhSachMUONTRA *next = nullptr;
//     DanhSachMUONTRA(const MUONTRA &muontra) : data(muontra), next(nullptr) {}
// };

// //----------------------------------------------------------------------------------------------------

// enum Phai{Nam = 1, Nu = 0};
// enum TrangThaiCuaThe{Dang_Hoat_Dong = 1, Khoa = 0};

// int DayNgauNhien[MAXRANDOM + 1];
// int Random_Ptr_Trai = 1;
// int Random_Ptr_Phai = 5001;
// int Random_PTr = 1;
// bool Lay_Tu_Trai = true;
// Danh_Sach_The_Doc_Gia* root = nullptr;

// struct The_Doc_Gia {
//     unsigned int MATHE;
//     string Ho;
//     string Ten;
//     TrangThaiCuaThe TrangThai;
//     Phai phai;
//     DanhSachMUONTRA* head_lsms = nullptr;// những quyển sách độc giả mượn 
// };

// struct Danh_Sach_The_Doc_Gia {
//     The_Doc_Gia thong_tin;
//     Danh_Sach_The_Doc_Gia* ptr_left = nullptr;
//     Danh_Sach_The_Doc_Gia* ptr_right = nullptr;
//     Danh_Sach_The_Doc_Gia(){};
//     Danh_Sach_The_Doc_Gia(const The_Doc_Gia& thong_tin_the_doc_gia) {
//         thong_tin.MATHE = thong_tin_the_doc_gia.MATHE;
//         thong_tin.Ho = thong_tin_the_doc_gia.Ho;
//         thong_tin.Ten = thong_tin_the_doc_gia.Ten;
//         thong_tin.TrangThai = thong_tin_the_doc_gia.TrangThai;
//         thong_tin.phai = thong_tin_the_doc_gia.phai;
//     };
// };

// #endif