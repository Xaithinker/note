SELECT prod_name FROM Products;
SELECT prod_id, prod_name, prod_price FROM Products;
SELECT * FROM Products; 
SELECT vend_id FROM Products; SELECT DISTINCT vend_id FROM Products; -- 使用DISTINCT返回不同的值
SELECT prod_name FROM Products LIMIT 5;  -- 只返回5行
SELECT prod_name FROM Products LIMIT 5 OFFSET 5; -- 指示DBMS返回第5行起的5行数据（当前仅有9行，所以只显示4行）

-- chapter 3
SELECT prod_name FROM Products ORDER BY prod_name; -- ORDER BY子句来排序
SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price, prod_name;  -- 首先使用价格排序，后姓名排序
SELECT prod_id, prod_price, prod_name FROM Products ORDER BY 2, 3;  -- 使用列的相对位置来排序，即先按第二列prod_price排序，后按第三列
SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price DESC, prod_name;  -- prod_price使用降序排序！使用DESC关键字（若在多个列上降序，则每列需指定DESC关键字）
 
 
 -- chapter 4
 
 -- 只检索所需数据需要指定 搜索条件(search criteria)，也称为 过滤条件(filter condition)。
 
 -- WHERE子句 语法：SELECT 列名称 FROM 表名称 WHERE 列 运算符 值
 SELECT prod_name, prod_price FROM Products WHERE prod_price = 3.49; -- ORDER BY应该在WHERE 之后
 SELECT prod_name, prod_price FROM Products WHERE prod_price < 10;
 SELECT vend_id, prod_name FROM Products WHERE vend_id <> 'DLL01'; -- 字符串加单引号
 SELECT prod_name, prod_price FROM Products WHERE prod_price BETWEEN 5 AND 10; -- 范围检查
 SELECT prod_name FROM Products WHERE prod_price IS NULL; -- 空值检查
 SELECT cust_name FROM Customers WHERE cust_email IS NULL; -- 邮件空
 
 -- chapter 5 高级数据过滤
 -- 组合WHERE子句
 SELECT prod_id, prod_price, prod_name FROM Products WHERE vend_id = 'DLL01' AND prod_price <= 4; -- AND 操作符
 SELECT prod_name, prod_price FROM Products WHERE vend_id = 'DLL01' OR vend_id = 'BRS01'; -- OR操作符
 SELECT prod_name, prod_price FROM Products WHERE (vend_id = 'DLL01' OR vend_id = 'BRS01') AND prod_price >= 10; -- AND操作符优先，故加括号
 
 -- IN操作符
SELECT prod_name, prod_price FROM Products WHERE vend_id IN ( 'DLL01', 'BRS01' ) ORDER BY prod_name;

-- NOT操作符：否定其后所跟的任何条件

-- chapter6 使用通配符过滤
-- LIKE操作符：其实谓词而不是操作符，通配符搜索只适用于文本字段。
-- 百分号(%)通配符：表示任意字符出现任意次数
SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE 'Fish%'; -- 以词Fish开头
-- %看起来可以匹配任何东西，但NULL不会匹配。
SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE '__ inch teddy bear'; -- '_'下划线通配符:匹配一个字符
SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE '% inch teddy bear'; -- %匹配一个或多个字符
SELECT cust_contact FROM Customers WHERE cust_contact LIKE '[JM]%' ORDER BY cust_contact; -- [charlist]:字符列中的任何单一字符 [^charlist]:不再字符列中的任何单一字符


-- chpater7 创建计算字段
-- 计算字段：存储在数据库表中的数据一般不是应用程序所需要的格式，我们需要直接从数据库中检索出转换、计算或格式化过的数据，而不是
-- 检索出数据，然后再客户端应用程序中重新格式化。
-- 计算字段并不实际存在于数据库表中，是运行时在SELECT语句内创建的。

-- field(字段):基本上与列的意思相同，通常与计算字段一起使用。（只有数据库知道SELECT语句中哪些列是实际的表列，哪些列是计算字段）
-- 提示：SQL语句内可完成许多转换和格式化工作都可直接在客户端应用程序完成，但一般来说，在数据库服务器上完成这些操作比在客户端中要快得多

