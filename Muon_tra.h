#ifndef MUON_TRA_H
#define MUON_TRA_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "ngay.cpp"
#include "The_doc_gia.h"
using namespace std;

/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, 
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách 
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

struct DanhSachTheDocGia {
    The_Doc_Gia docgia;
    DanhSachTheDocGia *next = nullptr;
};

int TrangThai(Date ngay_muon, Date ngay_tra) { // trạng thái sách của độc giả 
    int songay = DemSoNgay(ngay_muon, ngay_tra);
    if(songay != -1) {
        if(ngay_tra.day == 0) {return 0;} // chưa trả
        else if(songay<=7) {
            return 1; // đã trả
        }
        else {
            return 2; // mất sách
        }
    } else {cout<<"nhap sai! vui long nhap lai."<<endl;return -1;}
}

struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
    string masach;
    string tensach;
    Date NgayMuon;
    Date NgayTra;
    int trangthai;
    MUONTRA(string ma, const string &ten, const Date &ngayMuon, const Date &ngayTra) : masach(ma), tensach(ten), NgayMuon(ngayMuon), NgayTra(ngayTra) 
    { trangthai = TrangThai(NgayMuon, NgayTra);}

    bool operator == (const MUONTRA &other) const {
        return masach == other.masach && tensach == other.tensach && NgayMuon == other.NgayMuon && NgayTra == other.NgayTra;
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
    LichSuMuonSach *lichsumuonsach;

    DocGiaMuonSach(const The_Doc_Gia &thedocgia) : docgia(thedocgia), danhsachmuontra(nullptr), lichsumuonsach(nullptr){}
};

int DemSoSach(DanhSachMUONTRA *demsach) {
    DanhSachMUONTRA *temp = demsach;

    int dem = 0;
    while(temp!=nullptr) {
        temp = temp->next;
        dem++;
    }
    return dem;
}

void ThemSach (DanhSachMUONTRA * &head, string ma, const string &ten, const Date &ngayMuon, const Date &ngayTra) {
    MUONTRA data(ma, ten, ngayMuon, ngayTra);
    DanhSachMUONTRA * newMUONTRA = new DanhSachMUONTRA(data);
    if (head == nullptr)
    {
        head = newMUONTRA;
    }
    else {
        DanhSachMUONTRA * temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newMUONTRA;
    }
}

bool Empty(DanhSachMUONTRA * First)
{   return(First == NULL);
}

int XoaSachDauTien (DanhSachMUONTRA *&First)
{ DanhSachMUONTRA * p;
   if (Empty(First))      return 0;
    p = First;    // nut can xoa la nut dau
    First = p->next;
    delete p; 
    return 1;
}

int XoaSachSauSachP(DanhSachMUONTRA * p)
{   DanhSachMUONTRA * q;
  // nếu p là NULL hoặc sau p không có nút
   if((p == NULL) || (p->next == NULL))	
      return 0;
      q = p->next;  // q chi nut can xoa
      p->next = q->next;
     delete q;
     return 1;
}

int XoaSachTheoThongTin(DanhSachMUONTRA * &head, string ma, const string &ten, const Date &ngayMuon, const Date &ngayTra) {  
    MUONTRA data(ma, ten, ngayMuon, ngayTra);
    DanhSachMUONTRA * p=head;
  if (head == NULL ) return 0;
  if (head->data == data ) {
        XoaSachDauTien(head); return 1;
  }
     
while (p->next != nullptr) {
        if (p->next->data == data) {
            XoaSachSauSachP(p);
            return 1;
        }
        p = p->next;
    }

    return 0;
}

enum DenSach {daden, chuaden};

void InManHinhDSSach(DocGiaMuonSach * head) {
    DocGiaMuonSach * temp = head;
    DanhSachMUONTRA *tmp = temp->danhsachmuontra;
    while(tmp != nullptr) {
        cout << tmp->data.masach <<endl;
        InManHinhNgayThangNam(tmp->data.NgayMuon);
        InManHinhNgayThangNam(tmp->data.NgayTra);
        if(tmp->data.trangthai == 0) {
            cout<< "0" << endl;
        } else if(tmp->data.trangthai == 1) {
            cout<< "1" << endl;
        } else {
            DenSach densach;
            if(densach == daden) {
                temp->docgia.TrangThai = Dang_Hoat_Dong;
                tmp->data.trangthai = 1;
                cout<< "1" << endl;
            }
            else {
                temp->docgia.TrangThai = Khoa;
                cout<< "2" << endl;
            }
        }
        tmp = tmp->next;
    }
}

void LuuNgayMuon(const string& fileName, const Date& ngay_muon) {
    ofstream file(fileName);
    if (file.is_open()) {
        file << ngay_muon.day << "/" << ngay_muon.month << "/" << ngay_muon.year;
        file.close();
        cout << "Ngay muon sach da duoc luu: " << ngay_muon.day << "/" << ngay_muon.month << "/" << ngay_muon.year << endl;
    } else {
        cout << "Khong the mo file de ghi." << endl;
    }
}

void ThemSachVaoLSMS(LichSuMuonSach * &sach, const string& I_S_B_N, const string& ten_sach, int so_trang,
                        const string& tac_gia,int nam_sx, const string& the_loai, DanhMucSach* ptr_dms) {
    DauSach* thongtindausach = new DauSach (I_S_B_N, ten_sach, so_trang, tac_gia, nam_sx, the_loai, ptr_dms);
    LichSuMuonSach * newLichSu = new LichSuMuonSach( thongtindausach, nullptr);
    if (sach == nullptr)
    {
        sach = newLichSu;
    }
    else {
        LichSuMuonSach* temp = sach;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newLichSu;
    }
}

void MuonSach (DocGiaMuonSach *doc_gia) {
    DocGiaMuonSach *tmp = doc_gia;
    DanhSachMUONTRA *temp = tmp->danhsachmuontra;
    LichSuMuonSach *lichsu = tmp->lichsumuonsach;
    
    int sosach = DemSoSach(temp);
    if(doc_gia->docgia.TrangThai == Khoa || temp->data.trangthai == 2 || sosach>3) {
        cout<<"khong the muon sach"<<endl;
        return;
    } else {
        string ma; cout<<"nhap ma: ";
        cin>>ma;
        cin.ignore();
        temp->data.masach = ma;
        string tensach;
        getline(cin,tensach);
        temp->data.tensach = tensach;
        Date ngaymuon = NgayMuon();
        Date ngaytra = NgayTraThucTe();
        temp->data.NgayMuon = ngaymuon;
        temp->data.NgayTra = ngaytra;
        ThemSach(temp, ma, tensach, ngaymuon, ngaytra);
        ThemSachVaoLSMS(lichsu, lichsu->ThongTinDauSach->ISBN, temp->data.tensach, lichsu->ThongTinDauSach->sotrang, lichsu->ThongTinDauSach->tacgia, 
                    lichsu->ThongTinDauSach->namsx, lichsu->ThongTinDauSach->theloai, lichsu->ThongTinDauSach->dms );
    }
}

void TraSach (DocGiaMuonSach doc_gia) {
    
}

void DanhSachSachDocGiaMuon(DocGiaMuonSach doc_gia) {

}


#endif