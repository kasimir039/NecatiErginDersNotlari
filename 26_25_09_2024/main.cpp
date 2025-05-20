/*

MULTIPLE INHERITANCE

	 class XBase {
		public:
	 };
	 class YBase {
		public:
	 };

	 class Der : public XBase,public YBase{
		public:

	 
	 };

	 int main()
	 {
		
	 }

	AMBIGUITY �RNEK

		 class XBase {
			public:
				void foo(int);
		 };
		 class YBase {
			public:
				void foo(double);
		 };

		 class Der : public XBase,public YBase{
			public:

			// Der s�n�f�ndan foo fonksiyonu olsayd� base classlar�n foo fonksiyonunu g�lgelemi� olacacakt� ve main'de ambiguity olmayacakt�
		 };

		 int main()
		 {
			Der myder;
			// myder.foo(2); // foo ismi burda ambiguity'e sebep olur g�nderdi�imiz arg�man ile bir alakas� yok ��nk� function overloading yok
			
			myder.XBase::foo(12); // niteleyerek kullan�rsak sentaks hatas� olmaz
			myder.YBase::foo(12);
		 }
		
		using bildirimi ile t�remi� s�n�f�n i�ine foo fonksiyonlar�n� enjekte edersek function overloading olmu� olur
			class XBase {
			public:
				void foo(int) { std::cout << "XBase::foo(int)\n"; }
			};
			class YBase {
			public:
				void foo(double){ std::cout << "YBase::foo(int)\n"; }
			};

			class Der : public XBase, public YBase {
			public:
				using XBase::foo , YBase::foo; // foo fonksiyonlar�n� enjekte ediyoruz(sanki bu scopeta tan�mlanm�� gibi etki ediyor ve function overloading olmu� oluyor)
			};

			int main()
			{
				Der myder;
				myder.foo(2);
				myder.foo(2.5);
			}
			
			�IKTI:
			YBase::foo(int)
			XBase::foo(double)
	
	AMBIGUITY �RNEK

		class X {};
		class Y {};

		class D : public X,public Y{};

		void foo(X& ){}
		void foo(Y& ){}

		int main()
		{
			D dx;

			foo(dx); // dx'ten X ve Y'ye yap�lan d�n���m aras�nda bir se�ilebilirlik olmad��� i�in ambiguity

			foo(static_cast<X&>(dx)); // static_cast operat�r�n� kullanarak sentaks� ge�erli hale getirebiliriz

		}

	CTORLARIN �A�IRILMA SIRASI

		class XBase {
		public:
			XBase()
			{
				std::cout << "XBase ctor\n";
			}

		};
		class YBase {
		public:
			YBase()
			{
				std::cout << "YBase ctor\n";
			}
		};

		class Der : public XBase, public YBase { // kal�t�mdaki s�raya g�re classlar�n ctorlar� �a��r�l�r
		public:

			Der() {

				std::cout << "Der ctor\n";
			}
		};


		int main()
		{
			Der myder;
		}
		
		�IKTI:
		XBase ctor
		YBase ctor
		Der ctor
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DREADFUL(deatful) DIAMOND OF DERIVATION(DDD) / DIAMOND FORMATION 

	�o�unlukla �oklu kal�t�mda kulland���m�z taban s�n�flar ortak bir sanaf s�n�ftan kal�t�m elde edilmi� oluyorlar(g�rseli inceleyin)
	
		   DEVICE

	
	PRINTER		 SCANNER

			
			COMBO

	b�yle bir kal�t�m hiyerar�isi varsa �zel bir sentaks arac�n� kullanmaz PRINTER s�n�f� i�erisindede bir DEVICE olacak SCANNER s�n�f� i�erisinde de bir DEVICE olacak 
	ve bunlardan kal�t�m alan COMBO s�n�f� hem PRINTER hemde SCANNER s�n�f�ndan �oklu kal�t�m yoluyla elde edildi�i i�in COMBO s�n�f�n�n i�inde 2 tane DEVICE olmu� olacak
	��nk� hem PRINTER s�n�f�nda DEVICE var hemde SCANNER s�n�f�n�n i�inde de bir DEVICE var

	
	VIRTUAL INHERITANCE

		diamond of derivation sorununu ��zmek i�in kullan�lan y�ntem

		PROBLEM�N ORNE��

			class B {
				public:
					void foo();
			};

			class X : public B {};
			
			class Y : public B {};

			class D : public X , public Y {
				
				void bar()
				{
					// foo(); // ambiguity

					X::foo(); // ge�erli
					Y::foo(); // ge�erli

					static_cast<X*>(this)->foo(); // ge�erli
					static_cast<Y*>(this)->foo(); // ge�erli
				}	
			
			};

			int main()
			{
				D dx;

				// dx.foo(); ambiguity derleycinin �retti�i kodda B'nin foo fonksiyonuna B nesnesi adresi ge��lmesi gerekiyor ama dx'in i�inde 2 tane B nesnesi var biri X'ten gelen B di�eri Y'den gelen B

				dx.X::foo();
				dx.Y::foo(); // Y'nin B adresini kullanmak istersek ve niteleyerek kullan�rsak ge�erli olur

				// B* bptr = &dx; // ambiguity derleyici hangi adresi kullanaca��n� bilmiyor ��nk� dx'in i�erisinde 2 tane B nesnesi var

				B* bptr1 = static_cast<X*>(&dx); 
				B* bptr2 = static_cast<Y*>(&dx); // ikiside ge�erli
			}


		�RNEK SENARYO

			class B{
				public:
					void foo();
			};
			class X : virtual public B {
			
			};
			class Y : virtual public B{
			
			};
			class D : public X, public Y{ // bu s�n�f�n taban s�n�flar� olan s�n�flarda virtual keyword�n� kullan�yoruz
			
			}; 

			int main()
			{
				D dx;

				dx.foo(); // art�k sentaks hatas� yok

				B* bptr = &dx; // UP CASTING art�k ge�erli 

				virtual inheritance kulland���m�z i�in ambiguity olan senaryolar art�k ambiguity olmuyor
			}

		�RNEK SENARYO 2
			
			class EDevice {
			public:
				virtual ~EDevice() = default;
				 bool is_on() const { return m_flag; }
				void turn_on()
				{
					m_flag = true;

					std::cout << "cihaz acildi\n";
				}
				void turn_off()
				{
					m_flag = false;

					std::cout << "cihaz kapatildi\n";
				}
			private:
				bool m_flag = true;
			};

			class Printer : virtual public EDevice {
			public:
				void print()
				{
					if (!is_on()) {
						std::cout << "cihaz kapali oldugundan print islemi yapilamiyor\n";
					}
					else {
						std::cout << "print islemi tamamlandi\n";
					}
				}

			};

			class Scanner : virtual public EDevice {
			public:
				void scan()
				{
					if (!is_on()) {
						std::cout << "cihaz kapali oldugundan scan islemi yapilamiyor\n";
					}
					else {
						std::cout << "scan islemi tamamlandi\n";
					}
				}

			};

			class Combo : public  Printer,public  Scanner { // bu s�n�f�n taban s�n�flar� olan s�n�flarda virtual keyword�n� kullan�yoruz
			public:


			};
			int main()
			{
				Combo mycombo;

				Combo mycombo;

				mycombo.turn_on();
				
				mycombo.print();
				mycombo.scan();

				mycombo.turn_off();

				mycombo.print();
				mycombo.scan()
			}

			�IKTI:
			cihaz acildi
			print islemi tamamlandi
			scan islemi tamamlandi
			cihaz kapatildi
			cihaz kapali oldugundan print islemi yapilamiyor
			cihaz kapali oldugundan scan islemi yapilamiyor

		�RNEK:sadece DIRECT BASE CLASSLAR MIL sentaks� ile initialize edilebilir
			
			class X{
				public:
				X(int);
				X();
			};

			class Y : public X{};

			class Z : public Y{
				public:
					Z() : Y() // ge�erli ��nk� Y Z'nin DIRECT BASE CLASS'I , X(12); // ge�ersiz ��nk� X Z s�n�f�n�n IN-DIRECT BASE CLASS'I{}
			};

			ama �yle bir senaryo var ki s�n�f hiyerar�isinde ki t�m s�n�flar�n do�rudan taban s�n�f de�il ortak taban s�n�f nesnesini intialize etmesi gerekiyor
				
				class X
				{
				public:
					X(const char* p)
					{
						std::cout << "X ctor " << p << '\n';
					}
				};

				class Y : virtual public X {
				public:
					Y() : X("Y ctor\n") {}
				};

				class Z : virtual public X {
				public:
					Z() : X("Z ctor\n") {}
				};

				class D : virtual public Y, virtual public Z // virtual inheritance sayesinde s�n�f�n i�inde ortak taban s�n�f olan X nesnesinden bir adet nesne var
				{
				public:
					D() : X("D ctor\n") {} // X D'nin do�rudan taban s�n�f� de�il ama virtual inheritance'dan dolay� D'nin i�erisinde ortak olan X taban s�n�f nesnesini initialize etme 
											  g�revi art�k D'nin ctorunda
				};

				class E : public D {
				public:
					E() : X("E ctor\n") {} // X E'nin do�rudan taban s�n�f� de�il ama virtual inheritance'dan dolay� E'nin i�erisinde ortak olan X taban s�n�f nesnesini initialize etme 
											  g�revi art�k E'nin ctorunda
				};

				int main()
				{
					E dx;

				}

				�IKTI:
				X ctor E ctor
				Y ctor
				Z ctor
				D ctor
				E ctor
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
RTTI(RUN TIME TYPE INFORMATION)

	�al��ma zaman�nda t�r bilgisi elde etmek i�in kullan�l�r program �al���rken bir nesnenin ger�ek t�r�n� ��renmemizi sa�lar

	void car_game(Car* p)
	{
		if(p mercedes nesnesini g�steriyor ise onu mercedes olarak kullan)
	}

	dynamic_cast operat�r�: Polimorfik s�n�flar aras�nda g�venli t�r d�n���m� yapar run time'da DOWN CASTING'IN g�venli yap�l�p yap�lmad���n� bilgisini verir
		hedef t�r�
			a)pointer t�r�
			b)referans t�r�
			c)void* t�r�(az kullan�lan senaryo)

		class Base{
			public:
				virtual void foo(){}
		};

		class Der : public Base{

		};

		int main()
		{
			Der myder;
			Base* baseptr = &myder;

			Der* der_ptr = dynamic_cast<Der*>(baseptr); // operand olan baseptr ifadesi polimorfik bir t�r olmaas� gerekiyor e�er d�n���m i�lemi ba�ar�s�z olursa nullptr de�eri �retilecek


			if (Der* der_ptr = dynamic_cast<Der*>(baseptr)) // scope leakge olmamas� i�in if with initializer kullan�yoruz
			{
				// program�n ak��� buraya girerse nesnesin art�k Der nesnesi oldu�u anla��l�r
			}
		}

	D�KKAT:s�n�f hiyerar�isi olan s�n�flar i�in static_cast operat�r�yle de d�n���m yap�labilir ama bu saptama run time'a y�neik bir saptama de�il compile time'a y�nelik bir saptama
		
		class A {};
		class B : public A {};
		class C : public A {};

		int main()
		{
			B bx;

			A* ptr = &bx;

			C* cptr = static_cast<C*>(ptr); // kod legal ama ptr'nin g�sterdi�i nesnesin bir C s�n�f�n�n nesnesi oldu�unun garantisi yok static_cast ile yapt���m�z d�n���m�n
			derleme zaman�nda ge�erli olmas� ayn� s�n�f hiyerar�isinde olan s�n�flar aras�nda ge�erli ama operand olan pointer hedef t�r� g�steriyor mu g�stermiyor mu sorusunun cevab�n�
			run time'da vermiyor
		}

		�RNEK:

		int main()
		{
			for (int i = 0; i < 10; ++i)
			{
				Car* carptr = create_random_car();

				std::cout << *carptr;

				Volvo* vptr = static_cast<Volvo*>(carptr); // kod legal ama do�ru bir kod de�il buraya gelen t�r Volvo de�ilse �rne�in bir Mercedes ise tan�ms�z davran�� olacak
				vptr->open_sunroof();


				if (Volvo* vp = dynamic_cast<Volvo*>(carptr)) // DOWN CASTING ba�ar�l� olursa Volvo'nun open sunroof fonksiyonu �a��r�lacak e�er VOLVOXC90'�n adresi gelirse VOLVO s�n�f�na 
																 UP CASTING yap�lacak
				{
					vp->open_sunroof();

					e�er hedef t�r� referans t�r� olarak se�ersek null referans diye bir �ey olmad��� i�in e�er d�n���m ba�ar�s�z olursa bad_cast t�r�nden exception f�rlat�yor
				}

				delete carptr;
		}

	SIDE CAST
		
		Ayn� taban s�n�fa sahip olan s�n�f aras�nda yap�lan d�n���m

		class Base{
			virtual void foo(){}
		};

		class Xder: public virtual Base{};

		class Yder: public virtual Base{};

		class Mder: public Xder,public Yder{};

		int main()
		{
			Mder mder;

			Xder& dx = mder;

			Mder& r_mder = dynamic_cast<Mder&>(dx); // downcast

			Yder& ry = dynamic_cast<Yder&>(dx); // sidecast

		}

		Xder -> Mder (downcast)

		Mder -> Yder (upcast)

		Bu zincirli t�r d�n���m�ne side cast denir ��nk� Xder ve Yder aras�nda do�rudan bir ili�ki yok, ama ortak bir alt s�n�flar� (Mder) var.

	VOID POINTER
		dynamic_cast<void*> ile nesnenin ger�ek adresini ��renebiliriz

		Bu genellikle:

			1)Nesne kimli�ini (identity) saklamak

			2)Serile�tirme (serialization)

			3)Do�rudan bellekteki yerle ilgili i�lemler gibi �zel durumlar i�in kullan�l�r

		class Base{
			public:
				virtual void foo(){}
		};

		class Der : public Base {};
		class Erg : public Der {};

		int main()
		{
			Base* baseptr = new Erg; // Erg nesnesinin i�inde Der var Der nesnesinin i�inde de bir Base var bu y�zden ge�erli

				taban s�n�f pointer� ile Erg nesnesini g�steriyoruz ama taban s�n�f pointer�n�n de�eri Base* t�r�nden taban s�n�f nesnesini g�steriyor ama biz Erg nesnesinin adresini elde etmek istiyoruz

			void* vptr = dynamic_cast<void*>(baseptr); // run time'da baseptr'nin g�sterdi�i Erg nesnesinin adresini elde ediyoruz

			Erg nesnesinin adresiyle baseptr'nin adresi ayn� olmak zorunda de�il baseptr'nin Erg'i g�steriyor olmas� demek baseptr'nin de�erinin fiziksel olarak Erg nesnesinin adresi demek de�il
			��nk� Erg'in i�indeki Base'in adresini tutuyor
		}

	type_info(typeid operat�r�): Nesnenin t�r bilgisine eri�im sa�lar
		
		typeid operat�r�yle olu�turulan ifade 2 �ekilde olu�turabiliyor
			1)type(int) operaand olarak t�r alabiliriz
			2)type(10) operaand olarak ifade alabiliriz

		dynamic_cast operat�r�nden fark� operand� olan ifadenini yada t�r�n polimorfik olma mecburiyeti yok

		typeid ifadesi ile olu�turulan ifade std::type_info s�n�f�  t�r�nden const&

			const std:type_info& r = typeid(10);

		class Myclass{};
		int main()
		{
			std::boolalpha(std::cout);

			std::cout<<typeid(Myclass).name()<<'\n'; // burada gelen yaz� standart de�il 
			std::cout << (typeid(m1) == typeid(m2)); // true
			std::cout << (typeid(m1) != typeid(10)); // true
		}

		�IKTI: class Myclass
				true true

	�RNEK:
		class Base{
			public:
				
		};

		class Der : public Base{};

		int main()
		{
			Der myder;
			Base* baseptr = &myder; // baseptr'nin g�sterdi�i nese Der s�n�f t�r�nden olmas�na ra�men Base ��kt�s� al�n�yor

			std::cout<<typeid(*baseptr).name()<<'\n';
		}
		
		�IKTI: class Base

		e�er Base'de polimorfik bir t�r olsayd� run time'a ili�kin t�r olacakt�  

			class Base{
				public:
				virtual void foo(){}
			};

			class Der : public Base{};

			int main()
			{
				Der myder;
				Base* baseptr = &myder; 

				std::cout<<typeid(*baseptr).name()<<'\n';
			}
		
			�IKTI: class Der

		�RNEK:
			class Base{
				public:
				virtual void foo(){}
			};

			class Der : public Base{};

			int main()
			{
				Der myder;
				Base* baseptr = &myder;

				if(typeid(*baseptr) == typeid(Der)) // run time'da baseptr'nin t�r�n�n Der t�r�nden olup olmad���n� s�n�yoruz 
				{
					
				}
			}
*/