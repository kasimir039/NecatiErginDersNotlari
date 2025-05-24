/*
DESTRUCTOR
	�n�nde tilda tokeni vard�r
	~Myclass();
	1)parametresi olamaz
	2)overload edilemez
	3)geri d�n�� de�eri kavram� yoktur
	4)private yada protected olabilir ama clientler taraf�ndan �a��r�lmas� sentaks hata� olu�turur
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
T�m parametreleri varsay�lan arg�man alan constructorlara default constructor denir
	Myclass(); // default ctor

SPECIAL MEMBER FUNCTIONS
	s�n�flar�n baz� �ye fonksiyonlar� special member function olarak nitelenmi�(�zel �ye fonksiyonlar) bu fonksiyonlar� �zel yapan bu fonksiyonlar�n baz� nitelikleri
	modern C++ �ncesi bu kategoride 4 adet fonksiyon vard� modern C++ ile 6 ya y�kseldi
	bu fonksiyonlar� special yapan 1.�zellik
		belirli ko�ullar sa�land���nda bu fonksiyonlar�n kodunun bizim taraf�m�zdan de�il derleyici taraf�ndan yaz�labilmesi belirli kurallar ve belirli ko�ullar olu�tu�unda derleyici bu i�lemi yapabiliyor
	
	1)default ctor
	2)destructor
	3)copy ctor
	4)move ctor // modern C++ ile eklendi
	5)copy assignment
	6)move assignment // modern C++ ile eklendi

	special member functionlar cpp dosyas�ndada tan�mlanabilirler class definition i�indede tan�mlanabilirler
	
	modern C++ �ncesinde derleyici taraf�ndan yaz�lmas�na fonksiyonun generate edilmesi terimi kullan�l�yordu �imdi derleyici taraf�ndan default edilmesi terimi kullan�l�yor
	
	SORU
		1)constructor demek special member function m� demek?
			Cevap HAYIR
			Myclass(int);
			Myclass(int,int); // bunlar special member function de�il
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CONSTRUCTOR VE DESTRUCTOR NE ZAMAN �A�IRILIYOR?
	1)STATIC OMURLU NESNELERE ORNEK
		class Myclass
		{
		public:
			Myclass()
			{
				std::cout << "Myclass default ctor this = " << this << '\n';

			}
			~Myclass()
			{
				std::cout << "Myclass destructor this = " << this << '\n';

			}
		};

		Myclass m; // bir s�n�f nesnesini default initialize etti�imizde derleyici default ctoru �a��r�r ve nesne default ctor ile hayata gelir

		int main()
		{
			std::cout << "main has just started\n";
			std::cout << "main is finishing\n";

		}

	 �IKTI:
		Myclass default ctor this = 00007FF70EF41200
		main has just started
		main is finishing
		Myclass destructor this = 00007FF70EF41200

	SORU:
	ayn� kaynak dosyada birden fazla static �m�rl� de�i�ken olu�tursayd�k bunlar�n hayata gelme s�ras� belirli mi?
	kesinlikle EVET bildirimdeki s�raya g�re hayata gelecekler
	Myclass m1,m2,m3 // �nce m1 sonra m12 sonra m3 hayata gelecek ama D�KKAT destructorlar ters s�rayla �a��r�lacakt�
	�nce m3 sonra m2 en son m1 nesnesinin destructor� �a��r�l�r(hayata son gelen hayata ilk veda eden olur(yaz bunu g�zel laf :D))
	
	�IKTI:
		Myclass default ctor this = 00007FF688E41202
		Myclass default ctor this = 00007FF688E41200
		Myclass default ctor this = 00007FF688E41201
		main has just started
		main is finishing
		Myclass destructor this = 00007FF688E41201
		Myclass destructor this = 00007FF688E41200
		Myclass destructor this = 00007FF688E41202
	
	SORU:
	Farkl� kaynak dosyalardaki birden fazla static �m�rl� de�i�kenlerin hayata gelme s�ras� belirli mi ?
	HAYIR belirli de�il buda b�y�k bir sorun olu�turuyor bu probleme kar��l�k gelen terim STATIC INITIALIZATION FIASCO
		
		cengizhan.cpp
			C cx;

		doga.cpp
			D dx;

		oguzhan.cpp
			O ox;

	bunlar�n hauyata gelme s�ras� �ok �nemli s�k yap�lan hatalardan biri mesela buradaki CX hayat geldi�inde CX'in constructor� DX'i kullan�yorsa 
	CX'in DX'i kullanabilmesi i�in DX'inde hayatta olmas� laz�m ama b�yle bir garanti yok

	2)STATIC OMURLU YEREL NESNELERE ORNEK
		fonksiyonlar�n i�inde static anahtar kelimesiyle tan�mlanan de�i�enler

		void func()
		{
			static int cnt{};
			std::cout<<"func" << ++cnt<<".kez cagirildi\n";
			static Myclass m;

			fonksiyon �a��r�lmad��� s�rece hayata gelmiyorlar 

			fonksiyon �a��r�ld���nda constructor �a��r�lacak ama sadece ilk kez �a��r�ld���nda fonksiyon her �a��r�ld���nda hayata yeni bir nesne gelmez nesne sadece bir defa hayata gelir
		}

		int main()
		{
			std::cout<<"main basliyor\n";

			func();
			func();
			func();
			func();

			std::cout<<"main sonlaniyor\n";
		}

			�IKTI:
			main basliyor
			func 1.kez cagirildi
			Myclass default ctor this = 00007FF654C10204 // ayn� nesne hayat�n� devam ettiriyor constructor sadece bir defa �a��r�l�yor
			func 2.kez cagirildi
			func 3.kez cagirildi
			func 4.kez cagirildi
			main sonlaniyor
			Myclass destructor this = 00007FF654C10204

			static �m�rl� yerel de�i�kenlerin main fonksiyonunun bitmesinden sonra sonlan�yor,

	3)OTOMATIK OMURLU DEGISKENLER
		program�n ak��� onlar�n tan�m�na her geldi�inde ctor �a��r�lacak 
		prgram�n ak��� onlar�n scope'unun sonunu belirleyen closing brace'e geldi�inde hayatlar� bitecek
		void func()
		{
			static int cnt{};

			std::cout << "func ["<< ++cnt << "]" << '\n';
			 Myclass m;
			std::cout << "func [" << ++cnt << "]" << '\n';

		}

		int main()
		{
			std::cout << "main basliyor\n";

			func(); // program�n ak��� func'a girdi�inde nesne hayata gelicek ve hayata gelen her nesne farkl� bir nesne olmu� olacak
			func();
			func();
			func();

			std::cout << "main sonlaniyor\n";
		}

		�IKTI:
		main basliyor
		func [1]
		Myclass default ctor this = 000000175BCFF754
		func [2]
		Myclass destructor this = 000000175BCFF754
		func [3]
		Myclass default ctor this = 000000175BCFF754
		func [4]
		Myclass destructor this = 000000175BCFF754
		func [5]
		Myclass default ctor this = 000000175BCFF754
		func [6]
		Myclass destructor this = 000000175BCFF754
		func [7]
		Myclass default ctor this = 000000175BCFF754
		func [8]
		Myclass destructor this = 000000175BCFF754
		main sonlaniyor

		otomatik �m�rl� nesnelerde hayata bildirildi�i s�raya g�re geliyor ve destructor hayata gelme s�ras�s�n tam tersi �ekilde �a��r�l�yor
			Myclass m1,m2,m3 

	SORULAR
		1)ka� kez constructor �a��r�lacak?
			Myclass mx;
			Myclass& r1 = mx;
			Myclass& r2 = mx;

			bir referans� nesneye ba�lamam�z bir nesne olu�turmuyor(pointerlar i�inde ayn�s� ge�erli)

			R value referans olsayd�?
				Myclass mx;
				Myclass&& r1 = std::move(mx);
				Myclass& r2 = mx;

			R value referans olmas� yeni bir nesne olmayaca�� anlam�na gelir miydi? EVET ister L value ister R value referans olsun bunlar nesnelere ba�lanan
			isimlerdir

		2)S�n�f elemanlar� dizi t�r�nden olabilir mi? EVET
			Myclass ar[5];
			�ok kullan�lm�yor ��nk� bunlara daha iyi alternatifler var standart k�t�phanenin array s�n�f� gibi

			burda s�rayla dizinin her eleman� i�in 5 kez constructor �a��r�l�r 

		3)M�lakatta sorulan soru 1'den 100'e kadar say�lar� ekrana yazd�raca��z ama d�ng� kullanmayaca��z
			class Myclass
			{
			public:

				Myclass()
				{
					static int count;

					std::cout << ++count << " ";
				};

			};

			int main()
			{
				Myclass m[100];

			}

	HANG� DURUMLARDA DEFAULT CTOR �A�IRILIR?
		1)S�n�f nesnesini default initialize etti�imizde
			Myclass m;
		2)Value initialization
			Myclass m{};

		�RNEK:
			1)most vexing parse �rne�i
				Myclass m(); // burda nesne tan�m� yap�lm�yor burda bir bildirim yap�l�yor ismi M olan geri d�n�� t�r� Myclass olan bir fonkiyon tan�m� yap�yoruz
				burda value initialization kullanmam�z gerek

		SORU:
			1)Myclass s�n�f�n�n constructor� var m�?
				class Myclass
				{
					public:
						// EVET var bu konu �ok karma��k hangi durumda derleyici hangi special member functionlar� bizim i�in default ediyor ilerde g�rece�iz
				}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MODERN C++ ILE D�LE GELEN �OK ONEMLI BAZI OZELLIKLER
	1)Bir fonksiyonun delete edilmesi(delete decleration)
		fonksiyonun oldu�unun ama ona yap�lan �a�r�da sentaks hatas� olmas� gerekti�inin bildirilmesi
		
		void foo(int) = delete; // foo int arg�man bir de�erle �a��r�ld��� zaman sentaks hatas� verecek
		
		Neden b�yle bir �ey kullanmak isteyelim?
			hi� b�yle bir bildirim yapmazd�k derleyicide bu durumda ismi arar bulamazd� ama delete bildirimi �yle de�il fonksiyonun var oldu�unu 
			ama bunun �a��r�lmas� durumunda sentaks hatas� olu�aca��n� s�yl�yor bu ikisi ayn� durum de�il fonksiyonun olmamas� durumunda olu�an sentaks hatas� ba�ka 
			fonksiyonun delete edilmesi y�z�nden olu�an sentaks hatas� ba�ka

		�RNEK:delete bildirimi ile bildirilen bir fonksiyonda bir overloadtur
			void foo(int) = delete;
			void foo(double);
			void foo(long);

			int main()
			{
				foo(2.3); // double parametreli se�ilir
				foo(34); // sentaks hatas�
			}

	SORU:
		1)global fonksiyonlar delete edilebilir mi? EVET
		2)s�n�flar�n t�m functionlar� delete edilebilir mi? EVET
		3)s�n�flar�n constructorlar� ve destructorlar� delete edilebilir mi? EVET
	
	2)default bildirimi
		bir fonksiyonu default bildirimi ile bildirirsek derleyiciye bunun kodunu sen yazacaks�n talimat� vermi� oluyoruz
			class Nec
			{
				public:
					Nec() = default; // programc� Nec s�n�f�n�n default constructor kodunun derleyici taraf�ndan yaz�lmas�n� talep ediyor
			};

		SORU:
			1)hangi fonksiyonlar default bildirimi ile bildirebilir?
				special member functionlar
				1)default ctor
				2)destructor
				3)copy ctor
				4)move ctor
				5)move assignment
				6)copy assignment
				yani default bildirimi sadece s�n�flar�n special member functionlar� i�in yap�labilir

			ve spaceship operat�r�(C++ 20)

	Modern C++ ile dile gelen �ok ilgin� kurallar var
		special member functionlar �u stat�lerden birinde olabilir
			not declared(bildirilmemi�)
			user declared(programc� traraf�ndan bildirilmi�)
			implicitly declared(dilin kurallar� gere�i derleyici bu bildirimi yap�yor)

			class Nec
			{
				public:
					Nec(); // user declared
					Nec() = default // user declared
					Nec() = delete // user declared

					Nec s�n�f�n�n default constructor�n�n bildirimi hi� olmasayd� implicitly declared
			
			};

			implictly declared'in 2 kategorisi var
				1)bildiriyor ve default ediyor(impclitly declared defaulted)
					class Nec
					{
						public:
							// implictly declared defaulted derleyici burda �rt�l� olarak constructor� bildirir
					};

				2)bildiriyor fakat delete ediyor(implictly delete)

					class Nec
					{
						public:
							const int mx; // const nesneler default initalize edilemeyece�i i�in nesne olu�turulmaya �al���ld��� zaman constructor��n delete edilmi� oldu�u hatas�n� verecek
					}

					int main()
					{
						Nec mx; // derleyici burda default constructor� delete ediyor

						�yle durum var ki derleyici bir special member functionu implictly delete edebilir
					}

			SORU: b�t�n s�n�flar�n default constructor� olmak zorunda m� ? tabi ki HAYIR
				standartta baz� s�n�flar�n default constructor'� yok
				ama hoca %90 olmas� gerekiyor diyor ��nk� baz� ara�larla birlilkte kullan�lacak s�n�flar�n default constructor�n�n �a��r�lmas� gerekiyor

				mesela bir s�n�f nesnesini bir containerda tutmak istiyoruz 

				std::vector<Nec> vec(10); // burda default constructor�n �a��r�lmas� gerekir
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MEMBER INITIALIZER LIST(MIL) yada daha �ok yayg�n terim CONSTRUCTOR INITIALIZER LIST
	bir constructor�n s�n�f�n non-static veri elemanlar�n� initalize etmesini sa�layan sentaks bi�imi 

	class Nec
	{
		public:
			Nec()
			{
				mx = 5; // program�n ak���� constructor�n ana blo�una girmi� ise s�n�f�n veri elemanlar� hayata gelmi� durumda mx ve my'yi hayata gelmi� olarak d���n�yoruz burda sadece atama yap�yoruz
				hayata gelmi� olan bir nesneye de�er atam�� oluyoruz
				my = 3.4;
			}
		private:
			int mx;
			double my;
	};

	MIL sentaks� ile s�n�f�n veri eleman�n� hayata getiren onu initialize eden bir sentaks peki bunun fark� ne?
	hoca baz� durumlarda bir fark� yok diyor ama �yle durumlar var ki
	a)s�n�f�n veri eleman� initalize edilmek zorundaysa default initalize edilemiyorsa MIL sentaks�n� kullanmam�z gerekir �stteki const �rne�inde kullanmam�z gerekti�i gibi
		��nk� zaten default initalize edilemiyorsa derleyicinin yazd��� constructor her zaman veri elemanlar�n� default initalize ediyor
		yada MIL sentaks�n� kullanmazsak s�n�f�n veri elemanlar�n� default initalize etmi� oluyoruz
			
	s�n�f�n non-static veri elemanlar� i�in birinci tercihimiz MIL sentaks�n� kullanmak olmal� 
	

	class Nec
	{
		public:
			Nec();
		private:
		iny mx,my;
	};

	cpp
	Nec::Nec() : mx(12),my(34) // member initalizer list sentaks
	{
		// nec s�n�f�n�n default constructor� �a��r�ld���nda s�n�f�n mx eleman� hayata 12 de�eri ile ba�layacak my de�eri 34 de�eri ile ba�layacak
		
	}
			
	SORU:constructor initalizer listte t�m non-static veri elemanlar�n� initialize etmek zorunda m�y�z? HAYIR 
		e�er initalize etmedi�imiz non-static veri elemanlar� varsa derleyici onlar� default initialize edecek e�er onlar�n default initalize edilmesi sentaks hatas� olu�turuyorsa sentaks hatas� olacak
		
		�RNEK
		1)const memberlar MIL sentaks� ile initialize edilmek zorundad�r default initalize edilemez
		class nec
		{	
			public:
				Nec();
				const int mx;
		};

		Nec::Nec() : mx(0) {}
		
		2)referanslar MIL sentaks� ile initialize edilmek zorunda default initialize edilemez
			class Nec
			{
				public:
				int& mr;
			};
		
		3)s�n�f�n ba�ka s�n�flardan veri elemanlar� oldu�u senaryolarda MIL sentaks� �ok �nemli
			
			class Erg 
			{
				public:
					Erg(int); // ba�ka constructor'�n bildirimi ile s�n�f�n default constructor� derleyici taraf�ndan implictly delete edilmi� 
			}

			class Nec
			{
				public:
					Nec();
				private:
					Erg e; // Nec s�n�f�n�n default constructor�n�n tan�m�n� yapt���m�z zaman sentaks hatas� verir ��nk� default initialize edilemez s�n�f nesnesinin default initialize edilmesi demek 
							o s�n�f�n default constructor�n�n �a��r�lmas� demek derleyici taraf�ndan delete edildi�i i�in b�yle bir bildirimi yapamay�z 
			}

			Nec::Nec()
			{
				// no default constructor exists for class "Erg"
			}
			
			
		�RNEK:
			class Nec
			{
				public:
					Nec();
					void print()const
					{
						std::cout << "mx = << mx << " my = " << my << '\n';
					}
				private:
				int mx,my;
			};

			Nec::Nec() {} // derleyici MIL sentaks� ile implict olarak mx ve my de�i�kenini garbage value olarak default initialize eder bu durum UNDEFINED BEHAVIOUR

			int main()
			{
				Nec mynec;
				mynec.print();
			}


		SORU:MIL sentaks�nda K�me parantezi kullanabilir miyiz?
			Nec() : mx{10} {} // Modern C++ ile kullanabiliyoruz NARROWING CONVERSION s�z konusu de�il sentaks hatas� unutmayal�m 
				
			normalde parantez yerine k�me parantez kullanmak anlamsal olarak bir farka yol a�m�yor ama �yle yerler var ki parantez yada k�me parantez kullan�lmas� kodun anlam�n� de�i�tiriyor
			hoca daha sonra bu konuya de�inecekmi�

		
		class Nec
		{
			public:
				Nec()
				{
					mstr = "necati ergin"; // e�er burada b�yle bir kod yazarsak bunun anlam� derleyici �nce MIL sentaks� ile mstr yi default initialize eder sonra program�n ak��� program�n ana blo�una girer
					ondan sonrada bu atama i�i yap�l�r asl�na iki ayr� i�lem yap�lma durumu var 
					1.string s�n�f�n�n default constructor� �al��acak
					2)atamay� yapmak i�inde ba�ka bir fonksiyon �al��acak
				}
				std::string mstr;

				Nec() : mstr("necati ergin") // MIL sentaks�n� kullansayd�k burda string s�n�f�n�n parametresi const char* olan constructor �al��acakt�
		};

				
		�RNEK:Nesneyi hayata getirdi�imiz s�ray� de�ilde ters s�ray� MIL sentaks�nda kullansayd�k ne olurdu
			class Nec
			{
				public:
					Nec() : my(10),mx(20) // burada bu de�i�kenlerin hayata gelmesi s�n�fta ki bildirimm s�ras�na g�re esas al�n�r burdaki tan�mlama �ok tehlikeli hatalara neden olabiliyor
					{
						// e�er my(10), mx(my / 3) �eklinde bir ifade olsayd� �nce mx hayata gelecekti my'nin i�inde garbage value olacakt� ve bu durum UNDEFINED BEHAVIOUR olacakt� 
					}

					int mx,my;
			};
				
		MIL sentaks�n�n en �nemli oldu�u yerlerden biride parametreli constructorlar�n oldu�u durum
			class Point
			{
				public:
					Point() : mx(0), my(0) {}
					Point(int x,int y) : mx(x), my(y) {}
				private:
				int mx,my;
			};

		Modern C++'da en �ok yanl�� anla��lan konulardan birine de�iniyor hoca
			class Point
			{
				public:

				private:
					int x = 0; 
					int y = 0;
					// bu sentaks modern C++ �ncesi yoktu bu sentaks ile s�n�fnn x ve y de�i�kenleri 0 de�eri yap�lm�yor bu sentaksa
					in-class initializer yada default member initializer deniliyor yani member�n default olarak initialize edilece�i de�eri g�steriyor
					e�er yazd���m�z constructorlardan birinde MIL sentaks� ile bu veri elemanlar�n� initalize etmezsek normalde derleyici bunlar� default edicekti 
					ama derleyici default member initializer ile bizim verdi�imiz initalizer de�erlerini kullan�yor

					e�er MIL sentaks�n� kullanmazsak asl�nda derleyici arka planda b�yle bir kod ekliyor
					Point() : mx(0), my(0)

					s�n�f i�inde parantez atamonu b�yle kullanam�yoruz
						int x(10)
			};

		e�er derleyici s�n�df�n default constructorunu implictly declared ediyorsa derleyicinin yazd��� default constructor veri elemanlar�n�n hepsini default initialize eder
			class Myclass
			{
				public:
					// bu s�n�f�n default constructor� var derleyici yazd� derleyicinin yazd��� bu default constructor ne yap�yor?
						dilin kuralalr� derleyicinin implictly declared etti�i bir special member functionun kodunun derleyici taraf�ndan nas�l yaz�laca��n� belirliyor
						
				private:
					int mx,my;
			}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	derleyici implictly declare etti�i bir special member functionu tan�mlama s�recinde bir sentaks hatas� olu�ursa yani dilin kurallar�n� �i�neyen bir durum olursa
	derleyici default etmesi gereken special member functionu delete eder
		Myclass
		{
			public:
			
			private:
				int& r; // sentaks hatas� de�il ama referanslar default initialize edilemez bu y�zden constructor delete edilecek 
				delete edilmi� constructora �a�r� yap�ld��� zaman sentaks hatas� verir ayn�s� const de�erler i�inde ge�erlidir 
		}

		int main()
		{
			Myclass m; // defaut olan constructora �a�r� yapamay�z sentaks hatas�
		}
		
		�RNEK
			class Nec
			{
				private:
					Nec(); // public olsayd� herhangi bir problem olmayacakt�
				
			};
			
			class Myclass
			{
				public:
				 // bu s�n�f�n default construct�r� delete edilmi�tir ��nk� Nec s�n�f�n�n constructor� private oldu�u i�in derleyici Myclass s�n�f� i�in default constructor yazarken 
				 s�n�f�n veri eleman�n� default initalize edicek default initalize edilmesi demek default constructor�n �a��r�lmas� demek ama privare construct�r�n �a��r�lmas� sentaks hatas�
				 yani derleyici implictly declared edilen bir special member fucntionu default etme giri�iminde buludu�u zaman dilin herhangi bi kural�n� �i�neyen bir yap� olu�ursa sentaks hatas� vermek
				 yerine default etmesi gerekn special member function� implictly declared delete ediyor
				private:
					Nec mynec;
			};

		 derleyici special member functionu dilin kurallar�na g�re implictly declare ediyorsa derleyicinin yazd��� function s�n�f�n non-static public inline member function�d�r
		 
		 class Nec
		 {
			public:
				Nec() = default // user declared defaulted oldu�u i�in bu kural ge�erli de�il 
		 }
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
constructor� ismiyle �a��rabilir miyiz? HAYIR
	constructor�n di�er special member functionlardan �nemli bir fark� nokta operat�r�yle yada ok operat�r�yle �a��r�lam�yor olmas�
	class Nec
	{
		public:
			Nec();
			Nec(int);
			void func()
	};
				
	int main()
	{
		Nec mynec;
		mynec.Nec(); // sentaks hatas�
	}
				
	ayn� durumu destructor i�in uygulasak kod legal olur ama legal olmas� kodun do�ru oldu�u anlam�na gelmiyor destructor� kendimiz �a��r�yoruz sonra ana blok sonuna geldi�inde
	derleyici taraf�ndan tekrar destructor �a��r�lm�� oluyor

	mynec.~Nec();

	destructor�n b�yle kullan�lmas� placement new ad�nda bir operat�r kullan�m�nda gerekiyor dinamik �m�rl� nesnelerle ilgili durumlara izin vermesi i�in
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
hoca complete type incomplete type konusunu tekrar ediyor
	bir veri t�r� ya complete typet�r yada incomplete typet�r
		
	derleyici bir s�n�f�n varl���ndan haberdar fakat o s�n�f�n tan�m�n� hen�z g�rmemi� durumda
		class Myclass; // incomplete type yada forward decleration

		derleyici s�n�f tan�m�n� g�rd��� zaman art�k complete type olmu� olur
		
		incomplete type olu�turman�n bir yolu daha var
			class Myclass* ptr;

		derleyici bir s�nf�n varl���ndan haberdarsa bir ismin bir s�n�fa ili�kin oldj�unu biliyorsa ama hen�z os�n�f�n definitionunu g�rmediyse derleyici i�in o s�n�f incomplete type
		ama derleyici class definitionu g�rd��� anda derleyici i�in o s�n�f t�r� bir complete type

	incomplete typelar ile neler yaparsak sentaks hatas� olmaz
		1)fonksiyon prototype'inde kullanmam�z sentaks hatas� olmaz
			class Myclass;

			Myclass foo(Myclass);

		2)T�r e� isim bildirimleri
			using Type = Myclass;

		3)incomplete type t�rlerden pointer de�i�kenler tan�mlanabilir
			class Nec

			Nec* mp; // (object pointer) derleyici Nec s�n�f�n�n ne oldu�unu bilmemesine ra�men mp'nin storage de�erinin ne kadar oldu�unu biliyor

			Nec* create_nec();
			void foo(Nec*);

			int main()
			{
				Nec* p = create_nec();
				foo(p);
			}

			derleyici bu kodda Nec s�n�f�n�n definitinunu g�rm�yor olmas�na ra�men hepsi legal 
		
		4)extern bildirimi yapabiliyoruz
			extern Nec mynec; // non defining decleration bu bildirim mynec nesnesinin ba�ka mod�ldeki global bir de�i�ken oldu�unu s�yl�yor
			derleyiciye nec s�n�f nesnesinin yerini ay�rmas�n� s�ylemiyor yani burda nesne olu�turmuyor

		5)static anahtar kelimesi ile bildirebiliriz
			static Myclass m; 

		incomplete typelar ile neler yapamay�z
			1)incomplete type t�r�nden nesne tan�mlayamay�z
				class Nec;

				Nec mynec;

			2)s�n�f�n kendi t�r�nden veri eleman� olamaz(ama D�KKAT kendi t�r�nden pointer yada referans eleman� olabilir)
				class Myclass
				{
					Myclass m; // ��nk� bu noktada bu incomplete typet�r
				};
			
			�RNEK:
				auto sz = sizeof(Myclass); // incomplete t�rler sizeof operat�r�n�n operand� olamazlar ��nk� derleyici myclass i�in ne kadar yer ay�rmas� gerekti�ini bilemez
				
				pointerlarda kullan�labilir ama pointer� de-reference edecek bir ifade kullanamay�z

					Myclass* foo();

					int main()
					{
						Myclass * p = foo();
						auto x = *p; // incomplete type pointer� de-reference etti�imiz i�in sentaks hatas� subscript[] operat�r� i�inde ayn�s� ge�erli ok operat�r� i�inde
						
					}

			hoca programc�lar�n incomplete typelar�n i�lerini g�rd��� halde onu complete type haline getirmeleri durumununa de�iniyor
				
				kaveh.h
				
				#include "nec.h" // programc� bu tan�m�n gerekli oldu�unu d���n�yor bunu include etmek yerine
				Nec s�n�f� t�r�nden bir incomplete type olu�turabiliriz

				class Nec;

				class Myclass
				{
					Nec* mp; // programc� madem nec s�n�f�n� kullan�yoruz hemen include edeyim bari diyor :D
				};

				SORU:include etmenin bir zarar� m� var?
					dependency olu�turacakt� hemde compile time uzayacakt� dolay�s�y�la incomplete type'�n yeterli oldu�u yerlerde gereksiz yere complete type'a d�n��t�rmememiz gerekiyor

				SORU:void bir t�r m�d�r? EVET 
					ama void do�u�tan bir incomplete bir type
						void x; // sentaks hatas� ��nk� incomplete type t�rden nesne tan�mlam�� oluyoruz

					bir nesnenini t�r� void olamaz ama bir ifadenini t�r� void olabilir peki bu durumlar nelerdir
						1)herhangi bir ifadeyi void t�r�ne d�n��t�rmek
						2)function call
							void func();

							int main()
							{
								func(); // ifadenin t�r� void t�r�
							}
				SORU:(void)func(); ifadesi ne anlama gelir?
					fonksiyonun geri d�n�� de�eri var ama biz bunu void t�r�ne cast ederek o fonksiyonun geri d�n�� de�erini discard etmi� oluyoruz ve geri d�n�� de�erini kullanm�yoruz 			
*/