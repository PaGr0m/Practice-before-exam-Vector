# Аналог std::vector

Требуется реализовать собственный аналог класса из стандартной библиотеки
`std::vector`. У него должен быть максимально похожий интерфейс, необходимые
для реализации члены класса будут описаны ниже.

Решение должно быть выполнено в виде одного заголовочного файла `vector.hpp`,
включающего в себя объявление и реализацию необходимых функций. При 
необходимости можно создавать дополнительные файлы.

## Тесты
Исходя из требования похожего интерфейса, тесты следует запускать следующим 
образом:
* Найти в `smoke_test.cpp` строку
```c++
namespace current_namespace {
    using namespace std;
}
```
* Заменить в ней `namespace std` на свой.

## Требования

### Динамическая аллокация памяти
* Вектор должен удовлетворять идиоме RAII

В `std::vector` динамическая аллокация памяти реализована следующим образом:
- Выделяется динамический массив фиксированного размера
- При его переполнении выделяется новый большего размера, содержимое старого
 копируется, старый массив удаляется
- За актуальный размер и предвыделенный отвечают члены класса `size()` и 
`capacity()`
 
При этом категорически не допускаются утечки памяти.

### Шаблонные параметры
* У вектора должен быть шаблонный параметр для типа значений, которые в нём 
хранятся
* \* У вектора должен быть шаблонный параметр для кастомного аллокатора,
от которого он будет использовать функции `allocate`, `deallocate`, 
`construct` и `destroy`

### Конструкторы (кроме главных функций)
* Конструктор, который создаёт вектор заданной длины `n`
* Конструктор, который создаёт вектор заданной длины `n` и заполняет его
указанным вторым аргументом значением
 
### Типы-члены
* `value_type`
* `allocator_type` \*
* `size_type`

### Функции-члены
* `operator[]`
* `at()` – доступ к элементу с проверкой индекса; в случае неудачи кидает
исключение
* `front()`
* `back()`
* `data()` – возвращает актуальный указатель на данные, хранящиеся в массиве.
При реаллокации старый указатель, скорее всего, будет некорректный

* `empty()` – возвращает истину, если вектор пуст
* `size()`, `capacity()` – см. пункт про динамическеую аллокацию памяти
* `reserve(n)` – обеспечивает, что в вектор вместится `n` элементов 
(включая те, которые там есть). При необходимости выделяет память. Если
заданным ограничениям удовлетворить невозможно, кидает исключение
* `shrink_to_fit()` – сократить `capacity()` до `size()`. Есть реализации, 
где при каких-то условиях функция отказывается это делать (из соображений 
производтельности)

* `clear()` – очистить контейнер
* `insert(i, value)` – вставить элемент по итератору. Если итератор не 
реализован, то по индексу
* `erase(i)` – удалить элемент по итератору. Если итератор не реализован, то 
по индексу
* `push_back()`
* `pop_back()`
* `resize(n)` – делает вектор состоящим ровно из `n` элементов. Если 
`capacity()` вектора до вызова этой функции меньше, чем `n`, то происходит 
выделение памяти. После `resize()` все элементы, доступные в векторе, должны
быть инициализированы
* `swap()`

### Свободные функции
* Операторы сравнения, которые сравнивают вектора лексикографически
* `swap()`

### Итераторы*
По возможности реализовать `RandomAccessIterator`. Он будет считаться 
условно реализованным, если класс будет поддерживать enhanced for loop.