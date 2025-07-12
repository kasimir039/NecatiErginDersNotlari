/*

	template<typename T>
	class Myclass{

	};

	template<typename T>
	class Nec{};

	int main()
	{
		Myclass<Nec<int> > mx; // modern C++ �ncesinde maximal munch kural�na tak�l�yordu burada tokenizing yapabilmesi i�in bo�luk b�rakmam�z gerekirdi
	}

bir s�n�f �ablonu art�k bir s�n�f olmuyor 

	template<typename T>
	class Myint{ // class template derleyicinin s�n�f kodu yazmas�n� sa�layacak bir kod

	};

	�RNEK:
		template<typename T>
		class Myint{
		public:
			Myint(T x);
			Myint& set(T x)
			{
				Myint y; // function template i�inde s�n�f ismini yal�n olarak kulland���m�z zaman derleyici bunu hangi specialization i�in instantiation yap�caksa o t�r olarak g�r�yor
							Myint<T> y; yazmak aras�nda bir fark olmuyor
			}
			T get()const;
		private:
			T mval;
		}

		template<typename T> 
		Myint<T>& Myint<T>::set(T val) // scope resolution operat�r�nden sonra art�k class scopetay�z gerek parametreyi yazd���m�z yer gerek fonksiyonun ana blo�u i�inde 
		{
			// yukar�daki ifadeye g�re Myint<T> x; demek Myint x demek aralar�nda hi� bir fark olmuyor

			D�KKAT:fonksiyonun geri d�n�� de�erinin t�r�n� yazd���m�z yerde bu durum ge�erli de�il sadece bir istisna var oda ctorlar
				
				template<typename T>
				class Myint{
					public:
						Myint(int);
				};

				template <typename T>
				Myint<T>::Myint(int) // classs scope'a girdi�imizde s�n�f�n ismini yazmakla a��sal parantez i�inde template parametresini yazmak aras�nda burda fark var burada a��sal parantezi kullanmamak zorunday�z		
		}

		template<typename T> // SORU: T yerine U kullansayd�k yine ayn� anlama gelir miydi HAYIR GE�ERL� fonksiyonun tan�m�n� yaparken template parametresine 
								verdi�imiz ayn� ismi kullanmak zorunda de�iliz ama okunma amac�yla ayn� isim kullan�l�yor 
		T Myint<T>::get()const{
			return mval;
		}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CLASS TEMPLATELERDE INHERITANCE
	
	�RNEK: s�n�f �ablonunu olu�tururken �ablon olmayan bir taban s�n�ftan kal�t�m yoluyla elde edebiliriz
		class Base{};

		template <typename T>
		class Der: public Base{};

	�RNEK: �ablon olan bir taban s�n�ftan kal�t�m elde edebiliriz
		template <typename T>
		class Base{};

		class Der: public Base<int>{};

	�RNEK:
		template<typename T>
		class Base{};

		template <typename T>
		class Der: public Base<T>{};

		int main()
		{
			Der<int>; // Der'in int a��l�m�n�n taban s�n�f� Base'in int a��l�m� olacak
		}

	�RNEK:
		template<typename T>
		class Base{
			public:
				void foo();
		};

		class Der : public Base<int>{
			
			void bar()
			{
				foo(); // ge�erli
			}
		};	
		
		Der s�n�f� bir class template olsayd� bu sefer foo fonksiyonunu niteleyerek kullanmam�z gerekirdi

			template<typename T>
			class Base{
				public:
					void foo();
			};

			template<typename T>
			class Der : public Base<T>{ // 

			void bar()
			{
					foo(); // sentaks hatas� foo ismini niteleyerek kullanmal�y�z ��nk� T t�r�n�n ne oldu�u belli de�il Base<T>::foo();
				}
			};
		
	�RNEK:class templatelerde nested type'a sahip olabilir
		template<typename T>
		class Myclass{ // Myclass s�n�f� bir �ablon oldu�u i�in her instantiate i�in ayr� bir nested class var  
			public:
				class Nested{}; 
		};

		int main()
		{
			Myclass<int>::Nested
			Myclass<double>::Nested // ikiside farkl� t�rler
		}

	�RNEK:s�n�f�n i�inde nested type'� bildirip s�n�f�n d���ndada tan�m�n� yapabiliriz
		template<typename T>
		class Myclass{ 
			public:
				class Nested;
		};

		template<typename T>
		class Myclass<T>::Nested{

		};
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
NON-TYPE PARAMETRE
	template<int N>
	class Myclass{}; // bu s�n�f �ablonunun bir specializatiton'� i�in instantiation yapt�rd���m�zda derleyici compile time'da de�eri belli olan int t�rde bir de�er bekleyecek

	int main()
	{
		Myclass<5>
	}

	ayn� s�n�f i�in farkl� t�rden non-type parametrelerde kullanabilir miyiz? HAYIR SENTAKS HATASI fakat modern C++ ile dile yeni bir �zellik eklendi b�yle durumlarda 
	auto keyword�n� kullan�yoruz 
		template<int N>
		class Myclass{};

		template<long N> // sentaks hatas�
		class Myclass{}; 

		�RNEK:
			template<auto N> // hala non-type parameter bu ayr� bir deduction burada auto'yu kulland���m�z zaman s�n�f �ablonundan bir instantiate olu�turmak istersek
			struct Myclass		deduction olacak template arg�man� olarak kullan�lan constant expression ifadenin t�r� neyse o t�rden bir de�er kullanm�� olucaz
			{
				Myclass()
				{
					std::cout << typeid(N).name() << " " << N << '\n';
				}
			};

			int main()
			{
				Myclass<10> m1;
				Myclass<5u> m2;
				Myclass<4.5> m3; // C++20 ile legal hale geldi
			}

			�IKTI:
				int 10
				unsigned int 5
				double 4.5

	D�KKAT:
		template<int N> 
		struct Nec{};

		int main()
		{
			Nec<20> x;
			Nec<19> y; // ikiside birbirinden ayr� s�n�f
			Nec<10 + 5 + 4 +1> z; // ifadesini kullansayd�k bu ifadeninde de�eri 20 olaca�� i�in ayn� olmu� olur
		}
	
	D�KKAT:

		template<typename T, T x> // x'in t�r� burda non-type parameter typename anahtar kelimesini kullanmad�k
		class Myclass {
		public:
			void print() const {
				std::cout << "x = " << x << '\n';
			}
		};

		int main() 
		{
			Myclass<int, 42> obj;
			obj.print(); // x = 42

			Myclass<double, 4.5> obj2;
			obj2.print(); // x = 4.5
		}

	non-type parametrenin t�rleri
		
		1)tam say� t�rleri olabilir
			template <int N>
			class Myclass{};

		2)enum t�r� olabilir
			enum Color {blue,black,white};
			
			template <Color c>
			class Myclass{};

		3)pointer t�r� olabilir
			template<int *p>
			class Myclass{};

			D�KKAT: pointer olmas� durumunda template arg�man�na kar��l�k gelecek adresin static �m�rl� olmas� gerekiyor
			
				int main()
				{
					static int x = 5; 
					Myclass<&x> m;
				}
		4)referans t�r� olabilir
			template<int &r>
			class Myclass{};

			int g{};

			int main()
			{
				Myclass<g> m1;
			}

		5)function pointer olabilir
			template<int (*fp)(int)>
			class Myclass {
			public:
				void foo() {
					int x = fp(10);
				}
			};

			int f1(int x){}
			int f2(int x){}

			int main()
			{
				Myclass<f1> m1;

				m1.foo(); // foo fonksiyonu i�inde �a��r�lacak template arg�man� olan function pointer'�n g�sterdi�i fonksiyon olacak yani template arg�man�n non-type parametreye kar��l�k 
							 gelen template arg�man� bir free function'�n adresi olabilir
			}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MEMBER FUNCTION POINTER	

	s�n�flar�n static �ye fonksiyonlar�n�n this pointer� yoktu yani gizli parametreleri yok bu y�zden s�n�flar�n static �ye fonksiyonlar�n� g�stericek function 
	pointer t�rleri bildi�imiz C den gelen function pointer t�rleri

		class Myclass{
			public:
				static int foo(int);
		};

		int main()
		{
			int (*fptr)(int) = Myclass::foo;

			int x = fptr(20);  
		}

		e�er bu fonksiyon static �ye fonksiyon de�ilse art�k bu atamay� yapamay�z int (*fptr)(int) = Myclass::foo; bu iki t�r aras�nda uyumsuzluk var C de olmayan C++'da olan
		MEMBER FUNCTION DED���M�Z AYRI B�R T�R VAR

	�RNEK:
		class Myclass{
			public:
				 int foo(int);
		};

		int main()
		{
			int (Myclass::*fptr)(int) = Myclass::foo;
			Myclass m;

			(m.*fptr)(23); 
		}

	�RNEK:non-type parametreler member function pointer t�r�de olabilirler
		struct Myclass{
			int foo(int);
		};

		template<int (Myclass::*)(int)> 
		class Nec{

		};

		int main()
		{
			Nec<&Myclass::foo> mynec;
		}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
hoca non-type parametrelerde olan soruna de�iniyor
	template<const char* p>
	class Nec{
		public:
			void foo()
			{
				std::cout<<p;
			}
	};

	char s[] = "oguzhan esin"; ; // statik �m�rl� olmayan bir diziyi non-type arg�man olarak kullanamay�z global scopeta oldu�u i�in her hangi bir sentaks hatas� olmuyor
									ama main i�inde tan�mlasayd�k statik �m�rl� olmayaca�� i�in hata verecekti
	int main()
	{
		Nec<s> y;

		y.foo();

		Nec<"necati ergin"> x; // string literalini bu �ekilde kullanamay�z
	}
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
LEXICOGRAPHICAL COMPARE
	
	2 7 9 3
	2 7 6 6 9

	kar��l�kl� olarak her iki kaptaki ��eler kar��la�t�r�lacak ilk farkl� eleman �iftinde k���k olan k���kt�r buna g�re �sttekinde 9 alttakinde 6 oldu�u i�in �stte ki alttakinden b�y�k
	STL de bulunan b�t�n containerlar b�yle kar��la�t�r�l�yor

	�RNEK:
		int main()
		{
			std::vector<int> vx(100'00,1);
			std::vector<int> vy(2);

			std::cout<< vx.size() <<'\n';
			std::cout<< vy.size() <<'\n';

			if(vy > vx)
			{
				std::cout<<"do�ru \n";
			}
			else
			{
				std::cout<<"yanlis\n";
			}
		}

		container s�n�flar�n operator kar��la�t�rma fonksiyonlar� lexicographical compare yap�yor 

		�IKTI:
			10000
			2
			yanlis

	SORU: �yle bir less fonksiyonu yazaca��z ki �rne�in iki tane dizi i�in less fonksiyonunu less(a,b) �ekilnde �a��r�rsak lexicographical compare �eklinde true d�nd�r�cek
		template <typename T,int N,int M>
		constexpr bool Less(const T(&x)[N], const T(&y)[M])
		{
			for(int i = 0; i< N && i < M; ++i)
			{
				if(x[i] < y[i])
					return true;

				if(y[i] < x[i])
					return false;
			}

			return N < M;
		}

		int main()
		{
			int a[] = { 1, 5, 8};
			int b[] = { 1, 5, 8, 6, 8};

			Less(a,b)
		}
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPILICIT SPECIALIZATION(FULL SPECIALIZATION)
	
	belirli bir template arg�manlar� i�in zaten olu�turulmas� gereken specialization'�n kodunu sana veriyorum diyor intantiate etmek i�in kod yazmak yerine benim o t�r arg�manlar� 
	verdi�im kodu kullanacaks�n diyor
	
	template <typename T>
	T getmax(T x,T y)
	{
		return x > y ? x : y;
	}

	int main()
	{
		std::string x = "zeynep";
		std::string y = "fuat";

		std::cout<< getmax(x,y) << '\n'; // zeynep ��kt�s� al�n�r

		const char* x = "zeynep";
		const char* y = "fuat";
		
		std::cout<< getmax(x,y) << '\n'; // yaz�lar� de�il pointerlar� kar��la�t�rm�� oluyoruz ��kt� tamamen derleyiciye ba�l� 
	
		biz �unu istiyoruz e�er T t�r� const char* ise primary template'den bir instantiation yapmak yerine bizim verdi�imiz specialzation'� kullancaks�n diyece�iz i�te buna 
		EXPLICIT SPECIALIZATITN deniliyor
	}

	template<> // getmax'�n const char* t�r� i�in EXPLICIT SPECIALIZATION kullan�lacak
	conat char* getmax<const char* // buradaki a��sal parantez zorunlu de�il parametrelerden ��kar�m yap�labiliyor>(const char* p1,const char* p2)
	{
		return std::strcmp(p1,p2) > 0 ? p1 : p2; // art�k const char* kulland���m�z zaman adresler kar��la�t�r�lmaz yaz�lar kar��la�t�r�l�r ve do�ru ��kt�y� al�r�z
	}
	
	bizim verdi�imiz specialization'dan de�ilde derleyicinin instantiation yapaca�� ana template'den olu�ruulacak specializaiondan bahsediyorsak o template primary template deniliyor
		template <typename T>
		void foo(T){std::cout<<"primary template \n";}

		template<>
		void foo(int){std::cout<<"explicit specialization for foo(int)\n";}
		
		template<>
		void foo(double){std::cout<<"explicit specialization for foo(double)\n";}

		int main()
		{
			foo(34L); // primary template
			foo(3.4); // explicit specialization for foo(double)
		}

	meta function:compile timeda bir t�r yada bir de�er hesaplamak i�in kullan�lan koda meta function deniliyor meta function tipik olarak s�n�flarla ger�ekle�tiriliyor

	explicit specialization primary template ile ayn� interface'e sahip olmak zorunda de�il
		
		template<typename T>
		struct Myclass{
			Myclass()
			{
				std::cout<<"primary template\n";
			}
			void foo();
		};

		template<>
		struct Myclass<int>{
			Myclass()
			{
				std::cout<<"explicit specialization\n";

			}

			void bar();
			void baz();
		};

		int main()
		{
			Myclass<double> m1;
			m1.foo();
			Myclass<int> m2;

			m2.bar();
			m2.baz();
		}

		�IKTI:
			primary template
			explicit specialization

	�RNEK:template ile 0 dan 100 e kadar say� yazd�rmak
		template<int N>
		struct Print : Print<N -1>
		{
			Print()
			{
				std::cout<<N<< ' ' ;
			}
		};

		template<>
		struct Print< -1 > // template specialization ile recursion'u durdurduk
		{ 
		
		};
		
		int main()
		{
			Print<100> x;
		}

	�RNEK:explicit specialization'da ve partial specialization'da primary template'in complete type olmas� gerekmiyor

		template<typename>
		class Nec;

		template<>
		class Nec<int>
		{
			public:
				Nec()
				{
					std::cout<<"int spec\n";
				}
		}


		int main()
		{
			Nec<int> x;
			Nec<double> y; // primary template incomplete type oldu�u i�in bu sentaks hatas� 
		}

	�RNEK:fonksiyonlar�n explicit specialization'� oldu�unda anlamam�z gereken �ok �nemli bir yer
		function overload resolution'a her zaman primary template girer
			
			template<typename T>
			void func(T)
			{
				std::cout<<"primary\n"; // SORU: function overload resolution'� primary template kazan�rsa template parametresi kar��l��� kullan�lmas� gereken template arg�man�
												 �rne�in int* olursa derleyici bir instantiaton yapacak bu instantion'� explicit specialization'dan yap�yor
			}

			template<>
			void func(int*)
			{
				std::cout<<"int*\n";
			}	
			
			template<typename T>
			void func(T*)
			{
				std::cout<<"T*\n";
			}

			int main()
			{
				int* p = nullptr;

				func(p); // burda partial ordering rules kurallar� ge�erli buna g�re daha spesifik olan parametre kazanacak yani T* ��kt�s� al�n�r

			}
		
			SORU: T* ile int* parametreli func fonksiyonlar�n�n yerini de�i�tirirsek ne olur?
				template<typename T>
				void func(T)
				{
					std::cout<<"primary\n"; 
				}

				template<typename T>
				void func(T*)
				{
					std::cout<<"T*\n";
				}

				template<>
				void func(int*)
				{
					std::cout<<"int*\n"; // bu explicit specialization art�k T* parametreli template'in explicit specialization'�
											function overlaod resolutin T ve T* t�rleri aras�nda yap�lacak T* kazanacak instantiation'� explicit specialization'dan yapt��� i�in
											int* ��kt�s� al�n�r
				}

				int main()
				{
					int* p = nullptr;

					func(p);

				}
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PARTIAL SPECIALIZATION
	t�m template arg�manlar� k�mesi i�inde belirli nitelikteklere sahip t�rler i�in verilen specialization ve fonksiyon �ablonlar�nda partial specialization yok 
	class templatelerde ve value templatelerde var

	template<typename T>
	struct Myclass{
		Myclass()
		{
			std::cout<<"primary template\n";
		}
	};

	template <typename T> // ayn� say�da parametre olmas�na gerek yok daha fazlada olabilir
	struct Myclass<T*> { // template arg�man�n�n bir pointer t�r� olmas� durumunda partial specialization kullan�lacak
		Myclass()
		{
			std::cout<<"partial specialization\n";

		}
	}; 

	int main()
	{
		Myclass<int>m1;
		Myclass<double>m2;
		Myclass<int* >m3;
		Myclass<int** >m4;
	}
	
	�IKTI:
		primary template
		primary template
		partial specialization
		partial specialization

	�RNEK:
		template<typename T>
		struct Myclass{
			Myclass()
			{
				std::cout<<"primary template\n";
			}
		};

		template <typename T>
		struct Myclass<T,T>
		{
			Myclass()
			{
				std::cout<<"partial specialization\n";
			}
		};

		int main()
		{
			Myclass<int,double> m1; // primary
			Myclass<double,double> m2; // partial
		}

	�RNEK:
		template<typename T>
		struct Myclass{
			Myclass()
			{
				std::cout<<"primary template\n";
			}
		};

		template <typename T>
		struct Myclass<T,int> // 1.template parametresi ne olursa olsun 2.template parametresi int parametreyse partial specialization kullan�lacak 
		{
			Myclass()
			{
				std::cout<<"partial specialization\n";
			}
		};

		int main()
		{
			Myclass<double,long> m1; // primary
			Myclass<double,int> m2; // partial
		}
*/