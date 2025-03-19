/*

AAA(ALMOST ALWAYS AUTO) kullanabildi�in her yerde auto kullan
---------------------------------------------------------------------
- **Glvalue (Generalized Lvalue):** lvalue ve xvalue ifadelerinin birle�imidir. Bellekte bir nesneyi temsil eder.
- **Rvalue (Right Value):** prvalue ve xvalue ifadelerinin birle�imidir. Bellekte k�sa �m�rl� veya ge�ici bir nesneyi temsil eder.

privmary value category
    L value
    PR value -> Pure R value
    X value -> eXpiring value

combined value category
    L value ve X value demek -> GL value demek
    PR value ve X Value demek -> R value demek

++x // C de R value C++ Da L value
--x // C de R value C++ Da L value

ama x++ R value

comma operat�r ( , ) virg�l operat�r� C de R value C++ da L value expression olu�turuyor

turnory operat�r� C de R value C++da L value expression olu�turur
--------------------------------------------------------------------------------------------------------------------------------------------------
referanslar derleyici a��s�ndan pointer ile ayn�d�r k�sacas� pointerlar�n maskelenmi� halidir arka planda pointer i�lemi g�r�r
baz� yerlerde pointer semanti�i uygun olmad��� i�in referanslar gelmi�tir

NOT:Referanslar default initialize edilemez

    int& r; //syntax error

    referanslar�n data type'� ayn� olmak zorundad�r

    referanslar bir kez ba�lat�ld�ktan sonra ba�ka bir nesneye referans olamazlar(re-bindeble de�il)
        int x = 10;
        int y = 10;
        int&r = x;
        r = y; // burda y'yi x'e atamak anlam�na geliyor y'yi referans alm�yor

int x = 5;

int& r1 = x++ // son ek ++ operat�r� c++ dilinde rvalue oldu�u i�in syntax error
int& r1 = ++x // �n ek ++ operat�r� c++ dilinde lvalue oldu�u i�in ge�erli

int x = 5;
int& r = x;

std::cout << &r << '\n'; // x'in adresine ula��l�r

int x = 10;
int y = 5;
int* const p = &x; // p pointer� yaln�zca x in adresini tutaca�� g�vencesini veriyor yani p nin adresi de�i�emez hayat� boyunca sadece x'in adresini g�stericek

bu pointer t�r�n�n 3 ad� vard�r
// const pointer to int
// top level const
// right const

p = &y // syntax error
*p = y // ge�erli

const int* p = &x // p adl� pointer low level const oldu�u i�in i�eri�i dereferance edilemez sadece okuma ama�l�d�r(read-only pointer) ama adresi de�i�ebilir

bu pointer t�r�n�n 3 ad� vard�r
// pointer to const int
// low level const
// left const

*p = 20; // syntax error
p = &y; // ge�erli

const int* p const = &x; // p adl� pointerin g�sterdi�i yerde adresi de de�i�emez
//const pointer to const int

*p = 20; // syntax error
p = &y; // syntax error

*p olu�turdu�u ifade L Value
*p++ ve *p-- R value

NOT:Pointerlar� referans almak i�in kullan�lan syntax bi�imi ��yledir

int x{} // zero initialization
int y{36} // direct list initialization
int* p = &x; // x in adresi p pointera atand� p nin i�inde 0 de�eri var
int*& r = p; //p adl� pointer r adl� referansa atand� r demek art�k x demek ��nk� p x adl� de�i�kenin adresini g�steriyor

r = &y; // p = &y r referans� p ye referans oldu�u i�in p'ye y'nin adresi atan�yor
*p = 678; // y'nin de�eri 678 oluyor

int foo(); // r value

NOT:call by value ile pass by value ayn� �ey demek

NOT:
void func(T& r) // ifadesi bir mutator bir ifadenin de�erini de�i�tiriyor anlam�na gelir
void func(T* r) // mutator
void func(const T& r) // accessor
void func(const T* r) // accessor
T& func() // b�yle bir fonksiyon g�rd���m�zde bu fonksiyon bize bir nesne d�nd�r�yor demeliyiz bu fonksiyona �a�r� yaparak bir nesneyi kullanma hakk�na eri�mi� oluyoruz
T* func() // nesnenin adresini d�nd�ren fonksiyon
const T& func(); // nesneye ula�mak i�in kullan�l�r nesneninde const olmas� gerekir
const T* func(); // nesneye ula�mak i�in kullan�l�r nesneninde const olmas� gerekir

M�LAKAT SORUSU

C dilinde foo(x) ad�nda bir �a�r� g�r�yorsak bunun call by value oldu�unu anlar�z
ama C++ dilinde bilemeyiz ��nk� referans semanti�i kullan�lm�� olabilir

NOT:Otomatik �m�rl� (automatic storage duration) bir nesnenin adresini d�nd�rmek mant�kl� de�ildir ��nk� bu nesne,
fonksiyonun bitiminde yok olur ve bellekteki adresi ge�ersiz hale gelir. Otomatik �m�rl� nesneler, tan�mland�klar�
bloktan ��k�ld���nda otomatik olarak silinirler. Bu nedenle, bu t�r nesnelerin adresini d�nd�rmek, o adresin ge�erlili�i
sona erdi�inde bellek hatalar�na ve tan�ms�z davran��lara yol a�ar.

### �rnek A��klama

#include <iostream>

int foo()
{
    int g = 45;
    return g;
}

int main()
{
    int x = foo();
    std::cout << x;
    return 0;
}

Bu kod par�as� sorunsuz �al���r ��nk� `foo` fonksiyonu `int` t�r�nde bir de�er d�nd�r�yor ve bu de�er `g`nin kopyas�d�r. `g`, `foo`
fonksiyonu sona erdi�inde yok olsa bile, d�nd�r�len kopya `x` de�i�kenine atan�r ve bu nedenle ge�erli olur.

### Ge�ersiz Kod

Ancak, `g`nin adresini d�nd�rmeye �al���rsan�z, bu durumda sorunlarla kar��la��rs�n�z:

#include <iostream>

int* foo()
{
    int g = 45;
    return &g;  // Ge�ersiz: g'nin adresini d�nd�rmek
}

int main()
{
    int* x = foo(); // dangling pointer
    std::cout << *x;  // Tan�ms�z davran��
    return 0;
}

Bu kodda `foo` fonksiyonu, `g`nin adresini d�nd�rmeye �al���yor. g otomatik �m�rl� bir nesne oldu�u i�in tan�ms�z davran�� olur `foo` sona erdi�inde `g` yok olur ve `x`
ge�ersiz bir adresi i�aret eder. `*x` ifadesi tan�ms�z davran��a yol a�ar.

### Do�ru Yakla��m

E�er fonksiyondan bir nesnenin adresini d�nd�rmek istiyorsan�z, o nesnenin statik veya dinamik �m�rl� olmas� gereklidir:

1. **Statik �m�rl� Nesneler**:

    int* foo()
    {
        static int g = 45;
        return &g;  // Ge�erli: g'nin adresi her zaman ge�erli kal�r
    }

2. **Dinamik �m�rl� Nesneler**:

    int* foo()
    {
        int* g = new int(45);
        return g;  // Ge�erli: g'nin adresi, delete edilene kadar ge�erli kal�r
    }

    int main()
    {
        int* x = foo();
        std::cout << *x;
        delete x;  // Dinamik �m�rl� nesne serbest b�rak�l�r
        return 0;
    }

Bu yakla��mlar, d�nd�r�len adresin ge�erli kalmas�n� sa�lar. Ancak, dinamik �m�rl� nesnelerle �al���rken
bellek y�netimi �nemlidir ve `delete` ile bellek serbest b�rak�lmal�d�r.

volatile
volatile niteleyicisi, bir de�i�kenin program d��� kaynaklar (�rne�in, donan�m veya ba�ka bir i� par�ac���) taraf�ndan de�i�tirilebilece�ini belirtir.
Bu, derleyicinin bu de�i�ken �zerinde optimizasyon yapmamas� gerekti�ini garanti eder.

const volatile Birlikte Kullan�m�
const volatile niteleyicileri birlikte kullan�ld���nda, de�i�kenin program taraf�ndan de�i�tirilemeyece�ini, ancak program d��� kaynaklar taraf�ndan
de�i�tirilebilece�ini belirtir. Bu, �zellikle donan�m kay�tlar� veya �ok i� par�ac�kl� programlama durumlar�nda kullan��l�d�r.

const volatile int statusRegister = 0xFF;
while (statusRegister == 0xFF) {
    // 'statusRegister' de�i�keni program taraf�ndan de�i�tirilemez, ancak donan�m taraf�ndan de�i�tirilebilir.
}

NOT:lvalue referans ve rvalue atamas�

int g = 45;

int &foo() //foo burda l value referans ve g nin adresini d�nd�r�yor
{
    return g; // g nin adresi d�n�yor
}

int* foo() // yukar�daki referans tan�mlamas�n�n pointer kar��l��� bu �ekildedir
{
    return &g;
}

int main()
{
    int &x = foo(); x ile foo lvalue referans oldu�u i�in x de�i�keni g de�i�kenine referanst�r
    ++*foo() // �a�r�s� asl�nda derleyici taraf�ndan ++(*(foo())) ifadesi olarak ele al�n�r

    return 0;
}

int g = 45;

int foo() // foo burda rvalue
{
    return g;
}

int main()
{
    int &x = foo(); x lvalue referans oldu�u i�in bir lvalue de�erine rvalue atanamaz derleme hatas� verir

    return 0;
}

int g = 45;

int foo() // r value
{
    return g;
}

int main()
{
    int x = foo(); // x in kendisi burda lvalue ama ald��� de�er rvalue yani olan �ey asl�nda x = 45;

    return 0;
}

int foo()
{
    int g = 45;
    return g;
}

int main()
{
    int x = foo();

    return 0;
}

NOT:Pointer array var ama pointer referance yok

int x=10,y=5;
int* p[2] = {&x,&y};

NOT:Array decay ve array pointer farkl�l���

int a[5] = {1,2,3,4,5};

int* p = a; // array decay olarak ge�er a dizisinin ilk eleman�n�n adresini tutar(t�r� int)

int (*p)[10] = &a; // p, a dizisinin tamam�n�n adresini tutar ve p, a dizisini i�aret eden bir pointer olur(t�r� int[5])

int (&r)[10] = a; // r, a dizisinin tamam�na referans olan bir referans de�i�kenidir.

NOT:Dizinin tamam�n�n adresini d�nd�rmek ve dizinin ilk elaman�n� d�nd�rmek aras�nda ki fark

### 1. D�ng�

for (int i = 0; i < 10; i++)
{
    std::cout << &a + i << " ";
}

Bu d�ng�de `&a + i` ifadesi kullan�l�yor. Bu ifade, `a` dizisinin ba�lang�� adresine `i` kadar dizinin tipine g�re bir ofset ekler.
Burada `&a` ifadesi, `a` dizisinin tamam�n� i�aret eden bir pointer anlam�na gelir ve t�r� `int (*)[10]`'dir.

Dolay�s�yla `&a + i` ifadesi asl�nda �u anlama gelir:
- `&a` dizisinin ba�lang�� adresi (`int (*)[10]` t�r�nde).
- `+ i` bu adresin �zerine `i` tane `int[10]` boyutu kadar ekleme yapar. Yani her ad�mda 10 * 40 sizeof(int) = 40byte boyutu kadar aral�klarla ilerler.

Bu nedenle, bu d�ng�de her iterasyonda dizinin her seferinde 40 eleman uzunlu�unda bir blok atlayarak ilerlemesini sa�l�yoruz.
Adresleri bast�r�yoruz, bu adresler b�y�k ihtimalle bellek bloklar� aras�nda b�y�k aral�klara sahip olacakt�r.

### 2. D�ng�

for (int i = 0; i < 10; i++)
{
    std::cout << a + i << " ";
}
Bu d�ng�de `a + i` ifadesi kullan�l�yor. `a` ifadesi, dizinin ba�lang�� adresini (`int*` t�r�nde) temsil eder.

Dolay�s�yla `a + i` ifadesi �u anlama gelir:
- `a` dizisinin ba�lang�� adresi (`int*` t�r�nde).
- `+ i` bu adresin �zerine `i` tane `int` boyutu kadar ekleme yapar. Yani her ad�mda 1 * 4 sizeof(int) 4byte boyutu atlar.

Bu nedenle, bu d�ng�de her iterasyonda dizinin bir sonraki `int` eleman�na ge�erek ilerleriz. Adresleri bast�r�yoruz ve bu adresler
her seferinde sadece 1 * sizeof(int) = 4byte boyutu kadar aral�klarla ilerler.

�zetle:

&a ifadesi, dizinin tamam�n� temsil eden bir adres d�nerken,
a ifadesi veya a + 0 ifadesi, dizinin ilk eleman�n�n adresini d�ner.

NOT:Referanslara Farkl� T�rden Bir Nesne ile �lkde�er Verilmesi Durumu

Bir referans�n ayn� t�rden bir de�i�kenle ilkde�er verilerek tan�mlanmas� gerekir
Referans�ns farkl� t�rden bir de�i�kenle ilkde�er verilerek tan�mlanmas� ge�ersizdir.

void func
{
double d = 10.5;
int &r = d; //Ge�ersiz
//...
}

Ancak const bir referansa ba�ka t�rden bir nesne ile ilk de�er verilmesi ge�erlidir:

void func()
{
double d = 10.5;
const int &r = d; // Ge�erli
//...
}

Bu durumda �nce const referansa ba�lanan farkl� t�rden nesnenin de�eri, referans�n t�r�nden yarat�lacak
ge�ici bir nesneye atan�r. Referans da bu ge�ici nesneye ba�lan�r. Yani derleyici a�a��daki gibi bir kod �retir:

int main()
{
double d = 10.5;
int temp = (int)d;
const int &r = temp;
return 0;
}

Bir diziyle ilgili genel i�lem yapan i�lev tan�mlanabiliyordu. B�yle i�levlere dizinin ba�lang�� adresi ve boyutu
arg�man olarak g�nderiliyordu. Dizinin ba�lang�� adresini i�leve g�ndermek i�in g�sterici kullan�yordu. Peki,
b�yle bir i�levin parametresi bir referans olabilir mi? Hay�r! referanslarla bu i� g�stericilerle oldu�u gibi
yap�lamaz. Ancak, �rne�in 10 elemanl� int t�rden bir diziyi g�steren g�sterici oldu�u gibi 10 elemanl� int t�rden
bir dizinin yerine ge�ecek bir referans da tan�mlanabilir.

#include <iostream>
using namespace std;

void display(const int(&r)[10])
{
    for (int k = 0; k < 10; ++k)
    cout << r[k] << " ";
    cout << endl;
}

int main()
{
    const int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    display(a);
}

Referanslar daha �ok, tek bir nesneyi adres y�ntemiyle i�leve ge�irmek amac�yla kullan�labilir. �rne�in tek bir
int de�er ya da tek bir yap� de�i�keni referans yoluyla i�leve ge�irilebilir. Ancak int t�rden bir dizi ya da bir yap�
dizisi bu y�ntemle i�leve do�al bir bi�imde ge�irilemez.

S�zdizimsel a��dan referanslar�n g�stericilere g�re kullan�m alanlar� daha dard�r. G�sterici dizileri olur ama
referans dizileri olamaz. G�stericileri g�steren g�stericiler olabilir ama referanslar�n yerine ge�en referanslar
olamaz.
Ancak ��phesiz bir g�stericinin yerine ge�en bir referans olabilir.

int main()
{
    int x = 10;
    int *ptr = &x;
    int *&r = ptr;
    *r = 20;
    std::cout << "x = " << x << std::endl;
}
--------------------------------------------------------------------------------------------------------------------------------------------------
bir diziyi i�aret eden bir pointer referans� (pointer-to-array reference)

void func(const int(*&r)[5])
{
    for (int i = 0; i < 5; i++)
    {
        std::cout << (*r)[i] << "\n";
    }
}

int main()
{
    int a[5]{ 1,2,3,4,5 };
    int(*p)[5]{ &a };
    func(p);
}
--------------------------------------------------------------------------------------------------------------------------------------------------
Pointer referanslar�, pointer'lar�n kendilerine referans vermemizi sa�layan bir C++ dil �zelli�idir. Bu, bir pointer de�i�kenini bir fonksiyona aktar�rken,
fonksiyonun sadece pointer'�n i�aret etti�i de�eri de�il, pointer'�n kendisini de de�i�tirebilmesine olanak tan�r.

### 1. **Pointer ve Pointer Referans�**

- **Pointer:**
  Bellekteki bir de�i�kenin adresini tutan bir de�i�kendir. �rne�in:

  int x = 10;
  int* ptr = &x; // ptr, x'in adresini tutar

  Burada `ptr`, `x` de�i�keninin adresini saklar. Yani `*ptr` yaz�ld���nda `x`'in de�erine ula��r�z.

- **Pointer Referans�:**
  Bir pointer'�n kendisine referans vermek, yani pointer'�n i�aret etti�i adresi (de�er de�il) de�i�tirebilmek i�in kullan�l�r.
  Pointer referans� `int*&` gibi bir s�zdizimiyle ifade edilir.
  �rnek:

  int x = 10;
  int y = 20;
  int* ptr = &x;

  int*& ref = ptr; // ref, ptr'nin referans�
  ref = &y;        // ref �zerinden ptr de�i�tirildi Art�k `ptr` de�i�keni `y`'nin adresini tutar.

### 2. **Pointer Referans� Neden Kullan�l�r?**

#### a. Pointer'� De�i�tirmek:
E�er bir fonksiyonun pointer'�n i�aret etti�i adresi de�i�tirmesini istiyorsan�z, pointer referans� kullan�rs�n�z.

�rnek:

void changePointer(int*& ptr) {
    static int z = 50; // Kal�c� bir de�i�ken
    ptr = &z;          // Pointer'�n i�aret etti�i adresi de�i�tir
}

int main() {
    int x = 10;
    int* myPtr = &x;

    std::cout << "Before: " << *myPtr << '\n'; // 10
    changePointer(myPtr);
    std::cout << "After: " << *myPtr << '\n';  // 50

    return 0;
}

**�al��ma Mant���:**
- `changePointer` fonksiyonu, `myPtr`'nin adresini de�i�tirir.
- Fonksiyon, pointer'� referans olarak ald��� i�in de�i�iklik �a��ran tarafa yans�r.

#### b. Dinamik Bellek Y�netimi:
Dinamik olarak olu�turulan nesneleri d��ar� ta��mak i�in kullan�l�r. Bu, `new` ve `delete` ile s�k kar��la��lan bir durumdur.

�rnek:

void createObject(int*& ptr) {
    ptr = new int(42); // Dinamik olarak bir int olu�tur ve pointer'a ata
}

int main() {
    int* myPtr = nullptr;

    createObject(myPtr); // Fonksiyon pointer'� de�i�tirir
    std::cout << "Value: " << *myPtr << '\n'; // 42

    delete myPtr; // Dinamik belle�i serbest b�rak
    return 0;
}

**�al��ma Mant���:**
- `createObject`, dinamik olarak bir `int` olu�turur ve `myPtr`'nin adresini de�i�tirir.
- Pointer referans� olmadan, bu de�i�iklik fonksiyonun d���na yans�mazd�.

### 3. **Pointer Referans�n�n S�z Dizimi**

Pointer referanslar� �u �ekilde tan�mlan�r:

int*& ref = pointer; // ref, bir pointer'�n referans�d�r.

Burada:
- `int*` bir pointer t�r�d�r.
- `&` referans anlam�na gelir.
- `ref` art�k `pointer` de�i�keninin referans�d�r.

### 4. **Pointer Referans� ve Dereferans Fark�**

- Dereferans (`*`) bir pointer'�n i�aret etti�i de�ere ula�may� sa�lar:

  int x = 10;
  int* ptr = &x;

  std::cout << *ptr; // x'in de�eri (10)

- Pointer referans� (`*&`) pointer'�n kendisini de�i�tirmeyi sa�lar:

  int x = 10, y = 20;
  int* ptr = &x;

  int*& ref = ptr; // Pointer'�n referans�
  ref = &y;        // Pointer art�k y'yi i�aret eder

  std::cout << *ptr; // 20

### 5. **Neden `*&` Kullan�yoruz?**

Bir pointer'� do�rudan de�i�tirmek i�in neden referansa ihtiyac�m�z var? Bunun sebebi, C++'da fonksiyonlara de�er kopyalanarak (pass-by-value) veri g�nderilmesidir:
- E�er bir pointer fonksiyona **de�er olarak** (`int*`) ge�irilirse, bu pointer'�n bir kopyas� �zerinde i�lem yap�l�r ve orijinal pointer de�i�mez.
- E�er bir pointer **referans olarak** (`int*&`) ge�irilirse, orijinal pointer de�i�tirilir.

### 6. **Hata Durumlar� ve Dikkat Edilmesi Gerekenler**

#### a. `nullptr` Kullan�m�:
Bir pointer referans�n�n `nullptr` almas� m�mk�nd�r, ancak dereferans etmeye �al���rsan�z program ��ker:

int* ptr = nullptr;
int*& ref = ptr;

std::cout << *ref; // HATA: nullptr dereferans�!

#### b. Bellek S�z�nt�s�:
Dinamik bellekte bir pointer referans�n� yanl�� y�netmek bellek s�z�nt�s�na yol a�abilir. �rne�in:

void badExample(int*& ptr) {
    ptr = new int(10); // Yeni bellek ayr�ld�
    // Eski bellek serbest b�rak�lmad�, bu bir bellek s�z�nt�s�d�r!
}

#### c. Kullan�lmayan Adresler:
Statik ya da otomatik �m�rl� de�i�kenlere referans verirken dikkatli olun. �rne�in, lokal bir de�i�kenin adresi d�nd�r�lemez:

int* unsafePointer() {
    int x = 10;
    return &x; // HATA: Lokal de�i�kenin adresi d�nd�r�ld�
}

### 7. **�zet**

- **Pointer referans� (`int*&`)** bir pointer'� de�i�tirmek i�in kullan�l�r.
- Bellek y�netimi ve performans iyile�tirme gibi durumlarda faydal�d�r.
- Yanl�� kullan�ld���nda bellek s�z�nt�lar�na veya `nullptr` dereferans�na yol a�abilir.
--------------------------------------------------------------------------------------------------------------------------------------------------
Dangling Pointer Nedir:

Dangling pointer bellekte ge�ersiz veya serbest b�rak�lm�� bir adresi i�aret eden bir g�stericidir.
Bu durum, bellek hatalar�na ve tan�ms�z davran��lara yol a�ar. Bir g�sterici, hedefledi�i bellek alan� ge�erli olmad���
halde kullan�lmaya �al���ld���nda dangling pointer durumu ortaya ��kar.

1. **Otomatik �m�rl� Nesne Adresini D�nd�rme:**

   Otomatik �m�rl� (automatic storage duration) 
### Dangling Pointer �rnekleri

otomatik �m�rl� nesneler, fonksiyonun sona ermesiyle ge�ersiz hale gelirler. Bu nesnelerin adresini d�nd�rmek dangling pointer olu�turur.

   int* foo() {
       int x = 10;
       return &x;  // Ge�ersiz: x'in adresini d�nd�rmek
   }

   int main() {
       int* p = foo();
       // p burada dangling pointer'd�r.
       std::cout << *p;  // Tan�ms�z davran��
       return 0;
   }

2. **Dinamik Bellek Serbest B�rakma:**

   Dinamik bellek alan� `delete` veya `free` ile serbest b�rak�ld���nda, bu belle�i i�aret eden g�sterici dangling pointer haline gelir.

   int main() {
       int* p = new int(5);
       delete p;  // Bellek serbest b�rak�l�r
       // p burada dangling pointer'd�r.
       std::cout << *p;  // Tan�ms�z davran��
       return 0;
   }

3. **Scope D���na ��kan Yerel De�i�ken:**

   Bir g�sterici, scope d���na ��kan bir yerel de�i�keni i�aret ediyorsa dangling pointer olur.

   int* ptr;

   {
       int x = 20;
       ptr = &x;
   }

   // x burada scope d���na ��kt� ve ptr dangling pointer'd�r.
   std::cout << *ptr;  // Tan�ms�z davran��

### Dangling Pointer'lar� �nlemek ��in �pu�lar�

1. **G�stericiyi Serbest B�rakma Sonras� Null Yapmak:**

   Dinamik bellek serbest b�rak�ld���nda g�stericiyi null yaparak, tekrar kullan�lmas�n� �nleyebilirsiniz.

   int* p = new int(5);
   delete p;
   p = nullptr;  // p art�k ge�erli bir adresi i�aret etmiyor

2. **Ak�ll� G�stericiler Kullanmak:**

   C++'ta ak�ll� g�stericiler (smart pointers) kullanarak bellek y�netimini otomatikle�tirebilir ve dangling pointer sorunlar�n� azaltabilirsiniz.

   #include <memory>

   void foo() {
       std::unique_ptr<int> p = std::make_unique<int>(10);
       // p burada otomatik olarak bellekten serbest b�rak�lacak
   }

3. **Ge�erli Adresler D�nd�rmek:**

   Otomatik �m�rl� nesnelerin adreslerini d�nd�rmek yerine statik veya dinamik �m�rl� nesnelerin adreslerini d�nd�rmek.

   int* foo() {
       static int x = 10;
       return &x;  // Ge�erli: x her zaman ge�erli kal�r
   }

Dangling pointer'lar bellek hatalar�na ve program ��kmesine yol a�abilir, bu y�zden dikkatle y�netilmelidir.
--------------------------------------------------------------------------------------------------------------------------------------------------
NOT: referanslarda ampersand operat�r�nden sonra const yazmak anlaml� de�ildir
��nk� referanslar zaten tek bir yeri g�sterdi�i i�in default olarak const'tur
g�sterdi�i yer de�i�meyece�i i�in const niteli�ini ampersand operat�r�nden sonra eklemenin anlam� yoktur sadece fazlal�kt�r

int x = 10;
int& const r = x; // default olarak zaten orda gizli bir const bulunur yazmaya gerek yoktur

int x = 10;
const int& r = x;

int y = r + 5; // b�yle bir ifade kullan�rsak burda r'nin de�eri hala 10dur y'nin de�eri 15 olur
std::cout << y;
--------------------------------------------------------------------------------------------------------------------------------------------------
NOT:Bir fonksiyonun setter veya getter oldu�unu nereden anlar�z

void foo(T &r); // Const anahtar kelimesi olmad��� i�in de�eri de�i�tirmeye y�nelik yaz�lan bir fonksiyon olarak
anla��l�r bu tarz fonksiyonlar g�rd���m�zde anlamam�z gereken �ey bu fonksiyon bir de�eri set etti�idir

void foo(const T &r) // Const anahtar kelimesi oldu�u i�in sadece okuma amac�yla kullan�l�r
--------------------------------------------------------------------------------------------------------------------------------------------------
Bir fonksiyon veya de�i�ken const & ise hem lvalue de�er hemde rvalue de�er kabul eder

double x = 2.67;
const int& r = x; // farkl� t�rden olsa bile

int temp = x;
const int& r = temp;

void foo(int &r) // sadece lvalue al�r
{
    std::cout<<r;
}

int main()
{
    int x = 5;

    foo(x + 5); // pr value oldu�u i�in hata
}

void foo(const int &r) //  lvalue ve rvalue al�r
{
    std::cout<<r;
}

int main()
{

    int x = 5;

    foo(x + 5); // ge�erli foo de�eri const oldu�u i�in

}

NOT:Geri d�n�� de�eri Referans olmayan fonksiyon de�erleri rvalue say�l�r

Struct Nec{};

Nec func(const Nec&);
Nec foo();

int main()
{
    func(foo()); // func fonksiyonu const oldu�u i�in hem rvalue hemde lvalue de�eri kabul eder
}

Nec func(Nec&);
Nec foo();

int main()
{
    func(foo()); // func fonksionu lvalue referans ald��� i�in foo fonksiyonu yine atanamaz ��nk� foo rvalue
}

void bar(Nec&);
Nec& foo();

int main()
{
    bar(foo()) // GE�ERL� bar fonksiyonu lvalue referans de�eri al�yor
    foo fonkisiyonuda referans d�nd�rd��� i�in lvalue referans olmu� oluyor
}
--------------------------------------------------------------------------------------------------------------------------------------------------
func(&x) operat�r�n�n olu�turdu�u ifade PR value
func(nullptr) PR value
string literalleri L value
a[3] gibi bir ifade L value

pointer array
    int x = 5;
    int y = 5;
    int* p[2]{ &x,&y };

pointer de�i�kenler default initalize edilebilir ama iyi bir uygulama de�ildir
int* p; // wild pointer denir

*/