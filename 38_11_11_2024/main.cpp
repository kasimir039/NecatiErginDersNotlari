/*

LOCAL CLASS

	bir fonksiyon i�inde local class tan�mlayabiliriz

	�RNEK:
		void foo()
		{
			int x = 5; 

			class Nec{
			
				void func()
				{
					auto val = x; // ge�ersiz x static olsayd� ge�erli olacakt�
				} 

			};
		}

	�RNEK:
		
		void foo(int x) 
		{

		class Nec {

			void func()
			{
				auto val = x; // ge�ersiz parametre de�i�keninide kullanamay�z
			}

			};
		}

	�RNEK:
		
		int g = 10;

		void foo()
		{

			class Nec{
			
				void func()
				{
					auto val = g; // ge�erli
				}

			};
		}	
		
	�RNEK:
	
		void foo()
		{

			static int ival = 7;

			class Nec{

				void func()
				{
					auto val = ival; // ge�erli
				}

			};
		}

	�RNEK:local class t�r�nden nesneler modern C++'dan �nce templatelere arg�man olarak g�nderilemiyordu

		template<typenae T>
		void foo(T x){}

		void foo(int a){
			class Nec{
				void foo()
				{

				}
			}
			foo(Nec{}); // eski C++'da legal de�il legal yap�lmas�n�n amac� lambdalar ��nk� lambda ifadelerini fonksiyon �ablonlar�na ve �zellikle STL algoritmalar�na 
						   arg�man olarak lambda ifadelerinin ge�ilmesi

		}

LAMBDALARDAN DEVAM 

	modern C++'�n her standart�yla yeni ara�lar ekleniyor ya da daha �nce olan k�s�tlamalar kald�r�ld� 

	lambda ifadelerine baz� programc�lar lambda function diyor

	[] -> lambda introducer deniliyor i�ine yazd���m�z ifadelere capture close yada capture expression deniliyor
	[]() -> burda ki parantez derleyiciye yazd�rd��m�z s�n�f�n fonksiyon �a�r� operat�r fonksiyonunun parantezi 
	[](){} -> s�sl� parantez ise derleyicinin ana blo�u


	�RNEK:
		
		class Myclass
		{
			auto operator()(int x)const // fonksiyonun geri d�n�� de�eri t�r�n� return ifadesinden ��kar�m yoluyla elde ediyor
			{						  derleyicinin yazd��� fonksiyon �a�r� operat�r foksiyonu default olarak CONST MEMBER FUNCTION
				return x* x;
			}
		};

		int main()
		{
			[](int x) { return x * x; }; // derleyici b�yle bir lambda ifadesine kar��l�k yukar�da ki gibi bir s�n�f yaz�yor
			
			// Myclass{}(5) bunu b�yle �a��rmakla -> [](int x) { return x * x; }(5); b�yle �a��rmak aras�nda hi� bir fark yok bu �ekilde kullan�lan lambda ifadelerine
			   IIFE(Immediately Involved Function Expression) idiyomu deniliyor
		}	


	�RNEK:lambda ifadesini isimlendirilmi� bir closure objecte d�n��t�rebiliriz peki bunun faydas� ne?

		1)fonksiyonu birden fazla kez kullanmak isteyebiliriz
			int main()
			{
				const auto f = [](int x) { return x * x + 5; }; // const correctness'a dikkat etmemizde gerekir

				auto i1 = f(123);
				
				auto i2 = f(4);
			}

		2)kodun g�rsel karma��kl���n� azaltmak i�in olabilir

	
	closure typelar'�n copy ctoru var

		int main()
		{
		 auto f1 = [](int x) { return x * x + 5; };
		 auto f2 = f1; // f1 ve f2'nin t�r� burada ayn� ��nk� copy ctor ile ilk de�er verdik
		}
			
		D�KKAT: lambda ifadelerinin birebir ayn� olmas� ayn� t�rler oldu�u anlam�na gelmiyor derleyici her bir t�r i�in farkl� bir closure type tan�ml�yor
		
			int main()
			{
				 auto f1 = [](int x) { return x * x + 5; }; 
				 auto f2 = [](int x) { return x * x + 5; }; 
			
				constexpr auto b = std::is_same_v<decltype(f1), decltype(f2)>; // false
			}
		
	C++20 ile de�i�en bir kural var 

		int main()
		{
			 auto f1 = [](int x) { return x * x + 5; };
			 
			 decltype(f1) f2; // bu kod C++20'de ge�erli C++17'de ge�erli de�il
			auto f2 = f1; // C++17'de de ge�erli

			f1 = f2; // copy assignment deleted C++17'de ge�ersiz
		}

		C++17'de closure type'lar�n
			a)default ctor
			b)copy assignment ctor delete edilmi� durumda

		c++20 standard�nda stateless lambda'lar�n default ctoru ve copy assignment'� art�k delete edilmi� de�il

	SORU:fonksiyonlar�n geri d�n�� de�eri t�r� closure type olabilir mi? EVET

		foo(int x)
		{
			return [](int a) { return a * a - 12; };
		}

		bu ifadeyi fonksiyonun geri d�n�� de�eri yapmak i�in en az 2 ayr� ara� var
			1)auto return type
				auto foo(int x)
				{
					return [](int a) { return a * a - 12; };
				}
			2)her hangi bir callable'� sarmalayan std::function(ileride g�rece�iz)
				std::function<int(int)> foo(int x)
				{
					return [](int a) { return a * a - 12; };
				}			

	�RNEK: closure typelar kal�t�mda base class olarakta kullan�labilir

			auto f1 = [](int x) { return x * x; };
			auto f2 = [](int x) { return x + x; };

			class Myclass : public decltype(f1) , public decltype(f2) {};


	�RNEK: �yle bir fonksiyon yazmak istiyoruz ki fonksiyonumuzun yapt��� i� parametre de�i�kenine gelen arg�manla x'in �arp�m�n�n olu�turdu�u de�eri d�nd�rmek

		int main()
		{
			int x = 5;

			[](int a) { return x * a; }; // local claas oldu�u i�in x burda visible olmuyor 
		}

		 bunu ger�ekle�tirebilmek i�in COPY CAPTURE kullanmam�z gerekiyor
			
			int main()
			{
				int x = 5;

				[x](int a) { return x * a; }; // buraya x'i yazd���m�z zaman derleyiciye ��yle bir talimat veriyoruz
			}									 derleyici closure type'� olu�tururken s�n�fa bir veri eleman� koy veri eleman� ilk de�erini x'den als�n
												 fonksiyonun kodunda x ismini kulland���m�z zaman asl�nda s�n�f�n veri eleman�n� kullanm�� olucaz
		
	�RNEK:e�er bir s�n�f yaz�p kendimiz ayn� i�lemi yapmak isteseydik 
			
		class nec_26_54{
			public:
				nec_26_54(int x) : mx(x) {}

				auto operator()(int x) const { return mx * x; }

			private:
				int mx;
		};

		int main()
		{
			int x = 5;

			nec_26_54{x}(45);
		}

	D�KKAT:birden fazla isim olsayd� comma separated list kullanmam�z gerekirdi -> [x,y](int a) { return x * a * y; };
		   ama bunun kestirme bir yolu var -> [=] CAPTURE ALL VISIBLE LOCAL VARIABLES BY COPY

		   int main()
		   {
				[=] // 
					   
				int x = 5;
				int y = 7;

				[=]{ 
				
				 // isimleri tek tek yazmak yerine g�r�n�r her ismi lambda fonksiyonu i�inde kullanmak istiyorsak bunu kullan�yoruz ama hoca �o�unlukla �nermedi�ini 
					s�yl�yor ��nk� �rne�in y'yi kullanmak istemedi�imiz halde yanl��l�kla burda kullanma ihtimalimiz var 
				
				};
		   }

		   �RNEK:

				void func(int a,int b)
				{
					// auto f = [=](int x) { return x + (a * b); };
					// auto f = [a,b](int x) { return x + (a * b); };

					her iki �ekilde de kullanabiliriz
				}

	D�KKAT:t�m statik �m�rl� de�i�kenler capture edilemez
			
		int g = 5;
		int foo(int) {

			return 1;
		}

		int main()
		{
			auto f = [g] {return foo(g); }; // sentaks hatas�
		}

	�RNEK: derleyicinin �retti�i fonksiyon �a�r� operat�r fonksiyonu default olarak const member function oldu�u i�in sentaks hatas� olur

		int main()
		{
			std::string name {"hasan"};
			int x = 7;

			auto f = [x,name](int val)
			{
				x+= val;
				name += "can"; // ikiside sentaks hatas� ��nk� fonksiyon �a�r� operat�r� const member function
			};
		}

		D�KKAT: s�n�f�n veri eleman�n� �ye fonksiyon i�inde de�i�tirmek istiyorsak mutable anahtar kelimesini kullanmam�z gerekir
			int main()
			{
				std::string name {"hasan"};
				int x = 5;

				auto f = [x,name](int val) mutable 
				{
					x+= val; // D�KKAT burda asl�nda s�n�f�n veri eleman� olan x'i de�i�tirmi� oluyoruz bu x'i de�il 
					name += "can"; // mutable anahtar kelimesini kulland���m�z i�in her ikiside ge�erli olur s�n�f�n veri elemanlar� non-const member function olmu� olur  
				}

				f(12);

				std::cout << x; // 5 local olan x de�eri buda de�i�miyor

			}

		D�KKAT: ama� yukardaki x gibi local bir de�i�kenin de�erini de�i�tirmek olsayd� 
			
			int main()
			{
				std::string name{ "hasan" };
				int x = 5;

				auto f = [&x](int& val) // referans deklerat�r�n� kullan�yoruz
					{
						x += val;
					};

				f(x); // D�KKAT bu fonksiyon �a�r�s� olmadan x'in de�eri zaten de�i�meyecekti

				std::cout << x; // x + x = 10
			}
			
	[a,b,c] -> a,b,c kopyalama yoluyla al�n�r
	[=] -> hepsi kopyalama yoluyla al�n�r

	[&x] -> referans yoluyla al�n�r
	[&x,y] -> x referans yoluyla al�n�r y kopyalama ile al�n�r
	[&] -> hepsi referans yoluyla al�n�r
	[=, &a] -> hepsi kopyalama yoluyla al�n�r ama a referans yoluyla al�n�r
	[&,x] -> hepsi referans yoluyla al�n�r ama x kopyalama yoluyla al�n�r

	[&&] -> ge�ersiz

	�RNEK:parametre paketlerinide capture edebiliriz

		template<typename ...Ts>
		auto func(Ts ...args)
		{
			auto f = [args...]()
				{
					return (... + args);
				};

			return f() + 100;
		}

		int main()
		{
			std::cout<<func(5); // 105
		}

	stateless lambda -> capture etmez []
	stateful lambda -> bir yada birden fazla varl��� capture eder [x,y,z]

	�RNEK: stateless lambdalar i�in derleyici olu�turdu�u closure type i�in type cast operator fonksiyonu yaz�yor
		   lambda'n�n kendi t�r�nden bir fonksiyon adresi t�r�ne type cast operat�r� yaz�yor 

		int main()
		{
			[](int a){ return a * a; }; // �rne�in parametresi int olan geri d�n�� de�eri t�r� int olan bir fonksiyon adresi t�r�ne int(*)(int)
		}

		yani elimizde bir stateless lambda varsa onu do�rudan sanki bir fonksiyon adresiymi� gibi bizden fonksiyon adresi isteyen herhangi bir fonksiyona arg�man olarak g�nderebiliriz
		yada bir function pointer variable'� initalize etmek i�in yada atama yapmak i�in kullanabiliriz

			int main()
			{
				int(*fp)(int) = [](int a){ return a * a; }; 

				auto val = fp(12);

				std::cout<<val; // 144
			}
	
POSITIVE LAMBDA IDIOM
	
	function poniter type sign operat�r� +'n�n operand� olabiliyor

	int foo(int){};

	int main()
	{
		int(*fp)(int) = &foo;
		+fp;
		
		auto f = [](int x) { return x * x; }; // closure type
		auto f2 = +[](int x) { return x * x; }; // derleyicinin bu ifadeyi s�n�f�n type cast operat�r�yle function poniter t�r�ne d�n��t�rmesi gerekiyor 
												   f2 function pointer type
	}

	�RNEK:

		template<typename T>
		void func(T);

		int main()
		{
			func([](int x) { return x * x; }); // closure type
			func(+[](int x) { return x * x; }); // function pointer type

		}

LAMBDA INIT CAPTURE(C++14)

	int main()
	{
		int x = 5;

		auto f = [count = 0]()(int x) // derleyiciye ��yle bir talimat vermi� oluyoruz s�n�fa bir veri eleman� koy ismi a olsun veri eleman�n�da 0 ile initialize et
		{
			++count; 
			return a + x;
		};


		[x = x](int a) // 5 de�erini s�n�f�n veri eleman� olan x'e atam�� oluruz
	}

	bu �zelli�in eklenmesinin nedenleri

		1)move semantics
			
			int main()
			{
				std::unique_ptr<std::string> uptr(new std::string{ "canim hocam necati hocam" });

				auto f = [uptr = std::move(uptr)]() // uptr'nin kayna��n� s�n�f�n member'� olan uptr'ye devrettik
					{
						std::cout << *uptr << '\n';
					};

				f();

				if (uptr)
				{
					std::cout << "dolu"<<'\n';
				}
				else
				{
					std::cout << "bos"<<'\n';
				}
			}

			�IKTI: 
				canim hocam necati hocam
				bos

	can�m�z hocam�z capture'da deduction farkl�l���na de�iniyor

		int main()
		{
			int a[10]{};
		[a] { std::cout << "sizeof(a) = " << sizeof(a)<<'\n'; // sizeof = 40 burda array decay yap�lm�yor 10 elemanl� bir dizi

			}();

		[a = a] { std::cout << "sizeof(a) = " << sizeof(a)<<'\n'; // sizeof = 8 burda array decay yap�l�yor burda auto type deduction'da ki kural ge�erli oluyor

			}();
		}

D�KKAT:referans ile capture yap�ld���nda dangling reference olu�turmak tipik bir kodlama hatas�

	auto foo(int x)
	{
		return [&x](int a) { return a * x; }; // derleyicinin yazd��� referans veri eleman� fonksiyonun otomatik �m�rl� parametre de�i�keni olan x'e ba�lanacak buda dangling referens
	}

	int main()
	{
		auto f = foo(10);
	}

TRAILING RETURN TYPE

	fonksiyonun geri d�n�� de�erinin ��kar�m yoluyla elde edilmesesini istemiyorsak lambdalarda trailing return type'� kullanabiliriz

	int main()
	{
		auto f = [](int x) -> double
			{
				return x * 5; // ifadenin t�r� int ama fonksiyonun geri d�n�� de�eri double
			};

		auto val = f(5);
		std::cout << val;

	}

	trailing return type'�n kullan�lmas�ndaki di�er ama�ta fonksiyonun geri d�n�� de�erinin referans t�r� yap�lmak istenmesi

	trailing return type'�n lambdalarda kullan�lmas�n�n avantaj�

		1)farkl� t�rden return ifadelerine sahip birden fazla return statement varsa
		2)fonksiyonun geri d�n�� de�erininin ��kar�m yoluyla de�ilde kendimiz istedi�imiz t�r olmas�n� istiyorsak
		3)fonksiyonun geri d�n�� de�erinin referans t�r� olmas�n� sa�lamak i�in
		4)fonksiyonun geri d�n�� de�eri t�r�n�n auto type deduction ile de�ilde decltype(auto) ile elde edilmesini istiyorsak

GENERALIZED LAMBDA EXPRESSIONS
	derleyicinin closure type s�n�f� i�in fonksiyon �a�r� operat�r fonksiyonunu member template olarak yazmas� i�in auto keyword'�n� kullan�yoruz

		class Myclass
		{
			public:
				template<typename T>
				void operator()(T  x)const
				{
				
				}
		};

		int main()
		{
			[](auto x) // parametreyi auto keyword'� ile bildirerek derleyicinin fonksiyon �a�r� operat�r fonksiyonunu yukar�daki gibi member template olarak yazmas�n� sa�l�yoruz
			{
				return x * x;
			}
		}
		
		�RNEK:
	
			int main()
			{
				[](auto&& x) // derleyicinin yazd��� kodda s�n�f�n template'i olan fonksiyon �a�r� operat�r fonksiyonun parametresi universal reference
				{
					return x * x;
				}
			}

lambda ifadelerinde derleyicinin yazd��� closure type'�n fonksiyon �a�r� operat�r fonksiyonunun exception throw etmeme garantisini vermek i�in noexcept specifier'�n� kullan�yoruz
		
	auto f = [](int a)noexcept
	{
		return a * a;
	};
*/