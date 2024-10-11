#ifndef DAU_SACH_H
#define DAU_SACH_H

#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include <conio.h>//_getch
#define MAXSACH 10000
using namespace std;

struct DanhMucSach {
    string masach;
    int trangthai;
    string vitri;
    DanhMucSach* next= nullptr;
    DanhMucSach(const string &ma_sach, int trang_thai, const string &vi_tri) 
        : masach(ma_sach), trangthai(trang_thai), vitri(vi_tri) {}
    DanhMucSach() : masach(""), trangthai(0), vitri("") {};
};

struct DauSach {
    string ISBN;
    string tensach;
    int sotrang;
    string tacgia;
    int namsx;
    string theloai;
    DanhMucSach* dms = nullptr;
    DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia,int nam_sx, const string& the_loai, DanhMucSach* ptr_dms)
        : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia),namsx(nam_sx), theloai(the_loai), dms(ptr_dms) {}
};

struct DanhSachDauSach{
    int demsach= 0;
    DauSach* node[MAXSACH];    
    int Masach[10][10][100]; 
    int SodaytrongKhuvuc[10] = {0};
    int Sosachtrongday[10][10] ={{0}};
};


void TaoMaSach(string& ma_sach ,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri);

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri);

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai, 
                DanhMucSach* &head_dms, int trang_thai,string &vi_tri);


int TimKiemNhiPhanTenSach(DanhSachDauSach &danh_sach_dau_sach,string key);

int TimKiemNhiPhanTheLoai(DanhSachDauSach &danh_sach_dau_sach,string key);
//Su dung tham chieu nen phai tao ban sao roi xoa ban sao
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach);


void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach);

bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach,string vi_tri);

void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach, 
                    DanhMucSach* &head_dms);

void DocTuFile(DanhSachDauSach &danh_sach_dau_sach,DanhMucSach* &danh_muc_sach);

#endif