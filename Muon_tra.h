
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "ngay.cpp"
using namespace std;

/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, 
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách 
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/


enum trang_thai_cua_the{Khoa=0, Dang_Hoat_Dong=1};

struct DocGia {
    unsigned int MATHE;
    char ho[10];
    char ten[10];
    trang_thai_cua_the trangthaithe;
    DocGia *next = nullptr;
};

int TrangThai(Date ngay_muon, Date ngay_tra) {
    int songay = DemSoNgay(ngay_muon, ngay_tra);
    if(songay != -1) {
        if(ngay_tra.day == 0) {return 0;}
        else if(songay<=7) {
            return 1;
        }
        else {
            return 2;
        }
    } else {cout<<"nhap sai! vui long nhap lai."<<endl;return -1;}
}

struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
    int masach;
    string tensach;
    Date NgayMuon;
    Date NgayTra;
    int trangthai = TrangThai(NgayMuon, NgayTra);
};

struct DanhSachMUONTRA { // danh sach cac quyen sach da hoac dang muon
    MUONTRA data;
    DanhSachMUONTRA *next = nullptr;
};

struct DocGiaMuonSach { 
    DocGia docgia;
    DanhSachMUONTRA danhsachmuontra;
};

DanhSachMUONTRA * MakeNodes (MUONTRA data) {
    DanhSachMUONTRA * temp = new DanhSachMUONTRA();
    temp->data = data;
    temp->next = nullptr;
    return temp;
}

int DemSoSach(DanhSachMUONTRA *demsach) {
    DanhSachMUONTRA *temp = demsach;

    int dem = 0;
    while(temp!=nullptr) {
        temp = temp->next;
        dem++;
    }
    return dem;
}

void ThemSach (DanhSachMUONTRA * &head, MUONTRA data) {
    DanhSachMUONTRA * newMUONTRA = MakeNodes(data);
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

void InManHinhDSSach(DanhSachMUONTRA * head) {
    DanhSachMUONTRA * temp = head;
    while(temp != nullptr) {
        cout << temp->data.masach<<endl;
        InManHinhNgayThangNam(temp->data.NgayMuon);
        InManHinhNgayThangNam(temp->data.NgayTra);
        if(temp->data.trangthai == 0) {
            cout << "0"<<endl;
        } else if(temp->data.trangthai == 1) {
            cout << "1"<< endl;
        } else {
            cout << "2" << endl;
        }
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

void MuonSach (DocGiaMuonSach doc_gia) {
    int sosach = DemSoSach(doc_gia.danhsachmuontra.next);
    if(doc_gia.docgia.trangthaithe == Khoa || doc_gia.danhsachmuontra.data.trangthai == 2 || sosach>3) {
        cout<<"khong the muon sach"<<endl;
        return;
    } else {
        
        string tensach;
        getline(cin,tensach);
        doc_gia.danhsachmuontra.data.tensach = tensach;
        Date ngaymuon = NgayMuon();
        Date ngaytra = NgayTraThucTe();
        doc_gia.danhsachmuontra.data.NgayMuon = ngaymuon;
        doc_gia.danhsachmuontra.data.NgayTra = ngaytra;
        ThemSach(doc_gia.danhsachmuontra.next, doc_gia.danhsachmuontra.data);
    }
}

void TraSach (DocGiaMuonSach doc_gia) {
    
}

void DanhSachSachDocGiaMuon(DocGiaMuonSach doc_gia) {

}



int main() {

}