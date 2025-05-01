/*
 
namespace konusundan devam ediyoruz ge�en dersin tekrar� yap�ld�

hoca cppreference.com'dan �rnek veriyor
	void f();
	
	namespace A{
		void g();
	}

	namespace X{
		using ::f; // global f is now visible as ::X::f
		using A::g; // A::g is now visible as ::X::g
	}

	void h(){
		X::f(); // calls ::f 
		X::g(); // calls A::g
	}


	2.�RNEK
		namespace nec{
			void foo()
			{
				std::cout<<"nec::foo()\n";
			}
		}

		namespace erg{
			using nec::foo;
		}

		int main()
		{
			erg::foo(); // foo sanki erg i�inde tan�mlanm�� gibi kullanabiliyoruz
		}
	
	3.�RNEK
		namespace foo{
			void foo()
			{
				std::cout<<"foo::f()\n";
			}
		}

		namespace bar{
			using foo::f;
		}

		namespace baz{
			using bar::f;
		}

		int main()
		{
			baz::f(); /
		}

	4.�RNEK
		namespace nec{
			namespace pro{
				void foo()
				{
					std::cout<<"nec::pro::foo()\n;
				}
			}
		}

		namespace erg{
			using nec::pro::foo;
		}

		int main()
		{
			erg::foo();
		}

USING NAMESPACE DIRECTIVE

	using namespace std; �eklinde kullan�l�r

	nesnted namespaceler i�inde kullan�labilir
		using namespace nec::erg::pro;

	burada directive bir namespace ismi i�in yap�l�yor namespace i�indeki ��e i�in de�il �yenin kendisi namespace'se o zaman yazabiliriz
	ve bu namespace'in bildiriminin yap�ld��� scopeta visible olmas� gerekiyor
		
	direktifin kendisi
		a)do�rudan global namespacete
			using namespace std;
		b)bir namespace'in i�inde
			namespace nec{
				using namespace std;
			}
		c)fonksiyon tan�mlamas�nda fonksiyonun blo�u i�inde yada kapsayan bloklar i�inde yap�labilir
			int main()
			{
				using namespace std;
			}

	class definition i�inde do�rudan kullan�lmas� sentaks hatas�
		class Myclass{
			using namespace std;
		}

	ama s�n�f�n bir member function� olsayd� onun i�inde tan�mlamak sentaks hatas� olmayacakt�


	peki bu direktif ne yap�yor?
		bu direktifin kendi scope'u var burada iki tane namespace s�z konusu
		1)direktifin tan�mland��� namespace �rne�in global namespace alan�nda yaz�lmas�
		2)using namespace direktifi ile bildirilen namespace

		using namespace direktifi ile bildirilen namespace i�indeki isimler sanki bu isim alan� i�inde de�ilmi� gibi g�r�n�r durumda oluyorlar
			namespace ali{
				using namespace std; // std namespace'i i�indeki her �ey sanki std'nin i�erisinde de�ilmi� gibi g�r�n�r durumda oluyorlar
				
			}

		bunlar� i�ine alan en dar isim alan� i�inde using direktifinin kullan�ld��� yerde namespace'in isimleri visible duruma geliyor
			
			using namespace std;   // std namespace'i i�indeki isimler sanki global namespacetymi� gibi g�r�l�r durumda
				1)using direktifiiyle bildirin namespace std namespace'i
				2)bildirimin yap�ld��� namespace global namespace 

				ikisini i�ine alan en dar isim alan� global namespace 

		using bildiriminde oldu�u gibi using namespace direktifininde kendi scope'u var
			SORU:using namespace bildirimini global namespacete yapmakla main fonksiyonu i�inde yapmak aras�nda bir fark var m�? EVET VAR
				int main()
				{
					using namespace std; // burada yapt���m�z using namespace bildirimi sayesinde std namespace'i i�indeki isimler sadece main i�inde g�r�n�r olacak
				}

		 using namespace direktifini neden kullanmamal�y�z
			namespacelerin avantajlar�n� tamamen g�z ard� etmi� oluyoruz

			�RNEK:
				namespace nec{
					x = 34;
				}

				namespace erg{
					int x = 567;
				}

				using namespace nec;
				using namespace erg;
				
				hem nec namespace'i i�indeki isimler hemde erg namespace'i i�indeki isimler sanki global namespacete bildirilmi� gibi visible olacak
				
				int main()
				{
					x = 5; // ambiguity

					amac�m�z� isimleri birbirinden gizlemekti ama bunu burada ihlal etmi� oluyoruz using namespace direktifini kulaln�rken �ok dikkatli olmam�z gerekiyor

				}
			
		using bildirimiyle using namespace direktifinin farkl� oldu�u nokta
			using direktifi isimleri using direktifinin bulundu�u scopa enjekte etmiyor
				o isim tek olmak zorunda de�il
				namespace nec{
					int x = 34;
				}

				int main()
				{
					using namespace nec; 
					
					using nec::x // using bildirimi ile yapm�� olsayd�k bu nec namespace'inde bulunan x buraya enjekte edilmi� olacakt� ve sentaks hatas� olacakt�
					
					int x = 56; // burada name hiding olmu� oluyor sentaks hatas� yok

				}

				�RNEK:
					namespace nec{
						int x = 34;
					}

					int x = 56; // sentaks hatas� using namespace direktifi yap�ld��� i�in name hiding oluyor 

					using namespace nec; 

					int main()
					{
						
						x = 45; // ambiguity hatas� globaldeki x zaten g�r�n�r oldu�u i�in namespace nec direktifiyle ne namespace'i i�indeki x ismi de
						global namespace'i i�inde g�r�n�r oluyor
						::x = 45; // global namespaceteki x
						nec::x = 67; // nec namespace'i i�erisindeki x
					}
	
	�RNEK:
		namespace nec{
			void foo();
			int ival{};
				
				struct A{
					static void bar();
				};
		}

		using namespace nec;

		void f1()
		{
			foo();
			++ival;
			A::bar();
		}

		void f2()
		{
			foo();
			++ival;
			A::bar();
		}

		bu �rnekte hi� bir sentaks hatas� yok

		hoca using direktifini ya hi� kullan�lm�yorum yada dar kapsamda kullan�yorum diyor

		using namespace std; // global namespacete oldu�u std namespace'i i�indeki t�m isimler g�r�n�r olacakt�

		int main()
		{
			using namespace std; // sadece main i�inde g�r�n�r

		}

	�RNEK:
		namespace nec{
			namespace erg{
				namespace pro{
					struct A{
						static void foo();
					};

					void bar();
				}
			}
		}

		void f()
		{
			using namesapce nec::erg::pro;

			A::foo();

			bar();
		}

	using direktifi comma seperator list ile kullan�lam�yor
		using namespace nec,erg,pro // sentaks hatas�
	
	�RNEK:
		namespace nec{
			int a;
			int b;
		}

		namespace erg{
			int a;
			int b;
		}

		using namespace nec;
		using namespace erg;

		int main()
		{
			a = 10 // ambigious

			nec::a = 10; // ok
			erg::a = 10; // ok

			b = 20; // ok
			c = 30; // ok
		}

	�RNEK:
		namepace nec{
			int a;
		}

		namespace erg{
			using namespace nec;

			int b;
		}
		
		using namespace erg;

		int main(){
			a = 10; // valid
		}

		using namespace erg direktifi ile erg isim alan� i�erisindeki isimler global isim alan�nda g�r�l�r olur
		b�ylece isim alan�ndaki using namespace nec direktifi de sanki global isim alan�ndaym�� gibi etkiye sahip olur
		bu etki de nec isim alan� i�erisindekilerin global isim alan�na enjekte edilmesine yol a�ar

	�RNEK:
		namespace nec{
			int x = 10;
		}

		namespace erg{
			using namespace nec;

			int y = 20;
		}

		int main()
		{
			std::cout<< erg::x << '\n'; 
		}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ADL(ARGUMENT DEPENDENT LOOKUP) ARG�MANA BA�LI �S�M ARAMA
	bir fonksiyon �a�r�s�nda fonksiyon ismi nitelenmeden kullan�ld���nda fonksiyona g�nderilen arg�manlardan biri bir namespace i�inde
	bildirilen t�re ili�kinse fonksiyon ismi o namespace i�inde de aran�r

	namespace nec{
		class Myclass{};

		void foo();
		void bar(int);
		void baz(Myclass);
	}


	int main()
	{
		nec::Myclass m;

		//foo(); // name lookup hatas�
		//bar(34) // name lookup hatas�
		
		baz(m); // foo ve bar nas�l sentaks hatas� oluyorda baz sentaks hatas� olmuyor? 
	
		fonksiyona g�nderilen arg�man nec namespace'i i�erisinde bildirilen bir t�re il�kin bu y�zden isim arama
		nec namespace'i i�indede yap�l�yor
	}

	ayn� isimde ve parametreik yap�ya sahip olan global bir baz fonksiyonu olsayd�
		void baz(nec::Myclass);

		int main()
		{
			baz(m) // sentaks hatas� olur global namespacete aran�r ama ADL gere�i nec namespace'i i�erisindede aran�r
		}


	SORU:burada �a��r�lan bir fonksiyon var m�?
		std::cout<< "hello word"; global operator << fonksiyonu �a��r�l�yor
		
		member function olsa b�yle �a��r�lacakt�
			std::cout.operator<<("hello world"); // burada �a��r�lan fonksiyon parametresi void* olan fonksiyon
			hello world yaz�s�n�n tutuldu�u dizinin adresini yazd�r�yor

			operator<<(std::cout,"hello world"); // burada �a��r�lan global operator fonksiyonu

			std::cout<<'A'; // burada �a��r�lan fonksiyon global operator fonksiyonu
			std::cout<operator<<('A'); // burada �a��r�lan fonksiyon int parametreli member fonksiyon

			peki burada nitelenmi� isim kullanmamam�za ra�men nas�l sentaks hatas� olmuyot?
				operator<<(std::cout,hello); // ��nk� fonksiyonun birinci parametresine g�nderilen cout std namespace'i i�erisinde bir s�n�fa ili�kin oldu�u i�in
				isim arama std namespace'indede yap�l�yor

	POWER OF ADL
		std::vector<int< ivec {1,5,7,2,3,-5};

		//std::sort(std::begin(ivec),std::end(ivec));


		sort(begin(ivec),end(ivec)); // ortada her hangi bir using bildirimi yok ve bu isimlerin unqualified olarak kullan�lmas�na kar��n her hangi bir sentaks hatas�da yok 
		peki bu nas�l oluyor?

		begin fonksiyonuna g�nderilen arg�man olan ivec std namespace'i i�erisindeki std::vector s�n�f�na ili�kin
		bu isimler nitelenmemi� olmas�na ra�men std namespace'i i�ersinde aranmas�n� sa�layan ADL

		SORU:sort ismide std nsmespace i�erisinde peki nas�l oluyorda nitelenmemi� olmas�na ra�men aran�p bulunuyor?
			begin ve end fonksiyonlar�n�n geri d�n�� de�erleri sayesinde -> std::vector<int>::iterator

		�RNEK:
			namespace nec{
				class Myclass{
					public:
						void foo();
				};
				
				bool is_equal(const Myclass&,const Myclass&);
			}

			int main()
			{
				nec::Myclass m1,m2;

				m1.foo(); // bu ifadeyi yazd���m�zda nas�l ilave bir niteleme yapm�yorsak
				is_equal(m1,m2); // bu fonksiyonu �a��rd���m�z zamanda m1 ve m2 yi arg�man olarak g�nderdi�imizde namespace'i nitelememize gerek kalm�yor
			}

			1)bunlar�n ge�erli olabilmesi i�in funciton call operat�r�n�n kullan�lmas� gerekiyor
			2)function call operat�r�n� overload etmi� s�n�f nesneleri i�in bu ge�erli de�il

		�RNEK:
			namespace nec{
				class Duration{
					public:
						Duration(int hour,int min,int sec);
			};
				void print(const Duration&);
			}

			namespace erg{
				class Duration{
					public:
						Duration(double min);
			};
				void print(const Duration&);
			}

			int main()
			{
				nec::Duration x{2,12,51};
				erg::Duration y{3445,863};

				print(x);
				print(y);
			}

		M�LAKAT SORUSU:
			int main()
			{
				std::cout<< endl; // burda neden sentaks hatas� oluyorda ADL devreye girmiyor?
				
				��nk� endl bir fonksiyon burada �a��r�lan endl fonksiyonu de�il membwer operator<< fonksiyonu 
				
				endl(std::cout); // burda sentaks hatas� yok endl std namespeca'i i�erisnide bir fonkaiyon ve g�nderilen arg�man std namespac'i i�ersinide bildirien
				ostream s�n�f� t�r�nden bir nesne
			}

		�RNEK:
			namespace Enc{
				struct S{};

				void foo(S)
				{
					std::cout<<"Enc::foo(S)\n";
				}

				namespace Nested{
					void foo()
					{
						std::cout<<"Enc::Nested::foo()\n";
					}

					void func()
					{
						S ss;
						foo(ss);
					}
				}
			}
			
			int main()
			{
				Enc::Nested::func();
			}
			
			�IKTI:
			Enc::foo(S)

		�RNEK:
			namespace A{
				class B{};

				void func(std::vector<B>
				{
					std::cout<<"A::func(std::vector<A::B>\n";
				}
			}

			int main()
			{
				std::vector<A::B> x;

				func(x);
			}
		
		�RNEK:
			namespace nec{
				struct X{};

				void func(X) { std::cout<<"Nec::func(X)\n";}
			}

			class Myclass{
				public:
					void func(nec::X) { std::cout<<"Myclass::func(nec::X)\n"; }

					void foo()
					{
						nec::X ax;
						func(ax) // no ADL

						Myclass s�n�f�n�n func fonksiyonu olmaysad� ADL devreye girecekti
					}
			};

			int main()
			{
				Myclass mx;

				mx.foo();
			}

			�IKTI:
			Myclass::func(nec::X)

		�RNEK:
			namespace nec{
				class NA{

				};

				void foo(int);
				void bar(NA);
			}

			namespace erg{
				using EB = nec::NA;
				void func(EB);
			}

			int main()
			{
				erg::EB b;
				func(b) // invalid there is no func in nec (��nk� b nesnesi nec namespace'i i�erisinde ki bir nesneye ili�kin isim arama orada yap�l�yor)
				bar(b); // valid bar found in nec
			}


	bir namespace i�erisinde bildirilen bir fonksiyonu o namespace i�erisinde yada onu i�ine alan enclosing namespace i�erisinde tan�mlayabiliyoruz
		namespace nec{
			namespace erg{
				int foo(int);
			}
		}

		int nec::erg::foo(int x){
			return x * x;
		}

	UNNAMED NAMESPACE
		�nemli bir sentaks �zelli�idir derleyici unnamed namespace olu�turdu�umuzda derleyici ��yle bir kod olu�turuyor
			
			namespace xyz_98{
				int x;
			}
			 
			using namespace xyz_98; // derleyici namespace'in ��k���nda sanki b�yle bir tan�m yap�yormu� gibi b�ylelikle onu kapsayan namespace i�erisinde
			do�rudan g�r�l�r hale geliyor xyz_98 global namespace alan�nda bildirildi�i i�in t�m kaynak dosyada g�r�n�r durumda 

			int main()
			{
				x = 10;
				::x = 5; 
			}

			unnamed namespace kullan�lmas�n�n temel amac� sadece bir kaynak dosyaya ili�kin isimlerin di�er kaynak dosyalardan gizlenmesini sa�lamak
				ali cpp
					namespace { 
						int x;
					}
				veli cpp
					namespace {
						int y;
					}

				bu namespaceler i�erisindeki isimler global olarak do�rudan kullan�labilir ama di�er mod�llerden bunlar�n kullan�lma ihtimali olmayacak
				bu sayede static globallere bir alternatif olarak kullan�labilir ama tamamen bunlara olan ihtiyac� s�f�ra indiriyor diyemeyiz

			unnamed naemspacelerde k�m�latiftir 
				namespace {
					int x;
					void foo();
				}

				namespace {
					int y;

					class Nec{

					};
				}
	
			nested namespacelerde k�m�latiftif
				namespace ali{
					namespace can{
						int x = 5;
					}
				}

				namespace ali{
					namepace can{
						int y = 15;
					}
				}

				int main()
				{
					ali::can::x = 6;
					ali::can::y = 12;
				}

			�RNEK:
				namespace {
					int x = 5;
				}

				int x = 34;

				int main()
				{
					std::cout << ::x << '\n'; // valid x = 34
					std::cout << x << '\n'; // error ambiguous
				}

	namespacelerde overloading
		void foo(int)
		{
			std::cout<<"::foo(int)\n";
		}

		namespace nec{
			void foo(double)
			{
				std::cout<<"nec::foo(double)\n";
			}
		}
		
		using namespace nec; // using namespace direktifi ile nec namespace'i i�erisindeki isimler global namespace alan�nda g�r�n�r olur ve b�ylelikle overload set olu�turuluyor 

		int main()
		{
			foo(1.2) // double parametreli fonksiyon �a��r�l�r
		}

		�RNEK:
			namespace nec{
				void func(int)
				{
					std::cout<<"void nec::func(int)\n";
				}

				void func(double)
				{
					std::cout<<"void nec::func(double)\n";

				}
			}

			int func()
			{
				std::cout<<"int func()\n";

				return 1;
			}

			int main()
			{
				using nec::func;

				func(); // nec'in func ismi bu alana enjekte edildi�i i�in ge�ersiz
				func(12);
				func(2.5);
				::func();
			}

		�RNEK:
			namespace nec
			{
				void foo(int nec) { std::cout<< "nec::foo(int)<<'\n';} 
			}

			namespace erg
			{
				using namespace nec;

				void foo(long nec) { std:cout<<"erg::foo(long)" << '\n';}
			}

			void foo(double nec){ std::cout<<"::foo(double)" << '\n';}

			using namespace erg;

			int main()
			{
				foo(10); // nec::foo
				foo(10L); // erg::foo
				foo(3.14); // ::foo
			}


	INLINE NAMESPACE
		inline anahtar s�zc���yle bir namespace olu�turdu�umuz zaman onun i�indeki isimler onu kapsayan namespace i�inde g�r�l�r hale geliyor

		namespace nec{
			namespace erg{
				
				inline namespace asl{
					int x;
				}
			}
		}
		
		int main()
		{
			nec::erg::x; // inline oldu�u i�in bu �ekilde eri�ebiliyoruz
			erg te inline olsayd� nec::x �eklinde eri�ebilecektik hatta nec inline olsayd� direkt x ismi ile eri�ebilecektik
		}


		bunun dile eklenmesindeki 2 temel ama� var
			1)ADL
				using direktiflerinin kullan�ld��� yap�da ADL'in devreye girmedi�i ama inline namespace kullan�ld���nda ADL'in devreye girdi�i senaryolar var
			2)versiyon kontrol�
				namespace nec{
					inline namespace version_1{
						struct A{
							A() { std::cout<<"nec::version_1::A()\n"; } 
						}
					}

					namespace version_2{
						struct A{
							A() { std::cout<<"nec::version_2::A()\n"; }
						}
					}
				}

				int main()
				{
					nec::A ax; // �eklinde �a��r�yoruz inline anahtar s�zc��� version_2 namespace'inde yaz�lm�� olsayd� bu sefer version_2 namespace'i i�erisindeki ctor �a��r�lacakt�
					
					inline olmasayd� se�imi kodda kendimizin yapmas� gerekirdi
					nec::version_1::A ax;
					nec::version_2::A ax; // b�yle �a��rmam�z gerekirdi
				}

		C++20 ile nested namespacelerde inline olarak tan�mlanabiliyor
			namespace ali::veli:: inline gul{
				int x = 5;
			}

	NAMESPACE ALIAS
		namespace nec{
			
		}

		namespace erg = nec; // namespace alias erg namespace'ini nec namespace'i gibi kullanabiliyoruz erg demek nec demek 

		int main()
		{
			nec::x = 13;
			erg::x = 35;
		}

		namesapce alias kullanman�n en az 2 ihtiya� noktas� olabilir
			1)isim �ak��mas�
				namespace isminin kendiside �ak��maya sebep olabilir 

			2)yaz�m kolayl��� sa�lamas�
				namespace nec_proj_ai{
					namespace random{

						namespace details{
							int x = 10;
						}
					}
				}

				int main()
				{
					namespace details = nec_proj_ai::random::details;

				}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------					
NESTED TYPES
	class definition i�inde bir t�r�n bildirimini yaparsak o bir nested type/member type/type member 

	1)ba�ka bir s�n�f olmas�(structlarda dahil)
		class Myclass{
			
			class Nested{};

		};

	2)enumaration type olmas�(union dahil)
		class Myclass{
			
			enum class color { black,red,blue};

		};

	3)type alias
		class Myclass{
			using Word = int;
		}
*/