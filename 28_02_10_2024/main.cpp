/*

exception handligten devam ediyoruz

	bir fonksiyonun içinde gönderilen exception fonksiyonunun içinde handle ediliyor yani fonksiyon onu yakalýyor ve fonksiyonun çalýþmasý devam ediyor
	ama bu expcetion fonksiyonun içinde yakalanmazsa fonksiyondan dýþarý çýkýyor bir exceptionun fonksiyon tarafýndan yakalnmadan call chaindeki yukarýdaki fonksiyonlar tarafýndan 
	yakalanabilecek þekilde fonksiyondan dýþarý çýkmasý için bu terime EMIT yada EXCEPTION PROPAGATE deniyor


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

	call chain içinde birden fazla try bloðunun olmasý her exceptionun yakalanacaðý anlamýna gelmiyor catch bloðuna uygun bir tür varsa expcetion yakalanýyor
	exception yakalanýrsa programýn akýþý catch bloðuna giriyor gönderilen hata nesnesi fonksiyonun parametresine kopyalanýyor ve catch bloðu içinde program sonlandýrýlmazsa
	re-throw etmezse yada baþka bir exception gönderilmezse programýn akýþý catch bloðunu izleyen kodun çalýþmasýyla devam edecek


	SORU:expceptionun türü ne olursa olsun yakalamak mümkün mü? EVET dilin CATCH ALL aracýyla mümkün
		
	void baz()
	{
		try {
			bar();
		}
		catch (const std::exception& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		} 
		catch(...) // gönderilen hata nesnesi hangi türden olursa olsun hatayý yakalayacak en sonda olmasý gerekiyor çünkü özelden genele bir yaklaþýmý benimsememiz gerek
		{		   // exception'nun türünün ne olduðunu öðrenme þansýmýz yok sadece expcetionu yakalar 
				
		}
	}

	ÖRNEK:
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

	SORU:bütün exceptionlarý yakalayabilir miyiz? HAYIR
		
		gönderilen bütün exceptionlarý yakalamak mümkün olmayabilir çünkü main fonksiyonunun bütün kodunu bir try bloðu içine alabiliriz
		bütün fonksiyonlar mainden çaðýrýldýðýna göre mainin çaðýrdýðý fonksiyonlar diðer fonksiyonlarý çaðýrdýðýna göre exceptinolarýn hepsini yakalamýþ
		olmaz mýyýz? HAYIR çünkü global sýnýf nesneleri ve statik ömürlü sýnýf nesnelerinin ctorlarý programýn akýþý main fonksiyonuna girmeden çalýþýyor onlarýn ctorlarýndan gönderilen exceptionlarý
		main fonksiyonun içinde yakalamak mümkün deðil

	SORU:exception'ý yakaladýðýmýzda ne yapýyoruz?
		
		eðer yakaldaðýmýzda ne yapacaðýmýz konusunda bir fikrimiz yoksa o hataya müdahele etemk için bir fikrimiz yok demektir o hatayý yakalamayacaðýz
		yani exception gönderme ihtimali olan her hangi bir fonksiyona çaðrý yaptýðýmzýda o fonksiyonun çaðýrýldýðý yerde o exceptionu yakalamamýz gerekiyormuþ algýsý çok sýk görülüyor diyor hoca
		yapacak bir þeyimiz yoksa en iyisi yakalamamak burada sorumluluðumuz olmasý gerekiyor

	SORU:exceptionu yakalarsak ne yapýyoruz?
		
		1)terminative bir yaklaþým olur
			exception yakalanýr gerekli önlemler alýnýp program sonlandýrýlýr
		
		2)exception yakalanýr ve handle edilir(resumptive yaklaþým)
			expcetion nerde yakalanýyorsa orda gerekli iþlemler yapýlýr o fonksiyonu çaðýran koda karþý sorumluluk yerine getirilmiþ olur program çalýþmaya devam eder
		
		3)re-throw
			exception yakalanýr exceptiona kýsmen müdahele edilir ve ayný nesne excpetion olarak tekrar gönderilir
			ayný nesneyi yolladýðýmýz zaman polimorfik türü kaybetmemiþte oluyoruz

			ÖRNEK:
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

				ÇIKTI:
				exception caught in function bar
				&r = 0000001B99EFFAE4
				exception caught in main
				&r = 0000001B99EFFAE4 // re-throw edildiði için gönderilen nesnelerin adresleri ayný 

			ÖRNEK:
				void foo(int x)
				{
					throw std::out_of_range("out of range error\n");
				}

				void bar()
				{
					try {
						foo(23);
					}
					catch (const st::exception& ex)
					{d
						std::cout << "exception caught in bar()\n";
						throw ex; // not re-throw // sadece throw ifadesi olsaydý re-throw etmiþ olacaktýk ve out_of_range olan catch bloðu çalýþacaktý

						// burda bu throw statement'i kullandýðýmýz zaman gönderilen hata nesnesinin hayatý bitiyor ve bu türden yeni bir hata nesnesi oluþturmuþ oluyoruz
						// artýk dinamik tür kaybolmuþ oluyor dinamik tür kaybolmasaydý main fonksiyonu içinde out_of_range catch bloðu daha yukarýda olduðuna göre exceptionu onun yakalamasý gerekirdi
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

				ÇIKTI:
				exception caught in bar()
				exception caught in main exception : out of range error

			ÖRNEK:catch bloðu içinde re-throw etmemek
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
						foo(); // SORU: bar fonksiyonu doðrudan çaðýrýlýrsa ne olur?
										// re-throw statement yürütüldüðünde ortada gönderilmiþ bir exception nesnesi yoksa doðrudan terminate fonksiyonu çaðýrýlýyor
					}
					catch (const std::exception& ex)
					{
						std::cout << "exception caught: " << ex.what() << '\n';
					}
				}

				ÇIKTI:
				exception caught in foo()
				bar called
				exception caught: out_of_range error

			DÝKKAT:exception'ý re-throw etmek baþka exception'ý translate etmek baþka
				
				translate
					exceptionu yakaladýk çaðýrdýðýmýz call chain içinde bir exception gönderildi biz kendi amacýmýza uygun kendi clienlterýmýza uygun baþka bir exception gönderiiyoruz
					yani yakalýyoruz kýsmi müdahale ediyoruz ama yakaldýðoýmýz nesnesinin kendisini deðil yüksek ihtimalle baþka bir exception sýnýfý türünden baþka bizim yapamadýðýmýz iþi daha iyi
					betimleyen baþka bir exception nesnesi yolluyoruz

	NO-FAIL GURANTEE(no-throw gurantee) noexcept anahtar kelimesi kullanýlýr
		fonksiyonun iþini yapma garantisi yani eðer bir fonksiyon no fail garanti veriyorsa onu çaðýran kod o fonksiyonun exception göndermeyeceðini güvenerek yazýlabilir
		derleyicide bir fonksiyonun exception throw etmediðini gördüðünde bazý yerlerde daha iyi optimizasyon yada kod seçme þansýna sahip
		
		STRONG GURANTEE(commit or rollback)
				fonksiyon diyor ki ya ben iþimi yapacaðým ya da benden bir exception gittiðinde ben iþimin yapýlmasýndan önceki state'ini koruyacaðým
				yani ya iþin tamamýný yapar yada iþi yapmadan önceki hale geri döner
			
			BASIC GURANTEE
				exception'ý yakaladaðýmýz zaman program valid state'te kalmalý yoksa program kaynak yada kaynaklarý sýzdýrýrýsa yada program geçerli state'ini kaybederse
				örneðin exceptionu yakaladýk expcetionu yakaladýktan sonra kullandýðýmýz nesneler artýk kullanýlabilir nesneler deðil invariantlarý tutmuyor
				mesela string nesnesini kullanýyoruz tutuuðu yazý oguzhan esin ama length fonksiyonunu çaðýrdýðýmýzda 0 çýktsýýný alýyoruz burda invalid state söz konusu
				yani exceptionu yakalayýp programýn çalýþmasýný devam ettireceksek bir kaynak sýzýntýsý olmadýðýnda ve programýn geçerli bir durumda olduðundan emin olmalýyýz

				 bir programda basic gurantee saðlanmazsa doðru kabul edilmiyor bütün fonksiyonlar basic gurantee'yi saðlamak zorunda
				
				NO GURANTEE
					exception fýrlarsa programýn durumu belirsizdir Hafýza sýzýntýsý veri bozulmasý tanýmsýz davranýþ olabilir

		
	STACK UNWINDING

		Stack Unwinding, bir exception (istisna) fýrlatýldýðýnda, stack’te (yýðýnda) yer alan otomatik ömürlü nesnelerin sýrasýyla ve tersine yok edilmesi sürecidir.
		Yani, bir fonksiyonda exception fýrlatýldýðýnda: O fonksiyondan çýkýlýr, Çaðýran fonksiyona geçilir, Bu geçiþ sýrasýnda otomatik ömürlü (stack-allocated) nesnelerin destructor’larý çaðrýlýr.

		Amaç
			1)Bellek sýzýntýsýný engellemek,

			2)Kaynaklarý düzgün þekilde serbest býrakmak.
		ÖRNEK:

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
			throw std::runtime_error("person error\n"); // DÝKKAT eðer exceptionu yakalamazsak nesnelerin dtorlarý çaðýrýlmaz
			
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
		
		ÇIKTI:
		oguzhan icin kaynak edinildi
		alihan icin kaynak edinildi
		necati icin kaynak edinildi
		necati icin kaynak geri verildi
		alihan icin kaynak geri verildi
		oguzhan icin kaynak geri verildi
		exception caught: person error

	SORU:STACK UNWINDING'in verdiði garanti neden önemli
			eðer exception gönderildiðinde call chaindeki stack frame'lerde otomatik ömürlü nesneler oluþturulmuþsa exception yakalandýðýnda programýn akýþý exceptionu handle eden koda girmeden
			stack frame'lerde oluþturulan nesneler son çaðýrlan fonksiyondan ilk çaðýrýlan fonksiyona doðru hepsi için dtor'un çaðýrýlma garantisi var ve kaynaklar geri verilmiþ olacak kaynak sýzýntýsý
			ihtimali kalmamýþ olacak

	CTORLARDA EXCEPTION
		ctor invariantlarý ilk baþta saðlamasý gereken fonksiyon ve invariantlarý saðlayamazsa geri dönüþ deðeri olmadýðý için iletme þansýmýz yok 
		ctor iþini yapamýyorsa sýnýf nesnesi için invariantlarý doðru hale getiremiyorsa buda sýnýf nesnesinin baþarýlý bir þekilde hayata gelmemesi demek bu zamanda exception throw edecek

			class Myclass{
				public:
				Myclass()
				{
					std::cout<<"Myclass ctor called\n";
				 	throw std::runtime_error{"error"};
				}
				~Myclass()
				{
					std::cout<<"Myclass dtor called\n";
				}
			};

			int main()
			{
				try{
					Myclass m; // burada m nesnesi için dtor çaðýrýlmayacak çünkü ortada aslýnda m nesnesi yok o yüzden dtor çaðýrýlmýyor
				}
				catch(std::exception& ex{
					std::cout<<"excetpion caught: " << ex.what()<<'\n';
				}	
			}

		dinamik ömürlü bir nesneyi new ifadesiyle oluþturduðumuz zaman bu nesneyi oluþturuacak ctor çaðýrýldýðýnda zaten operator new çaðýrýlmýþ durumda oprator new'in kendisi exception throw
		etseydi ctor çaðýrýlmazdý çaðýrýlan ctor'un içinde exception throw edilirse allocete edilen bellek bloðuda geri verilecek

		DÝKKAT:ctor'ýn ana bloðu içinde exception gönderildiðinde exception yakalansa bile dtor çaðýrýlmýyordu çünkü ortada constructor edilen bir nesne yok AMA ELEMAN OLAN NESNELER ÝÇÝN DURUM BÖYLE DEÐÝL
		eleman olan nesneler ctor'un ana bloðu içinde oluþturulmuyorlar programýn akþý ana bloða gelmeden ctor initializer list içinde initialize ediliyorlar 

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
						std::cout<<"Nec ctor\n"; // programýn akýþý bu noktaya geldiðinde zaten Nec'in Member türünden olan mx nesnesi hayata gelmiþ durumda
						throw 1;				 // Nec nesnesi için çaðýrýlan ctor exception throw edildiðinde ve exception yakalandýðýnda Member'ýn dtor'u çaðýrýlmasý garanti altýnda
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

			ÇIKTI:
			Member ctor
			Nec ctor
			Member dtor
			exception caught

		SORU:Member'ýn ctor'u exceptin throw etseydi ne olurdu? NEC'IN VE MEMBER'IN DTORLARI ÇAÐIRILMAZDI çünkü MEMBER'ýn ctoru exception throw ettiði için aslýnda ortada bir nesne olmayacak
			class Member {
			public:
				Member()
				{
					std::cout << "Member ctor\n";
					throw 1;
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

		SORU:elemanlar pointer ile tutulsaydý ne olurdu? 
			
			DÝKKAT:Nec'in ctoru exception throw ederse eleman olan pointer'ýn gösterdiði dinamik ömürlü member nesnesi hayata gelmiþ olacak ama dtor çaðýrýlmadýðý için delete edilmeyecek
			böyle bir senaryoda smart pointerlar kullanýlýyor çünkü dtor bu senaryoda çaðýrýlýyor

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
	
		ctor kendi kodu içinde gönderilen exceptionu handle edebilir önemli olan ctordan exceptionun sýzmamasý eðer kendisi handle ediyorsa
		nesnenin hayata gelmesinde bir sorun olmayacak ama bu durumla ilgili özel bir durum var bu özel durumla ilgili dilin bir aracý var FUNCTION TRY BLOCK

			SORU:Member class'ýn throw ettiði exceptionu Myclass'ýn ctor'unun içinde yakalayabilir miyiz? HAYIR eðer exception yakalansaydý program catch bloðuna girerdi ama
			abort fonksiyonu çaðýrýlýyor bu senaryonun geçerli olmasý için FUNCTION TRY BLOCK kullanýlmasý gerekiyor
			
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

			eðer CTOR INITIALIZER LIST kýsmýnda construct edilen memberlardan birinin gönderdiði exceptionu sýnýfýn ctor'u içinde yakalamak istiyorsak
			try block yerine FUNCTION TRY BLOCK oluþturmamýz gerekiyor CTOR'da FUNCTION TRY BLOCK kullanýrsak o zaman CTOR INITIALIZER LIST'de memberlarýn gönderdiði exceptionlarý yakalama þansýmýz var

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
					catch (const std::exception& ex) // programýn akýþý catch bloðuna girecek exception yakalanacak ama artýk Myclass nesnesini construct etme þansýmýz yok eðer ctor'un 
														function try bloðunu izleyen catch bloðunda her hangi bir kod eklemezsek derleyici buraya doðrudan re-throw statement koyuyor
					{									ctor'da exceptionu neden yakaladýk çünkü member'dan gönderilen exceptionu yakaladýk exception yakalandýðý için member hayata gelmedi
														memberýn hayata gelmemesi sýnýfýn invariantlarýný oluþturamamasý demek logic açýdan bu bir felaket olmuþ olur yani exceptionu yakalamamýz demek
														Myclass nesnesinin kullanýlabilir olduðu anlamýna gelmiyor

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
			try { // bu block hem fonksiyonun ana bloðu hemde ayný zamanda try block
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
		
		SORU:function try block içinde yerel bir deðiþken olsaydý catch bloklarýnda kullanabilir miydik? HAYIR
			
			void func(int x)
			try { 
				int ival = 5;
			}
			catch(int i)
			{
				auto value = ival; // sentaks hatasý
			}
			
		SORU:fonksiyonun parametre deðiþkenini kullanabilir miyiz? EVET
			
			void func(int x)
			try {
				int ival = 5;
			}
			catch(int i)
			{
				auto value = x; // geçerli
			}

		SORU:fonksiyonun geri dönüþ deðeri olsaydý catch bloklarýn içinde return statement'ý kullanabilir miydik? EVET
			int func(int x)
			try {
			}
			catch(int i)
			{
				return x + 5;
			}

		SORU:fonksiyonun parametresi bir sýnýfa iliþkin olsaydý ve function try block kullanýlsaydý o sýnýf türünden bir nesne oluþturup func fonksiyonuna nesneyi
		argüman olarak gönderseydik function try block içerisindeki expcetion yakalanýrdý ama parametre deðiþkenini hayata gelmesi sürecindeki exceptionlarýn function try block'da
		yakalanma þansý var mý? HAYIR

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
		
	NOEXCEPT ANAHTAR KELIMESÝ
		modern C++ ile dile eklendi bu anahtar sözcüðün iki ayrý kullanýmý var ve ikisinin birbiriyle karýþtýrýlmasý çok yaygýn
			1)noexcept specifier
				void func(int)noexcept; // böyle bir bildirim func fonksiyonunun exception yollamayacaðý anlamýna geliyor

				noexcept(constant exppression) // compile time'da logic yorumlamaya tabi tutulacak ve bu logic yorumlama sonucunda true deðer elde edilirse
				fonksiyon noexcept olarak bildirilmiþ olacak false olursa exception throw etmeme garantisi vermiyor olacak

				void bar(int)noexcept(true); yazmakla void bar(int)noexcept; yazmak arasýnda hiç bir fark yok

				void bar(int)noexcept(false); yazmakla void bar(int); yazmak arasýnda hiç bir fark yok

				generic programlama tarafýnda noexcept'i compile time'a yönelik constant expression yazmak ve noexcept olmasýný o koþula baðlamak son derece önemli
					void bar()noexcept(sizeof(int) > 2);

			2)noexcept operatörü
				týpký sizeof operatürü gibi compile time operatörü yani noexcept operatörüyle oluþturulan ifadeler contstant expression
				bu operatör ile oluþturulan ifade contant expression ve bool deðer üretiyor

				int x = 10;
				constexpr bool b = noexcept(x + 5); // b'nin true yada false olduðu compile time'da garanti altýnda

				SORU:noexcept operatörü neye göre true yada false deðeri üretiyor
					constexpr bool b = noexcept(x + 5); // bu ifadenin yürütülmesi sýrasýnda exception throw etmemesi garanti altýnda

				SORU:foo fonksiyonu exception throw etmeme garantisi taþýyor mu? HAYIR çünkü foo fonksiyonu noexcept deðil				
						
					int foo();

					int main()
					{
						int x = 10;
						constexpr bool b = noexcept(foo());
					}
						
				noexcept operatörü için iþlem kodu üretilmiyor uneveluated context(iþlem kodu üretilmeyen baðlam)	
					
					int main()
					{
						int x = 10;
						constexpr bool b = noexcept(x++); // x'in deðeri burda artmýyor
					}
						
				ÖRNEK:TRUE çünkü bir pointerý de-reference etme ifadesinin exception throw etme ihtimali yok

					int main()
					{
						int* ptr{nullptr};
						constexpr bool b = noexcept(*ptr); // TRUE
					}
				
				ÖRNEK:
					
					class Myclass{};

					int main()
					{
						Myclass* ptr{nullptr};
						constexpr bool b = noexcept(*ptr); // TRUE
					}

				SORU:sýnýfýn operator* fonksiyonu olsaydý?

					class Myclass{
						public:
							Myclass& operator*();
					};

					int main()
					{
						Myclass m;
						constexpr bool b = noexcept(*m); // FALSE deðeri üretir çünkü operator*() fonksiyonu noexcept olmadýðý için exception throw edebilir
					}
					
				ÖRNEK:
						
					class Myclass{
					};

					int main()
					{
						constexpr bool b = noexcept(Myclass{}); // TRUE çünkü sýnýfýn default ctorunu derleyici yazýyor derleyici yazdýðý için kendi yazdýðý default ctoru noexcept olarak bildiriyor
																   kendimiz bildirseydik noexcept olarak bildirmemiz gerekirdi
						sýnýfýn special member functionlarý implictly declared ise yani derleyici tarafýndan yazýlýyorsa noexcept olarak bildiriliyor
					}
						
				bir fonksiyon noexcept olarak nitelenmesine raðmen expcetion throw ediyorsa terminate fonksiyonu  çaðýrýlýr								
*/