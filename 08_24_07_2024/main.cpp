/*

function overloading ile ilgili ilgili bir konu daha var
	C++ dilinde proje geli�tirirken C de olu�turulmu� kaynak dosyalar�n�da kullan�yoruz

		zeki.h
			int sum(int x,int y);
		zeki.c
			int sum(int x,int y)
			{
				return x + y;
			}

		main.cpp
			#include "zeki.h"

			int main()
			{
				auto x = sum(45,78);

				std::cout<<x;
			}

		iki dil aras�nda ki linker fark� oldu�u i�in linker hatas� verir C derleyicileride C++ derleyicileride inline expansion s�z konusu de�ilse
		�a��r�lan foknsiyona ili�kin linkera y�nelik derleyici olu�turdu�u obje dosyada bir external reference yaz�yor yani �a��r�lan fonksiyonu temsil eden bir referans derleyici ile
		linker aras�nda kararla�t�r�lm�� linkerda obje dosyalar� aras�ndaki ba�lant�y� derleyicinin obje dosyalara yazd��� external referenslar� takip ederek birle�tirme i�lemlerini yap�yor
		C dilinde function overloading yok fakat C++ dilinde function overloading var C dilinde function overloading olmad��� i�in derleyiciler obje dosyaya �a��r�lan fonksiyona 
		ili�kin bir referans isim yazd�klar�nda bu isim sadece fonksiyonun ismi ile dekore ediyorlar 

		C nin yazd��� isim �rne�in ��yle olsun C de buraya kadar yeterli ba�ka bir sum fonksiyonu olamaz
			@sum

		fakat C++ derleyicileri i�in bu durum ge�erli de�il e�er derleyici ger�ekten linker i�in yazaca�� referans ismi sadece fonksiyonun isminden dekore etseydi
		function overlaoding olmas� durumunda iki ayr� overload aras�ndaki fark nas�l anla��lacakt� C++ derleyicinin referans isim olarak objeye yazmas� farkl� bir deceration gerekiyor
			@sum_i_i // tamamen derleyiciye ba�l� hoca �rnek olarak verdi int int parametreli sum fonksiyona ili�kin overloading
			@sum_d_d // double i�in

		yukar�daki problemde derleyicinin bu fonksiyonun C de yaz�lm�� C de derlenmi� bir fonksiyon oldu�unu bilmedi�i i�in derleyici do�al olarak o fonksiyonuda 
		C++ fonksiyonu olarak ele al�yor sum �a�r�s�nda linkera referans yazarken C++ tarz� dekore ediyor b�ylece link a�amas�na geldi�inde linker fonksiyonu bulam�yor 
		��nk� ikisi ayn� de�il ger�ekte olan sum fonksiyonu C diline g�re dekore edilmi�

			zeki.h
				extern "C" int sum(int x,int y); // extern "C" bildirimi ile link a�amas�ndaki hata gitmi� olur bunun C derleyicisi ile derlenece�ini belirtiyor

			zeki.c
				int sum(int x,int y)
				{
					return x + y;
				}

		main.cpp
			#include "zeki.h" 

			int main()
			{
				auto x = sum(45,78);

			}

		Extern C decleration(C++ dilinde olan bir bildirim)
			bunun ��z�m� �u �ekilde biz derleyiciye �yle bir bildirim yap�caz ki diyece�iz ki derleyici bu fonksiyon bir C fonksiyonu C de derlenmi� dolay�s�yla sen bu fonksiyona 
			�a�r� yaparken bunu C tarz� dekore ediceksin C++ tarz� de�il ��nk� C++ tarz� dekore ederse linker bulam�yacak buna extern C bildirimi deniyor

		ama ��yle bir problem var mod�l C de derlenecek ama hem C de hemde C++ dilinde kullan�labilecek
			o�uzhan.h
				int foo(int,int); // c derleyicisinde extern c bildirimi olmad��� i�in bildirimi b�yle g�rmesi gerekiyor
				
				ama c++ derleyicisi g�r�cekse
					extern "C" int foo(int,int); �eklinde g�rmesi gerekiyor bu problemin ��z�m� ayr� ayr� headlerlar olu�turmak olabilir C de kullan�lacak header 
					C++ dilinde kullan�lacak header fakat onun yerine conditional compiling(ko�ullu derleme) komutlar�ndan faydalan�yoruz

					e�er diyelim ki birden fazla fonksiyonun extern "C" bildirimini yapacaksak bunu yapman�n alternatif bir yolu var
						extern "C"
						{
							int foo(int,int);
							int bar(int,int);
							int baz(int,int);
							int bom(int,int);
							
							bu durumda bu fonksiyonlar�n her biri i�in extern "C" bildirimi yapm�� oluyoruz bunu b�yle olmas�n�n esas sebebi conditional comopiling ile 
							hem C ye hemde C++ diline uygun hale getirmek
						}

						samet.h
							bu headerdaki bildirimleri hem C derleyicisine hemde C++ derleyicisine vermek istiyorum ama C++ derleyicisinin extern "C" bildirimi ile g�rmesini istiyorum
							C de de C++ ta da pre-defined macro denen varl�klar var(�n tan�ml� makro)

							#ifdef __cplusplus
							extern "C" {
							#endif

								int foo(int,int);
								int bar(int,int);
								int baz(int,int);

							#ifdef __cplusplus
							}
							#endif
--------------------------------------------------------------------------------------------------------------------------------------------------
CLASSES
	C++ Sadece Nesne Y�nelimli Programlama dili de�il NYP'ye de destek veren �ok paradigmal� bir programlama dili C++ '�n g�c�n�n en �nemli k�sm� Data abstraction kavram� 
	hocan�n kendi tan�m� ile problem domaninde ki varl�klar�n yaz�l�msal olarak temsil edilmesi 
	
	classlar c++ dilinin sentaks�n�n en fazla kural bar�nd�rd��� yer

	C de bulunan structlar C++ dilindede bir s�n�f ister struct anahtar kelimesini kullanay�m ister class'� kullanal�m olu�turdu�umuz t�rler class type

	bir s�n�f olu�turmak i�in derleyiciye bir s�n�f�n varl���ndan haberdar etmek i�in ya o s�n�fa ili�kin bir bildirimini yada o s�n�f�n tan�m�n� yapar�z

	class Nec;(incomplete type) // standart�n kulland��� teknik terim forward decleration deniliyor hoca complete type ile incomplete type konusuna de�inecek
	
	C++ dilinde s�n�flar�n hi� bir member'� olmayan s�n�f olu�turulabilir bunlara empty class deniliyor
		class Nec{};

		class Nec
		{
			// s�n�f�n i�inde bildirilen varl�klara class members deniliyor bu memberlar farkl� kategorilerde olabiliyor
				1)data member -> int mx;
				2)member function -> void foo();
				3)type member - member type- nested type hepsi ayn� anlamda -> enum,typedef,using,union,class,struct
					class Nec{
						class Erg // nested type;
						{

						};
					};
		};

		class d���nda tan�mlanan namespace scopeta olan fonksiyonlar i�in global function/free function/stand-alone function terimlerini kullanabiliriz
			void foo();

	C++ SCOPE KATEGOR�LER�
		1)namespace scope(file scope'u da i�eriyor)
		2)block scope
		3)class scope
		4)function prototype scope
		5)function scope

		ismin kapsam� ve nerelerde kullan�labilece�ine dair kurallar bu 5 kural setinden birine ili�kin olmak zorunda
			
	CLASS SCOPE
		�yle isim kullan�mlar� var ki bu kullan�mlara ili�kin isimler bir s�n�f tan�m�nda aran�rlar 3 tane senaryo var bu senaryolar�n olu�turdu�u k�meye 
		qualified name(ismin nitelenmesi) deniyor
		
			a)bir isim nokta operat�r�n�n sa� operand� ile kullan�l�m�ssa -> x.y (x hangi s�n�f t�r�nden nesneyse o s�n�fta y yi arayacak)
			b)ok operat�r�n�n(member selection arrow) sa� operand� olarak kullan�l�yorsa -> ptr->a (ptr hangi s�n�f t�r�nden adres ise a y� o s�n�fta arayacak)
			c)scope resolution operat�r�n�n sa� operand� olarak kullan�l�yorsa Nec::b (Nec s�n�f�nda b ismini arayacak) 
			
		struct Nec
		{
			int x;
		}


		int main()
		{
			auto b = x; // x ismini burda bulamayacak sentaks hatas� verecek

			Nec::x; // b�yle �a��rmak i�in x'in static olmas� gerekiyor
			
			Nec mynec;

			mynec.x // mynec Nec s�n�f�ndan nesne oldu�u i�in x de�erine ula��r

			Nec * necptr= &mynec;

			necptr->x; // necptr Nec s�n�f� t�r�nden bir adres oldu�u i�in Nec s�n�f�ndaki x de�erine ula��yor

		};

		int x; // global namespace

		class Myclass
		{
			int x; // Myclass class scope
		}

		class Nec
		{
			int x; // Nec class scope
		}

		farkl� scopelar� olduklar� i�in hata vermez
	
	NAME LOOKUP VE CONTEXT CONTROL KONUSUNUN KARI�ITIRILMASI 
		
		1)namelookup
			2)context control
				3)acces control yap�l�r

		int func(int x,int y)
		{
			return x + y;
		}

		int main()
		{
			int func = 4;
			func(2, 5); // func de�i�keni burda func fonksiyonunu maskeledi(namelookup ba�ar�l� oldu ve bitti bir daha namelookup ba�lamaz burda context controle tak�ld�)

			}

	ACCESS CONTROL
		class Myclass
		{
			// public: anahtar kelimesi bulunsayd� access controle tak�lmayacakt�
			int x; // x default olarak acces control bildirilmedi�i i�in private
		};

		int main()
		{
			Myclass m;
			m.x = 5; // Myclass::x cannot access private member declared in class Myclass
			bu kod namelookuptan ba�ar�yla ge�ti context controldende ge�ti ama en son access controlde tak�ld�
		}

	NOT:struct ile class anahtar kelimesinde ki 1 2 tane farkl�klara hoca ilerde de�inecek nested typelar i�in b�yle bir ayr�m yok

	DATA MEMBER VE MEMBER FUNCTIONLARI �K� KATEGOR�YE AYIRIYORUZ
		data member
			a)non-static data member -> int x; 
				s�n�flar�n non-static data memberlar� s�n�f nesnesinin(object) kendisine ait bu y�zden storage de�erini artt�r
				nesne y�nelimli programlama taraf�nda kullan�lan terim object burda biraz kavram karma�as�n� do�uruyor C++ dilinde ki object terimi NYP deki object terimi de�il 
				yani C++ standart� objecti NYP deki object anlam�nda kullanm�yor NYP deki object ve instance terimleri s�n�f t�r�nden nesnelerle ili�kilendiriliyor 
				bu y�zden s�n�flar�n non-static veri elemanlar�na instance variable deniliyor
								
				class Myclass{
					int x,int y;
				};

				int main()
				{

				Myclass m1,m2; // m1'in de x ve y de�i�keni olur m2'nin de x ve y de�i�keni olur

				}

				bir veri eleman�na sahip olmasa dahi s�n�f�n storage de�eri 1 byte'd�r sizeof hi� bir zaman 0 de�eri �retmez

				class Myclass{

				};

				int main()
				{
					Myclass m;
				}

			b)static data member -> static int x; 
		member function
			a)non-static member function -> int foo();
			b)static member function -> static int foo();

		SORULAR:
			1)function overloading var m� yok mu?
				void func(int); // namespace scope

				class Myclass
				{
					void func(double); // bu func class scopeta oldu�u i�in function overloading yoktur ��nk� farkl� scopetalar
				}

			2)function overloading var m� yok mu?
				class Myclass
				{
					void func(double); 
					void func(int); 

					// scopelar� ayn� oldu�u i�in function overloading
				}

			3)function overloading mi re-decleration m�?
					void func(int,int);
					void func(int,int); // bunlar re-decleration

				class Myclass{
					void func(int,int);
					void func(int,int); // s�n�flar�n member functionlar� re-decleration edilemez bu y�zden sentaks hatas�
				}
		
		ACCESS SPECIFIER
			s�n�flar�n memberlar� s�n�f�n eri�im ayr�cal�kl� alanlar�ndan birinde bildirilmek zorunda 3 tane access scpecifier mevcut
			public
				bir s�n�f�n public ��elerine o s�n�ftan olan nesnenin t�m public b�l�m�ne eri�imi var
			protected
				inheritance ile ilgili s�n�f�n kendisi ve o s�n�ftan kal�t�m yoluyla elde edilen s�n�flar eri�ebiliyor
			private
				s�n�f�n kendisine a��k ama d��ar�ya kapal� yani s�n�f�n i�inde eri�ilebilirler
			
			class Myclass
			{
				public: // private alan�na kadar public eri�im stat�s�nde
							
					int x;

				private: // protected alan�na kadar private eri�im stat�s�nde
					int y;
				
				protected: // alt�nda her hangi bir ba�ka access specifier belirtilmezse t�m belirtilen memberlar protected olur
					int z;
			}

			bu keywordler birden fazla kez kullan�labilir
				public:

				private:

				public:
			
			struct ile class aras�ndaki ilk fark(bir fark daha var inheritance konusunda g�r�lecek)structlarda default eri�imleri public classlarda ise private
				struct Nec
				{
					int x;
					void foo();
				}

				class Erg
				{
					int y;
				}
				
				int main()
				{
					Nec nec;
					Erg erg;

					nec.x = 10; // ge�erli;

					erg.y = 5; // access  controle tak�ld�
				}
				
			client kodlar�n do�rudan isimle eri�mesini istemedi�imiz s�n�f�n �yelerini s�n�f�n private b�l�m�ne koyar�z ama clientlar�n do�rudan isimle kullanmas�n� 
			istedi�imiz kodlar� s�n�f�n public b�l�m�ne koyuyoruz bu ilkeye DATA HIDING YADA INFORMATION HIDING denir 

				class Myclass
				{
					void foo(int); // private access
				}

				int main()
				{
					Myclass m;
					
					m.foo(12); // eri�im hatas�
				}

			SORU:
				1)kod legal mi ve function overloading var m� yok mu?
				
					class Myclass
					{
						public:
							void foo(int);
						private:
							void foo(double); // access specifierlar farkl� bir scope de�il hepsi ayn� class scopeta oldu�u i�in function overloading var ve kod legal 
					}; 
			
			s�n�f�n veri elemanlar�n� tipik olarak private b�l�m�ne koyuyoruz b�ylece bir tak�m avantajlar sa�lam�� oluyoruz
				1)s�n�f�n veri elemanlar�n� ve bunlar�n t�rlerini bilmezsek o s�n�f� daha kolay kullanabiliyoruz �st�m�zdeki ��renme y�k� azal�yor
				2)s�n�f nesnenelerini run timeda hizmet verirken �al��ma �eklini bozmay� riske etmemi� oluyoruz
			
				mesela s�n�f�n t�m memberlar�n� public b�l�m�ne koysayd�k bu memberlara nokta operat�r�yle yada ok operat�r�yle herkes eri�ecekti onlar� olmas� gereken 
				de�erler d���nda ba�ka de�erler verilmesi kontrol�m�zden ��kacakt� e�er s�n�f�n elemanlar�nda bir de�i�iklik yap�lsa o zaman kullan�c� kodlar�nda de�i�tirilmesi
				gerekicekti buda implementasyona ba��ml�l�k demek s�nf�n private b�l�m�ne veri elemanlar�n� koydu�umuz zaman zaten client kodlarla onlar�n ili�kisini kesiyoruz
				alaca��n hizmeti bizim sundu�umuz fonksiyonlara �a�r� yaparak alacaks�n demi� oluyoruz ve veri elemanlar�n� kullanmad��� i�in daha sonra s�n�f�n impelemansyonunda 
				veri elemanlar�n� de�i�tirmemiz durumunda client kodlar k�r�lmayacak veri gizlemenin temel mant��� bu
				
				eri�im kontrol� illa uygulanmak zorunda de�il hoca buna de�iniyor
					s�n�f prblem domaninide bir varl��� temsil ediyor ama s�rf information hiding olsun diye private b�l�m�ne koyulmu� get ve set fonksiyonlar� koyulmu� 
					ama bir s�n�f�n nesneleri set edilmiyor  
					k�sacas� private olmas� gerekmiyorsa private yapma

				C dilindede public private ayr�m� dosya baz�nda var 
					global bir de�i�ekene di�er dosyalardan eri�im sa�lamak istiyorsak
						extern int x; // de�i�enler default extern de�il extern anahtar s�zc���n� belirtmemiz gerekiyor
					
					bir fonksiyonun client kodlar taraf�ndan �a��r�lmas�n� istiyorsak header dosyas�nda extern bildirimini yap�yoruz
						void func(int); // default olarak extern
					
					ama clientlar�n do�rudan eri�mesini isteme�imiz sadece implementasyonun eri�mesini istedi�imiz global de�i�kenleri yada fonksiyonlar� static anahtar
					s�zc���yle tan�ml�yoruz
						static int g;
				
		SINIFLARIN MEMBER FUNCTIONLARI
			sentaks d�zeyinde client kodlar�n sanki c deki struct'�n elemanlar�na nokta operat�r�yle ve ok operat�r�yle eri�ir gibi isimlere eri�tikleri ama asl�nda o eylemi yapan 
			s�n�f nesnesinin adresini �rt�l� olarak alan fonksiyonlard�r s�n�f�n non-static member functionlar� t�pk� C de ki global fonksiyonlarda oldu�u gibi bir s�n�f
			nesnesinin adresini isteyen bir s�n�f nesnesinin adresiyle �a��r�lan fonksiyonlar sentaks 
			d�zeyinde gizli parametre olarak bulunur yani s�n�f�n non-static member functionlar� implicitly olarak bir s�n�f nesnesinin adresini al�r ve her zaman 1 adet 
			fazla gizli parametreleri bulunur
			
				class Nec
				{
					public:
					void foo(); // bu fonksiyonun g�r�n�rde 0 parametre de�eri var ama ger�ekte 1 tane gizli parametre de�i�keni var bu s�n�f t�r�nden bir pointer -> Nec*
				};

				int main()
				{
					Nec mynec;
					mynec.foo(); // derleyici burda mynec nesnesinin adresini Nec s�n�f�ndaki foo fonksiyonunun parametresine ge�iyor foo global bir fonksiyon olsayd� 
					ayn� bu �ekil kullanacakt�k -> foo(&mynec); ikisi ayn� anlamda
				}

				// class definiton
				class Fighter
				{
					public:
					int id;
					const char name[20];

					void attack(const Fighter fighter&);
				};

				int main()
				{
					Fighter fighter1,fighter2;

					fighter1.attack(fighter2); // burda fighter1 fighter2 ye sald�r�yor

					member functionlar�n ve referanslar�n sa�lad��� yarar kodun okunmas�n�n ve kullan�lmas�n�n kolayla�mas�
				}

				headera client kodlar�n kullanaca�� isimlere ili�kin varl�klar� s�n�flar �ok b�y�k �o�unlukla ama her zaman de�il class definition headerda olucak

				�yle bir s�n�f olabilir ki clientlarla hi� bir alakas� olmaz sadece implementasyon taraf�nda kullan�l�yor olabilir b�yle durumlarda header file'a koymak yerine 
				implementasyon dosyas�na koyaca��z b�yle s�n�flar� nested typeta yapabiliriz
			
				person.h
					class Prson
					{
						public:
							void set_person_name(const char* p);
					};
				person.cpp
					global fonksiyonlardan farkl� olarak derleyicinin bu fonksiyonun tan�m� olu�unu anlamas� i�in nitelenmi� isim kullan�yoruz
						void Person::set_person_name(const char* p)
						{

						}

				class Nec
				{
					public:
						void set(int x,int y);
					private:
						int mx;my;
				};

				int main()
				{
					Nec::set(3,6); // burda namelookup ba�ar�y�la yap�l�r ama context kontrole tak�l�r ��nk� set fonksiyonu bir non-static member function oldu�u i�in 
									  bir s�n�f nesnesiyle �a��r�lmas� gerekir 
				}

				member functionlar�n nitelenmemi� ismin kullan�lmas� durumunda isim arama kurallar� farkl�
					bloklarda aranacak 
					sonra class definition i�inde aranacak

					void Nec::set(int x ,int y)
					{
						x = x; // Nec s�n�f�ndaki x parametre de�i�keni taraf�ndan maskelenmi� bunu �nlemek i�in qualified name olarak Nec::x kullanabiliriz
						Nec::x = x; // scope resloution operat�r�n� binary olarak kullan�yoruz b�ylelikle direkt class scopeta arayacak	
					}
*/