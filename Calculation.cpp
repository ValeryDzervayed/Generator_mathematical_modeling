//---------------------------------------------------------------------------
//
// Программа 'DzmG1' 2008 г.
// Расчет переходного процесса в синхронном генераторе
// при нарушении связи с энергосстемой и симметричном набросе
// (сбросе) нагрузки на основе численного решения
// дифференциальных уравнений методом Рунге-Кутта
// четвеотого порядка

// ОБОЗНАЧЕНИЯ ПЕРЕМЕННЫХ В ПРОГРАММЕ:

// ПАРАМЕТРЫ СИСТЕМЫ ДИФФЕРЕНЦИАЛЬНЫХ УРАВНЕНИЙ
// NUR - количество фифференциальных уравнений в системе
// INTWR - интервал печати. Количество шагов изменения
// независимой переменной T, которые пропускаются при выводе
// результатов в файл-отчет.
// T0 - начальное значение независимой переменной T, c
// TKON - конечное значение независимой переменной T, c
// H - шаг изменения независимой переменной Т, c

// T - время (независимая переменная), с
// TAU - время относительное (синхронное), отн.ед.
// H1 - шаг изменения независимой переменной TAU, отн.ед.

// КАТАЛОЖНЫЕ ДАННЫЕ ГЕНЕРАТОРА, ЗАДАВАЕМЫЕ В ИСХОДНЫХ ДАННЫХ:
// Sn - номинальная мощность генератора, ВА
// Un - номинальное напряжение генератора, В
// Ufn - номинальное напряжение возбуждения генератора, В
// Ifxx - ток возбуждения холостого хода, А
// Ifn - ток возбуждения номинальный, А
// Jrt - момент инерции вращающихся частей (генератор и первич. двиг.), кг.м.м
// Rs - активное сопротивление обмотки статора, Ом
// Rf - активное сопротивление обмотки ротора, Ом
// Xd11 - сверхпереходное реактивное сопротивление по продольной оси, отн.ед.
// Xd1 - переходное реактивное сопротивление по продольной оси, отн.ед.
// Xd - полное синхронное реактивное сопротивление по продольной оси, отн.ед.
// X2 - реактивное сопротивление обратного следования фаз, отн.ед.
// Td0 - постоянная времени обмотки возбуждения при разомкнутом статоре, с
// Td11 - постоянная времени успокоительной обмотки (постоянная времени
//        сверхпереходных токов), с

// ПАРАМЕТРЫ НАГРУЗКИ ГЕНЕРАТОРА В ДОАВАРИЙНОМ РЕЖИМЕ, ЗАДАВАЕМЫЕ В
// ИСХОДНЫХ ДАННЫХ
// Snagr - мощность нагрузки генератора, ВА
// CosFI - коэффициент мощности нагрузки
// GAM - электрический угол пространственного положения ротора
// в начальный момент расчета относительно оси фазы А, рад

// ПАРАМЕТРЫ ГЕНЕРАТОРА, ВЫЧИСЛЯЕМЫЕ В ПРОГРАММЕ:
// Xasig - реактивное сопротивление рассеяния обмотки статора, отн.ед.
// Xad - реактивное сопротивление взаимоиндукции по продольной оси, отн.ед.
// Xaq - реактивное сопротивление взаимоиндукции по поперечной оси, отн.ед.
// Xq - полное реактивное сопротивление по поперечной оси, отн.ед.
// Xfsig - реактивное сопротивление рассеяния обмотки возбуждения, отн.ед.
// Xf - полное реактивное сопр. обмотки возб. при разомкнутом статоре, отн.ед.
// Xusigd - реактивное сопротивление успокоит. обмотки по продольной оси, отн.ед.
// Xud - полное реактивное сопр. успокоит. обмотки по продольной оси, отн.ед.
// Xq11 - сверхпереходное реакт. сопр. успокоит. обмотки по продольной оси, отн.ед.
// Xusigq - реактивное сопр. рассеяния успокоит. обм. по поперечной оси, отн.ед.
// Xuq - полное реактивное сопр. успокоит. обмотки по поперечной оси, отн.ед.
// Ibaz - ток базисный, А
// Ubaz - наряжение базисное, В
// Zbaz - сопротивление базисное, Ом
// Rso - активное сопротивление обмотки статора относительное, отн.ед.
// Rfo - активное сопротивление обмотки возбуждения относительное, отн.ед.
// Rudo - активное сопрот. успокоит. обм. по оси d относительное, отн.ед.
// Ruqo - активное сопрот. успокоит. обм. по оси q относительное, отн.ед.
// Ifbaz - ток возбуждения базисный, А
// Hj - постоянная инерции вращающихся частей, с
// SinFI - синус узла нагрузки
// FI - угол нагрузки, pад
// Inagr - ток нагрузки, А
// TETA - угол сдвига между ЭДС и напряжением машины, pад
// Id - ток статора по оси d, отн.ед.
// Iq - ток статора по оси q, отн.ед.
// Ud - напряжение статора по оси d, отн.ед.
// Uq - напряжение статора по оси q, отн.ед.
// Ia - ток фазы А обмотки статора, отн.ед.
// Ib - ток фазы В обмотки статора, отн.ед.
// Ic - ток фазы С обмотки статора, отн.ед.
// Eq - ЭДС обмотки статора, отн.ед.
// PSId - потокосцепление обмотки статора по оси d, отн.ед.
// PSIq - потокосцепление обмотки статора по оси q, отн.ед.
// PSIf - потокосцепление обмотки возбуждения, отн.ед.
// PSIud - потокосцепление успокоит. обмотки по оси d, отн.ед.
// PSIuq - потокосцепление успокоит. обмотки по оси q, отн.ед.
// PSIa - потокосцепление фазы А обмотки статора, отн.ед.
// PSIb - потокосцепление фазы В обмотки статора, отн.ед.
// PSIc - потокосцепление фазы С обмотки статора, отн.ед.
// Mem - момент электромагнитный, отн.ед.
// Mmex - момент механических сил, отн.ед.
// If - ток в обмотке возбуждения, отн.ед.
// Uf - напряжение на обмотке возбуждения, отн.ед.

