# Контролно 2

2018-12-15
СДП

## Вариант 2

В задачите можете да използвате наготово следните контейнери от STL: `array`, `vector`, `list`, `forward_list`, `stack` и `queue`. Всички останали структури от данни трябва да реализирате сами. Можете да използвате и помощните класове `pair` и `tuple`.

В случай, че ви потрябва хешираща функция, копирайте дадения по-долу код и използвайте наготово `getHash`. За да се компилира кодът, включете заглавния файл `<functional>`.

```cpp
template <typename T>
size_t getHash(const T &element) {
    return std::hash<T>()(element);
}

size_t getHash(const char *str) {
    return std::hash<std::string>()(str);
}
```

Забележете, че функцията връща число от тип `size_t`. То може да бъде произволно (вкл. много голямо). Ако реализирате собствен хеш, помислете как да ограничите стойността до размерите му, например като я вземете по модул.


**Задача 1.** Напишете програма, която от дадена двоична пирамида (binary heap) построява пълно двоично наредено дърво.

Програмата ви ще получи като вход N на брой цели числа.
Те трябва да бъдат съхранени в двоична пирамида (binary heap), която трябва да реализирате сами.

След това трябва, изваждайки числата едно по едно от пирамидата, да построите пълно двоично наредено дърво.
То трябва да бъде представено чрез масив.
Построяването на дървото трябва да стане със сложност не повече от O(N log N).

***Упътване:** реализирайте итератор, който обхожда дърво от дадения тип в ред ЛКД (ляво-корен-дясно). Използвайте го, за да попълните дървото с елементи.*

***Напомняне:** Пълно (complete) двоично дърво е такова, в което всички нива, освен последното са изцяло запълнени. Последното ниво е единственото, в което може да има липсващи елементи. В него всички възли са подредени възможно най-вляво.*

**Задача 2.** Напишете програма в която могат да се въведат данни за чудовища от компютърна игра, и след това да може да изчисли кои от тях са уязвими за даден тип атака.

На стандартния вход ще бъде подадено цяло число N > 0, следвано от описания на N чудовища.
Всяко чудовище се описва на отделен ред в следния формат:
* Име (символен низ, не повече от 30 символа);
* Цяло, неотрицателно число K;
* Списък от K на брой типове атаки към които това чудовище е уязвимо. Всеки тип атака е символен низ с дължина по-малка 30 символа

След въвеждането на данните за всички чудовища, вашата програма ще трябва по зададен тип атака да каже кои чудовища са уязвими към нея.
На стандартния вход ще получите цяло число P, и след него P на брой вида атаки.
За всеки вид атака трябва да изведете имената на чудовищата, които са уязвими към нея.
Ако няма нито едно такова чудовище, изведете низа `"[none]"`.

Сложността на операцията, с която по име на атака X намира и извежда уязвимите към нея чудовища трябва да бъде най-много O(L) или по-добра, където L е броят на чудовищата уязвими на X.

Входът на програмата ще отговаря на описанието и ще бъде валиден, няма нужда да го проверявате за коректност.

По-долу е дадено примерно изпълнение на програмата
```
5
Skeleton 3 shadow fire frost
Mage 2 arcane physical
Shapeshifter 2 arcane shadow
Warrior 3 fire frost lightning
Monk 3 shadow arcane lightning

4
shadow
> Skeleton Monk Shapeshifter
frost
> Warrior Skeleton
lightning
> Monk Warrior
ranged
> [none]
```