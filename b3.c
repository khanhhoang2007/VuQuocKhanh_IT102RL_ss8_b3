#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    struct UserAccount accounts[100];
    struct UserAccount temp;
    int n, i, j, pass;
    int device_limit;
    long long mrr_before = 0;
    long long mrr_after = 0;
    long long difference;

    /* Nhap so luong tai khoan */
    do {
        printf("Nhap so luong tai khoan (1-100): ");
        scanf("%d", &n);

        if (n < 1 || n > 100) {
            printf("So luong khong hop le!\n");
        }
    } while (n < 1 || n > 100);

    /* Nhap du lieu va tinh MRR truoc kiem toan */
    for (i = 0; i < n; i++) {
        printf("\nTai khoan thu %d:\n", i + 1);

        printf("Ma tai khoan: ");
        scanf("%d", &accounts[i].account_id);

        do {
            printf("Loai goi (0-Free, 1-Standard, 2-Premium): ");
            scanf("%d", &accounts[i].plan_type);

            if (accounts[i].plan_type < 0 ||
                accounts[i].plan_type > 2) {
                printf("Loai goi khong hop le!\n");
            }
        } while (accounts[i].plan_type < 0 ||
                 accounts[i].plan_type > 2);

        printf("Phi hang thang ban dau: ");
        scanf("%d", &accounts[i].monthly_fee);

        printf("So ngay con lai: ");
        scanf("%d", &accounts[i].remaining_days);

        printf("So thiet bi dang ket noi: ");
        scanf("%d", &accounts[i].active_devices);

        /* Ghi nhan MRR truoc khi thay doi du lieu */
        mrr_before += accounts[i].monthly_fee;
    }

    /* Buoc 1: Kiem toan va chuan hoa tung tai khoan */
    for (i = 0; i < n; i++) {

        /* Tai khoan het han bi ha cap ve Free */
        if (accounts[i].remaining_days <= 0) {
            accounts[i].plan_type = 0;
            accounts[i].monthly_fee = 0;
        } else {
            /* Chuan hoa phi theo loai goi */
            if (accounts[i].plan_type == 0) {
                accounts[i].monthly_fee = 0;
            } else if (accounts[i].plan_type == 1) {
                accounts[i].monthly_fee = 120000;
            } else {
                accounts[i].monthly_fee = 300000;
            }
        }

        /* Du lieu so thiet bi khong hop le */
        if (accounts[i].active_devices <= 0) {
            accounts[i].active_devices = 1;
        }

        /* Xac dinh gioi han thiet bi theo goi */
        if (accounts[i].plan_type == 0) {
            device_limit = 1;
        } else if (accounts[i].plan_type == 1) {
            device_limit = 2;
        } else {
            device_limit = 5;
        }

        /* Cat giam so thiet bi neu vuot gioi han */
        if (accounts[i].active_devices > device_limit) {
            accounts[i].active_devices = device_limit;
        }

        /* Tinh MRR sau kiem toan */
        mrr_after += accounts[i].monthly_fee;
    }

    /* Buoc 2: Bubble Sort on dinh
       - Goi tra phi dung truoc goi Free.
       - Trong nhom tra phi, phi giam dan.
       - Chi doi cho khi thu tu sai nghiem ngat,
         nen cac tai khoan bang phi giu nguyen thu tu. */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            pass = 0;

            if (accounts[j].plan_type == 0 &&
                accounts[j + 1].plan_type > 0) {
                pass = 1;
            } else if (accounts[j].plan_type > 0 &&
                       accounts[j + 1].plan_type > 0 &&
                       accounts[j].monthly_fee <
                       accounts[j + 1].monthly_fee) {
                pass = 1;
            }

            if (pass == 1) {
                temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }

    /* Buoc 3: In bao cao */
    difference = mrr_after - mrr_before;

    printf("\n========== BAO CAO KIEM TOAN ==========\n");
    printf("%-12s %-10s %-15s %-15s %-15s\n",
           "Ma TK", "Ma goi", "Phi hang thang",
           "Ngay con lai", "So thiet bi");

    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-12d %-10d %-15d %-15d %-15d\n",
               accounts[i].account_id,
               accounts[i].plan_type,
               accounts[i].monthly_fee,
               accounts[i].remaining_days,
               accounts[i].active_devices);
    }

    printf("---------------------------------------------------------------------\n");
    printf("MRR truoc kiem toan: %lld VND\n", mrr_before);
    printf("MRR sau kiem toan:   %lld VND\n", mrr_after);
    printf("Chenh lech MRR:      %lld VND\n", difference);

    if (difference < 0) {
        printf("Doanh thu giam:      %lld VND\n", -difference);
    } else if (difference > 0) {
        printf("Doanh thu tang:      %lld VND\n", difference);
    } else {
        printf("Doanh thu khong thay doi.\n");
    }

    return 0;
}