// dTdz - изменение периода напряжения. (для делительной защиты [мое])
// Tdz - период напряжения на данном этапе расчета
// Udz1 - напряжение на предыдущем этапе расчета
// Udz2 - напряжение на данном этапе расчета
// TdzN - момент времени начала периода
// TdzK - момент времени конца периода
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Calculation.h"
#include "Info.h"
#include <math.h>     // описание sin

#include <fstream.h>  // класс, обеспечивающий ввод и вывод в файл
//#include <iostream.h>  // класс, обеспечивающий ввод и вывод  на экран

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCalculationForm *CalculationForm;

//---------------------------------------------------------------------------
__fastcall TCalculationForm::TCalculationForm(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TCalculationForm::InfoButtonClick(TObject *Sender)
{
InfoForm->Show();
}
//---------------------------------------------------------------------------

int NUR, N, NREZ, INTWR;
float Rso, Rfo, RUdo, Ruqo, Ud, Uq, Uf,
      W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11, W12, W13,
      PSId, PSIq, PSIf, PSIud, PSIuq, PSIa, PSIb, PSIc,
      Id, Iq, If, Iud, Iuq, Ia, Ib, Ic,
      S, GAM, Mmex, Mem, Hj, OMEGA,
      Y[20],Y0[20],
      Ifxx, Ifn, Jrt, Ibaz, Ifbaz, Inagr,
      T0, TKON, H, Sn, Un, Ufn, Rs, Rf, Xd11,
      Xd1, Xd, X2, Td0, Td11, Snagr, CosFI,
      Xq, Xasig, Xad, Xaq, Xfsig, Xf, Xusigd, Xud, Xq11,
      Xusigq, Xuq, Ubaz, Sbaz, Zbaz, Xud11, Rudo, Xuq11,
      SinFI, FI, TETA, Eq,
      H1, HH, TAU, X, T,
      UQ, XF,
      YF[10],F[10],

       // Параметры для расчета делительной защиты
      dTdz, TdzN, TdzK, Tdz1, Tdz2, Udz1, Udz2, Tdz, Tfiksir, Dkol,

      Ua,Ub,Uc,                     
      Znagrd, Znagrq, Kzagr;       
float P[5] = {0.,    0., 0.5, 0.5, 1.};
float Q[5] = {0.,    1., 2.0, 2.0, 1.};

void __fastcall TCalculationForm::CalculationButtonClick(TObject *Sender)
{
 Series1->Clear();   // очистка области диаграммы для Ub
 Series2->Clear();   // очистка области диаграммы для Ib
 ofstream outfile ("Report.rez"); // открытие файла-отчета Report.rez

 // Чтение исходных данных с формы Calculation.dfm

 NUR = 7;
 INTWR = 10;
 T0 = 0;
 Sn = StrToFloat(Sn_Edit->Text);
 Un = StrToFloat(Un_Edit->Text);
// Ufn = StrToFloat(Ufn_Edit->Text);
 Ifxx = StrToFloat(Ifxx_Edit->Text);
 Ifn = StrToFloat(Ifn_Edit->Text);
 Jrt = StrToFloat(Jrt_Edit->Text);
 Rs = StrToFloat(Rs_Edit->Text);
 Rf = StrToFloat(Rf_Edit->Text);
 Xd11 = StrToFloat(Xd11_Edit->Text);
 Xd1 = StrToFloat(Xd1_Edit->Text);
 Xd = StrToFloat(Xd_Edit->Text);
 X2 = StrToFloat(X2_Edit->Text);
 Td0 = StrToFloat(Td0_Edit->Text);
 Td11 = StrToFloat(Td11_Edit->Text);
 Kzagr = StrToFloat(Kzagr_Edit->Text);
 Snagr = StrToFloat(Snagr_Edit->Text);
 CosFI = StrToFloat(CosFI_Edit->Text);
 GAM = StrToFloat(GAM_Edit->Text);
 H = StrToFloat(H_Edit->Text);
 TKON = StrToFloat(TKON_Edit->Text);

 if (Sn<=0||Sn>1000000000) // проверка правильности ввода Sn
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Sn: 1000 0000 ВА";
  return;
  }
 if (Un<=0||Un>30000) // проверка правильности ввода Un
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Un: 400..10000 В";
  return;
  }
 if (Ifxx<=0||Ifxx>5000) // проверка правильности ввода Ifxx
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Ifxx: 100..1000 А";
  return;
  }
 if (Ifn<=0||Ifn>10000) // проверка правильности ввода Ifn
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Ifxx: 200..2000 А";
  return;
  }
 if (Jrt<=0||Jrt>100000) // проверка правильности ввода Jrt
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Jrt: 1..100000 кг.м.м";
  return;
  }
 if (Rs<=0||Rs>1000) // проверка правильности ввода Rs
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Rs: 0.1..1 Ом";
  return;
  }
 if (Rf<=0||Rf>1000) // проверка правильности ввода Rf
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Rf: 0.001..0.1 Ом";
  return;
  }
 if (Xd11<=0||Xd11>1000) // проверка правильности ввода Xd11
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Xd11: 0.1..1";
  return;
  }
 if (Xd1<=0||Xd1>1000) // проверка правильности ввода Xd1
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Xd1: 0.1..1";
  return;
  }
 if (Xd<=0||Xd>1000) // проверка правильности ввода Xd
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Xd: 0.5..5";
  return;
  }
 if (Kzagr<=0||Kzagr>2) // проверка правильности ввода Kzagr
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Kzagr: 0.6..1";
  return;
  }
 if (Snagr<=0||Snagr>500000000) // проверка правильности ввода Snagr
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение Snagr: (0.5..2)Sn";
  return;
  }
 if (CosFI<=0||CosFI>1) // проверка правильности ввода CosFI
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение CosFI: 0.8";
  return;
  }
 if (GAM<=0||GAM>1.57) // проверка правильности ввода GAM
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение GAM: 0...1.57 рад";
  return;
  }
 if (H<=0.0000001||H>0.0001) // проверка правильности ввода H
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение H: 0.00001..0.000001";
  return;
  }
 if (TKON<=0.02||TKON>100) // проверка правильности ввода TKON
  {
  Warning_Label1->Caption = "Ввод исходных данных некорректный";
  Warning_Label2->Caption = "Рекомендуемое значение TKON: 1 с";
  return;
  }

 // Расчет параметров генератора, отсутствующих в каталоге
                                            // вывод для специалистов (необязательный)
 OMEGA=314.15928;                           // outfile<< "OMEGA  "<<OMEGA<<endl;
 Xq=0.9*Xd;                                 // outfile<< "Xq  "<<Xq<<endl;
 Xasig=Xd11-0.025;                          // outfile<< "Xasig  "<<Xasig<<endl;
 Xad=Xd-Xasig;                              // outfile<< "Xad  "<<Xad<<endl;
 Xaq=Xq-Xasig;                              // outfile<< "Xaq  "<<Xaq<<endl;
 Xfsig=Xad*(Xd1-Xasig)/(Xd-Xd1);            // outfile<< "Xfsig  "<<Xfsig<<endl;
 Xf=Xfsig+Xad;                              // outfile<< "Xf "<<Xf<<endl;
 Xusigd=1./(1./(Xd11-Xasig)-1./Xfsig-1./Xad);//outfile<< "Xusigd  "<<Xusigd<<endl;
 Xud=Xusigd+Xad;                            // outfile<< "Xud  "<<Xud<<endl;
 Xq11=X2*X2/Xd11;                           // outfile<< "Xq11  "<<Xq11<<endl;
 Xusigq=Xaq*(Xq11-Xasig)/(Xq-Xq11);         // outfile<< "Xusigq  "<<Xusigq<<endl;
 Xuq=Xaq+Xusigq;                            // outfile<< "Xuq  "<<Xuq<<endl;
 Ibaz=sqrt(2./3.)*Sn/Un;                    // outfile<< "Ibaz  "<<Ibaz<<endl;
 Ubaz=sqrt(2./3.)*Un;                       // outfile<< "Ubaz  "<<Ubaz<<endl;
 Sbaz=1.5*Ubaz*Ibaz;                        // outfile<< "Sbaz  "<<Sbaz<<endl;
 Zbaz=Ubaz/Ibaz;                            // outfile<< "Zbaz  "<<Zbaz<<endl;
 Rso=Rs/Zbaz;                               // outfile<< "Rso  "<<Rso<<endl;
 Rfo=Xf/(OMEGA*Td0);                        // outfile<< "Rfo  "<<Rfo<<endl;
 Xud11=Xusigd+1./(1./Xasig+1./Xad+1./Xfsig);// outfile<< "Xud11  "<<Xud11<<endl;
 Rudo=Xud11/(OMEGA*Td11);                   // outfile<< "Rudo  "<<Rudo<<endl;
 Xuq11=Xusigq+1./(1./Xasig+1./Xaq);         // outfile<< "Xuq11  "<<Xuq11<<endl;
 Ruqo=Xuq11/(OMEGA*Td11);                   // outfile<< "Ruqo  "<<Ruqo<<endl;
 Ifbaz=Xad*Ifxx/1.05;                       // outfile<< "Ifbaz  "<<Ifbaz<<endl;
 Hj=Jrt*OMEGA*OMEGA/Sbaz;                   // outfile<< "Hj  "<<Hj<<endl;

 // Расчет параметров режима генератора для момента времени Т=0.
 SinFI=sqrt(1.-CosFI*CosFI);                // outfile<< "SinFI  "<<SinFI<<endl;
 FI=acos(CosFI);                            // outfile<< "FI  "<<FI<<endl;
 Inagr=sqrt(2.)*Sn*Kzagr/(sqrt(3.)*Un*Ibaz);// outfile<< "Inagr  "<<Inagr<<endl;
 TETA=atan(Inagr*(Xq*CosFI-Rso*SinFI)/(1.+Inagr*SinFI*(Rso+Xq)));
                                            // outfile<< "TETA  "<<TETA<<endl;
 Id=-Inagr*sin(TETA+FI);                    // outfile<< "Id  "<<Id<<endl;
 Iq=Inagr*cos(TETA+FI);                     // outfile<< "Iq  "<<Iq<<endl;
 Ud=-sin(TETA);                             // outfile<< "Ud  "<<Ud<<endl;
 Uq=cos(TETA);                              // outfile<< "Uq  "<<Uq<<endl;
 Eq=Uq-Id*Xd+Rso*Inagr*cos(TETA+FI);        // outfile<< "Eq  "<<Eq<<endl;
 If=Eq/Xad;                                 // outfile<< "If  "<<If<<endl;
 Uf=If*Rfo;                                 // outfile<< "Uf  "<<Uf<<endl;
 PSId=Xd*Id+Xad*If;                         // outfile<< "PSId  "<<PSId<<endl;
 PSIq=Xq*Iq;                                // outfile<< "PSIq  "<<PSIq<<endl;
 PSIf=Xf*If+Xad*Id;                         // outfile<< "PSIf  "<<PSIf<<endl;
 PSIud=Xad*(Id+If);                         // outfile<< "PSIud  "<<PSIud<<endl;
 PSIuq=Xaq*Iq;                              // outfile<< "PSIuq  "<<PSIuq<<endl;
 Mem=PSId*Iq-PSIq*Id;                       // outfile<< "Mem  "<<Mem<<endl;
 Mmex=Mem;                                  // outfile<< "Mmex  "<<Mmex<<endl;
 Znagrd=Ud/Id;                              // outfile<< "Znagrd  "<<Znagrd<<endl;
 Znagrq=Uq/Iq;                              // outfile<< "Znagrq  "<<Znagrq<<endl;

 // Расчет начальных условий Y(0) для системы дифференциальных уравнений
 Y[1]=PSId;
 Y[2]=PSIq;                                                        
 Y[3]=PSIf;                                                        
 Y[4]=PSIud;                                                       
 Y[5]=PSIuq;                                                       
 Y[6]=0.;                                                          
 Y[7]=GAM;
 for (int I=1; I<=NUR; I=I+1) {Y0[I]=Y[I];}

 // Расчет промежуточных переменных W1-W13, используемых
 // при расчете токов по известным потокосцеплениям
 W1=Xuq*Xq-Xaq*Xaq;                                                 
 W2=Xad*Xad;                                                        
 W3=Xq/W1;                                                          
 W4=Xaq/W1;                                                         
 W5=Xuq/W1;                                                         
 W6=Xf*Xud*Xd+2.*Xad*Xad*Xad-W2*(Xud+Xf+Xd);                        
 W7=(Xf*Xd-W2)/W6;                                                  
 W8=(Xf*Xad-W2)/W6;                                                 
 W9=(Xad*Xd-W2)/W6;                                                 
 W10=(Xd*Xud-W2)/W6;                                                
 W11=(Xud*Xad-W2)/W6;                                               
 W12=(Xf*Xud-W2)/W6;                                                
 W13=120./180.*3.141593;

 // Подготовка к реализации алгоритма Рунге-Кутта
 H1=OMEGA*H;
 TAU=OMEGA*T0;                                                     
 T=T0;
 NREZ=0;

 // Выдача заглавия таблицы в выходной файл-отчет
 if (T_CheckBox-> Checked)     {outfile << "   T    ";}
 if (PSId_CheckBox-> Checked)  {outfile << "PSId    "<<"    ";}
 if (PSIq_CheckBox-> Checked)  {outfile << "PSIq     "<<"    ";}
 if (PSIf_CheckBox-> Checked)  {outfile << "PSIf    "<<"    ";}
 if (PSIud_CheckBox-> Checked) {outfile << "PSIud   "<<"    ";}
 if (PSIuq_CheckBox-> Checked) {outfile << "PSIuq   "<<"    ";}
 if (PSIa_CheckBox-> Checked)  {outfile << "PSIa    "<<"    ";}
 if (PSIb_CheckBox-> Checked)  {outfile << "PSIb    "<<"    ";}
 if (PSIc_CheckBox-> Checked)  {outfile << "PSIc    "<<"    ";}
 if (Id_CheckBox-> Checked)    {outfile << "Id      "<<"    ";}
 if (Iq_CheckBox-> Checked)    {outfile << "Iq      "<<"    ";}
 if (If_CheckBox-> Checked)    {outfile << "If      "<<"    ";}
 if (Iud_CheckBox-> Checked)   {outfile << "Iud     "<<"    ";}
 if (Iuq_CheckBox-> Checked)   {outfile << "Iuq     "<<"    ";}
 if (Ia_CheckBox-> Checked)    {outfile << "Ia      "<<"    ";}
 if (Ib_CheckBox-> Checked)    {outfile << "Ib      "<<"    ";}
 if (Ic_CheckBox-> Checked)    {outfile << "Ic      "<<"    ";}
 if (S_CheckBox-> Checked)     {outfile << "S       "<<"    ";}
 if (GAM_CheckBox-> Checked)   {outfile << "GAM     "<<"    ";}
 if (Mmex_CheckBox-> Checked)  {outfile << "Mmex    "<<"    ";}
 if (Mem_CheckBox-> Checked)   {outfile << "Mem     ";}
 if (Ud_CheckBox-> Checked)    {outfile << "Ud    ";}
 if (Uq_CheckBox-> Checked)    {outfile << "Uq    ";}
 if (Ua_CheckBox-> Checked)    {outfile << "Ua    ";}
 if (Ub_CheckBox-> Checked)    {outfile << "Ub    ";}
 if (Uc_CheckBox-> Checked)    {outfile << "Uc    ";}
 if (T_CheckBox-> Checked)     {outfile <<endl;}

 bool bol=true; //для Ud Uq
 Udz1=Ud*cos(GAM)+Uq*sin(GAM); //  Предварительно для ДЗ: Udz1=Ua   //901
 TdzN=0.;                      //  Предварительно для ДЗ: TdzN=0    //902
 dTdz=0.;                      //  Предварительно для ДЗ: dTdz=0    //903
 Tdz=0.;                       //  Предварительно для ДЗ: Tdz=0     //904
 Tfiksir=0.;                   //  Предварительно для ДЗ: Tfiksir=0 //905
 Dkol=0.;                      //  Предварительно для ДЗ: Dkol=0    //906

 // Начало циклической части решения системы уравнений генератора

 // Надо ли заносить значения текущего шага в выходной файл-отчет
