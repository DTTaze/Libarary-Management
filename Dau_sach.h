#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
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
};


void TaoMaSach(string& ma_sach ,int dem_sach, string& vi_tri){
    int day = (dem_sach % 1000) / 100 ; // day 1 den 100
    vi_tri += to_string(day);

    int ID_sach = dem_sach % 100 ; // ID sach trong day

    ma_sach = vi_tri + "-" + to_string(ID_sach);
}

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,int dem_sach, string& vi_tri) {

    //them vao dau danh sach voi O(1)
    string ma_sach;
    TaoMaSach(ma_sach,dem_sach,vi_tri);
    DanhMucSach* new_dms = new DanhMucSach(ma_sach,trang_thai,vi_tri);
    new_dms->next=head_dms;
    head_dms = new_dms;
    return new_dms;
};

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai, 
                DanhMucSach* &head_dms, int trang_thai,string &vi_tri){
    
    if(danh_sach_dau_sach.demsach >= MAXSACH){
        cout<<"Day sach";
        return;
    };
    
    DanhMucSach* danh_muc_sach = ThemDanhMucSach(head_dms,trang_thai,danh_sach_dau_sach.demsach,vi_tri);


    int n = danh_sach_dau_sach.demsach;
    // cap phat bo nho cho sach moi voi con trỏ dms chi vao danh_muc_sach vua tao
    DauSach* new_sach = new DauSach(I_S_B_N,ten_sach,so_trang,tac_gia,nam_sx,the_loai,danh_muc_sach);

    //mac dinh chen vao cuoi
    int vi_tri_them = n;
    //xac dinh vi tri chen
    for (int i = 0; i < n ; i++){
        if (ten_sach <= danh_sach_dau_sach.node[i]->tensach){
            vi_tri_them = i;
            break;
        }
    }

    //doi cac sach khac ra sau 1 vi tri
    for (int i = n; i > vi_tri_them ; i--){
        danh_sach_dau_sach.node[i] = danh_sach_dau_sach.node[i-1]; 
    }
    //chen sach vao vi tri tim duoc
    danh_sach_dau_sach.node[vi_tri_them] = new_sach;
    //tang dem sach len 1
    danh_sach_dau_sach.demsach++;
}

DanhSachDauSach SaoChepDanhSach(DanhSachDauSach &original) {
    DanhSachDauSach copy;
    copy.demsach = original.demsach;

    for (int i = 0; i < original.demsach; i++) {
        DauSach* original_dau_sach = original.node[i];
        // Tạo một bản sao của DauSach
        DauSach* new_dau_sach = new DauSach(
            original_dau_sach->ISBN,
            original_dau_sach->tensach,
            original_dau_sach->sotrang,
            original_dau_sach->tacgia,
            original_dau_sach->namsx,
            original_dau_sach->theloai,
            original_dau_sach->dms 
        );
        copy.node[i] = new_dau_sach;
    }

    return copy;
}

//Su dung tham chieu nen phai tao ban sao roi xoa ban sao
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach){

    DanhSachDauSach copy = SaoChepDanhSach(danh_sach_dau_sach);

    //Su dung thuat toan bubble sort de sap xep va in, khong dung tham chieu
    // for (int i = 0; i < copy.demsach - 1 ; i++){
    //     for (int j =0 ; j < copy.demsach - i - 1 ; j++){
    //         //sap xep theo the loai truoc
    //         if (copy.node[j]->theloai > copy.node[j+1]->theloai ){
    //             DauSach* temp = copy.node[j];
    //             copy.node[j] = copy.node[j+1];
    //             copy.node[j+1] = temp;
    //         }//sap xep theo ten sach neu cung the loai
    //         else if (copy.node[j]->theloai == copy.node[j+1]->theloai
    //                 && copy.node[j]->tensach > copy.node[j+1]->tensach) {
    //             DauSach* temp = copy.node[j];
    //             copy.node[j] = copy.node[j+1];
    //             copy.node[j+1] = temp;
    //         }
    //     }
    // };

    //in danh sach dau sach
    for (int i = 0; i < copy.demsach; i++){
        cout<<"ISBN : "<<copy.node[i]->ISBN<<"\n";
        cout<<"Ten sach : "<< copy.node[i]->tensach<<"\n";
        cout<<"So trang : "<< copy.node[i]->sotrang<<"\n";
        cout<<"Tac gia : "<< copy.node[i]->tacgia<<"\n";
        cout<<"Nam san xuat : "<< copy.node[i]->namsx<<"\n";
        cout<<"The loai : "<< copy.node[i]->theloai<<"\n";
        cout<<"Ma Sach : "<<copy.node[i]->dms->masach<<"\n";
        cout<<"Vi Tri : "<<copy.node[i]->dms->vitri<<"\n\n";

    }

    for (int i = 0; i < copy.demsach; i++) {
        delete copy.node[i]; 
    }

}


void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach, 
                    DanhMucSach* &head_dms){
    string I_S_B_N;string ten_sach;int so_trang;string tac_gia;int nam_sx;string the_loai;
    int trang_thai; string vi_tri;
    
     cout << "Nhap ISBN cua sach: \n";
    getline(cin, I_S_B_N);
    
    cout << "Nhap ten sach: \n";
    getline(cin, ten_sach);

    cout << "Nhap so trang: \n";
    cin >> so_trang;
    cin.ignore();  

    cout << "Nhap tac gia: \n";
    getline(cin, tac_gia);

    cout << "Nhap nam san xuat: \n";
    cin >> nam_sx;
    cin.ignore();

    cout << "Nhap the loai: \n";
    getline(cin, the_loai);

    cout << "Nhap khu vuc (A - J): \n";
    getline(cin, vi_tri); // Nhập khu vực từ A đến J

    // Kiểm tra khu vực hợp lệ
    if (vi_tri < "A" || vi_tri > "J") {
        cout << "Khu vuc khong hop le. Vui long nhap tu A den J." << endl;
        return;
    }

    ThemDauSach(danh_sach_dau_sach,I_S_B_N,ten_sach,so_trang, tac_gia,nam_sx, the_loai, 
                head_dms, 0,vi_tri);
}

void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms) {
    fstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string ISBN, tensach, tacgia, theloai, vitri;
        int sotrang,namsx;

        // tach thong tin tung dong
        size_t pos = 0; 
        pos = line.find('|');
        ISBN = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        tensach = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        sotrang = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        pos = line.find('|');
        tacgia = line.substr(0, pos); line.erase(0, pos + 1);
        
        pos = line.find('|');
        namsx = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        pos = line.find('|');
        theloai = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        vitri = line.substr(0, pos); line.erase(0, pos + 1);

        ThemDauSach(danh_sach_dau_sach, ISBN, tensach, sotrang, tacgia,namsx, theloai, head_dms, 0,vitri);
    }

    file.close();
}
