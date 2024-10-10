#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

enum Phai{Nam = 1, Nu = 0};
enum TrangThaiCuaThe{Dang_Hoat_Dong = 1, Khoa = 0};

struct The_Doc_Gia {
    unsigned int MATHE;
    string ho;
    string ten;
    TrangThaiCuaThe TrangThai;
    Phai phai;
    DauSach* head_lsms = nullptr;
};

struct Danh_Sach_The_Doc_Gia {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia* ptr_right = nullptr;
};

struct Danh_Sach_The_Doc_Gia_Theo_Ten {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia* ptr_right = nullptr;
};

void Them_Doc_Gia_Theo_Ma_So(Danh_Sach_The_Doc_Gia* &root, The_Doc_Gia thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia;
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

void Them_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia* &root, The_Doc_Gia thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia;
        con_tro_the_doc_gia->thong_tin = thong_tin_the_doc_gia;
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.ten[0] == thong_tin_the_doc_gia.ten[0] ) {
            cout << "Ma the doc gia da ton tai." << endl;   
            return;
        }
        if ( root->thong_tin.ten[0] < thong_tin_the_doc_gia.ten[0] ) {
            Them_Doc_Gia_Theo_Ten(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia_Theo_Ten(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}

Danh_Sach_The_Doc_Gia* rp;

void xoa_truong_hop_co_hai_cay_con(Danh_Sach_The_Doc_Gia* r ) {
    if ( r->ptr_left != nullptr ) {
        xoa_truong_hop_co_hai_cay_con(r->ptr_left);
    } else {
        rp->thong_tin = r->thong_tin;
        Danh_Sach_The_Doc_Gia* temp = r;
        r = r->ptr_right;
        delete temp;
    }
}

void Xoa_Doc_Gia_Theo_Ma_So(Danh_Sach_The_Doc_Gia* &r, int ma_the_doc_gia) {
    if ( r == nullptr ) printf("Khong Tim Thay ");
    else {  
        if ( r->thong_tin.MATHE < ma_the_doc_gia ) {
            Xoa_Doc_Gia_Theo_Ma_So(r->ptr_right, ma_the_doc_gia );
        } else if ( r->thong_tin.MATHE > ma_the_doc_gia ) {
            Xoa_Doc_Gia_Theo_Ma_So(r->ptr_left, ma_the_doc_gia );
        } else {
            rp = r;
            if ( rp->ptr_right == nullptr ) r = rp->ptr_left;
            else if ( rp->ptr_left == nullptr ) r = rp->ptr_right;
            else xoa_truong_hop_co_hai_cay_con(rp->ptr_right);
            delete rp;
        }
    }
}

void Xoa_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia* &r, const string& ten_doc_gia) {
    if (r == nullptr) {
        cout << "Khong Tim Thay " << ten_doc_gia << endl;
        return;
    }

    if (r->thong_tin.ten < ten_doc_gia) {
        Xoa_Doc_Gia_Theo_Ten(r->ptr_right, ten_doc_gia);
    } else if (r->thong_tin.ten > ten_doc_gia) {
        Xoa_Doc_Gia_Theo_Ten(r->ptr_left, ten_doc_gia);
    } else {
        rp = r;
        if (rp->ptr_right == nullptr) {
            r = rp->ptr_left;
        } else if (rp->ptr_left == nullptr) {
            r = rp->ptr_right;
        } else {
            xoa_truong_hop_co_hai_cay_con(rp->ptr_right);
        }
        delete rp;
    }
}

Danh_Sach_The_Doc_Gia* Tim_Kiem(Danh_Sach_The_Doc_Gia* root, int mathe ) {
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

void Doc_Thong_Tin_Tu_File(const string& file_name, Danh_Sach_The_Doc_Gia* &root) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Không thể mở file: " << file_name << endl;
        return;
    }

    unsigned int mathe;
    string ho, ten, phai_str;
    Phai phai;

    while (file >> mathe >> ho >> ten >> phai_str) {
        if (phai_str == "Nam") {
            phai = Nam;
        } else {
            phai = Nu;
        }

        The_Doc_Gia docGia;
        docGia.MATHE = mathe;
        docGia.ho = ho;
        docGia.ten = ten;
        docGia.phai = phai;
        docGia.TrangThai = TrangThaiCuaThe::Dang_Hoat_Dong;

        // Thêm độc giả vào cây
        Them_Doc_Gia_Theo_Ma_So(root, docGia);
        Them_Doc_Gia_Theo_Ten(root, docGia);
    }

    file.close();
}

