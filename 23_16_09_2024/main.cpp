/*

INHERITANCE

	inheritance'ý iki ayrý anlamda kullanmakta fayda var 
		1)Nesne yönelimli progralama tarafýndaki inheritance(is-a-relationship)
		2)Generic programming tarafýnda
	
	sentaks biçimi
		Animal(C++ teriminde kalýtýmda kaynak olarak kullanýlan sýnýfa Base class deniliyor ama Parent class yada Super class terimleride kullanýlabiliyor)
			interface 

		Lion(C++ teriminde kalýtým yoluyla elde edilen sýnýflara Derived(derivation) class deniliyor ama Child class yada Subclass terimleride kullanýlabiliyor)
			interface
		
		Animal sýnýfýndan olan türler örneðin Lion sýnýfý olsun bu sýnýfý Animal türünden kalýtým yoluyla elde edeceðiz
		ve Lion sýnýfý Animal sýnýfýnýn interface'ine sahip olmuþ olacak

	hocam modellemelere örnek veriyor

		SINGLE LEVEL INHERITANCE(fotoðraflarý inceleyiniz)
		MULTI LEVEL INHERITANCE
		MULTIPLE INHERITANCE

	kalýtým gerçekleþtireceksek base class'ýn complete type olmasý gerekiyor
		class Base{ // complete type

		};

	C++ dilinde 3 tane ayrý kalýtým modeli var
		1)public inheritance(is-a relationship'i saðlýyor)
			class Base{
		
			};
		
			class Der: public Base{
		
			}
		2)private inheritance(has-a-relationship'i saðlýyor)
			class Base{
		
			};
		
			class Der: private Base{
		
			}
		3)protected inheritance(has-a-relationship'i saðlýyor)
			class Base{
			
			};
			
			class Der: protected Base{
			
			}

	PUBLIC INHERITANCE(is-a-relationship)
		
		Taban sýnýfýn public interface'i türemiþ sýnýfýn public interface'ine dahil ediliyor

		class Base{
			public:
				void foo();
				void bar();
				void baz();
				static double dval;
				using value_type = int;
		};

		class Der: public Base{ // public inheritance eðer hiç bir þey yazmazsak default olarak private inheritance oluyor
								   class yerine struct olsaydý default olarak public inheritance olur
		
			// her Der nesnesinin içinde bir Base var

		};

		int main()
		{

			Der myder; 

			myder.foo();
			myder.bar();
			myder.baz();
			Der::dval;
			Der::value_type bx();
		}
		
		SORU:A sýnýf nesnesinin içinde fiziksel olarak B sýnýf nesnesi var(has-a-relationship) o zaman kesin olarak A'nýn B türünden elemaný var diyebilir miyiz? HAYIR
			 çünkü A sýnýfý kalýtým yoluyla B sýnýfýndan elde edilmiþte olabilir(is-a-relationship)

			 Eðer kalýtým söz konusuysa A class'ýna base class object diyoruz eðer composition söz konusuysa A'nýn içindeki B'ye Member object terimi kullanýlýyor 
			 
			 ÖRNEK:composition

			 class B {
				int x, y;
			};
			class A {

				int a, b;
				B bx;
			};


			int main()
			{

				std::cout << "sizeof(B) = " << sizeof(B) << '\n';
				std::cout << "sizeof(A) = " << sizeof(A) << '\n';

			}

			ÇIKTI:
			sizeof(B) = 8
			sizeof(A) = 16

			ÖRNEK:inheritance

			 class B {
				int x, y;
			};
			class A  : public B{

				int a, b;
			};


			int main()
			{

				std::cout << "sizeof(B) = " << sizeof(B) << '\n';
				std::cout << "sizeof(A) = " << sizeof(A) << '\n';

			}

			ÇIKTI:
			sizeof(B) = 8
			sizeof(A) = 16

			yine A sýnýfý 16 B sýnýfý 8 çünkü A'nýn içinde yine B sýnýfý var

	KALITIMDA ÝSÝM ARAMA
		
		bir ismi nokta operatörünün ok operatörünün yada scope resolution operatörünün sað operandý olarak kullanýrsak sol operand türemiþ sýnýfa 
		iliþkinse sað operand olan isim ilk önce türemiþ sýnýf içinde aranýr
		
		class Base{
			public:
				void x ();
		};

		class Der : public Base{
			public:
				int x;
		};
		
		int main()
		{
			Der myder;

			myder.x; // x ismi önce Derived classta aranacak orda bulunamazsa Base classta aranýr
		}

		SORU:function overloading mi deðil mi? DEÐÝL çünkü scopelarý farklý
				class Base{
					public:
						void foo(double);
				};

				class Der : public Base{
					public:
						void foo(int);
				};
				
				int main()
				{
					Der myder;

					myder.Base::foo(3.4);
				}

	ERÝÞÝM KONTROLÜ
		
		base class'ýn public interface'i derived class'a aktarýldýðý için derived class'ýn nesneleriyle base class'ýn public bölümüne eriþebiliyoruz ama private ve protected bölümüne
		eriþemiyoruz
			
				class Base{
					private:
						void foo();
					protected:
						void bar();
				};

				class Der : public Base{
				};

				int main()
				{
					Der myder;

					myder.foo(); // eriþim kontrolüne takýlýr
					myder.bar(); // eriþim kontrolüne takýlýr 
				}

			derived classlarýn içinde protected bölüme eriþebiliriz
				
				class Base{
					private:
						void foo();
					protected:
						void bar();
				};

				class Der : public Base{

					void func()
					{
						bar(); // geçerli
					}
				};

			SORU:sentaks hatasý mý deðil mi? ERÝÞÝM KONTRÖLÜNE TAKILIR çünkü isim derived classta aranýr ve bulunur isim arama sona erer
				class Base{
					public:
						void func(int);
				};

				class Der : public Base{
					private:
						void func(double);

				};

				int main()
				{
					
					Der myder;

					myder.func(12); // eriþim kontrolüne takýlýr

				}

			eðer Derived class Base class'tan public kalýtýmý ile elde edilmiþ ise her Der ayný zamanda bir Base'tir 
			her bmw bir arabadýr ama her araba bmw deðildir

			Derived class'tan Base class'a doðru implicit conversion var buna UP CASTING deniliyor örneðin Car gereken yerde bir Mercedes kullanýldýðýnda örtülü bir dönüþüm oluyor
				
				class Car{

				};

				class Mercedes : public Car{};

				class Audi : public Car{};

				class Volvo : public Car{};

				int main()
				{
					Mercedes mercedes;
					Audi audi;
					Volvo volvo;

					Car* pcar = &mercedes; // is-a-relationship iliþkisi olmasaydý bu sentaks hatasý olacaktý

					pcar = &audi;

					pcar = &volvo;

					referans semantiðinide kullanabiliriz
					
					Car& rcar = mercedes;
						
				}

				ÖRNEK:
					
					class Base{
						public:
							void foo();
					};

					class Der : public Base{

					};

					int main()
					{
						Der myder;
						myder.foo();
					};
				
				SORU:Base sýnýfýnýn non-static member function'ýn gizli parametre deðiþkeni var mý? EVET Base*
				SORU:foo fonksiyonun çaðýrýlmasý için aslýnda bir Base nesnesinin adresi gerekiyor deðil mi? EVET 

				Der nesnesiyle Base'in üye fonkiyonunu çaðýrdýðýmýzda aslýnda this pointerý olarak derleyici Der'in içindeki Base'in adresini geçiyor 

			Türemiþ sýnýfýn üye fonksiyonunun içinde nitelenmemiþ isim kullanýlmasý durumunda isim arama kurallarý

				// 6(namespace)

				class Base{
					// 5
				};

				class Der{
					// 4
				};

				void Der::foo()
				{
					// 3
					{
						// 2
						{
							// 1.aranacak yer
						}

					}
					
				}

			SORU:UP CASTING ile Derived class öðelerine eriþimimiz kalýyor mu? HAYIR çünkü Base class'ýn pointerý ile sadece Base classtaki isimleri kullanabiliriz
				
				class Base{

				};

				class Der : public Base{
					public:
						void foo();
				};

				int main()
				{
					Der myder;
					Base* baseptr = &myder;

					baseptr->foo(); // sentaks hatasý 
				}

			bazý özel durumlardaysa bir Car nesnesinin bir Mercedes olduðundan emin olduðumuz durumlarda Car nesnesinini Mercedes nesnesi olarak kullanmak için Car sýnýfýndan Mercedes 
			sýnýfýna dönüþüm yapacaðýz buna da DOWN CASTING deniliyor

			UP CASTING'IN destekleniyor olmasý DOWN CASTING'de ayný þekilde desteklendiði anlamýna gelmiyor
				
				class Car{

				};

				class Mercedes : public Car{};

				class Audi : public Car{};

				class Volvo : public Car{};

				int main()
				{
					Car mycar;

					Mercedes* pm = &mycar; // örtülü dönüþüm olmadýðý için sentaks hatasý dönüþümü explicit þekilde yapmamýz gerek
					//Mercedes* pm = static_cast<Mercedes*>(&mycar) 
					
				}

		OBJECT SLICING
			
			UP CASTING'I her zaman pointer semantiðiyle yada referans semantiðiyle yapmamýz gerekiyor 
				
				class Car{

				};

				class Mercedes : public Car{};

				class Audi : public Car{};

				class Volvo : public Car{}; 

				int main()
				{
					Mercedes m;
					Audi a;
					Volvo v;

					Car mycar = m; // artýk mercedes'e ait hiç bir þey kalmamýþ olur ileride daha detaylý inceleyeceðiz
					mycar = a;
					mycar = v;

						// Her ne kadar bu kod sentaks açýsýndan hatasýz olsa da object slicing nedeniyle türetilmiþ sýnýfýn özelliklerinin kaybolmasý durumu oluþur
						   Bu yüzden bu tarz kullaným tavsiye edilmez
				}

	ÖRNEK:

		class A{

		};

		class B : public A{

		};

		class C : public B{

		};

		SORU:her B bir A'mý dýr? EVET A sýnýfý B sýfýnýn taban sýnýfýdýr
		SORU:A sýnýfý C sýnýfýnýn taban sýnýfý mýdýr? EVET B sýnýfý C sýnýfýnýn taban sýnýfý mýdýr? EVET 

		B ile A'nýn farkýný belirtmek için DIRECT BASE CLASS(doðrudan taban sýnýf) terimini kullanýyoruz B sýnýfý C sýnýfýnýn Direct base class'ý  
		A sýnýfý C sýnýfýnýn INDIRECT BASE CLASS'I(dolaylý taban sýnýf) olmuþ oluyor

	POLYMORPHISM(çok biçimlilik demek daha detaylý göreceðiz)
		her polymorphism run time polymorphism olmak zorunda deðil function overloading'de bir polymorphism kalýtýmda bir polymorphism biçimi
		run time polymorphism'i ilerleyen derslerde göreceðiz
		
		class Car{
			public:
				void start();
				void run();
				void stop();
		};
		
		class Skoda : public Car{
			public:
				void maintain();
				void open_sunroof();
		};

		int main()
		{
			Skoda myskoda;

			myskoda.start();
			myskoda.run();
			myskoda.open_sunroof();
			myskoda.stop();
			myskoda.maintain();
		}

		kalýtýmýn çoðu zaman amacý code reuse'un(kodun yeniden kullanýlabilir olmasý) dýþýnda eskiden yazýlan kodlarýn yeni yazýlan kodlarý kullanabilmesi

			biz daha kalýtýmla elde edilecek sýnýflarý bilmeden tasarýmý taban sýnýfýn interface'ine baðlý olarak yapabiliyoruz

				class Car{
					public:
						void start();
						void run();
						void stop();
				};

				void car_game(Car* p)
				{
					p->start();
					p->run();
					p->stop();
				}
			tasarým tipik olarak yukarýdaki interface'e baðlý olarak yazýlýyor örneðin Mercedes sýnýfýný Car sýnýfýndan public kalýtým yoluyla oluþturursak
			bu fonksiyon Mercedes sýnýf nesneleri içinde kullanýlabilecek

	INHERITANCE & SPECAIL MEMBER FUNCTIONS

		türemiþ sýnýfý türünden bir nesne oluþturduðumuzda türemiþ sýnýfý nesnesnin içinde bir taban sýnýf nesnesi var örneðin Mercedes sýnýfý içinde bir Car nesnesi var 
		bu þu demek türemiþ sýnýfý türünden bir nesne oluþturduðumuzda türemiþ sýnýf türünden nesnesinin oluþturulabilmesi için ilk önce onun içindeki taban sýnýf nesnesinin 
		hayata gelmesi gerekiyor

		önce(varsa) taban sýnýf nesnesi yada nesneleri hayata gelir daha sonra elemanlar(member) olan nesneler hayata gelir
		sonra programýn akýþý ctor'un ana bloðunun içine girer ve ctor'un ana bloðunun içindeki bütün kodlar çalýþtýktan sonra 
		nesne hayata gelmiþ olur

		eðer MIL sentsaksý ile taban sýnýfýn belirlenmiþ bir ctoruna çaðrý yapmazsak derleyici her zaman türemiþ sýnýfýn ctrouna taban sýnýfýn default ctoruna
		yapýlan çaðrýyý ekler

			class Base{
				public:
					Base()
					{
						std::cout<<"Base default ctor<<'\n';
					}
			};

			class Der : public Base{
				// derleyicinin yazdýðý default ctor Base'in default ctoruna çaðrý yapýyor
			};

			int main()
			{
				Der myder; // geçerli
			}

			DÝKKAT:eðer Der'in default ctorunu biz yazsaydýk derleyici Base'in default ctoruna çaðrýyý yine yapmýþ olacaktý
				
				class Base{
					public:
						Base()
						{
							std::cout<<"Base default ctor\n";
						}
				};

				class Der : public Base{
					public:
						Der() : // Base() derleyici burda Base'in default ctoruna çaðrý yapýyor {
							std::cout<<"Der default ctor\n";
						}
				};

				int main()
				{
					Der myder; // geçerli
				}

		ÖRNEK:derleyicinin Der için yazdýðý default ctorda derleyici önce taban sýnýf nesnesini sonra elemenlarý bildirim sýrasýyla initalize edecek
		yani örneðin önce Base default ctor sonra Member default ctor yazýlarýnýn çýkmasý garanti altýnda 

				class Member{
					public:
						Member()
						{
							std::cout<<Member default ctor\n";
						}
				};
				class Base{
					public:
						Base()
						{
							std::cout<<"Base default ctor\n";
						}
				};

				class Der : public Base{
					public:
						Der() :  
						{
							std::cout<<"Der default ctor\n";
						}
					private:
						Member mx;
				};

				int main()
				{
					Der myder; // geçerli
				}

			ÇIKTI:
			Base default ctor
			Member default ctor
			Der default ctor

		ÖRNEK:Base sýnýfýnýn default ctoru olmasaydý baþka ctoru olsaydý bu durum sentaks hatasý olur muydu? HAYIR ama derleyici Der için yazacaðý default ctoru  
		sentaks hatasý oluþturacaðýndan derleyici default ctoru delete edecekti

			class Base {
			public:
				Base(int)
				{
					std::cout << "Base(int) ctor\n";
				}
			};

			class Der : public Base {
			public:
				Der() // : Base(5) burda sentaks hatasý olmamasý için Base sýnýfýnýn ctoruna çaðrý yapmamýz lazým eðer bir çaðrý yapmazsak  
				'Base': no appropriate default constructor available hatasý alýrýz yani hatayý almamýzýn sebebi olmayan bir ctora çaðrý yapmamýzdý(default ctor)
				{
					std::cout << "Der default ctor\n";
				}

			};

			int main()
			{
				Der myder; // Der sýnýfýnýn default ctoru var ama delete edilmiþ durumda
			}

		ÖRNEK:Base class'ýn default ctoru private olsaydý Der sýnýfýnýn default ctoru delete edilecekti
			
			class Base{
				private:
					Base();
			};

			class Der : public Base{

			};

			int main()
			{
				Der myder; // 'Der::Der(void)': attempting to reference a deleted function
			}

		ÖRNEK:nesneler hayata gelme sýrasýyla ters sýrada destroy edilecekler
			
			class Member {
			public:
				Member()
				{
					std::cout << "Member default ctor\n";
				}
				~Member()
				{
					std::cout << "Member dtor\n";
				}
			};
			class Base {
			public:
				Base()
				{
					std::cout << "Base default ctor\n";
				}
				~Base()
				{
					std::cout << "Base dtor\n";
				}
			};

			class Der : public Base {
			public:
				Der()
				{
					std::cout << "Der default ctor\n";
				}
				~Der()
				{
					std::cout << "Der dtor\n";
				}
			private:
				Member mx;
			};

			int main()
			{
				Der myder;
			}

			ÇIKTI:
			Base default ctor
			Member default ctor
			Der default ctor
			Der dtor
			Member dtor
			Base dtor

		ÖRNEK:Taban sýnýfýn ctorunu MIL sentaksýyla çaðýrmak

		class Person {
			public:
				Person(const std::string name, const std::string surname);
		};

		class VipPerson : public Person {
			public:
				VipPerson(const std::string& name,const std::string surname,int age) : Person(name,surname),m_age(age){}
			private:
				int m_age;
		};		

		ÖRNEK:Copy ctoru derleyicinin yazýmýna býrakmak

			hayata getirelecek türemiþ sýnýf nesnesinin içindeki taban sýnýf nesnesini copy construct ediyor

			class Base{
				public:
					Base()
					{
						std::cout<<"Base default ctor\n"; 
					}

					Base(const Base&)
					{
						std::cout<<"Base copy ctor\n"; 
					}
			};
			
			class Der : public Base{
				public:

			}

			int main()
			{
				Der d1;
				Der d2(d1);
			}

		ÖRNEK:eðer copy ctoru kendimiz yazarsak taban sýnýfýn default ctorunun deðil copy ctorunun çaðýrýlmasýndan sorumluyuz
		eðer çaðrý yapmazsak derleyici default ctora çaðrý yapacak olan kodu üretecek

			class Base{
				public:
					Base()
					{
						std::cout<<"Base default ctor\n";
					}

					Base(const Base&)
					{
						std::cout<<"Base copy ctor\n";
					}
			};

			class Der : public Base{
				public:
					Der() = default;
					Der(const Der& other) // : Base(other) derleyici burda Base sýnýfýnýn copy ctoruna çaðrýyý eklemiyor bizim eklememiz gerek eðer eklemezsek default ctora çaðrý yapýyor
					{
						std::cout<<"Der ctor\n";
					}
			};

			int main()
			{
				Der d1;
				Der d2(d1);
			}

		ÖRNEK:ayný kural move ctor içinde geçerli move ctoru kendimiz yazarsak taban sýnýfýn default ctorunun deðil move ctorunun çaðýrýlmasýndan sorumluyuz
		eðer çaðrý yapmazsak derleyici default ctora çaðrý yapacak olan kodu üretecek

			class Base {
			public:
				Base()
				{
					std::cout << "Base default ctor\n";
				}

				Base(Base&&)
				{
					std::cout << "Base move ctor\n";
				}
			};

			class Der : public Base {
			public:
				Der() = default;
				Der(Der&& other) // : Base(std::move(other)) eðer bu çaðrýyý kendimiz yapmazsak derleyici burda Base sýnýfýnýn move ctoruna çaðrý yapmak yerine default ctora çaðrý yapar
				{
					std::cout << "Der move ctor\n";
				}
			};

			int main()
			{
				Der d1;
				Der d2(std::move(d1));
			}

		ÖRNEK:memberlarda olduðu gibi derleyici eðer atama operatörü fonksiyonunu kendisi yazýyorsa copy assignment fonksiyonunu yazarken taban sýnýf nesnesi için copy assigmentý çaðýracak
		move assignment için move assignmentý çaðýracak eðer copy assigment'ý yada move assignment'ý kendimiz yazarsak taban sýnýfýn assignmentlarýný çaðýrmak
		yine bizim kontrolümüzde

			class Base{
				public:
					Base& operator=(const Base&)
					{
						std::cout<<"Base copy assignment\n";
						return *this;
					}
					Base& operator=(Base&&)
					{
						std::cout<<"Base move assignment\n";
						return *this;
					}
			};

			class Der : public Base{
				public:
					Der& operator=(const Der&)
					{
						// Base::operator=(other); Der sýnýfýnýn copy assignmentýný kendimiz yazdýðýmýz için Base sýnýfýnýn copy ctoruna bu çaðrýyý yapmasaydýk Base sýnýfýnýn 
													copy assignment fonksiyonu çaðýrýlmayacaktý
						std::cout<<"Der copy assignment\n";
						return *this;
					}
					Der& operator=(Der&& other)
					{
						// Base::operator=(std::move(other));  Der sýnýfýnýn move assignmentýný kendimiz yazdýðýmýz için Base sýnýfýnýn move ctoruna bu çaðrýyý yapmasaydýk Base sýnýfýnýn 
															   move assignment fonksiyonu çaðýrýlmayacaktý
						std::cout<<"Der move assignment\n";
						return *this;
					}
			};

			int main()
			{
				Der d1,d2;
				d1 = d2;
			}

	SORU:indirect class'ýn ctorlarýný çaðýrabilir miyiz? HAYIR sadece direct base class'ýn ctorlarýný çaðýrabiliriz

		class A {
			public:
				A(int);
		};

		class B : public A{
			public:
				B(int,int);
				B(int);
		};

		class C : public B {
			public:
				C(int x) : A(x) // A sýnýfý indirect class olduðu için geçerli deðil hoca sadece tek bir istisnasý olduðunu söyledi virtual inheritance konusunda göreceðiz
		}

	öyle bir bildirim var ki taban sýnýftaki bir ismi türemiþ sýnýfýn scopuna enjekte ediyor bu bildirimde using anahtar sözcüðü kullanýlýyor buda function overloadingide saðlamýþ oluyor
	yani using bildirimiyle sanki o scopeta tanýmlanmýþ gibi oluyor

		class Base {
	public:
		void foo(int i)
		{
			std::cout << "Base::foo(int i) i = " << i << '\n';
		}
	};

	class Der : public Base{
	public:
		using Base::foo;

		void foo(double d)
		{
			std::cout << "Der::foo(double d) d = " << d << '\n';
		}
	};

	int main()
	{
		Der myder;

		myder.foo(12); // Base::foo
		myder.foo(1.2); // Der::foo

	}

	ÇIKTI:
	Base::foo(int i) i = 12
	Der::foo(double d) d = 1.2
	
	Eðer using bildirimini yapmasaydýk þu þekilde yazmamýz gerekecekti

		class Base {
	public:
		void foo(int i)
		{
			std::cout << "Base::foo(int i) i = " << i << '\n';
		}
	};

	class Der : public Base{
	public:
		void foo(double d)
		{
			std::cout << "Der::foo(double d) d = " << d << '\n';
		}

		void foo(int i)
		{
			Base::foo(i); // Base classtaki foo fonksiyonunu çaðýrýyoruz
		}
	};
*/