m4:     if(T-H*(NREZ*INTWR)< 0.) {goto m5;}                          //260

 // Расчет параметров, выводимых в файл-отчет, в фазных координатах А,В,С
 Ia=Id*cos(GAM)+Iq*sin(GAM) ;                                        //270
 Ib=Id*cos(GAM-W13)+Iq*sin(GAM-W13) ;                                //271
 Ic=Id*cos(GAM+W13)+Iq*sin(GAM+W13);                                 //272
 PSIa=PSId*cos(GAM)+PSIq*sin(GAM) ;                                  //273
 PSIb=PSId*cos(GAM-W13)+PSIq*sin(GAM-W13) ;                          //274
 PSIc=PSId*cos(GAM+W13)+PSIq*sin(GAM+W13) ;                          //275

 Ua=Ud*cos(GAM)+Uq*sin(GAM) ;                                        //270
 Ub=Ud*cos(GAM-W13)+Uq*sin(GAM-W13) ;                                //271
 Uc=Ud*cos(GAM+W13)+Uq*sin(GAM+W13);                                 //272

 // Наращивание счетчика записей, выводимых в выходной файл-отчет
 NREZ=NREZ+1  ;                                                     //280

 // Занесение значения текущего шага в выходной файл-отчет

 if (T_CheckBox-> Checked)  {outfile <<T<<"  ";}
 if (PSId_CheckBox-> Checked)  {outfile << PSId<<"  ";}
 if (PSIq_CheckBox-> Checked)  {outfile << PSIq<<"  ";}
 if (PSIf_CheckBox-> Checked)  {outfile << PSIf<<"  ";}
 if (PSIud_CheckBox-> Checked) {outfile << PSIud<<"  ";}
 if (PSIuq_CheckBox-> Checked) {outfile << PSIuq<<"  ";}
 if (PSIa_CheckBox-> Checked)  {outfile << PSIa<<"  ";}
 if (PSIb_CheckBox-> Checked)  {outfile << PSIb<<"  ";}
 if (PSIc_CheckBox-> Checked)  {outfile << PSIc<<"  ";}
 if (Id_CheckBox-> Checked)    {outfile << Id<<"  ";}
 if (Iq_CheckBox-> Checked)    {outfile << Iq<<"  ";}
 if (If_CheckBox-> Checked)    {outfile << If<<"  ";}
 if (Iud_CheckBox-> Checked)   {outfile << Iud<<"  ";}
 if (Iuq_CheckBox-> Checked)   {outfile << Iuq<<"  ";}
 if (Ia_CheckBox-> Checked)    {outfile << Ia<<"  ";}
 if (Ib_CheckBox-> Checked)    {outfile << Ib<<"  ";}
 if (Ic_CheckBox-> Checked)    {outfile << Ic<<"  ";}
 if (S_CheckBox-> Checked)     {outfile << S<<"  ";}
 if (GAM_CheckBox-> Checked)   {outfile << GAM<<"  ";}
 if (Mmex_CheckBox-> Checked)  {outfile << Mmex<<"  ";}
 if (Mem_CheckBox-> Checked)   {outfile << Mem<<"  ";}
 if (Ud_CheckBox-> Checked)    {outfile << Ud<<"  ";}
 if (Uq_CheckBox-> Checked)    {outfile << Uq<<"  ";}
 if (Ua_CheckBox-> Checked)    {outfile << Ua<<"  ";}
 if (Ub_CheckBox-> Checked)    {outfile << Ub<<"  ";}
 if (Uc_CheckBox-> Checked)    {outfile << Uc<<"  ";}

 if (T_CheckBox-> Checked)  {outfile <<endl; outfile <<endl;}

  {Series1->AddXY( T,Ub ,"",clRed);}    //построение осциллограммы Ub
  {Series2->AddXY( T,Ib ,"",clGreen);}  //построение осциллограммы Ib

