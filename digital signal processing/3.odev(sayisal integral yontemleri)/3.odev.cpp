#include <iostream>
#include <math.h>
#include <fstream>
#define pi 3.14159265358979323846
#define exp 2.71828182845904523536
using namespace std;
double cdf(double numb); //cdf fonksiyonumuz
double simpson_13(double (*f)(double),double up,double down,double *y,int n); //simpson 1/3 fonksiyonu
double simpson_38(double (*f)(double),double up,double down,double *z,int n); //simpson 3/8 fonksiyonu
double trapezoidal(double (*f)(double),double up,double down,double *q,int n); //trapezoidal fonksiyonu NOT:trapezoidal=(left riemann+right riemann)/2
double boole(double (*f)(double),double up,double down,double *t,int n); //boole fonksiyonu
double l_rie(double (*f)(double),double up,double down,double *p,int n); //left riemann fonksiyonu
double r_rie(double (*f)(double),double up,double down,double *r,int n); //right riemann fonksiyonu
double m_rie(double (*f)(double),double up,double down,double *o,int n); //middle riemann fonksiyonu
int main()
{
    int step; //parca sayisi
    cout<<"alani kac parcaya ayirmak istiyorsunuz?"<<endl;
    cin>>step;
    double down; //integral alt sinir
    double up; //integral ust sinir
    cout<<"integralin ust sinir degerini giriniz:"<<endl;
    cin>>up;
    cout<<"\nintegralin alt sinir degerini giriniz:"<<endl;
    cin>>down;
    int choose; //islem turunu secmek icin
    cout<<"simpson 1/3 yontemi icin 1"<<endl;
    cout<<"simpson 3/8 yontemi icin 2"<<endl;
    cout<<"trapezoidal yontemi icin 3"<<endl;
    cout<<"boole yontemi icin 4"<<endl;
    cout<<"left riemann yontemi icin 5"<<endl;
    cout<<"right riemann yontemi icin 6"<<endl;
    cout<<"middle rieman (midpoint) yontemi icin 7"<<endl;
    cout<<"programdan cikmak icin -1"<<endl;
    cout<<"giriniz"<<endl;
    while(choose!=-1){
        cout<<"seciminizi yapiniz:"<<endl;
        cin>>choose;
    switch(choose){
case 1:
    {
    double y[step+1];
    double a=simpson_13(cdf,up,down,y,step);
    cout<<"simpson 1/3 yontemine gore integral sonucu: "<<a<<endl;
    }
    break;
case 2:
    {
    double z[step+1];
    double b=simpson_38(cdf,up,down,z,step);
    cout<<"simpson 3/8 yontemine gore integral sonucu: "<<b<<endl;
    }
    break;
case 3:
    {
    double q[step+1];
    double c=trapezoidal(cdf,up,down,q,step);
    cout<<"trapezoidal yontemine gore integral sonucu: "<<c<<endl;
    }
    break;
case 4:
    {
    double t[step+1];
    double d=boole(cdf,up,down,t,step);
    cout<<"boole yontemine gore integral sonucu: "<<d<<endl;
    }
    break;
case 5:
    {
    double p[step];
    double e=l_rie(cdf,up,down,p,step);
    cout<<"left riemann toplami yontemine gore integral sonucu: "<<e<<endl;
    }
    break;
case 6:
    {
    double r[step];
    double f=r_rie(cdf,up,down,r,step);
    cout<<"right riemann toplami yontemine gore integral sonucu: "<<f<<endl;
    }
    break;
case 7:
    {
    double o[step];
    double g=m_rie(cdf,up,down,o,step);
    cout<<"middle riemann(midpoint) yontemine gore integral sonucu: "<<g<<endl;
}
    break;
case -1:
    return 0;
    break;
default:
    cout<<"yanlis bir deger girdiniz lutfen tekrar deneyin!"<<endl;
    }
    }
    return 0;
}

