#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"
using namespace std;




void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms) {
    ifstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        string ISBN, tensach, tacgia, theloai, vitri, hoten,ho,ten,ngaymuon,ngaytra,test,phai;
        int sotrang,namsx,trangthaithe,trangthaimuontra,trangthaidms,den;
        unsigned int mathe;

        // tach thong tin tung dong
        size_t pos = 0; 
        //ISBN
        pos = line.find('|');
        ISBN = line.substr(0, pos); line.erase(0, pos + 1);

        //Ten sach
        pos = line.find('|');
        tensach = line.substr(0, pos); line.erase(0, pos + 1);

        //So trang
        pos = line.find('|');
        sotrang = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        //Tac gia
        pos = line.find('|');
        tacgia = line.substr(0, pos); line.erase(0, pos + 1);
		
        //nam san xuat
        pos = line.find('|');
        namsx = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        //The loai
        pos = line.find('|');
        theloai = line.substr(0, pos); line.erase(0, pos + 1);

        //Vi tri
        pos = line.find('|');
        vitri = line.substr(0, pos); line.erase(0, pos + 1);

        //Thieu 1 trong 5 thi bo qua dong
        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue; 
        }
		
		//mã thẻ(nếu có)
        pos = line.find('|');
        if (pos != std::string::npos){    
            mathe = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

            //ho và ten
            pos = line.find('|');
            hoten = line.substr(0, pos); line.erase(0, pos + 1);
            
            size_t spacepos = hoten.find(' ');

            if (spacepos != std::string::npos){
                ho = hoten.substr(0, spacepos);
                ten = hoten.substr(spacepos+1);

            }else{
            	continue;
			}
			
			//Ngay muon sach
			pos = line.find('|');
            ngaymuon = line.substr(0, pos); line.erase(0, pos + 1);
			
			//Ngay tra sach (neu co)
			pos = line.find('|');
			test = line.substr(0, pos);line.erase(0, pos + 1);
			if (!test.empty()){	
		    	ngaytra = test; 

			}else {
				ngaytra =  " ";

			}
            
            //Trang thai muon tra
            pos = line.find('|');
            test = line.substr(0, pos);line.erase(0, pos + 1);
        	if (!test.empty()){	
	            trangthaimuontra = stoi(test);

			}else {
				trangthaimuontra = -1;

			}

            //den
            pos = line.find('|');
            test = line.substr(0, pos);line.erase(0, pos + 1);
        	if (!test.empty()){	
	            den = stoi(test);

			}else {
				den = -1;

			}
			
			//Trang thai cua sach
			pos = line.find('|');
   			test = line.substr(0, pos);line.erase(0, pos + 1);
        	if (!test.empty()){	
	            trangthaidms = stoi(test);

			}else {
				trangthaidms = -1;

			}

            //phai
            pos = line.find('|');
            phai = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        }
    }
    file.close();
}



int main() {
    enum dayofWeeks{Monday = 0, Tweday};
    

    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach = nullptr;

    DocTuFile(danh_sach_dau_sach,danh_muc_sach);

    InTheoTungTheLoai(danh_sach_dau_sach);
}