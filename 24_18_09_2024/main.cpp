/*

inheritance konusundan devam

	SORU:ayn� parametreye sahip fonksiyonlar farkl� classlarda olsa using bildirimi yapt���m�zda sentaks hatas� olur muydu? HAYIR
		
		class Base{
			public:
				void foo(int);
				void foo(double);
		};

		class Der : public Base{
			public:
				using Base::foo; // ge�erli
				void foo(int);
		};

	INHERITED CONSTRUCTOR
		
		using bildirimi ile Base class'�n ctorlar�n� Der class'a enjekte ediyoruz

		class Base{
			public:
				Base(int,int);
				Base(int);
				Base(double);
		};

		class Der : public Base{
			public:
				using Base::Base; // Base class'�n ctorlar�n� enjekte etti�imiz i�in derleyici burda base class'�n ctorlar�na �a�r� yapacak

		};

		int main()
		{
			Der d1(23); // Base(int)
			Der d2(2.3); // Base(double)
			Der d3(10,20); // Base(int,int)
		}

	RUN TIME POLYMORPHISM

		bir taban s�n�f�n member functionlar�n� 3 kategoriye ay�r�yoruz
			1)t�remi� s�n�flara hem bir interface veren hemde implementasyon veren fonksiyonlar
				
				class Airplane{
					public:
						void fly(); // t�remi� s�n�flar Airplane s�n�f�n� kal�t�m yoluyla elde ederse onlardada fly fonksiyonu olacak ve t�m miras alan s�n�flar taban s�n�f�n fly fonksiyonunu kullanacak
				}

			2)t�remi� s�n�flara hem bir interface veren hemde bir default implementasyon veren fonksiyonlar
				ister base class'�n implementasyonunu kullan�rlar isterse kendi implementasyonunu kullan�rlar(POLYMORPHIC CLASS)

					class Airplane{
						public:
							virtual void fly(); // virtual function(t�remi� s�n�f bu fonksiyonu override edebilir)
							
							bir s�n�f�n en az bir tane bile virtual fonksiyonu varsa POLYMORPHIC CLASS olmu� olur
							
							e�er t�remi� s�n�f taban s�n�f�n fonksiyonunu override ederse t�remi� s�n�f�n kendisine ait fly fonksiyonu olmu� olur
							e�er override edilmezse taban s�n�f�n fonksiyonu kullan�lm�� olur
					};

			3)taban s�n�f�n �yle bir �ye fonksiyonu ki t�remi� s�n�flara sadece bir interface veren implementasyon vermeyen fonksiyonlar(ABSTRACT CLASS)
				
				class Airplane{
				public:
					virtual void fly(int) = 0; // pure virtual function-saf sanal fonksiyon(t�remi� s�n�flar bu fonksiyonu implemente etmek zorunda)
			
					ABSTRACT CLASS'lardan nesne olu�turulmaz 
				};
					
				class Boeing : public Airplane{ 
					void fly(int) override; // boeing s�n�f�n�n concrete olmas� i�in fly foknsiyonunu ayn� �ekilde override etmek zorunda
					override contextual keyword�n� yazmasak bile sentaks hatas� olmazd� ama mutlaka yazmam�z gerek

					// t�remi� s�n�f taban s�n�f�n bir sanal fonksiyonuyla ayn� isimle ayn� imzaya sahipse fakat geri d�n�� de�eri t�r� farkl� bir fonksiyon tan�mlarsa
					bu sentaks hatas� sadece tek bir istisna var COVARIANS deniliyor hoca di�er derslerde de�inecek
				};
	
			virtaul function'�n tan�m�n� cpp dosyas�nda yap�yorsak virtual keyword�n� kullanm�yoruz

		VIRTUAL DISPATCH
			// Base classta virtual ile niteledi�imiz fonksiyonlar� t�remi� s�n�flar override etti�inde o t�remi� s�n�ftan hangi nesneleri adres olarak yada referans olarak yollarsak 
				o s�n�f�n fonksiyonu �a��r�l�r ve burda �a��r�lan fonksiyon RUN TIME'DA belli oluyor
				
			class Car {
		public:
			virtual void start() { std::cout << "Car::start()\n"; } 
			virtual void run() { std::cout << "Car::run()\n"; }
			virtual void stop() { std::cout << "Car::stop ()\n"; }
		};

		class Volvo : public Car {
		public:
			void start() override { std::cout << "Volvo::start()\n"; }
			void run() override { std::cout << "Volvo::run()\n"; }
			void stop()override { std::cout << "Volvo::stop ()\n"; }
		};

		class Renault : public Car {
		public:
			void start() override { std::cout << "Renault::start()\n"; }
			void run() override { std::cout << "Renault::run()\n"; }
			void stop() override { std::cout << "Renault::stop ()\n"; }
		};


		class Mercedes : public Car {
		public:
			void start() override { std::cout << "Mercedes::start()\n"; }
			void run() override { std::cout << "Mercedes::run()\n"; }
			void stop()override { std::cout << "Mercedes::stop ()\n"; }
		};

		void car_game(Car& c) 
		{
			c.start();
			c.run();
			c.stop();
		}

		int main()
		{
			Mercedes m;
			Volvo v;
			Renault r;

			car_game(m); 
			car_game(v);
			car_game(r);
		}

		�IKTI:
		Mercedes::start()
		Mercedes::run()
		Mercedes::stop ()
		Volvo::start()
		Volvo::run()
		Volvo::stop ()
		Renault::start()
		Renault::run()
		Renault::stop ()

		bir fonksiyonun hangi fonksiyona ba�lanca�� 2 farkl� �ekilde anla��labiliyor
			1)static binding yada early binding(compile time'da belli olur)
			2)dynamic binding yada late binding(run time'da belli olur)

			derleyici b�yle zamanlarda optimizaasyon yaparak daha d���k maliyetli kod olsun diye virtual dispatch mekanizmas�na ili�kin kod �retmek
			i�ini run time'a b�rakmay�p compile time da ba�layay�m diyebilir buna DEVIRTULAZATION OPTIMIZATION deniliyor

	Car* create_random_car()
	{
		static std::mt19937 eng;
		static std::uniform_int_distribution dist{ 0,2 };

		switch (dist(eng))
		{
		case 0: std::cout << "Volvo..\n"; return new Volvo;
		case 1: std::cout << "Renault..\n"; return new Renault;
		case 2: std::cout << "Mercedes..\n"; return new Mercedes;
		default: return nullptr;
			break;
		}
	}

	int main()
	{

		for (int i = 0; i < 10; ++i)
		{
			Car* p = create_random_car(); // hangi fonksiyonun �a��r�ld��� run time'da belli olur
			car_game(p);
			(void)getchar;
		}
	}

	VIRTUAL DISPATCH'IN DEVREYE G�RD��� SENARYOLAR
		
		1)virtual dispatch'in devreye girmesi i�in fonksiyon �a�r�s�n�n taban s�n�f pointer� yada referans� ile yap�lmas� gerekiyor

				class Car {
			public:
				virtual void start() { std::cout << "Car::start()\n"; }
				virtual void run() { std::cout << "Car::run()\n"; }
				virtual void stop() { std::cout << "Car::stop ()\n"; }
			};

			class Volvo : public Car {
			public:
				void start() override { std::cout << "Volvo::start()\n"; }
				void run() override { std::cout << "Volvo::run()\n"; }
				void stop()override { std::cout << "Volvo::stop ()\n"; }
			};

			class Renault : public Car {
			public:
				void start() override { std::cout << "Renault::start()\n"; }
				void run() override { std::cout << "Renault::run()\n"; }
				void stop() override { std::cout << "Renault::stop ()\n"; }
			};


			class Mercedes : public Car {
			public:
				void start() override { std::cout << "Mercedes::start()\n"; }
				void run() override { std::cout << "Mercedes::run()\n"; }
				void stop()override { std::cout << "Mercedes::stop ()\n"; }
			};

			int main()
			{
				Mercedes m;
			
				Car* pcar = &m;

				pcar->start(); // pcar pointer� Mercedes'in adresini tuttu�u i�in Mercedes'in override fonksiyonlar� �a��r�lacak
				pcar->run();
				pcar->stop();
			}

		2)virtual olmayan fonksiyon i�erisinde gizli parametre fonksiyonuna hangi adres geldiyse o nesnesin adresiyle �a�r� yapabiliyoruz
			
				class Car {
			public:
				virtual void start() { std::cout << "Car::start()\n"; }
				virtual void run() { std::cout << "Car::run()\n"; }
				virtual void stop() { std::cout << "Car::stop ()\n"; }

				void test() // gizli parametre de�i�keni Car* 
				{
					start(); // hangi nesne ile �a��r�l�rlarsa gizli parametre de�i�kenine o nesnesinin adresini ge�ecek ve override olan fonksiyonu �a��racak
					run();
					stop();
					
					// Car::start(); // burda taban s�n�f�n fonksiyonunu niteleyerek �a��rd���m�z i�in virtual dispatch devreye girmiyor
					// Car::run();
					// Car::stop();
				}
			};

			class Volvo : public Car {
			public:
				void start() override { std::cout << "Volvo::start()\n"; }
				void run() override { std::cout << "Volvo::run()\n"; }
				void stop()override { std::cout << "Volvo::stop ()\n"; }
			};

			class Renault : public Car {
			public:
				void start() override { std::cout << "Renault::start()\n"; }
				void run() override { std::cout << "Renault::run()\n"; }
				void stop() override { std::cout << "Renault::stop ()\n"; }
			};


			class Mercedes : public Car {
			public:
				void start() override { std::cout << "Mercedes::start()\n"; }
				void run() override { std::cout << "Mercedes::run()\n"; }
				void stop()override { std::cout << "Mercedes::stop ()\n"; }
			};

			int main()
			{
				Mercedes m;

				m.test();
			}

	taban s�n�f sanal fonksiyonunu override eden t�remi� s�n�f fonksiyonunda virtual keyword'� kullan�lmasa da virtual functiond�r
	��nk� oda override edilebilir

		class Base{
			public:
				virtual void foo()
				{
					std::cout<<"Base::foo()\n";
				}
		};

		class Der : public Base{
			public:
				virtual void foo() override { // virtual anahtar kelimesini yazmasak bile hala virtual fonksiyondur Der s�n�f�ndan kal�t�mla yeni bir s�n�f olu�turuldu�u zaman 
												 bu fonksiyonu override edebilir
					std::cout<<"Der::foo()\n";
				}
		};

		class Sder : public Der{
			public:
				 void foo() override {
					std::cout<<"Sder::foo()\n";
				}
		};

		void bar(Base& r){
			r.foo();
		}

		void baz(Der& r){
			r.foo();
		}
		
		int main()
		{
			Sder x;

			bar(x); 
			baz(x);
			
			// Sder'in foo fonksiyonu �a��r�l�r ��nk� Sder hem Base hemde Der oldu�u i�in iki �ekildede �a��r�labilir
		}

	SORU:Der s�n�f� Base s�n�f�n�n pure virtual foo fonksiyonunu override etmezse Sder s�n�f� edebilir mi? EVET ama override etmedi�imiz i�in Der s�n�f�ndan nesne olu�turamay�z
	concrete class olmas� i�in ve Der s�n�f�ndan da nesne olu�turmak istiyorsak foo fonksiyonunu override etmemiz gerek
		
		class Base{
			public:
				virtual void foo() = 0;

		};

		class Der : public Base{
		
		};

		class Sder : public Der{
			public:
				 void foo() override {
					std::cout<<"Sder::foo()\n";
				}
		};

	�RNEK:eri�im kontrol�n�n run time ile hi� bir ilgisi yok

		class Base{
			public:
				virtual void foo(){}
		};

		class Der : public Base{
			private:
				void foo() override
				{
					std::cout<<"Der::foo()\n";
				}
		};

		void func(Base* baseptr)
		{
			baseptr->foo(); // burda eri�im kontrol� yap�l�yor ��nk� isim ile eri�iliyor e�er foo fonksiyonu Base class'�n private b�l�m�nde olsayd� burda sentaks hatas� olacakt�
		}

		int main()
		{
			Der myder;
			func(&myder); // virtual dispatch ile Der'in foo fonksiyonu �a��r�l�r

			myder.foo(); // �imdi eri�im kontrol�ne tak�l�r ��nk� ismi kulland�k direkt olarak Der s�n�f�nda arama yap�ld�
		}

		�RNEK:default arg�man static t�rle alakal�

			class Base{
				public:
					virtual void foo(int x = 5)
					{
						std::cout<<"Base::foo(int x) x = " << x <<'\n';
					}
			};

			class Der : public Base{
				public:
					virtual void foo(int x = 77) override
					{
						std::cout<<"Der::foo(int x) x = " << x <<'\n';
					}
			};

			int main()
			{
				Der myder;

				Base* baseptr = &myder;

				baseptr->foo(); // derleyici foo fonksiyonunu Base classta buldu virtual dispatch kodu �retecek ama g�nderilen arg�man�n virtual dispatch ile alakas� olmad��� i�in
				ba�ka arg�man g�nderilmedi�ini g�rd� bu y�zden Base class'�n default arguman�n� g�r�yor ve o arg�man� �a��r�yor 
			}
	
		�IKTI: Der::foo(int x) x = 5

	VIRTUAL DISPATCH DEVREYE G�RMED��� SENARYOLAR
		1)sanal fonksiyon �a�r�s� taban s�n�f nesnesiyle yap�l�rsa(object slicing)
			
			object slicing'te virtual dispatch devreye girmiyor(Taban s�n�f�n pointer yada referans olmayan nesnesine t�remi� s�n�f nesnesini atamak)
			
			class Car {
			public:
				virtual void start() { std::cout << "Car::start()\n"; }
				virtual void run() { std::cout << "Car::run()\n"; }
				virtual void stop() { std::cout << "Car::stop ()\n"; }

				void test() 
				{
					start(); 
					run();
					stop();

				}
			};

				class Mercedes : public Car {
			public:
				void start() override { std::cout << "Mercedes::start()\n"; }
				void run() override { std::cout << "Mercedes::run()\n"; }
				void stop()override { std::cout << "Mercedes::stop ()\n"; }
			};

			int main()
			{
				Mercedes m;

				Car mycar = m;
				mycar.start(); // virtual dispatch devreye girmez Car s�n�f�n�n start fonksiyonu �a��r�l�r
			}

		2)taban s�n�f�n sanal fonksiyonu taban s�n�f ismiyle nitelenerek �a��r�ld�ysa
				
				class Car {
			public:
				virtual void start() { std::cout << "Car::start()\n"; }
				virtual void run() { std::cout << "Car::run()\n"; }
				virtual void stop() { std::cout << "Car::stop ()\n"; }

				void test() // gizli parametre de�i�keni Car* 
				{
					start(); 
					run();
					stop();
					
					// Car::start(); // b�yle �a��r�rsak virtual dispatch devreye girmiyor
					// Car::run();
					// Car::stop();
				}
			};

		3)taban s�n�f�n ctor ve dtor i�inde sanal fonksiyona �a�r� yap�ld�ysa
			
			Ctor i�inde sanal fonksiyonlara yap�lan �a�r�da virtual dispatch devreye girmiyor e�er ctor i�inde virtual dispatch devreye girseydi felaket olurdu ��nk� t�remi� s�n�f nesnesi 
				program�n ak��� t�remi� s�n�f�n ctorunu tamamlad��� zaman e�er devreye girseydi t�remi� s�n�f�n override fonksiyonu t�remi� s�n�f�n memberlar�n� kullan�yor 
				olabilirdi e�er virtaual dispatch ba�lansayd� hayata gelmemi� t�remi� s�n�f nesnesi i�in fonksiyon �a�r�s� yapm�� olurduk

			class Base{
				public:
					Base()
					{
						foo();
					}
					
					virtual void foo()
					{

					}
			};

			class Der : public  Base
			{
				public:
					virtual void foo()
					{
						std::cout<<"Der::foo()\n";
					}
			};

		Dtor'da da virtual dispatch devreye girmiyor ��nk� nesnesin hayat� zaten bitmi� oluyor

	
	VIRTUAL CTOR IDIOM
		ctorlar virtual olabilir mi? HAYIR ama b�yle bir ihtiya� var buna kar��l� gelen idiom VIRTUAL CTOR IDIOM YADA CLON IDIOM deniyor

			class Car {
			public:
				virtual void start() { std::cout << "Car::start()\n"; }
				virtual void run() { std::cout << "Car::run()\n"; }
				virtual void stop() { std::cout << "Car::stop ()\n"; }
				virtual Car* clone() = 0;
				};
			class Volvo : public Car {
			public:
				void start() override { std::cout << "Volvo::start()\n"; }
				void run() override { std::cout << "Volvo::run()\n"; }
				void stop()override { std::cout << "Volvo::stop ()\n"; }
				Car* clone() override
				{
					return new Volvo(*this); // burda copy construct ediyoruz
				}
			};

			class Renault : public Car {
			public:
				void start() override { std::cout << "Renault::start()\n"; }
				void run() override { std::cout << "Renault::run()\n"; }
				void stop() override { std::cout << "Renault::stop ()\n"; }
				Car* clone() override
				{
					return new Renault(*this); // burda copy construct ediyoruz
				}
			};
			class Mercedes : public Car {
			public:
				void start() override { std::cout << "Mercedes::start()\n"; }
				void run() override { std::cout << "Mercedes::run()\n"; }
				void stop()override { std::cout << "Mercedes::stop ()\n"; }
				Car* clone() override
				{
					return new Mercedes(*this); // burda copy construct ediyoruz
				}
			};
			
		Car* create_random_car()
		{
			static std::mt19937 eng;
			static std::uniform_int_distribution dist{ 0,2 };

			switch (dist(eng))
			{
			case 0: std::cout << "Volvo..\n"; return new Volvo;
			case 1: std::cout << "Renault..\n"; return new Renault;
			case 2: std::cout << "Mercedes..\n"; return new Mercedes;
			default: return nullptr;
				break;
			}
		}

		void car_game(Car& c)
		{
			Car* pnewcar = c.clone();
			c.start();
			pnewcar->start();
			c.run();
			pnewcar->run();
			c.stop();
			pnewcar->stop();
		}
		
		int main()
		{
			for (int i = 0; i < 10; ++i)
			{
				Car* p = create_random_car();
				car_game(*p);
			}
		}

		�RNEK:s�n�fa sanal fonksiyon ekledi�imizde s�n�f�n sizeof de�eri artar

			class Base{
				public:
					int mx,my{};
					virtual void foo(){}
					virtual void bar(){}
					virtual void baz(){} // sadece 1 fonksiyonu virtual yaparsak s�n�f�n storage de�eri artar 
			};

		class Der {
		public:
			virtual void foo() {}
			virtual void bar() {}
			virtual void baz() {}
		};

			int main()
			{
				std::cout<<"sizeof(Base) = " << sizeof(Base) <<'\n';
				std::cout << "sizeof(Der) = " << sizeof(Der) << '\n';
			}
			
			�IKTI: 
			sizeof(Base) = 16 // virtual fonksiyon olmasa s�n�f�n storage de�eri 8 olacakt� storage de�eri derleyiciden derleyiciye de�i�iyor 
			sizeof(Der) = 8 

	CONTEXTUAL KEYWORD(ba�lamsal anahtar s�zc�k)
		belirli bir contextte kullan�ld��� zaman anahtar s�zc�k etkisi yap�yor ama o context'in d���nda anahtar s�zc�k olarak de�il
		do�rudan identifier olarak kullan�labiliyor

		modern C++ ile dile eklenen 2 tane contextual keyword var
			1)override
			2)final

			int main()
			{
				int override = 5; // e�er anahtar kelime olsayd� sentaks hatas� verirdi anahtar kelime olarak eklenmemesinin nedeni
				eski var olan kodlar�n k�r�lmamas� a��s�ndan
			}
*/