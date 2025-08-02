/*

capacity

	capacity vector'�n belle�inde haz�rda bulunan yerin ka� ��eye yetti�ini d�nd�r�r size'dan b�y�k ya da e�it olabilir.
		
		int main()
		{
			std::vector<int> ivec{ 3,5,7,8 };

			auto cap = ivec.capacity();

			while (ivec.capacity() < 1'000'000u)
			{
				ivec.push_back(0);

				if (ivec.capacity() != cap)
				{
					std::cout << "reallacation occured size = " << ivec.size() << " cap: " << ivec.capacity() << '\n';
					cap = ivec.capacity();
					(void)getchar();

				}
			}

		}

reserve

	vector'�n kapasitesini art�rmak i�in kullan�l�r ancak (size) de�i�mez sadece bellek blo�unu rezerve etmi� oluyoruz

	 �ok say�da push_back yap�lacaksa ve eleman say�s�n� �nceden biliyorsak reserve fonksiyonunu �a��rmak realloc maliyetini d���r�r

		 std::vector<int> vec;

		vec.reserve(100); // kapasiteyi 100 yapar ama size hala 0'd�r

		vec.push_back(42); // art�k belle�i yeniden ay�rmadan ekleme yap�labilir


MUTATING OPERATIONS

	container'da de�i�ikli�e neden olan container'�n state'inin de�i�tiren fonksiyonlar

	1)assignment operat�r�

		int main()
		{
			std::vector<int> ivec {3,6,8,9,12};
			ivec = {2,4,6,8}; // atama operat�r fonksiyonunun initalizer list'in int a��l�m� parametreli fonksiyonu
		}

	2)assign
		 i�eri�ini tamamen de�i�tirir ve yerine yeni elemanlar koyar
		
		1. assign(count, value)
			Belirtilen say�da, belirtilen de�erden olu�an ��eleri ekler

			std::vector<int> v;
			v.assign(5, 10); // 5 tane 10 eklenir // v = {10, 10, 10, 10, 10}

		2. assign(begin, end)
			Bir aral�ktaki ��eleri vekt�re kopyalar

			std::list<int> lst{1, 2, 3, 4};
			std::vector<int> v;

			v.assign(lst.begin(), lst.end()); // v = {1, 2, 3, 4}

		3. assign(initializer_list)
			C++11 ile gelen initializer_list ile atama yapar

			std::vector<std::string> v;
			v.assign({"ali", "veli", "ay�e"}); // v = {"ali", "veli", "ay�e"}

	3)resize

		resize, bir std::vector'�n eleman say�s�n� de�i�tirir vekt�r k���lt�l�rse: fazla elemanlar silinir 
		
		vekt�r b�y�t�l�rse: yeni elemanlar varsay�lan de�erle veya belirtti�iniz de�erle eklenir.

		1. vec.resize(new_size)
			Yeni elemanlar varsay�lan de�erle (T{}) doldurulur.

			std::vector<int> v{1, 2, 3};
			v.resize(5); // v = {1, 2, 3, 0, 0}  // 2 tane 0 eklendi
		
		2. vec.resize(new_size, value)
			Yeni elemanlar value ile doldurulur.

			std::vector<std::string> v{"a", "b"};
			v.resize(4, "x"); // v = {"a", "b", "x", "x"}

		3. containerda'ki ��eleri silme

			std::vector<int> v{1, 2, 3, 4, 5};
			v.resize(3); // v = {1, 2, 3}  // 4 ve 5 silindi // 0 de�eri ge�ilirse t�m ��eleri siler

		resize sadece boyutu de�i�tirir kapasiteyi azaltmaz yeni elemanlar default ctor ile olu�turulur T tipi int ise 0 std::string ise "" bo� string olur
		
		E�er T t�r�n�n default ctoru yoksa resize(n) kullan�lamaz.	

	INSERTION FUNCTIONS
	
		1)push_back
		
			elemanlar� en sona ekler

			ekleme fonksiyonlar�n�n en b�y�k avantaj� amortized constant time (O(1) olmas�

			int main() 
			{
				std::vector<int> v;

				v.push_back(10);
				v.push_back(20);
				v.push_back(30);

				for (int x : v) 
				{
					std::cout << x << " "; // ��kt�: 10 20 30
				}
			}	

		2)insert
			belirtilen konuma bir veya birden fazla ��e eklemek i�in kullan�l�r

			 insert(const_iterator pos, const T& value);             // 1 ��e ekler
			 insert(const_iterator pos, T&& value);                  // 1 ��e (move)
			 insert(const_iterator pos, size_type count, const T& value); // count kadar kopya
			
			template< class InputIt >
			 insert(const_iterator pos, InputIt first, InputIt last);    // range
			 insert(const_iterator pos, std::initializer_list<T> ilist); // init list ile

			�RNEK:

				int main()
				{

					std::vector<std::string> svec{ "abdullah","necati","emre","kaan","oguzhan" };

					for (std::string name : svec)
					{
						std::cout << name<<" ";
					}
					std::cout << '\n';

					auto iter = svec.insert(svec.begin() + 1, "kaveh");

					for (std::string name : svec)
					{
						std::cout << name << " ";
					}
					std::cout << '\n';
				}

			3)emplace_back
				
				konteynerin sonuna yeni bir ��e in-place (yerinde) olarak ekler yani nesne bellekte do�rudan olu�turulur kopyalanmaz veya ta��nmaz

					std::vector<std::string> names;

					names.emplace_back("ay�e"); // do�rudan yerinde olu�turulur

			4)erase

				konteyn�rlar da ki ��eleri siler ve en son silinen ��eden sonra ki silinmemi� ��enin konumunu d�nd�r�yor

				container.erase(iterator); // Tek bir ��eyi siler
				container.erase(begin, end); // Belirtilen aral�ktaki ��eleri siler

				�RNEK:

					int main() {
						std::vector<int> vec{1, 2, 3, 4, 5};

						auto it = std::find(vec.begin(), vec.end(), 3);
						if (it != vec.end()) {
							vec.erase(it);
						}

						for (int v : vec) {
							std::cout << v << " ";
						}
					}
				
				�RNEK:

					std::vector<int> vec{1, 2, 3, 4, 5, 6};

					vec.erase(vec.begin(), vec.begin() + 3); // 1, 2, 3 silinir

			5)clear

				konteyn�rda bulunan t�m ��eleri siler
					
					int main() 
					{
						std::vector<int> vec{1, 2, 3, 4};

						vec.clear();  // T�m elemanlar silinir

						// vec = std::vector<int>{}; // ge�ici nesnenin size'� 0 oldu�u i�in vec'in de size'� 0 olur b�t�n ��eler silinir
						// vec = {}; // ayn� i�lemi yapar
					}
			
			6)get_allocator

				s�n�f�n kulland��� allocator'� get eder

				int main() 
				{
					std::vector<int> vec{ 1, 2, 3, 4 };

					auto a = vec.get_allocator();

					std::cout << typeid(a).name() << '\n'; // class std::allocator<int>
				}

			7)max_size

				konteyn�r�n tutabilece�i en fazla eleman say�s�n� verir static �ye fonksiyon olmamas�n�n nedeni allocator'a ba�l� olmas�

					int main()
					{
						std::vector<int> vec{ 1, 2, 3, 4 };


						std::cout<<vec.max_size(); // 4611686018427387903
					}

----------------------------------

1)sort

	std::sort(begin, end);
	std::sort(begin, end, comparator);

	Belirtilen aral�kta (iterator ile) artan s�rada s�ralama yapar

	genellikle QuickSort/HeapSort/InsertionSort hibrit algoritmas� olan Introsort kullan�r
	O(n log n) karma��kl���na sahiptir

		int main()
		{
			std::vector<int> vec{ 5, 2, 8, 1, 4 };

			std::sort(vec.begin(), vec.end());  // Artan s�ralama
			// std::sort(vec.begin(), vec.end(),std::greater{});  // b�y�kt�r operat�r� kullan�lacakt� ve s�ralama b�y�kten k����e do�ru yap�lacakt� kar��la�t�r�lan de�erler k���kt�r 
																   ve b�y�kt�r operat�rleriyle kar��la�t�r�lmak zorunda e�er kendi nesnelerimizi kar��la�t�r�yorsak k���kt�r ve b�y�kt�r 
																   operat�rleri overload edilmeli

			for (int n : vec)
				std::cout << n << " ";  // ��kt�: 1 2 4 5 8
		}
	
	�RNEK:

		class Myclass{};

		int main()
		{
			std::vector<Myclass> vec(100);

			std::sort(vec.begin(),vec.end()); // sentaks hatas� olur ��nk� derleyici bu bir fonksiyon �ablonu oldu�u i�in fonksiyonu compile time'Da yaz�yor ve compile time'da
												 sort algoritmas�ndan specialization olu�turdu�unda Myclass nesneleri k���kt�r yada b�y�kt�r oeprat�r�n�n operand� olacak
												 ama Myclass k���kt�r veya b�y�kt�r operat�r�n� overload etmedi�i i�in sentaks hatas�
		}

2)stable_sort
	s�ralama algoritmas�n�n stable olmas� demek ayn� de�ere sahip ��eler s�ralamadan �nceki g�rece konumlar�n� koruyacaklar alogirtman�n stable olmas�n�n �nemi 
	birden fazla s�ralama i�leminin yap�lmas� 

	�RNEK:

		class Person
		{
		public:
			Person(int age, std::string name) : m_age(age), m_name(std::move(name)) {}

			friend std::ostream& operator<<(std::ostream& os, const Person& p)
			{
				return os << "(" << p.m_age << "," << p.m_name << ")";
			}

			bool operator<(const Person& other) const // ya�a g�re s�ralamak i�in < operat�r�n� overload ettik
			{
				return m_age < other.m_age;
			}

		private:
			int m_age;
			std::string m_name;
		};

		int main()
		{
			std::vector<Person> pvec{
				Person(68, "Abdullah"),
				Person(22, "Abdullah"),
				Person(40, "Ahmet"),
				Person(70, "Agah"),
				Person(22, "Elif"),
				Person(22, "Cemil"),

			};

			std::stable_sort(pvec.begin(), pvec.end());  // ya�a g�re k���kten b�y��e s�raland�

			for (const auto& p : pvec)
				std::cout << p << "\n";
		}

3)is_sorted
	bir range'in s�ral� olup olmad���n� s�namam�z� sa�lar
	
	std::is_sorted(beg, end)
	std::is_sorted(beg, end, comp)

	int main()
	{
			std::vector vec{ 7,2,4,9,3,5 };

			std::cout << std::boolalpha<<std::is_sorted(vec.begin(),vec.end()) <<'\n'; // false ��nk� vector k���kten b�y��e s�ral� de�il

	} 
 
4)is_sorted_until

	s�ralaman�n bozuldu�u yerin  konumunu d�nd�r�yor 

		int main()
		{

			std::vector vec{ 1,3,4,8,12,7,45,98,13 };

			auto iter = std::is_sorted_until(vec.begin(), vec.end());

			std::cout << std::distance(vec.begin(), iter); // 7'nin indeksini d�nd�r�r

		}
*/