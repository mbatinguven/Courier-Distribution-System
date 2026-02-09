#include <iostream>
#include<iomanip>                                       
#include <fstream>                                      //Geliştirici:Mustafa Batın GÜVEN
#include <cstdlib>                                      //Öğrenci No:b231200048
#include <ctime>                                        //Ödev no:1
#include <string>                                       //Ödev Konusu:Kurye Dağıtımı
#include <windows.h>

using namespace std;

struct Musteri {
public:
    Musteri();
    ~Musteri();


    void siparisDosyayaYaz(ofstream& dosya);
    static int siradakiMusteriNo;
    int musteriNo;
    float siparisTutari;
    Musteri* adres;
};

int Musteri::siradakiMusteriNo = 0;

Musteri::Musteri() {
    this->musteriNo = siradakiMusteriNo++;
    siparisTutari = (rand() % 901) + 100;
    adres = this;
}

Musteri::~Musteri() {}

void Musteri::siparisDosyayaYaz(ofstream& dosya) {
    if (dosya.is_open()) {
        dosya << musteriNo << "\t\t";
        dosya << siparisTutari << "\t\t";
        dosya << adres << endl;
    }
    else {
        cout << "Dosya acilamadi!" << endl;
    }
}

int main() {

    srand(time(0));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int musteriSayisi = 10;


    Musteri* musteriler = new Musteri[musteriSayisi];

    ofstream dosya("siparisler.txt");
    dosya << "\t Siparis Listesi " << endl;
    dosya << "-----------------------------" << endl;
    dosya << "Musteri no \t Tutar \t Adres" << endl;


    for (int i = 0; i < musteriSayisi; ++i) {
        musteriler[i].siparisDosyayaYaz(dosya);
    }


    for (int i = musteriSayisi - 1; i > 0; --i) {
        int r = rand() % (i + 1);
        swap(musteriler[i], musteriler[r]);
    }

    dosya << "-----------------------------" << endl;
    dosya << "\t Dagitim Rotasi " << endl;
    dosya << "-----------------------------" << endl;


    for (int i = 0; i < musteriSayisi; ++i) {
        musteriler[i].siparisDosyayaYaz(dosya);
    }
    dosya << endl << "-----------------------------" << endl;
    int toplamTutar = 0;
    for (int i = 0; i < 10; i++) {
        toplamTutar += musteriler[i].siparisTutari;
    }
    dosya << "Toplam Tutar : " << toplamTutar;
    auto minCustomer = std::min_element(musteriler, musteriler + musteriSayisi,
        [](const Musteri& a, const Musteri& b) {
            return a.siparisTutari < b.siparisTutari;
        });

    auto maxCustomer = std::max_element(musteriler, musteriler + musteriSayisi,
        [](const Musteri& a, const Musteri& b) {
            return a.siparisTutari < b.siparisTutari;
        });

    cout << "Musteri No \t\t" << "Tutar\t\t" << "Adres" << endl;
    for (int i = 0; i < musteriSayisi; ++i) {
        if (&musteriler[i] == &(*minCustomer)) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        }
        else if (&musteriler[i] == &(*maxCustomer)) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        }
        else {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }

        cout << musteriler[i].musteriNo << "\t\t" << musteriler[i].siparisTutari << "\t\t" << musteriler[i].adres << endl;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "----------------------------" << endl << "Toplam Tutar : " << toplamTutar;
    cout << endl << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << setw(5) << musteriler[i].siparisTutari - musteriler[j].siparisTutari;
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


    delete[] musteriler;
    dosya.close();
    return 0;
}
