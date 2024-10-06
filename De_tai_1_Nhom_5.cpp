#include <iostream> 
#include <cstring>
#define MAXSACH 10000

using namespace std;

struct DanhMucSach {
    char masach[10];
    int trangthai;
    char vitri[10];
    DanhMucSach* next;
    DanhMucSach(const char* ma_sach,int trang_thai,const char* vi_tri, DanhMucSach* ptr_dms_next) : trangthai(trang_thai), next(ptr_dms_next) {
        strcpy(vitri,vi_tri);
        strcpy(masach,ma_sach);
    };
    DanhMucSach(const char* ma_sach,int trang_thai,const char* vi_tri) : trangthai(trang_thai), next(nullptr) {
        strcpy(vitri,vi_tri);
        strcpy(masach,ma_sach);
    };
    DanhMucSach() : trangthai(-1), next(nullptr) {
        strcpy(vitri,"");
        strcpy(masach,"");
    };
};

struct DauSach {
    char ISBN[20];
    char tensach[50];
    int sotrang;
    char tacgia[50];
    char theloai[50];
    DanhMucSach* dms = nullptr;
    DauSach(const char* I_S_B_N,const char* ten_sach,int so_trang,const char* tac_gia,const char* the_loai, DanhMucSach* ptr_dms) :sotrang(so_trang), dms(ptr_dms) {
        strcpy(ISBN,I_S_B_N);
        strcpy(tensach,ten_sach);
        strcpy(tacgia,tac_gia);
        strcpy(theloai,the_loai);
    }
};

struct DanhSachDauSach{
    int demsach= 0;
    DauSach* node[MAXSACH];
};

struct MUONTRA {
    int masach;
    char ngaymuon[10];
    char ngaytra[10];
    int vitri;
    MUONTRA* next = nullptr;
};

struct The_Doc_Gia {
    unsigned int MATHE;
    char ho[10];
    char ten[10];
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

void TaoMaSach(char* ma_sach ,int dem_sach){
    
    char khu_vuc = 'A' + (dem_sach / 1000);  //moi khu vuc 1000 cuon
    int day = (dem_sach % 1000) / 100 + 1; // day 1 den 100
    int ID_sach = dem_sach % 100 ; // ID sach trong day

    sprintf(ma_sach, "%c%d-%d", khu_vuc, day, ID_sach);
}

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,const char* vi_tri,int dem_sach) {

    //them vao dau danh sach voi O(1)
    char ma_sach[10];
    TaoMaSach(ma_sach,dem_sach);
    DanhMucSach* new_dms = new DanhMucSach(ma_sach,trang_thai,vi_tri);
    new_dms->next=head_dms;
    head_dms = new_dms;
    return new_dms;
};

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const char* I_S_B_N,const char* ten_sach,int so_trang,const char* tac_gia,const char* the_loai, 
                DanhMucSach* &head_dms, int trang_thai,const char* vi_tri){
    
    if(danh_sach_dau_sach.demsach >= MAXSACH){
        cout<<"Day sach";
        return;
    };
    //tao danh muc sach co ma sach > 0 (demsach mac dinh = 0)
    DanhMucSach* danh_muc_sach = ThemDanhMucSach(head_dms,trang_thai,vi_tri,danh_sach_dau_sach.demsach);


    int n = danh_sach_dau_sach.demsach;
    // cap phat bo nho cho sach moi voi con trỏ dms chi vao danh_muc_sach vua tao
    DauSach* new_sach = new DauSach(I_S_B_N,ten_sach,so_trang,tac_gia,the_loai,danh_muc_sach);

    //mac dinh chen vao cuoi
    int vi_tri_them = n;
    //xac dinh vi tri chen
    for (int i = 0; i < n ; i++){
        if (strcmp(ten_sach,danh_sach_dau_sach.node[i]->tensach) < 0){
            vi_tri_them = i;
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

//Su dung tham chieu nen phai tao ban sao roi xoa ban sao
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach){
    //Su dung thuat toan bubble sort de sap xep va in, khong dung tham chieu
    for (int i = 0; i < danh_sach_dau_sach.demsach - 1 ; i++){
        for (int j =0 ; j < danh_sach_dau_sach.demsach - i - 1 ; j++){
            //sap xep theo the loai truoc
            if (strcmp(danh_sach_dau_sach.node[j]->theloai,danh_sach_dau_sach.node[j+1]->theloai) > 0 ){
                DauSach* temp = danh_sach_dau_sach.node[j];
                danh_sach_dau_sach.node[j] = danh_sach_dau_sach.node[j+1];
                danh_sach_dau_sach.node[j+1] = temp;
            }//sap xep theo ten sach neu cung the loai
            else if (strcmp(danh_sach_dau_sach.node[j]->theloai,danh_sach_dau_sach.node[j+1]->theloai) == 0
                    && strcmp(danh_sach_dau_sach.node[j]->tensach,danh_sach_dau_sach.node[j+1]->tensach) > 0) {
                DauSach* temp = danh_sach_dau_sach.node[j];
                danh_sach_dau_sach.node[j] = danh_sach_dau_sach.node[j+1];
                danh_sach_dau_sach.node[j+1] = temp;
            }
        }
    };

    //in danh sach dau sach
    for (int i = 0; i < danh_sach_dau_sach.demsach; i++){

        cout<<"The loai : "<< danh_sach_dau_sach.node[i]->theloai<<"\n";
        cout<<"Ten sach : "<< danh_sach_dau_sach.node[i]->tensach<<"\n";

    }
}

void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach, 
                    DanhMucSach* &head_dms){
    char I_S_B_N[20];char ten_sach[50];int so_trang;char tac_gia[50];char the_loai[50];
    int trang_thai; char vi_tri[10];
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
                head_dms, trang_thai, vi_tri);
}



void MUONSACH () {
    
}



int main() {
    enum dayofWeeks{Monday = 0, Tweday};
    

    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach = nullptr;

    ThemDauSach(danh_sach_dau_sach,"978-0-306-40615-7","Cho Tai Ngu", 154,"Tai cho dien","Ao Tuong",danh_muc_sach,0,"A-001");
    ThemDauSach(danh_sach_dau_sach,"978-1-4028-9462-6","Cho Kien Ngu", 844,"Kien cho dien","Ao Tuong",danh_muc_sach,0,"A-002");
    ThemDauSach(danh_sach_dau_sach,"978-0-14-312854-0","Bao dep zai", 1004,"Bao Hoang","Hien Thuc",danh_muc_sach,0,"A-003");

    InTheoTungTheLoai(danh_sach_dau_sach);
}