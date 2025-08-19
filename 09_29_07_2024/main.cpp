/*

non-static member functionlarda kalm��t�k
	
	class Myclass
	{
		public:
			void func(int x);
	};
	
	int main()
	{
		Myclass m;
		Myclass* p = &m;

		(*p).func(35);
		p->func(354);
		 
		// iki �ekilde de kullanmak ayn� anlama gelir
	}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
GLOBAL FUNCTIONLAR �LE MEMBER FUNCTIONLAR ARASINDAKI FARKLILIKLAR
	
	1)member fonksiyonlara nesne adresini yollam�yoruz nokta operat�r�n�n yada ok operat�r�n�n sol operand� olan nesnesnin adresini derleyici kendisi ge�iyor
		class Myclass
		{
			public:
				void func(int x);
		}
	
		void globalFunc(Myclass* p,int x;)

		int main()
		{
			Myclass m;
			m.func(24);

			// e�er pointer ile �a��rmak istersek 
			   Myclass* p = &m;

			   (*p).func(35);
			   p->func(354) // her iki kullan�mda ayn� anlama geliyor

			// global fonksiyona nesnenin adresini ge�mek zorunday�z
				globalFunc(&m,24);
		}

	2)eri�im kontrol� fark�(global fonksiyonlar s�n�f�n private b�l�m�ne eri�emez)

		class Myclass
		{
			private:
				int mx,my;
		}

		void globalFunc(Myclass* p,int x)
		{
			auto a = p->mx; // access controle tak�l�r
		}

		Myclass s�n�f� i�inde func fonksiyonu olsayd� class scopeta oldu�u i�in private memverlarada eri�ebilecekti

	3)scope farkl�l���
		class Myclass
		{
			public:
				void func(int x); // class scopeta
			private:
				int mx,my;
		}

		void globalFunc(Myclass* p,int x) // namespace scopeta
		{}
	
		int main()
		{
			Myclass::func(235); // burda nesnenin adresi ile �a��r�lmas� gerekiyor burda context kontrole tak�ld� static member function olursa ge�erli olurdu bu konu i�lenecek 
		}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CLASSLARIN MEMBER FUNCTIONLARININ TANIMI NASIL YAPILIR

2 tane alternatif durum var
	1).cpp dosyas�nda fonksiyonun normal tan�m�n� yapmak
		
		Myclass.h
			class Myclass
			{
				public:
					void set(int x,int y);
				private:
					int mx;int my;
			};
		
		Myclass.cpp
			void Myclass::set(int x,int y)
			{
				mx = x;
				my = y;
			}
	2)header fileda yapabiliriz ama implicit inline olmu� olur ODR �i�nenmemi� olur
			class Myclass
			{
				public:
					void set(int x,int y),
					{
						mx = x;
						my = y;
					}
				private:
					int mx;int my;
			}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------		
GLOBAL FUNCTIONLARADA VE MEMBER FUNCTIONLARADA NAME LOOKUP KURALLARI FARKLI
	Myclass.h
		class Myclass
		{
			public:
				void set(int x,int y);
			private:
				int mx;int my; // non-static data member
		};

	Myclass.cpp
		void Myclass::set(int x,int y)
		{
			// bu fonksiyon bir global function olsayd� bir ismi ifade bi�iminde kullan�d��m�zda isim �nce 
				1)block i�inde aran�r
				2)onu kapsayan block i�inde aran�r(enclosing block) 
				3)onuda bulamazsa namespace scopeta aran�r

			// fakat class memberlar i�in isim arama
				1)block i�inde aray�p bulamazsa
				2)class scopeta arar 

				mx = x; // block scopeta class'�n i�indeki mx de�i�kenini g�lgeyen ba�ka bir mx de�i�keni yoksa class scopeta ismi arar ve bulur
				derleyici burda mx'in non-static data member oldu�unu anlar
				my = y;
		}

		int main()
		{
			Myclass m;

			m.set(3,5); // buradaki 3 ve 5 de�eri m nesnesine ait olan mx ve my de�i�kenlerinin de�erleri
			
			3 tane farkl� nesneler olsayd� ��phesiz her �a�r�da set fonksiyonunun gizli parametresine aktar�lan adres farkl� adres olucakt� her nesne i�in farkl� de�erler biribirnden ba��ms�z olmu� olacakt�

			Myclass m1,m2,m3;

			m1.set(3,5);
			m2.set(4,7);
			m3.set(6,9);

		}

SORU: S�n�ftan global bir nesne olsa member function i�inde o global nesneden private elemanlara eri�ebilir miyiz?
		Myclass.cpp
			Myclass g;

			void Myclass::set(int x,int y)
			{
				g.mx = 5; // sentaks hatas� de�il s�n�f�n member functionu s�n�f�n private b�l�m�ne eri�ebilir derken bu fonksiyon hangi nesne i�in �a��r�l�rsa
				o nesnesnin private eleman�na de�il her ne �ekilde olursa olsun private b�l�m�ne eri�ebiliyor 
			}

			void Myclass::foo(Myclass& r)
			{
				r.mx = r.my;

				Myclass x;
				x.my = g.my;

				mx = my;

				// hi� biri sentaks hatas� de�il sadece data memberlar i�in de�il b�t�n memberlar i�in ge�erli private olan member function olsayd� yine eri�imide herhangi bir problem olmayacakt� veya nested type
			}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HOCA NAME HIDING KONUSUNA DE��N�YOR 
	void Myclass::set(int x,int y)
	{
		// block scopeta ki isimler class scopeta ki isimleri maskeleyebilir
			int mx = 45;
			mx // de�i�kenini arad���nda block scopeta bulur e�er buna ra�men s�n�fn eleman�na eri�mek istiyorsak 2 yolu var
		
			1)s�n�f ismiyle nitelemek
				Myclass::mx; // direkt s�n�f i�inde aran�r
			2)s�n�ftan nesne olu�turmak
				Myclass myclass;
				myclass.mx;
	}

	class scopetaki isimde namespaceteki ismi maskeleyebilir
		
		int mx = 56;

		void Myclass::set(int x,int y)
		{
			mx = x; // atama class scopetaki mx'e yap�lm�� olacak
			::mx = x; // global mx'e eri�mek i�in unary scope resolutin operat�r�yle eri�ebiliriz
		}

hem namespace scopeta hem class scope hemde block scopeta mx olsayd� nas�l ay�rt edecektik
		
		class Myclass
		{
			private:
				int mx;
		};

		int mx = 56;

		void Myclass::set(int x,int y)
		{
			int mx = 10;

			Myclass::mx // class scopeta ki mx
			mx // block scopetaki mx
			::mx // namespace scopeta ki mx
		}

SORU:bar fonksiyonu hangi nesnenin adresiyle �a�r�lm��sa foo fonksiyonuda bar fonksiyonunun i�inde ki ayn� nesne adresiyle nas�l �a��r�l�r
	void foo(Myclass *p)
	{};

	void bar(Myclass* p)
	{
		foo(p);
	}

	non-static member functionlarda birbirini �a��rmas� durumunda derleyici zaten isim aramayla o fonksiyonun non-static member function oldu�unu anlayacak
		
		class Myclass{
			public:
				void foo(int x,int y);
				void bar(int x);
			private:
				int mx; int my;
		};

		void Myclass::foo(int x,int y)
		{
			bar(x);
			bar(y);

			// non-static member fonksyiyonlar�n gizli nir parametre de�i�keni oldu�u i�in foo(Myclass* p,int x,int y) asl�nda derleyici burda bar fonksiyonuna myclass nesnesinin t�r�nden adres zaten yolluyor
				bar(p,x); 
				bar(p,y); // her iki �a�r�adada ayn� adresle de�erleri �a��r�yoruz
		}

		int main()
		{
			
			Myclass x;
			x.Myclass::bar(25); // bu fonksiyonu b�ylede �a��r�labiliriz ama burda nesneyle �a��rd���m�z i�in Myclass:: olarak nitelemeye gerek yok
		}

 SORU:
	1)
		Myclass
		{
			public:
				void bar(int x);
				void bar(double,double);
		};

		void bar(double);

		void Myclass::bar(int x)
		{
			bar(2.3); // doubledan int t�r�ne d�n���m olur int parametreli member function �a��r�l�r burda narrowing conversion s�z konusudur
		}

	2)
	Myclass
	{
		public:
			void bar(double);
		private:
			void bar(int x);
	};

	int main()
	{
		Myclass m;
		m.bar(12); // isim bulunur ama access contrele tak�l�r sentaks hatas� 

		// burda yanl�� anlam��sak double parametreli fonksiyonun �a��r�lmas�n� bekleyebiliriz ama asl�nda burda isim bulunur ve isim arama sonra erer int parametreli fonksiyon se�ilir ama private oldu�u
			i�in access controle tak�lacak
		}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SINIFIN �YE FONKSIYONLARI OLDU�U ZAMAN BIR FONKSIYONUN SET YADA GET FONKSIYONU OLDU�UNU NERDEN BILECE�IZ?

	class Myclass
	{
		public:
			void foo()const; // b�yle functionlara const member function deniliyor
			void bar(); // non-const member function yani non-static non-const member function deniliyor :D
	}

	s�n�fa bir interface olu�utururken �u soruyu sormam�z gerekiyor s�n�fa non-static member function m� tan�mlayaca��z bu fonksiyon s�n�f nesnesini de�i�tirmeye y�nelik mi? cevap evet ise kesinlikle 
	non-static non-const member function olacak ama s�n�f nesnesini de�i�tirmeye y�nelik de�ilse s�n�f nesnesinin de�erini kullanmaya y�nelikse mutlaka const member function yapmam�z gerekir bu �ok �nemli 

	SORU:
		const �ye olup olmad���n� d���n�yoruz karar� �una g�re vermeliyiz s�n�f�n nos-static veri elemanlar�ndam birini de�i�tiriyorsa -> non-const de�i�tirmiyorsa -> const member function olmal� saptamas� kesinlikle YANLI�
		NEDEN?:hoca bu tarz d���nenlere C tarz� d���nenler diyor 
				non-static fonksiyonun const member function olup olmamas� s�n�f nesnesinin veri elemanlar�yla do�rudan ilgisi yoktur
				s�n�f nesnesinin problem domaininde ki anlam�yla ilgisi vard�r �nemli olan nesnesinin stateinin de�i�ip de�i�memesi

		class Fighter
		{
			public:
				std::string cry_name(); // bu const �ye foknsiyon olmal� m� olmamal� m� ?
										burda d���nece�imiz �ey s�n�f nesnesinin problem domaninideki anlam�				
		}

		s�n�f�n veri eleman�n�n de�i�itren bir fonksiyon const olabilir mi? EVET 
	
		derleyicinin yapt��� sentaks kontrol� ile bizim yazd���m�z kodun semantik olarak ayn� olmak zorunda de�il
		derleyici const member function olmas� durumunda fonksiyonun gizli parametre de�i�kenine const Myclass* parametre de�erini ge�iyor
			class Nec
			{
				public:
					void foo(); // non-static non-const member function -> gizli parametre de�i�keni (Nec*);
					void foo()const; non-static const member function -> gizli parametre de�i�keni (const Nec*);
			};
	
	SORU
		1)
			class Nec
			{
				public:
					void foo(); // void foo/Nec*)
					void bar()const;
					int mx;
			};

			void Nec::foo()
			{
				mx = 5; // ge�erli // p->mx = 5; // gizli parametre ile arka planda olan
			}

			void Nec::bar()const
			{
				mx = 5; // Ge�ersiz // s�n�f�n const �ye fonksiyonlar� s�n�f�n non-static veri elemanlar�n� de�i�tiremezler ��nk� gizli parametre de�i�kenleri const T*
			}
		
		2)foo fonksiyonu i�inde bar fonksiyonunu �a��rmam�z sentaks hatas� m� de�il mi?
			void Nec::foo()
			{
				bar(); // hata de�il burda d�n���m T* t�r�nden -> const T* t�r�ne d�n���m
			}

			ama bar fonksiyonu i�inde foo fonksiyonu �a��rmay� denersek bu asl�nda derleyiciyiyi const T* t�r�nden T* t�r�ne d�n���m yapmay� zorluyor sentaks hatas�
			
			void Nec::bar()const
			{
				foo(); // sentaks hatas� burda const olmayan bir nesne �a��r�l�yor
				
				const member functionlar const olmayan member functionlar�n� �a��ramaz
				const �ye functionlar s�n�f�n data memberlar�n� de�i�tiremez
			}
		
		3)kod legal mi de�il mi
			class Nec
			{
				public:
					void bar()const;
				private:
					int *mp;
				};

				int g{}; // namespace scope

				void Nec::bar()const
				{
					*mp = 5; // buras� sentaks ile semanti�in ayr�ld��� yer mp'nin g�sterdi�i nesnesinin de�erini de�i�tirmek sentaks hatas� de�il

					mp = &g; // e�er mp'ye farkl� bir adres atasayd�k bu sefer sentaks hatas� olurdu
				}
			}

		4)
			class Person
			{
				public:
					std::string get_name() const;
				private:
					int m_debug_count = 0;
			
					her �ye fonksiyon �a��r�ld���nda m_debug_count de�erini bir artt�r�cak b�ylece herhangi bir noktada bir person nesnesi i�in m_debug_count �n de�erini get etti�imde o s�n�f nesnesi i�in 
					ka� kez �ye fonksiyon �a��r�ld���n� anlayaca��z 
			};

			std::string get_name()const
			{
				++m_debug_count; // sentaks hatas� 

				bu fonksiyonun gizli parametresi const Person* low level const bir pointer�n g�sterdi�i yeri de�i�tirmeye �al���yoruz ama semantik olarak bunu de�i�tirmem gerekiyor
				��nk� bu veri elaman�n de�erinin de�i�mesini person nesnesinin problem domainindeki anlam�n� de�i�tirmiyor �rne�in ismi ya�� paras� de�i�miyor burda MUTABLE anahtar kelimesini kullanyoruz
				b�ylelikle derleyiciye diyece�iz ki bu eleman�n s�n�f nesnesinin problem domainindeki g�zlemlenebilir davran���yla do�rudan bir ili�kisi yok normalde const bir member function 
				bu de�eri de�i�tiremez ama ben bu anahtar kelimeyi kulland���mda de�i�tirmeme izin ver derleyiciye bunu s�ylemi� oluyoruz const �ye fonksiyonun bunu de�i�tirmesine izin ver demi� oluyoruz

				bir veri eleman�n� mutable olarak bildirmek s�n�f nesnesinin de�erini de�i�mesiyle alakas� yok yani s�n�f nesnesinin problem domainindeki anlam�yla ilgisi yok demi� oluyoruz 
		
				mutable int m_debug_count

				++m_debug_count; // art�k ge�erli

			}

		BARI� DO�A YAVA� mutable anahtar kelimesinin ba�ka bir kullan�m� var m� diye sordu hoca bu anahtar kelimeninin overloadingleri oldu�unu s�yledi ve
		ilerde �zellikle lambdalarda kar��m�za ��kaca��n� s�yledi
	
		5)
			class Nec
			{
				public:
					void foo();
					void bar()const;
			};

			int main()
			{
				const Nec mynec;

				mynec.foo(); // mynec nesnesi const foo fonksiyonunun gizli parametre de�i�keni Nec* biz ona const bir nesne yollarsak const T* t�r�nden T* t�r�ne d�n���m olmad��� i�in sentaks hatas�
				mynec.bar(); // ge�erli

				const bir nesne i�in s�n�f�n sadece const member functionlar�n� �a��rabiliriz
				non-const member functionlar�n� �a��ramay�z
			}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
THIS KEYWORD
	bir s�n�f�n non-static member function� i�inde kullanabilece�imiz bir keyword

	THIS NERELERDE KULLANILMAZ
		1)global fonksiyon i�inde
		2)s�n�f�n static member functionlar� i�inde

	this'in ge�erli olarak kullan�labilece�i tek durum s�n�f�n non-static member functionunun tan�m�n�n i�inde
		class Myclass
		{
			public:
				void func();
				int x;
		}

		void Myclass::func()
		{
			stc::cout << "this = " << this << '\n'; // this keywordu bu fonksiyon hangi nesne i�in �a��r�l�yorsa o nesnenin adresini kullanm�� oluyoruz

		}

		int main()
		{
			Myclass m,m1;

			std::cout << "&m = " << &m << '\n';
			std::cout << "&m1 = " << &m1 << '\n';

			m.func();
			m1.func();

		}

	her hangi bir nedenle bir fonksiyon hangi nesne i�in �a��r�ld�ysa o nesnenin kendisini kullanmak istiyirosak *this ifadesini kullanaca��z nesnenin kendisi
		this -> nesnenin adresi
		*this -> nesnenin kendisi

	this pointer�n�n olu�turdu�u ifade PR value expression
		fonksiyon i�inde this pointer�n�n de�erini kullanabiliriz ama this pointer�n bir nesneymi� bir L value gibi bir atama yapma giri�imi bulundu�umuzda yada onunn adresini pointer�n kendi adresini
		almay� denersek sentaks hatas� olur

	class Myclass
	{
		public:
			void func();
			void foo();
		private:
			int x;
	};

	void Myclass::func()
	{
		x = 5;
		this->x = 5; // b�ylede yazabiliriz dimi? evet ama bu sorunun cevab�n�n evet olmas� ba�ka bu kodlar� b�yle yazmam�z ba�ka
		this->foo();

		this keywordunu s�rekli kullanmak gereksiz kod kalabal��� ve kirli bir g�r�n�m sa�l�yor this keywordunun varl�k nedeni bu anlamda kullanmak de�il

		bir data member ile parametre de�i�keni ayn� isme aitse isimlendirmeyi daha mant�kl� yapmam�z gerekiyor func fonksiyonunun int x parametresi olsayd� x = x yapmak self assigment olacakt� 
		bu sefer this keywordu yada scope resolution operat�r�n� kullanmam�z gerekecekti
			Myclas::x = x;
			this->x = x;
		ama b�yle kullan�lmamas� gerekiyor burada isimlendirme problemleri var data memberlara isim verirken di�er isimlerden ay�rt edici isimlendirme kullanmam�z gerekiyor 

		s�n�fn data memberlar�n�n ba��na m �n ekiyle ba�latabiliriz yada sonuna _ koyabiliriz 
			mx yada x_ b�yle bir durumda this keywordunu kullanmakta gerekmeyecekti
				mx = x;

	THIS KEYWORDUNUN MANTI�I
		
		1.Senaryo
			bir global fonksiyonumuz olsun
			void fg1(Myclass*);
			void fg2(Myclass&);

			s�n�f�n �ye fonksiyonu i�inde func hangi nesne i�in �a��r�lm��sa o nesnenin adresiyle global fg1 fonksiyonuna �a�r� yapmam�z gerekiyorsa yada
			func hangi nesne i�in �a��r�lm��sa ayn� nesneyi referans semanti�i ile fg2 fonksiyonuna arg�man olarak g�ndermemiz gerekiyorsa bunu nas�l yapaca��z?
			
			void Myclass::func(int x)
			{
				fg1(this); // Myclass*
				fg2(*this); // Myclass&
			}

			int main()
			{
				Myclass m,m1;

				m.func();
				m1.func();

			}
		2.Senaryo
			s�n�flar�n baz� �ye fonksiyonlar� yapt�klar� i�in neticesinde hangi nesne i�in �a��r�lm��larsa o nesnenin adresini ysda o nesnenini kendisini d�nd�r�yorlar
				class Myclass
				{
					public:
						Myclass* foo(); // bu fonksiyon hangi nesne i�in �a��r�lm��sa onun adresi
						// Myclass& foobar(); // daha basit ve s�k kullan�lan senaryo referans
				};

				Myclass* Myclas::foo()
				{
					// fonksiyon en son yapt��� i� neticesinde this pointer� d�nd�recek
					return this; // hangi nesne ile �a��r�lm��sa o nesnenin adresini d�nd�r�yor
				}

				Myclass& Myclass::bar()
				{
					// code
					return *this; // hangi nesne ile �a��r�lm��sa o nesneninn kendisini d�nd�r�yor
				}

				int main()
				{
					Myclass m;
					m.foo(); // fonksiyonun geri d�n�� de�eri m nesnesinin adresi olacak 
					m.bar(); // fonksiyonun geri d�n�� de�eri m nesneninin kendisi olacak
				}

		*this nesnenin kendisi oldu�u i�in L value expressiond�r ve atama yapabiliriz
			void Myvlass::foo()
			{
				*this =
			}

		e�er s�n�f�n �ye fonksiyonu const �ye fonksiyonsa this pointer� low level const pointer
			class Myclass
			{
				public:
					void foo()const
					{
						mx = 10;
						this->mx = 10; // her ikiside sentaks hatas�
					}
				private:
					int mx;
			};

			en �ok kar��t�r�lan yerlerden biri fonksiyonun geri d�n�� de�eri s�n�f nesnesinin adresi olan const member functionlar
				Myclass* foo()const
				{
					return this; // s�n�f�n member functionu const member funct�on oldu�u i�in this pointer�da low level const pointer const T* t�r�nden T* t�r�ne d�n���m olmad��� i�in sentaks hatas� verecek
					bu y�zden foo fonksiyonununda geri d�n�� de�eri const Myclass* olmas� gerekiyor(ayn� durum referanslardada ge�erli) 
				}

			const overloading member functionlar i�inde ge�erli
				class Myclass
				{
					public:
						void foo(); // const olmayan nesneler i�in bu fonksiyon �al��acak
						void foo()const; // const olan nesneler i�in bu fonksiyon �al��acak
				};

				int main()
				{
					Myclass m;
					m.foo(); // const olmayan foo �a��r�lacak

					const Myclass m1;
					m1.foo(); // const olan foo fonksiyonu �a��r�lacak
				}

		CHAINING TERIMI
			class Myclass
			{
			public:
				Myclass& foo();
				Myclass& bar();
				Myclass& baz();
			};

			Myclass& Myclass::foo()
			{
				return *this;
			}
			Myclass& Myclass::bar()
			{
				return *this;
			}
			Myclass& Myclass::baz()
			{
				return *this;
			}

			int main()
			{
				Myclass m;
				m.foo().bar().baz();

				m.foo();
				m.bar();
				m.baz(); // �eklindede �a��rabilirdik bir fark yok ama baz� durumlarda bu chainingten faydalanmam�z bize avantaj sa�layabiliyor
			}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
HOCA INLINE FONKS�YONLARA TEKRAR DE�INIYOR
	kar���t�r�lan bir yer daha var s�n�f�n �ye fonksiyonunun s�n�f i�inde tan�mlanmas�yla cpp dosyas�nda tan�mlanmas� ayn� �ey de�ildir

	class Myclass
	{
		public:
		void set(int x)
		{
			mx = x;
		}
		private:
			int mx;
	}

	void Myclass::set(int x)
	{
		mx = x;
	}

	global fonksiyonlarda oldu�u gibi s�n�f�n �ye fonksiyonlar�ndada ODR'� �i�nemememiz gerekiyor ODR'� �i�nemememiz i�in fonksiyonun inline olmas� gerekiyor 
	bir s�n�f�n �ye fonksiyonunu inline yapman�n birden fazla yolu var
		1)fonksiyonun tan�m�n� header dosyas�nda yapmak(en az yap�lan durum)
			myclass.h
			
			class Myclass
			{
				public:
					inline void set(int x);
				
				private:
					int mx;
			}

			inline void Myclass::set(int x)
			{
				mx = x;
			}

		2)fonksiyonun tan�m�n� direkt class definition i�inde yapmak
			class Myclass
			{
				public:
					void set(int x)
					{
						mx = x;
					}

				bir fonksiyonun tan�m�n� class definition i�inde yapmak fonksiyonu �rt�l� olarak inline yap�yor
			};

		SORU SORULDU:s�n�f i�inde bildirimi inline yapsak cpp dosyas�nda tan�m�n� yapsak inline expansion �ans� olabilir mi?
			derleyici fonksiyonun tan�m�n� g�rmedi�i i�in herhangi bir �ekilde inline expansion yapma �ans� do�urmaz
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SINIF NESNELER�N�N HAYATA BA�LAMASI VE HAYATLARININ SONLANMASI
	
	bir s�n�f nesnesinin hayata ba�lamas�n� sa�layan s�n�f nesnesini kullan�labilir bir varl�k haline getiren s�n�f�n bir �ye fonksiyonu fakat b�yle �ye fonksiyonlar i�in �zel bir terim kullan�yor
		constructor
	
	bir s�n�f nesnesinin hayat� bitti�inde s�n�f�n �ye fonksiyonuna yap�lan �a�r�n�n ad�
		destructor
	
	bu fonksiyonlara ili�kin kurallar
		1)constructor ve destructor s�n�f�n member functionu
		2)global fonksiyon olamazlar
		3)s�n�f�n statik member functionu olam�yorlar
		4)s�n�f�n non-static non-const member funct�onu olmak zorundalar
		
	CONSTRUCTOR
		1)s�n�f�n constructor�n�n ismi s�n�f�n ismiyle ayn� olmak zorunda
			class Myclass
			{
				public:
					Myclass();
			}
		2)constructor�n geri d�n�� de�eri yok

		3)constructor'�n const member function olmas� sentaks hatas�
			Myclass()const;

		4)overload edilebilirler
			Myclass();
			Myclass(int);
			Myclass(double);
			Myclass(int,int); // function overload resolution burdada ge�erli olacak

		5)s�n�f�n constructor� private ve protected olabilir ama clientlar taraf�ndan �a��r�lmas� sentaks hatas�

		6)class definition i�inde de tan�m� yap�labilir(�rt�l� olarak inline olurlar)

*/