m5:

 // Задание условий для внешней цепи генератора,
 // соответствующих режиму нарушения связи с энергосистемой,
 // с соответствующим сбросом/набросом нагрузки
 // по истечении двух периодов расчета нормального режима
     if ((T>0.04)&&(bol))  //работа блока один раз по истечении 2 периодов
    {                                                                 //300
    if (T_CheckBox-> Checked) {outfile <<" ====== Аварийный режим ====== "<<endl;}
    Znagrd=(Sn*Kzagr/Snagr)*Znagrd;  //изменение внешнего сопротивления при
    Znagrq=(Sn*Kzagr/Snagr)*Znagrq;  //нарушении связи с энергосистемой
    bol=false;                                                        //320
    }

  // Начало решения дифференциальных уравнений методом Рунге-Кутта (блок RNGKT)
 // ---------начало RNGKT--------

 // Начало цикла по четырем тактам Рунге-Кутта внутри каждого шага по x
 N=NUR;
 X=TAU;
 HH=H1;
 for (int J=1; J<=4; J=J+1)
 {                                                                    // 630
   // Вычисление независимой переменной x и интегрирунмых переменных Y как
   // аргументов функций F(x,Y) в правых частях уравнений
   XF=X+P[J]*HH;                                                      // 640
   for (int I=1; I<=N; I=I+1)  {YF[I]=Y0[I]+HH*F[I]*P[J];}            // 651
   // Вычисление значений функций F(x,Y) в правых частях уравнений (длок PRAV)
   // ---------начало PRAV--------

   // Пересылка иетегрируемых переменных в ячейки простых переменных
   PSId=YF[1];                                                        //840
   PSIq=YF[2];                                                        //841
   PSIf=YF[3];                                                        //842
   PSIud=YF[4];                                                       //843
   PSIuq=YF[5];                                                       //844
   S=YF[6];                                                           //845
   GAM=YF[7];                                                         //846
   // Вычисление токов по известных потокосцеплениям
   Id=W12*PSId-W11*PSIf-W8*PSIud;                                     //860
   Iq=W5*PSIq-W4*PSIuq;                                               //861
   If=W10*PSIf-W11*PSId-W9*PSIud;                                     //862
   Iud=W7*PSIud-W8*PSId-W9*PSIf;                                      //863
   Iuq=W3*PSIuq-W4*PSIq;                                              //864
   // Вычисление правых частей в системе дифференциальных уравнений
   F[1]=-(Znagrd*Id+(1.+S)*PSIq+Rso*Id);                              //880
   F[2]=-(Znagrq*Iq-(1.+S)*PSId+Rso*Iq);                              //881
   F[3]=Uf-Rfo*If;                                                    //882
   F[4]=-Rudo*Iud;                                                    //883
   F[5]=-Ruqo*Iuq;                                                    //884
   Mem=PSId*Iq-PSIq*Id;                                               //885
   F[6]=(Mmex-Mem)/(OMEGA*Hj);                                        //886
   F[7]=1.+S;                                                         //887
   // --------конец PRAV---------------

   //  Вычисление значений интегрируемых переменных Y на новом такте
   for (int I=1; I<=N; I=I+1) {Y[I]=Y[I]+HH*F[I]*Q[J]/6.;}            // 671
 }                                                                    // 680
 // Пересылка значений  интегрируемых переменных в массив Y0(N)
 for (int I=1; I<=N; I=I+1) { Y0[I]=Y[I]; }                           // 691
 // -------конец RNGKT------- ---------

 Ud=Znagrd*Id;     //вычисление напряжения на выводах генератора в оси d   
 Uq=Znagrq*Iq;     //вычисление напряжения на выводах генератора в оси q   

 // -----Вычисление параметров ДЗ-----                                //910
 //  Занесение в Udz2 значения Ua на текущем шаге
  Udz2=Ud*cos(GAM-W13)+Uq*sin(GAM-W13);                               //911
 //  Занесение в TdzK момент перехода Ua через ноль (конец полупериода)
 if((Udz2*Udz1)<0.) {TdzK=T; Dkol=Dkol+1;}                            //912
 if((TdzN>0)&&(Dkol<6))             //  Предотвращение ошибочного расчета в первый полупериод
 //  Вычисление продолжительности полупериода при переходе Ua через ноль
 {Tdz=fabs(TdzK-TdzN-0.01);                                           //913
 // Вычисление максимального изменения полупериода (бросок вектора в секундах)
 if ((Tdz<0.009)&&(Tdz>dTdz)) {dTdz=Tdz; Tfiksir=T;}                  //914
 }
 
 // вывод для отладки расчета ДЗ
 // outfile <<"T="<<T<< "; ";
 // outfile <<"Udz1="<<Udz1<< "; ";
 // outfile <<"Udz2="<<Udz2<< "; ";
 // outfile <<"TdzN="<<TdzN<< "; ";
 // outfile <<"TdzK="<<TdzK<< "; ";
 // outfile <<"TdzK-TdzN="<<TdzK-TdzN<< "; ";
 // outfile <<"Tdz="<<Tdz<< "; ";
 // outfile <<"dTdz="<<dTdz<< "; ";
 // outfile <<endl;

 TdzN=TdzK;
 Udz1=Udz2;

 // Периодизация угла GAM
 if(Y[7]<6.2831853) {goto m9;}                                      // 345
 Y[7]=Y[7]-6.2831853;                                               // 346
 Y0[7]=Y[7];

 // Продолжать ли вычисления?
