/*

templatelerden devam ediyoruz

�RNEK:

	template<long long N>
	constexpr long long factorial()
	{
		return N * factorial<N - 1>();
	}

	template<>
	constexpr long long factorial<0>() // recursive �a�r�y� durduracak olan explicit specialization
	{
		return 1;
	}

	int main()
	{
		factorial<5>();
	}

�RNEK:
	
	template<typename T>
	struct Myclass{
		
		template<typename U>
		void func(U)
		{
			std::cout<<"type T is" << typeid(T).name() << '\n';
			std::cout<<"type U is" << typeid(U).name() << '\n';
		}
	};

	int main()
	{
		Myclass<double> x;
		x.func(34);
	}
		�IKTI:
			type T is double
			type U is int

�RNEK:
	template<typename T>
	struct Myclass{

		template<typename U>
		void func(U)
		{
			std::cout<<"type T is " << typeid(T).name() << '\n';
			std::cout<<"type U is " << typeid(U).name() << '\n';
		}
	};

	template<>
	template<> // template'in member template'i i�in bir explicit specialization oldu�unu derleyici anlayacak
	void Myclass<double>::func(int)
	{
		std::cout<<"explicit specialization\n";
	}

	int main()
	{
		Myclass<double> x;
		x.func(34);
	}

		�IKTI:
			explicit specialization
			type T is int
			type U is int

PARTIAL SPECIZALIZATION

	fonksiyon �ablonlar�nda kullan�lm�yordu

	template parametrelerine kar��l�k gelen t�rler i�in kullan�l�yor

	�RNEK:
		template <typename T>
		struct Myclass{

		};

		template<typename T> // burada bulunan template parametre say�s� de�i�ebilir AMA A�ISAL PARANTEZ i�ine yazd���m�z template arg�man(Myclass<T*>) say�s� primary template'de
								bulunan arg�man say�s�yla ayn� olmak zorunda
		struct Myclass<T*> { // template arg�man olarak pointer t�r� kullan�l�rsa bu kod kullan�lacak ve interface'in primary tempalate ile ayn� olmas� gerekmiyor

		};

	�RNEK:
		template <typename T,int N>
		struct Nec{
			Nec()
			{
				std::cout<<"primary template\n";
			}
		};

		template <typename T, typename U, int N>
		struct Nec <std::pair<T, U>, N>
		{
			Nec()
			{
				std::cout << "partial template\n";
			}

		};

		int main()
		{
			Nec<std::pair<int, long>, 5> m1;
		}

	�RNEK:
		template <typename T,int N>
		struct Nec{
			Nec()
			{
				std::cout<<"primary template\n";
			}
		};

		template <typename T>
		struct Nec<T,3>{
			Nec()
			{
				std::cout<<"partial specialization Nec<T,3>\n";
			}
		};

		int main()
		{
			Nec<double,5> n1;
			Nec<int,3> n2;
			Nec<long,67> n3;
		}	

			�IKTI:
				primary template
				partial specialization Nec<T,3>
				primary template


	tpyename anahtar s�zc���n�n kullan�ld��� bir context daha var bu contexte typename anahtar s�zc���n�n yerine class anahtar s�zc���n� kullanam�yoruz
	
		template<typename T>
		void foo(const T& t)
		{
			T::size_type* p(T::npos); // b�yle isimlere dependent name deniliyor �yle bir isim ki template parametresine ba�l� dependent name'in namelookup kurallar�yla
										 dependent olmayanlar�n namelookup kurallar� farkl� yak�nda g�rece�iz 
			

			bar(); // sentaks hatas� olurdu ��nk� derleyici bar her hangi bir �ekilde template parametresine ba�l� bir isim olamd��� i�in template'in �st�nden ilk kez ge�ti�inde 
						bar ismini ar�yor ve bulamad��� i�in isim arama hatas� oluyor

			T::value_type x; // bu durumda value_type identifier fakat bu template parametresine ba�l� value_type'�n ne oldu�u T yerine kullan�lacak template aeg�man�n�n ne oldu�una ba�l� 
	
			dependent type'dan bahsediyorsak size_type bir t�rse nested type ise derleyicinin bunu nested type olarak almas� i�in typename anahtar s�zc���n� kullan�yoruz e�er typename
			anahtar s�zc���n� kullanmazsak derleyici bunu expression olarak ele al�yor

				typename T::size_type

				�RNEK:
					
					template<typename T>
					void foo(const T&)
					{
						typename T::size_type x; // template kodda template parametresinew ba�l� bir t�rden bahsediyorsak kodun ifade olarak de�ilde derleyici taraf�ndan 
													bir t�r olarak ele al�nmas� i�in typename anahtar s�zc���n� kullan�yoruz
					}

					struct A{
						using size_type = int;
					};

					int main()
					{
						A ax;

						foo(ax); // typename anahtar kelimesinin kullanmasayd�k hata verecekti 
					}

				�RNEK: C++20 ile bu kurallar baz� durumlar i�in gev�etildi template kod i�inde t�rden bahsetti�imiz her yerde typename anahtar kelimesini kullanmak zorundayd�k

					template <typename T>
					T::value_type foo(T) // C++20'den �nce olsayd� fonksiyonun geri d�n�� de�erinin t�r�de olsa burda yine typename anahtar s�zc���n� kullanmam�z gerekiyordu 
					{						fonksiyonun geri d�n�� de�erinin t�r�n�n yaz�ld��� yerde bir expression olma ihtimali olmad��� i�in b�yle durumlardada t�r olmas� d���nda
											ba�ka bir durum olmas� s�z konusu de�ilse typename anahtar s�zc���n� kullanmam�za gerek yok
						return {}; 
					}

					template<typename T>
					class Myclass{
						using value_type = T::value_type; // C++20 ile typename anahtar s�zc���n� kullanmam�za gerek kalm�yor
					};
	}		

VARIABLE TEMPLATE
	derleyici variable template'e bir instantiation yapt���nda bir variable tan�mlamas� olu�uyor yani variable tan�mlamas� i�in kullanaca�� template

	�RNEK:
		template <typename T>
		struct Myclass{
			constexpr static int value = 10; 
		};

		template <typename T>
		constexpr int Myclass_v = Myclass<T>::value;


		int main()
		{
			constexpr auto x1 = Myclass_v<int>;
		}

	�RNEK:
		template <std::size_t N>
		constexpr std::size_t fact = N * fact<N - 1>;

		template<>
		constexpr std::size_t fact<0> = 1;

	�RNEK:
		template<std::size_t X>
		constexpr std::size_t sbc = (X % 2) + sbc<X / 2>;

		template <>
		constexpr std::size_t sbc<0> = 0;

		int main()
		{
			constexpr auto val = sbc<15u>;
		}
	
ALIAS TEMPLATE
	
	template<typename T>
	using Ptr = T*; // ptrnin kendisi type ailas de�il type alias template type alias olacak olan Ptr'nin bir specialization'�


	int main()
	{
		Ptr<int> p1; // int*	
	}

	�RNEK:
		template<typename T,int N>
		using ar = T[N];

		int main()
		{
			ar<int,5>; // int[5]
		}

	�RNEK:
		template <typename T>
		using epair = std::pair<T,T>;

		int main()
		{
			epair<int>;
		}

	�RNEK:
		template<typename T>
		using fptr = T(*)(T);

		int foo(int);
		double bar(double);

		int main()
		{
			fptr<int> fp1 = &foo;
			fptr<double> fp2 = &bar;
		}

	standart k�t�phanede generic taraf�nda isminin sonunda _t olanlar alias template _v olanlar ise variable template oluyor
		
		is_floating_point_v<double>; // �o�unlukla bu variable templateler constexpr boolean sabitlerdir
										bunu yazmakla is_floating_point<double>::value yazmak ayn� anlama geliyor

		remove_reference<int&>::type // eleman�na eri�t�imizde bir t�r elde ediyoruz bu t�r template arg�man� olan t�r�n referanstan ar�nd�r�lm�� hali
										b�yle meta functionlar input olarak bir t�r al�yorlar output olarak bir t�r veriyorlar compile timeda ki bir fonksiyon gibi
										standart k�t�phane b�yle fonksiyonlar i�in alias template sa�l�yor remove_reference_t<int&> yazmakla ayn� �ey

		�RNEK:
			template<typename T>
			using remove_reference_t = std::remove_reference<T>::type;

			int main()
			{
				remove_reference_t<int&>;
			}

TEMPLATELER�N DEFAULT ARGUMAN ALMASI
	
	default arg�man her hangi bir template parametresi i�in kullan�labilir �rne�in non-type 

	template <typename T = int>
	class Myclass{};

	int main()
	{
		Myclass<double> m1; // default arg�man� kullanmam�� oluyoruz
		Myclass<> m3; // template arg�man�n� belirtmedi�imiz i�in T t�r� int oluyor
	}	

	class templatelerde ve variable templatelerde default arg�manlara ili�kin ��yle bir kural var
		bir template parametresi default arg�man al�yorsa onun sa��ndakilerin hepsi default arg�man almak zorunda

		template <typename T = int,typename U> // U t�r� de default arg�man almak zorunda

		�RNEK:
			template<typename T = int,typename U = double>
			struct Myclass{
				Myclass()
				{
					std::cout<<typeid(*this).name() << '\n';
				}
			};

			int main()
			{
				Myclass<char,char> m1;
				Myclass<char> m2;
				Myclass<> m3;
			}

			�IKTI:
				struct Myclass<char,char>
				struct Myclass<char,double>
				struct Myclass<int,double>

		D�KKAT:function templatelerde bu ge�erli de�il
			template <typename T = int,typename U> // ama bu �ekilde yaz�lmas� fonksiyona yap�lan her �a�r�n�n legal olaca�� anlam�na gelmiyor
			void func(T x,U y);

		�RNEK:
			void strfunc(const char* p,std::size_t len = std::strlen(p)) {} // bu sentaks ge�erli de�il ama templatelerde bu durum i�in bir k�s�tlama yok

			template<typename T, typename U = T>
			struct Myclass {
				Myclass()
				{
					std::cout << typeid(*this).name() << '\n';

				}
			};

			int main()
			{
				Myclass<int, double> m1; // default arg�man� kullanmad���m�z i�in U t�r� double olur
				Myclass<int> m2; // T ve U int olur
			}

		�RNEK:
			template <typename T>
			class Nec {};

			template<typename T, typename U = Nec<T>>
			struct Myclass {
				Myclass()
				{
					std::cout << typeid(*this).name() << '\n';
				}
			};

			int main()
			{

				Myclass<int> m;
			}

			�IKTI:
				struct Myclass<int,class Nec<int> >


		�RNEK:templatelerde de default parametreler k�m�latif olabilir

			template<typename T, typename U, typename W = int>
			class Myclass;

			template<typename T, typename U = double, typename W>
			class Myclass;

			template<typename T = char, typename U, typename W>
			class Myclass {
			public:
				Myclass()
				{
					std::cout << typeid(Myclass).name() << '\n';
				}
			};

			int main()
			{
				Myclass<> m1;
			}

			�IKTI:
				class Myclass<char,double,int>
			

	hoca function templatelerde s�k yap�lan bir hatadan bahsediyor

		template <typename T>
		void foo(T x = 43);

		int main()
		{
			foo(); // bu �a�r� legal de�il ��nk� burda template argument deduction yap�labilmesi i�in fonksiyona arg�man g�ndermemiz gerekiyor
					  
		}

		generic programlama taraf�nda �ok s�k kullan�lan bir yap� var
			template <typename T = int>
			T foo(T x = 0)
			{
				return x * x;
			}	

			int main()
			{
				auto val = foo();  // fonksiyonun parametresi default arg�man al�yor ama template'in parametreside default arg�man al�yor derleyici burda ��kar�m yap�lmad���n� 
									  g�rd��� zaman template parametresinin default arg�man al�p almad���na bak�yor int oldu�unu g�r�yor
			}
			
		bunun kullan�ld��� value initialization sentaks�da �nemli
			template<typename T = int>
			T foo(T x = {} ) // bu durumda default template arg�man�n� kullan�rsak T t�r� int olucak bu durumda int t�rden parametreye 0 de�eri ge�ilmi� olucak 
			{					T t�r� s�n�f t�r� oldu�u zaman bu durumda default ctor �a��r�lacak function template'in call parametresi default arg�man kullan�ld���nda 
								asl�nda default ctor edilmi� bir parametreyi kullanm�� olucaz
			}

			int main()
			{
				foo<std::string>();
			}

		default arg�manlarda k���kt�r b�ty�kt�r i�aretlerini kullan�rkan dikkat etmeliyiz
			template<int N = (5 < 9)>
		
PERFECT FORWARDING(M�KEMMEL G�NDER�M)

	void func(Myclass){} // fonksiyona arg�manlar� do�rudan g�ndermek yerine bu fonksiyonu �a��racak bir fonksiyona �a�r� yapaca��z �rne�in call_func'a g�nderdi�imiz arg�manlar�n call_func 
	call_func				taraf�ndan func'a g�nderilmesiyle yani call_func'�n bizden ald��� arg�manlarla func'� �a���rmas�yla bizim o arg�manlarla do�rudan func'� �a��rmak aras�nda
							hi� bir fark olmayacak

						g�nderdi�miz arg�manlar�n value kategorisi korunacak
						constlu�u korunacak

	�RNEK:perfect forwarding olmadan nas�l yapar�z
		class Myclass{};

		void func(Myclass&) { std::cout << "func(Myclass&)\n"; }
		void func(const Myclass&) { std::cout << "func(const Myclass&)\n"; }
		void func(Myclass&&) { std::cout << "func(Myclass&&)\n"; }
		void func(const Myclass&&) { std::cout << "func(const Myclass&&)\n"; } // nadiren kullan�lan parametre

		void call_func(Myclass& r) { func(r); }
		void call_func(const Myclass& r) { func(r); }
		void call_func(Myclass&& r) { func(std::move(r)); }
		void call_func(const Myclass&& r) { func(std::move(r)); }

		int main()
		{
			Myclass m;
			const Myclass cm;

			func(m);
			func(cm);
			func(std::move(m));
			func(std::move(cm));

			call_func(m);
			call_func(cm);
			call_func(std::move(m));
			call_func(std::move(cm));
		}

		burada bir sorun mevcut bunu yapmak i�in tek parametreli fonksiyon varsa 4 tane fonksiyon yazmam�z gerekir 2 tane parametresi olsayd� 4'�n karesi kadar 16 tane 
		fonksiyon yazmam�z gerekirdi 

		��Z�M:
			template<typename T>
			void call_func(T&& x)
			{
				func(std::forward<T>(x)); // fonksiyonu do�rudan �a��rmak yerine arg�man� forward'a arg�man olarak g�nderip forward'�n geri d�n�� de�eri ile fonksiyonu �a��rd���m�zda
											 hem constlu�unu hemde value kategorisini korumu� oluyoruz yani L value de�erini L value olarak koruyor R value de�erinide koruyor
			}

			�rne�in iki parametreli olsayd� 
				template<typename T,typename U>
				void call_func(T&& x,T&& y)
				{
					func(std::forward<T>(x), std::forward<U>(y));
				}
*/