-- 拼接字段
-- concatenate(拼接):将值联结到一起（将一个值附加到另一个值）构成单个值。
-- 解决办法：使用操作符+或||,在Mysql和MariaDB中，必须使用特殊函数
SELECT Concat(vend_name, '(', vend_country, ')') FROM Vendors ORDER BY vend_name;
-- 使用别名：新计算的列并没有名字，SQL支持列别名，(alias)别名是一个字段或值得替换名，用AS关键字赋予。
SELECT Concat(vend_name, '(', vend_country, ')') AS vend_title FROM Vendors ORDER BY vend_name; -- AS赋予vend_title别名

-- 执行算术运算
SELECT prod_id, quantity, item_price, quantity*item_price AS expanded_price FROM Orderitems WHERE order_num = 20008; -- 算术运算
-- 省略了FROM子句就是简单的访问和处理表达式
SELECT 3 * 2 AS a; SELECT Trim(' abc '); SELECT Now();

-- chpater8 使用函数处理数据
-- DBMS函数得差异:
-- ---------------------------------------------
-- 函数                                 语法
-- ---------------------------------------------
-- 提取字符串得组成部分      ACCESS:MID(); DB2,oracle,PostgreSQL,SQLite:SUBSTR(); MySQL,SQL Sever:SUBSTRING()
-- 数据类型转换              ACCESS和Oracle使用多个函数，每个类型对应一个；DB2和PostgreSQL使用CAST(); MariaDB,MySQL和SQL Server使用CONVERT()
-- 取当前日期                略
-- ---------------------------------------------
-- SQL语句是不可移植的

-- 使用函数
-- 用于处理文本字符串(如删除或填充值，转换值为大小写)；在数值数据上算术操作(返回绝对值，进行代数运算)；处理日期和时间值；返回DBMS正使用的特殊信息的系统函数
-- 文本处理函数
SELECT vend_name, UPPER(vend_name) AS vend_name_upcase FROM Vendors ORDER BY vend_name; -- 大写字母
SELECT cust_name, cust_contact FROM CUstomers WHERE cust_contact = 'Michael Green';SELECT cust_name, cust_contact FROM CUstomers WHERE SOUNDEX(cust_contact) = SOUNDEX('Michael Green'); -- 使用SOUNDEX()发音相似
-- 日期和时间处理函数
SELECT order_num FROM Orders WHERE YEAR(order_date) = 2012;
-- 数值处理函数
-- ABS() COS() EXP() PI() SIN() SQRT() TAN()


-- chapter9 汇总数据
-- 介绍SQL聚集函数，利用它们汇总表的数据（5个聚集函数，其在各种主要的SQL实现中得到了相当一致的支持）
-- 聚集函数：需要汇总数据而不用把它们实际检索出来
-- AVG():某列平均值
-- COUNT():某列行数
-- MAX(): 某列最大值
-- MIN()
-- SUM():某列值之和
SELECT AVG(prod_price) AS avg_price FROM Products;
SELECT AVG(prod_price) AS avg_price FROM Products WHERE vend_id = 'DLL01'; -- AVG总是忽略列值为NULL的行

SELECT COUNT(*) AS num_cust FROM Customers; -- *代表对行数目进行计数，不管列中包含空值还是非空值。
SELECT COUNT(cust_email) AS num_cust FROM Customers; -- COUNT(column)对特定列中具有值得行计数，忽略NULL值。

SELECT MAX(prod_price) AS max_price FROM Products; -- 在用于文本数据时，总是按该列排序后得最后一行；忽略NULL行

SELECT MAX(prod_price) AS max_price FROM Products; -- 在用于文本数据时，总是按该列排序后得最前面一行；忽略NULL行

SELECT SUM(quantity) AS items_ordered FROM OrderItems WHERE order_num = 20005;
SELECT SUM(quantity*item_price) AS total_price FROM OrderItems WHERE order_num = 20005;