m9: if(T<10) {goto m10;}                                            // 350
 Warning_Label1->Caption = "Задано слишком большое время расчета";
 Warning_Label2->Caption = "Рекомендуемое значение TKON: 0.1c";
 outfile <<"Дальнейший расчет нецелесообразен"<< endl;
 goto m11;                                                          // 360

m10: if ((T-TKON)>0.) {goto m11;}                                   // 370

 // Наращивание независимой переменной на величину шага
 TAU=TAU+H1;                                                        // 380
 T=TAU/OMEGA;                                                       // 390
 goto m4;                                                           // 400

m11:
 outfile << endl;
 outfile <<"Результат расчета параметров делительной защиты"<< endl;
 if (Sn*Kzagr>Snagr) {dTdz=-dTdz;}
 // Вывод на форму и в файл-отчет броска вектора (в градусах электрических)
 dTdz_Label->Caption = FloatToStrF(dTdz*360/0.02,ffGeneral,4,2);
 outfile <<"Угол смещения (бросок) вектора напряжения, эл. град.: "<<dTdz*360/0.02<< endl;
 // Вывод на форму и в файл-отчет времени макс. изменения периода напряжения (с)
 dTdz_Label2->Caption = FloatToStrF(dTdz,ffGeneral,4,2);
 outfile <<"Время максимального изменения периода напряжения, с: "<<dTdz<< endl;
 // Вывод на форму и в файл-отчет момента обнар. нар. связи с энергосистемой (с)
 dTdz_Label3->Caption = FloatToStrF(Tfiksir,ffGeneral,4,2);
 outfile <<"Момент обнаружения нарушения связи с энергосистемой ,с: "<<Tfiksir<< endl;
 // -------------
 //outfile.close();
}
//---------------------------------------------------------------------------




