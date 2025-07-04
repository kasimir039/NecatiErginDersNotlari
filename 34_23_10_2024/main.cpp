/*
forwarding reference kar��m�za 2 �ekilde ��k�yor
	1)template olarak
		template<typename T>
		void func(T&&) {} // const yada volatile gibi yada ba�ka bir specifier varsa art�k universal reference de�il sadece T&& bi�iminde universal reference olmu� oluyor

	2)auto type deduction
		auto&&r

	D�KKAT:
		hoca s�n�flar�n memberlar� s�z konusu oldu�unda yanl�� anla��lan bir konuya de�iniyor
			template<typename T>
			class Myclass{
				public:
					void foo(T&&){} // bu universal reference de�il sadece R value de�erleri al�r
			};

			�RNEK:vector s�n�f�ndan �rnek
				template Vector{
					public:
						void push_back(const T&); // L value de�erleri kopyalarak containera ekler
						void push_back(T&&); // R value de�erleri ta��yarak containera ekler
				
						template<typename U> // member template
						void emplace_back(U&&) {} // bu universal reference olmu� oluyor
				};

	�RNEK:perfect forwarding'in faydas�n� g�rmek i�in vector �rne�i
	
		sondan ekleme yap�l�rken nesne i�in ne copy ctor'un nede move ctor'un �a��r�lmas�n� istemiyoruz nesnesinin kendisi olu�turulacak ama nesnesinin kendisi olu�turulmas� i�in
		ctora g�nderdi�imiz arg�manlar� g�ndermemiz gerekiyor �yle bir fonksiyon olacak ki ne L value nede R value bir de�er g�ndermeyece�iz sadece ctor'a g�nderilecek arg�manlar� g�nderece�iz 
		bu fonksiyona adeta ��yle demi� olaca��z sevgili fonksiyon :D al bu arg�manlar� bu arg�manlar� kullanarak vector'�n nesneyi olu�turaca�� bellek alan�nda ctoru �a��rarak benim 
		arg�manlar�m� ctora g�nder demi� oluyoruz e�er burada bizim ctoru �a��r�mam�zla buradaki fonksiyonun bizim ad�m�za ctoru �a��rmas�n�n bir fark� olmamas� i�in g�nderdi�imiz arg�manlar�n
		value kategorisi ve constlu�unun korunmas� gerekiyor -> bunu yapan emplace_back fonksiyonu ne ta��ma ne de kopyalama yapmaz


	forward fonksiyonunun �a��rlmas� gibi bir zorunluluk yok ama
		1)kodu daha pratik hale getiriyor
		2)parametre paketleriyle kullan�lmas�n� m�mk�n hale getiriyor

IF CONSTEXPR(compile time'da ele al�n�r)

	if constexpr(std::is_lvalue_reference<T>::value)
	{
		foo(x);
	}
	else
	{
		foo(std::move(x));
	} // std::forward olmasayd� b�yle yazmam�z gerekecekti
	
ABBREVIATED TEMPLATE SENTAKSINDA FORWARDI NASIL KULLANIRIZ
	
	void func(auto&& x)
	{
		std::forward<decltype(x)>(x);
	}

TYPE TRAITS K�T�PHANES�
	meta functionlardan olu�an C++ dilinin standart k�t�phanesinin bir bile�enidir 
	bulunan varl�klar tamamen compile time'a ili�kin

	template<typename T,T v>
	struct integral_constant
	{
		static constexpr T value = v;
		using value_type = T;
		using type = integral_constant;
		constexpr operator value_type() const noexcept { return value; }
		constexpr value_type operator()() const noexcept {return value;}
	};

	using true_type = integral_constant<bool,true>;
	using false_type = integral_constant<bool,false>;

	int main()
	{
		integral_constant<int,5>::value_type; // int 
		integral_constant<int,5>::type; // integral_constant<int,5>

		true_type::type // integral_constant<bool,true>
		 
		constexpr auto val = integral_constant<int,5>{} + integral_constant<int,9>{} // 14 

	}

	�RNEK:bir t�r�n pointer t�r� olup olmad���n� compile time'da s�namak

		template <typename T>
		struct isPointer : std::false_type {};
		
		template <typename T>
		struct isPointer<T*> : std::true_type {}; // partial specialization
		
		template<typename T>
		constexpr bool isPointer_v = isPointer<T>::value; // value template

		template <typename T>
		 void func(T x)
		{
			if constexpr (isPointer_v<T>)
			{
				std::cout << "pointer turu\n";
			}
			else
			{
				std::cout << "hayir pointer t�r� de�il\n";
			}
		}

		int main()
		{
			isPointer<int*>::value; // true
			isPointer<const int*>::value; // true
			isPointer<int>::value; // false

			int* p = {};
			func(p); // true
		}
		
	�RNEK:bir t�r�n const olup olmad���n� s�namak	

		template<typename T>
		struct isConst : std::false_type {};

		template<typename T>
		struct isConst<const T> : std::true_type {};

		template<typename T>
		constexpr bool isConst_v = isConst<T>::value;

		int main()
		{
			isConst_v<const int>; // true
		}
		
	�RNEK:remove_const

		template<typename T>
		struct RemoveConst{
			using type = T;
		}

		template<typename T>
		struct RemoveConst<const T> {
			using type = T;
		}

	�RNEK:birinci parametre hangi t�rden ise ikinci parametre i�in bir ��kar�m yap�lmas�n o da ayn� t�r olsun

		func(1.24,45); // yani bu sentaks hatas� olmayacak 2.parametrede double t�rden olacak 
		 
		 template <typename T>
		 struct TypeIdentity{
			using type = T;
		 };

		 template<typename T>
		 void func(T x, std::type_idendtity_t<T> y);

		 int main()
		 {
			func(12.3, // 2.parametrenin t�r� type �dentitiy T 'nin double a��l�m� 
		 }

	�RNEK:remove_reference

		template <typename T> struct remove_reference { using type = T; };
		template <typename T> struct remove_reference<T&> { using type = T; };
		template <typename T> struct remove_reference<T&&> { using type = T; };

		template <typename  T>
		using remove_reference_t = typename remove_reference<T>::type;

		int main()
		{
			remove_reference_t<int&> x { 3 }; // int x
			remove_reference_t<int&&> y { 3 }; // int y
		}

	�RNEK:
		
		template <typename T> struct add_cv { using type = const volatile T; };
		template <typename T> struct add_const { using type = const T; };
		template <typename T> struct add_volatile { using type = volatile T; };

		template <typename T>
		using add_cv_t = typename add_cv<T>::type;

		template <typename T>
		using add_const_t = typename add_const<T>::type;

		template <typename T>
		using add_volatile_t = typename add_volatile<T>::type;

		int main()
		{
			add_cv_t<int> x1{}; // const volatile int
			add_cv_t<int*> x2{}; // int* const volatile
			add_const_t<int*> x3{}; // int* const
			add_const_t<const int*> x4{}; // const int* const
			add_volatile_t<int*> x5{}; // int* volatile
			add_volatile_t<const int*> x6{}; // const int* volatile
		}

	�RNEK:
		
		template<typename T>
		struct TypeIdentity {
			using type = T;
		};

		template<typename T>
		struct remove_const : TypeIdentity<T> {};

		template<typename T>
		struct remove_const<const T> : TypeIdentity<T> {};

		template<typename T>
		using remove_const_t = typename remove_const<T>::type;

		int main()
		{
					remove_const_t<const int> a;      // int
					remove_const_t<int> b;           // int
					remove_const_t<const int*> c;     // const int*
					remove_const_t<int* const> d;    // int*
		}


	�RNEK:

		her ikiside t�m arg�manlar� alabiliyor peki bunlar�n fark� ne?

		template <typename T> 
		void foo(T&& t) // bu fonksiyonda b�t�n arg�manlar� alabiliyoruz g�nderilen arg�man�n L value yada R value oldu�unu const olup olmad���n� b�t�n bunlar� fonksiyonun i�inde
						   compile time'da ��renebiliyoruz
		{
			std::is_lvalue_reference_v<T>

			//abbreviated template sentaks�nda b�yle yazabiliriz -> std::is_lvalue_reference_v<decltype(t)>;
		
			bu bize const yada const olmayanlar i�in ayr� bir kod yazmay� L value yada R value olup olmad���n� yada onlara kod yazma olana��n� bize veriyor 
	
		}

		template <typename T>
		void bar(const T&); // bu fonksiyonda her t�rl� arg�man� kabul ediyor ama g�nderilen arg�man�n� kendisinin const olup olmad���n� fonksiyonun kendisinin bilmesine olanak yok
							   g�nderilen arg�man�n L value yada R value oldu�unu bilme olas�l���m�zda yok bu template o bilgiyi kaybediyor bu template i�inde g�nderilen arg�man�n
							   value kategorisine ba�l� bir kod yazamay�z �rne�in ald��� arg�man� perfect forward edemez ��nk� value kategorisi kayboluyor

	�RNEK:
		
		template <typename T>
		struct IsFloatingPoint : std::integral_constant<bool, 
				std::is_same_v<float, std::remove_cv_t<T>> || 
				std::is_same_v<double, std::remove_cv_t<T>> ||
				std::is_same_v<long double, std::remove_cv_t<T>>
				> {}; // SORU: bu template neden b�yle yaz�lmak yerine ba�ka �ekildede implemenete edilmiyor?
		
		bool ifadesinden sonraki virg�lden sonraki ifade bir sabit ifade sabit ifadenin de�eri true ise true_type'dan kal�t�m elde edece�iz false ise false_type'dan 
		
	�RNEK:generic programlama taraf�nda �yle durumlar var ki bir ko�ula ba�l� olarak iki farkl� t�rden birini kullanmam�z gerekiyor

		template <typename T>
		void func(T x)
		{
			sizeof(T) // �rne�in T t�r�n�n sizeof de�eri 2 ise short t�r�n� kullanmak istiyoruz 4 ise int t�r�n�
		}	
		
		template <typename T>
		void func(T x)
		{
			std::conditional_t<std::is_floating_point_v<T>, double,int> val {};
			std::cout<<typeid(val).name()<<'\n';
		}

		int main()
		{
			func(20);
			func(2.3);
		}

VARIADIC TEMPLATE(parameter pack)

	her hangi bir say�da template parametresi kabul edebilir yani �yle bir template olu�turabiliriz ki o template'den olu�turulan instantiationlar sanki 3 tane parametreisi varm�� gibi yada
	n tane template parametresi varm�� gibide kullan�labilecek

	template parametrelerinin say�s�n�n de�i�ebilece�ini compile timeda se�ilebilece�ini g�steren sentaks ��esine TEMPLATE PARAMETER PACK deniliyor
	
	template <typename ...Args> // Args yerine Types,Ts isimleride yayg�n olarak kullan�l�yor
	class Myclass {};

	int main()
	{
		Myclass<> m1;
		Myclass<int> m2;
		Myclass<int,double> m3;
		Myclass<int,double,long> m4;
	}

	�RNEK:

		template <int ...VALS> // non-type
		class Myclass {};

		int main()
		{
			Myclass<> m1;
			Myclass<1> m2;
			Myclass<1,3,5,7> m3;
		}

	�RNEK:

		template <typename ... Ts>
		void foo(Ts ...params) // e�er fonksiyonun parametre de�i�kenilerinden biri(genelde sonuncusu) template parametre paketini kullan�yorsa ve template parametre paketinden 
								  sonra ellipsis tokenini kullan�yorsa b�yle bir fonksiyonun template parametre paketinde ka� tane t�r varsa o kadar parametre de�i�keni var demektir

		foo(2, 3.4, 5L, "necati"); // ge�erli
		
		void foo(Ts& ...params) // e�er referans deklerat�r� olsayd� fonksiyonun parametre de�i�keni her biri L value ref olacakt� ve t�r ��kar�mlar�da referans olmas�na g�re yap�lacakt�

		int main()
		{
			int x = 5;
			double dval = 3.4;
			int a[5] {};

			foo(x,dval,a)  // foo<int,double,int[5]>(int&,double&, int(&r)[5])
		}

		void foo(Ts&& ...params) // universal reference olsayd� her hangi t�rden bir arg�man g�nderebilece�iz fonksiyonun b�t�n parametreleri universal ref olacak ve ald���m�z arg�manlar�n 
									hepsini
										a)perfect forward edebilece�iz
										b)value kategorisini ��renebilece�iz
										c)const olup olmad�klar�n� ��renece�iz

	�RNEK:sizeof... operat�r�nde ellipsis kulland���m�z zaman bu operat�r�n operand� olarak template parameter pack yada function parameter pack kulland���m�zda compile time sabiti olarak 
		 pakette ki ��e say�s�n� size_t t�r�nden elde ediyoruz
										
			template<typename ...Ts>
			void func(Ts ...args)
			{
				constexpr auto sz1 = sizeof...(Ts);
				constexpr auto sz2 = sizeof...(args);

				// her ikiside ge�erli ve her ikisininde de�eri ayn� ve compile time sabiti
	
			}
							
			int main()
			{
				func(2,6,7.8,"murat");
			}

	�RNEK:variadic parametre paketi tek parametre olmak zorunda de�il
		
		template<typename ...Ts>
		void func(int,int,Ts ...args)
		{
			constexpr auto sz1 = sizeof...(Ts);
			constexpr auto sz2 = sizeof...(args);

			// e�er fonksiyon b�yle bildirilseydi parametre paketinde ki ��e say�s�yla fonksiyonun parametre de�i�keninin say�s� ayn� olmayacakt�
			std::cout<<sz1<<" " <<sz2;
		}
				
		int main()
		{
			func(1,3,6,7); // 1 ve 3 1.ve 2.non-type arg�mana gidecek 6 ve 7 parametre paketine gidecek
		}

	variadic templatelerde en �nemli kavramlardan biri PACK EXPANSION(paketin a��lmas� yada geni�letilmesi)

		template <typename ...Ts> 
		class Myclass : public Ts... { // �yle ba�lamlar var ki o ba�lamlar s�z konusu oldu�unda derleyici pack expansion ifadesini ba�ka bir ifadeye d�n��t�r�yor
										  burda template parametre paketinden sonra ellipsis tokeni var e�er burda template parametre paketi expand edilmi�se derleyici
										  pack expansion ifadesini virg�llerle ayr�lan bir listeye d�n��t�r�yor
		
		};

		struct A{};
		struct B{};
		struct C{};

		Myclass<A,B,C> // derleyicinin olu�turdu�u Myclass s�n�f �ablonunun specializationu -> class Myclass : public A,public B,public C {};
	
	�RNEK:
		template <typename... Args>
		struct Nec {};

		template <typename ...Ts>
		void func(Ts... params)
		{
			Nec<Ts...> x; // pack expansion Nec<int, double, long>
		}

		int main()
		{
			func(2,5.9 , 56L); // T = int, double, long
		}

	�RNEK:
		
		struct A {void foo(int); };
		struct B {void foo(double); };
		struct C {void foo(long); };

		template <typename ...Ts>
		class Myclass : public Ts..{

			using Ts::foo ...; // derleyici bunu her bir taban s�n�f�n foo isimli fonksiyonu i�in bir using decleration'� olacak
			
		 };

		 int main()
		 {
			Myclass<A,B,C> m1; 

			m1.foo(12); // A s�n�f�n�n foo fonksiyonunu kullan�r�z
			m1.foo(1.2); // B s�n�f�n�n foo fonksiyonunu kullan�r�z
		 }
*/