-- 聚集不同值
-- 对所有行计算指定ALL参数(默认行为)；只包含不同的值，指定DISTNCT参数
SELECT AVG(DISTINCT prod_price) AS avg_price FROM Products WHERE vend_id = 'DLL01'; -- 计算不同值
-- 注意：DISTINCT只能用于COUNT()不能用于COUNT(*); 必须使用别名，不能用于计算或表达式

-- 组合聚集函数: SELECT语句可能需要多个聚集函数
SELECT COUNT(*) num_items, MIN(prod_price) AS price_min, MAX(prod_price) AS price_max, AVG(prod_price) AS price_avg FROM Products;


-- chapter10 分组数据
-- 如何分组数据，以便汇总表内容中得子集，两个新的SELECT子句：GROUP BY 和 HAVING
-- 数据分组。使用分组可以使数据分成多个逻辑组，从而对每个组就行聚集计算

-- SQL GROUP BY 语法
-- ----------------------------------------------------
-- SELECT column_name, aggregate_function(column_name)
-- FROM table_name
-- WHERE column_name operator value
-- GROUP BY column_name
-- ORDER BY ...
-- ----------------------------------------------------
SELECT vend_id, COUNT(*) AS num_prods FROM Products GROUP BY vend_id;
-- 过滤分组
-- HAVING子句与WHERE子句非常相似，其区别仅是 WHERE过滤行，而HAVING过滤分组
SELECT cust_id, COUNT(*) AS orders FROM Orders GROUP BY cust_id HAVING COUNT(*) >= 2;
-- 说明：WHERE在数据分组前进行过滤，HAVING在数据分组后进行过滤。同时使用：
SELECT vend_id, COUNT(*) AS num_prods FROM Products WHERE prod_price >= 4 GROUP BY vend_id HAVING COUNT(*) >= 2;
SELECT vend_id, COUNT(*) AS num_prods FROM Products GROUP BY vend_id HAVING COUNT(*) >= 2;
-- 说明；使用HAVING时应结合GROUP BY子句，WHERE子句用于标准行级过滤

-- 分组和排序
-- GROUP BY和ORDER BY经常完成相同的工作
-- 提示：一般在使用GROUP BY时，应该也给出ORDER BY子句。这是保证数据正确排序的唯一方法。
SELECT order_num, COUNT(*) AS items FROM OrderItems GROUP BY order_num HAVING COUNT(*) >= 3 ORDER BY items, order_num;

-- SELECT子句顺序
-- SELECT:要返回的列或表达式 ； FROM; WHERE; GROUP BY; HAVING; ORDER BY


-- chapter11 使用子查询
-- SELECT语句是SQL的查询。迄今为止所有SELECT语句都是简单查询，即从单个数据库表中检索数据的单条语句。
-- 查询(query):任何SQL语句都是查询，但此术语一般指SELECT语句
-- SQL还允许创建子查询，(subquery),即嵌套在其他查询中的查询。

-- 使用子查询进行过滤
-- 1.检索包含物品RGAN01 的所有订单编号（OrderItems） 2.检索编号的所有顾客ID 3.检索顾客信息
SELECT order_nuum FROM OrderItems WHERE prod_id = 'RGAN01'; SELECT cust_id FROM Orders WHERE order_num IN (20007, 20008);SELECT cust_name, cust_contact FROM Customers WHERE cust_id IN ('1000000004', '1000000005');
SELECT cust_id FROM Orders WHERE order_num IN (SELECT order_num FROM OrderItems WHERE prod_id = 'RGAN01'); -- 使用子查询
SELECT cust_name, cust_contact FROM Customers WHERE cust_id IN (SELECT cust_id FROM Orders WHERE order_num IN (SELECT order_num FROM OrderItems WHERE prod_id = 'RGAN01'));
-- 对于子查询的SELECT语句只查询单个列！！多列错误
-- 作为计算字段使用子查询
SELECT cust_name, cust_contact, (SELECT COUNT(*) FROM Orders WHERE Orders.cust_id = Customers.cust_id) AS orders FROM Customers ORDER BY cust_name; -- 比较Orders表中的cust_id和正从Customers表中检索的cust_id(使用完全限定名)


