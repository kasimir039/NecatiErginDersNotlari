/*

 dynamic_cast'in C dilinde do�rudan kar��l��� yok inheritance(kal�t�m) run time polymorphism ile ilgili bir ara� ilerde bu operat�r� down casting'in run time da g�venli yap�l�p
 yap�lamad���n� s�nayaca��z

 t�r d�n��t�rme operat�rleri template sentaks�yla kullan�l�yor

 static_cast<target type>(operand) // <> buna angular bracket(hoca a��sal parantez diyor)
 const_cast<target type>(operand)
 reinterpret<target type>(operand)
 dynamic_cast<target type>(operand)

 a��sal parantezin i�ine her zaman hedef t�r�(target type) yaz�yoruz yani t�r d�n���m� hangi t�re d�n��t�r�lmek istiyorsa o t�r yaz�lacak

 hoca explicit d�n���mlerle ilgili kodda bir hata ararken �nce reinterpret_cast sonra const_cast en son static_caste bakmay� tercih ediyormu�

 static_cast
     dilin m�mk�n k�ld��� baz� �rt�l� d�n���mler var ve bunlar kategorize ediliyor bu �rt�l� d�n���mlerden en �nemlilerden belkide en s�k kullan�lanlar� 
     standart conversion deniliyor standart d�n���m asl�nda dilin kurallar�nca legal olan d�n���mler yani �rt�l� olarakta yap�lan d�n���mler static_cast sadece burada
     de�il ama burada �zellikle kullanmam�z gereken bir anahtar kelime yani biz dil taraf�nda �rt�l� olarak zaten yap�lan bir d�n���m� bilerek isteyerek yani 
     explicit olarak yap�yorsak kullanmam�z gereken operat�r static_cast 

    int main()
    {
        int i1 = 190;
        int i2 = 7;

        static_cast<double(i1) / i2; // burda b�lme i�lemini double olarak yapmak isteyebiliriz
    }

    double dval = 3.564;

    int ival = dval; // burda veri kayb� olur do�ru kabul edilmez ama bilerek isteyerek yap�yorsak t�r d�n��t�rme operat�r�n� kullanmam�z gerek
    
    tam say� t�rlerinden numaraland�rma t�rlerine implicit conversion yok bunu bazen bilerek isteyerek yapt��m�z yerler olabilir
        enum Fruit {Apple,Banana,Pear};
        in main()
        {
            Fruit f = Apple;
            int ival = 3;
            f = static_cast<Fruit>(ival);
        }

     numaraland�rma t�rlerinden tam say� t�rlerine impclicit conversion var ama do�ru de�il b�yle bir d�n���m olsa dahi yinede t�r d�n��t�rme
     operat�rlerini kullanmam�z iyi olur
        
       enum Fruit { Apple, Banana, Pear };
       int main()
       {
           Fruit f = Apple;
           int ival = 3;
           ival = static_cast<int>(f); // static_cast kullanmasak hata de�il ama do�ruda bir i�lem de�il 
       }

    void* t�r�nden void* olmayan t�re d�n���m
        int x{};
        void* vp{ &x };

        int* ip = static_cast<int*>(vp);

    �zetlemek gerekirse 
        standart d�n���mler 
        farkl� enum t�rleri aras�nda d�n���m
        tam say� t�rlerinden enum t�rlerine d�n���m
        enum t�rlerinden tam say� t�rlerine d�n���m� bilerek isteyerek yap�yorsak static_cast operat�r�n� kullanmal�y�z

    bir senaryo d���nelim enum t�rlerine kar��l�k string literalleri kullan�lmak istensin
        enum class Fruit { Apple, Pear, Banana, Cherry };
        const char* const fnames[] = { "Apple, Pear, Banana, Cherry" };

        int main()
        {
	        Fruit f{ Fruit::Banana };

	        //fnames[f]; // asl�nda burdada tam say�ya bir d�n���m oluyor unscoped enum olsayd� hata olmayacakt� 
	        fnames[static_cast<int>(f)]; 
        }
const_cast
    referans semanti�i ile ve pointer semanti�i ile kullan�labilir kar��m�za daha �ok pointer ile kullan�ld��� ��kacak const_cast'in kullan�lma amac�
    const nesne adresinden const olmayan nesne adresine d�n���m const int* -> int*  const MyClass* -> MyClass* gibi d�n���mler
    const int& -> int& buradaki d�n���m static_cast d�n���m� ile yap�lamaz sentaks hatas� olur
        int x{};

	    const int* p = &x;
	    int* ptr;

	    ptr = p; // const_cast<int*>(p);

       pointer yada referans semanti�ini kullanmazsak const_cast'i kullanamay�z

    const_cast �ok riskli kullan�rken �ok dikkatli olmak gerekir ��nk� fiziksel olarak const olan bir nesnenin adresini const olmayan bir nesne adresi gibi kullanmak
    legalite engelini a�sakta do�ru de�il

    constulu�u 2 ye ay�rmal�y�z bunlar standart'�n kulland��� terimler de�il
        contractual constness
            int x{4356};
            const int* p = &x; //p'nin g�sterdi�i nesnenin kendisi const de�il p'nin kendisi const burda adeta kontrakt imzal�yoruz p'nin kendisinden x nesnesine eri�ti�im zaman
            x'i const bir nesne gibi ele alaca��m�z� s�yl�yoruz 
            
            int* ptr = p; // burda const_cast kullanmam�z herhangi bir UNDEFINED BEHAVIOUR olmaz ��nk� p'nin g�sterdi�i nesne const de�il e�er x'in kendiside const olsayd� 
            yapt���m�z bu d�n���m UNDEFINED BEHAVIOUR olurdu

        physical constness 
            const int x{4356};
            const int* p = &x; // p burda sadece contractual const de�il ayn� zamanda physical const
            int* ptr = const_cast<int*>(p); // b�yle bir d�n���m� kesinlikle yapmamam�z gerekir UB

            dilin kutrallar� zaten const olmayan nesne adresi t�r�nden const olan nesne adresi t�r�ne d�n���mede const_cast'in kullan�lmas�na izin veriyor
                int x{ 4356 };
                const int * p= const_cast<const int*>(&x); // bu d�n���m zaten �rt�l� olarak yap�ld��� i�in ender kar��m�za ��kar

reinterpret_cast
    di�erlerine g�re �ok daha riskli ve �ok daha dikkatli �ekilde kullanmam�z gerekiyor legal olarak kullan�lmas� do�ru kullan�ld��� anlam�na gelmiyor kullan�ld��� yerler
        a)bir nesne adresini farkl� t�rden bir nesne adresiymi� gibi kullanmak
        b)tam say� de�erlerini adres de�erleri olarak kullanmak
   
        di�er t�r d�n��t�rme operat�rlerinin kullan�lmas� b�yle durumlarda legal de�il
        baz� durumlarda nesneleri char, signed char, unsigned char gibi elemanlara sahip dizilermi� gibi byte byte char char dola�mak istiyoruz bu durumda char* t�r�ne
        yada bu char t�rlerinden herhangi biri i�in pointer t�r�ne d�n���m yapmam�z gerekiyor

            int x{45};
            char* p = reinterpret_cast<char*)(x); 

        yada bazen asl�nda adres olarak kullanabilece�imiz tam say� de�er var ve bunu kullanmak istiyoruz
            int* p = reinterpret_cast<int*>(0x1AC4);

        reinterpret_cast'in kullan�lmas�n� zorunlu k�lan durumlar var mesela kursun sonlar�na do�ru dosya i�lemleri konusunu g�rd���m�zde formats�z okuma yazma i�lemlerinde
        tipik olarak char* t�r�ne d�n���m�n gerekti�ini g�rece�iz

        k�sacas� reinterpret_cast 
            ya farkl� adres t�rleri aras�nda 
            yada bazen bir tam say� ifadenini adres olarak kullan�lmas� gerektirdi�i yerler oluyor 

        bu d�n���m yanl��l�kla olursa ciddi problemler olabilir

        hoca s�k yap�lan bir sentaks hatas�ndan s�z ediyor
            const int x = 56;
            reinterpret_cast<char*>(&x); // burda tek bir d�n���m olmuyor iki ayr� d�n���m�n gerektirdi�i yerde tek bir d�n��t�rme operat�r�yle bu� i�i yapamay�z

            reinterpret_cast<char*>(const_cast<int*>(&x));

           const_cast<char*>(reinterpret_cast<const char*>(&x)); // iki �ekildede yapabiliriz            

        c'de olan type cast operat�r�n tam tersi c++ dilinde eskiden beri var olan explicit type cast dilin kurallar� buna functional type cast diyor
            double dval = 6.76;
            int(dval);
        
dynamic_cast
    inheritance konusunda ele al�nacak
 --------------------------------------------------------------------------------------------------------------------------------------------------
 constexpr(constant expression) specifier c de yok modern c++ ile geldi(c++11)
    derleme zaman� de�eri derleyici taraf�ndan belli olan garanti alt�nda olan ifadeler c diline g�re c++ dilinde constant expression �ok daha geni� ve daha fazla kurala tabii

    const int x = 45; // b�yle bir ifadeyi constant expression olarak kullanabilir miyiz cevap: evet yada hay�r de�il onu initialize eden ifadenin ne olduu�na ba�l�

    int foo();

    int main()
    {
        const int x = 45;  // constant expression
        const int y = foo(); // constant expression de�il
    }

    constexpr bir type qualifier de�il 
        constexpr int x = 45; // x'in decleration type'� const int constexpr anahtar s�zc��� zaten bildirimde constu ima ediyor
        constexpr const int x = 45; // ikisi aras�nda bir fark yok yani constexpr'yi kulland���m�z zaman constlu�uda alm�� oluyoruz

    e�er constantexpr ile bir de�er olu�turursak bu de�erin constant expression olma garantisi var constexpr anahtar s�zc���n�n se�ilmesindeki nedende bu
    ama constexpr ile initialize edilen de�erinde constant expression olmas� gerek 

    her de�i�keni constexpr yapamay�z sadece literal typelardan olan de�i�kenleri constexpr yapabiliriz

    auto ile constexprnin do�rudan bir ilgisi yok
        const int a = 67;
        const int b = 33;
        constexpr auto x = a + b; // burda auto i�in yap�lan ��kar�m x de�erini constexpr int olarak nitelemekle ayn� anlama geliyor
        a yada b const olmasayd� constexpr niteleyicisi ile olu�turulmu� de�i�kene b�yle bir ifadenin initalize olmas� sentaks hatas� olu�turucakt�
    
    �rnek
        int x = 45;
        int y = 13;

        int main()
        {
            constexpr int* py = &x;

            py = &y; // sentaks hatas� ��nk� p top level const -> constexpr int* const
            *py = 11;

            constexpr const int* p = &x; // b�yle bir bildirim genelde kar��t�r�l�yor burda p hem low level const hemde top level const olmu� oluyor

            *p = 11;  // art�k hata verir

            yani constexpr bir de�er pointer yada referans oldu�unda top level constlu�u sat�n al�r referans yada pointer olmad��� durumlarda
            low level constlu�u sat�n al�r

        }

    constexpr'yi biraz daha karma��k k�lan de�i�kenleri de�il fonksiyonlar� nitelemesi bir fonksiyonu constexpr yaparsak b�yle fonksiyonlara constexpr function deniyor
        constexpr int func(int x)
        {
            return x * x + 5;
        }

        ba�larda �ok k�s�tlama varm�� c++23 ile birlikte neredeyse k�s�tlama kalmam�� ama hala var
        k�s�tlamalrdan biri literal type ile ilgii bir constexpr fonksiyonun parametre de�i�kenleri yada de�i�keni fonksiyonun geri d�n�� de�eri t�r� fonksiyonun i�inde
        tanmlanan yerel de�i�kenler bunlar literal type olmak zorunda

    fonksiyonun constexpr olmas� ��yle bir garanti i�eriyor 
        b�yle bir fonksiyona yap�lan �a��rda fonksiyonun t�m parametre de�i�kenlerine g�nderilen arg�manlar constant expressionsa fonksiyon �a�r� ifadesi constant expression
        gereken bir yerde kullan�ld���nda fonksiyonun geri d�n�� de�eri derleme zaman�nda elde edilmek zorunda 
        not:fonksiyona g�nderilen ifadelerin constant expression olma zorunlulu�u yok
            
        constexpr int func(int x)
        {
	        return x * x + 5;
        }

        int main()
        {
	        int a[func(12)]; // int a[149] ile yazmak ayn�
        }

    hoca yanl�� anla��lan yere de�iniyor
        bu mecburiyet constexpr fonksiyona yap�lan �a�r�n�n const expression gereken yerde kullan�lmas� durumunda garantisi var,
            int a = func(12) + func(5); // buradaki elde edilen de�erlerin compile timeda elde edilmesi garantisi yok derleyici bunu compile timedada elde edebilir
            etmeyebilirde bu optimizyon sadece bu normal fonksiyonlardada var ama a de�eri constexpr olsayd� compile timeda elde edilme garantisi vard�

            yani burda sadece fonksiyonunda consexpr olmas� yetmiyor kullan�ld��� ifadeninde constant expression olmas� laz�m
            constexpr int a = func(12) + func(5); // derleyici art�k burda a'n�n de�erini compile timeda elde etmek zorunda
   
    constexpr fonksiyonlar ve de�i�kenler implicitly inline ODR'� ihlal etmezler
    not:constexpr fonksiyonlar run time ile de alakal� olabilir

    c++20 ile consteval anahtar s�zc��� eklendi bu tamamen compile time ile ilgili

    constexpr fonksiyon sabit ifadesi �reten bir yerde kullan�ld���nda undefined behaviour olu�tu�u durumda derleyici sentaks hatas� verir
    de�erlerin do�rudan compile timeda hesaplanmas� baz� i�lemlerin run timeda hesaplanmas�n�n �n�ne ge�iyor �zellikle generic programlamada b�yle durumlar �ok �nemli

    constexpr bildirimde ve tan�mda olmak zorunda
     necati.h
       constexpr bool isprime(int);
    necati.cpp
        constexpr bool isprime(int x);
 --------------------------------------------------------------------------------------------------------------------------------------------------
 hoca eksik olunan bir yere dikkat �ekiyor comma(virg�l) token'� virg�l hem bir operat�r hemde delimeter olarak kullan�l�yor(comma seperator list)
 kar��t�r�lan yer ise hangi virg�l operat�r virg�l ve hangi virg�l delimeter virg�l

 () parantez baz� yerlerde operat�r baz� yerlerde sentaks�n bir bile�eni baz� yerlerde ise �ncelik parantezi olarak kullan�l�yor
     Parantez i�inde hangi de�er varsa o de�erin value kategorisi odur

     int x = 50;

     (x) // l value

 baz�  durumlarda parantez sentaks�n gerektirdi�i parantez mi yoksa �ncelik parantezi mi diye kar��t�r�labiliyor
    int x = 6;
    auto sz = sizeof(x); // �ncelik parantezi e�er sentaks�n gerektirdi�i bir parantez olsayd� sizeof x; �eklinde bir kullan�m sentaks hatas� olu�tururdu
    sizeof(int) burada ki parantez art�k sentaks�n gerektirdi�i parantez

NOT:Functional type casting
    double dval = 6.76
    int(dval);
--------------------------------------------------------------------------------------------------------------------------------------------------
c++ dilinde standart olan digit seperator
    sabitlerin yaz�m�nda yazamy� ve okumay� kolayla�t�rmak i�in kullan�mas�
    auto x = 761243678 // gibi bir �ey yazsak g�rsel olarak alg�lamak hi� kolay de�il
    x = 761'243'678 �imdi okumas� daha kolay

    di�er say� sistemlerinin hepsinde de kullan�labilir
    auto x = 0x1AC4'2345;
    auto x = 0b101'0101;
--------------------------------------------------------------------------------------------------------------------------------------------------
attribute(hoca �znitelik diyor) modern c++ ile eklenen �nemli bir �zellik
    �zel bir sentaksla olu�turulan yap�lard�r [[nodiscard]] gibi sentaks bi�imi vard�r baz� yerlerde derleyiciyi uyar� vermeye te�vik ediyor
    bazen uyar� vermesini engelliyor baz� attirbutelar daha iyi optimizasyon yapmam�z� sa�l�yor

    ba�lang�� seviyesinde i�imize yarayacak olan [[nodiscard]] attribute �ok �nemli
        bir fonksiyonun geri d�n�� de�erinin olmas� o fonksiyonun geri d�n�� de�erinin kullan�lma mecburiyetini vermiyor
            int func(int)

            int main()
            {
                func(12); // b�yle yaparak fonksiyonun geri d�n�� de�erini dicard etmi� oluyoruz yani ge�ersiz k�lm�� oluyoruz SORU:burada logic hata var m�? de�i�ir
                fonksiyonun geri d�n�� de�erinin ne oldu�una ba�l� mesela printf("necati") printf karakter say�s�n� d�nd�r�yor bunu bir de�i�kende tutsayd�k 6 say�s�n� elde ederdik
                yani geri d�n�� de�eri i�imize yaramad��� i�in kullanm�yoruz burda discard etmi� oluyoruz

            }

    baz� fonksiyonlar�n tek farkl�l�k nedeni bir hesaplama yapmak program state'inde de bir de�i�iklik olu�turmuyor b�yle fonksiyonlara pure function deniyor

    bool isprime(int);

    inr main()
    {
        int x = 7321;
        isprime(x); // bu fonksiyon pure function oldu�u i�in logic bir hata var geri d�n�� de�erini kullanmam�z gerek
    }
        [[nodiscard]]
    bool ispirme(int); // burada [[nodiscard]] atrribute'u ben bu fonksiyona �a�r� yapt���m�zda e�er bu fonksiyonun geri dn�� de�erini kullanm�yorsak
                          bana uyar� mesaj� ver anlam�nda kullan�l�yor 
--------------------------------------------------------------------------------------------------------------------------------------------------
function overloading(fonksiyonlar�n y�klenmesi)
    hoca fonksiyonlar�n a��r� y�klenmesi terimini kabul etmiyor kula�a k�t� bir �eymi� gibi geldi�i i�in hoca buna fonksiyonlar�n y�klenmesi diyor
    function overloading dedi�imiz ara� belirli ko�ullar alt�nda fonksiyonlar�n ayn� isim ve farkl� kodlara sahip olmas�na ra�men ayn� ismi payla�mas�n� m�mk�n k�l�yor

    1)function overloading ne i�e yar�yor?
        e�er soyutland�klar� zaman farkl� kodlara sahip olmas�na ra�men soyutlamayla ayn� i�i yap�yorsa onlar�n isimlerinin ayn� olmas� b�yle fonksiyonlara �a�r� yapan
        programc�n�n i�ini kolayla�t�r�yor c dilinde �rne�in mutlak de�er fonksiyonu abs -> fabs ->labs bunlara bakt���m�zda hepsi mutlak de�er fonksiyonu
        isimleri farkl� ��nk� c de function overloading yok asl�nda hepsi ayn� i�i yap�yor sadece parametreleri ve geri d�n�� de�erleri farkl� int,float,long gibi

        ayn� ismi verdi�imiz ortak bir soyutlama yapm�� oluyoruz neyin mutlak de�erini hesaplarsak hesaplayal�m �a��raca��m�z fonksiyon abs() yine ayr� fonksiyonlar var ama 
        hepsinin ismi ayn� b�yle bir fonksiyona �a�r� yapt���m�zda derleyici compile timeda fonksiyona g�nderilen arg�manlar�n t�r�nden ve say�s�ndan hareketle 
        n tane abs isimli farkl� koda sahip fonsiyondan hangsinin �a��r�ld���n� compile timeda anl�yor ve fonkisiyon �a�r�s�n� o fonksiyona ba�l�yor konunun en zor 
        k�sm� derleyicinin bu i�i ger�ele�tirdi�i s�re� buna FUNCTION OVERLOAD RESOLUTION deniliyor   

    2)function overloading compile time'a y�nelik(static binding)
        fonksiyonlar�n hangisinin �a��rlaca�� compile time'da belli oluyor
        
    bir fonksiyon �a�r�s�n�n hangi fonksiyona ba�lanaca��(bind)
        a)derleme zaman�nda anla��l�yorsa
            pop�ler olarak static binding yada early binding deniliyor
        b)�al��ma zaman�nda anla��l�yorsa(inheritance konusunda g�r�lecek)RUN TIME POLYMORPHISM
            dynamic binding yada late binding deniliyor

    hoca bu konuyu ��renmeyi zorla�t�ran duruma de�iniyor
        function overloding var m� yok mu
            bu sorunun cevab� ya var ya yok tipik olarak kar��t�r�lan �u
            function overloading var bir fonksiyon �a�r�s� yap�lm�� o fonksiyon �a��r�syla biz birden fazla ayn� isimli fonksiyondan hangisini �a��rm�� oluyoruz
            burdada function overlaod resolution devreye giriyor

    function overloadingin olmas� i�in gerekli ko�ullar
        1)fonksiyonlar�n isimlerinin ayn� olmas� gerek
        2)ayn� scopeta olmalar� gerek
        3)imzalar�n�n farkl� olmas� gerek
            int foo(int,int); // 2 parametre de�i�kene sahip olmas� imzaya dahil oluyor fonksiyonun geri d�n�� de�erinin int olmas� imzaya dahil de�il

    �zellikle function overloading olu�turmayan durumlar� iyi anlama�z gerekiyor e�er ayn� isimli fonksiyonlar var ve function overloading s�z konusu de�ilse
    ve ayn� scopetaysa 2 tane ihtimal var ya sentaks hatas� ikinci bir bildirim ayn� isimle ge�erli de�il yada re-decleration en �ok kar��t�r�lan noktalardan biride bu

    fonksiyonlar�n imzalar�da geri d�n�� de�eri t�rleride ayn�ysa re-decleration
        int foo(int);
        int foo(int);

    e�er imzalar ayn� geri d�n�� de�eri t�r� farkl�ysa sentaks hatas� olur
        int foo(int);
        double foo(int);

    sorular:
    1)
        int foo(int);
        int foo(const int); //re-decleration overloading de�il pointer yada referans olsayd� const overloading olurdu
        e�er function overloading olsayd� zaten derleyici her ikisinin de tan�m�n� yapt��m�zda sentaks hatas� vermezdi
    
        int foo(int)
        {
            return 1;
        }

        int foo(const int) // parametre pointer yada referans de�ilse bildirimsel bir fark olu�turmuyor
        {
            return 3;
        } 
    2)
        void foo(int* p)
        void foo(int* const p) // re-decleration asteriks operat�r�nden sonra burda parametre de�i�keninin kendisi const 
        foo(const int *p); e�er b�yle olsayd� pointer�n kendisi const oldu�u i�in function overloading olurdu
    
    3)
        void func(char);
        void func(signed char);
        void func(unsigned char); // 3 adet function overloading var bunlar�n hepsi ayr� t�rlerdir 

    4)
        typedef int Word;
        void foo(int);
        void foo(Word); // re-decleration

    5)
        void foo(int32_t);
        void foo(int); // derleyiciye g�re de�i�ir ��nk� int32_t ba�ka derleyicilerde hi� olmayadabilir ama varsa derleyiciye ba�l� bizim derleyicimizde int32_t int t�r�
        oldu�u i�in re-decleration

*/