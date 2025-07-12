/*
exception handling konusundan devam ediyoruz

bir fonksiyonun noexcept ile nitelenmesine ra�men exception f�rlatmas� durumunda terminate fonksiyonu �a��r�l�r ve program sonland�r�l�r

	void bar()
	{
		throw std::runtime_error{ "error" };
	}

	void foo()noexcept
	{
		bar();
	}


	int main()
	{
		try
		{
			foo(); // terminate fonksiyonu �a��r�l�r exception yakalanmaz
		}
		catch (const std::exception&)
		{

		}
	}

bir s�n�f�n destructor'� default olarak noexcept garantisi verir
	
	class Nec {
	public:
		~Nec()
		{
		 
		}
	};

	int main()
	{
	
		constexpr auto b = noexcept(Nec{}.~Nec()); // TRUE de�eri �retir noexcept operat�r�n�n operand� olan ifade uneveluated context oldu�u i�in b�yle bir ifade yazmam�z sorun olmuyor 

	}

dtor exception throw etmemeli yada dtor exception throw ederse exception d��ar� s�zmamal� yani program�n ak��� kesinlikle dtor'dan ��kmamal�

	class Nec {
	public:
		~Nec()
		{
			if(1)
			{
				throw std::runtime_error{ "error from dtor" };
			}
		}
	};

	void myterminate()
	{
		std::cout << "myterminate called\n";
		std::abort();
	}

	int main()
	{
		set_terminate(&myterminate);
		try
		{
			Nec mynec; // mynec i�in dtor �a��r�ld���nda dtor excetpion throw edicek ve terminate fonksiyonu �a��r�lacak
		}
		catch (const std::exception&)
		{
			std::cout << "exception caught ";
		}
	}

	SORU:dtor neden exception throw etmemeli? ��NK� DEFAULT OLARAK NOEXCEPT OLARAK B�LD�R�L�YOR
		bir exception handle edildi�inde stack unwinding s�recinde bir s�n�f�n herhangi bir kodu excetpion throw ederse terminate �a��r�l�yor e�er buna m�sade edilseydi excetpion throw edildi�inde ve
		exception yakaland���nda stack unwinding s�ras�nda nesnelerin dtoru �a��r�ld�ktan sonra yine terminate fonksiyonu �a��r�lacakt�

	move ctor ve move assignment'�n noexcept olmas� gerekiyor ama move ctor ve move assignment default olarak noexcept de�il
	b�t�n swap fonksiyonlar�n�n da noexcept olmas� gerekiyor 
	memory de-allocation fonksiyonlar�n�n noexcept olmas� gerekiyor

	hoca noexcept specifier ile ilgili bir ka� yere daha de�iniyor
		1)function overriding
			
			class Base{
				public:
					virtual void foo()noexcept;
			};

			class Der : public Base{
				public:
					virtual void foo()override; // foo fonksiyonu noexcept garantisi vermedi�i i�in sentaks hatas� olur
			};

			SORU:tam tersi olsayd� Der s�n�f�n�n foo fonksiyonu noexcept olsayd� Base class'�n noexcept garantisi olmasayd� ne olurdu?
				Der s�n�f�n�n foo fonksiyonu exception throw etmeme garantisi olurdu ama Base class'�n foo fonksiyonu i�in b�yle bir garanti olmazd�
			
			class Base{
				public:
					virtual void foo();
			};

			class Der : public Base{
				public:
					virtual void foo()noexcept override; 
			};

		2)function pointers
			modern C++ dan �nce function pointerlarda noexcept anahtar kelimesini kullanam�yorduk

			int foo(int);
			int bar(int)noexcept;

			int main()
			{
				int (*fp1)(int)noexcept; = &foo; // fp1 ile yapaca��m�z fonksiyon �a�r�s�nda exception throw etmeme garantisi vermi� oluyoruz ama foo fonksiyonu bu garantiyi vermedi�i i�in sentaks hatas�
				
				int (*fp2)(int); = &bar; // fp2 noexcept garantisi vermese dahi bu kod ge�erli		
			
			}

	SORU:noexcept overloadingte kullan�l�yor mu? 
		HAYIR imzan�n bir par�as� ama overloadingte kullan�lm�yor sentaks hatas� olur
		
		int foo(int);
		int foo(int)noexcept;

	�RNEK:N.Jossutis'in kitab�ndan hoca �rnek veriyor
		class Base{
			public
				virtual void func() noxcept(sizeof(int) < 8); // might throw if sizeof(int) >= 8
				
		};

		class Derived : public Base{
			public:
				void func() noexcept(sizeof(int) < 4 ) override; // might throw if sizeof(int) >= 4
		}

		sizeof(int)'in 8 den k���k olmas� durumunda Base class'�n noexcept garantisine uyuyor ama t�remi� s�n�f�n noexcept garantisine uymuyor t�remi� s�n�f�n override fonksiyonu 
		Base class'�n verdi�i garantiden daha az�n� vermiyor oluyor bu y�zden sentaks hatas� oluyor

	�RNEK:generic programlama taraf�nda noexcept garatisi verip vermedi�ini s�namaya yarayan �ok say�da meta functionlar var
		meta functionlar compile time'da hesaplama yapan yap�lara deniliyor
		
		#include <type_traits>
			
		1)
			class Myclass{};

			int main()
			{
				constexpr auto b = std::is_nothrow_default_constructible_v<Myclass>; // TRUE de�eri �retilir yani default ctor noexcept 
			}

		2)
			class Myclass{
				public:
					Myclass();
			};

			int main()
			{
				constexpr auto b = std::is_nothrow_default_constructible_v<Myclass>; // FALSE de�eri �retilir yani default ctor noexcept de�il
			}

		3)
			template<typename T>
			void func(T) noexcept(std::is_nothrow_copy_constructible_v<T>) // T t�r�nden bir s�n�f�n copy ctoru exception throw etmeme garantisi veriyorsa 
																			  true de�ere sahip olacak ve bu fonksiyon noexcept olacak
			{

			}

		4)

			class Myclass{};

			template<typename T>
			void func(T) noexcept(std::is_nothrow_default_constructible_v<T>) // default ctor derleyici taraf�ndan yaz�ld��� i�in default olarak noexcept garantisi oluyor b�ylelikle 
																				 func fonksiyonu noexcept olacak
			{}

			int main()
			{

				constexpr auto b = noexcept(func(Myclass{})); // TRUE

			}

		5)
			class Myclass{
			public:
				Myclass(const Myclass&)noexcept = default;
			private:
				std::vector<int> mvec;
			};

			int main()
			{
				std::is_nothrow_copy_constructible_v<Myclass>; // TRUE

			}

	her hangi bir �ekilde exception g�nderilmedi�i zaman exception handling kodlar�n�n maliyeti zero'ya yak�n

	�RNEK:move ctorun noexcept olmas�n�n �nemi
		class Nec {
			public:
				Nec() : ms(2'000,'A'){}
				Nec(const Nec& other) : ms{ other.ms } { std::cout << "copy ctor\n"; }
				Nec(Nec&& other) : ms{std::move(other.ms)} {std::cout << "move ctor\n";} // move ctor noexcept olmad��� i�in copy ctor �a��r�l�yor 
				// Nec(Nec&& other) noexcept : ms{ std::move(other.ms) } { std::cout << "noexcept move ctor\n"; } 
		private:
			std::string ms;
		};

		int main()
		{
			using namespace std::chrono;
			using namespace std;
			vector<Nec> vec(100'000);

			auto start = steady_clock::now();

			vec.resize(vec.capacity() + 1);
			auto end = steady_clock::now();

			std::cout << duration<double,milli>(end - start).count() << "ms\n";

		}
		
		�IKTI: 229.928ms

		class Nec {
		public:
			Nec() : ms(2'000,'A'){}
			Nec(const Nec& other) : ms{ other.ms } { std::cout << "copy ctor\n"; }
			// Nec(Nec&& other) : ms{std::move(other.ms)} {std::cout << "move ctor\n";} 
			Nec(Nec&& other) noexcept : ms{ std::move(other.ms) } { std::cout << "noexcept move ctor\n"; } // kopyalama yerine ta��ma daha iyi oldu�u i�in ve move ctor noexcept oldu�u 
			i�in move ctor �a��r�l�yor
		private:
			std::string ms;
		};

		int main()
		{
			using namespace std::chrono;
			using namespace std;
			vector<Nec> vec(100'000);

			auto start = steady_clock::now();

			vec.resize(vec.capacity() + 1);
			auto end = steady_clock::now();

			std::cout << duration<double,milli>(end - start).count() << "ms\n";

		}

		�IKTI: 60.0461ms

EXCEPTION_PTR
	bazen yakalad���m�z bir exceptionu bulundu�u yerde de�ilde ba�ka bir yerde handle etmek istiyoruz bunun i�in exception_ptr s�n�f�n� kullan�yoruz
	poineter like bir s�n�f polimorfik bir pointer gibi davran�yor bu s�n�f t�r�nden bir nesnede bi excetpion nesnesini polimorfik olarak tutabiliyoruz yani exception belirli bir hiyerar�ide
	o hiyerar�ideki t�remi� s�n�flardan birinde exception_ptr s�n�f� t�r�nden bir nesneyle o exceptionu tutarsak ba�ka bir contexte dinamik t�r� koruyabiliyoruz bu s�n�f�n �nemi daha �ok concurrency taraf�nda 

	void handle_exception(std::exception_ptr eptr)
	{
		try
		{
			if(eptr)
			{
				std::rethrow_exception(eptr);
			}
		}
		catch(const std::exception& ex)
		{
			std::cout<<"exception caught : " << ex.what() << '\n';
		}
	}

	int main()
	{
		std::exception_ptr ep;

		try{
			std::string str{"cengizhan"};
			auto c = str.at(36);
		}
		catch(...)
		{
			ep = std::current_exception(); // exceptionu ep nesnesinde tutuyoruz current exception fonksiyonu hangi hata yakalanm��sa o hata nesnesini polimorfik oalrak tutan bir exception ptr nesnesi veriyor
			handle_exception(ep);
		}
	}

M�LAKAT SORUSUNA �RNEK:polimorfik exception idiom
	
	class EBase{
		public:
			virtual ~EBase() = default;
			virtual void raise()
			{
				throw *this;
			}
	};

	class Der1: public EBase
	{
		public:
			virtual void raise() override
			{
				throw* this;
			}
	};

	class Der2: public EBase
	{
		public:
			virtual void raise() override
			{
				throw* this;
			}
	};

	void foo(EBase& ex)
	{
		ex.raise(); // hangi s�n�f nesnesini g�nderirsek o s�n�f t�r�nden exception g�nderir
	}

	int main()
	{
		try
		{
			Der1 der1;
			foo(der1);
		}
		catch(Der1&) { std::cout<<"Der1 caught\n"; }
		catch(Der2&) { std::cout<<"Der2 caught\n"; }
		catch(...){
			std::cout<<"other exception type\n";
		}
	}

M�LAKAT SORUSUNA �RNEK:exception dispatcher

	class NecException{};
	class ErgException{};

	void handle_exception()
	{
		try{
			throw;
		}
		catch(NecException&){}
		catch(ErgException&){}
	}

	void func()
	{
		try{
			
		}
		catch(...)
		{
			handle_exception();
		}
	}	

NESTED EXCEPTION
	bir exceptionu yakal�yoruz fakat yakalad���m�z expcetionun kendisiyle birlikte ayr� bir exception g�ndermek istiyoruz yani daha yukar�daki katmanlar yakalad���m�z expceptiona ve g�nderdi�imiz exception
	hakk�nda bilgi sahibi olacaklar
	
		void print_exception(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			try {
				std::rethrow_if_nested(e); // std::exceptionu al�yor ve sarmalanan bir exception varsa onuda yakal�yor
			}
			catch (const std::exception& nested)
			{
				std::cerr << "nested: ";
				print_exception(nested);
			}
		}

		void baz()
		{
			throw std::runtime_error("exception from baz");
		}

		void bar()
		{
			try {
				baz();
			}
			catch (const std::exception&)
			{
				std::throw_with_nested(std::runtime_error("exception from bar")); // g�ndermek istedi�imiz exceptionu arg�man olarak ge�tik
			}
		}

		void foo()
		{
			try {
				bar();
			}
			catch (const std::exception&)
			{
				std::throw_with_nested(std::runtime_error("exception from foo")); // g�ndermek istedi�imiz exceptionu arg�man olarak ge�tik
			}
		}

		int main()
		{
			try {
				foo();
			}
			catch (std::exception& e)
			{
				print_exception(e);
			}
		}
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GENERIC PROGRAMMING(t�rden ba��ms�z programlama) TMP(template meta programmin'de denilebiliyor)
	
	Derleyicinin compile time'da belirli t�r yada t�rlere y�nelik kod yazmas�

	C++ kodlar�n� 2 kategoriye ay�rabiliriz
		1)derleyicinin derledi�i kod
		2)varl�k nedeni derleyiciye kod yazd�rmak olan kod
	
	standart k�t�phanenin en �nemli akronimi STL(standart template library) standart k�t�phanenin kendisi de�il standart k�t�phanenin bir bile�eni

	templatelerin belirli kategorileri var
		1)function template
			amac� derleyiciye fonksiyon kodu yazd�rmak olan kod

		2)class template
			derleyiciye s�n�f kodu yazd�ran templateler

		3)variable template(C++14 standard�yla eklendi)
			
		4)alias template
			derleyiciye t�r e� ismi bildirimi yapt�ran bir template

		5)concept(C++20 standard�yla eklendi)

		concept hari� bu template kategorilerinde template anahtar s�zc���n� kullan�yoruz
	
	derleyicinin compile time'da bir template'den faydalanarak ister function template ister class template olsun compile time'da olu�turdu�u varl���n kendsine o template'in specialization'� deniliyor
	
	t�rk�e olarak specialization'a hoca A�ILIM terimini kullanaca��n� belirtti

	template < //template parameters >(angular bracket -> a��sal parantez)
			
	template parametreleri 3 kategoriye ayr�l�yor
		1)type parameter
			bir t�re kar��l�k gelen parametre
				
				std::vector<int> // template type argument yada template argument deniliyor // template parametresine kar��l�k gelen t�r derleyicinin yazaca�� kodda int t�r�n� kullanaca��m�z� 
																							   belirtmi� oluyoruz

		2)non-type parameter
			t�r� olmayan bir parametre �rne�in bir sabit yada belirli bir t�rden de�er

				template <int n> // kullan�lacak olan t�r�n direkt olarak t�r�n� yaz�yoruz derleyici bizim i�in bu �ablondan bir kod �retti�inde template non-type parametresi kar��l��� 
									bu t�rden bir de�er kullanacak anlam�na geliyor C++20 ile beraber non-type parametrelerde geli�meler ya�and�
				
				O�UZHANIN SORUSU: n burda constant expression olmak zorunda m�?
					
					n'in kendisi bir ifade de�il n bir isim hoca burada soruyu �u �ekilde de�i�tiriyor: n'e kar��l�k gelen arg�man sabit olmak zorunda m�? EVET
					
		3)template parameter
			template parametresinin kendisinin template olmas�

	template<typename T> // buradaki T her hangi bir t�r anlam�nda typename yerine class anahtar kelimeside kullan�labiliyor ba�lang��ta class anahtar s�zc��� vard� templatelerde typename anahtar s�zc���n� 
						    kullanmakla class anahtar s�zc���n� kullanmak aras�nda hi� bir fark yok

	typename anahtar s�zc���n�n kullan�ld��� ba�ka bir ba�lam daha var hoca ileride de�inecek orada class anahtar s�zc���n� kullanam�yoruz 

	�RNEK:
		template <typename T>
		T func(T* x) // T==> t�r� yerine int kullan�l�rsa geri d�n�� de�eri int fonksiyonun parametresi de int olacak
		{
			T& r = *x; // buradaki T t�r� int& r

			return r;
		}

		int main()
		{
			int x = 5;
			func<int>(&x);
			
			// func(&x); 
		}
	
	DEN�Z�N SORUSU:T yerine incomplete type kullanabilir miyiz? SADECE BEL�RL� BA�LAMLARDA KULLANAB�L�YORUZ 

	SORU: madem derleyici bir template koddan bir specialization olu�turuken template'in parametrelere kar��l�k kullan�lan template arg�manlar�n� bilmek zorunda peki bunu nas�l bilecek?
		
		1)DEDUCTION derleyici koda bakarak template parametresi kar��l��� hangi arg�man�n kullan�laca��n� s�ylemesekte koda bakarak derleyici bunun ��kar�m�n� yapabiliyor
		
		template<typename T>
		void func(T);

		int main()
		{
			func(345); // belirli kurallar dahilinde derleyici fonksiyona g�nderilen arg�man olan ifadenin t�r�n�n int oldu�undan template parametresi kar��l��� kullan�lacak 
						  template arg�man�n�n int t�r� olmas� gerekti�ini anlayacak
		}

		2)EXPLICIT TEMPLATE ARGUMENT olarak derleyiciye bildirilmesi
			T func(T* x) 
			{
				T& r = *x; // buradaki T t�r� int& r

				return r;
			}

			int main()
			{
				int x = 5;
				func<int>(&x);
			}

		modern C++ �LE �ZEL�KLE 17 STANDADARDIYLA devrimsel bir de�i�iklik oldu 17 stadnard�ntan �nce deductrion mekanizmas� sadece function templateleri i�in m�mk�nd�
		CTAD(class template argument deduction) belirli s�n�rlar dahilinde s�n�f �ablnolar�nda template paremetrelrine kar����k gelen temaplte arg�manlar�n�n ��kar�m�n�n yap�lmas�
		olana�� kazand�r�ld�

		3)DEFAULT TEMPLATE ARGUMENT

			template parametreleeinden biri yada birden fazlasac� i�in default template argument belirlenebiliyor explicit olarak templat parametrelerine kar��l�k gelen arg�manlar�
			yazmasakta derleyici template bildirimine bakarak hangi arg�manlar�n default argument olarak kullan�laca��n� belirlemi� oluyor
*/