-- chapter12 联结表
-- SQL最强大的功能之一就是在数据查询的执行中 联结表(join)
-- 关系表以及关系数据库设计基础知识
-- 如果数据存储在多个表中，怎样用一条SELECT语句就检索出数据呢？答案是使用 联结。联结是一种机制，用来在一条SELECT语句中关联表。
-- 创建联结
SELECT vend_name, prod_name, prod_price FROM Vendors, Products WHERE Vendors.vend_id = Products.vend_id; -- WHERE作为过滤条件(笛卡儿积。没有联结条件的表关系返回的结果为笛卡儿积。(有时，返回笛卡尔积的联结，也称为叉联结(cross join)))

-- 内联结
-- 目前为止使用的联结称为等值联结(equijoin)，基于两个表之间的相等测试。这种联结也成为内联结(inner join)。使用稍微不同的语法。
SELECT vend_name, prod_name, prod_price FROM Vendors INNER JOIN Products ON Vendors.vend_id = Products.vend_id;
-- 联结多个表
-- 不限制一条SELECT语句中可以联结的表的数目。
SELECT prod_name, vend_name, prod_price, quantity FROM OrderItems INNER JOIN Products INNER JOIN Vendors ON Products.vend_id = Vendors.vend_id AND OrderItems.prod_id = Products.prod_id AND Order_num = 20007;
-- DBMS在运行时关联指定的每个表，以处理联结。可能非常耗费资源，不要联结不必要的资源。


-- 创建高级联结
-- 另外一些联结、使用表别名、对被联结的表使用聚集函数
-- 使用表别名（之前介绍给列、计算字段起别名）
-- 允许对表起别名。 1. 为缩短SQL语句 2.允许在一条SELECT语句中多次使用相同的表。
-- 表别名只在查询执行中使用，与列别名不一样，表别名不返回到客户端。
SELECT cust_name, cust_contact FROM Customers AS C, Orders AS O, OrderItems AS OI WHERE OI.order_num = O.order_num AND C.cust_id = O.cust_id AND prod_id = 'RGAN01';
-- 使用不同类型的联结
-- 自联结(self-join)、自然联结(natural join)、和外联结(outer join)。
-- 自联结：例子：给与Jim Jones同一公司的所有顾客发送一封邮件。
SELECT cust_id, cust_name, cust_contact FROM Customers WHERE cust_name = (SELECT cust_name FROM Customers WHERE cust_contact = 'Jim Jones'); -- 使用子查询
SELECT c1.cust_id, c1.cust_name, c1.cust_contact FROM Customers AS c1, Customers AS c2 WHERE c1.cust_name = c2.cust_name AND c2.cust_contact = 'Jim Jones'; -- 使用WHERE联结
-- 自联结通常作为外部语句，用来替代相同表中检索数据的使用子查询语句。(许多DBMS处理联结性能较子查询好)

-- 自然联结
-- 标准联结返回所有数据，相同的列甚至多次出现。自然联结排除多次出现，使每一列只返回一次。
SELECT C.*, O.order_num, O.order_date, OI.prod_id, OI.quantity, OI.item_price FROM Customers AS C, Orders AS O, OrderItems AS OI WHERE C.cust_id = O.cust_id AND OI.order_num = O.order_num AND prod_id = 'RGAN01';
-- 迄今为止建立的每个内联结都是自然联结，很可能永远用不到不是自然联结的内联结

-- 外联结（关键字会从左表 (table_name1) 那里返回所有的行，即使在右表 (table_name2) 中没有匹配的行。）
-- 许多联结将一个表中的行于另一个表中的行相关联，但有时候需要包含没有关联的行的那些行。
-- 例：对每个顾客下的订单进行计数，包括那些至今尚未下订单的顾客；列出所有产品以及订单的数量，包括没有人订购的产品；计算平均销售规模，包括那些至今尚未下订单的顾客。
-- 联结包含了那些在相关表中没有关联行的行。这种联结称为外联结。
SELECT Customers.cust_id, Orders.order_num FROM Customers LEFT OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id;
SELECT Customers.cust_id, Orders.order_num FROM Customers RIGHT OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id;