double simpson_13(double (*f)(double),double up,double down,double *y,int n){
double h;
double sum=0.0;
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
y[0]=(*f)(down);
y[n]=(*f)(up);
for(int i=1;i<n;i++){
    y[i]=(*f)(down+i*h);
}

for(int j=1;j<n;j++){
    if(j%2==1){
        y[j]=y[j]*4;
    }
    if(j%2==0){
        y[j]=y[j]*2;
    }
}
for(int k=0;k<=n;k++){
    sum+=y[k];
}
ofstream sonuclar_13;
sonuclar_13.open("sonuclar_13.txt");
for(int l=0;l<=n;l++){
sonuclar_13<<"y"<<l<<" = "<<y[l]<<"\n";
}
sonuclar_13<<"integral sonucu: "<<(h/3)*sum;
sonuclar_13.close();
return (h/3)*sum;
}
double simpson_38(double (*f)(double),double up,double down,double *z,int n){
double h;
double sum2=0.0;
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
z[0]=(*f)(down);
z[n]=(*f)(up);
for(int i=1;i<n;i++){
    z[i]=(*f)(down+i*h);
}
for(int j=1;j<n;j++){
    if(j%3!=0){
        z[j]=z[j]*3;
    }
    if(j%3==0){
        z[j]=z[j]*2;
    }
}
for(int k=0;k<=n;k++){
    sum2+=z[k];
}
ofstream sonuclar_38;
sonuclar_38.open("sonuclar_38.txt");
for(int l=0;l<=n;l++){
sonuclar_38<<"y"<<l<<" = "<<z[l]<<"\n";
}
sonuclar_38<<"integral sonucu: "<<(0.375)*h*sum2;
sonuclar_38.close();
return (0.375)*h*sum2;
}
double trapezoidal(double (*f)(double),double up,double down,double *q,int n){
double h;
double sum3=0.0;
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
q[0]=(*f)(down);
q[n]=(*f)(up);
for(int i=1;i<n;i++){
    q[i]=(*f)(down+i*h);
}
for(int j=1;j<n;j++){
        q[j]=q[j]*2;
}
for(int k=0;k<=n;k++){
    sum3+=q[k];
}
ofstream sonuclar_tr;
sonuclar_tr.open("sonuclar_tr.txt");
for(int l=0;l<=n;l++){
sonuclar_tr<<"y"<<l<<" = "<<q[l]<<"\n";
}
sonuclar_tr<<"integral sonucu: "<<(0.5)*h*sum3;
sonuclar_tr.close();
return (0.5)*h*sum3;
}
double boole(double (*f)(double),double up,double down,double *t,int n){
double h;
double sum4=0.0;
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
t[0]=7*((*f)(down));
t[n]=(*f)(up);
for(int i=1;i<n;i++){
    t[i]=(*f)(down+i*h);
}
for(int j=1;j<n;j++){
    if(j%2==1){
        t[j]=t[j]*32;
    }
    if(j%4==2){
        t[j]=t[j]*12;
    }
    if(j%4==0){
        t[j]=t[j]*14;
    }
}
for(int k=0;k<=n;k++){
    sum4+=t[k];
}
ofstream sonuclar_boo;
sonuclar_boo.open("sonuclar_boo.txt");
for(int l=0;l<=n;l++){
    sonuclar_boo<<"y"<<l<<" = "<<t[l]<<"\n";
}
sonuclar_boo<<"integral sonucu: "<<(2/45)*h*sum4;
sonuclar_boo.close();
return 2*h/45*sum4;
}
double l_rie(double (*f)(double),double up,double down,double *p,int n){
    double h;
double sum5=0.0;
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
for(int i=0;i<n;i++){
    p[i]=(*f)(down+i*h);
}
for(int k=0;k<n;k++){
    sum5+=p[k];
}
ofstream sonuclar_lrie;
sonuclar_lrie.open("sonuclar_left_riemann.txt");
for(int l=0;l<n;l++){
    sonuclar_lrie<<"y"<<l<<" = "<<p[l]<<"\n";
}
sonuclar_lrie<<"integral sonucu: "<<h*sum5;
sonuclar_lrie.close();
return h*sum5;
}
double r_rie(double (*f)(double),double up,double down,double *r,int n){
    double h;
double sum6=0.0;
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
for(int i=1;i<=n;i++){
    r[i-1]=(*f)(down+i*h);
}
for(int k=1;k<=n;k++){
    sum6+=r[k-1];
}
ofstream sonuclar_rrie;
sonuclar_rrie.open("sonuclar_right_riemann.txt");
for(int l=0;l<n;l++){
    sonuclar_rrie<<"y"<<l<<" = "<<r[l]<<"\n";
}
sonuclar_rrie<<"integral sonucu: "<<h*sum6;
sonuclar_rrie.close();
return h*sum6;
}
double m_rie(double (*f)(double),double up,double down,double *o,int n){
double h;
double sum7=0.0;
double fix_mrie_arr[n]; //bunu acma nedenin y0 y1 gibi seylerin yerine y1/2  y3/2 gibi argumanlarin olmasidir.Cunku biz y0 y1 y2 gibi argumanlari kullanarak y1/2  y3/2 gibi argumanlari elde ediyoruz!
if((n%2)==0&&n>0){
    h=(up-down)/n;
}else{
throw invalid_argument("n 0'dan buyuk cift sayi olmadigi icin islem yapilamaz");
}
for(int i=0;i<n;i++){
    o[i]=(*f)(down+i*h);
}
for(int j=0;j<n;j++){
    fix_mrie_arr[j]=(o[j]+o[j+1])/2;
}
for(int k=0;k<n;k++){
    sum7+=fix_mrie_arr[k];
}
ofstream sonuclar_mrie;
sonuclar_mrie.open("sonuclar_middle_riemann.txt");
for(int l=0;l<n;l++){
    sonuclar_mrie<<"y"<<l+1<<"/2"<<" = "<<fix_mrie_arr[l]<<"\n";
}
sonuclar_mrie<<"integral sonucu: "<<h*sum7;
sonuclar_mrie.close();
return h*sum7;
}
double cdf(double numb){
    double numb_fix=(pow(numb,2)*(-0.5)); //-(x^2)/2
    double exp_fix=pow(exp,numb_fix); //usttekinin e uzeri alinmis hali
    double fix_pi=1/pow(2*pi,0.5);// 1/(2pi)^0.5  yani 1/kok2pi
return fix_pi*exp_fix;
}
