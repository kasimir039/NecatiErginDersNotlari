/*

C+17 ile eklenen önemli 2 member function daha var 
	insert_or_assign
	try_emplace

	her iki fonksiyon daha önce yeterince iyi yapılamayan bazı işlemlerin yapılmasını sağlıyor

	1)insert_or_assign

		map'te subscript operatörünün şöyle bir dezavantajı var

		1.problem 
		subscript operatörünün mapped_type'ın(key'e karşılık gelen type) default constructible olması gerekiyor yani default constructible olmayan bir türü mapped_type
		olarak kullanamayız

			mymap[key] = value; // key varsa onun value değerine erişiyoruz ve onun value değerini referans semantiği ile kullanabiliyoruz atama yapıyoruz bunun yapılabilmesi için map type'ın 
								   defaut constructible olması gerekiyor yani map'in int string açılımı ise string türünün default constructible olması gerekşyor çünkü key yoksa key value 
								   pairi oluşturuluyordu ve key value pairi oluşturuken value'nun default ctoruna çağrı yapıyor 
		
		2.problem
			subscript operatör fonksiyonunu kullanıyoru ama geri dönüş değei var olan ya da oluşturulan pair'in value değerine referans subscript operatör fonksiyonu ekleme yapılıp 
			yapılmadığını söylemiyor yani  mymap[key] = value gibi bir kod yazdıktan sonra map'te key var da onun value değerini mi değiştirdik yoksa key value değerini insert mü
			ettiğimizi fonksiyonun geri dönüş değerinden bunu anlayamıyoruz ama insert_or_assign bu 2 problemi de çözüyor
			
			1)eklemenin yapılıp yapılmadığının bilgisi
			2)map type'ın default constructible olma zorunluluğu yok

		ÖRNEK:
			int main()
			{
				const auto& print_pair = [](const auto& p)
				{
						std::cout << "(" << p.first << ", " << p.second << ")";
				};

				const auto print_result = [&](const auto& p)
				{
						std::cout << (p.second ? "inserted: " : "not inserted:");
						print_pair(*p.first);
				};
				 
				std::map<int, std::string> mymap;

				auto ibp = mymap.insert_or_assign(12, "mustafa");

				print_result(ibp);
			}

	2)try_emplace
		
		emplace ve insert fonksiyonun şöyle bir problemi var

			insert fonksiyonu insert işleminin yapılabilmesi için bir pair'i oluşturuyor ama eğer set'te ve map'te eklenecek anahtar varsa ekleme işlemi yapılmıyor
			yani biz map için insert fonksiyonunu çağıtdığımız zaman pair'i zaten oluşturmuş oluyoruz artık pair'i oluşturmamak gibi bir ihtimal söz konusu değil oysa try_emplace
			önce anahtarın var olup olmadığını kontrol ediyor anahtar varsa pair'i oluşturmuyor anahtar yoksa pair'i oluşturuyor yani insert fonksiyonundan farkı eğer anahtar mevcutsa
			pair'i oluşturmaması pair'i oluşturmasının bir dezavantajı daha var eğer taşıma semantiğine açık tür kullanıyorsak pair'i oluştururken kaynak çalmış oluşucaz
			yani bir nesnenin kaynağını çalıyoruz ama ekleme işlemi yapılmıyor 

			ÖRNEK:

				int main()
				{

					std::map<int, std::string> mymap
					{
						{34,"kaveh"},
						{12,"necati"},
						{21,"selin"}
					};

					// mymap.try_emplace(56, "selami"); // 56 olmadığı için pair'i oluşturucak
					
						auto [iter,inserted] = mymap.try_emplace(12,str);
						
						if(inserted)
						{
							std::cout << "Yeni eleman eklendi: " << iter->first << " -> " << iter->second << '\n';
						}
						else
						{
							std::cout << "Anahtar zaten var: " << iter->first << " -> " << iter->second << '\n';
						}
				}			

		ÖRNEK: map kullananlarda üretimde çok tipik bi durum oluşuyor subscript operatör fonksiyonu verdiğimiz anahtarın value değerine eriştiriyor bazi maplerimiz const 
			    ve bazı mapleri lookup table olarak kullanıyoruz 

				int main()
				{
					const std::map<int,std::string> table;

					table[2] // bu anahtara karşılık gelen vaue değerine erişmek istiyor ama sentaks hatası oluyor çünkü subscript operatör fonksiyonu const member function değil
					
					table.at(2) // sentaks hatası oluşmuyor çünkü at fonksiyonu const member function ve anahtar yoksa exception throw ediyordu
				}

UNORDERED ASSOCIATIVE CONTAINERS

	diğer programlama dillerinde hash_set ve hash_map olarak geçiyor burda amaç constant time'da O(1) key ve value değerine erişmek aradaki fark set'te bu işlem O(log n) karşmaşıklığında
	unordered_set ve unordered_map'te ise ortalama olarak constant time'da

	
	ÖRNEK: key değerimiz bir string olsun ve bu anahtarı kullanarak constant time'da anahtarın var olup olmadığını ya da anahtara karşılık gelen value değerine karşılık gelen value değerini bulmaya çalışalım 
		  
		  şöyle olsaydı bir string'i bir indexe dönüştürseydik ve bu indeksi de vektörel bir veri yapısında indeks olarak kullansaydık vec[index] ve vectör'ün bu indeksteki öğesine erişseydik 
		  set ise ya o string'i buluyoruz ya da bulamıyoruz map ise string'e karşılık gelen value değerini buluyoruz burada şöyle bir süreç gerekiyoe vektörel veri yapısında indeksi kullanarak
		  anahtara erişmemiz için anahtarın indekse dönüştürülmesi gerekiyor veri yapısında tutulan öğeyi indekse dönüştürme işlemine HASHING deniliyor bu işi yapan fonksiyona da HASHER/HASH FUNCTION deniliyor 
		  yani öyle bir hash function olacak ki anahtarı alacak o anahtarı işaretsiz tam sayıya dönüştürecek ve biz onu doğrudan ya da dolaylı olarak indeks olarak kullanacağız 

		  bu veri yapısının doğru çalışması için problemlerin çözülmesi gerekiyor
			1)hashing tarafı
				veri yapısına ekleme,arama,silme gibi işlemlerde sürekli kullanıldığı için hash fonksiyonunun hızlı çalışması gerekicek
			
			2)aynı anahtarı aynı tam sayıya dönüştürmesi gerekiyor
				
				necati ergin 872341 gibi bir tam sayı değeri verirse ama daha sonra aynı hash fonksiyonuyla yine hash ettiğimizde aynı tam sayıyı vermezse o hasher kullanılabilir durumda değil
				yani atnı anahtarı aynı değere hash etmesi gerekiyor

			3)hash collision

				farklı anahtarlar bazen aynı hash değerini üretebiliyor 

				arka planda vekttörel veri yapısı var fakat vektörel veri yapısının indeksinde tutulan öğeler birer bağlı liste eğer anahtar tek bir değere yani birden fazla anahtar aynı değere 
				hash edilmemişse o zaman bağlı listede bir tane öğe var C++ terminolojisi vektördeki entrylere BUCKET terimini kullanıyor aslında vektörlerimiz bucketlar'dan oluşuyor
				bucketlar birer bağlı liste bir bucket'da eğer set'de ki öğelerden biri varsa collision yoksa o bucket'da bir tane öğe var demek
				iki tane collision varsa yani set'de ki 2 farklı anahtar aynı indekse hash edilmişse o zaman ilgili bucket'dan 2 tane öğe var demektir

				STL'de ki unordered_set ve unordered_map containerımız bucketlar için ayrı bir interface veriyor
				
				unordered_set ve unordered_map belirli bir sıra yok anahtarlar adeta bir torbaya atılmış çünkü anahtarlara erişim hashing yoluyla gerçekleşecek

				unordered_set ve unordered_mutliset grubunda sadece anahtarlar tutuluyor

				unordered_map ve unordered_multimap grubunda key ve value pairi tutuluyor

				GÖRSELEİ İNCELEYİN
					örneği vectör'ün 1.indeksi bir bucket yani arka planda bir bağlı liste bağlı listede 3 tane öğe olması demek set'De tutulan 3 farklı key'in aynı indsekse hash edilmesi demek
					ve alttaki bazı bucketlar'da boş

					unordered_set yada unordered_map'i construct ederken bucket sayısının ne olması gerektiğini
						a)kendimiz belirleyebiliyoruz
						b)default değeri kullanabiliyoruz

					STL'in bu conteinterların'da buradaki bağlı listelerin singly link list ya da doubly link list olması gibi bir koşul koyulmamış implementasyona bağlı
					bağlı listenin iteratörleri forward iteratör'de olabilir bi-directional iteratör'de olabilir

					hasher fonksiyonumuzun yapacağı bir key'i bir indekse dönüştürücek ama bir şeye dikkat bizim hasher'ımız aslında anahtarı diyelimki 4 bytelık işaretsiz tam sayıya hash ediyor
					ama diyelimki indeks 256'ya kadar olsun onu yapan set'in kendi kodu yani hasher gerçek indeksi vermiyor bir hash fonksiyonu
					anahtarı 0 ile işaretsiz diyelim ki 4 bytelık tm sayı türünün en büyük değerini hash ediyorlar

					standart kütüphane utility başlık dosyasında kendi türleri,aritmatik türler, pointer türleri için bir hash template'i veriyor ve eğer biz standart kütüphanenin hash template'ini kullanırsak
					standart kütüphaneye ilişkin türler için bizim hash function oluşturmamıza gerek kalmıyor 

			ÖRNEK:

				int main()
				{
					std::hash<int>::operator() // hashing'i yapıcak fonksiyon bu dolayısıyla hash'in int açılımının function call operator fonksiyonunu çağırırsak 
												  int türden bir değer verdiğimizde geri dönüş değeri olarak size_t veriyor

					std::cout<<std::hash<int>{}(567)<<'\n';
					std::cout<<std::hash<int>{}(568);
				}

			ÖRNEK:
				int main()
				{
					std::hash<int> hasher;

					for (int i = 5678; i < 5700; ++i)
					{
						std::cout << i << " " << hasher(i) << '\n';
					}

				}

			ÖRNEK:
				int main()
				{
					std::hash<int> hasher;

					int x;

					std::cout << "bir sayi girin: ";
					std::cin >> x;

					std::cout << hasher(x) << '\n';
					std::cout << hasher(x) << '\n'; // aynı değere hash edilmeli
				}

			ÖRNEK:
				int main()
				{
					std::hash<std::string> hasher{};

					std::vector<std::string> names = {
						"Ahmet", "Mehmet", "Ayşe", "Fatma", "Ali",
						"Veli", "Zeynep", "Kerim", "Nihal", "Sadullah"
					};

					for (const auto& name : names)
					{
						size_t hashValue = hasher(name);
						std::cout << name << " -> " << hashValue << '\n';
					}

				 }
							
	unordered_set

		int main()
		{
			std::unordered_set<int>; Açılımı aslında şöyle -> std::unordered_set<int, std::hash<int>, std::equal_to<int>, std::allocator<int>>
			
			1. parametre: Key (anahtar türü) -> int
			2. parametre: Hash fonksiyonu -> std::hash<int>
			3. parametre: Eşitlik kontrolü -> std::equal_to<int>
			4. parametre: Allocator -> std::allocator<int>
		}

		1)kendi türümüzü oluşturmak istersek

			template <>
			struct std::hash<Date> // Date sınıfı olduğunu varsayıp bu kodu yazıyoruz
			{
				size_t operator()(const Date& d) const noexcept
				{
					std::hash<int> hasher;
					return hasher(d.month()) + hasher(d.month_day()) + hasher(d.year));
				}
			};
		
		2)kendi hasher'ımızı template paramteresi yapabiliriz
		
			struct DateHasher
			{
				size_t operator()(const Date& d) const noexcept
				{
					std::hash<int> hasher;
					return hasher(d.month()) + hasher(d.month_day()) + hasher(d.year));
				}
			};	

			int main()
			{
				std::unordered_set<Date,DateHasher> x;
			}

		3)sınıf tanımlamadan bir fonksiyon oluşturmak template parametresi olarak fonksiyonun adresini kullanmak ve ctora fonksiyonun adresini argüman olarak geçmek

			
		4)lambda ifadeleri
			
			int main()
			{
				auto fhash = [](const Date& d)
				{
					std::hash<int> hasher;
					return hasher(d.month()) + hasher(d.month_day()) + hasher(d.year));
				};

				std::unordered_set<Date,decltype(fhash)> x;
			}

	bucket sayısını öğe sayısıyal oranlarsak öğe sayısına göre bucket sayısı ne kadar fazla olursa collision az olacak dolayısıyla bucket sayısını belirlememiz için ctora bunu argüman olarak geçebiliyoruz
	eğer ctora argüman olarak geçmezsek kendi belirlediği değer kullanılıyor

		ÖRNEK:
			
			int main()
			{
				std::unoredered_set<std::string> myset(100); // tam bu değer olmaz 

				std::cout<<"bucket count = " << myset.buket_count() << '\n';
			}

		ÖRNEK:

			int main()
			{
				std::unordered_set<std::string> myset;

				int cnt = myset.bucket_count();

				for (int i = 0; i < 1000; ++i)
				{
					std::string str = "ahmet" + std::to_string(i);

					myset.insert(str);

					if (myset.bucket_count() > cnt)
					{
						std::cout << "new bucket count is : " << myset.bucket_count() << " size is " << myset.size() << '\n';
						cnt = myset.bucket_count();
					}
				}

			}

			SORU:bucket count dinamik olarak artar mı? EVET
				belirli bir eleman sayısına geldiğinde bucket sayısının arttırılması için veri yapısı kendini yeniden organize ediyor bu işleme REHASH deniliyor
				yani bütün anahtarlar yeni bucket sayısına göre tekrar hash ediliyor bunun ciddi bir maliyeti var

			SORU:REHASH ne zaman yapılıyor?

				arka planda load_factor değeri var bu değer her bucket başına düşen ortalama öğe sayısını ifade eder load_factor yüksek olursa bucket’larda çok öğe birikir çakışmalar (collisions) 
				artar arama ve ekleme maliyeti artar load_factor belirli bir maksimum değeri aştığında hash tablosu rehash olur (yeni bucket sayısı artar)
				
				load_factor= size()​ / bucket_count() 
					
					ÖRNEK:

						int main()
						{
							std::unordered_set<std::string> myset;

							int cnt = myset.bucket_count();

							for (int i = 0; i < 1000; ++i)
							{
								std::string str = "ahmet" + std::to_string(i);

								myset.insert(str);
							}

							auto sz = myset.size();
							auto bcount = myset.bucket_count();

							std::cout << "size = " << sz << '\n';
							std::cout << "bucket count = " << bcount << '\n';
							std::cout << static_cast<float>(sz) / bcount << '\n';
							std::cout << myset.load_factor() << '\n'; // static_cast<float>(sz) / bcount ile aynı değeri döndürür
							std::cout << "max load factor = " << myset.max_load_factor() << '\n'; // max_load_factor'ün 1 olması şu demek load_factor max_load_factor değerine gelince REHASH yapılacak ama max_load_factor'ü 
																									 kendimizde belirleyebiliriz hem get hem set fonksiyonu
							myset.max_load_factor(0.75);
							std::cout << "max load factor = " << myset.max_load_factor() << '\n';
						}

						ÇIKTI:

							size = 1000
							bucket count = 1024
							0.976562
							0.976562
							max load factor = 1
							max load factor = 0.75
		ÖRNEK:
			
			int main()
			{
				std::unordered_set<std::string> myset;

				int cnt = myset.bucket_count();

				myset.insert("ahmet");
				myset.insert("mehmet");
				myset.insert("necati");
				myset.insert("uygar");
				myset.insert("elif");

				for (const auto& i : myset)
				{
					std::cout << i << " ";
				}

				std::cout << '\n';

				auto sz = myset.size();
				auto bcount = myset.bucket_count();

				std::cout << "size = " << sz << '\n';
				std::cout << "bucket count = " << bcount << '\n';
				std::cout << static_cast<float>(sz) / bcount << '\n';

				std::string name;
				std::cout << "ismi girin: ";
				std::cin >> name;

				std::cout << "bucket idx = " << myset.bucket(name) << '\n';
			}
		
		ÖRNEK: rehash ile reserve bizim için aynı işi yapıyorlar ama aralarındaki fark şu istedikleri değer farklı rehash bizden bucket değerini alıyor
			   
			   int main()
			   {
					std::unordered_set<std::string> myset(256);

					myset.rehash(300); // 300 değerini girdiğimiz için bucket size'ı 300 den küçük olmayacak bir değere ayarlayacak ve tekrar hash edecek
										  
					myset.reserve(2000) // reserve değeri eleman sayısı olarak alıyor rehash'i çağırmaya eşdeğer rehash(count / max_load_factor())
			   }
			
	associative konteynırlarla unordered associative konteynırlar arasında radikal bir başka bir farklılık var
		
		set map grubunda örneğin bir anahtarın var olup olmadığını tespit etmek için equivalence kullanıyorduk fakat unordered containerrlarda durum böyle değil bu bizim aradağımız değer mi? 
		sorgulaması == karşılaştırmaasıyla yapılıyor == karşlıştırmasını sağlayan function object type equal_to'nun key açılımını alıo-yor
		unordered_set'de tutacağaımız öğeler için insert erase gibi işlemler yapacaksak o türden değerlerin == operatörüyle karşılaştırılabilmesi gerekiyor 
		
			class Myclass
			{
				public:
					bool operator==(const Myclass&)const;
			};

			template <>
			struct std::hash<Myclass>
			{
				size_t operator()(const Myclass&)const
				{
					return 1u;
				}
			};

			int main()
			{
				std::unordered_set<Myclass> myset;

				Myclass m;

				myset.insert(m);
			}

	unordered_map

		int main()
		{
			std::unordered_map<std::string, int> m;

			 std::unordered_map<
			      Key,            // anahtar türü
			      T,              // değer türü
			      Hash = std::hash<Key>,       // hash fonksiyonu
			      KeyEqual = std::equal_to<Key>, // eşitlik kontrolü
			      Allocator = std::allocator<std::pair<const Key, T>> // bellek yöneticisi
			 >
			
			 std::unordered_map<std::string, int> yazdığımızda:
				 Key = std::string
				 T = int
				 Hash = std::hash<std::string>
				 KeyEqual = std::equal_to<std::string>
				 Allocator = std::allocator<std::pair<const std::string, int>>
		}

	std::array

		bu konteynırın amacı C dizilerini sarmalamak yani dizileri sanki bir sınıfmış gibi kullanma şansını elde ediyoruz

			template<typename T,size_t N>
			struct Array
			{
				T ar[N];
			}

		MÜLAKAT SORUSU: neden std::array kullanıyoruz?

			1)interface'i var(member fonksiyonları,free fonksiyonlarının olması)
			
			2)generic progralama ve STL uyumlu

			3)C dizilerinin boyutu 0 olamaz ama bazen generic programlama tarafında dizinin boyutunun 0 olması önemli faydalar sağlayabiliyor
			 
			4)fonksiyonlara 2 argüman olarak geçmek yerine tek argüman geçiyoruz

			5)C ve C++ dillerinde bir fonksiyonun geri dönüş değeri türünün kendisi direkt olarak bir dizi türü olamaz(dizinin adresi olabilir) 
			  fonksiyon parametresi direkt olarak bir dizi türü olamaz eğer istenirse 
				return type std::array
				parameter type std::array olabilir

			6)C de ve C++ dilinde bir dizinin ismini kullandığmızda array decay gerçekleşiyor C için bir çok yerde bilerek ve isteyerek kullanıyoruz
			  ama C++ için bir çok bağlamda aşırı riskli std::array'de array decay gerçekleşmiyor

		ÖRNEK:

			int main()
			{
				std::array<int,10> x; // 1. template argümanı dizinin elemanlarının türü 2.template argüman dizinin boyutu
				std::array<double,5> y;
				std::array<std::string,4> myarray;
				std::array<std::thread,4> myarray2;
			}
	
		SORU:boş bir array oluştursak burada tutulan değerler 0 mı olur yoksa garbage mı? GARBAGE değer olur
			
			int main()
			{
				std::array<int,5> x; 

				for(const auto i : x)
					std::cout<<i<<" ";

				garbage olmasının nedeni std::array'in aggregate type olması böyle bir dizi oluşturuyorsak ve primitive türden öğeler varsa değerler
				çöp değer

				eğer hepsini 0 değeri ile başlatmak istiyorsak value initialization etmemiz gerekir // std::array<int,5> x{};
			
			
				std::array<int,5> x{1,4,5,6,9}; // aggregate initalization 

			}

		2.14

*/