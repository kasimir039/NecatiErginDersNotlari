/*

önceki derste typeid operatörüyle ilgili anlatýlanlar tekrar edildi

typeid operatörü uneveluated context oluþturuyor(iþlem kodu üretilmeyen baðlam)

ÖRNEK:

	int main()
	{
		for(int i = 0; i < 50;++i)
		{
			Car* carptr = create_random_car();

			if(typeid(*carptr) == typeid(Volvo)) 
			{
				std::cout<<*carptr<<'\n';
				Volvo* vptr = static_cast<Volvo*>(carptr); // if bloðuna girerse artýk Volvo olduðunu bildimiðiz için static_cast yapýyoruz
				vptr->open_sunroof();
			}

			delete carptr;
		}
	}

	SORU:derleyicinin ürettiði kodda Volvo olup olmadýðýný nasýl anlýyoruz?

		run time polimorfizminde derleyiciler virtual dispatch için virtual function table oluþturuyorlar ve polimorfik sýnýf nesnesinin içine bu tabloyu gösterecek bir pointer gömüyorlardý
		polimorfik çaðrýyýda compile time'da bir indekse dönüþtürüp pointerýn gösterdiði nesnenin virtual function table pointerýna eriþip o tablodaki belirli indeksteki fonksiyonu çaðýrýyorlardý


	SORU:hangisinin maliyeti daha yüksek dynamic_cast mi yoksa typeid mi ?
		
		dynamic_cast operatörünün maliyeti daha yüksek Car* türünden Volvo* türüne cast ettiðimizde onun bir Volvo oldðunu anlamamýz için
		sýnýf hiyerarþisinde en dibe kadar gitmek zorunda ama typeid sadece belirli türe bakýyor
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXCEPTION HANDLING

	exception handling aslýnda error handling'in alt baþlýklarýndan biri

	ERROR(RUN TIME ERROR)
		
		run time error ile programming erroru karýþtýrmamamýz lazým
			programming error(yazdýðýmýz kodda hata var kod beklenen iþi yapamýyor)
		 
		programmin error'dan bahsediyorsak assertionlarý kullanmamýz lazým 2 ayrý kategoriye ayrýlýyor
			1)static assertions(compile time'a iliþkin)
				
			2)dynamic assertions(run time'a iliþkin)

		bir fonksiyon iþini yapamadýðý zaman kendisini çaðýran kod yada kodlarý bu durumdan nasýl haberdar edeceði ERROR HANDLING deniliyor
		error handling'in alt kategorisi exceptin handling

		bir fonksiyonun iþini yapamamasý ne demek
			1)pre-conditions
				a)fonksiyon çaðýrýldýðýnda oluþmasý gereken durum oluþmuþ mu?
					
					pre-conditions saðlanmýyorsa fonksiyonu çaðýran kod buun gerçekleþtirememiþse 2 tane farklý yaklaþým var
						1)narrow contract
							bir fonksiyonun belirli koþullar altýnda doðru çalýþacaðý anlamýna gelir Bu koþullar kullanýcý tarafýndan saðlanmak zorundadýr
							Aksi durumda undefined behavior olabilir

						2)wide contract yada broad contract(fonksiyon pre-conditionsun saðlanýp saðlanmadýðýný kendisi kontrol ediyor)
							fonksiyonun daha esnek olduðunu ve çoðu durumda güvenli çalýþtýðýný belirtir. Fonksiyon kendi içinde kontroller yapar, yanlýþ kullaným durumlarýnda 
							hata üretir, ama tanýmsýz davranýþa girmez.

				pre-conditionst'da önemli olan diðer durum fonksiyonun çaðýrdýðý fonksiyonun pre-conditionslarý
					double foo(double)
					{
						bar(x); // örneðin argüman olacak ifadenini deðerini hesaplamasý gerekiyor ama hesaplayamýyor bar'ýn pre-condtionsunu saðlayamadýðý için
						iþini yapamýyor
					}

			2)post conditions
				fonksiyon iþini yaptýðýnda oluþmasý gereken durum eðer bir fonksiyon olmasý gereken durumu saðlayamýyorsa bu bir error demektir
			
			3)invariants(bir sýnýfýn veya sistemin belirli bir durumda ya da hayat döngüsü boyunca her zaman doðru kalmasý gereken koþul)
				fonksiyon iþini yapmadan önce sýnýf nesnesinin geçerli durumunu biliyor ve iþini yaptýktan sonra sýnýfýn geçerli durumunu devam ettiriyor(valid state)  

		özetle error demek
			1)post-conditionsun karþýlanmamasý
			2)fonksiyon içinde yapýaln fonksiyon çaðrýlarýnda kullanýlacak argümanlarýn pre-conditionsu saðlayamamasý
			3)narrow yada wide contract kullanýlýp kullanlmadýðýna baðlý olarak fonksiyona gelen argümanlarýn fonkiyonun istediði dökümante ettiði özellikte olmamasý

	ERROR HANDLING

		fonksiyonun kendisini çaðýran kodu yada kodlarý bu durumdan haberdar etmesine ERROR HANDLING denir ve 2 ye ayrýlýr
			1)traditional error handling
				fonksiyonun iþini yapamamasý durumunda iþini yapamadýðýna iliþkin bir hata deðerini kendsini çaðýran koda geri dönüþ mekanzimasýyla iletmek
					int do_something(params); // örneðin fonksiyonun geri dönüþ deðeri -1 ise bu fonksiyon iþini yapamamaýþ demektir
					FILE* fopen(params) // örneðin bu fonksiyonun geri dönüþ deðeri nullptr ise iþini yapamamýþ demektir
			
				traditional error handlingte kötü olan durumlar neler?
					1)forcing(zorlayýcý deðil) yani program sonlanmaz
					2)hata iþleyen kodla iþ gören kod iç içe geçmiþ olmasý if deyimlerinin çok kullanýlmasý(ne kadar if deyimi varsa o kadar test yazmamýz gerekir)
					3)programýn akýþý hata olmasý durumunda hatayý tespit eden koddan hatayý iþleyen koda doðrudan yönlendirilmiyor tüm fonksiyonlar kendisini çaðýran fonksiyona hata durumunu bildirebiliyor

			2)exception handling
				
				throw statement
					hatayý testip eden kodun daha üst katmanlardaki kodlarý hata durumundan haberdar eder
			
				try(try block)
					run time'da hata gönderilmesi durumunda hataya müdahele edeceðimizi belirleyen hatanýn oluþacaðý kod aralýðýný belirler

				catch
					expceptiona müdahele eden kodu oluþturmak için catch bloðu kullanýlýr
			
				exceptionu throw etmek ne demek?
					exception fýrlatmak run time'da  bir hata durumu oluþtuðunda, bu hatayý bildirmek ve farklý bir yere genelde üst fonksiyonlara iletmek için kullanýlýr
					call chaindeki bir fonksiyon error durumuna düþtüðü zaman error'a iþaret eden bir hata nesnesi oluþturuyor büyük çoðunlukla bir polimorfik sýnýfn nesnesi ama olmak zorunda deðil
					yukarýdaki kodlara gönderiliyor yukarýdaki kodlardan içinde try bloðu olan hatayý yakalýyor hatayý yakalarsa programýn akýþý expcetionu throw eden koddan exceptionu catch eden koda 
					ilgili catch bloðuna çekiliyor

					void foo()
					{
						// throw expr; // exception object 

						throw state'teki nesnesinn kendisi gönderilmiyor throw ifadesi her zaman derleyicinin oluþturacaðý hata nesnesini initialize etmek için kullanýlýyor
						derleyici aslýnda kendisi bir nesne oluþturucak ve gönderdiði nesne kendisinin oluþturduðu nesne olucak 
					}

					eðer gönderilen hata nesnesi daha üst katmanlardan birinde yakalanmazsa buna UNCAUGHT EXCEPTION deniliyor ve std::terminate fonksiyonu çaðýrýlýyor program sonlandýrýlýyor
					customization point'imiz var normalde std::terminate fonksiyonunun default davranýþý var C'den gelen std::abort fonksiyonunu çaðýrmak bu fonksiyon hiç bir önlem almadan programý 
					sonlandýran fonksiyon hiç bir customization noktasýndan istifade etmemiþsek terminate fonksiyonunun çaðýrýlmasý demek abort fonksiyonunun çaðýrýlmasý demek

						void foo()
						{
							std::cout<<"foo called\n";
							throw 1;

							std::cout<<"foo is still running\n"; // exceptionun gönderilmesiyle bu satýr çalýþmaycak
						}

						int main()
						{
							foo(); // hata yakalnmadýðý için terminate fonksiyonunun default hali yani abort çaðýrýlýr
						}
						
						terminate fonksiyonunun default davranýþýný set_terminate fonksiyonuyla deðiþtirebiliyoruz 
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

							std::cout << "foo is still running\n"; // exceptionun gönderilmesiyle bu satýr çalýþmaycak
						}

						int main()
						{
							std::set_terminate(my_terminate);
							foo(); // terminate fonksiyonu artýk abort fonksiyonunu çaðýrmayacak bizim yazdýðýmýz my_terminate fonksiyonunu çaðýracak
						}

						exepction handling 2 ayrý þekilde kullanýlýyor
							1)resumptive
								fonksiyon iþini yapamdýysa programý sonlandýrmak yerine program çalýþmaya devam ediyor ama programýn in a valid state'i devam etmesi gerekiyor
							
							2)terminative
								program büyük bir hataya düþtüðünde gerekli önlemler alýnarak program saðlýklý bir þekilde sonlandýrýlýr

						peki bir exceptionu nasýl yakalarýz?
							
							void foo()
							{
								std::cout << "foo called\n";
								throw 14; // int parametreli catch bloðu çalýþr

								std::cout << "foo is still running\n"; // exceptionun gönderilmesiyle bu satýr çalýþmaycak
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
								try { // try bloðu þu anlama geliyor bu block içinde çalýþan kodlardan biri exception throw ederse o hatayý burda yakalamaya çalýþýyoruz
										// try bloðundan sonra bir yada birden fazla catch bloðu olmasý gerekiyor ama türleri farklý olmak zorunda

									// int x = 10;

									bar();

									// try bloðu içerisinde çalýþan kodlardan biri exception throw ederse gönderieln expcetion nesnesinin türüne göre olan catch bloðuna girecek
								}
								catch (int) // catch bloklarýda block scope'a sahip ve buradaki tür her hangi bir türden olabilir ve catch parametresini catch bloðu içerisinde kullanmayacaksak
											  //	 isim vermek zorunda deðiliz
								{
									// x ismini burada kullanamayýz çünkü try block bir scope oluþturuyor
									std::cout << "exception caught catch(int)\n";

									try bloðunda çaðýrýlan bar fonksiyonu call chaining durumu oluyor foo fonksiyonu int deðer throw ettiði için programýn akýþý iny parametreli catch bloðuna giriyor
									eðer throw edilen deðer türünden catch bloðu yoksa uncaught exception olurdu çünkü bu türler için burda conversion söz konusu deðil
								}
								catch (double)
								{
									std::cout << "exception caught catch(double)\n";

								}

								std::cout << "main devam ediyor\n";

							}

							ÇIKTI:
							foo called
							exception caught catch(int)
							main devam ediyor

						catch bloðunda olan türler için sýnýrlý sayýda conversion var

							class Base{};
							class Der : public Base{};
							
							void foo()
							{
								std::cout << "foo called\n";
								throw Der(); // Her Der bir Base olduðu için Base& parametreli catch bloðu çalýþýr

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

					throw ifadesiyle gönderilen hata nesnesiyle birlikte yukarýdaki kodlara 2 farklý þekilde bilgi vermiþ oluyoruz
						1)throw edilen nesnenin türü(çoðunlukla sýnýf türünden olacaklar)
						2)throw edilen hata nesnesinin türü hatanýn neyle ilgili olduðu konusunda bilgi veriyor

					exceptionu handle edecek kodu yazacaksak expception üstünde set iþlemi yapmayacaksak kesinlikle catch parametresi const l value ref olmalý
						try{

						}
						catch(const std::exception &ex)
						{

						}
					
					gönderilen hata nesnesinin std::exception türünden olmasý ne demek?
						
						exception handligte kullanýlan sýnýflarýn polimorfik taban sýnýf hangi hata olursa olsun yakalar

					exception sýnýfýnýn const char* döndüren virtual olan WHAT fonksiyonu türemiþ sýnýflar bu fonksiyonu override ediyorlar 
						
						try{

						}
						catch(const std::exception &ex)
						{
							ex.what(); // virtual dispatch devreye girer gönderilen hata logic error ise onun what override'ý çaðýrýlacak
						}
				
					ÖRNEK:

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
							catch(const std::out_of_range& ex) // yakalanýr
							{
								ex.what();
							}
							catch(const std::logic_error& ex) // yakalanýr
							{
								ex.what();
							}

							catch(const std::exception& ex) // bu catch bloðu en baþta olursa diðer catch bloklarýna girmez buna girer çünkü exception sýnýfý diðer sýnýflarýn taban sýnýfý 
							{								   eðer diðer catch bloklarýna girmezse buraya mutlaka girecek
								ex.what();
							}

						}

	ZOMBIE OBJECT
		Bir nesnenin ömrü bitmiþ ama nesneye ait bellek alanýna hala eriþiliyor demektir
		Yani nesne yok ama hayaleti kalmýþ gibi davranýlýyor Bu yüzden "zombie" denir.
	
		Base* ptr = new Base();
		delete ptr;
		ptr->foo();
*/