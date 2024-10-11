#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
using namespace std;

enum Phai{Nam = 1, Nu = 0};
enum TrangThaiCuaThe{Dang_Hoat_Dong = 1, Khoa = 0};

struct The_Doc_Gia {
    unsigned int MATHE;
    string Ho;
    string Ten;
    TrangThaiCuaThe TrangThai;
    Phai phai;
    LichSuMuonSach* head_lsms = nullptr;
};

struct LichSuMuonSach {
    DauSach* ThongTinDauSach;
    LichSuMuonSach* next; 
};

struct Danh_Sach_The_Doc_Gia_Theo_Ma_So {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia_Theo_Ma_So* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia_Theo_Ma_So* ptr_right = nullptr;
};

struct Danh_Sach_The_Doc_Gia_Theo_Ten {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia_Theo_Ten* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia_Theo_Ten* ptr_right = nullptr;
};

void Them_Doc_Gia_Theo_Ma_So(Danh_Sach_The_Doc_Gia_Theo_Ma_So* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia_Theo_Ma_So* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia_Theo_Ma_So;
        con_tro_the_doc_gia->thong_tin = thong_tin_the_doc_gia;
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.MATHE == thong_tin_the_doc_gia.MATHE ) {
            cout << "Ma the doc gia da ton tai." << endl;   
            return;
        }
        if ( root->thong_tin.MATHE < thong_tin_the_doc_gia.MATHE ) {
            Them_Doc_Gia_Theo_Ma_So(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia_Theo_Ma_So(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}

void Them_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia_Theo_Ten* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia_Theo_Ten* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia_Theo_Ten;
        con_tro_the_doc_gia->thong_tin = thong_tin_the_doc_gia;
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.Ten == thong_tin_the_doc_gia.Ten ) {
            cout << "Ten doc gia da ton tai." << endl;   
            return;
        }
        if ( root->thong_tin.Ten < thong_tin_the_doc_gia.Ten ) {
            Them_Doc_Gia_Theo_Ten(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia_Theo_Ten(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}
Danh_Sach_The_Doc_Gia_Theo_Ma_So* rp_ma_so;
Danh_Sach_The_Doc_Gia_Theo_Ten* rp_ten;

void Xoa_Truong_Hop_Co_Hai_Cay_Con_Ma_So(Danh_Sach_The_Doc_Gia_Theo_Ma_So* r ) {
    if ( r->ptr_left != nullptr ) {
        Xoa_Truong_Hop_Co_Hai_Cay_Con_Ma_So(r->ptr_left);
    } else {
        rp_ma_so->thong_tin = r->thong_tin;
        Danh_Sach_The_Doc_Gia_Theo_Ma_So* temp = r;
        r = r->ptr_right;
        delete temp;
    }
}

void Xoa_Truong_Hop_Co_Hai_Cay_Con_Ten(Danh_Sach_The_Doc_Gia_Theo_Ten* r ) {
    if ( r->ptr_left != nullptr ) {
        Xoa_Truong_Hop_Co_Hai_Cay_Con_Ten(r->ptr_left);
    } else {
        rp_ma_so->thong_tin = r->thong_tin;
        Danh_Sach_The_Doc_Gia_Theo_Ten* temp = r;
        r = r->ptr_right;
        delete temp;
    }
}

void Xoa_Doc_Gia_Theo_Ma_So(Danh_Sach_The_Doc_Gia_Theo_Ma_So* &r, const int& ma_the_doc_gia) {
    if ( r == nullptr ) {
        cout << "Khong Tim Thay " << ma_the_doc_gia << endl;
    }
    else {  
        if ( r->thong_tin.MATHE < ma_the_doc_gia ) {
            Xoa_Doc_Gia_Theo_Ma_So(r->ptr_right, ma_the_doc_gia );
        } else if ( r->thong_tin.MATHE > ma_the_doc_gia ) {
            Xoa_Doc_Gia_Theo_Ma_So(r->ptr_left, ma_the_doc_gia );
        } else {
            rp_ma_so = r;
            if ( rp_ma_so->ptr_right == nullptr ) {
                r = rp_ma_so->ptr_left;
            } else if ( rp_ma_so->ptr_left == nullptr ) {
                r = rp_ma_so->ptr_right;
            } else {
                Xoa_Truong_Hop_Co_Hai_Cay_Con_Ma_So(rp_ma_so->ptr_right);
            }
            delete rp_ma_so;
        }
    }
}

void Xoa_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia_Theo_Ten* &r, const string& ten_doc_gia) {
    if (r == nullptr) {
        cout << "Khong Tim Thay " << ten_doc_gia << endl;
        return;
    }
    if (r->thong_tin.Ten < ten_doc_gia) {
        Xoa_Doc_Gia_Theo_Ten(r->ptr_right, ten_doc_gia);
    } else if (r->thong_tin.Ten > ten_doc_gia) {
        Xoa_Doc_Gia_Theo_Ten(r->ptr_left, ten_doc_gia);
    } else {
        rp_ten = r;
        if (rp_ten->ptr_right == nullptr) {
            r = rp_ten->ptr_left;
        } else if (rp_ten->ptr_left == nullptr) {
            r = rp_ten->ptr_right;
        } else {
            Xoa_Truong_Hop_Co_Hai_Cay_Con_Ten(rp_ten->ptr_right);
        }
        delete rp_ten;
    }
}

Danh_Sach_The_Doc_Gia_Theo_Ma_So* Tim_Kiem_Theo_Ma_So(Danh_Sach_The_Doc_Gia_Theo_Ma_So* root, const int& mathe ) {
    Danh_Sach_The_Doc_Gia_Theo_Ma_So* curr = root;
    while ( curr != nullptr && curr->thong_tin.MATHE != mathe ) {
        if ( curr->thong_tin.MATHE < mathe ) {
            curr = curr->ptr_right;
        } else {
            curr = curr->ptr_left;
        }
    }
    return curr;
}

Danh_Sach_The_Doc_Gia_Theo_Ten* Tim_Kiem_Theo_Ten(Danh_Sach_The_Doc_Gia_Theo_Ten* root, const int& mathe ) {
    Danh_Sach_The_Doc_Gia_Theo_Ten* curr = root;
    while ( curr != nullptr && curr->thong_tin.MATHE != mathe ) {
        if ( curr->thong_tin.MATHE < mathe ) {
            curr = curr->ptr_right;
        } else {
            curr = curr->ptr_left;
        }
    }
    return curr;
}

void CapNhatLichSuMuonSach() {

}

void Inorder(Danh_Sach_The_Doc_Gia_Theo_Ten* root ) {
    if ( root != nullptr ) {
        Inorder(root->ptr_left);
        cout << root->thong_tin.MATHE << endl;
        Inorder(root->ptr_right);
    }
}

void Doc_Thong_Tin_Tu_File(const string& file_name, Danh_Sach_The_Doc_Gia_Theo_Ma_So* &root_ma_so, Danh_Sach_The_Doc_Gia_Theo_Ten* & root_ten) {
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
        Them_Doc_Gia_Theo_Ma_So(root_ma_so, DocGia);
        Them_Doc_Gia_Theo_Ten(root_ten, DocGia);
    }
    file.close();
}

