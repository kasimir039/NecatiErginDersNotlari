/*

nested typelardan devam

	nested typelar�n class scopeta olmas�
		1)bu isimleri kullanabilmek i�in s�n�f ismiyle nitelememiz gerekiyor(qualified name)
			class Nec{
				public:
					class Nected{

					};

					enum class Pos {On,Off};
					using Dollar = double;
			};

			int main()
			{
				Nec::Nested x;
			}
			
		2)isim arama kurallar�n� de�i�tiriyor

		3)eri�im kontrol� sa�l�yor

		4)logic olarak bu s�n�fla ili�kisini vurguluyor yani bu t�rler bu s�n�fla ilgili vurgusu yap�l�yor

	ENCLOSING CLASS TERIMI
		class Nec{  // burda Nec s�n�f�ndan bahsederken enclosing class terimini kullanaca��z
			public:
				class Nected{

				};

				enum Pos {On,Off};
				usind Dollar = double;
		};
		
		SORU:enclosing class nested type'�n private elemanlar�na eri�ebiliyor mu? HAYIR
			nested class'�n private b�l�m� di�er classlara kapal�

			class Nec{
				public:
					class Nested{
						private:
							void foo();
							int mx;

							frined class Nec; // Nec s�n�f�n�n nested type'�n private elemanlar�na eri�mesini istiyorsak
					};


					void bar()
					{
						Nested ns;

						ns.foo();
						ns.mx = 5; // ikiside sentaks hatas�
						
						bu bildirimlerin ge�erli olmas�n� istiyorsak Nested class i�inde enclosing classa friend bildirimi yapmam�z gerekir

					}
			};

		SORU:peki nested class enclosing class'�n private b�l�m�ne eri�ebilir mi? EVET
			buradaki kurallar modern C++ ile de�i�ti
		
			class Nec{
				private:
					static int sval;
				public:
					class Nested{
						private:
							void foo()
							{
								auto val = sval; // ge�erli

								auto sz = sizeof(sval);
							}
					};
			};
				sval static olmasayd� sentaks hatas� olur muydu ve olsayd� olmas�n�n nedeni ne olurdu? 
					sentaks hatas� olurdu ama olmas�n�n nedeni private olmas� de�il ortada bir nesne olmad��� i�in hata olurdu
					��nk� sval static de�ilse sadece Nec t�r�nden bir nesnesinin bir sval'i olabilir
						void foo()
						{
							Nec mynec;
							auto auto = mynec.sval; // ge�erli

							auto sz = sizeof(sval); // uneveluated context oldu�u i�in burada dilin kurallar�na g�re bir nesneye ihtiya� yok
						}			

	member function�n i�indeki kulland���m�zdaki isim arama kurallar�yla bir ismi s�n�f�n i�inde kullanmam�z durumunda isim arama kurallar� birbirinden farkl�
		
		struct Data{
			int get()const;
		}

		class Nec{
			Data mdata; // struct Data
			void foo();
			using Data = int;
			Data mval{}; // int Data(�nce Nec'in class definition i�inde aran�yor)
		};

		void Nec::foo()
		{
			mdata = 5; // invalid
			mval = 5;
			auto x = mdata.get();
			auto y = mval.get(); // invalid
		}

		SORU:
			class Myclass{
				private:
					class Nested{
						public:
							void set(int);
					};
				public:
					static Nested create_nested();
			};

			int main()
			{
				Myclass::Nested nx; // nested type olan Nested class private o y�zden sentaks hatas�

				Myclass::Nested mx = Myclass::create_nested(); // sentaks hatas�
				auto nx = Myclass::create_nested(); // ge�erli ��nk� eri�im kontrol� ortada bir isim varsa uygulan�yor �stte ki �rnekte Myclass::Nested mx ifadesinde olu�an 
				sentaks hatas� eri�im kontrol� ama burada bir eri�im kontrol� s�z konusu de�il
				
				nx.set(2); // ge�erli
			}

	cppreference.com �rne�i
		int x, y; // globals

		class enclose
		{
		private:
			int x;
			static int s;

		public:
			struct inner {

				void f(int i)
				{
					x = i; // error can't write to non-static enclose::x wihhout instance
					int a = sizeof x; // error until C++11
					// OK in C++11 operand of sizeof is uneveluated
					// this use of the non-static enclose::x is allowed

					s = i;
					 
					::x = i;
					y = i;
				}

				void g(enclose* p, int i)
				{
					p->x = i; // OK assign to enclose::x (inner class encloing class'�n private elemanlar�na eri�ebilir)
				}
			};
		};

	SORU:enclosing class i�erisinde nested class'�n fonksiyonunu tan�mlayabilir miyiz? HAYIR
		class Enc{
			
			class Nested{
				void foo(int);
			};

			void Nested::foo(int) // bu definition sentaks hatas� ama namespace alan�nda tan�mlayabiliriz
			{

			}
		};

		void Enc::Nested::foo(int) // art�k ge�erli
		{
		 
		}

	SORU:fonksiyonu namespacete tan�mlasayad�k foo fonksiyonunun parametresi Nested class t�r�nden olsayd� tan�m�nda Nested ismini nitelemeden kullansak ve Nested
	t�r�nden nesne olu�tursak sentaks hatas� olur muydu? HAYIR ��nk� class scopeta kabul ediliyor
		 	class Enc{
			
				class Nested{
				void foo(Nested);
			};

			void Nested::foo(int) // bu definition sentaks hatas� ama namespace alan�nda tan�mlayabiliriz
			{

			}
		};

		void Enc::Nested::foo(Nested) // ge�erli
		{
			Nested n;
		}

		ama fonksiyonun geri d�n�� de�eri nested t�r�nden olursa global namespacete fonksiyonun geri d�n�� de�erini yazarken orada art�k scope i�inde de�il 
		art�k Enc::Nested �eklinde yazmam�z gerek  
			Enc::Nested Enc::Nested::foo(Nested x) 
			{
				return x;
			}
	
	M�LAKAT SORUSU:pimpl idiomu(pointer implementation)
		ama� bu idiyom ile s�n�f�n private b�l�m�n� gizlemek

		class Myclass{
			private:
				int mx,my;

				void foo(); 
		}
			s�n�f�n private b�l�m�n�n s�n�f�n ba�l�k dosyas�nda olmas�n�n duruma g�re istenmeyen baz� sonu�lar� var
			yani s�n�f�n private b�l�m�n� hi� g�stermeme �ans�m�z olsayd� g�stermeye g�re g�stermemenin avantaj� ne olurdu?
				
				1)include zincirleri y�z�nden compile time'�n uzamas� �nlenir ve dependency'den kurtulmu� oluruz
					
					nec.h

					#include "a.h"
					#include "b.h"
					#include "c.h"

					bunlar� include etmek demek bunlar�n include etti�i ba�l�k dosyalar�n�da include ediyoruz demek

					class Nec{
						private:
							A ax;
							B bx;
							C cx;
					};

					nec.h

						class Nec{
							private:
								struct pimpl;
								pimpl* mp;
						};
					
					nec.cpp
						#include "a.h" // art�k cpp dosyas� bu kodlar� include ediyor
						#include "b.h"
						#include "c.h"

						struct Nec::pimpl{
							A ax;
							B bx;
							C cx;
						};					
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
COMPOSITION
	1)nesne y�nelimli progralama taraf�nda s�n�flar aras�nda ili�ki bi�imini betimliyor
		ASSOCIATION
			bir i�in yap�lmas� i�in iki s�n�f�n bir arada olmas� gerekiyor s�n�flardan biri di�erini biliyor ve kullan�yor
			
			AGGREGATION
				associationun �zel bir bi�imi her aggregation bir association diyebiliriz burada farkl� olan iki s�n�fn nesnesi birlikte i�ini g�r�yor
				ama s�n�f nesnelerinden bir tanesi di�er s�n�f nesnesinin sahibi durumunda has a relation-ship
				
				COMPOSITION
					aggregation'�n bir alt kategorisi her composition bir aggregation her aggregationda bir association ama her aggregation bir compostion olmak zorunda de�il 
					aggregation'�n composition hale gelmesi i�in sahip olan nesneyle sahip olunan nesne aras�nda �m�rsel bir birliktelik olmas� gerekiyor
					�rne�in car ve engine aggregationda olabilir compostionda olabilir �rne�in araba motoruyla hayata geliyor araban�n �mr� bitti�inde motorunda �mr� bitiyor

	HAS-A-RELATIONSHIP
		class Engine{

		};

		class Car{
			private:
				Engine m_Eng; // her car nesnesi hayata geldi�inde Engine t�r�nden veri eleman�da hayata geliyor
				Car nesnesi dtor �a��r�ld���nda Engine nesnesi i�inde dtor �a��r�lacak hoca buna containment diyor

				Engine* mp; // Car s�n�f� new ifadesiyle nesne olu�turur Car s�n�f�n�n dtoruda nesneyi delete eder
		};

		SORU:Car s�n�f� Engine s�n�f�n�n private b�l�m�ne eri�ebilir mi? HAYIR
		
		SORU:Bu nesneler nas�l hayata geliyor? car nesnesi hayata geldi�inde engine nesnesi nas�l hayata gelicek?
		iki car nesnesi birbirine atand���nda engine nesneleri birbirine nas�l atanacak? 

		class Car{
			private:
				Engine mx; // her Car nesnesinin i�inde bir Engine nesnesi var 
			
			her car nesnesi hayata geldi�inde engine nesneside hayata gelecek car nesnesinin hayat� bitti�inde de engine nesnesinin hayat� bitecek
		};
	
		1)Engine s�n�f�n�n sizeof'u kadar Car s�n�f�n�n sizeof'u artacak
		2)default member initialization kullan�lmad�ysa Car s�n�f�n�n derleyici taraf�ndan yaz�lan ctor'u elemanlar� default initalize eder Car s�n�f�n�n ctoru
		Engine s�n�f�n�n default ctoruna �a�r� yapacak
			
			class Engine{
				public:
					Engine(){
						std::cout<<"Engine default ctor\n";
					}

					~Engine(){
					std::cout<<"Engine dtor\n";

					}
			};

			class Car{
				public:

				private:
					Engine e;
			};

			int main()
			{
				Car mycar; // bir s�n�f�n default initialize edilmesi default ctorun �a��r�lmas� demek
				ortada do�rudan Engine nesnesini g�rmesekte Car nesnesini olu�turdu�umuzda Car nesnesinin hayata gelme s�recinde
				program�n ak��� Car s�n�f�n�n ctorunun ana blo�una hen�z girmemi� durumdayken Engine nesnesi hayata gelmi� olacak bu son derece �nemli
				Car nesnesi destroy oldu�unda Car s�n�f�n�n dtoru �al��acak program�n ak��� dtor'un kodunun sonuna geldi�inde memberlar hayata gelme s�ras�yla ters s�rada
				destroy olacaklar
				
				�IKTI:
				Engine default ctor
				Engine dtor
			}

			s�n�f�n default ctoru olmasayd� derleyici taraf�ndan yaz�lan Car s�n�f�n�n default ctoru Engine s�n�f�n�n default ctoruna �a�r� yapacak 
			bir sentaks hatas� olu�acak ama derleyici sentaks hatas� vermek yerine yazmas� gereken speacial member functionu delete edecek
				class Engine{
					public:
						Engine(int){
							std::cout<<"Engine(int) ctor\n";
						}

				};

				class Car{
					public:

					private:
						Engine e;
				};

				int main()
				{
					Car mycar; // derleyici car s�n�f�n�n default ctorunu delete etmi� durumda  
					
					the default constructor of "Car" cannot be referenced -- it is a deleted function
				}

				Engine() = delete; // Engine s�n�f�n�n default ctoru delete edilmi� olsayd� derleyic Car s�n�f� i�in yazmas� gereken default ctoru yine delete edecekti

				D�KKAT:e�er default member initialization kullan�rsak derleyici implictly declared defaulted olsa bile default member initialization kullanmak zorunda
					class Engine{
						public:
							Engine(int);
					};

					class Car{
						private:
							Engine e{ 4 };
					};

					int main()
					{
						Car mycar; // ge�erli
					}
				
				D�KKAT:ctorun tan�m�n� biz yaparsak durum de�i�iyor
					class Engine{
						public:
							Engine(int);
					};

					class Car{
						public:
							Car(){} // sentaks hatas�n�n olma sebebi derleyici b�raya MIL sentaks�yla default ctora yap�lan �a�r�y� ekledi Engine s�n�f�n�n default ctoru olmad���
										i�in hata veriyor 'Engine': no appropriate default constructor available

							Car() : e{5}
							{

							}

						private:
							Engine e; // burada default member initialization kullan�lsayd� yukar�da hata olmazd� 
					};

					int main()
					{
						Car mycar; // sentaks hatas�
					}

					D�KKAT:elemanlar�n hayata gelme s�ras� bildirimdeki s�raya g�re esas al�n�r
						class Team{
							Lead x; // 1.s�rada hayata gelecek
							CppDeveloper c; // 2
							BackendDev b; // 3

							MIL sentaks�yla bu s�raya uymayan bir s�rayla bunlar� initalize edersek  
							Team() : c(12),b(2),x() {} // b�ylede yazsak bildirimdeki s�rayla hayata gelecekler 
						}
			
			1)CTOR
			program�n ak��� run timeda ctorun ana blo�una girmi� ise veri elemanlar� art�k hayata gelmi� durumda buradaki kod veri elemanlar�n� kullan�rsa
			hayata hen�z gelmemi� bir veri eleman�n� kullan�yor olur muyuz? HAYIR zaten onlar e�er hayata gelmesiyle alakal� bir exception throw etseydi 
			zaten program�n ak��� ctorun ana blo�una hi� girmemi� olurdu
			
			2)DTOR
				~Car()
				{
					dtorda s�n�f�n veri elemanlar� dtorun ana blo�undaki kodlar�n hepsi en son an�na kadar �al��t��� zaman veri elemanlar� halen hayatta oluyor

				} // program�n ak��� buraya geldi�inde elemanlar hayata gelme s�ras�n�n tersiyle hayata veda edecek

			3)COPY CTOR
				derleyici s�n�f i�in copy ctor yazarsa yani copy ctoru default ederse elemanlar� copy construct ediyor 
					
					class Myclass{
						public:
							Myclass(const Myclass& other) : ax(other.ax),bx(other.bx),cx(other.cx) // derleyicinin yazd��� copy ctor
							{

							}

							copy ctoru biz tan�mlarsak bunlar derleyici taraf�ndan art�k copy construct edilmeyecek bizim etmemiz laz�m e�er etmezsek
							derleyici default construct eder
						private:
							A ax;
							B bx;
							C cx;
					}

					�RNEK:
						class Member{
							public:
								Member()
								{
									std::cout<<"Member default ctor\n";
								}

								Member(const Member& other)
								{
									std::cout<<"Member copy ctor\n";
								}
						};

						class Owner{
							private:
								Member mx;

							public:
								Owner() = default;
								Owner(const Owner& other) // copy ctoru kendimiz implemente etti�imizde elemanlar� copy ctor etmezsek derleyici default construct edecek  
								{
									std::cout << "Owner copy ctor\n";

								}
						};

						int main()
						{
							Owner owner;
							Owner o(owner); 

							�IKTI:
							Member default ctor
							Member default ctor
							Owner copy ctor
						}

						Owner(const Owner& other) : mx(other.mx) // elemanlar� copy construct edersek art�k member'�n copy ctoruda �a��r�l�r
						{
							
						}

						�IKTI:
						Member default ctor
						Member copy ctor
						Owner copy ctor
			4)MOVE CTOR
				copy ctordaki t�m kurallar ile ayn�

					class Myclass{
						public:
							Myclass(Myclass&& other) : ax(std::move(other.ax),bx(std::move(other.bx)),cx(std::move(other.cx)) // derleyicinin yazd��� move ctor
							{

							}
						private:
							A ax;
							B bx;
							C cx;
					}

			5)ASSIGNMENTLAR(sadece copy assignment� yazd�m)
				copy assginment'� biz tan�mlarsak elemanlar�n copy assign edilmesinden yine biz sorumluyuz
				class Myclass{
					public:
						Myclass& operator=(const Myclass& other) // derleyicinin yazd��� copy assignment
						{
						
							// derleyicinin yazd��� kodda bildirimdeki s�rayla her bir veri eleman�na di�er nesnenin veri eleman� atan�yor
							
							ax = other.ax;
							bx = other.bx;
							cx = other.cx;

							return *this;
						}
					private:
						A ax;
						B bx;
						C cx;
				};

				�RNEK:
					class Member {
					public:
						Member& operator=(const Member&)
						{
							std::cout << "Member copy assignment\n";

							return *this;
						}
					};

					class Owner {
					public:
						Owner& operator=(const Owner& other) 
						{
							std::cout << "Owner copy assignment\n";
							mx = other.mx;

							// 1 tane bile elemana atama yapmazsak eleman hala kendi de�erini koruyor olacak
							return *this;
						}
					private:
						Member mx;
					};

					int main()
					{
						Owner x, y;

						x = y;
					}
				
		inheritance konusunda olan ili�kiye IS-A-RELATIONSHIP deniliyor
		containmenta alternatif olarak private inheritance t�r�nde �zel bir kal�t�m bi�imi var ileride g�rece�iz
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
STRING SINIFI
	nesnelerinin de�erleri yaz� olan s�n�f  
			
	DYNAMIC ARRAY
		��elerin bellekte ard���k olarak tutuldu�u veri yap�s�

		string s�n�f�da dynamic array elemanlar� char t�rden olan nesnelerden olu�an bir dinamik dizi

		dinamik dizi veri yap�s�nda index ile elemana eri�mek constant time O(1)
		
		ekleme ve silme i�lemleri sondan yap�ld��� zaman sondan yap�lan ekleme i�leminin karma��kl��� AMORTIZED CONSTANT TIME
			bu sorunun cevab� dinamik dizi veri yap�s�ndaki kapasite kavram� ��elerin tutuldu�u bellek alan� program�n �al��ma zaman�nda dinamik olarak allocate ediliyor
			dinamik olarak allocate edilmi� bellek alan�nda tutulabilecek ��e miktar�na kapasite deniliyor �rne�in 24 tane nesnesinin s��aca�� kadar bir bellek alan� allocate edilmi�se
			dinamik dizinin kapasitesi 24 ama fiilen tutulmakta olan ��e say�s� -> size 12,45,9,3,empty,empty,empty,empty burada size 4 ��nk� dinamik dizide 4 ��e tutuluyor
			ama 4 tane daha ��eninin tutulabilece�i bellek alan� allocate edilmi� durumda bu y�zden kapasite 8 kapasite de�eri size de�erinden daha b�y�k oldu�u s�rece sondan yap�lan 
			ekleme asl�nda bir pointer�n g�sterdi�i bellek alan�na yazma �eklinde ger�ekle�iyor ekleme a�amas�nda �yle bir duruma gelece�iz ki size ile kapasite e�it olacak kapasite 8 iken 
			size de�eri de 8 olacak bu durumda yeni bir bir ekleme istersen sondan ister ortadan olsun yer olmad��� i�in ba�ka bir allocatationa ihtiya� duyacak re-allocation olmak 
			zorunda en �ok problemin ortaya ��kt��� durum re-allocation �rne�in kapasite ve size 8 iken api yi kullanarak bir instertion kodu �al��t���nda art�k yeni bir bellek alan� 
			allocate edilecek eski bellek alan�nda ki ��eler yeni bellek alan�na kopyalanacak ama yeniden yap�lan bu allocaton'da kapasite 1.5 kat 2 kat �eklinde artt�r�lacak bu tamamen 
			implementasyona ba�l� microsoft kapasiteyi 1.5 kat artt�yor clang gibi implementasyonlarda 2 kat artt�r�yor b�ylece size kapasiteye e�it oldu�unda reallocationla 
			kapasite artacak yine yap�lan sondan eklemeler sabit zamanda olacak i�te bu karma��kl��a AMORTIZED CONSTANT TIME deniliyor
			bunu kontrol alt�na almakta m�mk�n ba�tan ka� ��e tutulaca��n� biliyorsak kapasiteyi rezerve edebiliyoruz
			
			re-allocationda 2 tane dikkat etmemiz gereken konu var
				1)re-allocation text time
					yeniden allocation yap�lacak eski bellek alan�ndaki ��eler yeni bellek alan�na kopyalanacak yada ta��nacak
					eski bellek blo�uda serbest b�rak�lacak ciddi bir maliyeti var
				
				2)dangling pointer
					eski bellek alan�n� g�steren pointerlar yada referanslar invalidate olacak 
					�rne�in bir api'yi kullanarak bir ekleme yapt���m�zda re-allocationa neden olursa o ekleme size ve kapasiteye e�itken yap�lm��sa
					eski bellek alan�na i�aret eden pointerlar,referenslar,iterat�rler invalid hale gelecek dangling pointer olacak
					dangling de�ilmi� gibi de-reference edersek undefined behav�our olur
		
	STL'DE OLAN CONTAINER KAVRAMI
		burdaki container terimi belirli t�rden ��eleri bir data structure kullanarak bir arada tutulmas�n� kullan�lmas�n� sa�layan s�n�flara
		containter s�n�flar deniliyor string,vector,list,deque,set,map gibi container s�n�flar

		do�rudan string isminde olan bir s�n�f�m�z yok basic_string olan bir class template var basic_string<char,std::char_traits<char>,std::allocator<char>> e�er type alias 
		kullan�lmasayd� string s�n�f� t�r�nden bir nesneyi tan�mlamak i�in b�yle yazmamam�z gerekirdi
				
		string s�n�f�n�n interface'i ortalama bir s�n�fa g�re �ok b�y�k hocan�n tabiriyle fat class
			
		string s�n�f�n�n yaz� i�leri i�in �zelle�tirilmi� bir container olduu�u i�in bir index interface'ine sahip fonksiyonlar�n kodlar�n� zorla�t�ran �nemli
		fakt�rlerden biri bu ayn� fonksiyonun baz� durumlarda hem index interface'ini kullanan bir overloadu hemde iterator interface'ini kullanan overloadu var
			
			index interface'i
				int main()
				{
					std::string str{ "necatiergin" };

					str.erase(6); // 6 indeksinden sonra bulunan t�m yaz�lar� siler

					std::cout << str;

					�IKTI: 
					necati
				
					burda beklenti 6.indeksteki e'nin silinmi� olmas� ama 6.indeksten itibaren t�m yaz� siliniyor
				}
			
			STL'de bulunan containerlar�n iterator interfacesini kullansayd�k bu sefer istedi�imiz indeksteki harfi silmi� olduk

			int main()
			{
				std::string str{"necatiergin"};

				str.erase(str.begin() + 6);

				std::cout<<str<<'\n';

				�IKTI:
				necatirgin // 6.indekste bulunan e harfini bu sefer ger�ekten silmi� olduk
			}

			burda kar��t�r�lan temel nokta iki ayr� interface oldu�u buna dikkat etmemiz gerekiyor en �ok kar��t�r�lan yerlerden biri

	SMALL BUFFER OPTIMIZATION(SMALL STRING OPTIMIZATION)
		hemen hemen b�t�n derleyiciler bu optimizasyonu kullan�yor

		derleyici string s�n�f�n�n implementasyonunda string s�n�f nesnesi i�inde bir bellek alan�n� buffer olarak kullan�yor
		string s�n�f� t�r�nden nesnesinin tutaca�� yaz� belirli bir uzunluk de�erine gelmedik�e dinamik bir bellek alan� allocate etmiyor

			void* operator new(std::size_t sz)
			{
				std::cout << "operator new called for the size of: " << sz << '\n';

				if (sz == 0)
					++sz;

				if (void* ptr = std::malloc(sz))
					return ptr;

				throw std::bad_alloc{};
			}

			void operator delete(void* ptr) noexcept
			{
				std::cout << "operator delete called for the address of: " << ptr << '\n';
				std::free(ptr);
			}

			int main()
			{
				std::string str("cengizhan"); // bu yaz� asl�nda allocate edilmi� bir bellek blo�unda de�il do�rudan string nesnesinin i�inde tutuluyor
				
				std::string str("developer: cengizhan varli"); // bu sefer s�n�r� a�t��� i�in bellek blo�u allocate ediliyor
			}

	size_type
		container s�n�flar�n baz� nested typelar� ortak �ekilde isimlendirilmi� ki generic programlama taraf�nda olmazsa olmaz bir gereklilik
		�rne�in container s�n�flar�n string::size_type isimli nested type'� var t�r� derleyiciye ba�l� olarak de�i�iyor size_type �ok de�erli bir nested type
		��nk� global fonksiyonlarda yada member functionlarda a�a��daki t�rler string::size_type'� t�r�nden de�i�kenlerle ifade ediliyor
		
			1)yaz�n�n uzunlu�unu d�nd�ren length ve size fonksiyonuun geri d�n�� de�eri t�r� string::size_type'� size_t
		
			2)kapasite de�eri

			3)karakterlerinin indexlerini parametre olarak isteyen fonksiyonlar string::size_type t�r�nden

			4)baz� fonksiyonlar bizden tane ve adet de�eri istiyor 5 tane A karakteri

	std::string s�n�f� null-terminated (yani \0 ile biten) byte stream (C-style string) tutmak zorunda de�ildir

	cstring demek bir adres demek o adreste sonunda null karakter olan bir yaz� var demek (C-style string) 

	string s�n�f�n�n �nemli get fonksiyonlar�
		.length()const; yaz�n�n uzunlu�unu d�nd�r�r // geri d�n�� de�eri string::size_type 
		.size()const; containerda olan �ye say�s�n� d�nd�r�r // geri d�n�� de�eri string::size_type
		.capacity()const; allocate edilmi� bellek blo�unda ka� ��e tutulabilece�inin de�erini d�nd�r�yor // geri d�n�� de�eri string::size_type
		.empty(const); size'�n 0 olup olmad���n� s�n�yor container bo� mu cevab�n� d�nd�r�yor true d�nerse container bo� demektir // geri d�n�� de�eri bool

		int main()
		{

			std::string str;

			std::cout << "size = " << str.size() << '\n';
			std::cout << "length = " << str.length() << '\n';
			std::cout << "capacity = " << str.capacity() << '\n';

			std::boolalpha(std::cout);

			std::cout << "empty = " << str.empty() << '\n';
		}
	 
		�IKTI:

		size = 0
		length = 0
		capacity = 15 // small string optimization sayesinde 15 karakterlik alan� kullanabiliyoruz
		empty = true
	
	CSTRING PARAMETRE(const char*)
		string s�n�f�n�n interface'inde fonksiyonlar�n parametre de�i�kenleri yada de�i�kenleri olacak ve bunlar i�in bellirli kal�plar var bunlara kar��l�k gelen
		pop�ler terimler var baz� fonksiyonlar bizden null terminated byte stream isteyecek �rne�in bir fonksiyonun parametresi sadece const char* ise bu fonksiyonun
		parametresinin cstring oldu�unu anlayaca��z (C-style string) yani bu fonksiyon bizden null terminated byte stream istiyor demek oluyor b�yle bir fonksiyona
		adres ge�ersek ve ge�ti�imiz adresteki yaz� null terminated byte stream de�ilse undefined behaviour olur 

	DATA PARAMETRE(const char*,size_t n)
		bir fonksiyonun parametresi yine bir null terimated byte stream ve onun yan�na string::size_type'�(size_t) istiyorsa bu parametrik yap�ya data deniliyor
		bu fonksiyon bizden bir adres ve bir tam say� istiyor kullanaca�� yaz� art�k null terminated byte stream de�il verdi�imiz adresten ba�layarak n kadar karater girmemizi istiyor 

	FILL PARAMETRE(size_t,char c)
		string::size_type'�(size_t) ve char parametre al�yor yani yapmak istedi�imiz i�lem �rne�in 5 tane A karakteri gibi bir yaz�

	SUBSTRING PARAMETRE
		bir ba�ka string nesnesinin tuttu�u yaz�y� kullanacak demek(const std::string&)

		string nesnesinin tuttu�u yaz�n�n belirli indeksli karakterinden ba�layarak geriye kalan b�t�n karakterlerin olu�turdu�u substring �st�nde
		i�lem yapacak demek(const std::string&,size_t idx)

		string nesnesinin tuttu�u yaz�n�n belirli indeksli karakterinden itibaren n tane karakter �st�nde i�lem yapacak demek(const std::string&,size_t idx,size_t n)		
*/