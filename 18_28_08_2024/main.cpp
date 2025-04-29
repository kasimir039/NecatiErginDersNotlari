/*

SINIFLARIN STATIC MEMBERLARINDAN DEVAM

	ge�en ders anlat�nlar tekrar edildi

	s�n�f�n ctorunun private olmas� 
	
		class Nec
		{
			private:
				Nec(int x){}
			public:
				static void foo()
				{
					Nec x(10); // baz� �r�nt�lerde s�n�f�n ctorlar�n� private yap�p ctormu� gibi member functionlar olu�turabiliriz

				}
		}

	NAMED CTOR IDIOM(�S�MLEND�R�LM�� CTOR �D�YOMU) 
		asl�nda ctor de�il ama ctormu� gibi davranan static member functionlard�r
		
		1)ctorlar�n client kodlar taraf�ndan do�rudan �a��r�lmas�n� istemiyoruz o y�zden private yap�yoruz ama s�n�f�n static member functionlar� s�n�f�n member functionu oldu�u i�in
		onlar�n private ctora eri�mesi bir sentaks hatas� de�il
		
		2)named ctor idiomu kullanma sebebimiz
			a)nesneyi olu�turman�n tek bir noktadan yap�lmas�
			b)nesneyi belirli bir bi�imde olu�turulmas�n�n mecburi hale getirmesi i�inde kullan�labilir
				class Complex{
					private:
						//Complex(double r, double i);
						//Complex(double angle, double distance,int dummy); // dummy parametre olmasayd� ikiside sentaks hatas� ��nk� s�n�flar�n member functionlar� re-definition edilemez o y�zden 
						imza farkl�l��� olarak dummy parametresini ekleyip overloading mekanizmas�na �evirebiliriz

					public:

						static Complex create_cartesian(double r,double i)
						{
							return Complex(r,i);
						}
						static Complex create_polar(double angle,double distance)
						{
							return Complex(angle,distance,0);
						}
				};
			c)belirli bir nedenle s�n�f t�r�nden nesnelerin sadece dinamik olarak olu�turulmas�n� istiyorsak
				class DynamicOnly{
					private:
						DynamicOnly(){}
					
					public:
						static DynamicOnly* create_object()
						{
							return new DynamicOlny;
						}
				};

				int main()
				{
					auto p = DynamicOnly::create_object();
				}

	�RNEK:ka� tane nesne var ve ne kadar nesne hayatta
		#include <iostream>
		class Nec {
		public:
			Nec()
			{
				++ms_live_count;
				++ms_lived_count;
			}

			~Nec()
			{
				--ms_live_count;
			}

			static int get_live_count() { return ms_live_count; }
			static int get_lived_count() { return ms_lived_count; }

		private:
			inline static int ms_live_count{};
			inline static int ms_lived_count{};// sadece static anahtar kelimesiyle bildirseydik ve cpp dosyas�nda tan�m�n� yapsayd�k zero initialize edilecekti ama cpp
						tan�m�n� yapmasayd�k bu sadece bildirim oldu�u i�in link zaman�nda hata verecekti ama �imdi inline olarak tan�mlad���m�z i�in zero initialize edilecek
		};

		int main()
		{
			Nec n1, n2, n3;

			std::cout << Nec::get_live_count() << '\n'; // 3 ��kt�s�

			Nec n4;
			std::cout << Nec::get_live_count() << '\n'; // 4 ��kt�s�

		}

	�RNEK:bir s�n�f t�r�nden nesnelerin birbiriyle hayatta olan di�er nesnelerle ileti�imini sa�lamak
		class Fighter {
		public:
			Fighter() = default;
			Fighter(const std::string& name) : m_name(name)
			{
				msvec.push_back(this);
			}
			~Fighter()
			{
				std::erase(msvec, this);
			}

			Fighter(const Fighter&) = delete;
			Fighter& operator=(const Fighter&) = delete;

			void ask_for_help()
			{
				std::cout << "ben savasci " << m_name << '\n';
				std::cout << "dusman kabile beni oldurecek\n ";

				for (auto p : msvec)
				{
					if (p != this)
					{
						std::cout << p->m_name<<' ';
					}
				}
				std::cout << "\n yetisin yardim edin kosunnnnnn :D";
			}

		private:
			inline static std::vector<Fighter*> msvec;
			std::string m_name;
		};

		int main()
		{
			Fighter f1{ "fatih" };
			Fighter f2{ "oguzhan" };
			Fighter f2{ "rasul" };

			auto fp1 = new Fighter("cagri");

			fp1->ask_for_help();

			auto fp2 = new Fighter("necati");

			delete fp2;

			fp1->ask_for_help(); 

		}

SINGLETON
	bir s�n�f t�r�nden tek bir nesne olacak ve o nesneye global bir eri�im s�z konusu olacak 

		class Singleton{
			public:
				Singleton(const Singleton&) = delete;
				Singleton& operator=(const Singleton&) = delete;

				static Singleton* get_instance()
				{
					if(!mp)
						mp = new Singleton;

					return mp;
				}

				void foo();
				void bar();
				void baz();

			private:
				Singleton();
				inline static Singleton* mp{};
			};

		int main()
		{
			Singleton::get_instance()->foo();
			Singleton::get_instance()->bar();
			Singleton::get_instance()->baz();

			Singleton* p1 = Singleton::get_instance();

			Singleton* p2 = Singleton::get_instance();
		}

	MAYERS SINGLETON
		static Singleton& get_instance()
		{
			static Singleton instance

			return instance;

			1)static yerel nesneler i�in ctor bu fonksiyon i�in ilk kez �a��r�ld���nda �a��r�l�yor
			2)static yerel de�i�kenlerin initializationu thread safe bir senkranizasyon olu�turmam�z gerekmiyor

		}
		void foo();
		void bar();
		void baz();
	private:
		Singleton();
	};

	int main()
	{
		Singleton::get_instance.foo();
	}
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
NAMESPACE(�S�M ALANLARI)
	  namespace nec{

	  } // burada el al��kanl��� olabilir ama noktal� virg�l yok 
	
	namespaceler global namespacetelerdir

	1)isim alanlar� local d�zeyde olu�turulamaz
		int main()
		{
			namespace nec{ // sentaks hatas�

			}
		}
	
	2)bir namespace i�indeki namespaceten bahsetti�imiz zaman kullan�lan terim NESTED NAMESPACE
		namespace nec{
			namespace erg{

			} 
		}

	3)bir namespace'in ismi olmas�na gerek yok ama bu bir �zel durum buna UNNAMED NAMESPACE deniliyor
		namespace { }

	4)namespaceler isim �ak��malar�n� �nl�yor
		int x = 5;

		int x = 7; // ayr� namespacelere al�rsak her hangi bir sentaks hatas� olmaz

		namespace nec{
			int x = 5;

		}

		namespace erg{
			int x = 7;
		}

	5)global namespace alan�nda yap�lan her tan�mlamay� namespace i�indede yapabiliriz
		namespace nec{
			void foo();

			class Myclass{};
		}	

	6)namespace bir scope 
		SORU:function overloading olur mu? HAYIR ��nk� scopelar� farkl�
		
		namespace nec{
			void foo(int);
		}

		namespace erg{
			void foo(double);
		}

		namespace nec{
			void foo(int);

			namespace erg{
				void foo(double); // yine function overloading olmaz farkl� scopetalar
			}
		}

	7)namespace i�indeki bir ismi isim aramayla buldurmak i�in scope resolution operat�r� kullan�l�yor
		namespace nec{
			int x;
		}

		int main()
		{
			nec::x; // derleyiciye burda x ismini nec namespace'i i�inde arayacaks�n talimat�n� veriyoruz
		}
	
	8)namespaceler k�m�latif bir yap�ya sahip
		namespace nec{
			int x = 5;
		}

		namespace nec{
			int y = 5;
		}

		namespace nec{
			int z = 5;
		}

		e�er derleyici bir namespace definitionla kar��la�t�ktan sonra ayn� definition ile yine kar��la��rsa bunu ayn� namespace olarak kabul eder
		
		namespace nec{
			int x = 5;
			int y = 15;
			int z = 7; // kodun bu �ekilde derleyiciye sunulmasas�yla �stteki gibi sunulmas� aras�nda bir fark yok
		}

		neden b�yle bir olanak sa�lanm��? HEADER FILE'LAR ���N
			�rne�in vector ba�l�k dosyas�n� include etti�imizde std namespace alan�ndaki ��elerde geliyor
			list ba�l�k dosyas�n� include etti�imizde ordakilerde geliyor bunu sa�layan bu k�m�latif yap�

		SORU:sentaks hatas� m� de�il mi? SENTAKS HATASI AYNI NAMESAPCE ���NDELER
			namespace nec{
				int x;
			}

			namespace nec{
				void x(int);
			}

	9)C++17 ile nested namespaceler bir defada tan�mlanabiliyor
		namespace nec{
			namespace erg{
				namespace proj{
					double x = 5.4
			}

			}

		}

		namespace nec::erg::proj{ // bu tan�m derleyiciye nec'in bir namespace oldu�unu ama erg'in nec namespace'i i�inde bir nested namespace oldu�unu proj'unda erg namespace'i 
									i�inde bir nested namespace oldu�unu anlat�yor
			double x = 5.4;
		} 

		k�m�latif olma durumu burdada ge�erli
			namespace nec{
				int a = 6;
			}

			namespace nec::erg{
				int b = 7;
			}

				
			int main()
			{
				nec::a++;

				nec::foo();

				nec::erg::b++;
			}

	SORU:nested namespace i�inde onu i�ine alan enclosing bracete ki namespaceteki isimlere eri�ebilir miyiz? EVET
		
		namespace nec{
			int x = 5;
				namespace erg{
					void foo(int a)
					{
						x++; // 1)isim �nce block i�inde aranacak
								2)erg namespace'i i�inde aranacak orda bulunamazsa nested namespace i�inde aranacak
					}
				}
		}

USING KEYWORD
	bir ismi nitelemeden ismin yinede namespace i�erisinde aranmas�n� sa�layan ara�lar var
		1)using decleration
			namespace nec{
				int x;
			}

			int main()
			{
				using nec::x; // bu bir decleration bunun bir bildiriminin olmas� bununda bir scope'unun olmas� demek
				�rne�in block i�inde bildirmekle global isim alan�nda bildirmemiz aras�nda fark var using bildirimi ile tan�t�lan isim
				bildiriminin oldu�u scope'a enjekte edilir yani adeta o scopeta tan�mlanm�� gibi etki yapar
				
				x = 10; // using bildiriminin g�r�l�r oldu�u yerlderde bu ismi kulland��m�z zaman derleyici isim aramayla using nec::x bildirimini g�r�cek
				ve bu ismin nec namespace'inde oldu�unu anlayacak
			}
			
			e�er bu bildirim global isim alan�nda yap�lsayd� hepsinde g�r�n�r olurdu
				
				void foo(){
					x = 5;
				}

				void bar(){
					x = 7;
				}

			�RNEK:
				namespace nec{
					int x;
				}

				namespace erg{
					using nec::x; // x ismi erg namespace'ine enjekte edilir
				}

				int main()
				{
					erg::x; // bu isim direkt erg namespace'indeymi� gibi kullan�labilir
				}
		
		D��ER KONULAR SONRAK� DERSLERDE G�R�LECEK

		2)using namespace directive
		3)ADL
		4)C++17 ve sonras� i�in inline namespace(sonra g�r�lecek)
*/ 