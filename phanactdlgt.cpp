#include <bits/stdc++.h>

using namespace std;

// Lop dai dien cho mot nha hang
class nhahang {
private:
    string ten;
    string chusohuu;
    double doanhthu;
    string diachi;
    int soluongnhanvien;
    float danhgia;

public:
    nhahang() : ten(""), chusohuu(""), doanhthu(0), diachi(""), soluongnhanvien(0), danhgia(0) {}

    // Nhap thong tin nha hang
    friend istream& operator>>(istream& is, nhahang& nh) {
        cout << "Nhap ten nha hang: "; is.ignore(); getline(is, nh.ten);
        cout << "Nhap chu so huu: "; getline(is, nh.chusohuu);
        cout << "Nhap doanh thu: "; is >> nh.doanhthu;
        is.ignore();
        cout << "Nhap dia chi: "; getline(is, nh.diachi);
        cout << "Nhap so luong nhan vien: "; is >> nh.soluongnhanvien;
        cout << "Nhap danh gia: "; is >> nh.danhgia;
        return is;
    }

    // Xuat thong tin nha hang
    friend ostream& operator<<(ostream& os, const nhahang& nh) {
        os << "Ten: " << nh.ten << ", Chu so huu: " << nh.chusohuu 
           << ", Doanh thu: " << nh.doanhthu << ", Dia chi: " << nh.diachi 
           << ", So luong nhan vien: " << nh.soluongnhanvien 
           << ", Danh gia: " << nh.danhgia;
        return os;
    }

    // So sanh theo doanh thu
    bool operator<(const nhahang& other) const {
        return doanhthu < other.doanhthu;
    }

    // Phan loai nha hang dua tren danh gia
    string phanloai() const {
        if (danhgia >= 4.5) return "Sang trong";
        else if (danhgia >= 4.0) return "Cao cap";
        else if (danhgia >= 2.0) return "Tam trung";
        else return "Kem chat luong";
    }

    double getdoanhthu() const { return doanhthu; }
    string getten() const { return ten; }
    string getdiachi() const { return diachi; }
    float getdanhgia() const { return danhgia; }
    string getchusohuu() const { return chusohuu; }
};

	// Lop quan ly danh sach nha hang
class danhsachnhahang {
private:
    vector<nhahang> danhsach;

public:
    // Nhap danh sach nha hang
    void nhapdanhsach() {
        int n;
        cout << "Nhap so luong nha hang: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            nhahang nh;
            cin >> nh;
            danhsach.push_back(nh);
        }
    }

    // Hien thi danh sach nha hang
    void hienthidanhsach() {
        for (const auto& nh : danhsach) {
            cout << nh << endl;
        }
    }

    // Hien thi nha hang co doanh thu cao nhat va thap nhat
    void hienthidoanhthumaxmin() {
        if (danhsach.empty()) {
            cout << "Danh sach rong!" << endl;
            return;
        }

    auto maxIt = max_element(danhsach.begin(), danhsach.end());
    auto minIt = min_element(danhsach.begin(), danhsach.end());

    cout << "Nha hang co doanh thu cao nhat:\n" << *maxIt << endl;
    cout << "Nha hang co doanh thu thap nhat:\n" << *minIt << endl;
    }

    // Tim nha hang theo ten
    void timnhahangtheoten(const string& ten) {
        for (const auto& nh : danhsach) {
            if (nh.getten() == ten) {
                cout << "Nha hang tim thay:\n" << nh << endl;
                return;
            }
        }
        cout << "Khong tim thay nha hang voi ten: " << ten << endl;
    }

    // Sap xep danh sach nha hang theo doanh thu
    void heapify(vector<nhahang>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left].getdoanhthu() > arr[largest].getdoanhthu()) {
            largest = left;
        }

        if (right < n && arr[right].getdoanhthu() > arr[largest].getdoanhthu()) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heapsort(vector<nhahang>& arr) {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    void sapxepphaidoanhthu() {
        heapsort(danhsach);
        cout << "Da sap xep danh sach nha hang theo doanh thu." << endl;
        hienthidanhsach();
    }

    // Sap xep danh sach nha hang theo phan loai
    void quicksort(vector<nhahang>& arr, int low, int high, function<bool(const nhahang&, const nhahang&)> cmp) {
    if (low < high) {
        	int pivot = partition(arr, low, high, cmp);
       	 	quicksort(arr, low, pivot - 1, cmp);
        	quicksort(arr, pivot + 1, high, cmp);
    	}
	}

	int partition(vector<nhahang>& arr, int low, int high, function<bool(const nhahang&, const nhahang&)> cmp) {
    nhahang pivot = arr[high]; 
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (cmp(arr[j], pivot)) {
            	i++;
            	swap(arr[i], arr[j]);
        	}
    	}
		swap(arr[i], arr[high]);
    	return i;
	}

    void sapxepphaiphanloai() {
    	auto cmp = [](const nhahang& a, const nhahang& b) {
        	return a.phanloai() < b.phanloai();
   		 };
    	quicksort(danhsach, 0, danhsach.size() - 1, cmp); 
    	cout << "Da sap xep danh sach nha hang theo phan loai." << endl;
    	hienthidanhsach();
	}
	// Ghi danh sach nha hang vao file
    void ghinhahang() {
        ofstream file("nhahang2.txt");
        file << "Phan loai        | Ten nha hang          | Chu so huu            | Danh gia\n";
        file << "---------------------------------------------------------------------------\n";

        for (const auto& nh : danhsach) {
            string phanloai = nh.phanloai();
            string ten = nh.getten();
            string chusohuu = nh.getchusohuu();
            double danhgia = nh.getdanhgia();

            file << phanloai << string(15 - phanloai.length(), ' ')
                 << "  | " << ten << string(20 - ten.length(), ' ')
                 << "  | " << chusohuu << string(20 - chusohuu.length(), ' ')
                 << "  | " << danhgia << "\n";
        }

        file.close();
        cout << "Da ghi danh sach nha hang vao file nhahang2.txt." << endl;
    }
};

