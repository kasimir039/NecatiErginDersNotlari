/*

UNARY FOLD EXPRESSION
	
	ortada binary bir operat�r olmas� gerekiyor ve burda kullan�lan parantez �ncelik parantezi de�il sentaks�n gerektirdi�i parantez
	
	( + ) // parantezin i�inde hangi operator �st�nde fold expression'� olu�turuyorsak UNARY FOLD OVER + operator deniliyor

	(... + args) // ellipsis solda oldu�u i�in unary left fold
	(args + ...) // unary right fold

	ikisi aras�nda ki fark associativity(�ncelik y�n�nde)
		a)unary left fold ise -> derleyici b�yle bir kod �retiyor ((((p1 + p2) + p3) + p4) + p5)
		b)unary right fold ise -> derleyici b�yle bir kod �retiyor (p1 + (p2 + (p3 + (p4 + p5))))

		bu bir / operat�r� olsayd� left fold ve right fold'un �retti�i sonu�lar de�i�irdi

		D�KKAT: unary fold'da && operat�r� || operat�r� ve , operat�r� d���nda paket bo� olamaz

			�RNEK:

				template <typename ...Ts>
				auto sum(const Ts& ...args)
				{
					return (... + args);
				}

				int main()
				{
					auto val = sum(); 

				}

			�RNEK:

				template <typename ...Ts>
				auto sum(const Ts& ...args)
				{
					// return (... && args); // arg�man g�ndermezsek true de�eri elde edilir 
					// return (... || args); // arg�man g�ndermezsek false de�eri elde edilir
					// return (... , args); 

				}

				int main()
				{
					auto val = sum(); // && -> true de�er || -> false de�er

				}

			�RNEK:

				template <typename ...Args>
				void print(const Args&... args)
				{
					((std::cout << args << ' ') , ...) // unary right fold 
				}

				int main()
				{
					print(2,5,3.4,"neco"); // derleyici b�yle bir koda �eviriyor -> ((std::cout<<2<<' '), ((std::cout<<5<<' '), ((std::cout<<3.4<<' '), (std::cout<<"neco"<<' '))));
				}

BINARY FOLD EXPRESSION

	burda da binary operat�r kullan�lmak zorunda

	hangi operat�r �st�nde binary fold olu�turuyorsak operat�r� 2 kez yaz�yoruz

	(expression + ... + args) // ellipsis tokeni parametre paketinin sol taraf�nda kald��� i�in binary left fold -> (((((expression + p1) + p2) + p3) + p4) + p5)
	(args + ... + expression) // binary right fold	-> (p1 + (p2 + (p3 + (p4 + (p5 + expression)))))

	�RNEK:

		template <typename ...Args>
		constexpr auto sum(Args ...args)
		{
			return (args + ... + 0); //  binary fold expression'da bu sentaks ile paket bo� b�rak�labilir
		}

		int main()
		{
			constexpr auto val = sum(); // paket bo� ama ge�erli buda
		}

	�RNEK:

		template <typename ...Args>
		auto sum(Args ...args)
		{
			 (std::cout << ... << args); // fonksiyona gelen t�m arg�manlar� yazd�r�r
		}

		int main()
		{
			sum(2, 5, 6);
		}

STL(STANDARD TEMPLATE LIBRARY)
		
	STL demekle STANDARD C++ LIBRARY ayn� �ey demek de�il STL bir akronim C++ standart k�t�phanesi tamamen STL demek de�il ama STL C++'�n standart k�t�phanesinin en �nemli bile�eni 
	ve b�y�k �o�unlu�unu olu�turuyor STL bir generic library OOP'ye y�nelik bir k�t�phane de�il 

CONTAINERS

	belirli t�rden yada t�rlerden de�erleri bir arada tutan s�n�flar�n olu�turulmas� i�in kullan�lacak s�n�f �ablonlar�(vector,list gibi)

	SORU:sequence container'lar ile associative container'lar ve unordered associative container'lar aras�nda ki fark nedir?

		sequence container'lar ��eleri bir arada tutuyor ve ��elerin bir s�ras� var ��eleri ekledi�imiz zaman ekleme zaman� ya da ekleme yeriyle ilgili bir s�ra olu�uyor
		yani konum belirterek her hangi bir de�eri insert edebiliyoruz sondan ekleme yapabiliyoruz 

		associative container'lar ekleme ve s�rayla de�il de�erle yap�yor yani container'�n belirli bir i� s�ralamas� var

		unordered associative container'lar da ise s�ralama yok de�ere g�re tutuyor ama temel ama�lar� s�ralama ili�kisi olmadan var m� yok mu sorusuna cevap vermek

	sequence container'lar
		std::vector -> dinamik dizi
		std::deque _ dinamik dizilerin dizisi
		std::list -> �ifte ba�l� liste
		std::forward_list -> tekli ba�l� liste
		std::array -> C dizilerinin sarmalay�c�s�
		std::string -> amac� yaz� tutmak olan dinamik dizi

	associative container'lar(binary search tree/red black tree)
		std::set -> s�ralama ili�kisiyle birbirinden farkl� keyleri tutuyor
		std::multiset -> s�ralama ili�kisiyle keyleri tutuyor ayn� key birden fazla olabilir
		std::map -> key-value de�erlerini tutar key birbirinden farkl� olmal�d�r
		std::mutlimap -> key-value de�erlerini tutar ayn� key birden fazla olabilir

	unordered associative containers
		std::set std::map gibi a�a� (tree) tabanl� konteynerlerin hash tabanl� versiyonlar�d�r
		
		std::unordered_set -> s�ralamas� olmayan birbirinden farkl� keyleri tutar O(1) karma��kl���nda
		std::unordered_multiset -> s�ralamas� olmayan keyleri tutar ayn� key birden fazla olabilir O(1) karma��kl���nda
		std::unordered_ map -> key-value de�erlerini tutar keyler birbirinden farkl� keyleri tutar O(1) karma��kl���nda
		std::unordered_ multimap -> key-value de�erlerini tutar ayn� key birden fazla olabilir O(1) karma��kl���nda


	STL'in �ok �nemli bir �zelli�i var 
		STL'in b�t�n tasar�m� geni�letilebilirlik �st�nede kurulu STL'de bir �ok ��e var mesela di�er ��elerle birlikte olmayan bir container kullan�labilir mi? EVET
		algoritmalar yada �rne�in sequence containters i�erisinde olmayan 3.parti bir k�t�phanenin containterlar�yla da kullan�labilir yeni containerlar yeni iterat�rler olu�turabiliriz 

ITERATORS
	
	containterda tutulan ��elerin konumunu tutarlar

	pointerlar�n daha soyutlanm�� hali iterat�rleride pointer olarak kullanabiliriz ya da pointer-like bir aray�ze sahip s�n�f �eklinde kullanabiliriz

	*iter -> iterat�rler containerlardan ba��ms�zd�rlar hangi container'in iterat�r�yse o containerda de�eri olan ��eye eri�ir
	++iter -> bir sonraki ��eninin konumunu tutar
	
	�RNEK:

		template<typename Iter>
		void print_range(Iter first, Iter last)
		{
			while (first != last)
			{
				std::cout << *first++ << ' ';
			}
			std::cout << '\n';
		}

		int main()
		{
			std::vector vec{ 4,7,9,1,23,89,12 };
			print_range(vec.begin(), vec.end());

			std::list mylist{ 4,7,9,1,23,89,12 };
			print_range(mylist.begin(), mylist.end());
		}

	STL konteynerlar� s�z konusu oldu�unda iterat�rler konteynerlar�n nested type'� oluyor

	iterat�rlerin interface'inin hangi operasyonlar� sa�lad��� ve destek verdi�i iterat�r�n kategorisine ba�l�d�r

		1)input iterator
		2)output iterator
		3)forward iterator
		4)bidirectional iterator
		5)random access iterator
		6)contigues iterator(C++20)

		iterat�rlerin iterat�r kategorisi bu iterat�rlerden birine ait olmak zorunda bir iterat�r�n iterat�r kategorisinin hangi kategoride oldu�unu compile time'da da 
		meta functionlarla da s�nayabiliyoruz iterat�rlerin hangi kategoride oldu�u itrat�r�n hangi operasyonlar� sa�lad���n� belirtiyor

	RANGE(aral�k)
		STL'de range iki konumdan olu�an bir unit e�er iki konum bir range belirtiyorsa ��yle bir garanti olu�turuyor
		[konum1 konum2] konum1'i s�rekli artt�rd���m�zda belirli bir noktada konum2'ye e�it olacak yani konum1'den konum2'ye kadar olan 
		��eleri �rne�in yazd�raca��z ama konum2'ye dokunmayaca��z demek yani son ��eyi yazd�rm�yoruz

		�RNEK:copy algoritmas�(bir range'de ki ��eleri bir konuma bir konumdan ba�layarak kopyal�yor)

			template <typename InIter, typename OutIter>
			OutIter Copy(InIter beg, InIter end, OutIter destbeg)
			{
				while (beg != end)
				{
					*destbeg++ = *beg++;
				}

				return destbeg; // yazma algoritmalar� en son yazd�klar� konumdan bir sonraki konumu d�nd�r�yorlar
			}

			int main()
			{
				std::vector<int> ivec{3,6,8,1,9};
				std::list<int> ilist{9,1,4,6,7,3,6,5};

				Copy(ivec.begin(), ivec.end(), ilist.begin()); // Copy<std::vector<int>::iterator,std::list<int>::iterator>(ivec.begin(), ivec.end(), ilist.begin());

				for (auto i : ilist)
					std::cout << i << " ";
			}

			derleyicinin olu�turdu�u instantiation
				std::list<int>::iterator Copy(std::vector<int>::iterator beg,std::vector<int>::iterator end,std::list<int>::iterator destbeg)
				{
					while (beg != end)
					{
						*destbeg++ = *beg++;
					}

					return destbeg;
				}

		�RNEK
			
			template <typename InIter, typename T>
			InIter Find(InIter beg, InIter end, const T& val)
			{
				while (beg != end)
				{
					if (*beg == val)
						return beg;

					++beg;
				}

				return end;
			}

			int main()
			{
				std::list<int> ilist{ 9,1,4,6,7,3,6,5 };

				auto iter = Find(ilist.begin(), ilist.end(), 3);

				if (iter != ilist.end())
				{
					std::cout << "bulundu: " << *iter<<'\n';
				}
			}
			
		global olarak begin fonksiyonunu kullanmakla �rne�in bir vector'�n begin fonksiyonunu kullanmak aras�nda bir fark yok

			ivec.begin();
			begin(ivec);
*/