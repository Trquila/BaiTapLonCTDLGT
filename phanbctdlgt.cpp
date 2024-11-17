#include <iostream>
#include <vector>
using namespace std;

struct Nut {
    int gia_tri;
    Nut* trai, *phai, *cha;
    Nut(int x) : gia_tri(x), trai(nullptr), phai(nullptr), cha(nullptr) {}
};
    
class CayNhiPhan {

private:
    Nut* goc;
	
public:
    
	CayNhiPhan() : goc(nullptr) {}
	
    // Ham tao cay tu mang
    Nut* tao_cay(const vector<int>& nodes, int i, Nut* cha = nullptr) {
        if (i >= nodes.size() || nodes[i] == -1) return nullptr;
        Nut* node = new Nut(nodes[i]);
        node->cha = cha;
        node->trai = tao_cay(nodes, 2 * i + 1, node);
        node->phai = tao_cay(nodes, 2 * i + 2, node);
        return node;
    }

    // Ham khoi tao cay
    void tao_cay(const vector<int>& nodes) {
        goc = tao_cay(nodes, 0);
    }

    // Ham kiem tra xem dau thu 2 co the thang hay khong
    bool kiem_tra_thang(int x, int y) {
        vector<bool> da_to_nuoc(1000, false); // Mang luu trang thai cac nut da to
        vector<Nut*> to_dau_thu_1, to_dau_thu_2; // Danh sach cua tung dau thu
        int so_nut_dau_thu_1 = 1, so_nut_dau_thu_2 = 1; // So nut cua tung dau thu

        // To mau cho cac nut ban dau
        Nut* nut_dau_thu_1 = tim_nut(x);
        Nut* nut_dau_thu_2 = tim_nut(y);
        da_to_nuoc[nut_dau_thu_1->gia_tri] = true;
        da_to_nuoc[nut_dau_thu_2->gia_tri] = true;

        to_dau_thu_1.push_back(nut_dau_thu_1);
        to_dau_thu_2.push_back(nut_dau_thu_2);

        // Choi theo luat
        while (!to_dau_thu_1.empty() || !to_dau_thu_2.empty()) {
            // Dau thu 1
            if (!to_dau_thu_1.empty()) {
                Nut* current = to_dau_thu_1.back();
                to_dau_thu_1.pop_back();

                // To cac nut lan can
                if (current->trai && !da_to_nuoc[current->trai->gia_tri]) {
                    da_to_nuoc[current->trai->gia_tri] = true;
                    to_dau_thu_1.push_back(current->trai);
                    so_nut_dau_thu_1++;
                }
                if (current->phai && !da_to_nuoc[current->phai->gia_tri]) {
                    da_to_nuoc[current->phai->gia_tri] = true;
                    to_dau_thu_1.push_back(current->phai);
                    so_nut_dau_thu_1++;
                }
                if (current->cha && !da_to_nuoc[current->cha->gia_tri]) {
                    da_to_nuoc[current->cha->gia_tri] = true;
                    to_dau_thu_1.push_back(current->cha);
                    so_nut_dau_thu_1++;
                }
            }

            // Dau thu 2
            if (!to_dau_thu_2.empty()) {
                Nut* current = to_dau_thu_2.back();
                to_dau_thu_2.pop_back();

                // To cac nut lan can
                if (current->trai && !da_to_nuoc[current->trai->gia_tri]) {
                    da_to_nuoc[current->trai->gia_tri] = true;
                    to_dau_thu_2.push_back(current->trai);
                    so_nut_dau_thu_2++;
                }
                if (current->phai && !da_to_nuoc[current->phai->gia_tri]) {
                    da_to_nuoc[current->phai->gia_tri] = true;
                    to_dau_thu_2.push_back(current->phai);
                    so_nut_dau_thu_2++;
                }
                if (current->cha && !da_to_nuoc[current->cha->gia_tri]) {
                    da_to_nuoc[current->cha->gia_tri] = true;
                    to_dau_thu_2.push_back(current->cha);
                    so_nut_dau_thu_2++;
                }
            }
        }

        // Kiem tra nguoi thang
        return so_nut_dau_thu_2 > so_nut_dau_thu_1;
    }
    
    // Ham tim nut theo gia tri
	Nut* tim_nut(int gia_tri) {
        return tim_nut(goc, gia_tri);
    }

    Nut* tim_nut(Nut* node, int gia_tri) {
        if (!node) return nullptr;
        if (node->gia_tri == gia_tri) return node;
        Nut* left = tim_nut(node->trai, gia_tri);
        if (left) return left;
        return tim_nut(node->phai, gia_tri);
    }
};

int main() {
    vector<int> nodes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Cay nhi phan
    CayNhiPhan cay;
    cay.tao_cay(nodes); 

    int x, y;
    cout << "Nhap gia tri cua nut ma dau thu 1 (x): ";
    cin >> x;
    cout << "Nhap gia tri cua nut ma dau thu 2 (y): ";
    cin >> y;

    // Kiem tra dau thu 2 co the thang khong
    cout << (cay.kiem_tra_thang(x, y) ? "True" : "False") << endl;

    return 0;
}

