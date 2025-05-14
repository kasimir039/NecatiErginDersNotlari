/*

INHERITANCE

	inheritance'� iki ayr� anlamda kullanmakta fayda var 
		1)Nesne y�nelimli progralama taraf�ndaki inheritance(is-a-relationship)
		2)Generic programming taraf�nda
	
	sentaks bi�imi
		Animal(C++ teriminde kal�t�mda kaynak olarak kullan�lan s�n�fa Base class deniliyor ama Parent class yada Super class terimleride kullan�labiliyor)
			interface 

		Lion(C++ teriminde kal�t�m yoluyla elde edilen s�n�flara Derived(derivation) class deniliyor ama Child class yada Subclass terimleride kullan�labiliyor)
			interface
		
		Animal s�n�f�ndan olan t�rler �rne�in Lion s�n�f� olsun bu s�n�f� Animal t�r�nden kal�t�m yoluyla elde edece�iz
		ve Lion s�n�f� Animal s�n�f�n�n interface'ine sahip olmu� olacak

	hocam modellemelere �rnek veriyor

		SINGLE LEVEL INHERITANCE(foto�raflar� inceleyiniz)
		MULTI LEVEL INHERITANCE
		MULTIPLE INHERITANCE

	kal�t�m ger�ekle�tireceksek base class'�n complete type olmas� gerekiyor
		class Base{ // complete type

		};

	C++ dilinde 3 tane ayr� kal�t�m modeli var
		1)public inheritance(is-a relationship'i sa�l�yor)
			class Base{
		
			};
		
			class Der: public Base{
		
			}
		2)private inheritance(has-a-relationship'i sa�l�yor)
			class Base{
		
			};
		
			class Der: private Base{
		
			}
		3)protected inheritance(has-a-relationship'i sa�l�yor)
			class Base{
			
			};
			
			class Der: protected Base{
			
			}

	PUBLIC INHERITANCE(is-a-relationship)
		
		Taban s�n�f�n public interface'i t�remi� s�n�f�n public interface'ine dahil ediliyor

		class Base{
			public:
				void foo();
				void bar();
				void baz();
				static double dval;
				using value_type = int;
		};

		class Der: public Base{ // public inheritance e�er hi� bir �ey yazmazsak default olarak private inheritance oluyor
								   class yerine struct olsayd� default olarak public inheritance olur
		
			// her Der nesnesinin i�inde bir Base var

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
		
		SORU:A s�n�f nesnesinin i�inde fiziksel olarak B s�n�f nesnesi var(has-a-relationship) o zaman A'n�n B t�r�nden eleman� var diyebilir miyiz? HAYIR
			 ��nk� A s�n�f� kal�t�m yoluyla B s�n�f�ndan elde edilmi�te olabilir(is-a-relationship)

			 E�er kal�t�m s�z konusuysa A class'�na base class object diyoruz e�er composition s�z konusuysa A'n�n i�indeki B'yr Member object terimi kullan�l�yor 
			 
			 �RNEK:composition

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

			�IKTI:
			sizeof(B) = 8
			sizeof(A) = 16

			�RNEK:inheritance

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

			�IKTI:
			sizeof(B) = 8
			sizeof(A) = 16

			yine A s�n�f� 16 B s�n�f� 8 ��nk� A'n�n i�inde yine B s�n�f� var

			�RNEK:

	KALITIMDA �S�M ARAMA
		
		bir ismi nokta operat�r�n�n ok operat�r�n�n yada scope resolution operat�r�n�n sa� operand� olarak kullan�rsak sol operand t�remi� s�n�fa 
		ili�kinse sa� operand olan isim ilk �nce t�remi� s�n�f i�inde aran�r
		
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

			myder.x; // x ismi �nce Derived classta aranacak orda bulunamazsa Base classta aran�r
		}

		SORU:function overloading mi de�il mi? DE��L ��nk� scopelar� farkl�
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

	ER���M KONTROL�
		
		base class'�n public interface'i derived class'a aktar�ld��� i�in derived class'�n nesneleriyle base class'�n public b�l�m�ne eri�ebiliyoruz ama private ve protected b�l�m�ne
		eri�emiyoruz
			
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

					myder.foo(); // eri�im kontrol�ne tak�l�r
					myder.bar(); // eri�im kontrol�ne tak�l�r 
				}

			derived classlar�n i�inde protected b�l�me eri�ebiliriz
				
				class Base{
					private:
						void foo();
					protected:
						void bar();
				};

				class Der : public Base{

					void func()
					{
						bar(); // ge�erli
					}
				};

			SORU:sentaks hatas� m� de�il mi? ER���M KONTR�L�NE TAKILIR ��nk� isim derived classta aran�r ve bulunur isim arama sona erer
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

					myder.func(12); // eri�im kontrol�ne tak�l�r

				}

			e�er Derived class Base class'tan public kal�t�m� ile elde edilmi� ise her Der ayn� zamanda bir Base'tir 
			her bmw bir arabad�r ama her araba bmw de�ildir

			Derived class'tan Base class'a do�ru implicit conversion var buna UP CASTING deniliyor �rne�in Car gereken yerde bir Mercedes kullan�ld���nda �rt�l� bir d�n���m oluyor
				
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

					Car* pcar = &mercedes; // is-a-relationship ili�kisi olmasayd� bu sentaks hatas� olacakt�

					pcar = &audi;

					pcar = &volvo;

					referans semanti�inide kullanabiliriz
					
					Car& rcar = mercedes;
						
				}

				�RNEK:
					
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
				
				SORU:Base s�n�f�n�n non-static member function'�n gizli parametre de�i�keni var m�? EVET Base*
				SORU:foo fonksiyonun �a��r�lmas� i�in asl�nda bir Base nesnesinin adresi gerekiyor de�il mi? EVET 

				Der nesnesiyle Base'in �ye fonkiyonunu �a��rd���m�zda asl�nda this pointer� olarak derleyici Der'in i�indeki Base'in adresini ge�iyor 

			T�remi� s�n�f�n �ye fonksiyonunun i�inde nitelenmemi� isim kullan�lmas� durumunda isim arama kurallar�

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

			SORU:UP CASTING ile Derived class ��elerine eri�imimiz kal�yor mu? HAYIR ��nk� Base class'�n pointer� ile sadece Base classtaki isimleri kullanabiliriz
				
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

					baseptr->foo(); // sentaks hatas� 
				}

			baz� �zel durumlardaysa bir Car nesnesinin bir Mercedes oldu�undan emin oldu�umuz durumlarda Car nesnesinini Mercedes nesnesi olarak kullanmak i�in Car s�n�f�ndan Mercedes 
			s�n�f�na d�n���m yapaca��z buna da DOWN CASTING deniliyor

			UP CASTING'IN destekleniyor olmas� DOWN CASTING'de ayn� �ekilde desteklendi�i anlam�na gelmiyor
				
				class Car{

				};

				class Mercedes : public Car{};

				class Audi : public Car{};

				class Volvo : public Car{};

				int main()
				{
					Car mycar;

					Mercedes* pm = &mycar; // �rt�l� d�n���m olmad��� i�in sentaks hatas� d�n���m� explicit �ekilde operat�rleri kullanarak yapmam�z gerek
					//Mercedes* pm = static_cast<Mercedes>(&mycar) 
					
				}

		OBJECT SLICING
			
			UP CASTING'I her zaman pointer semanti�iyle yada referans semanti�iyle yapmam�z gerekiyor 
				
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

					Car mycar = m; // art�k mercedes'e ait hi� bir �ey kalmam�� olur ileride daha detayl� inceleyeece�iz
					mycar = a;
					mycar = v;

						// Her ne kadar bu kod sentaks a��s�ndan hatas�z olsa da object slicing nedeniyle t�retilmi� s�n�f�n �zelliklerinin kaybolmas� durumu olu�ur
						   Bu y�zden bu tarz kullan�m tavsiye edilmez."
				}

	�RNEK:multiple inheritance �rne�i

		class A{

		};

		class B : public A{

		};

		class C : public B{

		};

		SORU:her B bir A'm� d�r? EVET A s�n�f� B s�f�n�n taban s�n�f�d�r
		SORU:A s�n�f� C s�n�f�n�n taban s�n�f� m�d�r? EVET B s�n�f� C s�n�f�n�n taban s�n�f� m�d�r oda EVET 

		B ile A'n�n fark�n� belirtmek i�in DIRECT BASE CLASS(do�rudan taban s�n�f) terimini kullan�yoruz B s�n�f� C s�n�f�n�n Direct base class'�  
		A s�n�f� C s�n�f�n�n INDIRECT BASE CLASS'I(dolayl� taban s�n�f) olmu� oluyor

	POLYMORPHISM(�ok bi�imlilik demek daha detayl� g�rece�iz)
		her polymorphism run time polymorphism olmak zorunda de�il function overloading'de bir polymorphism kal�t�mda bir polymorphism bi�imi
		run time polymorphism'i ilerleyen derslerde g�rece�iz
		
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

		kal�t�m�n �o�u zaman amac� code reuse'un(kodun yeniden kullan�labilir olmas�) d���nda eskiden yaz�lan kodlar�n yeni yaz�lan kodlar� kullanabilmesi

			biz daha kal�t�mla elde edilecek s�n�flar� bilmeden tasar�m� taban s�n�f�n interface'ine ba�l� olarak yapabiliyoruz

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
			tasar�m tipik olarak yukar�daki interface'e ba�l� olarak yaz�l�yor �rne�in Mercedes s�n�f�n� Car s�n�f�ndan public kal�t�m yoluyla olu�turursak
			bu fonksiyon Mercedes s�n�f nesneleri i�inde kullan�labilecek

	INHERITANCE & SPECAIL MEMBER FUNCTIONS

		t�remi� s�n�f� t�r�nden bir nesne olu�turdu�umuzda t�remi� s�n�f� nesnesnin i�inde bir taban s�n�f nesnesi var �rne�in Mercedes s�n�f� i�inde bir Car nesnesi var 
		bu �u demek t�remi� s�n�f� t�r�nden bir nesne olu�turdu�umuzda t�remi� s�n�f t�r�nden nesnesinin olu�turulabilmesi i�in ilk �nce onun i�indeki taban s�n�f nesnesinin 
		hayata gelmesi gerekiyor

		�nce(varsa) taban s�n�f nesnesi yada nesneleri hayata gelir daha sonra elemanlar(member) olan nesneler hayata gelir
		sonra program�n ak��� ctor'un ana blo�unun i�ine girer ve ctor'un ana blo�unun i�indeki b�t�n kodlar �al��t�ktan sonra 
		nesne hayata gelmi� olur

		e�er MIL sentsaks� ile taban s�n�f�n belirlenmi� bir ctoruna �a�r� yapmazsak derleyici her zaman t�remi� s�n�f�n ctrouna taban s�n�f�n default ctoruna
		yap�lan �a�r�y� ekler

			class Base{
				public:
					Base()
					{
						std::cout<<"Base default ctor<<'\n';
					}
			};

			class Der : public Base{
				// derleyicinin yazd��� default ctor Base'in default ctoruna �a�r� yap�yor
			};

			int main()
			{
				Der myder; // ge�erli
			}

			D�KKAT:e�er Der'in default ctorunu biz yazsayd�k derleyici Base'in default ctoruna yine yapm�� olacakt�
				
				class Base{
					public:
						Base()
						{
							std::cout<<"Base default ctor\n";
						}
				};

				class Der : public Base{
					public:
						Der() : // Base() derleyici burda Base'in default ctoruna �a�r� yap�yor {
							std::cout<<"Der default ctor\n";
						}
				};

				int main()
				{
					Der myder; // ge�erli
				}

		�RNEK:derleyicinin Der i�in yazd��� default ctorda derleyici �nce taban s�n�f nesnesini sonra elemenlar� bildirim s�ras�yla initalize edecek
		yani �rne�in �nce Base default ctor sonra Member default ctor yaz�lar�n�n ��kmas� garanti alt�nda 

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
					Der myder; // ge�erli
				}

			�IKTI:
			Base default ctor
			Member default ctor
			Der default ctor

		�RNEK:Base s�n�f�n�n default ctoru olmasayd� ba�ka ctoru olsayd� bu durum sentaks hatas� olur muydu? HAYIR ama derleyici Der i�in yazaca�� default ctoru  
		sentaks hatas� olu�turaca��ndan derleyici default ctoru delete edecekti

			class Base {
			public:
				Base(int)
				{
					std::cout << "Base(int) ctor\n";
				}
			};

			class Der : public Base {
			public:
				Der() // : Base(5) burda sentaks hatas� olmamas� i�in Base s�n�f�n�n ctoruna �a�r� yapmam�z laz�m e�er bir �a�r� yapmazsak  
				'Base': no appropriate default constructor available hatas� al�r�z yani hatay� almam�z�n sebebi olmayan bir ctora �a�r� yapmam�zd�(default ctor)
				{
					std::cout << "Der default ctor\n";
				}

			};

			int main()
			{
				Der myder; // Der s�n�f�n�n default ctoru var ama delete edilmi� durumda
			}

		�RNEK:Base class'�n default ctoru private olsayd� Der s�n�f�n�n default ctorun delete edilecekti
			
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

		�RNEK:nesneler hayata gelme s�ras�yla ters s�rada destroy edilecekler
			
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

			�IKTI:
			Base default ctor
			Member default ctor
			Der default ctor
			Der dtor
			Member dtor
			Base dtor


		�RNEK:Taban s�n�f�n ctorunu MIL sentaks�yla �a��rmak

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

		�RNEK:Copy ctoru derleyicinin yaz�m�na b�rakmak

			hayata getirelecek t�remi� s�n�f nesnesinin i�indeki taban s�n�f nesnesini copy construct ediyor

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

		�RNEK:e�er copy ctoru kendimiz yazarsak taban s�n�f�n default ctorunun de�il copy ctorunun �a��r�lmas�ndan sorumluyuz
		e�er �a�r� yapmazsak derleyici default ctora �a�r� yapacak olan kodu �retecek

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
					Der(const Der& other) // : Base(other) derleyici burda Base s�n�f�n�n copy ctoruna �a�r�y� eklemiyor bizim eklememiz gerek e�er eklemezsek default ctora �a�r� yap�yor
					{
						std::cout<<"Der ctor\n";
					}
			};

			int main()
			{
				Der d1;
				Der d2(d1);
			}

		�RNEK:ayn� kural move ctor i�inde ge�erli move ctoru kendimiz yazarsak taban s�n�f�n default ctorunun de�il copy ctorunun �a��r�lmas�ndan sorumluyuz
		e�er �a�r� yapmazsak derleyici default ctora �a�r� yapacak olan kodu �retecek

			class Base {
			public:
				Base()
				{
					std::cout << "Base default ctor\n";
				}

				Base(const Base&)
				{
					std::cout << "Base copy ctor\n";
				}

				Base(Base&&)
				{
					std::cout << "Base move ctor\n";
				}
			};

			class Der : public Base {
			public:
				Der() = default;
				Der(const Der& other) Base(other)
				{
					std::cout << "Der ctor\n";
				}
				Der(Der&& other) // : Base(std::move(other)) e�er bu �a�r�y� kendimiz yapmazsak derleyici burda Base s�n�f�n�n move ctoruna �a�r� yapmak yerine default ctora �a�r� yapar
				{
					std::cout << "Der move ctor\n";
				}
			};

			int main()
			{
				Der d1;
				Der d2(std::move(d1));
			}

		�RNEK:memberlarda oldu�u gibi derleyici e�er atama operat�r� fonksiyonunu kendisi yaz�yorsa copy assignment fonksiyonunu yazarken taban s�n�f nesnesi i�in copy assigment� �a��racak
		move assignment i�in move assignment� �a��racak e�er copy assigment'� yada move assignment'� kendimiz yazarsak taban s�n�f�n assignmentlar�n� �a��rmak
		yine bizim kontrol�m�zde

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
						// Base::operator=(other); Der s�n�f�n�n copy assignment�n� kendimiz yazd���m�z i�in Base s�n�f�n�n copy ctoruna bu �a�r�y� yapmasayd�k Base s�n�f�n�n 
													copy assignment fonksiyonu �a��r�lmayacakt�
						std::cout<<"Der copy assignment\n";
						return *this;
					}
					Der& operator=(Der&& other)
					{
						// Base::operator=(std::move(other));  Der s�n�f�n�n move assignment�n� kendimiz yazd���m�z i�in Base s�n�f�n�n move ctoruna bu �a�r�y� yapmasayd�k Base s�n�f�n�n 
															   move assignment fonksiyonu �a��r�lmayacakt�
						std::cout<<"Der move assignment\n";
						return *this;
					}
			};

			int main()
			{
				Der d1,d2;
				d1 = d2;
			}

	SORU:multiple inheritance'ta undirect class'�n ctorlar�n� �a��rabilir miyiz? HAYIR sadece direct base class'�n ctorlar�n� �a��rabiliriz

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
				C(int x) : A(x) // A s�n�f� indirect class oldu�u i�in ge�erli de�il hoca sadece tek bir istisnas� oldu�unu s�yledi virtaul inheritance konusunda g�rece�iz
		}

	�yle bir bildirim var ki taban s�n�ftaki bir ismi t�remi� s�n�f�n scopuna enjekte ediyor bu bildirimde using anahtar s�zc��� kullan�l�yor buda function overloadingide sa�lam�� oluyor
		
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

	�IKTI:
	Base::foo(int i) i = 12
	Der::foo(double d) d = 1.2
	
	E�er using bildirimini yapmasayd�k �u �ekilde yazmam�z gerekecekti

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
			Base::foo(i); // Base classtaki foo fonksiyonunu �a��r�yoruz
		}
	};
*/