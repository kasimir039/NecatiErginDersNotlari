/*

friend bildirimlerinden devam 3 tane maddemiz vard�
		1)global fonksiyonlara verilen friendlik
			
			class Myclass
			{
			public:
				friend int foo(int);
			private:
				int mx;
				void bar();
			};

			int foo(int x)
			{
				// burda s�n�f�n private b�l�m�ne eri�im sentaks hatas� olarak de�erlendirilmez

				Myclass m;
				auto val = m.mx;
			}

			s�n�f�n hangi b�l�m�nde friend bildirimi yapt���m�z farkeder mi? FARKETM�YOR public private protected hepsinde bildirebiliriz de�i�en bir �ey olmuyor

		2)bir ba�ka s�n�f�n bir member functionuna verilen friendlik

			class Nec{
				public:
				int foo();
			}

			class Myclass{
				public:
					friend int Nec::foo();
				private:
					int mx;
			}

			int Nec::foo()
			{
				Myclass m;

				m.mx = 5;
			}

		3)bir s�n�f�n tamam�na verilen friendlik(nadiren kar��m�za ��kar)

			class Myclass
			{
				public:
					friend class Nec; // Nec s�n�f� Myclass s�n�f�n�n private elemanlar�na eri�ebilir
				private:
					int mx;
			}

			class Nec{
				void foo()
				{
					Myclass m;
					m.mx = 5;
				}
			}

	S�n�f�n special member functionlar�n�da friendlik verebiliriz	

	generic programlama taraf�nda friendlik daha karma��k hale gelecek ileride bahsedilecek

	FRIEND HAKKINDA KURALLARA �RNEK
		1)A s�n�f� -> B s�n�f�na friendlik versin
			class A
			{
				friend class B; // burada B s�n�f�da A s�n�f�na friendlik vermi� olmuyor yani A s�n�f� B s�n�f�n�n private b�l�m�ne eri�emez
			}

		2)Geci�kenlik yok yani A -> B s�n�f�na friendlik versin B s�n�f�da -> C s�n�f�na friendlik versin
			B s�n�f� A s�n�f�n�n private b�l�m�ne eri�ebilir C s�n�f�da B s�n�f�n�n private b�l�m�ne eri�ebilir
			ama C A'n�n private b�l�m�ne eri�emez burada hoca inheritance konusuna vurgu yap�yor
		
		3)bir s�n�fa friendlik vermek istiyoruz ama b�t�n private b�l�m�ne de�il istedi�imiz fonksiyona eri�mesini istiyoruz b�yle bir �ey m�mk�n m�? HAYIR
		bunu ger�ekle�tiren do�rudan bir ara� yok ama dolayl� olarak idiomatik baz� yap�lar� kullanarak bunu ger�ekle�tirmek m�mk�n buna ATTORNEY-CLIENT IDIOM deniliyor
			
			"Attorney" (avukat), eri�imi arac�l�k eden s�n�ft�r.

			"Client" (m��teri), eri�mek isteyen kod/s�n�ft�r.

			"Target" (hedef), eri�ilmek istenen s�n�ft�r (private/protected �yeleri olan).

			Ama�: Target s�n�f, do�rudan Client'a friend yapmak yerine, araya bir Attorney s�n�f� koyar, sadece bu s�n�fa friend eri�im verir. B�ylece eri�im daha kontroll� olur

		// Target class: Eri�imi korunan s�n�f
		class Engine {
		private:
			void start() const {
				std::cout << "Engine started!\n";
			}

			// Sadece Attorney'e friend veriyoruz
			friend class EngineAttorney;
		};

		// Attorney class: Ara katman, sadece start fonksiyonunu a�ar
		class EngineAttorney {
		public:
			static void startEngine(const Engine& e) {
				e.start(); // private fonksiyona eri�im burada sa�lan�yor
			}
		};

		// Client class: start()'a do�rudan eri�emez ama Attorney �zerinden eri�ebilir
		class Car {
		public:
			void run() {
				Engine e;
				EngineAttorney::startEngine(e); // Engine'e do�rudan de�il, Attorney �zerinden eri�im
			}
		};

		int main() {
			Car myCar;
			myCar.run(); // Output: Engine started!
		}

HIDDEN FRIEND
 bir �ok durumda s�n�f�n free function olan friend fonksiyonlar�n� do�rudan inline olarak s�n�f i�inde tan�mlayabiliriz
 �nemini ileride hoca anlatacak
	class Myclass
	{
		public:
			friend int foo(int)
			{

			}
	};	

idiom -> programlama diline ba�l�d�r ba�ka bir programlama dilinde o kal�psal yap�y� kullanamayabiliriz 
	idiom burada kal�pla�m�� �ok say�da programc�n�n kodu daha iyi hale getirmek i�in kulland��� kodsal yap�lar anlam�na geliyor

pattern -> hoca �r�nt� demeyi tercih ediyor dilden ba��ms�z bir yap�ya i�aret ediyor �o�u programlama dilinde kullan�lan kal�plar   
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
OPERATOR OVERLODING

	C++ dilinde bir s�n�f nesnesi bir operat�r�n operand� oldu�unda derleyici dilin kurallar�na g�re operat�r�n operand� olmu� s�n�f nesnesi ifadesini bir fonksiyon �a�r�s�na d�n��t�r�yor
	yani ortada do�rudan fonksiyon �a�r� operat�r� yok ama kodun anlam� derleyicinin bir fonksiyona �a�r� yapmas� 
	bunlara operator functions deniliyor

	a + b ifadesi olsun a ve b bir s�n�f t�r�nden nesneler olsun bu durumda tan�mlanm�� bir fonksiyon varsa derleyici a + b ifadesini bir operat�r fonksiyonuna yap�lan �a�r� ifadesine d�n��t�r�yor
	peki burada �a��r�lan fonksiyon global function m� yoksa s�n�f�n non-static member function� m� ? HER �K�S�DE OLAB�L�R 
	
	SORU:run time'a y�nelik bir mekanizma m� compiler time'a m�?
		compile time'a y�nelik bir mekanizma ��nk� derleyici hangi fonksiyonun �a��r�ld���n� derleme zaman�nda anl�yor

	operat�r fonksiyonlar� static member function olamaz

	operat�r overloadingten faydalanabilmemiz i�in intuitive olmam�z gerekiyor

	OPERATOR OVERLOADING KURALLARI
		1)operat�r overloadingten bahsedebilmemiz i�in operat�r�n operand� olan ifadelerden en az birinin bir s�n�f t�r�nden yada bir enumaration t�r�nden olmas� gerekiyor
			
		2)overload edilecek operat�r�n C++ dilinin operat�r k�mesinde olmas� gerekiyor
			�rne�in @ C++ dilinin operat�r k�mesinde yok
		
		3)operat�r overloading fonksiyonlar�n� istedi�imiz gibi isimlendiremiyoruz hangi operat�r� overload ediyorsak onu belirtmemiz gerekiyor
			operator+ ,operator[] gibi

		4)dilin b�t�n operat�rleri overload edilemiyor baz� operat�rler i�in overloading mekanizmas� yasaklanm��
			sizeof
			:: scope resolution operat�r�
			. member access operat�r�
			.* pointer to member operat�r�
			? : conditional operat�r�
			->* pointer to member operat�r�
			typeid

		5)operat�r fonksiyonlar�n�n baz�lar� free function olarak tan�mlanam�yor member function olmak zorundalar
			() function call operat�r�
			[] subscript operat�r�
			-> member access operat�r�
			= assignment operat�r�
			type cast operat�rleri

		6)t�m operat�r fonksiyonlar� istisnas�z isimleriylede �a��r�labilir
			class Myclass{};

			int main()
			{
				Myclass m1,m2;

				m1.operator=(m2); // m1 = m2 
			}

		7)function call () operat�r� hari� di�er operat�r overloading mekanizmas�nda kullan�lan fonksiyonlar default argument alamazlar
			
		8)operat�r overloading mekanizmas�nda ki operat�rlerin (arity) de�i�tirilemez yani operat�r�n unary yada binary olmas� 
			
			binary operators
				x * y // binary bir operat�r� oldu�u i�in buna uygun sentaksla overload edilecek bu overloading free functionla yap�l�yorsa bu durumda
			
				�arpma oeprat�r�n�n sol operand� ve sa� operand�da o fonksiyonun parametrelerine arg�man olarak g�nderiliyor
				derleyici x * y ifadesini operator*(x,y) ifadesine d�n��t�r�cek bu global fonksiyonun 2 tane parametre de�i�keni olmal� bunun d���nda ba�ka bir parametre olursa sentaks hatas� olur
				derleyici sol operand� 1.ci parametresini sa� operand� 2.ci parametresine ge�iyor 
			
					class Matrix{
						public:

					};

					bool operator<(const Matrix&,const Matrix&)

				fakat binary operat�r�n� overload edicek fonksiyon member function ise o member function binary operat�r�n�n sol operand� i�in �a��r�l�yor,
				this pointer� sol operand olan nesnenin adresi x > y ifadesini derleyici x.operator>(y) ifadesine d�n��t�r�yor bu functionlar tek parametre olmak zorundalar bunun d���nda 
				ba�ka bir parametre olursa sentaks hatas� olur
				
					class String{
						public:
							bool operator<(const String&) const;
					}

			unary operators
				!ptr// unary opeart�r oldu�u i�in buna uygun sentaksla yaz�lmas� gerek

				unary operator olan ifade global function ise derleyici operat�r ifadesini operator!(ptr) ifadesine yap�lan bir �a�r�ya d�n��t�r�cek operat�r�n operand� olan s�n�f nesnesinide 
				bu fonksiyona yap�lan �a�r�da arg�man olarak kullan�cak tek parametre almak zorundalar bunun d���nda sentaks hatas� olur 

					class SmartPtr{};

					bool operator!(const SmartPtr&)const;

				unary operator bir member function ise parametresi olmaz zaten o nesne i�in �a��r�l�r
					class SmartPtr{
						public:
							bool operator!() const;
					};

			SORU:sentaks hatas� m� de�il mi?
				class Myclass
				{
					public:
						Myclass operator+(); // sentaks hatas� de�il ��nk� bu toplama operat�r�n� overload etmiyor sign operat�r�n� overload ediyor
						Myclass operator+(Myclass) const; // toplama operat�r�n� overload ediyor
				}


		9)operat�r overloading mekanizmas�nda function overloadingte kullan�labilir

			class Bigint{
				public:
					Bigint operator+(int)const;
					Bigint operator+(long)const;
					Bigint operator+(long long)const;
			}

			int x = 10;
			double dval = 3.4;

			operator<<(cout.operator<<(x), '\n'); // derleyici function overload resolution ile int parametreli functionu �a��r�yor
			operator<<(cout.operator<<(dval), '\n'); // derleyici function overload resolution ile double parametreli functionu �a��r�yor

		atama operat�r fonksiyonu demek illa ki special member function olmas� anlam�na gelmiyor
			class Myclass {
			public:
				Myclass& operator=(int) {

					std::cout << "operator=(int)\n"; // Myclass s�n�f� t�r�nden bir nesneye int atada��m�zda bu fonksiyon �a��r�lacak
					return *this;
				}
				Myclass& operator=(double) {

					std::cout << "operator=(double)\n";// Myclass s�n�f� t�r�nden bir nesneye double atada��m�zda bu fonksiyon �a��r�lacak
					return *this;

				}

			};

			int main()
			{
				Myclass m;

				m = 5;
				m = 5.5;
			}

	10)operator overloading mekanizmas�nda operat�rlerin �ncelik seviyesini de�i�tiremeyiz
		class Bigint{
		};

		Bigint operator*(const Bigint&,const Bigint&);
		Bigint operator+(const Bigint&,const Bigint&);
		Bigint operator&const Bigint&,const Bigint&);

		int main()
		{
			Bigint b1,b2,b3,b4,b5;
			Bigint bx;

			bx = b1 * b2 + b3 * b4 & b5; // 5 adet operator oldu�u i�in o kadar fonksiyon �a��r�lm�� oluyor 

			bx.operator=(operator&(operator+(operator*(b1,b2), operator*(b3,b4)), b5)); // ((b1 * b2)) + (b3 * b4)) & b5; bu iki kodun anlamsal olarak hi� bir fark� yok
		
			bu operat�rlerin yaz�m �ekliyle �ncelik seviyesini de�i�tiremeyiz
		}

		member function olsayd�lar
			Bigint operator*(const Bigint&)const;
			Bigint operator+(const Bigint&)const
			Bigint operator&const Bigint&)const;

			 int main()
			 {
				bx.operator=(b1.operator*(b2).operator+(b3.operator*(b4)).operator&(b5));
			 }

	SORU:global operator fonksiyonlar� neden var?
		1)x + 5;
		x.operator+(5); // x + 5 gibi bir i�lemi yapabiliyorsak 5 + x gibi bir i�lemide yapabilmemiz gerekiyor ama bu sefer sol operand bir s�n�f t�r�nden olmam�� oluyor int t�r�n�n bir operator fonksiyonu 
		olamaz bu i�i global operator fonksiyonlar yapabilir yani global operator fonksiyonlar olmasayd� sol operand�n bir s�n�f t�r�nden olmamas� durumunda s�n�f�n �ye operat�r 
		fonksiyonuna �a�r�ya d�n��t�rme imkan�m�z olmazd�
		
		2)
			class Matrix{};

			std::ostream& operator<<(std::ostream&,const Matrix&);

			int main()
			{
				Matrix m;

				std::cout << m; // inserter deniliyor 
			}

	 referans semanti�i olmasayd� operator overloading mekanizmas�n� kullanmak m�mk�n de�ildi

	SORU:operator overloading ile const corretncess aras�ndaki ili�ki nedir?
		
		toplama operat�r�n� ve b�y�kt�r operat�r�n� d���nelim bu operat�rler side effecte sahip de�il �rne�in a + b ifade kar��l��� bir i�lem yap�ld��� i�in program stateinde bir de�i�iklik olmuyor 
		ne a ne b de�i�ecek a + b yazmakla bir fonksiyonu �a��r�lmas�n� sa�l�yorsak fonksiypnun a ve b yi de�i�tirmeme garantisi vermesi gerekiyor
		
		oeprator+(const Matrix&,const Matrix&) // global operator+ fonksiyonunda burda const anahtar s�zc���n� kullanmasayd�k semantik olarak ciddi bir hata olurdu kodu okuyanlar� yan�lt�rd� ve
		const nesneleri ve r value de�erleri ba�lamayazd�k

		member function olsayd�

		Matrix operator+(const Matrix&) const;

		unary operatorler i�in
			bool operator!() const; // side effecte sahip olmad��� i�in const member function olmal�

		e�er operator bir mutatorsa const olmamas� gerek
			operator*=(int); // 
			
		return value type
			dilin operator overloadinge il�kin kurallar� fonksiyonlar�n geri d�n�� de�eri �st�nde bir k�s�tlama yapm�yor
				int operator+(const Matrix&)const; // bir matris ile bir matrisi topluyoruz ve bir tam say� elde ediyoruz semantik olarak do�ru de�il ama derleyici burda hata vermiyor 
				sentaks hatas� olmamas� b�yle bir bildirimin do�ru oldu�u anlam�na gelmiyor
				
				fonksiyonun geri d�n�� de�eri t�r�n�n ne olaca��n� problem domaini belirliyor mesele kar��la�t�rma operat�rleri primitive t�rlerde bool de�er �retiyor
					
					class Date
					{
						public:
							Date operator+(int ndays)const;
							Date operator-(int ndays)const;
							Date operator-(const Date&)const;
					};
					
					int main()
					{
						Date today{14,8,2024};
						Date dx{5,5,2017};

						today - dx;
					}
+
			SORU:
				class Matrix{
					public:
						Matrix& operator+(const Matrix&)const; // geri d�n�� de�eri referans olmas� iyi bir fikir olabilir mi? HAYIR
						referans bir nesnenin yerine ge�ti�i i�in fonksiyonun geri d�n�� de�eri kime referans olacak? e�er fonksiyonun geri d�n�� de�eri otomatik �m�rl� bir nesneyse ona referans d�nd�rmemiz
						undfined behaviour ve dangling reference b�yle fonksiyonlar�n geri d�n�� de�erini l value reference yapmamal�y�z
				
				};

			operator fonksiyonlar�n�n bir ka� istisna d���nda �ok b�y�k �o�unlukla geri d�n�� de�erini discard etmek logic bir hata
				class Bigint
				{
					public:
						[[nodiscard]] Bigint operator+(const Bignit&);
				}

				�zellikle side effect olmayan operat�rlerin nodiscard attribute ile nitelenmesi do�ru bir yakla��md�r

			bir operat�r� overload etmek istiyoruz ama free function m� olsun member function m� olsun?
				bu sorunun net bir cevab� yok fakat bir �ok ki�inin uydu�u ilke simetrik operat�rleri global operator fonksiyonu yapmak
				yani x + y yazmakla y + x yazmak ayn� i�leme kar��l�k geliyorsa o zaman global operator fonksiyonu tercih ediliyor

				aritmatik operatorler ve kar��la�t�rma operat�rleri global operator fonksiyonu olarak tan�mlamak bir kural de�il ama daha iyi bir tercih olarak g�r�l�yor

			https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines hoca bu sitedeki ilkeleri benimsememizi tavsiye ediyor

			SORU:
				class Myclass{
					public:
						Myclass operator+(int)const;

				  };

				  int main()
				  {
					Myclass m;
					m += 5; // burada + ve = operat�r� ayr� ayr� overload edilmi�se += fonksiyonu otomatik var oluyor mu? HAYIR
				  }

				ayn�s� C++20 de kar��la�t�rma �perat�rleri i�in ge�erli de�il C++20 de operat�r overloadinge �ok b�y�k bir ekleme geldi dile yeni bir operat�r eklendi
				<=> space ship operator bunun sayesinde 6 tane operat�r� ayr� ayr� overload etmemize gerek kalm�yor
				s�n�fta ya sadece space ship operat�r� var yada onun yan�nda == operat�r�de var
*/