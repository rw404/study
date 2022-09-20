# Лекция № 5-6

## Императивная парадигма

Последовательность шагов:
1. Подготовить данные(ввод)
2. Обработать(реверс)
3. Завершение(вывод)

### Язык C:
- ОС(ядро ОС)
- Язык _среднего_ уровня(высокий уровень в сравнении с asm, но использующий низкоуровневые
  инструкции)
  
```c
int
main(int argc, char **argv)
{
  ...
}
```

Старый синтаксис(от языка __B__):

```c
int
main(argc, argv) // Не определен тип argc, значит int
char ** argv;
{
  ...
}
```

Наивное решение:
```c
#include <stdio.h>
#define MAX_EL 1024

char input[MAX_EL];

int main()
{
  int cur, count = 0;
  while ((cur=getchar()) != EOF) {
    if (count == MAX_EL) {
      fprintf(stderr, "tm");
      return 1;
    } else {
      input[count++] = cur;
    }
  }
  for (int i=count-1; i>=0; --i) {
    putchar(input[i]);
  }
  
  return 0;
}
```

Input:
```bash
1 2 3 4 5 6 7
```

Output:
```bash

7 6 5 4 3 2 1
```

Проблема в определении массива и отсутсвии динамического выделения памяти.

Динамические массивы позволяют использовать рост производительности через КЭШ.

Основная проблема работы с динамической памятью:
- Частые запросы к выделению малого количества памяти.

Решение:
- Расширение динамической памяти в несколько раз/на большее число элементов, чем 1 - _Сложность
  $O(n)$_.

Проблема __интенсивного ввода текста__:
- __Текстовые редакторы__;

Модификация заключается в подключении буфера для работы с динамической памятью:
- Увеличивается размер программы(характерно для __императивной парадигмы__).

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *pInp = NULL;

#define MAX_EL 1024

char input[MAX_EL];

int main()
{
  size_t cur, count = 0;
  pInp = (char*)calloc(1, sizeof(char));

  while (fgets(input, sizeof input, stdin)) {
    int oldCount = count;
    cur = strlen(input);
    count += cur;
    pInp = (char*)realloc(pInp, count+1);
    if (!pInp) { 
      fprintf(stderr, "tm");
      return 1;
    } else {
      for (int i=0; i<cur; ++i) { 
        pInp[count-cur+i] = input[i];
    }
  }
  for (int i=count-1; i>=0; --i) {
    putchar(pInp[i]);
  }

  free(pInp)
  
  return 0;
}
```

Input:
```bash
1 2 3 4 5 6 7
```

Output:
```bash

7 6 5 4 3 2 1
```


### Язык GO

- не ООП-язык

> наследник языка C, но из его экологической ниши(автоматическая сборка мусора)

Пример Go:
```go
package main
import ("fmt"; "io/ioutil"; "os";)

func main() {
  rdr := os.Stdin
  b, err := ioutil.ReadAll(rdr) // Кортеж tuple
  if err != nil {
    panic("bad input") // Единственный способ отображения исключения
  }

  s := string(b) // ReadALL возвращает массив байтов; 
  // Для строки нужно добавить, чтобы байты понимались с кодировкой UTF-8
  // Динамическая строка

  for i := len(s)-1; i>= 0; i-- {
    fmt.Print(s[i]) // Последовательность байтов
  }
}
```

Output:
```bash

1055325432533252325132503249
```

Правильный вариант:
```go
package main
import ("fmt"; "io/ioutil"; "os"; "strings")

func main() {
  rdr := os.Stdin
  b, err := ioutil.ReadAll(rdr) // Кортеж tuple
  if err != nil {
    panic("bad input") // Единственный способ отображения исключения
  }

  s := strings.Split(string(b), "") // ReadALL возвращает массив байтов; 
  // Делим строку на символы, чтобы обращаться по индексу к символам(UTF-8) 

  // Реверс
  for i, j:=0, len(s)-1; i<j; i,j=i+1, j-1 {
    s[i], s[j] = s[j], s[i]
  }

  // Вырезку из массива объединяем в строку
  fmt.Println(strings.Join(s, ""))
}
```

Output:
```bash

7 6 5 4 3 2 1
```

- Указатели есть, но хранят исключительно адрес(для языка С, чтобы ОС понимала, какую функцию
  вызывать).
  
+:
- Простота и эффективность

### Язык Python

- создавался для научного программирования;
- управляется собственным сообществом(PEP);
- индустриальный:
  - ml-frameworks
  - web-dev

> Веб держится на LAMP(Linux_Apache_MySQL_Perl/PHP/Python)

Массив - __непрерывная__ последовательность однотипных данных
- Вырезка из массива в Python - динамическая генерация нового массива по существующему

```python
#! /usr/bin/python3
import sys

print(sys.stdin.read()[::-1])
```

Output:
```bash

7 6 5 4 3 2 1
```

### Проблемы программы

Оптимизация важна, т.к.
- много запросов к `realloc` + чтение буфера[__С__]
- с большими файлами  __С__ работает быстрее Python, используя системные вызовы, чтобы узнать
размеры файлов
- Python можно оптимизировать для аналогичных действий, но __использует лишние копии__

### Объектно-императивная парадигма

- взаимодействие через обмен объектов сообщениями

```c
C++: bool
C: typedef unsigned BOOL;

void f(bool)
void f(BOOL) // Ошибки не будет
void f(unsigned) // Компилятор скажет, что повторяется определение
```

#### C\#

```c#
using System;
public class Program
{
  static void Main(string[] args) {
    string s = Console.In.ReadToEnd();
    char[] seq = s.ToCharArray();
    Array.Reverse(seq);
    Console.Write(seq);
  }
}
```

### Обобщенное программирование

> Ортогонально ООП

- Наследование более общное, нежели статическая параметризация типов;
- STL:
  1. Создаем контейнер(ex `std::vector`);
  2. Вызываем реверсивный метод контейнера;
- __Ввод и вывод__ тоже __контейнеры__.

#### C++

- Создали контейнер `std::vector<char> ...`;
- Создаем итераторы для стандартного потока ввода;
- Копируем данные, используя итераторы.

- Как задать диапазон итератора?
  - `istream_iterator(in_stream) ~ begin()`;
  - `istream_iterator() ~ end()`.

```c++
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int
main() {
  std::vector<char> v;

  std::copy(std::istream_iterator<char>(std::cin),
      std::istream_iterator<char>(),
      std::back_inserter(v)
      );

  std::copy(v.rbegin(), v.rend(), std::ostream_iterator<char>(std::cout));
  return 0;
}
```

Output:
```bash

7654321
```