void __fastcall TCalculationForm::ImportClick(TObject *Sender)
{
float A;
 ifstream infile ("Initial.dat");
  infile >> Sn ;
  infile >> Un ;
  infile >> Ifxx ;
  infile >> Ifn ;
  infile >> Jrt;
  infile >> Rs;
  infile >> Rf;
  infile >> Xd11;
  infile >> Xd1;
  infile >> Xd;
  infile >> X2;
  infile >> Td0;
  infile >> Td11;
  infile >> Kzagr;
  infile >> Snagr;
  infile >> CosFI;
  infile >> GAM;
  infile >> H;
  infile >> TKON;
 //infile.close();
  
  Sn_Edit->Text = FloatToStrF(Sn,ffGeneral,7,1);
  Un_Edit->Text = FloatToStrF(Un,ffGeneral,7,1);
  Ifxx_Edit->Text = FloatToStrF(Ifxx,ffGeneral,7,1);
  Ifn_Edit->Text = FloatToStrF(Ifn,ffGeneral,7,1);
  Jrt_Edit->Text = FloatToStrF(Jrt,ffGeneral,7,1);
  Rs_Edit->Text = FloatToStrF(Rs,ffGeneral,7,1);
  Rf_Edit->Text = FloatToStrF(Rf,ffGeneral,7,1);
  Xd11_Edit->Text = FloatToStrF(Xd11,ffGeneral,7,1);
  Xd1_Edit->Text = FloatToStrF(Xd1,ffGeneral,7,1);
  Xd_Edit->Text = FloatToStrF(Xd,ffGeneral,7,1);
  X2_Edit->Text = FloatToStrF(X2,ffGeneral,7,1);
  Td0_Edit->Text = FloatToStrF(Td0,ffGeneral,7,1);
  Td11_Edit->Text = FloatToStrF(Td11,ffGeneral,7,1);
  Kzagr_Edit->Text = FloatToStrF(Kzagr,ffGeneral,7,1);
  Snagr_Edit->Text = FloatToStrF(Snagr,ffGeneral,7,1);
  CosFI_Edit->Text = FloatToStrF(CosFI,ffGeneral,7,1);
  GAM_Edit->Text = FloatToStrF(GAM,ffGeneral,7,1);
  H_Edit->Text = FloatToStrF(H,ffGeneral,9,1);
  TKON_Edit->Text = FloatToStrF(TKON,ffGeneral,7,1);
  
}
//---------------------------------------------------------------------------

