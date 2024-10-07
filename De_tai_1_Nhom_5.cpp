#include <iostream> 
#include <cstring>
#include <string>
#include <fstream>
#include "Dau_sach.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"
using namespace std;




void LayDayNgauNhien (int *A, int m, int n = 1){
	for (int i = 1; i <= n; i++) {
        A[i] = i ;
        for (int i = 1; i <= m; i++) {
            int select = rand() % (n - i+1) + i; 
            swap(A[select], A[i]);
        }
    }
}




int main() {
    enum dayofWeeks{Monday = 0, Tweday};
    

    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach = nullptr;
    DocTuFile(danh_sach_dau_sach,danh_muc_sach);

    InTheoTungTheLoai(danh_sach_dau_sach);
}