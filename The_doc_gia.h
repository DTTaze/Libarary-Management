#ifndef THE_DOC_GIA_H
#define THE_DOC_GIA_H
#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "Muon_tra.h"
#define MAXRANDOM 10000 // Random tối đa 10000 số
#define MAXRANGE 5000 // Giá trị đi từ 1->4999, bỏ qua index 0

using namespace std;

enum Phai{Nam = 1, Nu = 0};
enum TrangThaiCuaThe{Dang_Hoat_Dong = 1, Khoa = 0};

int DayNgauNhien[MAXRANDOM + 1];
int Random_Ptr_Trai = 1;
int Random_Ptr_Phai = 5001;
int Random_PTr = 1;
bool Lay_Tu_Trai = true;
Danh_Sach_The_Doc_Gia* root = nullptr;

struct The_Doc_Gia {
    unsigned int MATHE;
    string Ho;
    string Ten;
    TrangThaiCuaThe TrangThai;
    Phai phai;
    DanhSachMUONTRA* head_lsms = nullptr;// những quyển sách độc giả mượn 
};

struct Danh_Sach_The_Doc_Gia {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia* ptr_right = nullptr;
    Danh_Sach_The_Doc_Gia(){};
    Danh_Sach_The_Doc_Gia(const The_Doc_Gia& thong_tin_the_doc_gia) {
        thong_tin.MATHE = thong_tin_the_doc_gia.MATHE;
        thong_tin.Ho = thong_tin_the_doc_gia.Ho;
        thong_tin.Ten = thong_tin_the_doc_gia.Ten;
        thong_tin.TrangThai = thong_tin_the_doc_gia.TrangThai;
        thong_tin.phai = thong_tin_the_doc_gia.phai;
    };
};

void Them_Doc_Gia(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) ;

void Them_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia );

Danh_Sach_The_Doc_Gia* rp;

void Xoa_Truong_Hop_Co_Hai_Cay_Con(Danh_Sach_The_Doc_Gia* r );

void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia* &r, const int& ma_the_doc_gia);

Danh_Sach_The_Doc_Gia* Tim_Kiem(Danh_Sach_The_Doc_Gia* root, const int& mathe ) ;

void Inorder(Danh_Sach_The_Doc_Gia* root );

void Tao_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* root_maso, Danh_Sach_The_Doc_Gia* &root_ten) ;

void Xoa_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* &root_ten) ;

void swap( int& a, int& b );

void LayDayNgauNhien ();

int LayMaTheNgauNhien() ;

void TraVeSoNgauNhien(int So_Tra_Ve);

void Doc_Thong_Tin_Tu_File(const string& file_name, Danh_Sach_The_Doc_Gia* &root_ma_so);

#endif