-- 使用带聚集函数的联结
-- 检索所有顾客以及每个顾客所下的订单数
SELECT Customers.cust_id, COUNT(Orders.order_num) AS num_order FROM Customers INNER JOIN Orders ON Customers.cust_id = Orders.cust_id GROUP BY Customers.cust_id; -- 聚集函数作用于分组

-- 使用联结和联结条件
-- 汇总联结要点：
-- 注意所使用联结类型。一般使用内联结，但使用外联结也有效
-- 确切联结语法，查文档
-- 保证正确的联结条件
-- 总是提供联结条件，否则会得出笛卡儿积
-- 在一个联结中可以包含多个表，甚至可以对每个联结采用不同的联结类型。



-- chapter14 组合查询
-- 利用UNION操作符将多余SELECT语句组合成一个结果集

-- 组合查询
-- 多数查询只包含从一个或多个表中返回数据的单条SELECT语句。SQL也允许执行多个查询(多个SELECT语句），并将结果作为一个查询结果集返回。这些组合查询通常称为UNION或复合查询
-- 主要有两种情况需要使用查询：1.在一个查询中从不同的表返回结构数据 2.对一个表执行多个查询，按一个查询返回数据
-- 创建组合查询:UNION操作符组合数条SQL查询

SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI'); -- 三个州的所有顾客
SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fuun4ALL'; -- 名称为Fun4All
-- 组合
SELECT cust_name, cust_contact, cust_email FROm Customers WHERE cust_state IN ('IL', 'IN', 'MI')
UNION
SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4ALL';
-- UNION注意事项：
-- UNION中每个查询必须包含相同的列、表达式或聚集函数
-- 列数据类型必须兼容：类型不必完全相同，但必须是DBMS可以隐含转换的类型。

-- 包含和取消重复的行
SELECT cust_name, cust_contact, cust_email FROm Customers WHERE cust_state IN ('IL', 'IN', 'MI')
UNION ALL -- UNION ALL DBMS不取消重复的行
SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4ALL';

-- 对组合查询结果排序
SELECT cust_name, cust_contact, cust_email FROm Customers WHERE cust_state IN ('IL', 'IN', 'MI')
UNION
SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4ALL'
ORDER BY cust_name, cust_contact; -- ORDER BY始终在最后。


-- chapter15 插入数据
-- INSERT INTO 表名称 VALUES (值1, 值2,....)
-- INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)
-- INSERT将数据插入表中
-- 插入完整的行；行的一部分；某些查询结果
-- 插入完整的行
INSERT INTO Customers VALUES('1000000006', 'Toy Land', '123 Any Street', 'New York', 'NY', '111111', 'USA', NULL, NULL); -- 虽然这种语法很简单，但不安全
-- 编写INSERT语句更安全的方法如下:
INSERT INTO Customers(cust_id, cust_contact, cust_email, cust_name, cust_address, cust_city, cust_state, cust_zip)
VALUES('1000000006',  NULL, NULL, 'Toy Land', '123 Any Street', 'New York', 'NY', '111111');
-- 插入部分行
-- 如果表定义允许，则可以在INSERT操作中省略某些列。

-- 插入检索出的数据
-- INSERT一般用来给表插入具有指定列值的行。INSERT还存在另外一种形式，可利用它将SELECT语句的结果插入表中。即 INSERT SELECT。
INSERT INTO Customers(cust_id, cust_contact, cust_email, cust_name, cust_address, cust_city, cust_state, cust_zip, cust_country)
SELECT cust_id, cust_contact, cust_email, cust_name, cust_address, cust_city, cust_state, cust_zip, cust_country FROM CustNew;
-- INSERT SELECT中的列名:DBMS一点也不关心SELECT返回的列名，他使用的是列的位置。
-- INSERT通常只插入一行，INSERT SELECT插入多行，不管SELECT返回多行，都将被插入

