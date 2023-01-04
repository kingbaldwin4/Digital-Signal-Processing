#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
using namespace std;
void ai_ortalama_sapma(int dizi[],int size);
void ai_standart_sapma(int dizi[],int size);
double standart_sapma(int dizi[],int size);
double ortalama_sapma(int dizi[],int size);
int main(){
srand(time(NULL));
int not_sayisi; //veri kumesindeki eleman sayisi
int temp; //dosyadan cekecegimiz verileri tutan eleman
int num=0; //dosyadan veri cekmek icin kullandigim while dongusundeki dongu degiskeni
int ran_notlar; //dosyaya yazilacak notlari tutan degisken
not_sayisi=40+rand()%11;
int *notlar; //dosyadan cekecegimiz notlari tutan ve fonksiyonlara yollayacagimiz dizi(dinamik bellek yontemiyle olusturdum)
notlar=new int[not_sayisi];
for(int z=0;z<not_sayisi;z++){
    notlar[z]=0;
}
ofstream outfile;
outfile.open("notlar.txt");
for(int q=0;q<not_sayisi;q++){
ran_notlar=1+rand()%100;
outfile<<ran_notlar<<"\n";
}
outfile.close();
ifstream infile("notlar.txt");
while ( num< notlar[not_sayisi] && infile >> temp){
				notlar[num++] = temp;
}
ai_standart_sapma(notlar,not_sayisi);
cout<<endl;
cout<<endl;
ai_ortalama_sapma(notlar,not_sayisi);
cout<<"\n"<<"Tum serinin standart sapmasi: "<<standart_sapma(notlar,not_sayisi)<<endl;
cout<<"Tum serinin ortalama sapmasi: "<<ortalama_sapma(notlar,not_sayisi);
delete [] notlar;
infile.close();
return 0;
}
void ai_standart_sapma(int dizi[],int size){
int N=0; //adim sayisini tutan degisken
double sum_squares=0.0; //dizi elemanlarinin kareleri toplami
double seri_toplam=0.0; //dizi elemanlari toplami
double ortalama=0.0; //veri kumesi ortalamasi
double varyans;
double std_sapma;
cout<<"Akan istatistikte standart sapma ve ortalama sapma hesaplari:"<<endl;
for(int j=0;j<size;j++){
    N=N+1;
    seri_toplam=seri_toplam+dizi[j];
    sum_squares=sum_squares+pow(dizi[j],2);
    ortalama=seri_toplam/N;
    if(N==1){
        std_sapma=0;
    }else{
    varyans=fabs((sum_squares-(pow(seri_toplam,2)/N))/(N-1));
    std_sapma=pow(varyans,0.5);
cout<<j+1<<" elemanli veri kumesi icin standart sapma ve veri kumesinin anlik ortalama degeri sirasiyla "<<std_sapma<<"   ve    "<<ortalama<<endl;
}
}
}
void ai_ortalama_sapma(int dizi[],int size){
int M=0; //adim sayisini tutan degisken
double ort_sapma;
double ortalama; //veri kumesi ortalamasi
cout<<"Akan istatistikte ortalama sapma hesaplari:"<<endl;
for(int p=0;p<size;p++){
        double toplam=0.0;//ortalamayi bulmak icin(dizi elemanlari toplami)
        double ort_toplam=0.0; //ortalama sapma formulundeki seri toplamini tutan degisken(karismasin diye basina ortalama sapmanin "ort" kelimesini ekledim)
         M=M+1;
    for(int f=0;f<=p;f++){
    toplam+=dizi[f];
}ortalama=toplam/M;
for(int y=0;y<=p;y++){
    ort_toplam=ort_toplam+abs(dizi[y]-ortalama);
}ort_sapma=ort_toplam/M;
cout<<p+1<<" elemanli veri kumesi icin ortalama sapma "<<ort_sapma<<endl;
}
}
//Klasik standart sapmayi bulan fonksiyonumuz
double standart_sapma(int dizi[],int size){
double toplam1=0.0; //ortalamayi bulmak icin kullandim(dizinin elemanlari toplami)
double toplam2=0.0; //standart sapmadaki toplam sembolu icin kullandim((xi-u)^2 lerin toplamini tutuyor)
double enson_varyans;
double enson_std_sapma;
double average2; //dizi ortalamasi
for(int p=0;p<size;p++){
    toplam1+=dizi[p];
}
average2=toplam1/size;
if(size<2){
    throw invalid_argument("standart sapma hesabi icin en az 2 elemanli bir dizi gerekmektedir!");
}else{
for(int j=0;j<size;j++){
    toplam2=toplam2+(pow((dizi[j]-average2),2));
}
enson_varyans=toplam2/(size-1);
enson_std_sapma=pow(enson_varyans,0.5);
}
return enson_std_sapma;
}
//Klasik ortalama sapmayi bulan fonksiyonumuz
double ortalama_sapma(int dizi[],int size){
double toplam3=0.0; //ortalamayi bulmak icin kullandim(dizi elemanlari toplami)
double toplam4=0.0; //ortalama sapmadaki toplam sembolu icin kullandim((xi-u) lerin toplamini tutuyor)
double enson_ort_sapma;
double average3; //dizi ortalamasi
for(int s=0;s<size;s++){
    toplam3+=dizi[s];
}
average3=toplam3/size;
for(int j=0;j<size;j++){
    toplam4=toplam4+fabs((dizi[j]-average3));
}
enson_ort_sapma=toplam4/size;
return enson_ort_sapma;
}