// Lop app de quan ly
class app {
private:
    danhsachnhahang dsNhaHang;
	bool data;
public:
    void menu() {
        int choice;
        string input;

        do {
            cout << "\n--- MENU QUAN LY NHA HANG ---\n";
            cout << "1. Nhap danh sach nha hang\n";
            cout << "2. Hien thi danh sach nha hang\n";
            cout << "3. Hien thi nha hang co doanh thu cao nhat va thap nhat\n";
            cout << "4. Tim nha hang theo ten\n";
            cout << "5. Sap xep danh sach nha hang theo doanh thu\n";
            cout << "6. Sap xep danh sach nha hang theo phan loai\n";
            cout << "7. Ghi danh sach nha hang sang trong vao file\n";
            cout << "0. Thoat\n";
            cout << "Nhap lua chon: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    dsNhaHang.nhapdanhsach();
                    data = true; 
                    break;
                case 2:
                    if (!data) {
                        cout << "Can phai hoan thanh buoc 1!" << endl;
                    } else {
                        dsNhaHang.hienthidanhsach();
                    }
                    break;
                case 3:
                    if (!data) {
                        cout << "Can phai hoan thanh buoc 1!" << endl;
                    } else {
                        dsNhaHang.hienthidoanhthumaxmin();
                    }
                    break;
                case 4:
                    if (!data) {
                        cout << "Can phai hoan thanh buoc 1!" << endl;
                    } else {
                        cout << "Nhap ten nha hang can tim: ";
                        cin.ignore();
                        getline(cin, input);
                        dsNhaHang.timnhahangtheoten(input);
                    }
                    break;
                case 5:
                    if (!data) {
                        cout << "Can phai hoan thanh buoc 1!" << endl;
                    } else {
                        dsNhaHang.sapxepphaidoanhthu();
                    }
                    break;
                case 6:
                    if (!data) {
                        cout << "Can phai hoan thanh buoc 1!" << endl;
                    } else {
                        dsNhaHang.sapxepphaiphanloai();
                    }
                    break;
                case 7:
                    if (!data) {
                        cout << "Can phai hoan thanh buoc 1!" << endl;
                    } else {
                        dsNhaHang.ghinhahang();
                    }
                    break;
                case 0:
                    cout << "Thoat chuong trinh." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long chon lai." << endl;
            }
        } while (choice != 0);
    }
};

	// Ham main
int main() {
    app myApp;
    myApp.menu();
    return 0;
}
