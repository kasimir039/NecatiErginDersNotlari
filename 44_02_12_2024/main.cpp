/*

set'in tekrar� yap�ld� ve �rnekler verildi

	�RNEK: find(iterat�r d�nd�r�yor)

		int main()
		{
			std::set<int> myset{ 5,9,12,14,15,18 };

			for (auto i : myset)
				std::cout << i << " ";

			int x;

			std::cout << "\nenter the key value: ";
			std::cin >> x;

			std::cout << '\n';


			if (auto iter = myset.find(x); iter == myset.end())
			{
				std::cout << "not found\n";
			}
			else
			{
				std::cout << "found: " << *iter<<'\n';
			}
		}

	�RNEK: count(ka� tane ayn� ��eden oldu�unu d�nd�r�r)

		int main()
		{
			std::multiset<int> myset{ 5,5,5,9,12,14,15,18 };

			for (auto i : myset)
				std::cout << i << " ";

			std::cout << '\n';

			if (auto n = myset.count(5)) 
			{
				std::cout << "in set:" << n; // 3
			}
			else {
				std::cout << "not in set\n";
			}
		}


	�RNEK: contains(C++20 ile gelen boolean de�er d�nd�r�yor varsa true yoksa false)

		int main()
		{
			std::set<int> myset{ 5,9,12,14,15,18 };

			for (auto i : myset)
				std::cout << i << " ";

			std::cout << '\n';

			if (auto n = myset.contains(14))
			{
				std::cout << "var:" << n; // true
			}
			else {
				std::cout << "yok\n";
			}
		}

	�RNEK: 

		int main()
		{
			std::set<std::string> myset{"asim","ceyda","ceylan","handesu","izzet","kasim","olcay","rumeysa","zerrin","ziya"};

			for (auto i : myset)
				std::cout << i << " ";

			std::cout << '\n';

			std::string oldkey, newkey;

			std::cout << "eski ve yeni anahtarlar: ";
			std::cin >> oldkey >> newkey;

			if (auto iter = myset.find(oldkey); iter != myset.end())
			{
				myset.erase(iter);
				myset.insert(newkey);
				std::cout << "anahtar degisti\n";

				for (auto i : myset)
					std::cout << i << " ";
			}
			else {
				std::cout << "bulunamadi\n";
			}
		}

	arka planda implementasyon ikili arama a�ac� oldu�una g�re node'lar� kullan�yor bizim set'imiz node'lardan olu�uyor de�i�tirmek istedi�imiz anahtar� 
	set'den sildi�imiz zaman set'de olan ��e destroy oluyor node'da arka planda dynamic olarak allocate edildi�i i�in free edilmi� oluyor peki madem set kendi d���mlerine hakimse
	o d���m� set'den ��karal�m ama nesneyi destroy etmeyelim d���mdeki ��eyi de�i�tirelim o d���m� insert edilmesi gereken yere insert edelim e�er b�yle yaparsak
	gereksiz olan destruction,de-allocation,construction, ve tekrar allocation ve construction'dan ka��nm�� oluruz modern C++ �ncesinde b�yle bir imkan yoktu 
	modern C++'da buna EXTARCT isimli fonksiyon ile �nlem al�nd�

	extract
		extract bir node handle d�nd�r�r bu handle containerdan ��kar�lan ��enin t�m i�eri�ini saklar (anahtar + de�er) art�k bu ��e containerdan ayr�l�r ama haf�zadan silinmez
		bunu ba�ka bir kapsay�c�ya ta��yabilir ya da �zerinde de�i�iklik yapabiliriz
		
		extract(key)
		extract(iter)

		�RNEK:

			int main()
			{
				std::set<std::string> myset{"asim","ceyda","ceylan","handesu","izzet","kasim","olcay","rumeysa","zerrin","ziya"};

				for (auto i : myset)
					std::cout << i << " ";

				std::cout << '\n';

				std::string oldkey, newkey;

				std::cout << "eski ve yeni anahtarlar: ";
				std::cin >> oldkey >> newkey;

				if (auto iter = myset.find(oldkey); iter != myset.end())
				{
					auto handle = myset.extract(iter);
					handle.value() = newkey;
					myset.insert(std::move(handle));
					std::cout << "anahtar degisti\n";

					for (auto i : myset)
						std::cout << i << " ";
				}
				else {
					std::cout << "bulunamadi\n";
				}
			}

		�RNEK: hint insert 

			int main()
			{
				std::set<std::string> myset{"asim","ceyda","ceylan","handesu","izzet","kasim","olcay","rumeysa","zerrin","ziya"};
			
				for(auto n = : myset)
					std::cout<<n<<" ";,

					myset.insert(myset.begin(),"abidin"); // hint insert (burda bu konuma ekleme yapm�yor) yani demi� oluyoruz ki bu konumu ba�lang�� noktas� olarak alman� istiyoruz 
															 e�er bu konum ger�ekten eklenebilecek bir konumsa ekle ama de�ilse burdan hareketle eklenecek en yak�n konumu bulacak
			}

		
	�RNEK: transparent function object

		Normalde std::set veya std::map bir ��eyi eklerken veya ararken anahtar tipi ile kar��la�t�rma yapar e�er farkl� t�rler ile kar��la�t�rma yapmak istersek 
		(�rn. std::string ve const char*) normal comparator �al��maz transparent comparator bunu m�mk�n k�lar farkl� ama kar��la�t�r�labilir t�rlerle de kar��la�t�rma yapabiliriz

		struct Nec
		{
			int ival;
			std::vector<std::string> vec;
			bool operatorz(const Nec&) const;
		};

		bool operator<(const Nec&,int);
		bool operator<(int,const Nec&);

		struct TransparentCmp
		{
			using is_transparent = void; // burada olan fonksiyonun bulunmas� i�in isim aramayla ��yle bir ko�ul var bu s�n�f�n is_transparent isimli bir nested type'� olacak ve bu nested type'�n 
										   hangi t�r oldu�unun �nemi yok zaten t�r kullan�lmayacak kar��la�t�rma gerekti�inde fonksiyon bulunacak
			template<typename T,typename U>
			bool operator()(T&& lsh, U&& rhs) { return std::forward(lsh) < std::forward(rhs); }
		};

		int main()
		{
			// std::set<Nec> myset;
			// myset.find(12); // ge�ersiz

			// std::set<Nec,TransparentCmp> myset;
			// myset.find(12); // ge�erli ��nk� olu�turdu�umuz function object type'�n is_transparent nested type'� var
		}

		TransparentCmp gibi function object type olu�turmak yerine standart k�t�phanenin kendi function object type'� var LESS<> maliyet a��s�ndan b�y�k bir fark var

			�RNEK:

				int main()
				{
					std::set<Nec less<>> myset; // less'in void a��l�m� 

					myset.find(12);

					// bir function object'in transparent function object olup olmad���n� anlamak i�in is_transparent type'� olup olmada��na bakmam�z yeterli less<void>::is_transparent 
				}

	�RNEK:

		int main()
		{
			std::multiset<int> myset{ 1,4,6,8,9,15,23 };

			for (auto i : myset)
				std::cout << i << " ";

			std::cout << '\n';

			int key;

			std::cout << "enter the key: ";
			std::cin >> key;

			//auto iter_lower = myset.lower_bound(key); // eklemenin yap�laca�� ilk konum(key�den k���k olmayan (yani >= key) ilk eleman� bulmak e�er key multiset i�inde o eleman varsa o eleman� d�ner
																						  e�er yoksa, ekleme yap�l�rsa nereye koyulaca��n� g�sterir)
			//auto iter_upper = myset.upper_bound(key); // eklemenin yap�laca�� son konum(key�den b�y�k (> key) ilk eleman� bulmak bu �zellikle ayn� de�erden birden fazla oldu�unda o grubun sonras�n� verir
																						  yani o grubun hemen sonras�n� i�aret eder key de�erine sahip son eleman�n bir sonraki yeri)

			auto[iter_lower, iter_upper] = myset.equal_range(key); // (lower_bound(key) ve upper_bound(key) ikilisini tek seferde d�nd�r�r)

			if (iter_lower != myset.end())
				std::cout << "Lower bound: " << *iter_lower << '\n';
			else
				std::cout << "Lower bound: end\n";

			if (iter_upper != myset.end())
				std::cout << "Upper bound: " << *iter_upper << '\n';
			else
				std::cout << "Upper bound: end\n";

		}

	emplace_hint

		diyoruz ki eleman� nereye koyaca��m� tahmin ettim i�te sana ipucu :D buradan ba�la ve eklemeyi yap

		int main() 
		{
			std::set<int> s{1, 3, 5};

			// Normal emplace � STL kendi arar
			s.emplace(4);

			// emplace_hint � biz ipucu veriyoruz
			auto hint = s.find(5); // 5'in yeri belli, 4 buradan �nce gelecek
			s.emplace_hint(hint, 2); // ipucu 5'in yeri

			for (int x : s)
				std::cout << x << " "; // 1 2 3 4 5

		}

			emplace = Bul bakal�m nereye koyacaks�n :D

			emplace_hint = Bence �u eleman�n yan�na koy :D :D


	merge

		bir set'de olan ��eleri ba�ka bir set'e kat�yor yani bir container�dan di�erine elemanlar� ta��yarak ekler (kopyalamaz kayna�� container�dan siler)

			int main() 
			{
				std::set<int> s1{1, 3, 5};
				std::set<int> s2{2, 4, 5}; // dikkat: 5 s1'de de var

				s1.merge(s2);

				std::cout << "s1: ";
				for (int x : s1) std::cout << x << " ";
				std::cout << "\ns2: ";
				for (int x : s2) std::cout << x << " ";
			}

			�IKTI:

			s1: 1 2 3 4 5
			s2: 5 // 5 zaten s1�de oldu�u i�in s2'den ta��nmad� Di�er elemanlar (2, 4) s1�e ta��nd� ve s2�den silindi

	generic programlama taraf�nda containerlardan nested typelar� �nem ta��yor

	std::set<int>::value_type // containerda tutulan ��enin t�r�n� verir -> int
	std::set<int>::difference_type
	std::set<int>::reference // containerda tutulan ��eye referans t�r� -> int&
	std::set<int>::const_reference // -> const int&
	std::set<int>::pointer //  -> int*
	std::set<int>::const_pointer //  -> const int*
	std::set<int>::key_type // anahtar�n t�r� set'de tutulan ��enin t�r� -> int
	std::set<int>::key_compare // anahtar� kar��la�t�rmada kullan�lan t�r
	std::set<int>::value_comp // ortak aray�z i�in value_comp'da var set'de key_comp ile ayn� anlama geliyor
	

MAP VE MULTIMAP
	
	map ile set neredeyse ayn� aradaki fark map key value pairleri tutuyor yani map'de tutlan ��eler birer pair set'de tutulan ��eler key map'de her key'e kar��l�k gelen bir value var
	map bir key'den bir tane tutuabiliyorken multi_map birden fazla tutabiliyor
	

	�RNEK: map i�in eleman eklemenin farkl� yollar�

		int main()
		{
			std::map<int,std::string> mymap;

			std::pair<int,std::string> p1 {45 ,"suleyman" };
			std::pair<int,std::string> p2 {14 ,"naciye" };

			mymap.insert(p1);
			mymap.insert(std::move(p2));
			mymap.insert(std::pair {24,"turgut"});

			mymap.emplace(41,"sevim");

			mymap.insert(std::make_pair(12,"necati"));

			for(const auto&p : mymap)
			{
				std::cout<<p.first<<" " <<p.second<<'\n';
			}
		}
	
		mapler'de structure binding ile dola�mak daha yayg�n ama vector'�n pair a��l�m� olsayd� yinede dola�abilirdik

			for(const auto& [no,name] : mymap) 
			{
				std::cout<<no<<" "<< name<<'\n';
			}

			�RNEK: 
				
				struct Data
				{
					int x,y,z;
				};

				int main()
				{
					std::vector<Data> myvec
					{
						{5,9,15},
					   {33,48,65},
					   {35,45,89}
					};

					for(auto [a,b,c] : myvec)
					{
						std::cout<<a<<" " <<b <<" " <<c<<'\n';
					}
				}

	�RNEK:

		int main()
		{
			std::multimap<int, std::string> mymap;

			std::pair<int, std::string> p1{ 45 ,"suleyman" };
			std::pair<int, std::string> p2{ 14 ,"naciye" };

			mymap.insert(std::move(p1));
			mymap.insert(std::move(p2));
			for (const auto& [no, name] : mymap)
			{
				std::cout << std::format("{:<10} {:<20}\n", no, name);
			}
		}
	
	�RNEK:
		
		int main()
		{
			std::map<std::string,int> mymap;

			mymap.insert({ "suleyman",45 });
			mymap.insert({ "naciye",14 });
			mymap.insert({ "necati" ,18 });

			for (auto i : mymap)
				std::cout << i.first << " "<<i.second<<'\n';

			std::cout << '\n';

			std::cout << "aranacak ismi giriniz: ";

			std::string name;
			std::cin >> name;

			if (auto iter = mymap.find(name); iter != mymap.end())
			{
				std::cout << "bulundu " << iter->first << " " << iter->second << '\n';
			}

		}

	�RNEK:

		int main()
		{
			std::map<std::string, int> mymap;

			mymap.insert({ "suleyman",45 }); 
			mymap.insert({ "naciye",14 });
			mymap.insert({ "necati" ,18 });

			for (auto i : mymap)
				std::cout << i.first << " " << i.second << '\n';

			std::cout << '\n';

			std::cout << "eski ve yeni anahtarlar: ";

			std::string oldkey, newkey;
			std::cin >> oldkey>>newkey;

			if (auto iter = mymap.find(oldkey); iter != mymap.end())
			{
				auto handle = mymap.extract(iter);
				handle.key() = newkey;

				mymap.insert(std::move(handle));

				std::cout << "degistirildi \n";
			}
			else
				std::cout << "bulunamadi\n";

			for (auto i : mymap)
				std::cout << i.first << " " << i.second << '\n';

		}
	
	D�KKAT: map s�n�f�n�n k��eli parantez operat�r fonksiyonu var �ok i�e yar�yor ama �ok dikkatli kullanmam�z gerekiyor
	 
		int main()
		{
			std::map<std::string,int> mymap;

			mymap.insert({ "suleyman",45 });
			mymap.insert({ "naciye",14 });
			mymap.insert({ "necati" ,18 });

			for(auto i : mymap)
			std::cout << i.first<<" "<<i.second << " ";
		
			mymap["emre"] = 76; // e�er bu anahtar map'de varsa bu ifade map'de olan ��enin value de�erine eri�tiriyor yani bu value de�erine referans b�ylece key'i "emre" olan�n value'sunu de�i�tirmi� oluyoruz
			
			e�er key(emre) map'te mevcut ise o key'e kar��l�k gelen value'ya eri� ve onu de�i�tir demi� oluyoruz
			
			e�er "emre" map�te yoksa operator[] yeni bir { "emre", 0 } �ifti ekler (yani int i�in default de�er 0) sonra o value 76 ile de�i�tirilir
		}

		�RNEK:

			int main()
			{
				std::map<std::string, int> mymap;

				mymap.insert({ "suleyman",45 });
				mymap.insert({ "naciye",14 });
				mymap.insert({ "necati" ,18 });

				for (auto i : mymap)
					std::cout << i.first<<" "<<i.second << " ";

				std::cout << '\n';

				std::string name;
				int val;

				std::cout << "isim ve numara girin: ";

				std::cin >> name >> val;

				mymap[name] = val; // e�er key varsa o key'in value de�erini de�i�tirmi� oluyoruz
									  e�er key yoksa yeni bir pair insert edicek ve yeni key ve value de�eri eklenir
				
				for (auto i : mymap)
					std::cout << i.first << i.second << " ";
			}
			 
		�RNEK:

			int main()
			{
				std::vector<std::string svec{ "ahmet","emre","kaan","necati" };

				std::map<std::string,int> cmap;

				for(const auto& name : svec)
					++cmap[name]; // diyelim ki d�ng�n�n ilk turunda name ahmet �u an cmap bo� oldu�una g�re ahmet'i ekleyecek
									(varsa value de�erine eri�tiyordu yoksa ekleyip eklenmi� ��enin value de�erine eri�tiyordu)

									eklenmi� ��eyi eklerken value initalize ediyordu(0 de�eri) cmap'e ahmet 0 pair'inin second'a referans yoluyla eri�tirecek o secodn'� 1 artt�r�p 1 yapm�� olaca��z
									ama d�ng�n�n her hangi bir tutunda name tekrar ahmet oldu�unda ahmet de�eri mapte oldu�u i�in value de�erine eri�tirecek �rne�in value de�eri 5 ise 6 olacak
			}

		�RNEK:

			int main()
			{
				std::vector<std::string> svec{ "emre","zeynep","ahmet","kaan","kaan","necati" };

				std::map<std::string, int> cmap;


				for (const auto& name : svec)
					++cmap[name]; // e�er name map�te yoksa operator[] yeni bir {name, 0} �ifti ekler  sonra ++ ile 0 de�eri 1 olur e�er name(key) zaten varsa mevcut de�eri bir art�r�l�r

				for (const auto& [name, count] : cmap)
				{
					std::cout << name<<" "<<count<<'\n';
				}

				std::vector<std::pair<std::string, int>> vec(cmap.begin(), cmap.end()); // map i�indeki t�m (key,value) �iftlerini bir vekt�re kopyal�yoruz
			}

		�RNEK: subscript( [] ) �perat�r� yerine at fonksiyonunu kullan�rsak anahtar olmad��� zaman exception throw ediyor

			int main()
			{
				std::map<std::string, int> cmap;
       
				cmap["emre"] = 10;
        
				try
				{
            
					cmap.at("emre");  // bulundu�u i�in exception f�rlatmaz 
					cmap.at("ahmet"); //  exception f�rlat�r     
				}
				catch(const std::exception& ex)
				{
					std::cout<<"exception caught: " << ex.what() << '\n';
				}
			}
*/