-- 从一个表复制到另一个表(运行时创建的表)
-- 您可以把所有的列插入新表：
-- SELECT *
-- INTO new_table_name [IN externaldatabase] 
-- FROM old_tablename
-- 或者只把希望的列插入新表：
-- SELECT column_name(s)
-- INTO new_table_name [IN externaldatabase] 
-- FROM old_tablename

-- SELECT INTO
-- SELECT * INTO CustCopy FROM Customers;
CREATE TABLE CustCopy AS SELECT * FROM Customers;


-- chapter16 更新和删除数据
-- 利用UPDATE 和 DELETE进一步操作表数据

-- 更新数据
-- UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值
-- 更新表中特定行；更新表中所有行
-- ！注意：不要省略WHERE子句，否则会更新表中的所有行
UPDATE Customers SET cust_email = 'kim@thetoystore.com' WHERE cust_id = '1000000005';
UPDATE Customers SET cust_contact = 'Sam Roberts', cust_email = 'sam@toyland.com' WHERE cust_id = '1000000006';

-- 删除数据
-- DELETE FROM 表名称 WHERE 列名称 = 值
-- 从表中删除特定行；删除所有行； ！！不要省略WHERE子句
DELETE FROM Customers WHERE cust_id = '1000000006';
-- 想要从表中删除所有行，不要使用DELETE 可使用TRUNCATE TABLE。



-- chapter 17 创建和操纵表
-- 一般由两种创建表的方法:1.多数DBMS都具有交互式创建和管理数据库表的工具；2.可以直接用SQL语句操纵。
-- CREAT TABLE基础
-- 必须给出下列信息：
-- 新表的名字，在关键字CREAT TABLE之后；表列的名字和定义，用逗号分隔；有的DBMS还要求指定表的位置；
CREATE TABLE Products
(
    prod_id        CHAR(10)        NOT NULL
    -- ...
);
-- NULL就是没有值或缺值。允许NULL值的列也允许在插入行时不给出该列的值。不允许NULL值得列不接受没有列值得行，即插入或更新行时，该列必须有值；
-- 每列要么是NULL列，要么是NOT NULL列。
CREATE TABLE Orders
(
    order_num INTEGER  NOT NULL,
    order_date DATETIME NOT NULL,
    cust_id    CHAR(10)  NOT NULL
); -- 均不允许没有值得列
-- 只有不允许NULL的列可作为主键，允许NULL值的列不可作为唯一标识。
-- 指定默认值
CREATE TABLE Products
(
    prod_id    INTEGER     NOT NULL  DEFAULT 1 -- DEFAULT CURRENT_DATE()
    -- ...
);


-- 更新表：
-- 如需在表中添加列，请使用下列语法:
-- ALTER TABLE table_name
-- ADD column_name datatype.
-- 要删除表中的列，请使用下列语法：
-- ALTER TABLE table_name 
-- DROP COLUMN column_name
-- 要改变表中列的数据类型，请使用下列语法：
-- ALTER TABLE table_name
-- ALTER COLUMN column_name datatype
ALTER TABLE Vendors ADD vend_phone CHAR(20);
ALTER TABLE Vendors DROP vend_phone;
-- 复杂表结构的更改一般需要手动删除过程，它涉及以下步骤：
-- 1. 用新的列布局创建一个新表
-- 2. 使用INSERT SELECT语句从旧表复制数据到新表。如有必要，可使用转换函数和计算字段
-- 3. 检验包含所需数据的新表；
-- 4. 重命名旧表
-- 5. 用旧表原来的名字重命名新表；
-- 6. 根据需要， 重新创建触发器、存储过程、索引和外键
-- 使用ALTER TABLE要小心！！改动之前做完整的备份

-- 删除表
DROP TABLE CustCopy; -- 使用关系规则放止意外删除

-- 重命名表


-- chapter 18 使用视图
-- 介绍什么是视图，怎样工作，何时使用；讲述如何利用视图简化前面执行的某些SQL操作

