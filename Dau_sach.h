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


void TaoMaSach(string& ma_sach ,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri){
    int Khu_vuc = vi_tri[0] - 'A'; // khu A : 0 , B : 1 , ...
    int day = danh_sach_dau_sach.SodaytrongKhuvuc[Khu_vuc];
    
    if(danh_sach_dau_sach.Sosachtrongday[Khu_vuc][day] > 99) {
        danh_sach_dau_sach.SodaytrongKhuvuc[Khu_vuc]++;//neu da co 100 cuon sach thi tang len day tiep theo
        day++;
    };
    
    
    int so_sach = danh_sach_dau_sach.Sosachtrongday[Khu_vuc][day];
    vi_tri += to_string(day);
    ma_sach = vi_tri + "-" + to_string(danh_sach_dau_sach.Sosachtrongday[Khu_vuc][day]);

    danh_sach_dau_sach.Sosachtrongday[Khu_vuc][day]++;
};

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri) {

    //them vao dau danh sach voi O(1)
    string ma_sach;
    TaoMaSach(ma_sach,danh_sach_dau_sach,vi_tri);
    DanhMucSach* new_dms = new DanhMucSach(ma_sach,trang_thai,vi_tri);
    DanhMucSach* t = nullptr;
    DanhMucSach* s = head_dms;
    for ( ; s != nullptr && new_dms->masach > s->masach; t = s , s = s->next);
    if (s == nullptr){
        new_dms->next = head_dms;
        head_dms = new_dms;
    }else{
        new_dms->next = s;
        t->next = new_dms;
    }
    
    return new_dms;
};

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai, 
                DanhMucSach* &head_dms, int trang_thai,string &vi_tri){
    
    if(danh_sach_dau_sach.demsach >= MAXSACH){
        cout<<"Day sach";
        return;
    };
    
    DanhMucSach* danh_muc_sach = ThemDanhMucSach(head_dms,trang_thai,danh_sach_dau_sach,vi_tri);


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

DanhSachDauSach SaoChepDanhSach(DanhSachDauSach &Dau_sach_goc) {
    DanhSachDauSach copy;
    copy.demsach = Dau_sach_goc.demsach;

    for (int i = 0; i < Dau_sach_goc.demsach; i++) {
        DauSach* original_dau_sach = Dau_sach_goc.node[i];
        // Tạo một bản sao của DauSach goc voi pointer chỏ vao cung bo nho voi Dau sach goc
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


int TimKiemNhiPhanTenSach(DanhSachDauSach &danh_sach_dau_sach,string key){
	int left = 0;
	int right = danh_sach_dau_sach.demsach-1;
	int ket_qua = -1;
	
	while(left <= right){
		int mid = (left + right) /2;
		string tien_to = danh_sach_dau_sach.node[mid]->tensach.substr(0,key.size());
		
		if (tien_to == key) {
            ket_qua = mid; 
            right = mid - 1;//doi right ve mid de xac dinh vi tri tien to dau tien 
        } else if (tien_to < key) {//key ben phai
            left = mid + 1; 
        } else {//key ben trai
            right = mid - 1; 
        }
	}
	return ket_qua;	
}

int TimKiemNhiPhanTheLoai(DanhSachDauSach &danh_sach_dau_sach,string key){
	int left = 0;
	int right = danh_sach_dau_sach.demsach-1;
	int ket_qua = -1;
	
	while(left <= right){
		int mid = (left + right) /2;
		
		if (danh_sach_dau_sach.node[mid]->theloai == key) {
            ket_qua = mid; 
            right = mid - 1;//doi right ve mid de xac dinh vi tri tien to dau tien 
        } else if (danh_sach_dau_sach.node[mid]->theloai < key) {//key ben phai
            left = mid + 1; 
        } else {//key ben trai
            right = mid - 1; 
        }
	}
	return ket_qua;	
}
//Su dung tham chieu nen phai tao ban sao roi xoa ban sao
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach){

    DanhSachDauSach copy = SaoChepDanhSach(danh_sach_dau_sach);

    //Su dung thuat toan bubble sort de sap xep va in, khong dung tham chieu
    
   	int so_luong_sach = copy.demsach;
   	//sap xep theo the loai
   	for (int i = 0; i < so_luong_sach - 1; i++) {
        for (int j = 0; j < so_luong_sach -  i - 1; j++) {
            if (copy.node[j]->theloai > copy.node[j + 1]->theloai) {
                DauSach* temp = copy.node[j];
	            copy.node[j] = copy.node[j+1];
	            copy.node[j+1] = temp;
            }	//sap xep theo ten sach trong the loai
            else if (copy.node[j]->theloai ==copy.node[j + 1]->theloai && copy.node[j]->tensach > copy.node[j + 1]->tensach) {
                DauSach* temp = copy.node[j];
	            copy.node[j] = copy.node[j+1];
	            copy.node[j+1] = temp;
            }
        }
    }
    string key;
    cout<<"Nhap the loai : ";getline(cin,key);
    int vi_tri_dau_tien = TimKiemNhiPhanTheLoai(copy,key);
    
    if (vi_tri_dau_tien != -1 ){
	    for (int i = vi_tri_dau_tien; i < copy.demsach && copy.node[i]->theloai == key; i++){
		    cout<<"The loai : "<< copy.node[i]->theloai<<" | Ten sach : "<< copy.node[i]->tensach<<"\n";
	
	    }
	}
	
	for (int i = 0; i < copy.demsach; i++) {
	    delete copy.node[i]; 
	}
};


void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach){
    string key;
    char c;

    cout<<"Nhap ten sach : ";
    while (true){
        c = _getch(); // lay ki tu khong dung enter

        if (c == 13) { // enter de dung
            break;
        } else if (c == '\b') { // phim backspace
            if (!key.empty()) {
                key.pop_back(); // Xoa ky tu cuoi
            }
        } else if (isprint(c)) { 
            key += c;
        }
        
   		system("cls");
		cout<<"Nhap ten sach : "<<key<<endl;
		
		int vi_tri_dau_tien = TimKiemNhiPhanTenSach(danh_sach_dau_sach,key);
		
        if (!key.empty()){
			for (int i = vi_tri_dau_tien; i <danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->tensach.substr(0,key.size()) == key;i++ ){
					cout << "- " << danh_sach_dau_sach.node[i]->tensach <<endl;
			}
		}
	} 
}

bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach,string vi_tri){
    int Khu_vuc = vi_tri[0] - 'A'; // khu A : 0 , B : 1 , ...,J : 9
    int day = danh_sach_dau_sach.SodaytrongKhuvuc[Khu_vuc];
    int so_sach = danh_sach_dau_sach.Sosachtrongday[Khu_vuc][day];
    if (day == 9 && so_sach > 99){
        cout<<"So sach trong vi tri : "<<vi_tri<< " da day, vui long nhap lai.\n";
        return true;
    }else{return false;};
};

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

    do{
        bool k_hop_le = true;
        do{
            cout << "Nhap vi tri (A - J): \n";
            getline(cin, vi_tri); 
            
            if (vi_tri < "A" || vi_tri > "J") {
                cout << "vi tri khong hop le. Vui long nhap tu A den J." << endl;
                k_hop_le = false;
            }
        }while(!k_hop_le);

    }while(KiemTraDaySachKV(danh_sach_dau_sach,vi_tri));

    ThemDauSach(danh_sach_dau_sach,I_S_B_N,ten_sach,so_trang, tac_gia,nam_sx, the_loai, 
                head_dms, 0,vi_tri);
    //ghi vao file
    ofstream file("Danh_sach_dau_sach.txt", ios::app); // Mo file che do append
    if (file.is_open()) {
        file << I_S_B_N << '|'
             << ten_sach << '|'
             << so_trang << '|'
             << tac_gia << '|'
             << nam_sx << '|'
             << the_loai << '|'
             << vi_tri << endl; 
        file.close(); 
    } else {
        cout << "Khong the mo file de ghi!" << endl;
    }
}

void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms) {
    ifstream file("Danh_sach_dau_sach.txt");
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

        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue; 
        }

        ThemDauSach(danh_sach_dau_sach, ISBN, tensach, sotrang, tacgia,namsx, theloai, head_dms, 0,vitri);
    }

    file.close();
}
