#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
double find_average(int *rp,int boyut ); //ortalamayi bulan fonksiyon prototipi
double find_variance(int *rp,int boyut); //varyansi bulan fonksiyon prototipi
void draw_histogram(int *ha,int ha_size); //histogrami cizdiren fonksiyon prototipi
int main() {
    Mat resim=imread("cat.jpg"); //gray-level olmayan resmi açıp pixelleri okuyup matrise yazma islemi
	resize(resim,resim,Size(200,220)); //resim boyutunu ozellestirmek
	cvtColor(resim,resim,COLOR_BGR2GRAY); //resmi gray-level hale cevirmek
	/* asagida bahsettigim fonksiyonsuz kontrol icin gerekli olan degiskenlerdir
	kullanici eger kontrol etmek isterse bu degiskenleri aktif hale getirmelidir!
	int sum_rp_mlt_index=0;
	int sum_rp=0;
	int sum_rp_squares=0;
	double rp_variance_ctrl=0.0;
	double rp_avg_for_ctrl=0.0;
	*/
	int rows=200;
	int columns=220;
	int repeated_size=256;
	int** pixels=new int*[rows]; //200x220'lik matris(piksel degerlerini tutuyor)
	if(rows){
        pixels[0]=new int[rows*columns];
        for(int i=1;i<rows;i++)
            pixels[i]=pixels[0]+i*columns;
	}
	for(int i=0;i<rows;i++){
	for(int j=0;j<columns;j++){
	pixels[i][j]=resim.at<uchar>(i,j); //resmin (i,j) konumundaki pikseline erisim
	}
	}
	int *repeated; //piksel degerlerinin tekrar sayisini tutan 256 elemanli dizi
	repeated=new int[repeated_size];
	for(int a=0;a<repeated_size;a++){ //initialize
        repeated[a]=0;
	}
	int *hist_array=new int[16]; //repeated dizisinin 16'sar olarak gruplanmis halini tutan 16 elemanli dizi(cizim icin kullanilacak)
	for(int g=0;g<16;g++){  //initialize
        hist_array[g]=0;
	}
	unsigned int counter=0;
	int repeated_fixed_sum=0; //bulundugu dongunun icinde ne ise yaradigini yazdim daha iyi anlasilir

	for(int k=0;k<rows;k++){  //piksellerin tekrar yapma kontrolunu saglayan nested-for donguleri
            for(int l=0;l<columns;l++){
                    counter=0;
        for(int m=0;m<rows;m++){
            for(int n=0;n<columns;n++){
                if((pixels[k][l]==pixels[m][n])){
                    counter++;}
            }

        }if(repeated[pixels[k][l]]==0){repeated[pixels[k][l]]=counter;} //burada tekrar sayilarini diziye yaziyor(eger o renk degerinin tekrar durumu daha once kontrol edilmemisse)
	}
}

//bu kısımdan kullanici fonksiyonsuz bir sekilde degerleri buldurup fonksiyondan gelecek degerler ile karsilastirabilsin diye var
//eger degerler ayni cikarsa fonksiyonlar dogrudur demektir!
/*for(int z=0;z<256;z++){
sum_rp+=repeated[z];
}
	for(int w=0;w<256;w++){
            sum_rp_mlt_index+=(repeated[w]*w);
        cout<<repeated[w]<<"\n";
	}cout<<"repetead sum: "<<sum_rp_mlt_index<<endl;
	rp_avg_for_ctrl=(double)sum_rp_mlt_index/(double)sum_rp;
	cout<<"repeated average is: "<<rp_avg_for_ctrl;
for(int f=0;f<256;f++){
    sum_rp_squares+=(pow((f-rp_avg_for_ctrl),2)*repeated[f]);
}
rp_variance_ctrl=((double)sum_rp_squares/(double)(sum_rp-1));
cout<<"repeated variance is: "<<rp_variance_ctrl<<endl;
*/



	//256 adet histogram binimiz var ve cizimi daha kolay olsun diye 16 adet aralik yapacagim yani:(0-15,16-31,32-47,48-63,64-79,80-95,96-111,112-127,128-143,144-159,160-175,176-191,192-207,208-223,224-239,240-255)
    //ornegin 0-15 arasi renk degerlerine sahip piksellerin tekrar sayilarinin toplamini hist_array dizisinin 0.index'inde
    //16-31 arasi renk degerlerine sahip piksellerin tekrar sayilarinin toplamini hist_array dizisinin 1.index'inde(boyle devam ediyor)tutacagim
	//Bunu yapmamin tek sebebi gorsel olarak histogram fazla yer kaplamasin ve okunabilirligi daha rahat olsun.
	//ayrica ortalama bulurken 16'sar araligi tutan diziyi kullanmak hata verecektir dolayisiyla aralik kullanmadan histogramin saf halinin(repeated dizisi) ortalama ve varyans fonksiyonuna gönderilmesi lazimdir!

	for(int b=0;b<repeated_size;b+=16){ //Hist array dizisinin degerlerini aldigi kisim!
            repeated_fixed_sum=0; //gruplanmis eleman degerlerinin toplamini tutan degisken(ornegin 0-15 arasi renklerin tekrar degerlerinin toplamini tutmak gibi)
        for(int c=b;c<16+b;c++){
            repeated_fixed_sum+=repeated[c];
        }hist_array[b/16]=repeated_fixed_sum;
	}
cout<<endl;
cout<<"Piksellerin renk degeri tekrarlarini 16'sar 16'sar  olacak sekilde gruplayip tutan histogram dizimiz:"<<endl;
	for(int u=0;u<16;u++){
        cout<<hist_array[u]<<" ";
	}cout<<endl;
cout<<"Piksel degerlerinin ortalamasi: "<<find_average(repeated,repeated_size)<<endl;
cout<<"Piksel degerlerinin varyansi: "<<find_variance(repeated,repeated_size)<<endl;
cout<<"Piksel degerlerinin standart sapmasi: "<<pow(find_variance(repeated,repeated_size),0.5)<<endl;
cout<<"Histogram cizimi(iyi bir gorsellik icin yanlamasina cizdirdim)"<<endl;
draw_histogram(hist_array,16);


if (rows) delete [] pixels[0]; //pixels matrisinin yikimi
delete [] pixels;


delete [] repeated; //repeated dizisinin yikimi


delete [] hist_array; //hist_array dizisinin yikimi





	imshow("Resim",resim); //gray-level ve boyutu ayarlanmis resmi gosteren fonksiyon
	waitKey(0);
	return 0;
}
double find_average(int *rp,int boyut){ //ortalama fonksiyonu govdesi
    int rp_sum1=0; //repeated dizisi elemanlarinin toplamini tutuyor
    int rp_mlt_index_sum1=0; //repeated dizisi elemanlarinin,indexleriyle olan carpimlarinin toplamini tutuyor(i*Hi)
    double average=0.0; //ortalamamiz
for(int k=0;k<boyut;k++){
    rp_mlt_index_sum1+=((rp[k])*k);
}
for(int j=0;j<boyut;j++){
    rp_sum1+=rp[j]; //histogramdaki elemanlar toplami  ornek sayisini veriyor
}
average=(double)rp_mlt_index_sum1/(double)rp_sum1;
return average;
}
double find_variance(int *rp,int boyut){ //varyans fonksiyonu govdesi
    int rp_sum2=0; //repeated dizisi elemanlarinin toplamini tutuyor
    int rp_mlt_index_sum2=0; //repeated dizisi elemanlarinin,indexleriyle olan carpimlarinin toplamini tutuyor(i*Hi)
    double variance=0.0;
    int square_sum=0; //((index-ortalama)^2)*Hi lerin toplamini tutuyor
    double average=0.0;
    for(int k=0;k<boyut;k++){
            rp_mlt_index_sum2+=(rp[k]*k);
    }
for(int j=0;j<boyut;j++){
    rp_sum2+=rp[j];
}
average=(double)rp_mlt_index_sum2/(double)rp_sum2;
for(int g=0;g<boyut;g++){
    square_sum+=(pow((g-average),2)*rp[g]);
}

variance=(double)square_sum/(double)(rp_sum2-1);
return variance;
}
void draw_histogram(int *ha,int ha_size){ //histogram cizdiren fonksiyonun govdesi
cout<<"\nHer yildiz 100 degerinde olacak sekilde:"<<endl;
for(int i=0;i<16;i++){
        int k=i*16;
        cout<<k<<"-"<<k+15<<":"; //araliklar belirtiliyor
        for(int j=0;j<(ha[i]/100);j++){ //asil yildiz sayisinin yuzde 1'i
    cout<<"*";
}cout<<"  ("<<(ha[i]/100)<<" adet yildiz)"; //kac tane yildiz oldugu belli olsun diye(tek tek saymanizi istemedim :))
cout<<endl;
}
}
