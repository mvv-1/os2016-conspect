#Power button to login prompt
> Author: Greg Fefelov. Отчислен со второго курса КТ. Дважды. Работает в "ВКонтакте"

#Как загружается ОС?

* Embedded controller. 
    Маленький контроллер со своей архитектурой и кучей пинов. На материнке.
* Intel Managament.
    Внутри процессора. Код не получить. Может использоваться для remote management
    
Порядок загрузки:
1. Нажали на кнопку. EC просыпается, проверяет батарею/доступность электричества, если ему всё нравится, пинает процессор с Intel Managament.
2. Процессор отправляется по адресу 0xFFFFFFF0 в незащищенном режиме. По историческим причинам (640Кб хватит всем) это оказывается джамп на какую-то часть биоса.
3. Два стула: BIOS/EFI. Они должны проинициализировать железо. BIOS ничего не знает о современных технологиях. Зато EFI знает про разметку диска, разделы и т.п.
4. Если мы загрузились из биоса, загрузчик лежит в первом секторе диска. EFI может просто выполнить код с /boot/efi/... , не используя загрузчики
5. Ядро: init(на самом деле два - один минимальный, чтобы смониторовать норм FS, другой реальный, который может находиться хрен пойми где). Udev - для Plug'n'Play
6. SysVinit - овно, upstart - что-то не взлетевшее из убунты, systemd - норм.

###Эпилог
> All software is shit. Всё очень плохо.

###Копипаста письма
Библиография:

* Про не-x86 железки в компьютере: Joanna Rutkowska, x86 considered
harmful: http://blog.invisiblethings.org/papers/2015/x86_harmful.pdf
* Про socket activation, про которую я плохо рассказал: Lennart
Poettering, systemd for Administrators XX
http://0pointer.de/blog/projects/socket-activated-containers.html
* Про то, как инициализируется процессор: Intel® 64 and IA-32
Architectures Software Developer’s Manual Volume 3 (3A, 3B, 3C & 3D):
System Programming Guide, Chapter 9:
https://www-ssl.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-system-programming-manual-325384.pdf
* Про EFI: Beyond BIOS
http://www.microbe.cz/docs/Beyond_BIOS_Second_Edition_Digital_Edition_(15-12-10)%20.pdf

Презенташка называется OS-init