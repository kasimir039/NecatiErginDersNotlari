/*

operator overloadingten devam
	fonksiyonu �a��rd���m�z nesne bir r value expression ise kopyalama yerine ta��ma semanti�inden faydalanablir miyiz? EVET
		class Big{};
		class Nec
		{
			public:
				const Big& get_biggie()& 
				{
					return biggie;
				}
				const Big& get_biggie()&&
				{
					return std::move(biggie);
				}
			private:
				Big biggie;
	};

	baz� veri yap�lar�n� temsil eden soyutalam yap�ld���nda bellekte ard���kl�k olmas� s�z konusuysa subscript operat�r� array-like bir eri�imi
	�a�r��t�rd��� i�in overload ediliyor
		std::string[]
		std::array[]
		std::vector
		std::deque
		
		baz� iterator s�n�flar� iterator yine pointer like bir s�n�f fakat burada iterator dedi�miiz t�rlerin g�revi veri yap�lar�ndaki tutulan elemanlar�n konumunu tutmak
			vecotr<int>::iterator
		
		smart pointer s�n�f� ama� bir nesnenin bir kayna��n hayat�n� kontrol etmek
			unieque_ptr 

		associative containerlar
			bir key'den value'ya eri�ti�imiz veri yap�lar�
				std::set
				std::multiset
				std::map
				std::multimap
		
		unordered containerlar
			 elemanlar� s�ras�z (unsorted) olarak tutan ve hash tablolar� �zerinden eri�im sa�layan
				std::unordered_multiset
				std::unordered_multimap
				std::unordered_map
				std::unordered_set
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DEREFERENCING VE MEMBER SELECTIN ARROW OPERATOR
		a * b -> asteriks
		*ptr -> dereferencing
			
			DEREFERENCING
			unary operat�rd�r
			1)dereferenence operat�r�n�n operand� adres olmak zorunda
			2)operat�r�n olu�turdu�u ifade l value expression

			baz� s�n�flar pointer like s�n�flar
				class Iterator{};
					amac� bir veri yap�s�ndaki elenan�n konumunu tutmak
				
				�RNEK
				class SmartPtr{};
					dinamik �m�rl� nesnelerin hayatlar�n� kontrol etmek
				
				class Nec
				{
					public:
						void foo();
				};

				class NecPtr
				{
					public:
						NecPtr(Nec* p);
						Nec& operator*();
				};

				int main()
				{
					NecPtr = new Nec;
					(*ptr).foo();
					ptr.operator*().foo(); // iki �ekildede eri�ebiliriz
				}
				
				�RNEK
				int main()
				{
					std::vector<int> ivec{ 4,7,3,1,2,7,9 };
				
					auto iter = ivec.begin(); // dinamik dizide tutulan ilk eleman�n konumunu tutuyor
					std::vector<int>::iterator iter2 = ivec.begin(); // auto olmasayd� b�yle yazacakt�k
				
					std::cout << *iter << '\n'; // 4 ��kt�s� al�n�r
					std::cout<<++*iter<<'\n';// ilk eleman�n� de�erini 1 artt�r�r 5 yapar
				
					++iter; // bir sonraki eleman� g�sterir -> 7

					*iter = 987; // 7'nin de�erini de�i�tirir
					iter.operator*() = 777; // ikiside ayn� anlama geliyor
				
					std::cout << *iter << '\n';
				}

				baz� pointer-like s�n�flar ++ operat�r�n� overload ediyor

			MEMBER SELECTION
				binary operat�rd�r ama unary operat�r olarak overload edilir
				
				SmartPtr ptr;
				
				ptr->mx; // derleyici b�yle bir ifade ile kar��la�t���nda ptr'nin bir s�n�f nesnesi oldu�unu g�rd���nde ptr'nin ili�kin oldu�u s�n�f�n yani SmartPtr'nin member selection arrow 
				operat�r� olup olmad���na bak�yor 
				
				ptr.operator->() // derleyici s�n�f�n ok operator fonksiyonu oldu�unu g�rd� bu ifadeyi okun sol operand� yap�yor 
				ptr.operator->()->mx ifadesine d�n��t�r�yor bu y�zden member selection arrow operat�r�n�n geri d�n�� de�eri pointer olmal� ��nk� ancak bir pointer ok operand�n�n sol operand� olabilir

				�RNEK
				Mint* t�r�nden bir de�er sanki pointerm�� gibi davranacak bir s�n�f yaz�yoruz neden bunu yapal�m?
				MinPtr s�n�f� dinamik �m�rl� Mint nesnelerinin hayat�n� kontrol eden smart pointer s�n�f
				class MintPtr
				{
				public:
					explicit MintPtr(Mint* p) : mp(p) {} //  p'yi s�n�f�n veri elaman� olan mpde tutuyoruz
					~MintPtr()
					{
						if (mp)
						{
							delete mp; // mp'nin g�sterdi�i nesne i�in
						}
					}
				
				// e�er ama� dinamik �m�rl� bir mint nesnesini sadece bir pointer� g�stermesini sa�lamaksa kopyalamaya kar�� kapatmam�z gerek
					MintPtr(const MintPtr&) = delete;
					MintPtr& operator=(const MintPtr&) = delete;
				
					MintPtr(MintPtr&& other) : mp(other.mp)
					{
						other.mp = nullptr; // nesneyi yok etmiyor
					}
					MintPtr& operator=(MintPtr&& other)
					{
						delete mp;
				
						mp = other.mp;
				
						other.mp = nullptr;
					}
				
					Mint& operator*()
					{
						return *mp;
					}
				
					Mint* operator->() 
					{
						return mp;
					}
				
				private:
					Mint* mp;
				};
			
				int main()
				{

					MintPtr ptr{ new Mint(45) };

					std::cout << *ptr << '\n';
					++*ptr;

					std::cout << ptr->get() << '\n';
					std::cout << ptr.operator->()->get() << '\n'; // hi� bir anlam fark� yok

				}

			�ok b�y�k �o�unlukla member selection arrow operat�r�n�n geri d�n�� t�r� pointer t�r�nden olacak ama do�rudan pointer olmas� d���nda nadir olarak kullan�lsada ��yle bir kullan�mda var
				class A{
					public:
						void foo();
				};

				class B{
					public:
						A* operator->();
				};

				class C{
					public:
						B operator->(); // B* de�il B d�nd�r�yor 
				};

				int main()
				{
					C cx;
					cx->foo(); // derleyici bunu cx.operator->().operator->()->foo(); ifadesine d�n��t�r�yor
				}

				�rne�in Mint de�ilde Sint t�r�nden ba�ka bir s�n�f�n dinamik nesnelerinin hayat�n� kontrol eden bir s�n�fa ihtiyac�m�z olursa ne yapaca��z?
				burda i�imize yarayan durum generic programming burda derleyiciye diyece�iz ki derleyici ben sana ak�ll� pointer s�n�f� yazman�n yolunu ��retece�im
				�yle bir kod verece�im ki sen o kodu kullanarak Mint s�n��f t�r�nden nesneleri g�sterecek ak�ll� pointer s�n�f�n�da Sint s�n�f� t�r�nden dinamik �m�rl�
				nesneleri g�sterecek ak�ll� pointer s�n�f�n�da bizim verdi�imiz kal�ba g�re kodu yazacaks�n yani s�n�flar�n kodunu biz yazmayaca��z ama s�n�f�n kodunu yazd�racak
				kodu biz yazaca��z 

				template<typename T>
				class SmartPtr {
					// T t�r� i�in Mint'i kullan desek derleyici T yerine Mint s�n�f�n� kullanarak bir s�n�f yazacak
				public:
					explicit SmartPtr(T* p) : mp(p){}
					~SmartPtr()
					{
						if (mp)
						{
							delete mp;

						}
					}
					SmartPtr(T&& other) mp(other.mp)
					{
						other.mp = nullptr;
					}
					SmartPtr& operator=(SmartPtr&& other)
					{
						delete mp;
						mp = other.mp;
						other.mp = nullptr;
					}
					T& operator*()
					{
						return *mp;
					}

					T* operator->()
					{
						return mp;
					}
				private:
					T* mp;
				};

				int main()
				{

					SmartPtr<Mint> ptr{ new Mint(45) };

					std::cout << *ptr << '\n';
					++*ptr;

					std::cout << ptr->get() << '\n';
					std::cout << ptr.operator->()->get() << '\n'; // hi� bir anlam fark� yok

				}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	FUNCTION CALL OPERATOR
		C de foo(4) �eklinde bir ifade g�rsek 
		1)foo ger�etken bir fonksiyon ismidir
		2)foo nun function macro olmas�
		3)foo nun bir function pointer variable olmas�  
			void(*foo)(int) = &bar;
		C++ da ise C de ki senaryolar hala devam etmekte birlikte
			foo bir s�n�f t�r�nden nesne olabilir
			Nec foo;
			fonksiyon �a�r� operat�r�n�n oprand� oldu�u i�in foo nun �ye fonksiyonu olan function call operat�r�n� �a��r�r foo nun ili�kin oldu�u Nec s�n�f�
			fuonksiyon �a�r� operat�n� overlaod etmi�tir fonksiyon �a�r� operat�r�n� overload etti�i i�in kendisi bir s�n�f nesnesi olmas�na ra�men
			fonksiyon �a�r� operat�r�n�n operand� olabilen s�n�flara FUNCTOR CLASS yada FUNCTION OBJECT
			foo.operator()(4) olarak �a��r�labilir
		fonksiyon �a�r� operat�r�n�n operand� oldu�unda bir fonksiyonun �a��r�lamas� s�z konusuysa bu anlamda kullan�lan terim CALLABLE

		class Myclass {
		public:
			int operator()(int x)
			{
				std::cout << "Myclass::operator()(int x) x = " << x << '\n';
				std::cout << "this = " << this << '\n';
				return 42;
			}

			// parametre alabilir const yada non-const olabilir

			// fonksiyonun geri d�n�� de�eri t�r�nde k�s�tlama yok

			// birden fazla function call operator overloadingi olabilir

			// sadece bu operator fonksiyonu default argument alabilir

			// double parametreli bir function call operator daha olsayd� derleyici hangi fonksiyonu �a��raca��n� founction overlaod resolutionda analyacakt�

			int operator()(double x)
			{
				std::cout << "Myclass::operator()(int x) x = " << x << '\n';
				std::cout << "this = " << this << '\n';
				return 42 * 0.5;
			}

		};

		int main()
		{
			Myclass m;
			
			std::cout << "&m = " << &m << '\n';
			
			auto x = m(25);
			std::cout << "x = " << x << '\n';

			auto y = m(2.5);
			std::cout << "y = " << y << '\n';

		}

		SORU:peki function call operator ne i�e yar�yor?
			esas faydas� generic programlamada olacak

			operaor() fonkaiyonu s�n�f nesnesi i�in �a��r�l�yor ve �a�r�n�n yap�ld��� s�n�f nesnesi o s�n�f�n ne anlama geldi�ine g�re farkl� farkl� statete olabilir
			bu state s�n�f�n private veri elemanlar�ylada temsil edilebilir s�n�f�n mx isimli veri eleman� olsayd� operator() fonksiyonunda mx'i kulland���m�zda bu fonksiyon hangi nesne i�in �a��r�l�rsa
			o nesnenin mx'ini kullanm�� olurduk biz �yle bir fonksiyon olu�turmu� oluoruz fonksiyonun kendidi adete bir state sahip yani fonksiyona bir arg�man g�ndermeden fonksiyonun
			zaten bir state'i var
			
			�yle bir fonksiyon olsun ki o fonksiyon verilen bir aral�kta rastgele bir say� �retsin mesela 20 ve 50
			ama biz yine ayn� fonksiyona 1000 2000 aral���nda rastgele say� �retmesini talep edebilece�iz b�yle bir senaryoyu ger�ekle�tirmenin en pratik yolu 
			bunu bir s�n�f olarak tasarlamak aral�k ��elerini s�n�f�n private veri elemanlar� yapmak s�n�f nesnesinin contrcut ederken ctoru kullanacak user codedan aral�k de�erlerini
			arg�man olarak almak ve s�n�fa bir fonksiyon �a�r� operat�r� tan�mlamak ve bu fonksiyonda s�n�f�n veri elemanlar�n� kullanacak

			class Random
			{
			public:
				Random(int low, int high) : mlow(low), mhigh(high) {}
				int operator()()
				{
					++mcount;
					return rand() % (mhigh - mlow + 1) + mlow;
				}

				int get_count()const
				{
					return mcount;
				}

			private:
				int mlow, mhigh,mcount{};
			};

			int main()
			{
				Random rand1{ 42,87 };

				for (int i = 0; i < 5; ++i)
				{
					std::cout << rand1() << ' ';
				}
				std::cout<<rand1.get_count() << " sayi uretildi\n";

				std::cout << '\n';


				Random rand2{ 8764,8923 };
				for (int i = 0; i < 10; ++i)
				{
					std::cout << rand2() << ' '; // bu nesnede kendi stateine sahip
				}
				std::cout<<rand2.get_count() << " sayi uretildi\n";


			}

			void func(Random rx){
				rx(); // b�yle bir fonksiyonumuz olsa rx'i kullanarak rastgele bir say� olu�tursak func fonksiyonu hangi aral�kta rastgele say� �retece�ini bilmiyor
				onu bilen parametreye g�nderilen Random nesnesinin kendisi
			}
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	TYPE CAST OPERATOR FUNCTIONS
		user defined conversion kategorsindedir

		class Nec{
			public:
				operator int()const // s�n�f�n stateini de�i�tirmedi�i i�in const yapt�k
				{
					std::cout<<"Nec::operator int()\n";
					return 4; 
				}
		};

		int main()
		{
			Nec mynec;
			int ival{};

			ival = mynec; // derleyi operator int fonksiyonuna implicit conversion olarak �a�r� yapt� yani asl�nda ival'e myneci de�il mynec'in
							operator int fonksiyonuna yap�lan �a�r�dan elde edilen geri d�n�� de�erini atam�� olduk	ival'e asl�nda 4 de�erini atam�� olduk

			
			ival = mynec.operator int(); // ikisinide yazmak ayn�

		}

		burda bir istisna var genelde fonksiyonlar�n bildirimnde yada tan�m�nda fonksiyonun geri d�n�� de�erini yazmam�z gerekir t�r d�n��t�rme operat�r fonksiyonlar�n�n ismi 
		operat�r keyword�n� izleyen d�n��t�r�lecek hedef t�r �rne�in operator int() hedef t�r k�sm�nda hi� bir k�s�tlama yoktur her hangi bir t�r olabilir
		geri d�n�� de�eri t�r�n�n bo� b�rak�lmas� geri d�n�� de�erinin olmamas� anlam�na gelmiyor gereksiz yere tekrardan ka��n�ld���n� i�in yaz�lm�yor hedef t�r ne ise fonksiyonun heri d�n�� de�eri t�r�

		conversion ctorda oldu�u gibi bu d�n���m�n yap�lmas� gerekti�i durumlarda bu d�n���mleri �tr�l� olarak d�n���m� yapcak buda �ok b�y�k bir risk olu�turuyor
		ya yanl��kl�kla bir kod yazarsak dilin kurallar� gere�i o fonksiyon �a��r�l�rsa? b�y�k bir risk olu�turur ve e�er bir d�n���m �rt�l� olarak �nce standart d�n���m sonra user defined conversion
		olarak yap�l�yorsa derleyici bu d�n���m� yapmak zorunda yada �nce user defined conversion sonra standart conversion uygulanarak yap�l�yorsa derleyici bu d�n���m�
		yapmak zorunda 
			class Nec {
			public:
				explicit operator int() const // istenmeyen d�n���mlerin implicit olarak yap�lmas�n� istemiyorsak explicit olarak bildirmemiz gerekir
				{
					std::cout << "operator int()\n";

					return 1;
				}

			};

			int main()
			{
				Nec mynec;

				int ival{};

				ival = static_cast<int>(mynec); // t�r d�n��t�rme operator int fonksiyonu �a��r�l�r
			};
		
		SORU:Ba�ka bir s�n�fa d�n���m yapabilir miydik? EVET
			class Erg{};

			class Nec{
				public:
					 operator Erg()const;
			};

			int main()
			{
				Erg erg;
				Nec mynec;

				erg = mynec; // Nec t�r� Erg t�r�ne d�n���yor
				erg = mynec.operator Erg(); // ikiside ayn� anlama geliyor
			}

		SORU:t�r d�n��t�rme operat�rlerinde hedef t�r function pointer t�r� olabilir mi? EVET
			usin fptr = int(*)(int);
			class Nec{
				operator fptr()const;
			}
			 
		t�r d�n��t�rme operat�rlerini neden kullan�r�z?
			baz� s�n�flarda zaten do�al olarak interface'e bizim eklemek istedi�imiz bir api 
				class Fraction{
					public:
						Fraction(int nom = 0,int den = 1) : m_nom(nom),m_den(den){}

						explicit operator double() const
						{
							return static_cast<double>(m_nom) / m_den;
						}
					private:
						int m_nom, m_den;
				};

				int main()
				{
					Fraction f1(3,7);
					Fraction f1(3);
					Fraction f1;

					double dval = static_cast<double>(f1);

					std::cout<<"dval =" << dval<<'\n';
				}	

			baz� s�n�flar�n isimlendirilmi� d�n���m fonksiyonlar� var
			int main()
			{
				std::string{"meric turkcan"};

				const char* p = str // str yi const char* t�r�ne d�n��t�r�cek do�rudan bir operat�r fonksiyonu yok

				p = str.c_str(); // isimlendirilmi� bir fonksiyonla bu d�n���m yap�labiliyor ama operator fonksiyonu ilede yap�labilirdi ama b�yle tercih edilmi�

			}

			�RNEK 2
				functional k�t�phanesinde tan�mlana reference wrapper ad�nda generic bir s�n�f var

				int main()
				{
					using namespace std;
					
					int x = 10;
					reference_wrapper r = x; // asl�nda kendisi bir referans de�il ama referans olarak kullan�l�yor �stelik re-bindble normalde referenslar tekrardan ba�lanamaz
					reference wrapper s�n�f� bir pointer� sarmal�yor ve biz b�yle bir nesne olu�turdu�umuzda asl�nda ctor s�n�f�n ver eleman� olan pointera x'in adresini yerle�tirmi� oluyor

					++r; // nas�l oluyorda bu ifadeyi yazd���m�zda x de�i�kenini de�eri 11 oluyor?
					reference wrapper s�n�f�n�n t�r d�n��t�rme operat�r fonksiyonu var bu �rnek i�in int& t�r�ne d�n��t�r�yor 
					derleyici bu ifadede ++r.operator int&() fonksiyonuna �a�r� yap�yor sarmalad��� pointer�n g�terdi�i nesneye referans d�nd�r�yor

				}

		nerelerde logic yorumlama yap�l�yor?
			!exp
			exp1 && exp2
			exp1 || exp2
			exp ? op2 : op3
			if(expr)
			while(expr)
			do while(expr)
			for(;expr;)

		SORU:
			class Sint{

			}

			class SmartPtr{
			}
			
			int main()
			{
				Sint i;
				SmartPtr ptr;

				if(i) {} 
				if(ptr) {} //  her ikisindede b�yle ifadelerde bool t�r�ne bir d�n���m bekleniyor logic ifade beklenen yerde kullanmak i�in operator bool fonksiyonunu tan�mlarsak bunlar� legal k�lm�� oluruz
				di�er derste hoca anlatacak
			}
*/