/*

template konusundan devam ediyoruz

derleyiciler template koda ili�kin sentaks kontrol�n� bir ka� farkl� a�amada yap�yorlar
	
	1)template kod kullan�lmadan template'in kendisi �st�nde yap�l�yor

		template<typename T>
		void func(T x)
		{
			++x;
			
			x = 5; // T t�r�n�n ne oldu�unun bilinmemesine kar��n yinede sentaks hatas� vermiyor

			// foo(x); // foo fonksiyonu olmamas�na ra�men burada sentaks hatas� hala yok ��nk� T t�r�n�n ne oldu�una ba�l� olarak foo ismi ADL ile
						  aranabilir 
			
			//	bar(19); // template parametresine kar��l�k gelen template arg�man�n�n ne oldu�una ba�l� olmad��� i�in burada sentaks hatas� olur
		}

	2)template argument deduction s�z konusuysa deduction'�n yap�lamama ihtimali var bu durumda template parametrelerine kar��l�k gelen template arg�man�n�n ne oldu�u
	anla��lamad�ysa sentaks hatas� olur

		template <typename T>
		T func();
		
		int main()
		{
			func(); // burda derleyicinin T t�r�n�n ne oldu�unu anlama �ans� yok deduction ba�ar�s�z oldu�u i�in derleyici sentaks hatas� verecek 
		}

	3)argument deduction'�n yap�lamamas�n�n nedeni ambiguity olmas�
		
		template <typename T>
		void func(T x,T y); // fonksiyonun parametresine CALL PARAMETER deniliyor

		int main()
		{
			func(10,20); // fonksiyonu b�yle �a��r�rsak 1.arg�mandan template'in 1.parametresine yap�lacak kopyalama i�in arg�man�n t�r� int oldu�u i�in fonksiyonun parametresinin t�r�n�n 
							int t�r� olmas� gerekiyor

			// func(10,2.0); // 2.parametreyi double yapsayd�k burada bir belirsizlik olaca�� i�in ambiguity hatas� olacakt�
		}

TEMPLATE ARGUMENT DEDUCTION NASIL YAPILIYOR
	
	bir istisna haricinde auto type deduction ile temple argument deduction aras�nda kural a��s�ndan hi� bir fark yok

	t�rlerin ne oldu�unu ��renmemiz i�in bir trick var

	template <typename T>
	class TypeTeller;

	template <typename T>
	void func(T)
	{
		TypeTeller<T> x;
	}
	int main()
	{
		int x = 5;

		func(x); // 'x' uses undefined class 'TypeTeller<int>'

	} 

	�RNEK:
		template <typename T>
		void func(T)
		{
			TypeTeller<T> x;
		}

		int main()
		{

			int y[5];

			func(y) // array decay uygulan�r T t�r� int*

			const int y[5];
			
			func(y); // burda constluk d��m�yor T t�r� const int*
		}

	�RNEK:
		template <typename T>
		void func(T&)
		{
			TypeTeller<T> x;
		}

		int main()
		{
			const int x = 5;

			func(x); // T t�r� const int ��nk� referans declerat�r� oldu�u i�in constluk d��m�yor

		}

	�RNEK:
		template <typename T>
		void func(T&)
		{
			TypeTeller<T> x;
		}

		int main()
		{
		
			int a[5]{};
			func(a); // referans deklerat�r� oldu�u i�in array decay uygulanm�yor T t�r� int[5] 

			derleyicinin yazd��� func fonksiyonun parametresi ��yle olacak void func(int(&r)[5]
		}

	�RNEK:
		template <typename T>
		void func(T&)
		{
			TypeTeller<T> x;
		}

		int foo(int);

		int main()
		{
			func(foo); // referans deklerat�r� oldu�u i�in T i�in yap�lan ��kar�m int(int)
			
			derleyicinin yazd��� func fonksiyonun parametresi ��yle olacak void func(int (&) (int))
		}

	 �RNEK:
		template <typename T>
		void func(T&)
		{
			TypeTeller<T> x;
		}

		int main()
		{
			func("alican"); // referans deklerat�r� oldu�u i�in T t�r� i�in yap�lan ��kar�m const char[7]
		}

	�RNEK:
		template <typename T>
		void foo(T,T);

		template <typename T>
		void bar(T&,T&);

		int main()
		{
			foo("veli","bayar"); // T i�in yap�lan ��kar�m const char*
			bar("veli","bayar"); // veli yaz�s� i�in T t�r�n�n ��kar�m� -> const char[5] oldu�u i�in bayar yaz�s� i�in T t�r� -> const char[6] olamaz burda ambiguity s�z konusu 
									bu y�zden sentaks hatas�
		}

	�RNEK:
		template <typename T>
		void foo(T,T&);

		int main()
		{
			int a[5]{};

			foo(a,a); // 1.parametre i�in yap�lan ��kar�m -> int* 2.parametre i�in yap�lan ��kar�m -> int[5] ambiguity s�z konusu oldu�u i�in sentaks hatas�
		}

	�RNEK: template functionlarda ba��nda const veya volatile anahtar kelimeleri yoksa bu UNIVERSAL REFERENCE
			burda T i�in yap�lan ��kar�m g�nderilen arg�man�n value kategorisine ba�l�
			
			g�nderilen arg�man L value ise T i�in yap�lan ��kar�m -> T&
			g�nderilen arg�man R value ise T i�in yap�lan ��kar�m -> T

		1.SENARYO:
			template <typename T>
			void foo(T&&);
			
			int main()
			{
				foo(12); // T i�in yap�lan ��kar�m int

				int x = 230;
				foo(x); // T i�in yap�lan ��kar�m int&

				T i�in yap�lan ��kar�m int& oldu�unda C++ dilinde referansa referanse olmad��� i�in reference collapsing kurallar� uygulan�yordu

					T& & -> T&
					T& && -> T&
					T&& & -> T&
					T&& && -> T&&  
			}

			template <typename T>
			void foo(T&& x)
			{
				// T y; // mainde T i�in yap�lan ��kar�m int& oldu�u i�in sentaks hatas� ��nk� referanslar default initalize edilemezler
				T y = x; // T i�in yap�lan ��kar�m int& x bir isim oldu�u i�in L value yani L value bir de�eri L value'ya ba�lam�� oluyoruz bu y�zden ge�erli
			}

			int main()
			{
				int x = 230;
				foo(x);
			}

		2.SENARYO
			template <typename T>
			void foo(T&&);

			int main()
			{
				foo(10); // T i�in yap�lan ��kar�m int yani fonksiyonun parametre de�i�keninin t�r� T&& olur
			}


			template <typename T>
			void foo(T&&)
			{
				T x; // bu sefer sentaks hatas� yok ��nk� main'de T i�in yap�lan ��kar�m int
			}

			int main()
			{
				foo(10);
			}

		�RNEK:
			template <typename T>
			void foo(T&&, T);

			int main()
			{
				int x = 10;
				
				foo(x,x); // T i�in yap�lan ��kar�mlar s�ras�yla -> int&,int sentaks hatas�
				foo(5,x); // T i�in yap�lan ��kar�mlar s�ras�yla -> int,int ge�erli
				foo(5,5);  // T i�in yap�lan ��kar�mlar s�ras�yla -> int,int ge�erli
			}

		�RNEK:
			template <typename T>
			void foo(T&&, T&);

			int main()
			{
				int x = 10;

				foo(x,x); // T i�in yap�lan ��kar�mlar s�ras�yla -> int&,int sentaks hatas�
				foo(19,x) // T i�in yap�lan ��kar�mlar s�ras�yla -> int,int	
			}

		�RNEK:
			template <typename T>
			void foo(T*);

			int main()
			{
				int x{};
				foo(&x); // T i�in yap�lan ��kar�m int

				int* ptr = &x;
				foo(&ptr); // T i�in yap�lan ��kar�m int*
			}	

		�RNEK:
			template <typename T>
			void foo(T**);

			int main()
			{
				int x{};
				
				int* ptr = &x;
				int** p = &ptr;

				foo(p); // T i�in yap�lan ��kar�m int
				foo(&p); // T i�in yap�lan ��kar�m int*
			}

		�RNEK:
			template <typename T>
			void foo(T);

			int main()
			{
				int x{};
				int* ptr = &x;

				foo(&x); T -> int*
				foo(&ptr); T -> int**
			}
		
		�RNEK:
			template <typename T, int N>
			void foo(T(&)[N]) // T t�r�nden N elemanl� bir diziye referans
			{

			}

			int main()
			{
				int a[20]{};

				foo(a); // int[20];
			}

			dizinin boyutunu derleme zaman�nda elde etmek i�in 
				template <typename T, int N>
				constexpr int asize(T(&)[N])
				{
					return N;
				}

				int main()
				{
					int a[5]{};

					constexpr auto size = asize(a); // 5
				}

	hoca kendi kendine function templateleri ��renenlerin yapt��� hatalara de�iniyor
		
		template <typename T>
		void foo(T)
		{
			std::cout << typeid(T).name() << '\n';
		}

		int main()
		{
			foo(1.2); 
			foo(12);
			foo('A');

			derleyici her t�r i�in farkl� fonksiyon yazar

			�IKTI:
				double
				int
				char

				foo(1.2);
				foo<double>(12);
				foo<double>('A'); // explicit bir �ekilde t�r�n� yazarsak bu sefer sadece tek bir fonksiyon olmu� olacak
		}

	�RNEK:b�t�n parametreler template parametresine ba�l� bir t�r olmak zorunda de�iller

		template <typename T>
		void foo(T x,int y,std::string);

	�yle fonksiyon �ablonlar� var ki ��kar�m yapmak m�mk�n olmad��� i�in bir yada birden fazla template parametresi i�in explicit template arg�man� kullanmak zorunda kalabiliriz

		EXPLICIT TEMPLATE ARGUMANLARI
			a)��kar�m s�z konusu de�ilse yani ��kar�m yap�lma imkan� yoksa
				
				template <typename T>
				T foo(); // fonksiyonun geri d�n�� de�eri t�r� T dolay�s�yla T t�r�n�n ��kar�m�n�n yap�lmas�n�n imkan� yok

				int main()
				{
					foo<int>();
				}
			
			b)��kar�m yapma imkan� var ama biz ��kar�m yapmas�n� istemiyoruz
			 
		�RNEK:birden fazla template parametreleri olabilir ve farkl� template parametresine kar��l�k gelen template arg�manlar� ayn� t�r olabilirler

			template <typename T,typename U>
			void foo(T,U);

			int main()
			{
				foo(2,5); // T ve U i�in yap�lan ��kar�m int
				foo<int,int>(2,5); // bu fonksiyonu b�yle �a��rmak demek �stte ki fonksiyonu �a��rmak demek
			}

		SORU: birden fazla template parametresi oldu�unda b�t�n template parametrelerini de�ilde sadece bir k�sm�n� explicit olarak yazmak m�mk�n m�? EVET
			
			template <typename T,typename U>
			void foo(T,U);

			int main()
			{
				foo(2,5);
				foo<int>('A',5.6); // 1.template parametresine char arrg�man� g�ndermemize ra�men 1.template parametresi kar��l��� kullan�lacak olan template arg�man�n�n int oldu�unu 
									s�yledi�imiz i�in ��kar�m yap�lmayacak ama 2.template parametresi i�in explicit template arg�man� kullanmad���m�z i�in ��kar�m yap�lacak 
									derleyicinin yazaca�� fonksiyon T t�r�n�n-> int U t�r�n�n-> double t�r�nden oldu�u fonksiyon olacak
			}

	standart k�t�phanede ve 3.parti k�t�phanelerde �ok s�k rastlanan senaryolardan biri fonksiyon �ablonunun kodu i�inde fonksiyon parametresinin
	function call operat�r�n�n operand� olmas�

		template <typename T>
		void foo(T f)
		{
			f(10); // pop�ler olarak CALLABLE deniliyor yani fonksiyon �a�r� operat�r�n�n operand� olabilen varl�klar
		}

		void bar(int x)
		{
			std::cout << "bar: x = " << x <<'\n';
		}

		int main()
		{
			foo(bar); // derleyicinin yapt��� ��kar�m T t�r� void(*)int olacakt� bar fonksiyonun adresini function poiner'a g�ndermi� olacakt�k bu durumda function
						 pointer'�n g�stermi� oldu�u fonksiyon �a��r�lm�� olacakt�
		}

		�IKTI:
		bar: x = 10
		
		CALLABLE illa ki bir fonksiyon adresi olmak zorunda de�il
			template <typename T>
			void foo(T f)
			{
				std::cout<<f(10);
			}	

			class Myclass{
				public:
					int operator()(int x) // function call operat�r�n� overload eden s�n�flara functor class deniliyordu ��nk� nesne gibi g�r�n�p fonksiyon gibi davranabiliyorlard�
					{
						return x;
					} 
			 };

			 int main()
			 {
				Myclass m;
				foo(m);
			 }
			 
			 �IKTI: 10;
			 
			 callable'lar generic kodlarda yo�un olarak kullan�l�yor
	

	�RNEK: fonksiyonun geri d�n�� de�erinin farkl� t�rden olmas� girilen arg�manlara g�re veri kayb� olmamas� i�in �rnek
	
		template<typename Result,typename T,typename U>
		Result sum(T x,U y)
		{
			return x + y;
		}

		int main()
		{
			auto val = sum<double>(5.7,3); // fonksiyonun geri d�n�� de�erinin ne olaca��n�n saptam�s�n� fonksiyonu �a��ran koda verdik Result'�n geri d�n�� de�eri t�r�n� explicit olarak 
											  belirtiyoruz -> double
		}

		C++ sentaks� fonksiyonlar�n geri d�n�� de�eri t�rleri i�in 2 tane farkl� ara� sunuyor
			1)trailing return type
				fonksiyonun geri d�n�� de�eri t�r� yerine auto keyword�n� kullan�yoruz 

				auto foo() -> int {} // int foo yazmaya e� de�er

				hoca main fonksiyonunda s�rf ilgin�lik olsun diye trailing return type kullananlara g�c�k oluyormu� :D
					auto main() -> int {}

				normal fonksiyonlarda trailing return type kullan�lmas�n� tercih edebilece�imiz bir durum var
					fonksiyonlar�n geri d�n�� de�eri function pointer olabilir
						int bar(int) 
						{
							return 5;
						}

						int (*foo(int (*fp)(int)))(int)
						{
							return fp;
						}

						int main()
						{
							auto f = foo(&bar);
						}

					yaz�m� kolayla�t�rmak i�in type alias kullan�yoruz
						using fptr = int (*)(int);

						fptr foo(fptr fp)
						{
							return bar;
						}
					
					ama b�yle yazmak yerine trailing return type kullanarak yazarsak
						auto foo() -> int (*)(int){} 

						auto foo() -> int (&)[5]{}

			�RNEK:�yle bir fonksiyon olsun ki bu fonksiyonn geri d�n�� de�eri t�r� x + y ifadesinden hangi t�r elde ediliyorsa o t�r olsun
				template <typename T,typename U>
				auto foo(T x,U y) -> decltype(x + y){}

		2)auto return type
			
			template<typename T,typename U>
			auto foo(T x,U y)
			{
				return x + y; // fonksiyonun geri d�n�� de�eri t�r� x + y ifadesinin t�r� olacak
			}

	auto type deduction ile template argument deductionda sentaks a��s�ndan ilgin� bir farkl�l�k var
		
		auto x = {2,5,6,8}; // auto i�in yap�lan ��kar�m initalizer list s�n�f �ablonunun int a��l�m�

		template <typename T>
			void foo(T);

		int main()
		{
			foo({2,5,6,8}); // burda initalizer list ��kar�m� yap�lm�yor explicit �ekilde yazmam�z gerekir
		}

	t�r ��kar�m� daha karma��kta olabilir

		template<typename T,typename U>
		void foo(T (*fp) (U))
		{
			T x; // int
			U y; // double
		}

		int bar(double);

		int main()
		{
			foo(bar); // int (*)double
			}
	
	fonksiyon �ablonlar�yla ayn� isimli fonksiyonlar bir arada bulunabilir 
		template<typename T>
		void foo(T)
		{
			std::cout<<1function template " << typeid(T).name()<<'\n';
		}

		void foo(int)
		{
			std::cout<<"void func(int)\n";
		}

		buda bir overloading bi�imi bu durumda dilin kurallar� biraz farkl�: e�er fonksiyon �a�r�s�nda kullan�lan arg�man ger�ek fonksiyonun parametresiyle tam uyu�uyorsa derleyici
		fonksiyon �ablonundan bir fonksiyon yazmayacak

		int main()
		{
			foo(4.5); // function template overload resolution s�recinde derleyicinin template'ten olu�turdu�u specialization se�ilir void foo<double>(double)
			foo(4u); // function template
			foo(4); // void func(int)
			foo('A'); // function template

			ger�ek fonksiyon parametresiyle tam uyum sa�larsa ger�ek fonksiyon se�ilir aksi halde template se�iliyor 
		}

	M�LAKAT SORUSU: �yle bir fonksiyon olsun ki sadece parametre de�i�keninin t�r�nden arg�man kabul etsin onun d���ndakiler sentaks hatas� olsun

		template<typename T>
		void foo(T) = delete;

		void foo(int){}

		int main()
		{
			// foo(4.5); // sentaks hatas� sadece int parametreli fonksiyon �a��r�labilir
			   foo(4); // ge�erli
		}

	function template ve template function ayn� anlama geliyor baz� programc�lar bunlar� ayr� anlamlar i�in kullanabiliyormu� ama bir fark� yok

	SORU: fonksiyon �ablonlar� ayn� isimde olabilir mi? EVET

		template <typename T>
		void foo(T);

		template <typename T>
		void foo(T,T);

		template <typename T,typename U>
		void foo(T,U);

			�RNEK:
				template <typename T>
				void foo(T)
				{
					std::cout<<"foo(T) " << typeid(T).name() <<'\n';
				}

				template<typename T>
				void foo(T x,T y)
				{
					std::cout<<"foo(T,T)" << typeid(T).name() << '\n';
					foo(x); 
					foo(y);
				}

				int main()
				{
					foo(12,56);
				}

				SORU: istersek void foo(T x,T y) template'inden ba�ka bir t�r arg�man�yla yeni bir fonksiyon yaz�lma�n� sa�layabilir miydik? EVET

	�RNEK: programc�lar�n en �ok kafas�n� kar��t�ran ve zor konulardan biri E�ER FONKS�YON �A�RISI �K� AYRI TEMPLAT'E B�RDEN UYUYORSA NE OLACAK?
		
		template<typename T>
		void foo(T)
		{
			std::cout<<"foo(T)\n";
		}

		template<typename T>
		void foo(T*)
		{
			std::cout<<"foo(T*)\n";
		}

		int main()
		{
			// foo(12) // T t�r�nden olan template �a��r�l�r

			int x = 10;

			// foo(&x); // T* t�r�nden template olmasa T t�r�nden olan template kullan�labilirdi bu durumda T t�r� int* olurdu 
						   ama T t�r�nden olan template olmasayd� T* t�r�nden olan template'in t�r� int olurdu

			SORU:peki b�yle bir durumda ikisi birden oldu�unda her iki template'den specialization olu�turabilece�ine g�re derleyici nas�l bir karar verecek?
				
				burda uygulanan kurallara PARTIAL ORDERING RULES deniliyor

					parametresi en spesifik olan se�ilecek demek yani foo(&x) ifadesine g�re T* T t�r�ne g�re daha spesifik oldu�una g�re T* t�r�nden parametresi olan template se�ilecek
					
					yani e�er templatelerden biri di�erinin kabul etti�i b�t�n arg�manlar� kabul ediyorsa fakat di�erinin kabul etmed�i arg�manlar�da kabul ediyorsa o zaman daha az spesifik
					
					ve �unuda diyebiliriz genelden daha �ok �zele hitap eden bir parametresi varsa o parametreye g�re se�ilme olasl��� daha fazla olur
		}
*/