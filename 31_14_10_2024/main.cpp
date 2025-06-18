/*

derleyicinin bir template koddan template specialization'� olu�turmas�na template instantiation deniliyor
specialization ile kar��t�rmayal�m specialization olu�an �r�n�n ismi derleyici template instantiation yapt���nda yani template'den kodu yazd���nda 
olu�an �r�n o template'in bir specialization'� yani derleyici template'i instantiation ederek template'in specialization�n� olu�turuyor

	
	TEMPLATE SPECIALIZATION OLU�TURMANIN YOLLARI
		1)implict
			derleyicinin durumdan vazife ��kartarak instantiation'� yapmas�

			template<typename T>
			T getMax(T x,T y)
			{
				return x > y ? x : y;
			}

			int main()
			{
				getMax(20,10); // derleyici bu fonksiyona �a�r� yap�ld��� i�in ve fonksiyon �ablonu oldu�u i�in �nce argument deduction yap�cak sonra substitution s�recini y�netecek yani
				template parametresine kar��l�k gelen template arg�man�n� yerine koyacak ve derleyici burda template'i instantiate ediyor derleyicinin burda template'i
				instantiate etmesi i�in bir talimat vermiyoruz ama  EXPLICIT TEMPLATE INSTANTIATION(hoca ileride de�inecekmi�) ile derleyiciye fiilen bir template'den 
				instantiotionu yapmas� i�in talimat veriyoruz
					template<typename T>
					T getMax(T x,T y)
					{
						return x > y ? x : y;
					}
					template double getMax<double>(double,double);
			}

		2)explicit


	C++20 standar�nda generic programlmaya ili�kin revolution eklemekler oldu bunlardan en iyi eklemelerden biri ABBREVIATED TEMPLATE SYNTAX(KISALTILMI� �ABLON SENTAKSI)
		void foo(auto x) 
		{

		}

		bu asl�nda bir function template b�yle yazmakla a�a��daki gibi yazmak ayn� anlamda
			template <typename T>
			void foo(T x); 

		D�KKAT:
			template <typename T>
			void func(T x,T y);

			void func(auto x, auto y); // �eklinde yazarsak buradaki x ve y farkl� template t�rlerinden olmu� olur yani sanki ��yle yazm�� gibi olur
			
				template <typename T,tyepname U>
				void func(T x,U y);

			auto func(auto x,auto y ) // fonksiyonun geri d�n�� de�eri auto return type fonksiyonun parametreli ABBREVIATED TEMPLATE SYNTAX


	bir s�n�f generic olmasada s�n�f�n static veya non-static member functionlarda function template olabilir

		class Myclass{
			public:
				
				template <typename T>
				void foo(T);

				template <typename T> // type cast operatorlerde template olabilir
				operator T()const{
					std::cout << "operator T \n";
					return 5; // derleme s�ras�nda d�n���m�n int t�r�ne yap�laca��n� belirtiti�imiz i�in geri d�n�� de�erini kullanmam�z gerekli
				}
		};

		int main()
		{
			Myclass m;

			m.foo(45); // derleyici s�n�fa int parametreli specialization olu�turuacak
			
			int x = m;
		}

	C++20 ile gelen �zellikleri saymazsak fonksiyonun geri d�n�� de�eri t�r� i�in ya 
		a)t�r� kendimiz belirliyoruz
			template <typename T>
			T foo(T) {} // T t�r�n� int olarak belirlersek geir d�n�� de�eri int olur

		b)geri d�n�� de�eri t�r�n�n trailing return type yap�lmas�
			hem generic olmayan kodda hemde generic kodda kullan�labiliyordu

			int ar[10];

			auto foo() -> int(&)[10]
			{
				return ar;
			}

			trailing return type kullanmazsak b�yle yazmam�z gerekirdi

				int (& foo())[10]
				{
					return ar;
				}

			�RNEK:
				class Myclass{
					public:
						class Nested{

						};

						Nested foo();
				};

				auto Myclass::foo()-> Nested // ismi nitelemeden yazabiliyoruz
				{
					return {};
				}

			�RNEK:
				struct Nec {
					std::vector<int> mvec;

					auto begin() const -> decltype(mvec.begin()) // fonksiyonun geri d�n�� de�eri mvec.begin() fonksiyon�u �a��r�ld���nda bu ifadenin t�r� neyse fonksiyonunda
																	geri d�n�� t�r� o
					{
						return mvec.begin();
					}

					decltype(mvec.end()) end() const // fonksiyonun geri d�n�� de�erini trailing return type yapmad�k mvec.end() fonksiyonun geri d�n�� de�eri yapt�k
														end() fonksiyonumuz const oldu�u i�in t�r uyu�mazl��� oldu
					{
						return mvec.end(); // bu fonksiyonu �a��rd���m�z zaman sentaks hatas� olur ��nk� mvec.end() fonksiyonu const de�il bu y�zden t�r uyu�mazl��� var
					}

				};

				bu �rneklerde trailing return type'� kullanmakla geri d�n�� de�erini do�rudan yazmak aras�nda sentaks a��s�ndan farkl�l�klar olu�mu� oluyor

	AUTO RETURN TYPE
		
		auto foo(int x)
		{
			// fonksiyonun geri d�n�� de�eri t�r� fonksiyonun return ifadesinden deduction yoluyla anla��lacak
		}

		
		�RNEK: 
			auto foo(int x); // sadece bildirim olursa derleyici ��kar�m yapamaz


			int main()
			{
				auto val = foo(5); // sentkas de�eri ��nk� geri d�n�� de�erini ��kar�m yapma imkan� yok direkt tan�m�n� yazmam�z laz�m
			}

			auto foo(int x)
			{
				return x * 5;
			}

		�RNEK: birden fazla return statement varsa return statementlarda geri d�n�� de�eri t�r�n�n ayn� olmas� gerek

			auto foo(int x)
			{
				if(x > 10)
					return 1;

				return 3.4; // sentaks hatas� fonksiyonun geri d�n�� de�eri int yani birden return statement varsa t�rleri ayn� olmak zorunda
			}

		�RNEK: fonksiyonun geri d�n�� de�eri sadece auto olmak zorunda de�il

			auto& foo(int x);
			auto&& foo(int x);
			const auto& foo(int x);
		
		�RNEK:
			auto foo(int& x)
			{
				return x; // auto type deductiona g�re fonksiyonun geri d�n�� de�eri int fonksiyonun geri d�n�� de�eri int& olmas� i�in geri d�n�� de�erini auto& yapmam�z gerekirdi
			}

		�RNEK:

			template<typename T>
			auto pri1(const T& x) -> decltype(std::cout << x); // fonksiyonun geri d�n�� de�eri ostream&
			{

				return std::cout<<x;
			}

			int main()
			{
				pri(10) << 40; // sentaks hatas� yok ��nk� fonksiyonun geri d�n�� de�eri ostream&
			}
		
			D�KKAT: e�er fonksiyon ��yle olsayd�
				template<typename T>
				auto pri1(const T& x)  // auto type deduction oldu�u i�in ve referans declerat�r� olmad��� i�in fonksiyonun geri d�n�� de�eri ostream
				{

					return std::cout<<x;
				}

				int main()
				{
					pri(10) << 20; // �imdi sentaks hatas� olur ��nk� fonksiyonun geri d�n�� de�eri ostream oldu�u i�in kopyalama semanti�i devreye girdi ve copy ctor delete edildi�i i�in
									  sentaks hatas� oldu
				}
	
PARAMETER PACK(parametre paketi) variadic template'de deniliyor
	modern C++ ile eklenen �ok �nemli ara�
	
	template <typename ...Types> // ellipsis token� ile kullan�l�yor
	class Myclass{

	};
	
CLASS TEMPLATE
	
	template<typename T>
	class Myclass{
		
		public:
			T get()const;
			void set(const T&);

		private:
			T mx;
			T* a[10];
	};


	int main()
	{
		Myclass<int> m1;
		Myclass<double> m2;

		m1 ve m2 birbirinden tamamen farkl� s�n�flard�r

		m2 = m1; // sentaks hatas�
	}

	s�n�f �ablonunun �ye fonksiyonunu s�n�f�n i�inde inline olarak yada class definition d���nda tan�mlayabiliriz
		template<typename T>
		class Myclass{
			public:
				T foo(T x);

		};

		template<typename T>
		T Myclass<T>::foo(T x)
		{

		}

	class scope i�inde s�n�f �ablonunun ismini do�rudan specialization ismi olarak kullanabiliriz
		template<typename T>
		class Myclass{
			public:
				Myclass<T> foo(Myclass<T>); 
				Myclass bar(Myclass) // ikiside ayn� anlamda yani class scope i�inde s�n�f �ablonunun ismini kullanmak ilgili specializationu kullanmak demek
				{
					Myclass m; // Myclass'�n int a��l�m� i�in bu yerel de�i�kenin t�r� Myclass'�n int a��l�m� t�r�nden olacakt�
				}
			};

			int main()
			{
				Myclass<int> x;
			}

			�RNEK:
				template<typename T,typename U>
				class Myclass{
					public:			
						void foo()
						{
							Myclass m;
							std::cout<<typeid(m).name()<<'\n';
						}
				};

				int main()
				{
					Myclass<int,long> x;

					x.foo();
				}
	
	specialization'�n kendisi class oldu�una g�re ba�ka template'de bir template arg�man� olarak'da kullan�labilir
		
		template<typename T,typename U>
		class Myclass{
			
			public:

		};
		
		int main()
		{
			std::vector<Myclass<int,double>>

			Myclass<Myclass<int,double>,Myckass<long,char>>
		}

	�RNEK:
		template<typename T,typename U>
		class Myclass;

		template<typename T>
		void func(T);

		int main()
		{
			Myclass<int,double> m;

			func(m);
		}

	�RNEK:
		template<typename T,typename U>
		class Myclass;

		template<typename T,typename U>
		void func(Myclass<T,U> p);

		int main()
		{
			Myclass<int,double> m;

			func(m);
		}

	�RNEK:
		template <typename T>
		class Myclass{
			public:
				T val{};
		};

		template<typename T>
		bool operator<(const Myclass<T>& lhs,const Myclass<T>& rhs)
		{
			return lhs.val == rhs.val;
		}

		int main()
		{
			Myclass<int> x,y;
			Myclass<double> d1,d2;

			x < y;
			d1 < d2;
		}

	�RNEK:
		template<typename T>
		class Myclass{
			public:
				template<typename U>
				void foo(U)
		};

		int main()
		{

			Myclass<int> m;
			m.foo(std::string{}); 
		}

	�RNEK:
		template<typename T>
		class Myclass{
			public:
				template<typename U>
				void foo(Myclass<U> p)
				{
					// *this'in t�r� Myclass<int> a��l�m�
					// p'nin t�r� Myclass<double> a��l�m�

					std::cout<<typeid(*this).name() <<'\n';
					std::cout<<typeid(p).name() <<'\n';
				}
		};
		
		int main()
		{
			Myclass<int> x;
			Myclass<double> y;

			x.foo(y);
		}
		
		�IKTI:
			class Myclass<int>
			class Myclass<double>

	�RNEK:
		template<typename T,typename U>
		struct Pair{
			
			Pair = default;
			template<typename X,typename Y>
			Pair(const Pair<X,Y>&);

			T first;
			U second;
		};

		int main()
		{
			Pair<double,double> pd;
			Pair<int,int> pi;

			pd = pi; // normalde farkl� s�n�flar ama yazd���m�z ctor member template oldu�u i�in bunu ge�erli hale getirebiliyoruz 
		}
*/