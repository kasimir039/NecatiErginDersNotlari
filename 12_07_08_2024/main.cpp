/*
modern cpp �ncesinde big three terimi vard�

destructor
copy constructor
copy assignment operator
 
bu fonksiyonlardan birini �zellikle destructor�n yaz�m�n� derleyiciye b�rakmak yerine kendimiz yapmak zorundaysak di�er iki fonksiyonuda implemente etmeliyiz
��nk� destructor� yazma nedenimiz tipik olarak bir kayna��n geri verilmesi bu durumda copy ctor ve copy assignment operator function derleyici taraf�ndan yaz�l�rsa onlar�n kodu uygun olmayacak

modern cpp ile big five terimi geldi
	destructor
	copy ctor
	copy assignment operator
	move ctor
	move assignment operator

hoca bu overloading tipini bize tekrar an�msat�yor
	class Nec {};

	void foo(Nec&); // l value &
	void foo(const Nec&); // const l value &
	void foo(Nec&&); // r value &
	void foo(const Nec&&); // const r value & tipik olarak bir i�e yaram�yor semantik kar��l��� �ok nadir

	�retimde �o�unlukla kar��m�za ��kacak overloading 
		void foo(const Nec&); // const l value &(l value arg�manlar� al�r)
		void foo(Nec&&); // r value & (r value arg�manlar� al�r)

		Nec bar();
		Nec&& baz(); // X value(geri d�n�� de�eri R value olan fonksiyonlara yap�lan �a�r� ifadeleri)


		int main()
		{
			Nec mynec; // l value expression

			Nec{}; // r value expression temporary object s�n�f t�r�nden nesne anlam�na geliyor fakat ortada o nesnenin ismi yok sadece s�n�f�n ismi var(ayr� bir ba�l�k alt�nda incelenecek)

			foo(mynec); // const Nec& �a��r�l�r
			foo(std::move(mynec)); // Nec&& �a��r�l�r
			foo(Nec{}) // Nec&& �a��r�l�r
			foo(bar()); // Nec&& �a��r�l�r
			foo(baz()); // Nec&& �a��r�l�r

			burda void foo(Nec&&) overloadunu silsek bile sentaks hatas� olmaz ��nk� foo fonksiyonu const Nec& oldu�u i�in hem l value hemde r value ile �a��r�labilir buna pop�ler olarak FALL BACK deniliyor
			
			}	

		void bar(const Nec&&); 
		
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MOVE CONSTRUCTOR VE MOVE ASSIGMENT
	�yle durumlar var ki koda bakarak bir s�n�f nesnesinin art�k kullan�lma olana��n�n olmad���n� o nesnenin kullanbabilecek bir kodun s�z konusu olmad���n� derleyici anlayabilir
	bizde kod bakarak anlayabiliyoruz b�yle bir durumda bir s�n�f nesnesi varken �rne�in string s�n�f�m�z onun de�eri iile ba�ka bir s�n�f nesnesini hayata getirmek istedi�imizde MODERN CPP �ncesi copy ctoru kullan�rken
	de�erini kullanaca��m�z de�erini alaca��m�z s�n�f nesnesinin hayat� bitecek olmas�naa kar��n onun kayna��n� yine bir �ok durumda kopyal�yorduk fakat MOVE CTOR ile derleyiciye �unu demi� oluyoruz

		sen s�n�f nesnesi seni kullanacak ba�ka bir kod yok sen gidicisin :D o zaman ben neden senin kayna��n� kopyalayay�m? ben senin kayna��n� devralay�m kayna��n� �alay�m(TO STEAL THE RESOURCE)

	HOCANIN ��Z�M� �ZER�NE(L�TFEN ��Z�ME BAKIP B�R YANDAN BUNU OKUYUN)string.png

		bizim yazd���m string s�n�f�ndan bir nesnemiz var bu s�n�f nesnesinin hayat� bitecek
		hayat� biterken bunun i�in destrutor �a��r�lacak dynamic allocate edilmi� kayna�� geri vericek
		ama biz bu s�n�f nesnenini de�eri ile ba�ka bir s�n�f nesnesi olu�turmak istiyoruz peki bu neden kayna��n� geri versin ki?
		onun kayna��n� biz elde edelim �alm�� olal�m yani bizim s�n�f nesnemiz di�er s�n�f nesnesinin kayna��n� edinmek i�in bu sefer ger�ekten pointer� kopyalas�n
		ama burda bir problem var 
			1)derleyicinin koda bakarak buradaki s�n�f nesnesinin hayat�n�n bitecek olu�unu anlamas� gerekiyor 
			2)alternatif ba�ka bir kodu se�mesi gerekiyor

		e�er kopyalama hayat� devam edecek bir nesne kaynak olarak kullan�lmas� suretiyle yap�l�yorsa copy ctor

		ama kopyalama hayat� bitecek olan kullan�lmayacak olan bir nesneden yap�l�yorsa deep copy yapmak yerine ger�ekten pointer� kopyalayacak bir kodu se�memiz gerekiyor
		MODERN CPP �ncesinde bunu yapma imkan�m�z yoktu ve MODERN CPP ile bunun rahatl�kla implemente edilmesini sa�layan ba�lay�c� araa� R value &
		
		bir problem daha var yeni hayata getirece�imiz nesne di�erinin pointer�n� kopyalad� ama de�erini ald��� nesne i�in destructor �a��r�ld���nda yine o kayna�� geri verece�i i�in dangling pointer olmu� oluyor
		�yle bir fonksiyon yazabilmeliyiz ki di�er nesnenin kayna��n� �almakla birlikte yani pointer�n� kopyalamakla birlikte di�er nesneyi �yle bir state sokmas� gerekiyor ki destructor �a��r�ld���nda 
		kyna��n�n �al�nd���n�n fark�nda olacak ve kayna�� geri vermeyecek bunu sa�layan fonksiyon MOVE CTOR 

		iki tane nesne varsa kendisine atama yapaca��m�z nesnenin alaca�� yeni de�eri temsil eden di�er nesnenin art�k kullan�labilir olmad���n� biliyorsak yine nesnenin kayna��n� �alabiliriz

		move ctor ve move asignment �yle fonksiyonlar ki copy ctor ve copy assigmenta g�re yapt�klar� i� kopyalama yapmamak(sdeep copy yapmamak) di�er nesnenin kayna��n� �almak ve nesnenin destructor 
		�a��r�ld���nda kayna��n�n geri verilmemesini sa�lamak

		peki bunu nas�l yapaca��z
			ba�ka bir kodun kullan�lma ihtimali olmayan hayat� bitecek nesneler dilin kurallar�na g�re bu ifadeler(r value)
			iki tane constructor overloadu olsa biri l value di�eri r value arg�manlar� alsa r value de�eri alan overload referans�n ba�land��� nesnenin hayat�n�n bitece�ini
			ba�ka bir kodun ona ihtiya� duymad���n� bilecek ve onun kayna��n� �alacak

		hem move ctor hemde copy ctor var ise l valuelar i�in copy ctor r value arg�manlar i�in move ctor �a��r�lacak
		move ctor bir nedenden yok ise hem r value hemde l value i�in copy ctor �a��r�lacak fall back terimini i�te burada kullan�yoruz
			Myclass(const Myclass&);
			Myclass(Myclass&&);

			Myclass& operator=(const Myclass&); // l valuelar i�in 
			Myclass& operator=(Myclass&&); // r valuelar i�in

			kopyalama yerine ta��ma daha fazla yararl� olur mu?
				s�n�fa g�re de�i�ir

			move constructor�n avantaj sa�lamas� i�in ortada bir kayna��n olmas� o kayna�� kopyalama altarnatifine kar�� kopyalamay� tamamen ortadan kald�r�p o kayna�� �alma alternatifini kullanm�� oluyoruz
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		DERLEY�C�N�N YAZDI�I MOVE CTOR

			class Myclass
			{
			public:
				Myclass(Myclass&& r) : ax(std::move(r.ax)), bx(std::move(r.bx)), cx(std::move(r.cx))
				{
				 // bu ifadeler isim formunda oldu�u i�in normalde l value olmu� oluyor compile timeda r value expression olarak kullan�lmas�n� sa�layan move fonksiyonudur
				}
			private:
				A ax;
				B bx;
				C cx;
			};

			Rasulun sorusu �zerine
				class Nec
				{
					private:
						std::string str;
						std::vector<int> vec;

						// bu s�n�f�n move ctor�n� biz yazmasak derleyicinin yazs�d� move ctor bir nec nesnesini hayata getiren bir r value nec nesnesi oldu�unda
						derleyicinin yazd��� move ctor �a��r�lacakt� derleyicinin yazd��� move ctor nec'in str eleman�n� string s�n�f�n�n move ctoru ile hayata getirecekti
						yani hayata gelen nec nesnesi kaynak olarak kullan�lan nec nesnesinin stringinin kayna��n� �al�cakt� bizim bu durumda bir �ey yapmam�z gerekmiyor AMA!
						e�er handle elemanlar varsa ta��ma semanti�inin implementasyonunu kendimiz yapmal�y�z
				}
				
				copy ctorun derleyici taraf�ndan yaz�lmas� e�er s�n�f�n elemanlar� handle ise felakete neden oluyor
				ama s�n�f�n move ctoru olmamas� bir felaket senaryosu de�il sadece efficiently(performans a��s�ndan zarar� var) 
					
			class String
			{
			public:
				String(const String& other) : mlen(other.mlen)
				{
					mp = static_cast<char*>(std::malloc(mlen + 1));

					if (!mp) {
						std::cerr << "cannot allocate memory\n";
						std::exit(EXIT_FAILURE);
					}

					strcpy(mp, other.mp);
				}
				String(String&& other) : mlen(std::move(other.mlen)),mp(std::move(other.mp)) 
				{
					// other'�n ba�land��� nesne i�inde destructor �a��r�lacak mp isimli pointer burda nullptr olmu� olmuyor 
					destructor �a��r�ld��� zaman bizim �ald��m�z kayna�� geri vermemesi laz�m 
					other.mp = nullptr;
					other.mlen = 0; // bunun hakk�nda hoca daha sonra konu�acak
				}
				String(const char* p) : mlen(std::strlen(p))
				{
					mp = static_cast<char*>(std::malloc(mlen + 1));

					if (!mp) {
						std::cerr << "cannot allocate memory\n";
						std::exit(EXIT_FAILURE);
					}

					strcpy(mp, p);
				}
				~String()
				{
					if (mp)
						std::free(mp);
				}
				void print() const
				{
					std::cout << '['<<mp << "]\n";
				}

				size_t length()const
				{
					return mlen;
				}
			private:
				size_t mlen;
				char* mp;
			};

			void foo(String s)
			{
				std::cout << "foo cagrildi\n";
				s.print();
				(void)getchar();
			}

			int main()
			{
				String str(String{"bugun yine cok sicak hava vardi"}); // temporary object oldu�u i�in move ctor �a��r�l�r			
				
			}
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	HOCANIN M�LAKATTA TA�IMA SEMANT��� �LE �LG�L� SORDU�U SORU
		class Myclass{};

		void func(Myclass&&){}

		int main()
		{
			Myclass m;

			func(std::move(m)); // bu sat�rdan sonra m nesnesinin kayna�� �al�nm��m�d�r?
				TAB�K� HAYIR B�R NESNEY� B�R SA� TARAF REFERANSINA BA�LAMAK ONUN KAYNA�INI �ALMAK DE��LD�R
				FUNC ���NDE �YLE B�R �MPLEMANTASYON OLMALI K� BU SA� TARAF REFERANSININ BA�LANDI�I NESNES�N KAYNA�INI �ALMALI BUNUNDA 2 TANE YOLU VAR
				1)Myclass nesnesini hayata getirece�iz
				2)Myclass nesnesine atama yapaca��z
					void func(Myclass&& r)
					{
						Myclass mx = std::move(r); // bu fonksiyon nesnenin kayna��n� �alar
					}
		}
			iki ayr� overload olsa
				void func(Myclass&&)
				{  
					Myclass mx = std::move(r); // r value de�erler i�in ta��ma yapmas�n� sa�l�yoruz
				}
				void func(Myclass&)
				{
					Myclass mx = r; // l value de�er i�in kopyalama yapmas�n� sa�l�yoruz
				}

		move ctorun implemente edilmesi i�in bir fayda sa�lamas� gerekiyor	
			class Myclass
			{
				private:
					int ar[1000]; // bu s�n�f i�n move ctor yazman�n bir anlam� yok b�yle olmas� efficiently a��s�ndan bir fayda sa�lamaz ��nk� derleyiciyede b�raksak burda bu dizi kopyalanacak
					
					std::string* p; // dinamik olarak allocate edilmi� bir bellek blo�undaki string nesnenelerinin bulundu�u bellek blo�unun adresini tutuyor olsayd�
					move ctor burda hayati �nem ta��rd� ��nk� kopyalama ile yetinirsek kopyalama yoluyla hayata getirdi�imiz nesne gidecek ayr� bir bellek alan� allocate edicek
					ve orda string nesnenelerini olu�turacak yani di�erinin allocate etti�i bellek blo�unda 10 bin string nesnesi varsa bizim hayata getirdi�imiz nesnede 10bin tane string nesnesini hayata getirecek
			}
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	DERLEYICININ YAZDI�I MOVE ASSIGMENT
		class Myclass
		{
			public:
				Myclass(const Myclass& r) : ax(r.ax),bx(r.bx),c(r.cx){}
				Myclass(Myclass&& r) : ax(std::move(r.ax)), bx(std::move(r.bx)), cx(std::move(r.cx)) {}
				Myclass& operator=(const Myclass& r)
				{
					ax = r.ax;
					bx = r.bx;
					cx = r.cx;,
					return *this;
				}
				Myclass& operator=(Myclass&& r)
				{
					ax = std::move(r.ax);
					ax = std::move(r.bx);
					ax = std::move(r.cx);
					return *this;
					D�KKAT:string s�n�f� i�in yazd��m�z other.mp = nullptr di�er nesnenin pointer�n� nullptr yapabilmemiz i�in referans de�i�kenin const olmamas� gerekiyor o y�zden MOVE CTOR yada MOVE ASSIGMENT parametreleri const olmayan referans

				}
			private:
				A ax;
				B bx;
				C cx;
		};

		class String
		{
		public:
			String(String&& other) : mlen(other.mlen), mp(other.mp)
			{
				other.mp = nullptr;
				other.mlen = 0;
			}

			String& operator=(String&& other)
			{
				if (this == &other)
					return* this;

				free(mp); // bunu yapmasak kaynak s�z�nt�s� olurdu ��nk� pointera yeni de�er atanmas� o pointer�n g�sterdi�i kayna��n geri verildi�i anlam�na gelmiyor
				mlen = other.mlen;
				mp = other.mp;

				other.mp = nullptr;
				other.mlen = 0;

				return *this;

			}

		private:
			size_t mlen;
			char* mp;
		};
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		MOVED FROM STATE/OBJECT
			nesne hala hayatta ama kayna�� �al�nm�� anlam�na geliyor 

			int main()
			{
				std::string str(10000,'A'); // 10000 tane A karakteri i�eren string nesnesi

				std::string sx = std::move(str); // str nesnesinin kayna��n� �ald�k

				standart k�t�phanenin s�n�flar� kayna�� �al�nm�� nesneler i�in �u garantileri veriyor
				
				1)kayna�� �al�nm�� bir nesne valid statete olacak
					s�n�f�n invariantlar� korunmu� olacak(nesnenin de�erinin uzunlu�u gibi)
				2)destructor�n �a��r�lmas� herhangi bir soruna yol a�mayacak
					yani destructor �a��r�lmas� durumunda bir problem olmayaca�� anlam�na geliyor

				3)nesneye yeni bir de�er atayarak tekrar kullanabiliriz
					
				nesnenin de�eri garanti alt�nda de�il valid statete olmas� ba�ka nesnenin de�erinin ne oldu�u ba�ka

				moved from statete ki nesnenin de�erinin ne olaca�� derleyiciye ba�l� ama nesne ge�erli bir durumda oldu�u i�in o de�eri gerekirse kullanabiliriz

			}

			valid state
				string str{"oguzhan esin ve fatih akgul c++ programcilari"};

				auto s = std::move(str);

				std::cout<<str.length(); // str nesnesinin uzunlu�u 0 olacak

				if(str.empty())
					std::cout<<"str nesnesi bo�\n";
				else
					std::cout<<"str nesnesi dolu\n";

				std::cout<<"(" << str << ")\n"; // str nesnesinin i�eri�i belirsiz ama valid state 

				str = "baris doga yavas"; // burda her hangi bir tan�ms�z davran�� yok

			s�n�f nesnelerinin kopyalanmas�nda bir sorun yoksa bunlara COPYABLE s�n�flar denebilir ama baz� durumlarda s�n�flar�n kopyalanmas�n� engellemek istiyoruz
				nedeni kopyalaman�n o s�n�f i�in anlaml� bir yap� olu�turmamas� yani semantik bir kar��l���n�n olmamas� problem domaininde temsil ettikleri kavram i�in zaten kopyalama bir anlam ta��m�yor 

				ifstream ifs"text.txt"};
				if(!ifs)
				{
					std::cerr<<"cannot open file\n";
					return 1;
				}

				std::vector<std::string> svec;

				std::string sline;

				while(getline(ifs,sline))
				{
					svec.push_back(sline); // burda sline nesnesinin kopyalanmas� mant�kl� bir durum de�il b�yle durumlarda s�n�f�n copy ctoru ve copy assignment operator� delete ediliyor b�yle s�n�flara NON-COPYABLE s�n�flar deniliyor
				}

				Nec(const Nec&) = delete;
				Nec& operator=(const Nec&) = delete;					
				
				kopyalama olmayan(non-copyable) sadece ta��nabilir olan s�n�flara MOVE ONLY CLASS deniyor
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DERLEY�C� HANG� DURUMLARDA SINIFIN SPECIAL MEMBER FUNCTIONLARINI IMPLICITLY DECLARE EDER(DOSYALARA KOYDU�UM G�RSEL� �NCELEY�N L�TFEN)
		
		S�n�fta herhangi bir special member function yoksa derleyici hepsini impilictly declared olarak default bildirir

		class Myclass
		{
			Myclass() = default;
			~Myclass() = default;
			Myclass(const Myclass&) = default;
			Myclass(Myclass&&) = default;
			Myclass& operator=(const Myclass&) = default;
			Myclass& operator=(Myclass&&) = default;

		} // derleyicinin yapt��� implicitly olarak budur
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa special member function olan yada olmayan her hangi bir constructor bildirilirse derleyici default contructoru
		implictly declared etmez default constructor not declared durumuna d��er di�er special member functionlar hala implicitly declared edilmi� haldedir
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa default constructor user declared edilmi�se di�er specail member functionlar hala implicitly declared edilmi� haldedir
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa Destructor user declared olarak bildirilirse
			default contructor derleyici taraf�ndan implicitly declared olarak default edilir
			copy constructor derleyici taraf�ndan implicitly declared olarak default edilir ->istenmeyen durum deprecated
			copy assginment operator derleyici taraf�ndan implicitly declared olarak default edilir ->istenmeyen durum deprecated

			move contructor olmaz/not declared
			move assignment operator olmaz/not declared

			Destructor user declared oldu�u zaman move constructor ve move assignment operator default edilmez
			ve bu deprecated(gelecekti standartlarda bu tamamen sentaks hatas�na yol a�abilir) edilmi�tir asla olmamas� gereken bir �ey
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa copy constructor user declared olarak bildirilirse
			copy assignment operator derleyici taraf�ndan implicitly declared olarak default edilir ->istenmeyen durum deprecated
			destructor derleyici taraf�ndan implicitly declared olarak default edilir

			default contructor olmaz/not declared
			move constructor/not declared
			move assignment operator olmaz/not declared
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa copy assignment user declared olarak bildirilirse
			default contructor derleyici taraf�ndan implicitly declared olarak default edilir
			destructor derleyici taraf�ndan implicitly declared olarak default edilir
			copy contructor derleyici taraf�ndan implicitly declared olarak default edilir ->istenmeyen durum deprecated

			move constructor olmaz/not declared
			move assginment operator olmaz/not declared
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa move constructor user declared olarak bildirilirse
			destructor derleyici taraf�ndan implicitly declared olarak default edilir

			move assignment operator olmaz/not declared
			default contructor olmaz/not declared
			copy constructor var ama/delete edilmi�tir
			copy assignment var ama/delete edilmi�tir
		--------------------------------------------------------------------------------------------------------------------------------------------------
		S�n�fa move assignment operator user declared olarak bildirilirse
			default constructor derleyici taraf�ndan implicitly declared olarak default edilir
			destructor derleyici taraf�ndan implicitly declared olarak default edilir

			move constructor olmaz/not declared
			copy constructor/delete edilmi�tir
			copy assignment operator/delete edilmi�tir
		
	Bir s�n�fa default ctor olmayan her hangi bir constructor bildirirsek derleyici default ctoru bildirmez(not declared)
	
	Bir s�n�f�n her zaman destructor� vard�r biz bildirirsek user declared bizim bildirmedi�imiz b�t�n durumlarda implicitly declared
			
	eskiden big three denilen
		destructor
		copy ctor
		copy assignment
			bunlardan her hangi bir tanesini bildirirsek derleyici move memberlar� bildirmez/not declared

	S�n�fa move memberlardan her hangi birini bildirirsek derleyici copy memberlar� delete eder
	
	bir s�n�fta copy memberlar� delete etmek istenebilir bir �eydir ama
	move memberlar� yani move constructor ve move assignment operator asla delete edilmemeli ��nk�
	move gereken yerde sentaks hatas� olur move memberlar delete edilmese ama s�n�fta copy contructor olsayd�
	move gereken yerde kopyalamaya fall back olurdu

		class Myclass
		{
			public:
				Myclass();
				Myclass(const Myclass&);
				Myclass& operator=(const Myclass&);
		};

		int main()
		{
			Myclass m1,m2;

			m1 = std::move(m2);
		}
*/