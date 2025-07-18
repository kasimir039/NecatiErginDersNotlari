/*

copy
	int main()
	{
		std::vector<int> ivec{ 3,9,7,};
		std::list<int> ilist{ 5,9,11,4,};

		 std::copy(ivec.begin(), ivec.end(), ilist.begin());

		 for (auto x : ilist)
		 {
			 std::cout << x << " "; // vectorde bulunan elemanlar listeye kopyaland� 3,9,7,4
		 }

	}

copy_n
	int main()
	{
		std::vector<int> ivec{ 3,9,7,};
		std::list<int> ilist{ 5,9,11,4,};
	
		std::copy_n(ivec.begin(), ivec.size(), ilist.begin());
		

		 for (auto x : ilist)
		 {
			 std::cout << x << " "; // vectorde bulunan eleman say�s� kadar t�m elemanlar� listeye kopyaland� 3,9,7
		 }

		std::copy_n(ivec.begin(), ivec.size(), std::back_inserter(ilist)); // listeye sondan ekleme yapt�k


		 for (auto x : ilist)
		 {
			 std::cout << x << " ";  // 5 9 11 4 3 9 7
		 }

	}

copy_if

	int main()
	{
		std::vector<std::string> svec{ "necati","ergin","kaan","aslan"};
		std::vector<std::string> svec2;

		size_t len;

		std::cout << "uzunlugu kac olanlar kopyalansin: ";

		std::cin >> len;

		std::copy_if(svec.begin(), svec.end(), std::back_inserter(svec2), [len](const std::string& s) { return s.length() == len;  });


		std::copy(svec2.begin(), svec2.end(), std::ostream_iterator<std::string>(std::cout, " "));
	}

copy_backward

	int main()
	{
		std::vector<int> ivec{ 3,9,7, };
		std::vector<int> destvec(7); // tane 0 de�eri eklemi� olduk

		std::copy_backward(ivec.begin(), ivec.end(), destvec.end());

		for (auto x : destvec)
		{
			std::cout << x << " "; // 0 0 0 0 3 9 7
		}

	}

reverse
	int main()
	{
		std::vector<int> ivec{ 3,9,7, };

		std::reverse(ivec.begin(), ivec.end());

		for (auto x : ivec)
		{
			std::cout << x << " "; // 7,9,3
		}

	}
	
reverse_copy
	range'in ters �evirilmi� halini bir yere kopyal�yor

	int main()
	{
		std::vector<int> ivec{ 3,9,7, };
		std::vector<int> destvec(7);

		std::reverse_copy(ivec.begin(), ivec.end(),destvec.begin());

		for (auto x : destvec)
		{
			std::cout << x << " "; // 7 9 3 0 0 0 0
		}

	}

replace

	int main()
	{
		std::vector<int> ivec{ 3,9,7,3,3 };

		std::replace(ivec.begin(),ivec.end(),3,-1);

		for (auto x : ivec)
		{
			std::cout << x << " "; // -1 9 7 -1 -1
		}

	}

replace_if

	int main()
	{
		std::vector<int> ivec{ 2,4,6,9,15,18 };


		int n = 0;
		std::cout << "kaca bolunenler: ";
		std::cin >> n;

		int val = 0;
		std::cout << "yeni deger: ";
		std::cin >> val;
	
		std::replace_if(ivec.begin(), ivec.end(), [n](int i) {return i % n == 0; },val); // n say�s�na tam b�l�nenlerin yerine val i�in girilen de�er yaz�lacak
		 
		for (auto x : ivec)
		{ 
			std::cout << x << " ";
		}

		SENARYO:
			kaca bolunenler: 2
			yeni deger: 1
			1 1 1 9 15 1
	} 

replace_copy

	int main()
	{
		std::vector<int> ivec{ 2,4,2,3,2,18 };
		std::vector<int> destvec(ivec.size());

	
		std::replace_copy(ivec.begin(), ivec.end(),destvec.begin(),2,9); // 2 say�s�n�n yerine 9 say�s� yaz�lacak

		for (auto x : destvec)
		{ 
			std::cout << x << " "; // 9 4 9 3 9 18
		}

	} 

replace_copy_if

	int main()
	{
		std::vector<int> ivec{ 2,4,2,3,2,18 };
		std::vector<int> destvec(ivec.size());


		int n = 0;
		std::cout << "kaca bolunenler: ";
		std::cin >> n;

		int val = 0;
		std::cout << "yeni deger: ";
		std::cin >> val;

		std::replace_copy_if(ivec.begin(), ivec.end(), destvec.begin(), [n](int i) { return i % n == 0; },val); // n say�s�na tam b�l�nenlerin yerine val i�in girilen de�er yaz�lacak

		for (auto x : destvec)
		{ 
			std::cout << x << " "; // 
		}

		SENARYO:
			kaca bolunenler : 2
			yeni deger : 65
			65 65 65 3 65 65

	}

SORU:herhangi bir algoritma bir range'i al�p o range'in sahibi olan container'a ekleme yada silme yapabilir mi? HAYIR ��NK� ALGOR�TMALAR ITERATOR PARAMETRES�NE SAH�P
	peki nas�l oluyorda remove gibi fonksiyonlar iterat�r al�p silme i�lemini yap�yor?

	remove

		logic silme i�lemini uygluyor ve geri d�n�� de�eri olarak asl�nda silinmemi� ��elerin end konumunu veriyor

		ger�ekten silme i�lemi yapmam container'�n size'�n� de�i�tirmem madem bize silinmemi�ler gerekiyor o zaman bu range'i sanki ��eler silinmi� gibi kullanabiliriz

		�RNEK:
			int main()
			{
				std::vector<int> ivec{ 2,4,2,3,2,18 };
				
				std::cout << "size = "<<sizeof(ivec) << '\n';

				auto logic_end_iter = remove(ivec.begin(), ivec.end(), 4);

				std::cout << "size = "<<sizeof(ivec) << '\n'; // size de�i�miyor

				for (auto x : ivec)
				{
					std::cout << x << " "; //
				}
				std::cout << '\n';

				std::cout<<"silinmemis ogelerin sayisi = "<<std::distance(ivec.begin(), logic_end_iter)<<'\n';
				std::cout<<"silimis ogelerin sayisi = "<<std::distance(logic_end_iter,ivec.end());
			}

		�RNEK: amac�m�z sadece o de�erleri container'dan ��kartmaksa ERASE REMOVE IDIOMUNU kullanmal�y�z

			int main()
			{
				std::vector<int> ivec{ 2,4,4,4,2,18 };

				std::cout << "size = " << sizeof(ivec) << '\n';

				ivec.erase(remove(ivec.begin(), ivec.end(), 4),ivec.end()); // ger�ek silme i�lemi yapt�k

				for (auto x : ivec)
				{
					std::cout << x << " "; //
				}
				std::cout << '\n';

				std::cout << "size = " << sizeof(ivec) << '\n';


				// global erase fonksiyonuyla ERASE REMOVE IDIOMUNU kullanmam�za gerek yok

					erase(ivec,4); // daha basit �ekilde silme i�lemini ger�ekle�tiriyoruz
			}

	remove_if

		int main()
		{
			std::vector<std::string> svec{ "necati","ergin","oguzhan","kaveh","mehmetcan","abdullah","veli","rasul" };

			std::cout << "enter the character: ";
			char c;
			std::cin >> c;

			svec.erase(std::remove_if(svec.begin(), svec.end(), [c](const std::string& s) { return s.find(c) != std::string::npos; }),svec.end()); // C++23 -> i�in sadece s.contains(c) yazmam�z yeterli

			for (auto x : svec)
			{
				std::cout << x << " "; //
			}
		}

		SENARYO:
			enter the character: e 
			oguzhan abdullah rasul // i�erisinde e karakteri bulunan stringler silindi

	unique
		ard���k ayn� ��elerin say�s�n� 1'e indiriyor

		�RNEK:1.overload
			int main()
			{
			std::vector<int> ivec{ 12,8,8,8,3,8,2};

			for (auto x : ivec)
			{
				std::cout << x << " "<<'\n';
			}
			
			std::cout << '\n';

			ivec.erase(std::unique(ivec.begin(), ivec.end()),ivec.end());

			for (auto x : ivec)
			{
				std::cout << x << " "<<'\n';
			}

			std::cout << '\n';

		}

		�RNEK:2.overload binary predicate al�yor

			int main()
			{
				std::vector<int> ivec{ 12,8,8,8,3,8,2};

				for (auto x : ivec)
				{
					std::cout << x << " ";
				}
				std::cout << '\n';
				auto fpred = [](int x,int y){ return x % 2 == y % 2; }; // ard���k olan x'in ve y'nin 2 ye b�l�m�nden kalanlar e�itse bunlar� silecek

				ivec.erase(std::unique(ivec.begin(), ivec.end(),fpred),ivec.end());

				for (auto x : ivec)
				{
					std::cout << x << " ";
				}

				std::cout << '\n';

			}

		M�LAKAT SORUSU: string'de birden fazla bo�luk var ve bu bo�lu�u 1'e indirmek istiyoruz

			int main()
			{
				std::string s;

				std::cout << "enter a string: ";
				std::getline(std::cin, s);

				const auto fpred = [](char c1, char c2) { return isspace(c1) && isspace(c2); };

				s.erase(std::unique(s.begin(), s.end(), fpred),s.end());

				std::cout << "[" << s << "]\n";

			}

	remove_copy_if

		int main()
		{

			std::vector<std::string> svec{ "necati","ergin","kaan","aslan" };

			std::vector<std::string> destvec;

			for (auto x : svec)
			{
				std::cout << x << " ";
			}
			std::cout << '\n';

			size_t len;

			std::cout << "uzunluk degeri girin: ";
			std::cin >> len;

			auto pred = [len](const std::string& s) { return s.length() >= len; }; 

			std::remove_copy_if(svec.begin(), svec.end(), std::back_inserter(destvec),pred); // uzunlu�u len veya daha fazla olanlar� atlayacak (kopyalamayacak) di�erlerini destvec'e ekleyecek

			for (auto x : destvec)
			{
				std::cout << x << " ";
			}
			std::cout << '\n';
		}

STL CONTAINERS

	sequence containers
		vector
		deque
		list
		forward_list
		string
		array
	
	associative containers
		set
		multi_set
		map
		multi_map

	unordered associative containers
		unordered_set
		unordered_multiset
		unordered_map
		unordered_multimap

	SORU: elimizde bir container var ve iki ayr� yolumuz var ama ikiside ayn� i�i yap�yor hangisini se�memiz gerek?
		1)algoritmay� �a��rmak
		2)container'�n fonksiyonunu �a��rmak

		CONTAINER'�n �ye fonksiyonunu se�memiz gerek ��nk� algoritma iterat�rle i�lemi yap�yor container'�n i�sel implementasyonuna eri�me imkan� yok
		
		�rne�in find algoritmas� == ile s�n�yor ama set'in kendi fonksiyonlar� equivalence kavram�n� kullan�yor �rne�in -> !(a < b) && !(b < a)  
		
	VECTOR
	
		vector'�n bool a��l�m� i�erisinde bool tutan bir vect�r de�il bir partial specialization 

		vector C++20 ile birlikte contiguous_iterator kategorisine dahil edilmi�tir bu da vector ��elerinin bellekte ard���k (contiguous) 
		�ekilde tutulmas�n�n zorunlu oldu�u anlam�na gelir yani t�m ��eler tek bir bellek blo�unda yer al�r
		
		referans wrapper
			vector<int &> // ge�ersiz

			a)container'�n T& a��l�m�n� olu�turamoyoruz ama container'�n reference wrapper specialization a��l�m�n� kullanabiliyoruz

				vector<reference_wrapper<string>>

			b)containerda nesnelerin adresini tutmak
				vector<int *> // bunun yerine daha �ok smart pointer s�n�f� kullan�l�yor 
			
		SEQUENCE CONTAINLER'LARIN CTORLARI

			a)default ctor

				ister default initalize ister value initalize edelim bu durumda default ctor �a��r�lacak
				size'�n 0 olmas� ve empty fonksiyonun true d�nd�rmesi garanti alt�nda

					vector<int> ivec;
					vector<int> ivec{};

			b)size_t parametreli ctor(fill ctor)

				vector<int> ivec(10) // container'� 10 tane 0 de�eriyle ba�lat�r �rne�in bool ise false de�eri ile pointer ise nullptr de�eri ile ba�lat�r

				containerlar�n size_t parametreli ctoru i�in containerda tutulan ��enin default constructible olmas� gerekiyor

			c)
				ival = 56;

				vector<int> ivec(10,ival); // 10 adet val de�eri olu�turur

			d)range ctor
				
				ba�ka bir container'� ba�ka bir container ile ba�latam�yoruz ama range ctoru ile bunu yapabiliyoruz

					list<int> mylist;

					vector<int> ivec = mylist; // ge�ersiz

					list mylist2 {3,5,7,9,2};

					vector<int> ivec {mylist.begin(),mylist.end()}; // ge�erli
			
			e)initalizer list ctor

				vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

				s�sl� parantezler {} ile verilen bir listeyi kullanarak vector'� ba�latmam�z� sa�lar
				
				std::vector<int> v1(10, 5); // 10 adet 5 i�erir
				std::vector<int> v2{10, 5}; // 2 eleman i�erir: 10 ve 5

				D�KKAT: �kisi farkl� ctor'ar� �a��r�r

					v1 (size_type, T) ctor
					v2 initializer_list ctor

	SORU:vect�rdeki ilk ��enin adresini kullanmak istiyoruz

		int main()
		{
			std::vector<int>{3,6,9,1,6,6};

			auto p1 = ivec.data();
			auto p2 = &ivec[0];
			auto p3 = &*ivec.begin();
			auto p4  = &ivec.front();
		}

CTAD(CLASS TEMPLATE ARGUMENT DEDUCTION C++17)
	
	vector ivec {3,6,9,2,1}; // CTAD

	int main()
	{
		list mylist{3,6,8,1};

		vector ivec2{ mylist.begin(),mylist.end()};

		for(auto x : ivec2)
		{
			std::cout<<x<<" "; // hata olmas�n�n sebebi iterat�r ��kar�m� yap�lmas�
		}
	}

Modern C++ �ncesinde ta��ma semanti�i olmad��� i�in containerlar kopyalama semanti�ine g�re �al���yordu containerlarda tutlacak ��eye ili�kin t�rlerin copy constructible olma
zorunlulu�u vard� 

i�inde emplace fiili ge�en fonksiyonlar container'�n tutaca�� nesneyi olu�turmak i�in ne copy ctoru nede move ctoru �a��r�yorlar kendilerine g�nderilen arg�manlar� 
perfect forwarding mekanizmas�yla s�n�f�n ctoruna ge�iyorlar  
*/