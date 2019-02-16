# **Selectors**
在抓取网页时，您需要执行的最常见任务是从HTML源提取数据。有几个库可用于实现此目的，例如：
- [BeautifulSoup](https://www.crummy.com/software/BeautifulSoup/)是Python程序员中非常流行的Web抓取库，它基于HTML代码的结构构造Python对象，并且还合理地处理坏标记，但它有一个缺点：它很慢。
- [lxml](http://lxml.de/)是一个XML解析库（也可以解析HTML），它使用基于[ElementTree](https://docs.python.org/2/library/xml.etree.elementtree.html)的pythonic API。（lxml不是Python标准库的一部分。）

Scrapy带有自己的提取数据机制。它们被称为选择器，因为它们“选择”由XPath或CSS表达式指定的HTML文档的某些部分。
> ! Note
> 
> Scrapy Selectors是一个围绕parsel库的薄包装器;此包装器的目的是提供与Scrapy Response对象的更好集成。
> 
> parsel是一个独立的Web抓取库，可以在没有Scrapy的情况下使用。它使用了lxml库，并在lxml API之上实现了一个简单的API。这意味着Scrapy选择器的速度和解析精度与lxml非常相似。

# **使用选择器**
## **构建选择器**
响应对象在`.selector`属性上公开`Selector`实例：
```python
>>> response.selector.xpath('//span/text()'.get())
'good'
```
使用XPath和CSS查询响应非常常见，响应包括另外两个快捷方式：`response.xpath()`和`response.css()`：
```python
>>> response.xpath('//span/text()').get()
'good'
>>> response.css('span::text').get()
'good'
```
Scrapy选择器是通过将`TextResponse`对象或标记作为unicode字符串（在`text`参数中）传递而构造的`Selector`类的实例。通常不需要手动构建Scrapy选择器：在Spider回调中可以使用`response`对象，因此在大多数情况下使用`response.css()`和`response.xpath()`快捷方式会更方便。通过使用response.selector或其中一个快捷方式，您还可以确保仅解析一次响应正文。

但如果需要，可以直接使用`Selector`。从**文本**构造：
```python
>>> from scrapy.selector import Selector
>>> body = '<html><body><span>good</span></body></html>'
>>> Selector(text=body).xpath('//span/text()').get()
'good'
```
从**响应**构造 - `HtmlResponse`是`TextResponse`子类之一：
```python
>>> from scrapy.selector import Selector
>>> from scrapy.http import HtmlResponse
>>> response = HtmlResponse(url='http://example.com', body=body)
>>> Selector(response=response).xpath('//span/text()').get()
'good'
```
`Selector`根据输入类型自动选择最佳解析规则（XML与HTML）。

## **使用选择器**
