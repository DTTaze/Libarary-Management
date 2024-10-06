#include <iostream> 
#include <cstring>
#include <string>
#define MAXSACH 10000
#define MAXKHUVUC 10 // 10 khu vuc tu A - J
#define MAXDAY 1000 // 1 day la 1000 cuon sach
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
    string theloai;
    DanhMucSach* dms = nullptr;
     DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia, const string& the_loai, DanhMucSach* ptr_dms)
        : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia), theloai(the_loai), dms(ptr_dms) {}
};

struct DanhSachDauSach{
    int demsach= 0;
    DauSach* node[MAXSACH];     
};

struct MUONTRA {
    int masach;
    string ngaymuon[10];
    string ngaytra[10];
    int vitri;
    MUONTRA* next = nullptr;
};

struct The_Doc_Gia {
    unsigned int MATHE;
    string ho[10];
    string ten[10];
    enum phai{Nam, Nu};
    enum trang_thai_cua_the{Khoa=0, Dang_Hoat_Dong=1};
    DauSach* head_lsms = nullptr;
};

struct Danh_Sach_The_Doc_Gia {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia* ptr_right = nullptr;
};

void Them_Doc_Gia(Danh_Sach_The_Doc_Gia* &root, The_Doc_Gia thong_tin_the_doc_gia ) {
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
            Them_Doc_Gia(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia(root->ptr_left, thong_tin_the_doc_gia);
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

void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia* &r, int ma_the_doc_gia) {
    if ( r == nullptr ) printf("Khong Tim Thay ");
    else {  
        if ( r->thong_tin.MATHE < ma_the_doc_gia ) {
            Xoa_Doc_Gia(r->ptr_right, ma_the_doc_gia );
        } else if ( r->thong_tin.MATHE > ma_the_doc_gia ) {
            Xoa_Doc_Gia(r->ptr_left, ma_the_doc_gia );
        } else {
            rp = r;
            if ( rp->ptr_right == nullptr ) r = rp->ptr_left;
            else if ( rp->ptr_left == nullptr ) r = rp->ptr_right;
            else xoa_truong_hop_co_hai_cay_con(rp->ptr_right);
            delete rp;
        }
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

void LayDayNgauNhien (int *A, int m, int n = 1){
	for (int i = 1; i <= n; i++) {
        A[i] = i ;
        for (int i = 1; i <= m; i++) {
            int select = rand() % (n - i+1) + i; 
            swap(A[select], A[i]);
        }
    }
}

void TaoMaSach(string& ma_sach ,int dem_sach, string& vi_tri){
    string khu_vuc = 'A' + to_string(dem_sach / 1000);
    vi_tri = khu_vuc;

    int day = (dem_sach % 1000) / 100 + 1; // day 1 den 100
    vi_tri += to_string(day);

    int ID_sach = dem_sach % 100 ; // ID sach trong day

    ma_sach = khu_vuc + to_string(day) + "-" + to_string(ID_sach);
}

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,int dem_sach) {

    //them vao dau danh sach voi O(1)
    string ma_sach;
    string vi_tri;
    TaoMaSach(ma_sach,dem_sach,vi_tri);
    DanhMucSach* new_dms = new DanhMucSach(ma_sach,trang_thai,vi_tri);
    new_dms->next=head_dms;
    head_dms = new_dms;
    return new_dms;
};

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,const string& the_loai, 
                DanhMucSach* &head_dms, int trang_thai){
    
    if(danh_sach_dau_sach.demsach >= MAXSACH){
        cout<<"Day sach";
        return;
    };
    
    DanhMucSach* danh_muc_sach = ThemDanhMucSach(head_dms,trang_thai,danh_sach_dau_sach.demsach);


    int n = danh_sach_dau_sach.demsach;
    // cap phat bo nho cho sach moi voi con trỏ dms chi vao danh_muc_sach vua tao
    DauSach* new_sach = new DauSach(I_S_B_N,ten_sach,so_trang,tac_gia,the_loai,danh_muc_sach);

    //mac dinh chen vao cuoi
    int vi_tri_them = n;
    //xac dinh vi tri chen
    for (int i = 0; i < n ; i++){
        if (ten_sach < danh_sach_dau_sach.node[i]->tensach){
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
    for (int i = 0; i < copy.demsach - 1 ; i++){
        for (int j =0 ; j < copy.demsach - i - 1 ; j++){
            //sap xep theo the loai truoc
            if (copy.node[j]->theloai > copy.node[j+1]->theloai ){
                DauSach* temp = copy.node[j];
                copy.node[j] = copy.node[j+1];
                copy.node[j+1] = temp;
            }//sap xep theo ten sach neu cung the loai
            else if (copy.node[j]->theloai == copy.node[j+1]->theloai
                    && copy.node[j]->tensach > copy.node[j+1]->tensach) {
                DauSach* temp = copy.node[j];
                copy.node[j] = copy.node[j+1];
                copy.node[j+1] = temp;
            }
        }
    };

    //in danh sach dau sach
    for (int i = 0; i < copy.demsach; i++){

        cout<<"The loai : "<< copy.node[i]->theloai<<"\n";
        cout<<"Ten sach : "<< copy.node[i]->tensach<<"\n";
        cout<<"Ma Sach : "<<copy.node[i]->dms->masach<<"\n";
        cout<<"Vi Tri : "<<copy.node[i]->dms->vitri<<"\n";

    }

    for (int i = 0; i < copy.demsach; i++) {
        delete copy.node[i]; 
    }

}

void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach, 
                    DanhMucSach* &head_dms){
    string I_S_B_N;string ten_sach;int so_trang;string tac_gia;string the_loai;
    int trang_thai; string vi_tri;
    cout<<"Nhap ISBN cua sach : \n";
    cin>>I_S_B_N;
    cout<<"Nhap ten sach : \n";
    cin>>ten_sach;
    cout<<"Nhap so trang : \n";
    cin>>so_trang;
    cout<<"Nhap tac gia : \n";
    cin>>tac_gia;
    cout<<"Nhap the loai : \n";
    cin>>the_loai;
    cout<<"Nhap trang thai : \n";
    cin>>trang_thai;
    cout<<"Nhap vi tri : \n";
    cin>>vi_tri;

    ThemDauSach(danh_sach_dau_sach,I_S_B_N,ten_sach,so_trang, tac_gia, the_loai, 
                head_dms, trang_thai);
}



void MUONSACH () {
    
}



int main() {
    enum dayofWeeks{Monday = 0, Tweday};
    

    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach = nullptr;

    ThemDauSach(danh_sach_dau_sach,"978-0-306-40615-7","Cho Tai Ngu", 154,"Tai cho dien","Ao Tuong",danh_muc_sach,0);
    ThemDauSach(danh_sach_dau_sach,"978-1-4028-9462-6","Cho Kien Ngu", 844,"Kien cho dien","Ao Tuong",danh_muc_sach,0);
    ThemDauSach(danh_sach_dau_sach,"978-0-14-312854-0","Bao dep zai", 1004,"Bao Hoang","Hien Thuc",danh_muc_sach,0);

    InTheoTungTheLoai(danh_sach_dau_sach);
}