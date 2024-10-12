#ifndef THE_DOC_GIA_H
#define THE_DOC_GIA_H
#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "Muon_tra.h"
#define MAXRANDOM 10000
using namespace std;

enum Phai{Nam = 1, Nu = 0};
enum TrangThaiCuaThe{Dang_Hoat_Dong = 1, Khoa = 0};
int DayNgauNhien[MAXRANDOM];
int Random_Ptr = 0;

struct The_Doc_Gia {
    unsigned int MATHE;
    string Ho;
    string Ten;
    TrangThaiCuaThe TrangThai;
    Phai phai;
    DanhSachMUONTRA* head_lsms = nullptr;
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

void Them_Doc_Gia(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia(thong_tin_the_doc_gia);
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.MATHE == thong_tin_the_doc_gia.MATHE ) {
            cout << "Ma the doc gia da ton tai." << endl;   
            return;
        }
        if ( root->thong_tin.MATHE < thong_tin_the_doc_gia.MATHE ) {
            Them_Doc_Gia(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}

void Them_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia(thong_tin_the_doc_gia);
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.Ten == thong_tin_the_doc_gia.Ten ) {
            cout << "Ten doc gia da ton tai." << endl;   
            return;
        }
        if ( root->thong_tin.Ten < thong_tin_the_doc_gia.Ten ) {
            Them_Doc_Gia(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}

Danh_Sach_The_Doc_Gia* rp;

void Xoa_Truong_Hop_Co_Hai_Cay_Con(Danh_Sach_The_Doc_Gia* r ) {
    if ( r->ptr_left != nullptr ) {
        Xoa_Truong_Hop_Co_Hai_Cay_Con(r->ptr_left);
    } else {
        rp->thong_tin = r->thong_tin;
        Danh_Sach_The_Doc_Gia* temp = r;
        r = r->ptr_right;
        delete temp;
    }
}

void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia* &r, const int& ma_the_doc_gia) {
    if ( r == nullptr ) {
        cout << "Khong Tim Thay " << ma_the_doc_gia << endl;
    }
    else {  
        if ( r->thong_tin.MATHE < ma_the_doc_gia ) {
            Xoa_Doc_Gia(r->ptr_right, ma_the_doc_gia );
        } else if ( r->thong_tin.MATHE > ma_the_doc_gia ) {
            Xoa_Doc_Gia(r->ptr_left, ma_the_doc_gia );
        } else {
            rp = r;
            if ( rp->ptr_right == nullptr ) {
                r = rp->ptr_left;
            } else if ( rp->ptr_left == nullptr ) {
                r = rp->ptr_right;
            } else {
                Xoa_Truong_Hop_Co_Hai_Cay_Con(rp->ptr_right);
            }
            delete rp;
        }
    }
}

Danh_Sach_The_Doc_Gia* Tim_Kiem(Danh_Sach_The_Doc_Gia* root, const int& mathe ) {
    Danh_Sach_The_Doc_Gia* curr = root;
    while ( curr != nullptr && curr->thong_tin.MATHE != mathe ) {
        if ( curr->thong_tin.MATHE < mathe ) {
            curr = curr->ptr_right;
        } else {
            curr = curr->ptr_left;
        }
    }
    return curr;
}

void Inorder(Danh_Sach_The_Doc_Gia* root ) {
    if ( root != nullptr ) {
        Inorder(root->ptr_left);
        cout << root->thong_tin.MATHE << endl;
        Inorder(root->ptr_right);
    }
}

void Tao_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* root_maso, Danh_Sach_The_Doc_Gia* &root_ten) {
    if ( root_maso == nullptr ) {
        return;
    }

    Them_Doc_Gia_Theo_Ten(root_ten, root_maso->thong_tin);
    Tao_Danh_Sach_Theo_Ten(root_maso->ptr_left, root_ten);
    Tao_Danh_Sach_Theo_Ten(root_maso->ptr_right, root_ten);
}

void Xoa_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* &root_ten) {
    if ( root_ten == nullptr ) {
        return;
    }
    Xoa_Danh_Sach_Theo_Ten(root_ten->ptr_left);
    Xoa_Danh_Sach_Theo_Ten(root_ten->ptr_right);
    delete root_ten;
}

void swap( int& a, int& b ) {
    int temp = b;
    b = a;
    a = temp;
}

void LayDayNgauNhien (int *DayNgauNhien) {
    srand(time(NULL)); 
	for (int i = 0; i < MAXRANDOM; i++) {
        DayNgauNhien[i] = i + 1;
    }
    for (int i = 0; i < MAXRANDOM; i++) {
        int select = rand() % (MAXRANDOM - i) + i; 
        swap(DayNgauNhien[select], DayNgauNhien[i]);
    }
}

int LayMaTheNgauNhien() {
    if ( Random_Ptr >= MAXRANDOM) {
        return -1;
    }
    return DayNgauNhien[Random_Ptr++];
}

void TraVeSoNgauNhien(int So_Tra_Ve) {
    int ViTri = 0;
    for ( ; ViTri < Random_Ptr; ViTri++ ) {
        if ( DayNgauNhien[ViTri] == So_Tra_Ve ) {
            break;
        }
    }
    
    if ( ViTri != -1 ) {
        swap(DayNgauNhien[ViTri], DayNgauNhien[--Random_Ptr]);
    }
}

void Doc_Thong_Tin_Tu_File(const string& file_name, Danh_Sach_The_Doc_Gia* &root_ma_so) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Không thể mở file: " << file_name << endl;
        return;
    }

    unsigned int mathe;
    string Ho, Ten, phai_str;
    Phai phai;

    while (file >> mathe >> Ho >> Ten >> phai_str) {
        if (phai_str == "Nam") {
            phai = Nam;
        } else {
            phai = Nu;
        }
        The_Doc_Gia DocGia;
        DocGia.MATHE = mathe;
        DocGia.Ho = Ho;
        DocGia.Ten = Ten;
        DocGia.phai = phai;
        DocGia.TrangThai = TrangThaiCuaThe::Dang_Hoat_Dong;
    }
    file.close();
}

#endif