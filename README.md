# Реализация простейшего генератора абстрактного синтаксического дерева

### Заданная грамматика:
```
<Программа> ::= <Объявление переменных> <Описание вычислений>
<Описание вычислений> ::= <Список операторов>
<Объявление переменных> ::= Var <Список переменных> ;
<Список переменных> ::= <Идент> | <Идент> , <Список переменных>
<Список операторов> ::= <Оператор> | <Оператор> <Список операторов>
<Оператор>::=<Присваивание> |<Сложный оператор>
<Присваивание> ::= <Идент> := <Выражение> ;
<Выражение> ::= <Ун.оп.><Подвыражение> | <Подвыражение>
<Подвыражение> :: = ( <Выражение> ) | <Операнд> |
< Подвыражение > <Бин.оп.> <Подвыражение>
<Ун.оп.> ::= "-"
<Бин.оп.> ::= "-" | "+" | "*" | "/"|"<"|">"|"=="
<Операнд> ::= <Идент> | <Const>
|<Сложный оператор>:: = IF <Выражение> THEN <Оператор> |
IF <Выражение> THEN <Оператор> ELSE <Оператор> | <Составной 
оператор>
<Составной оператор> ::= Begin <Список операторов> End
<Идент> ::= <Буква> <Идент> | <Буква>
<Const> ::= <Цифра> <Const> | <Цифра>
```

### Инструкция по работе с компилятором
1. make all - сборка проекта
2. cat code.x | ./compiler.out, где code.x - файл с кодом

### Демонстрация работы реализованного решения
#### Тестовая программа

```
Var a, b, c, d;
a := 8;
b := 9;
c := 5;
d := 4;
IF (a > 5) THEN
Begin
 d := d / 2;
 c := b + d;
End
ELSE 
b := b - a * 3;
a := 0;
b := 0;
c := 0;
d := 0;
```

#### Полученный ассемблерный код

```
a := 8
b := 9
c := 5
d := 4
tmp_0 = a > 5
cmp_true tmp_0 label_0
tmp_1 = d / 2
d := tmp_1
tmp_2 = b + d
c := tmp_2
goto label_1
label_0:
tmp_4 = a * 3
tmp_3 = b - tmp_4
b := tmp_3
label_1:
a := 0
b := 0
c := 0
 d := 0
```

#### Построенное абстрактное синтаксическое дерево

```
+----[Program_Body](NULL)
 +----[Identifier](0)
 +----[Operator](:=)
 +----[Identifier](d)
 +----[Operators](NULL)
 +----[Identifier](0)
 +----[Operator](:=)
 +----[Identifier](c)
 +----[Operators](NULL)
 +----[Identifier](0)
 +----[Operator](:=)
 +----[Identifier](b)
 +----[Operators](NULL)
 +----[Identifier](0)
 +----[Operator](:=)
 +----[Identifier](a)
 +----[Operators](NULL)
 +----[Identifier](3)
 +----[Expression](*)
 +----[Identifier](a)
 +----[Expression](-)
 +----[Identifier](b)
 +----[Operator](:=)
 +----[Identifier](b)
 +----[Condition_Expression](NULL)
 +----[Operators](NULL)
 +----[Identifier](d)
 +----[Expression](+)
 +----[Identifier](b)
 +----[Operator](:=)
 +----[Identifier](c)
 +----[Operators](NULL)
 +----[Identifier](2)
 +----[Expression](/)
 +----[Identifier](d)
 +----[Operator](:=)
 +----[Identifier](d)
 +----[If_Else](NULL)
 +----[Identifier](5)
 +----[Expression](>)
 +----[Identifier](a)
 +----[Operators](NULL)
 +----[Identifier](4)
 +----[Operator](:=)
 +----[Identifier](d)
 +----[Operators](NULL)
 +----[Identifier](5)
 +----[Operator](:=)
 +----[Identifier](c)
 +----[Operators](NULL)
 +----[Identifier](9)
 +----[Operator](:=)
 +----[Identifier](b)
 +----[Operators](NULL)
 +----[Identifier](8)
 +----[Operator](:=)
 +----[Identifier](a)
[Root](NULL)
 +----[Variables](d)
 +----[Variables](c)
 +----[Variables](b)
 +----[Variables](a)
+----[Variables_Declaration](NULL)
```


