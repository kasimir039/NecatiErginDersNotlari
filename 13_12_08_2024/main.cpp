/*

TEMPORARY OBJECT
	bir ge�ici nesne ismi temp olan bir nesne de�il hoca b�yle d���n�nler i�in diyor bunu
		int temp;

	ge�ici nesneler PR value expressiond�r ve C++ dilinin b�yle nesnelere ili�kin �nemli kurallar� var hoca bahsedecek

	class Myclass{};

	void func(Myclass);

	int main()
	{
		Myclass{}; //b�yle bir ifadeyle ne yapabiliriz
		
				1)bir ba�ka myclass nesnesine ilk de�er vericek ifade olarak kullanabiliriz
		
				auto m = Myclass{};

				2)bir fonksiyonun parametresine ge�ici nesne olarak ge�irebiliriz
					func(Myclass{});
	}	

	isimlendirilmemi� nesneler i�imizi g�r�yorsa nesneleri isimlendirmeyin ��nk� bunlar� b�yle kullanman�n avantajlar� var 

	referanslar s�z konusu oldu�u zaman ge�ici nesne ifadesi PR value expression oldu�u i�in ba�lancak referans�n const L value & yada
	R value && olmas� gerekiyor

		const Myclass& = Myclass{};
		Myclass&& = Myclass{};

	TEMPORARY OBJECT sa�lad��� avantajlar
		1)�yle durumlar var ki bir fonksiyon �a�r�s�nda kullanaca��m�z arg�mana ihtiyac�m�z var ama amac�m�z sadece orda kullan�lmas� �rne�in
		func fonksiyonuna myclass s�n�f� t�r�nden bir arg�man g�nderece�iz ama olu�turdu�umuz arg�man�n de�eri zaten belliyse
			Myclass{3,5}; b�yle bir myclass nesnesini arg�man olarak g�ndermek istiyorsak 

			Myclass m;
			func(m)  b�ylede yazabiliriz ama b�yle yazarsak
				
				1)isim alan�na bir isim enjekte etmi� oluyoruz
				2)kodu okuyan ki�iye buradaki myclass nesnesinin fonksiyon �a�r�s�ndan sonra tekrar kullan�laca�� alg�s�n� yarat�yoruz
				3)myclass nesnesinin hayat� otomatik �m�rl� bir de�i�ken oldu�u i�in tan�mland��� blo�un sonuna kadar ge�erli olacak

				oysa bizim sadece bu i� i�in bu nesneye ihtiyac�m�z varsa i�ini yapt�ktan sonra hala hayat�n�n devam etmesi  
				�zellikle bu nesne bir tak�m kaynaklar kullan�yorsa bu bizim istedi�imiz bir �ey de�il bu ayn� zamanda bir SCOPE LEAKAGE

		e�er b�yle kullanmak yerine temporary object kullansayd�k �nce isim alan�na gereksiz olarak bir isim enjekte etmemi� olacakt�k ayn� zamanda ge�ici nesnelerin hayata veda etmesi otomatik �m�rl� yerel nesneler gibi de�il
		ge�ici nesneler i�lerinde bulunduklar� full expression�n y�r�t�lmesi sonucunda hayata veda ediyorlar

		C++17 standart�ndan �nce �imdiye kadar kulland���m�z terimlerde bir yanl��l�k yok ama C++17 ile birlikte kulland���m�zda terimlerde daha dikkatli olmak gerekiyor
			Myclass{3,5}; // bu bir nesne mi ? HAYIR 
				C++17 standart� ile PR value expression art�k do�rudan bir nesne de�il bir nesnenin olu�turulmas� i�in bir re�ete bir talimat gibi yani yeri geldi�inde bu ifadeden bir nesne yarat�labilir
				bunun teknik olarak kar��l��� TEMPORARY MATERIALIZATION
			
		2)do�rudan bir nesne olmamas� ve baz� senaryolarda COPY ELISION dedi�imiz sonucu do�urmas�
			
			MANDATORY COPY ELISION
				C++ dilinde �ok �nemli bir durum yazd���m�z kodun verimini %100 artt�rabilecek bir durum COPY ELISION demek kopyalaman�n yap�lmamas� demek
				modern c++ �ncesinde derleyiciler yine COPY ELISION yap�yorlard� fakat derleyicinin ger�ekle�tirdikleri COPY ELISION koda bakt��m�zda bir kopyalama var ama run timeda bir
				kopyalama yap�lm�yor bu derleyicinin ger�ekle�tirdi�i bir optimizasyondu �imdi bahsedece�imiz senaryolarda zaten art�k dilin kural� gere�i COPY ELISION garanti alt�nda yani kopyalama yap�lmayacak  
				
				1)ge�ici nesne ifadesini ba�ka bir ge�ici nesne ifadesini olu�turken arg�man olarak kullanmak
					class Mylcass
					{
						public:
							Myclass()
							{
								std::cout<<"default ctor\n";
							}

							Myclass(const Myclass&)
							{
								std::cout<<"copy ctor\n";
							}

							~Myclass()
							{
								std::cout<<"destructor \n";
							}
					};

					int main()
					{
						Myclass m = Myclass{}; 
					}

					�IKTI:
					default ctor
					destructor

				2)bir temporary object ile parametresi s�n�f t�r�nden olan fonksiyona �a�r� yapmak
					int main()
					{
						func(Myclass{}) // c++17 �ncesi �nce default ctor �a��r�lacakt� sonra copy ctor �a��r�lacakt� ve derleyici bunu optimize edecekti
					}
					
					�IKTI:
					default ctor
					destructor
					
				bu �ok �nemli ��nk� baz� s�n�f nesnelerinin in�as� �ok ciddi bir maliyet biz do�rudan kopyalama maliyetinden kurtulmu� oluyoruz yani COPY ELISION bize
				b�y�k bir verimlilik sa�l�yor vector yada string gibi s�n�flar�m�z olsayd� yine temporary object kullansayd�k bu sefer de move ctor'un �a��r�lma maliyetinden kurtulmu� olacakt�k
				s�n�f�n ne oldu�una ba�l� olarak move operation copy operationdan daha az maliyetli olabilir ama copy elision bunlar�n hepsinden daha verimli ��nk� 1 kere nesne olu�turuyoruz

				buda bize ��yle bir olanak sa�l�yor copy ctoru ve move ctoru olmayan yada delete edilmi� s�n�flar i�in hala bu �ekilde fonksiyon �a��r�lar� yapabiliriz

				3)bir fonksiuonun geri d�n�� de�erinin bir s�n�f t�r�nden olmas� ve fonksiyonun return ifadesinin s�n�f t�r�nden bir PR value expression olmas�
				(buna kar��l�k gelen terim Unnamed Return value optimization(URVO)) isimlendirilmemi� geri d�n�� optimizasyonu

					C++17 �ncesi URVO bir compiler optimizationd� ama art�k bir compiler optimization de�il dilin kural�
					Myclass func()
					{
						return Myclass{};
					}

					int main()
					{
						Myclass m = func(); // C++17 �ncesi �nce default ctor �a��r�lacak sonra copy ctor �a��r�lacak ve derleyici bunu optimize edecekti
											   C++17 sonras� ise sadece default ctor �a��r�lacak
					}

				4)Named return value optimization(NRVO) isimlendirilmi� geri d�n�� de�er optimizasyonu
					copy elision'�n bir ba�ka bi�imidir c++ dili taraf�ndan garanti alt�nda de�ildir mandatory de�ildir(yani zorunlu de�il)bu compiler optimizationdur 
					dilin direkt olarak kural� de�ildir ve NRVO kod verimini artt�ran bir durumdur
					
					Myclass func()
					{
						Myclass x;

						return x;
					}

					int main()
					{
						Myclass m = func(); // bu durumda func fonksiyonu �a��r�ld���nda func fonksiyonun i�indeki x nesnesi i�in default ctor �a��r�lacak fonksiyon �a��r�s� tamamland���nda fonksiyonun geri d�n�� de�erini 
						m ismini verdi�imiz nesneye kopyalad��m�zda 1 yada 2 kez copy ctor �a��r�lacak 1 yada 2 kez dememimizin sebebi asl�nda b�yle durumda derleyici fonksiyonun geri d�n�� de�erini 
						bellekte bir yere yaz�yor ordada bir nesne olu�uyor o nesnede bir temporary object ve o nesne copy ctor ile hayata getiriliyor ama o nesnedende yine kopyalama yoluyla m isimli nesneyi olu�turuyoruz

						bu optimizasyonu yapmak garanti de�ildir derleyiciye ba�l�d�r yani derleyici optimizasyon yaparsa copy ctor yada move ctor �a��r�lmaz 
					}
			
			TEMPORARY MATERIALIZATION OLAN DURUMLAR
			1)referansa ba�lama
				Myclass &&r = Myclass{};
				const Myclass& r = Myclass{};

			2)ifadeden bir nesne olu�turursak
				Myclass m = Myclasss{3,5}; // burada dikkat acaba derleyici burada �nce iki int parametreli ctoru �a��r�p ge�ici nesneyi olu�turup ondan sonra bu ge�ici nesneden hareketle belki move yada copy ctoru �a��r�p
				m isimli nesneyi mi olu�turuacak? HAYIR bu kodda ctor yada destructor�n �a��r�ld���n� g�steren statementlar koysayd�k sadece bir kez ctorun �a��r�ld���n� g�recektik buna C++17 de COPY ELISION deniliyor
				yani bir PR value expression�n materyalize olmadan kullan�lmas� durumu ne demek?
					class Mylcass
					{
						public:
							Myclass()
							{
								std::cout<<"default ctor\n";
							}

							Myclass(const Myclass&)
							{
								std::cout<<"copy ctor\n";
							}

							~Myclass()
							{
								std::cout<<"destructor \n";
							}
					};

					int main()
					{
						Myclass m = Myclass{}; // C++17 �ncesi copy ctor �a��r�l�rd� ve copy ctor delete edilmi�se yada private durumdaysa sentaks hatas� olur
					}

					�IKTI:
					default ctor
					destructor
					
					C++17 standart�ndan �nce bu t�r durumlar compiler'�n yapt��� optimizasyon olarak ele al�n�yordu yani C++17 standart�n� desteklemiyorsa
					1 defadan fazla default ctor �a��r�lm�yor 1 kere destructor �a��r�l�yor gibi bu derleyicinin yapt��� bir optimizasyon fakat C++17 ile birlikte
					bu PR value expression olan ge�ici nesnelerin nesnenin kendisi de�ilde nesne olu�turmaya y�nelik bir re�ete olmas� C++17 standart�nda MANDOTARY COPY ELISION terimi
					ama bu terim pek do�ru bulunmuyor ��nk� bir nesne yok ki kopyalans�n nesne ne zaman olu�acak? TEMPORAY MATERIAZLIZATION gerekece�i zaman olu�acak
					dolay�s�yla PR value expression�n do�rudan bir nesne olarak kabul edilmemesi hedefini buldu�unda bir nesne haline gelmesi kural� COPY CTOR'un �a��r�lmayayaca�� durumlarda 
					delete edilmesi yada private olmas� durumunda hala bir sentaks hatas� olu�mayacak ��nk� copy ctor burada �a��r�lm�yor
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
CONVERSION CONSTRUCTOR(D�N��T�REN KURUCU ��LEV)
	s�n�flar�n �zellikle tek parametreli ctorlar� nesneyi olu�turman�n d���nda ilgin� bir niteli�e daha sahipler
	
		class Myclass
		{
			public:
				Myclass()
				{
					std::cout<<"default ctor this = " << this<<'\n';
				}
				~Myclass()
				{
					std::cout<<"destructor this = " << this<<'\n';
				}
				Myclass(int x) // bu ctor ayn� zamanda parametresi olan t�rden bu s�n�f t�r�ne �rt�l� bir d�n���m ger�ekle�tirmek i�inde kullan�l�yor 
				{
					std::cout<<"Myclass(int x) x = " << x <<'\n';	
					std::cout<<"this = " << this <<'\n';	

				}
				Myclass& operator=(const Myclass& r)
				{
					std::cout<<"copy assignment"<<'\n';
					std::cout<<"this = " << this <<'\n';
					std::cout<<"&r = "<< &r <<'\n';
					return *this;
				}
		}
		
		int main()
		{
			Myclass m;

			m = 5; // Myclass(int x) parametreli conversion ctor olmasayd� hata verirdi ��nk� int t�r�nden s�n�f t�r�ne d�n���m yok
			dilin kurallar�na g�re derleyici conversion ctor tan�m�n� g�rd���nde int t�r�nden s�n�f t�r�ne d�n���m� conversion ctora �a�r� yaparak d�n��t�r�yor
			burada asl�nda olan �u derleyici conversion ctorun bildirimini g�rd� conversion ctora �rt�l� olarak �a�r� yapt� 5 ifadesini arg�man olarak g�nderdi ve bir myclass nesnesi olu�turdu
			asl�nda m = 5 ifadesi arka planda bir gecici nesne m = Myclass{5] ifadesi gibi bir ifade
		
		}
		
		�IKTI:
		default ctor this = 0000000EC42FF644
		Myclass(int x) x = 5
		this = 0000000EC42FF724
		copy assignment
		this = 0000000EC42FF644
		&r = 0000000EC42FF724
		destructor this = 0000000EC42FF724
		destructor this = 0000000EC42FF644

		b�yle bir d�n���m�n dilin kurallar�na g�re yap�lmas� iyi bir �ey mi k�t� bir �ey mi?
			de�i�ir ��nk� �yle bir s�n�f olabilir ki s�n�f�n genel mant���yla genel kullan�m fikriyle o s�n�f� tasarlayan�n iste�iyle
			zaten b�yle bir �rt�l� d�n���m�n yap�lmas� istenebilir fakat di�er taraftan conversion ctor sayesinde yap�lan �rt�l� d�n���mler �ok b�y�k bir risk kayna��

			int main()
			{
				Myclass m;
				double dval{};
				bool flag{};

				m = dval; 
				m = flag; 

				dilin bu konuda ��yle bir kural� var 
					standard conversion(dilin kurallar� gere�i varolan d�n���m)
					user defined conversion(bir fonksiyona �a�r� yap�larak olu�turulan d�n���m)
						ama user defined conversion = conversion ctor diyemeyiz asl�nda 2 tane birbirinden ayr� user defined conversion var
						
						1)conversion ctor yoluyla yap�lan d�n���m
						2)ba�ka bir fonksiyonun �a��r�lmas�yla yap�lan user defined conversion(type cast operator function deniliyor)
							class Nec{
								public:
								operator int()const // bu fonksiyon nec t�r�nden bir nesneyi int t�r�ne d�n��t�ren bir fonksiyon	
								{
									std::cout<<"operator int \n";
									return 49;
								}
							};

							int main()
							{
								Nec mynec;
								int ival;

								ival = mynec;

								std::cout<<"ival = "<< ival <<'\n';
							}

							�IKTI:
							operator int
							ival = 49

					e�er bir �rt�l� d�n���m �nce 
						standart conversion + user defined conversion uygulanarak yap�labiliyorsa derleyici �nce standart conversion sonra user defined conversionu uygular
						�nce user defined conversion + standart conversion uygulayarak d�n���m� ger�ekle�tirebiliyorsa derleyici �nce user defined conversion ondan sonra standart conversion uygular
						user defined conversion + user defined conversion uygulan�yorsa derleyici hi� bir zaman bu d�n���m� �rt�l� olarak yapmaz

						Myclass m;
						double dval{};
						double flag{};

						m = dval; // �nce standart conversion yap�l�r(double t�r�nden int t�r�ne d�n���m) sonra user defined conversion yap�l�r(int t�r�nden s�n�f t�r�ne d�n���m)
						m = flag; // �nce standart conversion yap�l�r(double t�r�nden int t�r�ne d�n���m) sonra user defined conversion yap�l�r(int t�r�nden s�n�f t�r�ne d�n���m)
						
						bu durumu daha k�t� bir hale getiriyor diyebilir miyiz? KES�NL�KLE
						class Myclass
						{
						public:
							Myclass() {}

							Myclass(bool b)
							{
								std::cout << "b = " << b << '\n'; 
							}
						};

						int main()
						{
							Myclass m;
							m = "fatih akgul"; // ge�erli oldu ama �ok tehlikeli bir durum array decay ile const char* t�r�ne d�n���yor const char* t�r�ndende bool t�r�ne d�n���yor
							 bu yap�lan �rt�l� d�n���m baz� senaryolarda istenen bir durum ama bir �ok durumda bizi riske sokanda bir durum

						}

						�IKTI:
						b = 1 // m ekrana bool oldu�u i�in true de�erini yazd�r�r

						EXPLICIT CONSTRUCTOR(istenmeyen d�n���mlerin �n�ne ge�mek i�in kullan�l�r)
							bir ctoru ama �zellikle tek parametreli bir ctoru explicit anahtar s�zc���yle bildirmek o ctoru explicit ctor yap�yor
							bu ctor sadece explicit conversiona(a��k d�n���me) izin verir yani bir d�n���m yap�lacaksa c++'�n t�r d�n��t�rme operat�rleriyle yap�lmal�
							her zaman tek parametreli ctorlar� explicit olarak belirtmeliyiz anca �zel bir durum oldu�u zaman non-explicit yapmal�y�z

								class Myclass
								{
									public:
										Myclass(){}
										explicit Myclass(int){}
								};

								int main()
								{
									Myclass m;
									m = 5; // ctor explicit oldu�u i�in �rt�l� d�n���m yap�lam�yor ve constructor'�n explicit olmas� copy initialization sentaks�n�da ge�ersiz k�l�yor

									
									e�er bu d�n���m� explicit olarak yapmak istersek

									ival{245};
									m = static_cast<Myclass>(ival); // art�k d�n���m� explicit olarak yapt��m�z i�in sentaks hatas� olmaz
								
								}
								t�m constructorlar explicit olabilir ama olmas� gerekiyor mu buna karar vermek gerek

								class Myclass
								{
									explicit Myclass();
									explicit Myclass(int);
								};

								void func(Myclass);

								Myclass foo()
								{
									return 15; // int parametreli ctor explicit oldu�u i�in sentaks hatas�
								}
								int main()
								{
									Myclass x = {}; // b�yle yazmak Myclass x = Myclass{}; yazmak ayn� �ey dilin kurallar�na g�re �rt�l� d�n���m olmu� oluyor ama default ctor explicit oldu�u i�in sentaks hatas�

									Myclass x = {12,56}; // int parametreli ctor explicit oldu�u i�in �rt�l� d�n���m yap�lam�yor sentaks hatas�
									
									func(132); // int parametreli ctor explicit oldu�u i�in implicit conversion sentaks hatas�na sebep oluyor
								}
							
							SORU: 
								class Myclass
								{
									public:
										explicit Myclass(int);
										Myclass(dobule);
								};

								int main()
								{
									// Myclass m = 12; // double parametreli ctor �a��rlacak genel beklenti sentaks hatas� olmas� ama sentaks hatas� yok explicit ctor overlaod set'e dahil edilmiyor 
														
								}
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DELEGATING CONSTRUCTOR
	bir ctorun bir nesneyi hayata getirirken bir ba�ka ctor ile memberlar�n initialize edilmesini sa�lamak
	bir ctor MIL sentaks� ile s�n�f�n di�er ctorlar�na �a�r� yaparak initalization yapma s�recini o ctora delege edebiliyor

	class Myclass{
		public:
			Myclass(int,int,int);
			Myclass(int,int);
			Myclass(int x) : Myclass(x,x,x)
			{

			}

			burda recursive bir �a�r� olu�ursa bu durum programc�n�n sorumlulu�unda
	}
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FRIEND DECLERATION(ARKADA�LIK B�LD�R�MLER�)

	bir s�n�f�n private b�l�m� client kodlara kapal� eri�meye �al���rsak access control s�recinde sentaks hatas� al�r�z friend bildirimleri s�n�f�n kendi kodlar�n d���nda ba�ka kodlar�n s�n�flar�n 
	private ve protected elemanlar�na eri�imini ge�erli k�l�yor e�er bir kod friend olarak bildirilmi�se o kodun i�inde friend bildirimi yapan s�n�f�n private ve protected b�l�m�ne eri�im sentaks hatas� olmayacak
	friend bildirimleri client kodlar i�in yap�lm�yor s�n�f�n kendi kodlar� i�in yap�l�yor 
	bir s�n�f�n public inerface'i sadece s�n�fn public b�l�m�nden ibaret de�il ba�l�k dosyas�nda yap�lan t�m bildirimler(public ��eler ve global ��eler) s�n�f�n public inerface'ine dahil oluyor
	
	friend bildirimi verilen fonksiyonlar
		1)global fonksiyonlara
		2)bir ba�ka s�n�f�n bir member functionuna
		3)bir s�n�f�n tamam�na
*/