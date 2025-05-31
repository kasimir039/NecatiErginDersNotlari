/*

exception handligten devam ediyoruz

	bir fonksiyonun i�inde g�nderilen exception fonksiyonunun i�inde handle ediliyor yani fonksiyon onu yakal�yor ve fonksiyonun �al��mas� devam ediyor
	ama bu expcetion fonksiyonun i�inde yakalanmazsa fonksiyondan d��ar� ��k�yor bir exceptionun fonksiyon taraf�ndan yakalnmadan call chaindeki yukar�daki fonksiyonlar taraf�ndan 
	yakalanabilecek �ekilde fonksiyondan d��ar� ��kmas� i�in bu terime EMIT yada EXCEPTION PROPAGATE deniyor


	void foo()
	{
		throw std::runtime_error{ "run time error" };
	}

	void bar()
	{
		try {
			foo();
		}
		catch (const std::bad_alloc& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	}

	void baz()
	{
		try {
			bar();
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		} // 
	}

	int main()
	{
		baz();
	}

	call chain i�inde birden fazla try blo�unun olmas� her exceptionun yakalanaca�� anlam�na gelmiyor catch blo�una uygun bir t�r varsa expcetion yakalan�yor
	exception yakalan�rsa program�n ak��� catch blo�una giriyor g�nderilen hata nesnesi fonksiyonun parametresine kopyalan�yor ve catch blo�u i�inde program sonland�r�lmazsa
	re-throw etmezse yada ba�ka bir exception g�nderilmezse program�n ak��� catch blo�unu izleyen kodun �al��mas�yla devam edecek


	SORU:expceptionun t�r� ne olursa olsun yakalamak m�mk�n m�? EVET dilin CATCH ALL arac�yla m�mk�n
		
	void baz()
	{
		try {
			bar();
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		} 
		catch(...) // g�nderilen hata nesnesi hangi t�rden olursa olsun hatay� yakalayacak en sonda olmas� gerekiyor ��nk� �zelden genele bir yakla��m� benimsememiz gerek
		{		   // exceptio'nun t�r�n�n ne oldu�unu ��renme �ans�m�z yok sadece expcetionu yakalar 
				
		}
	}

	�RNEK:
		void foo(int x)
		{
			if (x % 2 == 0)
			{
				throw 4;
			}
		}

		int main()
		{
			try
			{
				foo(4);
			}
			catch (...)
			{
				std::cout << "exception caught\n";
			}
		}

	SORU:b�t�n exceptionlar� yakalayabilir miyiz? HAYIR
		
		g�nderilen b�t�n exceptionlar� yakalamak m�mk�n olmayabilir ��nk� main fonksiyonunun b�t�n kodunu bir tyr blo�u i�ine alabiliriz
		b�t�n fonksiyonlar mainden �a��r�ld���na g�re mainin �a��rd��� fonksiyonlar di�er fonksiyonlar� �a��rd���na g�re exceptinolar�n hepsini yakalam��
		olmaz m�y�z? HAYIR ��nk� global s�n�f nesneleri ve statik �m�rl� s�n�f nesnelerinin ctorlar� program�n ak��� main fonksiyonuna girmeden �al���yor onlar�n ctorlar�ndan g�nderilen exceptionlar�
		main fonksiyonun i�inde yakalamak m�mk�n de�il

	SORU:exception'� yakalad���m�zda ne yap�yoruz?
		
		e�er yakalda��m�zda ne yapaca��m�z konusunda bir fikrimiz yoksa o hataya m�dahele etemk i�in bir fikrimiz yok demektir o hatay� yakalamayaca��z
		yani excetion g�nderme ihtimali olan her hangi bir fpnksiyona �a�r� yapt��mz�da o fonksiyonun �a��r�ld��� yerde o exceptionu yakalamam�z gerekiyormu� alg�s� �ok s�k g�r�l�yor diyor hoca
		yapacak bir �eyimiz yoksa en iyisi yakalamamak burada sorumlulu�umuz olmas� gerekiyor

	SORU:exceptionu yakalarsak ne yap�yoruz?
		
		1)terminative bir yakla��m olur
			exception yakalan�r gerekli �nlemler al�n�p program sonland�r�l�r
		
		2)exception yakalan�r ve handle edilir(resumptive yakla��m)
			expcetion nerde yakalan�yorsa orda gerekli i�lemler yap�l�r o fonksiyonu �a��ran koda kar�� sorumluluk yerine getirilmi� olur program �al��maya devam eder
		
		3)re-throw
			exception yakalan�r exceptiona k�smen m�dahele edilir ve ayn� nesne excpetion olarak tekrar g�nderilir
			ayn� nesneyi yollad���m�z zaman polimorfik t�r� kaybetmemi�te oluyoruz

			�RNEK:
				void foo(int x)
				{
					throw 12;
				}

				void bar()
				{
					try{
						foo(23);
					}
					catch(int &r)
					{
						std::cout<<"exception caught in function bar\n";
						std::cout<<"&r = "<<&r<<'\n';
						throw;
					}
				}

				int main()
				{
					try{
						bar();
					}
					catch(int& r)
					{
						std::cout<<"exception caught in function bar\n";
						std::cout<<"&r = "<<&r<<'\n';
					}
				}

				�IKTI:
				exception caught in function bar
				&r = 0000001B99EFFAE4
				exception caught in main
				&r = 0000001B99EFFAE4 // re-throw edildi�i i�in g�nderilen nesnelerin adresleri ayn� 

			�RNEK:
				void foo(int x)
				{
					throw std::out_of_range("out of range error\n");
				}

				void bar()
				{
					try {
						foo(23);
					}
					catch (const std::exception& ex)
					{
						std::cout << "exception caught in bar()\n";
						throw ex; // not re-throw // sadece throw ifadesi olsayd� re-throw etmi� olacakt�k ve out_of_range olan catch blo�u �al��acakt�

						// burda bu throw statement'i kulland���m�z zaman g�nderilen hata nesnesinin hayat� bitiyor ve bu t�rden yeni bir hata nesnesi olu�turmu� oluyoruz
						// art�k dinamik t�r kaybolmu� oluyor dinamik t�r kaybolmasayd� main fonksiyonu i�inde out_of_range catch blo�u daha yukar�da oldu�una g�re exceptionu onun yakalamas� gerekirdi
					}
				}

				int main()
				{
					try {
						bar();
					}
					catch (const std::out_of_range& ex)
					{
						std::cout << "exception caught in main out_of_range : " << ex.what() << '\n';

					}
					catch (const std::exception& ex)
					{
						std::cout << "exception caught in main exception : " << ex.what() << '\n';

					}
				}

				�IKTI:
				exception caught in bar()
				exception caught in main exception : out of range error

			�RNEK:catch blo�u i�inde re-throw etmemek
				void bar()
				{
					std::cout << "bar called\n";
					throw; // re-throw
				}

				void func()
				{
					throw std::out_of_range("out_of_range error");
				}

				void foo()
				{
					try {
						func();
					}
					catch (const std::exception)
					{
						std::cout << "exception caught in foo()\n";
						bar();
					}
				}

				int main()
				{
					try {
						foo(); // SORU: bar fonksiyonu do�rudan �a��r�l�rsa ne olur?
										// re-throw statement y�r�t�ld���nde ortada g�nderilmi� bir exception nesnesi yoksa do�rudan terminate fonksiyonu �a��r�l�yor
					}
					catch (const std::exception& ex)
					{
						std::cout << "exception caught: " << ex.what() << '\n';
					}
				}

				�IKTI:
				exception caught in foo()
				bar called
				exception caught: out_of_range error

			D�KKAT:exception'� re-throw etmek ba�ka exception'� translate etmek ba�ka
				
				translate
					exceptionu yakalad�k �a��rd���m�z call chain i�inde bir exception g�nderildi biz kendi amac�m�za uygun kendi clienlter�m�za uygun ba�ka bir exception g�nderiiyoruz
					yani yakal�yoruz k�smi m�dahale ediyoruz ama yakald��o�m�z nesnesinin kendisini de�il y�ksek ihtimalle ba�ka bir exception s�n�f� t�r�nden ba�ka bizim yapamad���m�z i�i daha iyi
					betimleyen ba�ka bir exception nesnesi yolluyoruz

	NO-FAIL GURANTEE(no-throw gurantee) noexcept anahtar kelimesi kullan�l�r
		fonksiyonun i�ini yapma garantisi yani e�er bir fonksiyon no fail garanti veriyorsa onu �a��ran kod o fonksiyonun exception g�ndermeyece�ini g�venerek yaz�labilir
		derleyicide bir fonksiyonun exception throw etmedi�ini g�rd���nde baz� yerlerde daha iyi optimizasyon yada kod se�me �ans�na sahip
		
		STRONG GURANTEE(commit or rollback)
				fonksiyon diyor ki ya ben i�imi yapaca��m�z yada benden bir exception gitti�inde ben i�imin yap�lmas�ndan �nceki state'ini koruyaca��m
				yani ya i�in tamam�n� yapar yada i�i yapmadan �nceki hale geri d�ner
			
			BASIC GURANTEE
				exception'� yakalada��m�z zaman program valid state'te kalmal� yoksa program kaynak yada kaynaklar� s�zd�r�r�sa yada program ge�erli state'ini kaybederse
				�rne�in exxceptionu yakalad�k expcetionu yakalda�ktan sonra kulland���m�z nesneler art�k kullan�labilir nesneler de�il invariantlar� tutmuyor
				mesela string nesnesini kullan�yoruz tutuu�u yaz� oguzhan esin ama length fonksiyonunu �a��rd���m�zda 0 ��kts��n� al�yoruz burda invalid state s�z konusu
				yani exceptionu yakalay�p program�n �al��mas�n� devam etitreceksek bir kaynak s�z�nt�s� olmad���nda ve program�n ge�erli bir durumda oldu�undan emin olmayl�y�z

				 bir programda basic gurantee sa�lanmazsa do�ru kabul edilmiyor b�t�n fonksiyonlar basic gurantee'yi sa�lamak zorunda
				
				NO GURANTEE
					exception f�rlarsa program�n durumu belirsizdir Haf�za s�z�nt�s� veri bozulmas� tan�ms�z davran�� olabilir

		
	STACK UNWINDING

		Stack Unwinding, bir exception (istisna) f�rlat�ld���nda, stack�te (y���nda) yer alan otomatik �m�rl� nesnelerin s�ras�yla ve tersine yok edilmesi s�recidir.
		Yani, bir fonksiyonda exception f�rlat�ld���nda: O fonksiyondan ��k�l�r, �a��ran fonksiyona ge�ilir, Bu ge�i� s�ras�nda otomatik �m�rl� (stack-allocated) nesnelerin destructor�lar� �a�r�l�r.

		Ama�
			1)Bellek s�z�nt�s�n� engellemek,

			2)Kaynaklar� d�zg�n �ekilde serbest b�rakmak.
		�RNEK:

		class Person{
			public:
				Person(const char* pname) : m_name(pname)
				{
					std::cout<<m_name << " icin kaynak edinildi\n";
				}
				~Person()
				{
					std::cout<<m_name << " icin kaynak geri verildi\n";
				}
			private:
				std::string m_name;
		};
		void baz()
		{
			Person p3{"necati"};
			throw std::runtime_error("person error\n"); // D�KKAT e�er exceptionu yakalamazsak nesnelerin dtorlar� �a��r�lmaz
			
		}
		void bar()
		{
			Person p2{"alihan"};
			baz();
		}

		void foo()
		{
			Person p1{"oguzhan"};
			bar();
		}

		int main()
		{
			try
			{
				foo();
			}
			catch (const std::exception&)
			{
				std::cout << "exception caught: \n";
			}
		}
		
		�IKTI:
		oguzhan icin kaynak edinildi
		alihan icin kaynak edinildi
		necati icin kaynak edinildi
		necati icin kaynak geri verildi
		alihan icin kaynak geri verildi
		oguzhan icin kaynak geri verildi
		exception caught: person error

	SORU:STACK UNWINDING'in verdi�i garanti neden �nemli
			e�er exception g�nderildi�inde call chaindeki stack frame'lerde otomatik �m�rl� nesneler olu�turulmu�sa exception yakaland���nda program�n ak��� exceptionu handle eden koda girmeden
			stack frame'lerde olu�turulan nesneler son �a��rlan fonksiyondan ilk �a��r�lan fonksiyona do�ru hepsi i�in dtor'un �a��r�lma garantisi var ve kaynaklar geri verilmi� olacak kaynak s�z�nt�s�
			ihtimali kalmam�� olacak

	CTORLARDA EXCEPTION
		ctor invariantlar� ilk ba�ta sa�lamas� gerekn fonksiyon ve invariantlar� sa�layamazsa geri d�n�� de�eri olmad��� i�in iletme �ans�m�z yok 
		ctor i�ini yapam�yorsa s�n�f nesnesi i�in invariantlar� do�ru hale getiremiyorsa buda s�n�f nesnesinin ba�ar�l� bir �ekilde hayata gelmemesi demek bu zamanda exception throw edecek

			class Myclass{
				public:
				Myclass()
				{
					std::cout<<"Myclass ctor called\n";
				 	throw std::runtime_erro{"error"};
				}
				~Myclass()
				{
					std::cout<<"Myclass dtor called\n";
				}
			};

			int main()
			{
				try{
					Myclass m; // burada m nesnesi i�in dtor �a��r�lmayacak ��nk� ortada asl�nda m nesnesi yok o y�zden dtor �a��r�lm�yor
				}
				catch(std::exception& ex{
					std::cout<<"excetpion caught: " << ex.what()<<'\n';
				}	
			}

		dinamik �m�rl� bir nesneyi new ifadesiyle olu�turdu�umuz zaman bu nesneyi olu�turuacak ctor �a��r�ld���nda zaten operator new �a��r�lm�� durumda oprator new'in kendisi exception throw
		etseydi ctor �a��r�lmazd� �a��r�lan ctor'un i�inde exception throw edilirse allocete edilen bellek blo�uda geri verilecek

		D�KKAT:ctor'�n ana blo�u i�inde excption g�nderildi�inde exception yakalnsa bile dtor �a��r�lm�yordu ��nk� ortada constructor edilen bir nesne yok AMA ELEMAN OLAN NESNELER ���N DURUM B�YLE DE��L
		eleman olan nesneler ctor'un ana blo�u i�inde olu�turulmuyoarlar program�n ak��� ana blo�a gelmeden ctor initializer list i�inde initialize ediliyorlar 

			class Member{
				public:
					Member()
					{
						std::cout<<"Member ctor\n";
					}
					~Member()
					{
						std::cout<<"Member dtor\n";
					}
			};

			class Nec{
				public:
					Nec()
					{
						std::cout<<"Nec ctor\n"; // program�n ak��� bu noktaya geldi�inde zaten Nec'in Member t�r�nden olan mx nesnesi hayata gelmi� durumda
						throw 1;				 // Nec nesnesi i�in �a��r�lan ctor exception throw edildi�inde ve exception yakaland���nda Member'�n dtor'u �a��r�lmas� garanti alt�nda
					}
					~Nec()
					{
						std::cout<<"Nec dtor\n";
					}
				private:
					Member mx;
			};

			int main()
			{

				try
				{
					Nec n;
				}
				catch (int)
				{
					std::cout << "exception caught\n";
				}
			}

			�IKTI:
			Member ctor
			Nec ctor
			Member dtor
			exception caught

		SORU:Member'�n ctor'u exceptin throw etseydi ne olurdu? NEC'IN VE MEMBER'IN DTORLARI �A�IRILMAZDI ��nk� MEMBER'�n ctoru exception throw etti�i i�in asl�nda ortada bir nesne olmayacak
			class Member {
			public:
				{
					std::cout << "Member ctor\n";
					throw 1;
				Member()
				}
				~Member()
				{
					std::cout << "Member dtor\n";
				}
			};

			class Nec {
			public:
				Nec()
				{
					std::cout << "Nec ctor\n"; 
					throw 1;				 
				}
				~Nec()
				{
					std::cout << "Nec dtor\n";
				}
			private:
				Member mx;
			};

			int main()
			{

				try
				{
					Nec n;
				}
				catch (int ex)
				{
					std::cout << "exception caught\n";
				}
			}

		SORU:elemanlar pointer ile tutulsayd� ne olurdu? 
			
			D�KKAT:Nec'in ctoru exception throw ederse elemaan olan pointer'�n g�sterdi�i dinamik �m�rl� member nesnesi hayata gelmi� olacak ama dtor �a��r�lmad��� i�in delete edilmeyecek
			b�yle bir senaryoda smart pointerlar kullan�l�yor ��nk� dtor bu senaryoda �a��r�l�yor

			class Member {
			public:
				Member()
				{
					std::cout << "Member ctor\n";
				}
				~Member()
				{
					std::cout << "Member dtor\n";
				}
			};

			class Nec {
			public:
				Nec() : mp(new Member)
				{
					std::cout << "Nec ctor\n";
					throw 1;
				}
				~Nec()
				{
					std::cout << "Nec dtor\n";

					delete mp;
				}
			private:
				Member *mp;
			};

			int main()
			{

				try
				{
					Nec n;
				}
				catch (int ex)
				{
					std::cout << "exception caught\n";
				}
			}
	
		ctor kendi kodu i�inde g�nderilen exceptionu handle edebilir �nemli olan ctordan exceptionun s�zmamas� e�er kendisi handle ediyorsa
		nesnenin hayata gelmesinde bir sorun olmayacak ama bu durumla ilgili �zel bir durum var bu �zel durumla ilgili dilin bir arac� var FUNCTION TRY BLOCK

			SORU:Member class'�n throw etti�i exceptionu Myclass'�n ctor'unun i�inde yakalayabilir miyiz? HAYIR e�er exception yakalansayd� program catch blo�una girerdi ama
			abort fonksiyonu �a��r�l�yor bu senaryonun ge�erli olmas� i�in FUNCTION TRY BLOCK kullan�lmas� gerekiyor
			
				class Member
				{
				public:
					Member()
					{
						std::cout << "Member ctor\n";
						if (1)
						{
							throw std::runtime_error("error in Member ctor\n");
						}
					}
					~Member()
					{
						std::cout << "Member dtor\n";

					}
				};

				class Myclass {
				public:
					Myclass()
					{
						std::cout << "Member ctor\n";

						try
						{
							Member mx;
						}
						catch (const std::exception&)
						{
							std::cout << "exception caught\n";
						}
					}

					~Myclass()
					{
						std::cout << "Member dtor\n";

					}
				private:
					Member mx;
				};

				int main()
				{
					Myclass m;

				}

			e�er CTOR INITIALIZER LIST k�sm�nda construct edilen memberlardan birinin g�nderdi�i exceptionu s�n�f�n ctor'u i�inde yakalamak istiyorsak
			try block yerine FUNCTION TRY BLOCK olu�turmam�z gerekiyor CTOR'da FUNCTION TRY BLOCK kullan�rsak o zaman CTOR INITIALIZER LIST'de memberlar�n g�nderdi�i exceptionlar� yakalama �ans�m�z var

				class Member
				{
				public:
					Member(int x)
					{
						std::cout << "Member ctor\n";
						if (x % 2 == 0)
						{
							throw std::runtime_error("error in Member ctor\n");
						}
					}
					~Member()
					{
						std::cout << "Member dtor\n";

					}
				};

				class Myclass {
				public:
					Myclass() try : mx(4)
					{
						std::cout << "Member ctor\n";

					}
					catch (const std::exception& ex) // program�n ak��� catch blo�una girecek exception yakalanacak ama art�k Myclass nesnesini construct etme �ans�m�z yok e�er ctor'un 
														function try blo�unu izleyen catch blo�unda her hangi bir kod eklemezsek derleyici buraya do�rudan re-throw statement koyuyor
					{									ctor'da exceptionu neden yakalad�k ��nk� member'dan g�nderilen excetpionu yakalad�k exception yakalnd���� i�in member hayata gelmedi
														member�n hayata gelmemesi s�n�f�n invariantlar�n� olu�turamamas� demek logic a��dan bu bir felakt olmu� olur yani exceptionu yakalamam�z demek
														Myclass nesnesinin kullan�labilir oldu�u anlam�na gelmiyor

						std::cout << "exception caught: " << ex.what()  <<'\n';
					}

					~Myclass()
					{
						std::cout << "Member dtor\n";

					}
				private:
					Member mx;
				};

				int main()
				{
					Myclass m; 
				}

		FUNCTION TRY BLOCK
			
			void func(int x)
			try { // bu block hem fonksiyonun ana blo�u hemde ayn� zamanda try block
				if (x % 2 == 0)
					throw 4;
			}
			catch (int i)
			{ 
				std::cout << "exception caught int: " << i << '\n';

			}

			catch (double)
			{
				std::cout << "exception caught double\n";
			}

			int main()
			{
				func(24);
			}
		
		SORU:function try block i�inde yerel bir de�i�ken olsayd� cathc bloklar�nda kullanabilir miydik? HAYIR
			
			void func(int x)
			try { 
				int ival = 5;
			}
			catch(int i)
			{
				auto value = ival; // sentaks hatas�
			}
			
		SORU:fonksiyonun parametre de�i�kenini kullanabilir miyiz? EVET
			
			void func(int x)
			try {
				int ival = 5;
			}
			catch(int i)
			{
				auto value = x; // ge�erli
			}

		SORU:fonksiyonun geri d�n�� de�eri olsayd� catch bloklar�n i�inde return statement'� kullanabilir miydik? EVET
			int func(int x)
			try {
			}
			catch(int i)
			{
				return x + 5;
			}

		SORU:fonksiyonun parametresi bir s�n�fa ili�kin olsayd� ve function try block kullan�lsayd� o s�n�f t�r�nden bir nesne olu�turup func fonksiyonuna nesneyi
		arg�man olarak g�nderseydik function try block i�erisindeki expcetion yakalan�rd� ama parametre de�i�kenini hayata gelmesi s�recindeki exceptionlar�n function try block'da
		yakalanma �ans� var m�? HAYIR

			class Myclass{};
			
			int func(Myclass m)
			try {
			}
			catch(int i)
			{
			}
			
			int main()
			{
				Myclass mx;

				func(mx);
			}
		
	NOEXCEPT ANAHTAR KELIMES�
		modern C++ ile dile eklendi bu anahtar s�zc���n iki ayr� kullan�m� var ve ikisinin biribiriye kar��t�r�lmas� �ok yayg�n
			1)noexcept specifier
				void func(int)noexcept; // b�yle bir bildirim func fonksiyonunun exception yollamayaca�� anlam�na geliyor

				noexcept(constant exppression) // compile time'da logic yorumlamaya tabi tutulacak ve bu logic yorumlama sonucunda true de�er elde edilirse
				fonksiyon noexcept olarak bildirilmi� olacak false olursa exception throw etmeme garantisi vermiyor olacak

				void bar(int)noexcept(true); yazmakla void bar(int)noexcept; yazmak aras�nda hi� bir fark yok

				void bar(int)noexcept(false); yazmakla void bar(int); yazmak aras�nda hi� bir fark yok

				generic programlama taraf�nda noexcept'i compile time'a y�nelik constant expression yazmak ve noexcept olmas�n� o ko�ula ba�lamak son derece �nemli
					void bar()noexcept(sizeof(int) > 2);

			2)noexcept operat�r�
				t�pk� sizeof operat�r� gibi compile time operat�r� yani noexcept operat�r�yle olu�turulan ifadeler contstant expression
				bu operat�r ile olu�turulan ifade contant expression ve bool de�er �retiyor

				int x = 10;
				constexpr bool b = noexcept(x + 5); // b'nin true yada false oldu�u compile time'da garanti alt�nda

				SORU:noexcept operat�r� neye g�re true yada false de�eri �retiyor
					constexpr bool b = noexcept(x + 5); // bu ifadenin y�r�t�lmesi s�ras�nda exception throw etmemesi garanti alt�nda

				SORU:foo fonksiyonu excetpion throw etmeme garantisi ta��yor mu? HAYIR ��nk� foo fonksiyonu noexcept de�il				
						
					int foo();

					int main()
					{
						int x = 10;
						constexpr bool b = noexcept(foo());
					}
						
				noexcept operat�r� i�in i�lem kodu �retilmiyor uneveluated context(i�lem kodu �retilmeyen ba�lam)	
					
					int main()
					{
						int x = 10;
						constexpr bool b = noexcept(x++); // x'in de�eri burda artm�yor
					}
						
				�RNEK:TRUE ��nk� bir pointer� de-reference etme ifadesinin exception throw etme ihtimali yok

					int main()
					{
						int* ptr{nullptr};
						constexpr bool b = noexcept(*ptr); // TRUE
					}
				
				�RNEK:
					
					class Myclass{};

					int main()
					{
						Myclass* ptr{nullptr};
						constexpr bool b = noexcept(*ptr); // TRUE
					}

				SORU:s�n�f�n operator* fonksiyonu olsayd�?

					class Myclass{
						public:
							Myclass& operator*();
					};

					int main()
					{
						Myclass m;
						constexpr bool b = noexcept(*m); // FALSE de�eri �retir ��nk� operator*() fonksiyonu noexcept olmad��� i�in exception throw edebilir
					}
					
				�RNEK:
						
					class Myclass{
					};

					int main()
					{
						constexpr bool b = noexcept(Myclass{}); // TRUE ��nk� s�n�f�n default ctorunu derleyici yaz�yor derleyici yazd��� i�in kendi yazd��� default ctoru noexcept olarak bildiriyor
																   kendimiz bildirseydik noexcept olarak bildirmemiz gerekirdi
						s�n�f�n special member functionlar� imlictly declared ise yani derleyici taraf�ndan yaz�l�yorsa noexcept olarak bildiriliyor
					}
						
				bir fonksiyon noexcept olarak nitelenmesine ra�men expcetion throw ediyorsa terminate fonksiyonu �a��r�l�r								
*/