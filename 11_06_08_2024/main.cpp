/*

special member functionlardan devam ediyoruz

B�R SINIF NESNES�N�N KOPYALANARAK HAYATA GELMES� NE DEMEK(COPY CONSTRUCTOR k�saltmas� CC)
	KOPYALAMA SEMANT���

	bir nesneyi bir ba�ka nesnenin de�eri ile hayata getiriyoruz yada bir nesneye bir ba�ka nesnenin de�erini at�yoruz
	
	1)bu nesneler birbirinden ba��ms�z yani bundan sonraki bir nesnenin biri �st�nde yap�lan i�lemler di�erini etkilemeyecek yani kopyalamadan sonra bu nesnelerin birbiriyle bir ili�kisi kalm�yor
	2)bu nesneler kar��la�t�r�labilir nesnelerse(equality comparable) b�yle bir kopyalamadan sonra nesneler ayn� de�erde oldu�u i�in kar��la�t�rma yaparsak elde edece�imiz de�er true de�eri olur
		Date dx{12,4,1987};
	
		Date dy = dx; // dy nesnesininde de�eri 12,4,1987 olucak
		dy == dx gibi bir i�lem true de�eri verir

	class Myclass{};

	int main()
	{
		Myclass m1;
		Myclass m2 = m1; // m2 nesnesini hayata getirecek constructor copy ctor
		Myclass m3(m1); // copy ctor �a��r�l�r
		Myclass m4{m1}; // copy ctor �a��r�l�r
		auto m5 = m2 // Myclass m5 = m2 ��kar�m� yap�l�r

		s�n�f�n copy constructor� olmak zorunda delete edilmi� olabilir yada implictly declare edilmi� olabilir ama kesinlikle olmak zorunda

	}
	
	RULE OF ZERO
		s�n�f�n special member functionlar�n�n derleyici taraf�ndan yaz�lmas� derleyici bizim i�in dilin kurallar�na uygun bir �ekilde special member functionlar�n� default ediyorsa i�i derleyiciye b�rak�yoruz
		bizim i�in bu special member functionlar� tan�mlamak i�in zaten bir gereklilik olmas� gerekiyor derleyicinin yazd��� fonksiyonlar i�imizi g�rd��� noktada i�i derleyiciye b�rakmak
		ama �yle durumlar var ki special member functionlar� kendimiz tan�mlamam�z gerekiyor b�yle durumlarda derleyicinin tan�mlamas�na b�rak�rsak bu durumda UNDEFINED BEHAVIOUR'a sebep olabiliyor 

	DERLEY�C�N�N YAZDI�I COPY CTOR NASIL B�R YAPIYA SAH�P
		class Myclass
		{
			public:  
				Myclass(const Myclass& r){} // derleyici taraf�ndan yaz�lan derleyicinin implicitly declare etti�i copy ctor s�n�f�n public non-static inline �ye fonksiyonudur
				
		};

		int main()
		{
			Myclass m1;
			Myclass m2(m1); // copy ctor �a��r�ld���nda this pointer� m2 nin adresi olucak r referans� m1'e ba�lanacak
		
		}

	PEK� DERLEY�C�N�N YAZDI�I COPY CTOR NE YAPIYOR
		diyelim ki bu s�n�f�n non-static data memberlar� var

		class Myclass
		{
			public:
				Myclass(const Myclass& r) : ax(r.ax), bx(r.bx) cx(r.cx) {} // derleyici s�n�f�n her bir veri eleman�n� parametresi olan l value referans�n�n ba�land��� nesnenin ilgili eleman�yla hayata getiriyor 
			private:
				A ax;
				B bx;
				C cx; 

			burdan ��kan sonu�lar �unlar
			1)e�er Myclass s�n�f�n�n bu de�i�kenleri int double pointer gibi elemanlarsa di�er nesneninn kar��l�kl� eleman�ndan alacaklar 
			2)bu t�rler s�n�f t�r�ndense bu durumda a�a��daki gibi copy construct edilecekti b�ylece bizim kopyalama ile hayata getirdi�imiz nesne de�erini di�er nesnenini elemanlar�ndan al�yor
				Myclass(const Myclass& r) : ax(r.ax), bx(r.bx) cx(r.cx) {} 
		};
			
		class Date
		{
			public:
				Date(int d, int m,int y) : md{d},mm{m},my{y}
				{
					std::cout<<"Date(int,int,int) this = " << this <<'\n';
				}

				~Date()
				{ 
					std::cout<<"Date() this = " << this <<'\n';
				}
			private:
				int md,mm,my;
				
		};

		int main()
		{
			Date d1 {12,4,1998};
			Date d2 = d1; // burda derleyicinin yazd��� copy ctor d2 nesnesini hayata getirdi derleyicinin ipmlictly declare etti�i copy constructor sayesinde
		
		}

		�IKTI:
		Date(int,int,int) this = 000000735519F548
		Date() this = 000000735519F578 
		Date() this = 000000735519F548

		bu durumda implictly declare etti�i copy ctoru nas�l yazd�
			Date(const Date& r) : md(r.md), mm(r.mm),my(r.my) // derleyicinin impclitly declare etti�i copy ctor
			{
				std::cout<<"Date copy ctor this = " << this << '\n'; // ��kt�y� g�rmek i�in yazd�k
				std::cout<<"&r = " << &r << '\n'; // r'nin adresi de�erini veren nesnesinin adresi
			}

			int main()
			{
				Date d1{ 12,4,1998 };
				Date d2 = d1; // derleyici asl�nda burda copy ctor'un �a��r�lmas�n�n gerekti�ini function overload resolution ile anl�yor

				std::cout << "&d1 = " << &d1 << '\n';
				std::cout << "&d2 = " << &d2 << '\n';
			}
		�IKTI:
		Date(int,int,int) this = 00000069138FF838
		Date copy ctor this = 00000069138FF868
		&r = 00000069138FF838
		&d1 = 00000069138FF838 
		&d2 = 00000069138FF868
		Date() this = 00000069138FF868
		Date() this = 00000069138FF838
		
		COPY CTORUN �A�IRILDI�I SENARYOLAR
			1)
				class Myclass{};

				int main()
				{
					Myclass m1;
					Myclass m2 = m1;// copy initalization
					Myclass m3(m1); // direct initialization
					Myclass m4{m1}; // direct list initiazaliton
				}

			2)bir fonksiyonun parametresinin s�n�f t�r�nden olmas�(CALL BY VALUE) ve fonksiyonada s�n�f t�r�nden bir arg�man ge�ilmesi
				class Myclass
				{
				public:
					Myclass()
					{
						std::cout << "default ctor this = " << this << '\n';
					}
					~Myclass()
					{
						std::cout << "destructor this = " << this << '\n';
					}
					Myclass(const Myclass&)
					{
						std::cout << "copy ctor this = " << this << '\n';
					}
				};

				void func(Myclass m)
				{
					std::cout << "foo cagirildi: " << "&m = " << &m << '\n';

				}

				int main()
				{
					Myclass m1;
					func(m1); // func fonksiyonunun m parametre de�i�keni i�in copy ctor �a��r�lacak

					std::cout << "&m1 = " << &m1 << '\n';
				}

				�IKTI:
				default ctor this = 0000001310AFFB24
				copy ctor this = 0000001310AFFC04
				&m = 0000001310AFFC04
				destructor this = 0000001310AFFC04
				&m1 = 0000001310AFFB24
				destructor this = 0000001310AFFB24
			
			3)bir fonksiyonun geri d�n�� de�eri t�r�n�n bir s�n�f t�r� olmas� ve fonksiyonun return ifadesinin bir s�n�f nesnesi olmas� bu durumda fonksiyonun geri d�n�� de�erini tutucak temporary object i�in copy ctor �a��r�lacak
				burda dilin baz� ba�ka kurallar� devreye giriyor COPY ELISION,RETEUN VALUE OPTIMIZATION, NAMED RETURN VALUE OPTIMIZATION C++17 DE D�LE EKLENEN MANDOTARY COPY ELISION gibi kurallar devreye giriyor 
				hoca sonra de�inecek 
				
				class Myclass
				{
				public:
					Myclass(const Myclass& r)
					{
						std::cout<<"Copy ctor this = " <<this<<'\n';
					}
					Myclass()
					{
						std::cout << "Default ctor this = " << this<<'\n';
					}
					~Myclass()
					{
						std::cout << "~Destructor() this = " << this << '\n';
					}
				};

				Myclass g;

				Myclass foo()
				{
					std::cout <<"&g " << &g << '\n';
					return g;
				}

				int main()
				{
					foo();
				}
			�IKTI:
			default ctor this = 00007FF608071200
			&g = 00007FF608071200
			Copy ctor this = 00000097691CF834
			~Destructor() this = 00000097691CF834
			~Destructor() this = 00007FF608071200

			�RNEK:
				// myclass.h
				class Myclass
				{
					public:
						Myclass(const Myclass&);
						// Myclass(const Myclass&) = default; // b�ylede yaz�labilir cpp de oldu�u gibide yaz�labilir
						Myclass(const Myclass&) = delete; // ilerde bizi �ok ilgilendiricek e�er b�yle bir fonksiyon bildirmi�sek copy ctor'un �a��r�ld��� senaryolarda delete edilmi�
						bir fonksiyona �a�r� yapt��m�z i�in sentaks hatas� olacak 
				};
				// myclass.cpp
					Myclass::Myclass(const Myclass&) = default // bu bildirim cpp dosyas�nda da yap�labilir derleyici ilk bildirimde onun default edilmesi gerekti�ini g�rmese cpp dosyas�nda defualt bildirimini g�rebilir
					ama dikkat ayn�s� DELETE bildirimi i�in ge�erli de�il

	HANG� DURUMLARDA DERLEY�C� YER�NE KEND�M�Z COPY COSTRUCTOR YAZMALIYIZ
		�yle s�n�flar var ki bu s�n�flar kaynak kullan�yorlar bu kaynak dinamik allocate edilmi� bir bellek blo�u olabilir bir dosya olabilir bir veri taban� olabilir gibi gibi
		b�yle durumlarda s�n�f nesneneleri bu kayna�� handle tutuyor

		String str("bugun sinifin ozel fonkiyonlarini isliyoruz"); // �zel bir optimizasyon senaryosu olmaad��� s�rece bu yaz�y� bir yerde tutmak zorunda dinamik olarak allocate edilen bir dynamic arrayde tutucak 
		ve string nesnesi yaz�y� kullanabilmek i�in dynamic array'in adresine sahip olmak zorunda bu durumda o adreste s�n�f�n bir veri eleman� olan bir pointer tutucak
		
		class String
		{
			public:
				String(const char*);
			private:
				char *mp; // dinamik olarak allocate edilen bellek blo�unun adresini tutacak
				size_t mlen; // yaz�n�n uzunlu�unu tutacak
		};

		int main()
		{
			String str("bugun sinifin ozel fonkiyonlarini isliyoruz"); 

			String s = str; // value semantik kaybolmu� oluyor memberwise copy oluyor hayata gelen nesnesinin her bir eleman�n� di�er nesnenin eleman�yla initalize edecekti 
			buda nesnelerin birbiriyle ili�kisi bitmiyor s ile str �u an ayn� bellek alan�n� kullan�yor bu yaz� �zerinde de�i�iklik yap�lmas� demek ayn� yaz� �zerinde de�i�iklik yap�lmas� demek s nesnesinin
			�ye fonksiyonlar�ndan biriyle str yaz�s�n� de�i�tirseydik str nesneside bu yaz�y� kullan�yor olacakt� bu nesnelerden birinin hayat� bitti�inde bu kayna��n destructorda geri 
			verilmesi gerekiyor buna RAII(Resource Acquisition Is Initialization) deniyor kaynak edinimi ilk de�er verme yoluyla olur 
		}

		bu nesnelerin biribirnden ba��ms�zl���n� kurmak value semanti�ini korumak i�in hayata gelen nesnede ayr� bir dinamik bellek alan� allocate edicek ve ba�lat�ld��� de�erlerini kopyalayacak art�k nesnelerin pointer 
		elemanlar� ayr� bellek alanlar�n� g�steriyor s ile str birbirinden ba��ms�z olmu� oluyor

		SHALLOW COPY/MEMBER WISE COPY
			derleyicinin yazd��� copy ctor elemanlar pointerda olsa kayna�� g�steren pointerlar�n kopyaland���n� yani kayna��n kendisi de�il kayna��n adresini tutan pointer yada referans kopyalan�yor
			
			#define _CRT_SECURE_NO_WARNINGS

			#include <iostream>
			#include <cstdlib>
			#include <cstring>

			class String
			{
			public:
				String(const String* other) : mlen(other->mlen), mp(other->mp) {} // derleyicinin arka planda yazd��� copy constructor 
				~String()
				{
					if (mp)
						free(mp);
				}
				String(const char* p) : mlen(std::strlen(p))
				{
					mp = static_cast<char*>(std::malloc(mlen + 1));

					if (!mp) {
						std::cerr << "cannot allocate memory\n";
						std::exit(EXIT_FAILURE);
					}

					strcpy(mp, p);
				}
				void print() const
				{
					std::cout << '['<<mp << "]\n";
				}

				size_t length()const
				{
					return mlen;
				}
			private:
				size_t mlen; // yaz�n�n uzunlu�unu tutacak
				char* mp; // dinamik olarak allocate edilen bellek blo�unun adresini tutacak
			};

			void foo(String s)
			{
				std::cout << "foo cagrildi\n";
				s.print();
				(void)getchar();
			} // program�n ak��� buraya geldi�inde s nesnesinin hayat� bitiyor ve s nesnesinin destructoru �a�r�l�yor ve s nesnesinin mp eleman� tuttu�u dinamik bellek blo�unu free ediyor

			int main()
			{
				String str("bugun sinifin ozel fonkiyonlarini isliyoruz");

				str.print();

				foo(str); // burda s nesnesi hayata getiriliyor ve s nesnesinin mp eleman� str nesnesinin mp eleman�n�n adresini tutuyor

				str.print(); // dangling pointer kullanm�� oluyoruz
			}

		DEEP COPY
			pointer kopyalanmas�n hayata gelecek nesnede yeni bir bellek alan� allocate etsin o allocate edilmi� bellek alan�na kendi kayna��n� edinsin di�erinin kayna��ndan copy ctor ile hayata gelen
			nesnenin kayna��na kopyalama yap�ls�n b�ylelikle nesneler birbirinden ba��ms�z olmu� olur

			copy constructor� kendimiz yaz�yorsak b�t�n veri elemanlar�n�n almas� gereken de�erlerini vermekte biz sorumluyuz derleyiciye b�rak�rsak default initialize eder

			class String
			{
			public:
				String(const String& other) : mlen(other.mlen)
				{
					mp = static_cast<char*>(std::malloc(mlen + 1));

					if (!mp) {
						std::cerr << "cannot allocate memory\n";
						std::exit(EXIT_FAILURE);
					}

					strcpy(mp, other.mp);
				}
				String(const char* p) : mlen(std::strlen(p))
				{
					mp = static_cast<char*>(std::malloc(mlen + 1));

					if (!mp) {
						std::cerr << "cannot allocate memory\n";
						std::exit(EXIT_FAILURE);
					}

					strcpy(mp, p);
				}
				~String()
				{
					if (mp)
						std::free(mp);
				}
				void print() const
				{
					std::cout << '['<<mp << "]\n";
				}

				size_t length()const
				{
					return mlen;
				}
			private:
				size_t mlen; 
				char* mp;
			};

			void foo(String s)
			{
				std::cout << "foo cagrildi\n";
				s.print();
				(void)getchar();
			}

			int main()
			{
				String str("bugun sinifin ozel fonkiyonlarini isliyoruz");

				str.print();

				foo(str); 

				str.print();
			}

		copy constructor� her zaman kendimizin yazmas�na gerek kalm�yor ��nk� standart k�t�phane bunu bizim yerimize yap�yor s�n�f�m�z�n elemanlar� ba�ka s�n�flar t�r�nden kaynak kullanan elemanlarsa 
		onlar kendi kaynak y�netimini kendileri yap�yorlar otomatik olarak deep copy yap�l�yor ��nk� onlar�n copy ctoru ona g�re yaz�lm��
			class Student
			{
				int age;
				int id;
				std::string m_address;
				std::vector<int> m_grade;
				// buna rule of zero deniliyor s�n�f�n special member functionlar�n�n yaz�m�n� derleyiciye b�rakm�� oluyoruz 
				 string ve vector s�n�f� kendi kopyalamalar�ndan kendileri sorumlu yani bunu bizim yerimize standart k�t�phanede olan s�n�flar�n copy copy ctorlar� yap�yor
			}

		�RNEK STRING SINIFINDAN DEVAM
		int main()
		{
			String str("bugun sinifin ozel fonkiyonlarini isliyoruz");

			str.print();
			if (str.length() > 10)
			{
				String sx{"ben blok icinde kullanilan bir yaziyim"};
				sx.print();
				sx = str; // bir s�n�f nesnesine atam operat�r� kullan�larak ayn� t�rden bir s�n�f nesnesi atand���nda bu atama i�lemini s�n�f�n �zel fonksiyonu olan Copy Assigment yap�yor
							operat�r overloading ile yap�l�yor bir s�n�f nesnesini bir operat�r�n operand� yap�yoruz operand� s�n�f nesnesi olan operat�r ifadesini derleyici bir fonksiyona yap�lan �a�r�ya d�n��t�r�yor 
							bu �ekilde �a��r�lan fonksiyonlara operator function deniliyor 
  				sx.print();
				(void)getchar();

			//  burda iki ayr� nesne var derleyicinin yazd��� copy assignment sx'nin mp eleman�na str'in mp eleman�n�n adresini at�yor bu y�zden dangling pointer oluyor

			}

			str.print(); // run timeda hata verir 
		}

		burda copy assignment bu �ekilde yaz�lmal�
			String& operator=(const String& other)
			{
				mlen = other.mlen;
				std::free(mp);

				mp = static_cast<char*>(std::malloc(mlen+1));

				if(!mp)
				{
					std::cerr << "cannot allocate memory\n";
					std::exit(EXIT_FAILURE);
				}
				strcpy(mp,other.mp);

				return *this;
			}

			ama kodda enteresan olan bir durum var

			SORU:
				int x = 10;
				x = x; // sentaks a��s�ndan bir hata yok buna self assigment deniliyor semantik olarak nesnenin de�i�memesi gerekir ��nk� kendine atama yap�l�yor,
				self assignment yazd���m�z String s�n�f� i�in olursa bir felaket olur

				str.print();

				str = str;

				str.print(); // other nesnesiyle *this ayn� nesne olmu� oluyor yazd���m�z copy assignmentta nesnenin de�eri de�i�medi�i halde biz kayna�� geri verdik bu y�zden ayn� nesnenin kayna��n� geri vermi� olduk
				bu durumda dangling pointer olmu� oluyor bu durumda adresleri kontrol etmemiz gerekiyor

			String& operator=(const String& other)
			{
				if(this == &other) // self assignment kontrol�
					return *this;

				mlen = other.mlen;
				std::free(mp);

				mp = static_cast<char*>(std::malloc(mlen+1));

				if(!mp)
				{
					std::cerr << "cannot allocate memory\n";
					std::exit(EXIT_FAILURE);
				}
				strcpy(mp,other.mp);

				return *this;
			}

		self assignment olabilecek farkl� bir durum

		void func(Myclass *p1, Myclass *p2)
		{
			*p1 = *p2; // arg�mana ayn� nesne ge�ilirse self assignment olma durumu yine var
		}

		DERLEY�C�N�N YAZDI�I COPY ASSIGMENT
			class Myclass
			{
				Myclass(const Myclass& r) : ax(r.ax),bx(r.bx),cx(r.cx) {}
				Myclass& operator=(const Myclass& r)  // geri d�n�� de�eri s�n�f t�r�nden L value referans
				{
					ax = r.ax;
					bx = r.bx;
					cx = r.cx; 

					return *this; // copy assigment kendisine atama yap�lan nesneyi d�nd�r�yor 

					derleyicinin yazd��� copy assignment s�n�f�n veri elamanlar�na di�er nesnenin veri elemanlar�n� copy assign ediyor 
					1)e�er elemanlar primitive t�rlerdense int'e int'i atam�� oluyoruz pointer'a pointer'� atam�� oluyoruz
					2)fakat bunlar s�n�f t�r�nden nesnelerse bu durumda s�n�f�n copy assignment fonksiyonu �a��r�l�yor 
				}
				Myclass& set(int){}
				void print()const

			private:
				A ax;
				B bx;
				C cx;
			};

			int main()
			{
				Myclass m1,m2;

				m1 = m2; // burda m2 yi de�i�tirme gayretimiz olmad��� i�in copy assignment'�n paramtresi const Myclass& olmas� gerekiyor

				m1.operator=(m2); // m1 i�in copy assignment �a��r�l�yor b�ylede yazabiliriz
								
				geri d�n�� de�erinin L value referans olmas� 
					1)atama operat�r�yle olu�turulan t�m ifadelerin L value olmas�n� destekliyor
			
				(m1 = m2).set(12).print(); // b�ylede yazabiliriz m1 i�in set fonksiyonu ve print fonksiyonu �a��r�l�yot
			}

			int x,y,z,t;
			x = y = z = t = foo(); // right associativity �zelli�i var yani bu ifade sa�dan sola do�ru de�erlendiriliyor

			x = (y = (z = (t = foo()))); // bu �ekilde yazmakla yukar�daki gibi yazmak aras�nda bir fark yok

			s�n�f t�r�nden olsalard� operat�r overloading sayesinde bu yine ge�erli olurdu 

			 x.operator=(y.operator=(z.operator=(t.operator=(foo())))); // s�n�f t�r�nden olsayd� bu �ekildede yazabilirdik
*/