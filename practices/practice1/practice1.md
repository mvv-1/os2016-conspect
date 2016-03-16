*16.02.2016*

#Файловые операции:
*(ЧИТАЙТЕ man 2 XXX , ЁПТА!!! но briefly ниже)*

**open
read
write
close**

```c
int open(char *path, int flags)
```

`O_RDONLY | O_WRONLY | O_RDWR | O_APPEND` - флаги доступа.

> Вернёт число - файловый дескриптор

```c
int read(int fd, void* dst, size_t size)
```

> fd - file descriptor;
dst - where to read up (buffer);
size - how much to read in bytes.
Возвращает ssize_t (< 0 - ERROR, 0 - input is over).
Может прочитать меньше (короче в мане всё есть)

```c
int write(int fd, void* src, size_t size)
```

> fd - file descriptor; src - where to take (buffer); size - how much to write in bytes.

`int close(int fd)` 

> Закрывает fd (как неожиданно-то, блять)

#Динамические и статические библиотеки.
Статическая библиотека при линковке засовывается вся в бинарник.
Динамическая - выше этого (загружается по адресу из памяти).

**hello.c**

```c
#include <stdio.h>
void hello() {
	printf("Hello World!"\n");
}
```

**main.c**
```c
void main(int argc, char** argv) {
	hello();
}
```

## Создание статической библиотеки
```
gcc *.c -o *.o -c
ar rcs libhello.a hello.o //собирает в хитрый архивчик, интерпретируемый gcc, как библиотечка
gcc -static main.o -L. -l hello -o main
```

## Создание динамической библиотеки
```
libhello.so //shared object
gcc -fPIC hello.c -c -o hello.o //Position Independent Code
gcc -shared hello.o -o libhello.so //немного магии (это и строка выше) и получаем динамическую библиотеку, ура
gcc -s main.o -L. -lhello -o main
```

```
LD_LIBRARY_PATH=. //prefix для запуска через динамическую библиотеку
export [переменная среды]={путь} //запоминает env variable для текущего терминала
```

* Задание 1: слинковать hello1 и hello2 в один main.
* Задание 2: сделать то же самое через Makefile.

Примеры можете посмотреть в папке examples.
