*01.03.2016*

*Устаревшие комментарии Стаса*
> Да начнётся вторая практика по ОСям, ещё тёпленькая после ох$нной Джавки :333
Однажды я может сделаю это не в txt-шнике, а как элитный Артем с tex-ом, но пока
да здравствует минимализм.

В прилагающейся папке всякие простенькие скриптики на баше.

#Bash Scripts

Система при попытке запустить файл смотрит в него. Если файлик начинается с `#!`, то 
система интерпретирует оставшуюся часть файла, как скрипт.

Например:

**hello.sh**
```
#!/bin/sh
echo hello
```

Система делает:
```
/bin/sh echo hello
```

Даём права на запуск `chmod +x ./hello.sh`. И радуемся жизни.

**vars.sh**

    A=5
    echo $A "$A" '$A'

Вывод: 
> 5 5 $A

Всякие циклики

    for i in 1 2 3 4
    do
        echo $i
    done

Вывод: 
> 1 2 3 4

**ls.sh**

    for i in `ls` ; do
        echo $i
    done

Вывод: аналогичен ls

\`ls\` эквивалентно $(ls) (команда в апострофах выполняется и результат подставляется в код)

Есть чудесный while.
Код 0 - true.
Код не 0 - false.

test - хорошая команда, которая проверяет expression-ы и выходит с каким-то кодом.
Можно просто обрамить квадратными скобками. Будет аналогично.
Но есть проблемы с <, >, ||, &&. Поэтому сделали двойные квадратные скобочки. 
Внутри них не действуют правила для специальных символов. Хихикс.

Баш может в арифметику:
`$((2 + 3 + $N))`
	
"Advanced Bash Scripting Guide" - для любителей 
поизвращаться есть целая библия по Башу.

    case $var in
		a)
		;;
		b)
		;;
		*) //default
		;;
	esac //ВОТ ТАКОЙ ВОТ СИНТАКСИС ММ

ТУТ ДАЖЕ ЕСТЬ ФУНКЦИИ (ГОСПОДИ 10 ИЗ 10)

	name() {
		echo $1, $2, $* //$i - итый аргумент, $* - все аргументы
	}
    
Вызов
`name arg1 arg2`

Немного очевидностей.

    a && b - если а, то запустится b.
    a || b - если a вернёт не ноль, то делает b.
    a;b - просто выполнит по порядку.

globbing - фича баша

`ls *.c` Распарсит вам масочку в `ls a.c b.c`

* \* - какая-то последовательность
* ? - любой символ

#Регулярные выражения.
Это как бы язык такой, который позволяет задавать шаблоны для строк.

    . - любой символ
    [abc], [a-zA-z] - интервалы
    [^a-k] - дополнение к группе. Всё кроме (a-k).
    R* - R 0 или более раз
    R+ - R 1 или более раз
    R? - 0 или 1 раз
    A|B - A или B
    (R) - найти и запомнить
    \1, \2 ... \i - взять значение i-ой скобочки
    ^ - начало строки
    $ - конец строки

Туториал по регуляркам есть в этих ваших интернетах.

Примеры:
Рассмотрим регулярочку
`(a+b)c\1`

Посмотрим, как регулярка подходит под строки:
*	abcab - match. Потому что в первую скобочку запомнили ab.
*	abcaab - ничего :( В первую скобочку запомнили ab, а вот aab не подходит.
*	aabcaab - match. Потому что в первую скобочку запомнили aab


#Немного про консольные утилиты (grep, sed, xargs)
##grep
Берёт регулярку и выделяет в stdout, те строчки из stdin, что подходит под эту регулярку. 
Штука довольно примитивная, но в расширенный синтаксис с помощью флажка -E умеет.
Так например, если сделать:

	echo -e > test.txt abcab'\n'abcaab'\n'aabcaab
	grep -E '(a+b)c\1' < test.txt

То в консольку выведется abcab и aabcaab.

##sed - Stream EDitor
Истинный текстовый редактор для тех, кому даже Vim кажется чересчур 
громоздким и слишком элегантным. Работать с ним в принципе, как с Vim-ом, 
только вслепую. Здорово, правда?
Из функционала регулярок нас интересует команда

	's/[regexp]/[чем]/[флаги]'
    
Собственно говоря, s значит substitute, и всё подходящее под regexp, наш доблестный sed 
заменит на то, что в [чем]. (В Vim тоже такая команда есть, кук-карекууу!) Примечателен флаг g, значащий global, так как он поменяет
все вхождения регулярки, а не только первое встреченное. Флаг самой команды -re позволит
нам применять регулярку с расширенным функционалом.
Пример:

	echo > test2.txt 123454321
	sed -re 's/([0-9]+)/\1\1/g'

Выведет нам в консольку:
`123454321123454321`.
Где найти больше информации вы знаете (MAN).


##xargs cmd.
Читает строки из ввода и запускает cmd для каждой строки.
Например:

	ls > files
	xargs rm < files

Результат попробуйте угадать или запустите данную последовательность команд
сами в самой важной папке на вашей машине.

Достойные внимания флажки xargs:

    -P <n> - запустить xargs в n потоков.
    -n <n> - применять команду не к каждой строке, а к каждым n строк.
    -I replace-str - заменяет replace-str в аргументах на что-то из stdin. 
    
Пример с последним флажком:

**a.c, b.c**

	int main(int argc, char* argv[]) {
		return 0;
	}
	
**src**
```
a
b
```
	
`xargs -I FILE gcc "FILE".c -o "FILE".o < src`
    
Соберёт нам два объектника a.o и b.o.

##pipe
Есть ~~два стула~~ несколько программ. a, b, c, d.
И мы хотим, чтобы вывод a пошёл на ввод к b, вывод b на ввод к c и так вся
эта программная многоножка бы заключилась между stdin и stdout.
Окей.
`a|b|c|d` cделает это за нас.
Так например самый первый пример из xargs можно переписать как:

	ls|xargs rm

Почему это хорошо? Потому что реализована параллельность.
Более точное описание реализации есть в `man 2 pipe` (невероятно, но да).
Примерно так: есть буфер фиксированного размера (чёт про ~64Кб заехало), 
куда пишет программа. Если он заполнился, то программа туда не пишет. 
Из этого же буфера читает следующая в пайпе программа, поэтому по мере 
чтения в буфере освобождается место. Так всё и происходит.
Если есть желание явно создать файл, исполняющий роль буфера и работающий
именно по такой технологии:

	mkfifo [filename]
    
Так например `a|b|c` можно записать, как:

	mkfifo ab; mkfifo bc
	a > ab
	b < ab > bc
	c < bc
    
Но чтобы обеспечить параллельность добавьте в конец комманды амперсанд, тогда
она запустится в фоне (bg aka background). Иначе пока не выполнится первая, вы ничерта не введёте.

Интересные команды:

`fg [job_id]` - переключает команду с id=job_id на передний план с фона.

`jobs` - выводит список программ, выполняющихся в фоне.
Подробности (НЕТ НЕ В MAN-е! По ним почему-то страниц в мане нет) в интернетах.