-- 视图
-- 视图是虚拟的表。只包含使用时动态检索数据的查询。
-- 例如一个查询用来检索订购了某种产品的顾客。任何需要这个数据的人都必须理解相关表的结构。检索其他产品的相同数据，须修改最后的WHERE子句。
-- 现在，可以把整个查询包装成一个名为ProductCustomers的虚拟表
-- SELECT cust_name, cust_contact FROM ProductCustomers WHERE prod_id = 'RAG01';
-- 这就是视图的作用，ProductCustomers是一个视图，他不包含任何数据。包含的是一个查询
-- 提示：DBMS非常一致的支持视图创建语法

-- 为什么使用视图
-- 重用SQL语句；简化复杂的SQL操作（重用它而不必知道其查询细节）；使用表的一部分而不是整个表；保护数据（可以授予用户访问部分权限）；更改数据格式和表示；
-- 视图不包含数据，每次使用视图时，都必须处理查询执行需要的所有检索。

-- 视图的限制和规则
-- 与表一样，视图必须唯一命名；创建视图数量无限制；创建视图必须有足够的访问权限；视图可以嵌套；许多DBMS禁止在视图查询中使用ORDER BY子句；许多DBMS要求返回的所有列命名
-- ；视图不能索引，也不能有关联的触发器或默认值；有些DBMS把视图当作只读对象；有些DBMS允许创建这样的视图，其不能进行导致行不再属于视图的插入或更新。

-- 创建视图
-- CREATE VIEW
-- DROP VIEW viewname;
-- 利用视图简化复杂的联结
CREATE VIEW ProductCustomers AS
SELECT cust_name, cust_contact, prod_id FROM Customers, Orders, OrderItems WHERE OrderItems.order_num = Orders.order_num;

SELECT cust_name, cust_contact FROM ProductCustomers WHERE prod_id = 'RGAN01';

-- 用视图重新格式化检索出的数据

-- 用视图过滤不想要的数据
CREATE VIEW CustomerEMailList AS
SELECT cust_id, cust_name, cust_email FROM Customers WHERE cust_email IS NOT NULL; -- 过滤没有电子邮件的顾客

SELECT * FROM CustomerEMailList;


-- 使用视图和计算字段
CREATE VIEW OrderItemsExpanded AS 
SELECT order_num, prod_id, quantity, item_price, quantity*item_price AS expanded_price FROM OrderItems;

SELECT * FROM OrderItemsExpanded WHERE order_num = 20008;



-- chapter19 使用存储过程
-- 存储过程
-- 迄今为止，我们使用的大多数SQL语句都是针对一个或多个表的单条语句。并非所有操作都这么简单。
-- 例如：1.为了处理订单，必须核对以保证库存中有相应的物品；2.如果物品有库存，需要预定，不在出售给别人，并且减少物品数据以反映正确的库存量；
-- 3.库存中没有的物品需要订购，这需要与供应商进行某种交互。4.关于哪些物品入库和哪些物品退订，需要通知想要的顾客。
-- 怎样编写？可以单独编写每条SQL语句，并根据结果有条件的执行； 可以创建存储过程。即为以后使用而保存的一条或多条SQL语句。可将其视为批文件。

-- 执行存储过程
-- EXECUTE接受存储过程名和需要传递给它的任何参数。
-- EXECUTE AddNewProduct( 'JTS01', 'Stuffed Eiffel Tower', 6.49, 'Plush stuffed toy with the text La Tour Eiffel in red white and blue' );
-- 执行一个名为AddNewProduct的存储过程，将一个新产品添加到Products表中。
-- 要保证恰当的生成此ID,最好使生成此ID的过程自动化，而不是依赖于最终的用户的输入。这也是这个例子使用存储过程的原因。

-- 创建存储过程
-- .......................

-- chapter20 管理事务处理
-- COMMIT和ROLLBACK语句管理事务处理

