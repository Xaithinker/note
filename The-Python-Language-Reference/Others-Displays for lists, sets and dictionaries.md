# Displays for lists, sets and dictionaries
为了构造一个列表，一个集合或一个字典，Python提供了一种称为`displays`的特殊语法，每种语法都有两种形式：
- 容器内容是明确列出的，或者
- 它们是通过一组循环和过滤指令计算出来的，称为*comprehension*(解析)。

解析语法
```
comprehension ::=  expression comp_for
comp_for      ::=  ["async"] "for" target_list "in" or_test [comp_iter]
comp_iter     ::=  comp_for | comp_if
comp_if       ::=  "if" expression_nocond [comp_iter]
```
`Comprehension`包括单个表达式，后跟至少一个`for`子句和零个或多个`for`或`if`子
句。在这种情况下，新容器的元素是通过将每个`for`或`if`子句从左到右嵌套，并且
每次到达最内部块时计算表达式以产生元素而生成的元素。

示例：
```python
>>> [x+y for x in range(2) for y in range(x, x+5)]
[0, 1, 2, 3, 4, 2, 3, 4, 5, 6]
```

# Displays
> From [PEP 448 -- Additional Unpacking Generalizations](https://www.python.org/dev/peps/pep-0448/)

让我们看几则示例：
## List displays
```
list_display ::= "[" [starred_list | comprehension] "]"
```
`*` 星号用来解析迭代对象(*iterable unpacking*), 故其操作对象必须是**可迭代对象**
```python
>>> [*range(3), 4, 5]
[0, 1, 2, 4, 5]
```
当然下面的行为似乎是显然的，但其验证了结果的正确性
```python
>>> [*[1, 2, 3, 4, ]]
[1, 2, 3, 4]
```
使用`列表解析`示例:
```python
>>> [x for x in range(5)]
[0, 1, 2, 3, 4]
```

## Set displays
```
set_display ::=  "{" (starred_list | comprehension) "}"
```
集合对象从定义来看，区别是由一对`{ }`括起来的，注意其与字典类的区别，后者显然是由`key:value`对组成。

示例：
```python
>>> {*range(3), 4, 5}
{0, 1, 2, 4, 5}
>>> {*[1, 2, 3, 4, 5]}
{1, 2, 3, 4, 5}
```
使用`解析`示例：
```python
>>> {x for x in range(5)}
{0, 1, 2, 3, 4}
```

## Dictionary displays
字典显示是用花括号括起来的可能为空的一系列`key:value`对：
```
dict_display       ::=  "{" [key_datum_list | dict_comprehension] "}"
key_datum_list     ::=  key_datum ("," key_datum)* [","]
key_datum          ::=  expression ":" expression | "**" or_expr
dict_comprehension ::=  expression ":" expression comp_for
```
使用`**`双星号来代表解析字典(*dictionary unpacking*)
示例：
```python
>>> dict(**{'x':1,'y':2},z=3)
{'x': 1, 'y': 2, 'z': 3}
>>> {**{'x':1, 'y':2}, 'z':3}
{'x': 1, 'y': 2, 'z': 3}
```
我们知道字典的`key`是`hashable`，其不允许可变类型同时其值也只有一个。所以下面行为具有合理性:
```python
>>> {'x': 1, **{'x': 2}}
{'x': 2}
>>> {**{'x': 2}, 'x': 1}
{'x': 1}
```

使用`字典解析`示例：
```python
>>> dic = {'x': 1, 'y': 2, 'z': 3}
>>> {key:value for key in dic.keys() for value in dic.values()}
{'x': 3, 'y': 3, 'z': 3}
```

# tuple
如果你在交互式命令行输入
```python
>>> 1, 2, 3, 4
(1, 2, 3, 4)
>>> *range(4), 4
(0, 1, 2, 3, 4)
```
直接得到的便是一个`tuple`类型的对象。使用`*`号解析亦是如此。

使用`列表解析`可以得到如下：
```python
>>> [(x,y) for x in range(2) for y in range(2)]
[(0, 0), (0, 1), (1, 0), (1, 1)]
```
会得到包含`tuple`的`list`对象。(注意`x,y`需要加括号)

# 最后
方便产出各种数据类型的方式上面介绍了两种：
- 使用 `*` 号和 `**` 双星号来产生`list, set, dic, tuple`等类型对象
- 使用*comprehension*解析器来产生对象

可以看出，最重要的一点是其操作对象是`iterable`可迭代的对象。当然，可以使用如`generator`生成器来创建自己的可迭代对象。

以上只是Python强大内置类型的一部分，后续看情况更新。