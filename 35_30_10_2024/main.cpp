/*

template parametre paketi
	1)type parameter pack
	2)non-type parameter pack
	3)template template parameter pack olabilir

	template parametre paketinin olmas� class template variable template yada function template olmas� ile ilgili de�il 

	fonksiyon �ablonu oldu�unda e�er template parametre paketinden sonra ellipsis tokeni gelirse buda fonksiyonun parametre paketi 
	template parametre paketi ba�ka fonksiyon parametre paketi ba�ka birbiriyle ili�kili ama olmak zorunda da de�il
		
		template <typename ...Ts>
		void func(Ts ...args)
		{

		}

		int main()
		{
			func(1,4,7,2.3); // derleyicinin olu�turdu�u instantiation asl�nda ��yle -> void func(int p1,int p2,int p3,double p4) {}
		}

	SORU: birden fazla template parametre paketi olabilir mi? OLAB�L�R ama belirli templatelerde olamaz  
				template <typename ...A, typename ...B> // hata class templateler'de ge�erli de�il
				struct Myclass {}

		ama function templatelerde esneklik var parametre paketi ne bir tane olmak zorunda ne de en sonda olmak zorunda
		
			template <typename ...X, typename ...Y>
			void foo(X ...xargs, int, int, Y ...yargs) // ge�erli
			{
				std::cout << "sizeof...X() = " << sizeof...(X) << '\n';
				std::cout << "sizeof...Y() = " << sizeof...(Y) << '\n';

			}

			int main()
			{
				foo<int, double, int>(1, 2.5, 3, 5, 5, 6, 7, 8, 9); // ilk 3 parametre X parametre paketine gidecek 5 ve 5 int int parametresine gidecek di�er geri kalanlar ise
																	   Y parametre paketine gidecek
			}

			�IKTI:
				sizeof...X() = 3
				sizeof...Y() = 4

			function templatelerde variadic parametre paketi s�z konusu oldu�unda standart 2 ye ayr�yor
				1)trailing(en son parametre paketi olmas�)
				2)non-trailing(en son parametre paketi olmamas�)
				
				template <typename ...X, typename ...Y>
				void foo(X ...xargs, int, int, Y ...yargs) // ge�erli
				{
					std::cout << "sizeof...X() = " << sizeof...(X) << '\n';
					std::cout << "sizeof...Y() = " << sizeof...(Y) << '\n';
				}

				int main()
				{
					
					foo(1, 2.5, 3, 5, 5, 6, 7, 8, 9); // fonksiyonu �a��rd���m�zda explicit arg�man kullanmazsak 1.parametre paketi bo� kabul ediliyor bu durumda arg�manlar ondan 
														 sonraki ��elere da��t�l�yor
				}	

				�IKTI:
					sizeof...X() = 0
					sizeof...Y() = 7

	visual studio derleyicisinde __FUNCSIG__ makrosu fonksiyonun geri d�n�� de�eri dahil parametrelerinede i�aret eden bir yaz�ya a��l�yor

	derleyicinin olu�turdu�u instantiation'�n nas�l bir fonksiyon oldu�unu g�rebiliyoruz

		template <typename T , typename ...Ts>
		void foo(T x, Ts ...yargs) 
		{
			std::cout << __FUNCSIG__ << '\n';

		}

		int main()
		{
			foo(12, 4 , 'A',3.4); // void __cdecl foo<int,int,char,double>(int,int,char,double)
		}

PACK EXPANSION(paketin geni�letilmesi
	
	derleyici ilgili context'de belirli �r�nt�lere uygun olarak virg�llerle ayr�lan bir listeye d�n��t�r�yor 
	
	PACK EXPANSION'I template parametre paketi i�inde ve foknsiyon parametre paketi i�inde kullanabiliriz 
	
		template<typename ...Ts>
		void foo(Ts ...args)
		{
			Ts...  // e�er template parametre paketinin isminden sonra ellipsis tokeni'ni kullan�rsak derleyici bunu paketteki t�rlerin isimlerini i�eren virg�lerle 
					  ayr�lan bir listeye �eviriyor
		}	

		�RNEK:

			template<typename ...Ts>
			void foo(Ts ...args)
			{
				std::tuple<Ts...> x; // template parametre paketi expand edildi�inde parametre paketinde ki t�rler yada de�erlerden olu�an comma separated list'e d�n���yor
			}
			
		D�KKAT:e�er parametre paketi fonksiyon parametre paketi pack expansion'a tabi tutulursa buda derleyici taraf�ndan yine virg�lle ayr�l�yor ama
				�rne�in fonksiyon parametre paketinde 3 tane parametre varsa T1 t�r�nden -> p1 , T2 t�r�nden -> p2 , T3 t�r�nden -> ,p3 ��kar�m yap�l�yor
				template parametre paketini expand edersek asl�nda bu �una d�n���yor -> T1 ,T2 ,T3 listesine d�n��t�r�lecek 
				fonksiyon parametre paketini expand edersek -> p1, p2, p3 listesine d�n��t�r�l�yor
				virg�llerle ayr�lan liste kullan�lan bir �ok context'de parametre paketinin expand edilmi� halini kullanabiliyoruz
			
				�RNEK:
					template<typename ...Ts>
					void foo(Ts ...args)
					{	
						bar(args...); // bar fonksiyonu fonksiyonun parametre de�i�kenlerinin de�erlerini g�nderir yani -> p1,p2,p3 
					}

					pack expansion daha uzun bir �r�nt�de olabilirdi

						template<typename ...Ts>
						void foo(Ts ...args)
						{	
							bar(&args...); // derleyici bunu bar(&p1,&p2,&p3); listesine d�n��t�r�cek
						}

				�RNEK:

					template<typename ...Ts>
					void baz(Ts ...args)
					{
						bar(baz(args)...); // burda expansion -> bar(baz(p1), baz(p2,) , baz(p3))
					}

	�RNEK:
		
		template <typename ...Ts>
		void print(Ts ...args)
		{
			((std::cout << args << ' '), ...);
			std::cout << '\n';
		}

		template <typename T>
		auto g(T* x) { return *x * *x + 10; }

		template <typename ...Ts>
		void f(Ts ...args)
		{
			//print(args...); // p1 , p2, p3 -> 1 2 3
			//print(&args...); // &p1 , &p2 , &p3 -> 0x7ffd733d40bc 0x7ffd733d40b8 0x7ffd733d40b4
			//print(10 * args...); // 10 * p1, 10 * p2, 10 * p3 -> 10 20 30
			//print(args * args...); // p1 * p1 , p2 * p2, p3 * p3 -> 1 4 9
			//print(g(&args)...); // g(&p1) , g(&p2) , g(&p3) -> 11 14 19
			//print(++args...); // ++p1 , ++p2 ++p3 -> 2 3 4

		}

		int main()
		{
			int x{ 1 }, y{ 2 }, z{ 3 };
			f(x, y ,z);
		}

	�RNEK:
		1)fonksiyonun parametre paketinde referans deklerat�r� olursa fonksiyonun b�t�n parametreleri L value reference olacakt�
			template <typename ...Ts>
			void f(Ts &...args) {}
			
		2)fonksiyonun parametre paketinde const ve referans deklerat�r� olursa fonksiyonun b�t�n parametreleri const L value reference olacakt�
			template <typename ...Ts>
			void f(const Ts &...args) {}

		3)fonksiyonun parametre paketi universal reference olursa �rne�in parametre paketinden 2 tane template parametresi varsa 2 tane universal reference parametre olacakt�
			template <typename ...Ts>
			void f(Ts &&...args) {}

	�RNEK:

		template <typename... Us>
		void f(Us... pargs{}
		
		template<typename... Ts>
		void g(Ts... args) {
			
			f(&args...); // &args... is a pack expansion 

		}

		int main()
		{
			g(1,0.2,"a"); // Ts... args expand int E1, double E2 ,const char* E3

			// &args expand to &E1,&E2,&E3

			Us... pargs expand to int* E1,double* E2,const char** E3
		}

	�RNEK:

		template <typename T,typename ...Args>
		std::unique_ptr<T> MakeUnique(Args&& ...args)
		{
			new T(args...) // fonksiyonun parametre de�i�kenlerini g�ndermi� olurduk
			new T(f(args)...) // ismi F olan bir fonksiyona arg�manlar� g�nderip onlar�n virg�llerle olu�turdu�u listeyi T s�n�f�n�n ctoruna arg�man olarak g�ndermi� olurduk
			
			return std::unique_ptr<T>(new T(std::forward<Args>(args)...)) // burda MANDATORY COPY ELISION GER�EKLE��YOR ve parametre paketinde �rne�in 3 arg�man varsa 3 kez forward'a 
																			 �a�r� yap�lacak								
		}

	�RNEK:

		template<typename ...TS>
		class Var{};

		template <typename ...Types>
		class Myclass : public Var<Types...>{
			public:
				constexpr static size_t size = sizeof...(Types);
		};

		int main()
		{
			constexpr auto n = Myclass<int,double>::size;
			static_assert(std::is_base_of_v<Var<int,double>,Myclass<int,double>>);	
		}

	�RNEK:
			
		 template <typename... Types, int... N>
		 void func(Types(&...args)[N])
		 {
			std::cout<< __FUNCSIG__ << '\n';
		 }

		 int main()
		 {
			int a[2]{};
			int b[3]{};
			int c[5]{};
			double d[7]{};

			func(a,b,c,d); // func<int[2],int[3],int[5],double[7]>(int(&)[2],int(&)[3],int(&)[5],double(&)[7])
		 }

	variadic parametre paketine sahip fonksiyon �ablonlar� diledi�imiz say�da arg�manla �a��rma olana�� veriyor ama bu olanaktan nas�l istifade ediyoruz?

		template <typename ...Ts>
		void print(const Ts&... args) 
		{
			 �rne�in bu fonksiyonun t�m gelen arg�manlar� yazd�rmak olsayd� fonksiyonun parametrelerinin her birine eri�memiz gerekirdi bunu nas�l yapaca��z?
			
				1)COMPILE TIME RECURSIVE PACK EXPANSION
					
				�RNEK:
					template<typename T>
					void print(const T& r) { std::cout<< r << '\n'; }

					template <typename T, typename ...Ts>
					void print(const T& r,const Ts& ...args)
					{
						std::cout<< __FUNCSIG__ << '\n';
						print(r);
						print(args...);
					}

					int main()
					{
						int x = 10;
						double d = 23.5;
						print(x,d,9L,"necati"); // x fonksiyonun 1.parametresine gidecek geri kalan arg�manlar fonksiyonun parametre paketi olan ...args'a gidecek
												   print(r) �a�r�s� ilk arg�man� yazd�racak print(args...) pack expansion'� geriye kalan 3 arg�man� yazd�racak			
												   pakette ne zaman 1 arg�man kal�rsa onuda en son �a��r�lan print fonksiyonu yazd�r�cak yani arg�manlar
												   azalmaya ba�lad��� zaman geriye en son 1 parametre kalm�� olacak ve en son �stte ki print fonksiyonunu �a��rm�� olucaz 
					}

				�RNEK:
					
					template<typename T>
					std::ostream& print(std::ostream& os,const T& t) { return os << t; } 
					
					template<typename T,typename... Args>
					std::ostream& print(std::ostream& os, const T& t,const Args& ...rest)
					{
						os << t << ", ";
						return print(os,rest...);
					}

					int main()
					{
						print(std::cout,45,"ali",3.87,'A');
					}

				�RNEK:

					template<typename T>
					T max(const T&,const T& b) 
					{
						return a > b ? a : b;
					}

					template <typename T,typename ...Args>
					T max(const T& a,const Args&... args)
					{
						return max(a,(max(args...));
					}

					int main()
					{
						std::cout<< max(2,4,1) << '\n';
						std::cout<< max(4.2,2.6.5.1,8.2 ) << '\n';
					}

				2)INITIALIZER LIST

					template <typename ...Ts>
					void print(const Ts& ...args)
					{
						(void)std::initalizer_list{ std::cout << args << " " , 0)... }; // burda virg�l operat�r�n�n sequence point olu�turmas� ve virg�l operat�r�n�n �retti�i 
																						   de�erin sa� operand�n de�eri olmas�
					}

					int main()
					{
						print(2, 2.3, "alihan", std::bitset<16>{453u});
					}

				3)FOLD EXPRESSION(katlama ifadeleri C++17 ile geldi)

					variadic parametre paketleriyle ilgili yani ortada parametre paketi yoksa ve variadic her hangi bir template yoksa fold ifadesinin kullan�lmas� m�mk�n de�il 
					FOLD EXPRESSION parametre paketinin �nceden belirlenmi� bir �ekilde expand edilmesini sa�l�yor 

					fold i�lemi bir operat�r �st�nde yap�lmak zorunda
					
					dil 2 kategoriye ay�r�yor

						1)unary fold expressions
							a)unary right fold
							b)unary left fold

						2)binary fold expressions
							a)binary right fold
							b)binary left fold

					�RNEK:

						template <typename ...Ts>
						auto sum(Ts ...args)
						{
							return (... + args) // ellipsis tokeni binary operat�r�n solundaysa buna unary left fold deniliyor
						}

						SORU: derleyici burda nas�l bir kod �retecek bu ifade b�t�n arg�manlar�n toplam� anlam�na gelecek -> ((p1 + p2) + p3) + p4 left fold oldu�u i�in soldan 
							  parantez i�ine al�nd�

					�RNEK:right fold olsayd� derleyici nas�l bir kod �retirdi
						
						template <typename ...Ts>
						auto sum(Ts ...args)
						{
							return (args + ...); -> �rne�in 5 tane parametre de�eri varsa derleyici bunu �una d�n��t�recek return (p1 + p2 + p3 + (p4 + p5)) // right fold oldu�u i�in 
																																								parantez sa�dan
						}
					D�KKAT:left fold ve right fold birbirinden farkl� sonu�lar �retebilir
						template <typename ...Ts>
						auto sum(Ts ...args)
						{
							// return (... + args)
							return (args + ...); 
																																								
						}

						int main()
						{
							std::string name{"samet"};

							std::cout<<"sum(name,"sen","gel") << '\n'; // right fold'da hata verir ��nk� iki adresi toplayamay�z(const char* + const char*) 
																		  ama string ile const char* toplanabilir
						}

					�RNEK:

						template <typename ...Ts>
						auto div(Ts ...args)
						{
							// return(args / ...);
							 return(... / args);
						}

						int main()
						{
							std::cout<<div(500,50,5,2); // left fold oldu�unda 1 sonucunu �retir
														   right fold oldu�unda 20 sonucunu �retir
						}

					�RNEK:

						template <int ...N>
						constexpr int Sum = (... + N);

						int main()
						{
							Sum<2,5,7,9>
						}
						
				4)CONSTEXPR IF & compile time recursive
					
					derleyicinin bir kodu g�rmesini yada g�rmemesini sa�layacak derleme zaman�nda ele al�n�yor ama� if'in kontrol ifadesi bir constant expression olacak
					e�er o constant exxpression compile time'da true de�er �retirse if'in do�ru k�sm�ndaki kodu derleyecek false ise o k�s�mdaki kodu derleyecek
					normal fonksiyonlar i�inde static if'i kullanabiliriz ama orda kurallar daha farkl� oluyor

					template <typename T>
					void func(T)
					{
						if constexpr(sizeof(T) > 2)
						{
							std::cout<<"compiled code is true path\n";
						}
						else
						{
							std::cout<<"compiled code is false path\n";
						}
					}

					int main()
					{
						short s = 34;

						func(s); // false
						func(45); // true
					}	

					1)bu ifadenin sabit ifade olma mecburiyeti var 
						template <typename T>
						void func(T x)
						{
							if constexpr(x > 2) // gibi bir ifade yazamay�z
							{
								std::cout<<"compiled code is true path\n";
							}
							else
							{
								std::cout<<"compiled code is false path\n";
							}
						}	

					2)derleyicinin derlemede�i k�s�mdaki kod sentaks hatas� olu�turmuyor
						
						namelookup ile ilgili bir problem olmad��� s�rece o kod derlenmiyor 
						
						struct Nec{
							void foo(){};
						};

						template <typename T>
						void func(T x)
						{
							if constexpr(!std::is_integral_v<T>) // bu ifadenin do�ru olmas� i�in T t�r�n�n tam say� t�rlerinden olmamas� gerekiyor
							{
								x.foo(); 
							}
							else
							{
								std::cout<<"compiled code is false path\n";
							}
						}	

						int main()
						{
							func(12); // T t�r� int olacak else k�sm� �al��acak e�er if constexpr k�sm�n� derleseydi int t�rden de�i�keni nokta operat�r�n�n operand� yapm�� olacakt�k
										 buda sentaks hatas� olu�turacakt� ama derleyici o kodu derlemede�i i�in sentaks hatas� olu�mayacak
						}

					D�KKAT: else if yazarken constexpr yazmay� unutmamal�y�z yazmazsak run time'a ili�kin olur
							if constexpr(!std::is_integral_v<T>)
							{
								x.foo();
							}
							else if constexpr(std::is_floating_point_v<T>){}

					�RNEK:
						
						template <typename T>
						std::string as_string(T x)
						{
							if constexpr (std::is_same_v<T, std::string>)
							{
								return x;
							}
							else if constexpr (std::is_arithmetic_v<T>)
							{
								return std::to_string(x);
							}
							else
							{
								return std::string(x);
							}
						}

						int main()
						{
							std::cout << as_string(42) << '\n';
							std::cout << as_string(4.2) << '\n';
							std::cout << as_string(std::string("hello")) << '\n';
							std::cout << as_string("hello") << '\n';
						}

					�RNEK:
						
						template <typename T>
						void func(T tx)
						{
							if constexpr(std::is_integral_v<T>)
							{
								if(tx !=0)
								{
									func(tx--);
								}
							}
							else
							{
								// undeclared_f(); // sytanx error name non dependent on template parameter
								// undeclared_f(); // error if else part instantiated
								
							}
						}

					D�KKAT: if constexpr fonksiyon �ablonu de�ilse true k�sm�da false k�sm�da compile time'da hata olu�turmayacak kodlardan olu�mal�
						
					�RNEK:
					
						template <typename T>
						auto get_value(T x)
						{
							if constexpr (std::is_pointer_v<T>)
								return *x;
							else
								return x;
						}

						int main()
						{
							int i = 56;
							std::string s{ "necati ergin" };
							auto* p = &s;

							std::cout << get_value(i) << '\n';
							std::cout << get_value(p) << '\n';
						}

					�RNEK:

						template <typename T>
						std::string tostr(T t) { return std::to_string(t); }
						std::string tostr(const std::string& s) { return s; }
						std::string tostr(const char* cstr) { return cstr; }
						std::string tostr(bool) { return b ? "true" : "false"; }

						int main()
						{
							std::cout<<"tostr("necati")<<'\n';
							std::cout<<"tostr(std::string{"ergin})<<'\n';
							std::cout<<"tostr(13)<<'\n';
							std::cout<<"tostr(5.9)<<'\n';
							std::cout<<"tostr(true)<<'\n';
						}
						
						�stte bulunan overloadingler yerine derleyicinin compile time'da kod se�mesini sa�layal�m

							template <typename T>
							std::string tostr(T t)
							{
								if constexpr(std::is_convertible_v<T,std::string>)
									return t;
								else if constexpr(std::is_same_v<T,bool>)
									return t ? "true" : "false"
								else
									return std::to_string(t);
							}

	STATIC_ASSERT DECLERATION

		1)bildirimi global olarak yapabiliriz
		2)local d�zeyde yapabiliriz
		3)s�n�f i�inde yapabiliriz
		
		ortada template olsada olmasada kullanabiliriz yani generic kodlarla kullan�lmak zorunda de�il ama template kodlalrla kullan�m� �ok daha yayg�n

		static_assert(constant expression, string literal); // derleyici compile time'da static assert'e g�nderilen sabit ifadenin compile time'da true yada false oldu�unu s�n�yor
															   true ise sentaks hatas� olu�muyor ama false ise sentaks hatas� olu�uyor ve hatay� verirken derleyici 2.parametre olan 
															   string literali'ni hata mesaj� olarak g�steriyor(C++ 17'ye kadar string literali arg�man�n� girmek zorunluydu ama sonra kalkt�)

		�RNEK:

			static_assert(sizeof(int) > 4,"sizeof int must be greater than 2"); // compile time'da yanl�� oldu�u i�in derleyici sentaks hatas� verir 

		�RNEK: concept'ler dile eklenmeden �nce templateleri k�s�t�lamak i�in farkl� farkl� ara�lar kullan�l�yordu bu ara�lardan biride static_assert
				
			template <typename T>
			class Myclass {

				static_assert(std::is_integral_v<T>);
			};

			int main()
			{
				Myclass<int> x;
				Myclass<double> x; // static_assertion'a tak�l�r ve hata verir
			}

		�RNEK:

			template <typename T>
			class Myclass{
				static_assert(std::is_default_constructible_v<T>);
			};

			struct Nec{
				Nec(int); 
			};

			int main()
			{
				Myclass<Nec> x; // Nec s�n�f�n�n default ctor'u olmad��� i�in sentaks hatas� olu�tu
			}
*/