-- 事务处理（transaction processing）
-- 使用事务处理，通过确保成批的SQL操作要么完全执行要么完全不执行，来维护数据库的完整性。
-- 事务处理是一种机制，用来管理必须成批执行的SQL操作，保证数据库不包含不完整的操作结果。利用事务处理，可以保证一组操作不会中途停止，它们要么完全执行
-- 要么完全不执行。如果没有错误发生，整组语句提交给数据库表；发生错误，进行回退，将数据库恢复到某个已知且安全的状态；
-- 事务有关术语：
-- 1. 事务(transaction)指一组SQL语句。2.回退(rollback)指撤销指定SQL语句过程；3.提交(commit)指将未存储的SQL语句结果写入数据库表；4.保留点(savepoint)指事务处理中设置的临时占位符(placeholder)，可以对它发布回退

-- 控制事务处理
-- START TRANSACTION
-- ...
-- 使用ROLLBACK
DELETE FROM Orders;
ROLLBACK; -- 说明DELETE、INSERT、UPDATE不是最终的结果

-- 使用COMMIT
-- 一般sQL语句都是针对数据库表直接执行和编写的。即所谓隐式提交。
-- 在事务处理块中，提交不会隐式进行。

-- 使用保留点
-- ROLLBACK TO delete1;




-- chapter21 使用游标
-- 简单的使用SELECT语句，没办法得到第一行、下一行或前10行。
-- 有时需要在检索出来的行中前进或后退一行或多行，这就是游标的用途所在。
-- 常见特性和选项
-- 1.能够标记游标为只读，是数据能读取，不能更新或删除 2.能控制可以执行的定向操作； 3. 能标记某些列是可编辑的，某些列是不可编辑的 4.规定范围，使游标对创建它的特定请求或所有请求可访问 5. 指示DBMS对检索数据进行复制，使数据在游标打开和访问期间不变化。
-- DECLARE CustCursor CURSOR FOR SELECT * FROM Customers WHERE cust_email IS NULL;
-- 略


-- chapter22 高级SQL特性
-- 约束(constraint)
-- 关联表和引用完整性已经在前面讨论过几次。正如所述，关系数据库存储分解为多个表的数据，每个表存储相应的数据。利用键来建立从一个表到另一个表的引用(产生了引用完整性)。
-- 主键
-- 主键是一种特殊的约束。若没有主键，安全的UPDATE和DELETE特定行而不影响其他行会非常困难；
-- 定义主键
-- CREATE TABLE Vendors{
-- (
--     vend_id      CHAR(10)          NOT NULL       PRIMARY KEY,
--     ...
-- )
-- 或
ALTER TABLE Vendors ADD CONSTRAINT PRIMARY KEY (vend_id);

-- 外键
-- 外键是表中的一列，其值必须列在另一表的主键中。外键是保证引用完整性的极其重要的部分。
CREATE TABLE Orders
(
    order_num      INTEGER    NOT NULL PRIMARY KEY,
    order_date     DATETIME   NOT NULL,
    cust_id        CHAR(10)   NOT NULL REFERENCES  -- 外键
    Customers(cust_id) -- 表明cust_id中的任何值都必须是CUstomers表的cust_id值。
)


-- 唯一约束：用来保证一列(或一组列）中的数据是唯一的，他们类似于主键，但存在区别：
-- 1.表可以包含多个约束，但只有一个主键 2.唯一约束列可包含NULL值 3.唯一约束列可修改或更新 4.唯一约束列的值可重复使用 5.与主键不一样，唯一约束不能用来定义外键

-- 检查约束：保证一列中的数据满足一组指定的条件。


-- 索引：用来排序数据以加快搜索和排序操作的速度。
CREATE INDEX prod_name_ind ON Products (prod_name);

-- 触发器：特殊的存储过程，它在特定的数据库活动发生时自动执行。触发器可与INSERT、UPDATE和DELETE相关联
-- 与存储过程不同，触发器只与单个表相关联，与Orders表上的INSERT操作相关联的触发器只在Orders表中插入行时执行。


-- 数据库安全
-- 一般来说，需要保护的操作有：
-- 对数据库管理功能（创建表、更改和删除已存在的表等）
-- 对特定数据库或表访问
-- 访问的类型（只读、对特定列的访问）
-- 仅通过视图或存储过程对表进行访问
-- 创建多层次的安全措施，从未允许多中基于登陆的访问和控制
-- 限制管理用户账号的能力

