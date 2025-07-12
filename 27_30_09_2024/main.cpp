/*

�nceki derste typeid operat�r�yle ilgili anlat�lanlar tekrar edildi

typeid operat�r� uneveluated context olu�turuyor(i�lem kodu �retilmeyen ba�lam)

�RNEK:

	int main()
	{
		for(int i = 0; i < 50;++i)
		{
			Car* carptr = create_random_car();

			if(typeid(*carptr) == typeid(Volvo)) 
			{
				std::cout<<*carptr<<'\n';
				Volvo* vptr = static_cast<Volvo*>(carptr); // if blo�una girerse art�k Volvo oldu�unu bildimi�iz i�in static_cast yap�yoruz
				vptr->open_sunroof();
			}

			delete carptr;
		}
	}

	SORU:derleyicinin �retti�i kodda Volvo olup olmad���n� nas�l anl�yoruz?

		run time polimorfizminde derleyiciler virtual dispatch i�in virtual function table olu�turuyorlar ve polimorfik s�n�f nesnesinin i�ine bu tabloyu g�sterecek bir pointer g�m�yorlard�
		polimorfik �a�r�y�da compile time'da bir indekse d�n��t�r�p pointer�n g�sterdi�i nesnenin virtual function table pointer�na eri�ip o tablodaki belirli indeksteki fonksiyonu �a��r�yorlard�


	SORU:hangisinin maliyeti daha y�ksek dynamic_cast mi yoksa typeid mi ?
		
		dynamic_cast operat�r�n�n maliyeti daha y�ksek Car* t�r�nden Volvo* t�r�ne cast etti�imizde onun bir Volvo old�unu anlamam�z i�in
		s�n�f hiyerar�isinde en dibe kadar gitmek zorunda ama typeid sadece belirli t�re bak�yor
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXCEPTION HANDLING

	exception handling asl�nda error handling'in alt ba�l�klar�ndan biri

	ERROR(RUN TIME ERROR)
		
		run time error ile programming erroru kar��t�rmamam�z laz�m
			programming error(yazd���m�z kodda hata var kod beklenen i�i yapam�yor)
		 
		programmin error'dan bahsediyorsak assertionlar� kullanmam�z laz�m 2 ayr� kategoriye ayr�l�yor
			1)static assertions(compile time'a ili�kin)
				
			2)dynamic assertions(run time'a ili�kin)

		bir fonksiyon i�ini yapamad��� zaman kendisini �a��ran kod yada kodlar� bu durumdan nas�l haberdar edece�i ERROR HANDLING deniliyor
		error handling'in alt kategorisi exceptin handling

		bir fonksiyonun i�ini yapamamas� ne demek
			1)pre-conditions
				a)fonksiyon �a��r�ld���nda olu�mas� gereken durum olu�mu� mu?
					
					pre-conditions sa�lanm�yorsa fonksiyonu �a��ran kod buun ger�ekle�tirememi�se 2 tane farkl� yakla��m var
						1)narrow contract
							bir fonksiyonun belirli ko�ullar alt�nda do�ru �al��aca�� anlam�na gelir Bu ko�ullar kullan�c� taraf�ndan sa�lanmak zorundad�r
							Aksi durumda undefined behavior olabilir

						2)wide contract yada broad contract(fonksiyon pre-conditionsun sa�lan�p sa�lanmad���n� kendisi kontrol ediyor)
							fonksiyonun daha esnek oldu�unu ve �o�u durumda g�venli �al��t���n� belirtir. Fonksiyon kendi i�inde kontroller yapar, yanl�� kullan�m durumlar�nda 
							hata �retir, ama tan�ms�z davran��a girmez.

				pre-conditionst'da �nemli olan di�er durum fonksiyonun �a��rd��� fonksiyonun pre-conditionslar�
					double foo(double)
					{
						bar(x); // �rne�in arg�man olacak ifadenini de�erini hesaplamas� gerekiyor ama hesaplayam�yor bar'�n pre-condtionsunu sa�layamad��� i�in
						i�ini yapam�yor
					}

			2)post conditions
				fonksiyon i�ini yapt���nda olu�mas� gereken durum e�er bir fonksiyon olmas� gereken durumu sa�layam�yorsa bu bir error demektir
			
			3)invariants(bir s�n�f�n veya sistemin belirli bir durumda ya da hayat d�ng�s� boyunca her zaman do�ru kalmas� gereken ko�ul)
				fonksiyon i�ini yapmadan �nce s�n�f nesnesinin ge�erli durumunu biliyor ve i�ini yapt�ktan sonra s�n�f�n ge�erli durumunu devam ettiriyor(valid state)  

		�zetle error demek
			1)post-conditionsun kar��lanmamas�
			2)fonksiyon i�inde yap�aln fonksiyon �a�r�lar�nda kullan�lacak arg�manlar�n pre-conditionsu sa�layamamas�
			3)narrow yada wide contract kullan�l�p kullanlmad���na ba�l� olarak fonksiyona gelen arg�manlar�n fonkiyonun istedi�i d�k�mante etti�i �zellikte olmamas�

	ERROR HANDLING

		fonksiyonun kendisini �a��ran kodu yada kodlar� bu durumdan haberdar etmesine ERROR HANDLING denir ve 2 ye ayr�l�r
			1)traditional error handling
				fonksiyonun i�ini yapamamas� durumunda i�ini yapamad���na ili�kin bir hata de�erini kendsini �a��ran koda geri d�n�� mekanzimas�yla iletmek
					int do_something(params); // �rne�in fonksiyonun geri d�n�� de�eri -1 ise bu fonksiyon i�ini yapamama�� demektir
					FILE* fopen(params) // �rne�in bu fonksiyonun geri d�n�� de�eri nullptr ise i�ini yapamam�� demektir
			
				traditional error handlingte k�t� olan durumlar neler?
					1)forcing(zorlay�c� de�il) yani program sonlanmaz
					2)hata i�leyen kodla i� g�ren kod i� i�e ge�mi� olmas� if deyimlerinin �ok kullan�lmas�(ne kadar if deyimi varsa o kadar test yazmam�z gerekir)
					3)program�n ak��� hata olmas� durumunda hatay� tespit eden koddan hatay� i�leyen koda do�rudan y�nlendirilmiyor t�m fonksiyonlar kendisini �a��ran fonksiyona hata durumunu bildirebiliyor

			2)exception handling
				
				throw statement
					hatay� testip eden kodun daha �st katmanlardaki kodlar� hata durumundan haberdar eder
			
				try(try block)
					run time'da hata g�nderilmesi durumunda hataya m�dahele edece�imizi belirleyen hatan�n olu�aca�� kod aral���n� belirler

				catch
					expceptiona m�dahele eden kodu olu�turmak i�in catch blo�u kullan�l�r
			
				exceptionu throw etmek ne demek?
					exception f�rlatmak run time'da  bir hata durumu olu�tu�unda, bu hatay� bildirmek ve farkl� bir yere genelde �st fonksiyonlara iletmek i�in kullan�l�r
					hcall chaindeki bir fonksion error durumuna d��t��� zaman error'a i�arete eden bir hata nesnesi olu�turuyor b�y�k �o�unlukla bir polimorfik s�n�fn nesnesi ama olmak zorunda de�il
					yukar�daki kodlara g�nderiliyor yukar�daki kodlardan i�inde try blo�u olan hatay� yakal�yor hatay� yakalarsa porgram�n ak��� expdetionu throw eden koddan exceptionu catch eden koda 
					ilgili catch blo�una �ekiliyor

					void foo()
					{
						// throw expr; // exception object 

						throw state'teki nesnesinn kendisi g�nderilmiyor throw ifadesi her zaman derleyicinin olu�turaca�� hata nesnesini initialize etmek i�in kullan�l�yor
						derleyici asl�nda kendisi bir nesne olu�turucak ve g�nderdi�i nesne kendisinin olu�turdu�u nesne olucak 
					}

					e�er g�nderilen hata nesnesi daha �st katmanlardan birinde yakalanmazsa buna UNCAUGHT EXCEPTION deniliyor ve std::terminate fonksiyonu �a��r�l�yor program sonland�r�l�yor
					customization point'imiz var normalde std::terminate fonksiyonunun default davran��� var C'den gelen std::abort fonksiyonunu �a��rmak bu fonksiyon hi� bir �nlem almadan program� 
					sonland�ran fonksiyon hi� bir customization noktas�ndan istifade etmemi�sek terminate fonksiyonunun �a��r�lmas� demek abort fonksiyonunun �a��r�lmas� demek

						void foo()
						{
							std::cout<<"foo called\n";
							throw 1;

							std::cout<<"foo is still running\n"; // exceptionun g�nderilmesiyle bu sat�r �al��maycak
						}

						int main()
						{
							foo(); // hata yakalnmad��� i�in terminate fonksiyonunun default hali yani abort �a��r�l�r
						}
						
						terminate fonksiyonunun default davran���n� set_terminate fonksiyonuyla de�i�tirebiliyoruz 
							terminate_handler set_terminate(terminate_handler);

						void my_terminate()
						{
							std::cout << "my_terminate called\n";
							std::exit(EXIT_FAILURE);
						}

						void foo()
						{
							std::cout << "foo called\n";
							throw 1;

							std::cout << "foo is still running\n"; // exceptionun g�nderilmesiyle bu sat�r �al��maycak
						}

						int main()
						{
							std::set_terminate(my_terminate);
							foo(); // terminate fonksiyonu art�k abort fonksiyonunu �a��rmayacak bizim yazd���m�z my_terminate fonksiyonunu �a��racak
						}

						exepction handling 2 ayr� �ekilde kullan�l�yor
							1)resumptive
								fonksiyon i�ini yapamd�ysa program� sonland�rmak yerine program �al��maya devam ediyor ama program�n in a valid state'i devam etmesi gerekiyor
							
							2)terminative
								program b�y�k bir hataya d��t���nde gerekli �nlemler al�narak program sa�l�kl� bir �ekilde sonland�r�l�r

						peki bir exceptionu nas�l yakalar�z?
							
							void foo()
							{
								std::cout << "foo called\n";
								throw 14; // int parametreli catch blo�u �al��r

								std::cout << "foo is still running\n"; // exceptionun g�nderilmesiyle bu sat�r �al��maycak
							}

							void baz()
							{
								foo();
							}
							void bar()
							{
								baz();
							}
							int main()
							{
								try { // try blo�u �u anlama geliyor bu block i�inde �al��an kodlardan biri exception throw ederse o hatay� burda yakalamaya �al���yoruz
										// try blo�undan sonra bir yada birden fazla catch blo�u olmas� gerekiyor ama t�rleri farkl� olmak zorunda

									// int x = 10;

									bar();

									// try blo�u i�erisinde �al��an kodlardan biri exception throw ederse g�nderieln expcetion nesnesinin t�r�ne g�re olan catch blo�una girecek
								}
								catch (int) // catch bloklar�da block scope'a sahip ve buradaki t�r her hangi bir t�rden olabilir ve catch parametresini catch blo�u i�erisinde kullanmayacaksak
											  //	 isim vermek zorunda de�iliz
								{
									// x ismini burada kullanamay�z ��nk� try block bir scope olu�turuyor
									std::cout << "exception caught catch(int)\n";

									try blo�unda �a��r�lan bar fonksiyonu call chaining durumu oluyor foo fonksiyonu int de�er throw etti�i i�in program�n ak��� iny parametreli catch blo�una giriyor
									e�er throw edilen de�er t�r�nden catch blo�u yoksa uncaught exception olurdu ��nk� bu t�rler i�in burda conversion s�z konusu de�il
								}
								catch (double)
								{
									std::cout << "exception caught catch(double)\n";

								}

								std::cout << "main devam ediyor\n";

							}

							�IKTI:
							foo called
							exception caught catch(int)
							main devam ediyor

						catch blo�unda olan t�rler i�in s�n�rl� say�da conversion var

							class Base{};
							class Der : public Base{};
							
							void foo()
							{
								std::cout << "foo called\n";
								throw Der(); // Her Der bir Base oldu�u i�in Base& parametreli catch blo�u �al���r

								std::cout << "foo is still running\n"; 
							}
							void baz()
							{
								foo();
							}
							void bar()
							{
								baz();
							}

							int main()
							{
								
								try
								{
									bar();
								}
								catch(const Base&)
								{
									std::cout<<"exception caught catch(Base&)\n";
								}

								std::cout<<"main devam ediyor\n";
							}

					throw ifadesiyle g�nderilen hata nesnesiyle birlikte yukar�daki kodlara 2 farkl� �ekilde bilgi vermi� oluyoruz
						1)throw edilen nesnenin t�r�(�o�unlukla s�n�f t�r�nden olacaklar)
						2)throw edilen hata nesnesinin t�r� hatan�n neyle ilgili oldu�u konusunda bilgi veriyor

					exceptionu handle edecek kodu yazacaksak expception �st�nde set i�lemi yapmayacaksak kesinlikle catch parametresi const l value ref olmal�
						try{

						}
						catch(const std::exception &ex)
						{

						}
					
					g�nderilen hata nesnesinin std::exception t�r�nden olmas� ne demek?
						
						exception handligte kullan�lan s�n�flar�n polimorfik taban s�n�f hangi hata olursa olsun yakalar

					exception s�n�f�n�n const char* d�nd�ren virtual olan WHAT fonksiyonu t�remi� s�n�flar bu fonksiyonu override ediyorlar 
						
						try{

						}
						catch(const std::exception &ex)
						{
							ex.what(); // virtual dispatch devreye girer g�nderilen hata logic error ise onun what override'� �a��r�lacak
						}
				
					�RNEK:

						void foo(size_t idx)
						{
							std::string name{"deniz akkus"};

							auto c = name.at(idx);
						}
						
						int main()
						{
							try{
								foo(56);
							}
							catch(const std::out_of_range& ex) // yakalan�r
							{
								ex.what();
							}
							catch(const std::logic_error& ex) // yakalan�r
							{
								ex.what();
							}

							catch(const std::exception& ex) // bu catch blo�u en ba�ta olursa di�er catch bloklar�na girmez buna girer ��nk� exception s�n�f� di�er s�n�flar�n taban s�n�f� 
							{								   e�er di�er catch bloklar�na girmezse buraya mutlaka girecek
								ex.what();
							}

						}

	ZOMBIE OBJECT
		Bir nesnenin �mr� bitmi� ama nesneye ait bellek alan�na hala eri�iliyor demektir
		Yani nesne yok ama hayaleti kalm�� gibi davran�l�yor Bu y�zden "zombie" denir.
	
		Base* ptr = new Base();
		delete ptr;
		ptr->foo();
*/