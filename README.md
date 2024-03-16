# OS IHW-1
# Чечуров Владимир Сергеевич БПИ227, ОС ИДЗ-1

## Вариант 19

Разработать программу, заменяющую все согласные буквы в заданной ASCII–строке на заглавные.

## Примечание

Компилятор не мог корректно определить функцию `mknod()` (для создания именованных каналов между процессами), поэтому в начале некоторых файлов, где она применяется указан вверху следующий код:

```
#if defined __USE_MISC || defined __USE_BSD || defined __USE_XOPEN_EXTENDED
extern int mknod (const char *__path, __mode_t __mode, __dev_t __dev)
__THROW __nonnull ((1));
#endif
```



## Решение

### 4 балла

Для решения этой задачи была написана программа, в которой процесс создает 2ой процесс, который в свою очередь создает 3ий процесс. 1ый процесс считывает содержимое файла полностью (максимум 5000 ASCII-символов), передает через неименованный канал 2ому, который заменяет строчные согласные буквы в строке на заглавные, а он в свою очередь передает 3ему через неименованный канал, и этот процесс записывает результат в файл.

1. `cr_4.c` - исполняемый файл
2. `inp1.txt`, `inp2.txt`, `inp3.txt`, `inp4.txt`, `inp5.txt` - примеры входных файлов
3. `out1.txt`, `out2.txt`, `out3.txt`, `out4.txt`, `out5.txt` - соответсвующие примеры выходных данных

При запуске программы через консоль следует указать первым аргументом - имя входного файла, вторым аргументом - имя выходного файла.

### 5 баллов

Для решения этой задачи была написана программа, в которой один процесс создает 2ой процесс, который в свою очередь создает 3ий процесс. 1ый процесс считывает содержимое файла полностью (максимум 5000 ASCII-символов), передает через именованный канал 2ому, который заменяет строчные согласные буквы в строке на заглавные, а он в свою очередь передает 3ему через именованный канал, и этот процесс записывает результат в файл.

1. `cr_5.c` - исполняемый файл
2. `inp1.txt`, `inp2.txt`, `inp3.txt`, `inp4.txt`, `inp5.txt` - примеры входных файлов
3. `out1.txt`, `out2.txt`, `out3.txt`, `out4.txt`, `out5.txt` - соответсвующие примеры выходных данных

При запуске программы через консоль следует указать первым аргументом - имя входного файла, вторым аргументом - имя выходного файла.

### 6 баллов

Для решения этой задачи была написана программа, в которой один процесс создает 2ой родственный процесс. 1ый процесс считывает содержимое файла полностью (максимум 5000 ASCII-символов), передает через неименованный канал 2ому, который заменяет строчные согласные буквы в строке на заглавные, а он в свою очередь передает обратно первому через неименованный канал, и этот 1ый процесс записывает результат в файл.

1. `cr_6.c` - исполняемый файл
2. `inp1.txt`, `inp2.txt`, `inp3.txt`, `inp4.txt`, `inp5.txt` - примеры входных файлов
3. `out1.txt`, `out2.txt`, `out3.txt`, `out4.txt`, `out5.txt` - соответсвующие примеры выходных данных

При запуске программы через консоль следует указать первым аргументом - имя входного файла, вторым аргументом - имя выходного файла.

### 7 баллов

Для решения этой задачи была написана программа, в которой один процесс создает 2ой родственный процесс. 1ый процесс считывает содержимое файла полностью (максимум 5000 ASCII-символов), передает через именованный канал 2ому, который заменяет строчные согласные буквы в строке на заглавные, а он в свою очередь передает обратно первому через именованный канал, и этот 1ый процесс записывает результат в файл.

1. `cr_7.c` - исполняемый файл
2. `inp1.txt`, `inp2.txt`, `inp3.txt`, `inp4.txt`, `inp5.txt` - примеры входных файлов
3. `out1.txt`, `out2.txt`, `out3.txt`, `out4.txt`, `out5.txt` - соответсвующие примеры выходных данных

При запуске программы через консоль следует указать первым аргументом - имя входного файла, вторым аргументом - имя выходного файла.

### 8 баллов

Для решения этой задачи было написано две программы, которые при запуске создают в ОС 2 неродственных процесса (для условности 1ый процесс - процесс программы в `cr_8.c`, второй - `cr_8_s.c`). 1ый процесс считывает содержимое файла полностью (максимум 5000 ASCII-символов), передает через именованный канал 2ому, который заменяет строчные согласные буквы в строке на заглавные, а он в свою очередь передает обратно первому через именованный канал, и этот 1ый процесс записывает результат в файл.

1. `cr_8.c` - исполняемый файл для чтения из файла и записи результата работы в файл
2. `cr_8_s.c` - исполняемый файл для замены строчных согласных букв на заглавные
3. `inp1.txt`, `inp2.txt`, `inp3.txt`, `inp4.txt`, `inp5.txt` - примеры входных файлов
4. `out1.txt`, `out2.txt`, `out3.txt`, `out4.txt`, `out5.txt` - соответсвующие примеры выходных данных

При запуске программы `cr_8.c` через консоль следует указать первым аргументом - имя входного файла, вторым аргументом - имя выходного файла. При запуске `cr_8_s.c` не нужно указывать дополнительных аргементов.

### 9 баллов

Для решения этой задачи было написано две программы, которые при запуске создают в ОС 2 неродственных процесса (для условности 1ый процесс - процесс программы в `cr_9.c`, второй - `cr_9_s.c`). 1ый процесс считывает содержимое файла частично (первые 16 байт), передает через именованный канал 2ому, который заменяет строчные согласные буквы в строке на заглавные, а потом передает обратно первому итоговую строку через именованный канал, и этот 1ый процесс записывает результат в файл (записывает 16 байт), после чего 1ый процесс снова считывает 16 байт из входного файла, передает их по именовонному каналу второму процессу...., и так продолжается по циклу, пока во входном файле есть не прочитанные символы.

1. `cr_9.c` - исполняемый файл для чтения из файла и записи результата работы в файл
2. `cr_9_s.c` - исполняемый файл для замены строчных согласных букв на заглавные
3. `inp1.txt`, `inp2.txt`, `inp3.txt`, `inp4.txt`, `inp5.txt` - примеры входных файлов
4. `out1.txt`, `out2.txt`, `out3.txt`, `out4.txt`, `out5.txt` - соответсвующие примеры выходных данных

При запуске программы `cr_9.c` через консоль следует указать первым аргументом - имя входного файла, вторым аргументом - имя выходного файла. При запуске `cr_9_s.c` не нужно указывать дополнительных аргементов.
