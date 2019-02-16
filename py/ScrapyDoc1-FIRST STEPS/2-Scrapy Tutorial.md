# Scrapy Tutorial
在本教程中，我们假设您的系统上已经安装了Scrapy。如果不是这种情况，请参阅安装指南。

我们将爬取[quotes.toscrape.com](http://quotes.toscrape.com/)，这是一个列出着名作家引用的网站。

本教程将指导您完成以下任务：
1. 创建一个新的Scrapy项目
2. 编写蜘蛛来抓取网站并提取数据
3. 使用命令行导出已爬取的数据
4. 改变蜘蛛以递归方式跟随链接
5. 使用蜘蛛参数

Scrapy是用Python编写的。如果您不熟悉该语言，您可能需要先了解语言是什么样的，以便充分利用Scrapy。

如果您已经熟悉其他语言，并希望快速学习Python，那么[Python Tutorial](https://docs.python.org/3/tutorial/)是一个很好的资源。

如果您不熟悉编程并希望从Python开始，以下书籍可能对您有用：
- [Automate the Boring Stuff With Python](https://automatetheboringstuff.com/)
- [How To Think Like a Computer Scientist](http://openbookproject.net/thinkcs/python/english3e/)
- [Learn Python 3 The Hard Way](https://learnpythonthehardway.org/python3/)

## 创建一个项目
在开始抓取之前，您必须设置一个新的Scrapy项目。输入您要存储代码的目录并运行：
```python
scrapy startproject tutorial
```
这将创建一个包含以下内容的教程目录：
```
tutorial/
    scrapy.cfg            # deploy configuration file

    tutorial/             # project's Python module, you'll import your code from here
        __init__.py

        items.py          # project items definition file

        middlewares.py    # project middlewares file

        pipelines.py      # project pipelines file

        settings.py       # project settings file

        spiders/          # a directory where you'll later put your spiders
            __init__.py
```
## 第一个Spider
Spiders 是您定义的类，Scrapy用来从网站（或一组网站）中提取信息。他们必须继承scrapy.Spider子类并定义初始请求，可选择如何跟踪页面中的链接，以及如何解析下载的页面内容以提取数据。

这是我们第一个蜘蛛的代码。将它保存在项目tutorial/spiders目录下名为quotes_spider.py的文件中：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"

    def start_requests(self):
        urls = [
            'http://quotes.toscrape.com/page/1/',
            'http://quotes.toscrape.com/page/2/',
        ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        page = response.url.split("/")[-2]
        filename = 'quotes-%s.html' % page
        with open(filename, 'wb') as f:
            f.write(response.body)
        self.log('Saved file %s' % filename)
```
如您所见，我们的Spider子类[scrapy.Spider](https://docs.scrapy.org/en/latest/topics/spiders.html#scrapy.spiders.Spider)并定义了一些属性和方法：
- **name**:识别蜘蛛。它在项目中必须是唯一的，也就是说，您不能为不同的Spiders设置相同的名称。
- **start_requests()**:必须返回一个可迭代的请求（您可以返回一个请求列表或编写一个生成器函数），Spider将开始从中爬行。后续请求将从这些初始请求中连续生成。
- **parse()**:将被调用以处理为每个请求下载的响应的方法。 response参数是[TextResponse](https://docs.scrapy.org/en/latest/topics/request-response.html#scrapy.http.TextResponse)的一个实例，它保存页面内容并具有处理它的其他有用方法。

 parse（）方法通常会解析响应，提取已删除的数据作为dicts，并查找要遵循的新URL并从中创建新请求（Request）。

 ## 如何允许我们的爬虫
 要让我们的蜘蛛工作，请转到项目的顶级目录并运行：

`scrapy crawl quotes`

此命令运行带有我们刚刚添加的名称引号的spider，它将发送一些quotes.toscrape.com域的请求。您将获得类似于此的输出：
```
... (omitted for brevity)
2016-12-16 21:24:05 [scrapy.core.engine] INFO: Spider opened
2016-12-16 21:24:05 [scrapy.extensions.logstats] INFO: Crawled 0 pages (at 0 pages/min), scraped 0 items (at 0 items/min)
2016-12-16 21:24:05 [scrapy.extensions.telnet] DEBUG: Telnet console listening on 127.0.0.1:6023
2016-12-16 21:24:05 [scrapy.core.engine] DEBUG: Crawled (404) <GET http://quotes.toscrape.com/robots.txt> (referer: None)
2016-12-16 21:24:05 [scrapy.core.engine] DEBUG: Crawled (200) <GET http://quotes.toscrape.com/page/1/> (referer: None)
2016-12-16 21:24:05 [scrapy.core.engine] DEBUG: Crawled (200) <GET http://quotes.toscrape.com/page/2/> (referer: None)
2016-12-16 21:24:05 [quotes] DEBUG: Saved file quotes-1.html
2016-12-16 21:24:05 [quotes] DEBUG: Saved file quotes-2.html
2016-12-16 21:24:05 [scrapy.core.engine] INFO: Closing spider (finished)
...
```
现在，检查当前目录中的文件。您应该注意到已经创建了两个新文件：quotes-1.html和quotes-2.html，以及各个URL的内容，正如我们的解析方法所指示的那样。

## 刚刚发生了什么？
Scrapy调度由Spider的start_requests方法返回的scrapy.Request对象。收到每个响应后，它会实例化Response对象并调用与请求相关的回调方法（在本例中为parse方法），将响应作为参数传递。

## start_requests方法的快捷方式
您可以只使用URL列表定义**start_urls**类属性，而不是实现从URL生成scrapy.Request对象的**start_requests**()方法。然后，start_requests（）的默认实现将使用此列表来创建对spider的初始请求：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"
    start_urls = [
        'http://quotes.toscrape.com/page/1/',
        'http://quotes.toscrape.com/page/2/',
    ]

    def parse(self, response):
        page = response.url.split("/")[-2]
        filename = 'quotes-%s.html' % page
        with open(filename, 'wb') as f:
            f.write(response.body)
```
将调用parse（）方法来处理这些URL的每个请求，即使我们没有明确告诉Scrapy这样做。发生这种情况是因为parse（）是Scrapy的默认回调方法，在没有明确分配回调的情况下调用请求。

## 提取数据
学习如何使用Scrapy提取数据的最佳方法是使用shell Scrapy shell尝试选择器。运行：
```
scrapy shell 'http://quotes.toscrape.com/page/1/'
```
> 记住在从命令行运行Scrapy shell时始终将URL括在引号中，否则包含参数（即。＆character）的url将不起作用。
> 在Windows上，请使用双引号：
> 
> `scrapy shell "http://quotes.toscrape.com/page/1/"`

你会看到类似的东西：
```
[ ... Scrapy log here ... ]
2016-09-19 12:09:27 [scrapy.core.engine] DEBUG: Crawled (200) <GET http://quotes.toscrape.com/page/1/> (referer: None)
[s] Available Scrapy objects:
[s]   scrapy     scrapy module (contains scrapy.Request, scrapy.Selector, etc)
[s]   crawler    <scrapy.crawler.Crawler object at 0x7fa91d888c90>
[s]   item       {}
[s]   request    <GET http://quotes.toscrape.com/page/1/>
[s]   response   <200 http://quotes.toscrape.com/page/1/>
[s]   settings   <scrapy.settings.Settings object at 0x7fa91d888c10>
[s]   spider     <DefaultSpider 'default' at 0x7fa91c8af990>
[s] Useful shortcuts:
[s]   shelp()           Shell help (print this help)
[s]   fetch(req_or_url) Fetch request (or URL) and update local objects
[s]   view(response)    View response in a browser
>>>
```
使用shell，您可以尝试使用CSS和响应对象选择元素：
```
>>> response.css('title')
[<Selector xpath='descendant-or-self::title' data='<title>Quotes to Scrape</title>'>]
```
运行**response.css**('title')的结果是一个名为SelectorList的类似列表的对象，它表示包含XML/HTML元素的**Selector**对象列表，并允许您运行更多查询以细化选择或提取数据。

从上面的标题中提取文本，你可以这样做：
```
>>> response.css('title::text').getall()
['Quotes to Scrape']
```
这里有两点需要注意：一个是我们在CSS查询中添加了::text，意味着我们只想在\< title >元素中直接选择文本元素。

如果我们不指定:: text，我们将获得完整的title元素，包括其标签：
```
>>> response.css('title').getall()
['<title>Quotes to Scrape</title>']
```
另一件事是调用.getall（）的结果是一个列表：选择器可能返回多个结果，因此我们将它们全部提取出来。当你知道你只想要**第一个结果**时，就像在这种情况下，你可以这样做：
```
>>> response.css('title::text').get()
'Quotes to Scrape'
```
作为替代方案，你可以写：
```
>>> response.css('title::text')[0].get()
'Quotes to Scrape'
```
但是，直接在SelectorList实例上使用.get（）可以避免IndexError，并在找不到与选择匹配的任何元素时返回None。

这里有一个教训：对于大多数抓取代码，您希望它能够在页面上找不到任何内容时对错误具有弹性，因此即使某些部分无法被删除，您也至少可以获得**一些**数据。

除了getall（）和get（）方法之外，您还可以使用re（）方法使用正则表达式进行提取：
```
>>> response.css('title::text').re(r'Quotes.*')
['Quotes to Scrape']
>>> response.css('title::text').re(r'Q\w+')
['Quotes']
>>> response.css('title::text').re(r'(\w+) to (\w+)')
['Quotes', 'Scrape']
```
为了找到合适的CSS选择器，您可能会发现使用view(response)从Web浏览器中的shell打开响应页面非常有用。您可以使用浏览器开发人员工具检查HTML并选择一个选择器（请参阅使用[浏览器的开发人员工具进行抓取](https://docs.scrapy.org/en/latest/topics/developer-tools.html#topics-developer-tools)一节）。

Selector Gadget也是一个很好的工具，可以快速找到视觉选择元素的CSS选择器，适用于许多浏览器。

## XPath：一个简短的介绍
除了CSS，Scrapy选择器还支持使用XPath表达式：
```
>>> response.xpath('//title')
[<Selector xpath='//title' data='<title>Quotes to Scrape</title>'>]
>>> response.xpath('//title/text()').get()
'Quotes to Scrape'
```
XPath表达式非常强大，是Scrapy Selectors的基础。实际上，CSS选择器在引擎盖下转换为XPath。如果仔细阅读shell中选择器对象的文本表示，则可以看到。

虽然可能不像CSS选择器那样流行，但XPath表达式提供了更多功能，因为除了导航结构外，它还可以查看内容。使用XPath，您可以选择以下内容：选择包含文本“下一页”的链接。这使XPath非常适合抓取任务，我们鼓励您学习XPath，即使您已经知道如何构造CSS选择器，它也会使抓取更容易。

我们不会在这里介绍XPath的大部分内容，但您可以在此处阅读有关[在Scrapy选择器中使用XPath](https://docs.scrapy.org/en/latest/topics/selectors.html#topics-selectors)的更多信息。要了解有关XPath的更多信息，我们建议[ this tutorial to learn XPath through examples](http://zvon.org/comp/r/tut-XPath_1.html)，本教程将学习[this tutorial to learn “how to think in XPath”](http://plasmasturm.org/log/xpath101/)。

## 提取引用和作者
现在你已经了解了一些关于选择和提取的知识，让我们通过编写代码从网页中提取引号来完成我们的蜘蛛。

http://quotes.toscrape.com中的每个引用都由HTML元素表示，如下所示：
```html
<div class="quote">
    <span class="text">“The world as we have created it is a process of our
    thinking. It cannot be changed without changing our thinking.”</span>
    <span>
        by <small class="author">Albert Einstein</small>
        <a href="/author/Albert-Einstein">(about)</a>
    </span>
    <div class="tags">
        Tags:
        <a class="tag" href="/tag/change/page/1/">change</a>
        <a class="tag" href="/tag/deep-thoughts/page/1/">deep-thoughts</a>
        <a class="tag" href="/tag/thinking/page/1/">thinking</a>
        <a class="tag" href="/tag/world/page/1/">world</a>
    </div>
</div>
```
让我们打开scrapy shell并演示一下以了解如何提取我们想要的数据：

`$ scrapy shell 'http://quotes.toscrape.com'`

我们得到了引用HTML元素的选择器列表：

`>>> response.css("div.quote")`

上面的查询返回的每个选择器允许我们对其子元素运行进一步的查询。让我们将第一个选择器分配给一个变量，这样我们就可以直接在特定的引号上运行CSS选择器：

`>>> quote = response.css("div.quote")[0]`

现在，让我们使用刚刚创建的引用对象从该引用中提取标题，作者和标记：
```python
>>> title = quote.css("span.text::text").get()
>>> title
'“The world as we have created it is a process of our thinking. It cannot be changed without changing our thinking.”'
>>> author = quote.css("small.author::text").get()
>>> author
'Albert Einstein'
```
鉴于标签是一个字符串列表，我们可以使用.getall()方法来获取所有这些：
```python
>>> tags = quote.css("div.tags a.tag::text").getall()
>>> tags
['change', 'deep-thoughts', 'thinking', 'world']
```
在弄清楚如何提取每个位之后，我们现在可以迭代所有引号元素并将它们放在一起放入Python字典：
```python
>>> for quote in response.css("div.quote"):
...     text = quote.css("span.text::text").get()
...     author = quote.css("small.author::text").get()
...     tags = quote.css("div.tags a.tag::text").getall()
...     print(dict(text=text, author=author, tags=tags))
{'tags': ['change', 'deep-thoughts', 'thinking', 'world'], 'author': 'Albert Einstein', 'text': '“The world as we have created it is a process of our thinking. It cannot be changed without changing our thinking.”'}
{'tags': ['abilities', 'choices'], 'author': 'J.K. Rowling', 'text': '“It is our choices, Harry, that show what we truly are, far more than our abilities.”'}
    ... a few more of these, omitted for brevity
>>>
```
## 在我们的蜘蛛中提取数据
让我们回到我们的蜘蛛。到目前为止，它并没有特别提取任何数据，只是将整个HTML页面保存到本地文件中。让我们将上面的提取逻辑集成到我们的蜘蛛中。

Scrapy蜘蛛通常会生成许多包含从页面提取的数据的字典。为此，我们在回调中使用yield Python关键字，如下所示：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"
    start_urls = [
        'http://quotes.toscrape.com/page/1/',
        'http://quotes.toscrape.com/page/2/',
    ]

    def parse(self, response):
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('small.author::text').get(),
                'tags': quote.css('div.tags a.tag::text').getall(),
            }
```
如果你运行此蜘蛛，它将使用日志输出提取的数据：
```python
2016-09-19 18:57:19 [scrapy.core.scraper] DEBUG: Scraped from <200 http://quotes.toscrape.com/page/1/>
{'tags': ['life', 'love'], 'author': 'André Gide', 'text': '“It is better to be hated for what you are than to be loved for what you are not.”'}
2016-09-19 18:57:19 [scrapy.core.scraper] DEBUG: Scraped from <200 http://quotes.toscrape.com/page/1/>
{'tags': ['edison', 'failure', 'inspirational', 'paraphrased'], 'author': 'Thomas A. Edison', 'text': "“I have not failed. I've just found 10,000 ways that won't work.”"}
```

## 存储已爬取的数据
存储已爬取数据的最简单方法是使用Feed exports，使用以下命令：

`scrapy crawl quotes -o quotes.json`

这将生成一个quotes.json文件，其中包含以JSON序列化的所有已爬取项。

由于历史原因，Scrapy会附加到给定文件而不是覆盖其内容。如果在第二次之前没有删除文件的情况下运行此命令两次，则最终会出现损坏的JSON文件。

您还可以使用其他格式，例如[JSON Lines](http://jsonlines.org/)：

`scrapy crawl quotes -o quotes.jl`

JSON Lines格式非常有用，因为它类似于流，你可以轻松地向其添加新记录。当你运行两次时，它没有相同的JSON问题。

此外，由于每条记录都是一个单独的行，您可以处理大文件而无需将所有内容都放在内存中，有些工具如[JQ](https://stedolan.github.io/jq)可以帮助您在命令行中执行此操作。

在小项目中（如本教程中的项目），这应该足够了。但是，如果要使用已爬取的项目执行更复杂的操作，可以编写[项目管道](https://docs.scrapy.org/en/latest/topics/item-pipeline.html#topics-item-pipeline)。在项目创建时，在tutorial/pipelines.py中为您设置了项目管道的占位符文件。如果您只想存储已爬取的项目，则不需要实现任何项目管道。

## 下一个链接
依我们看，你不仅仅是从http://quotes.toscrape.com的前两页中抓取内容，而是需要网站中所有页面的引用。

既然您知道如何从页面中提取数据，那么让我们看看如何从它们中提取链接。

首先是提取我们想要关注的页面的链接。检查我们的页面，我们可以看到下一页的链接带有以下标记：
```html
<ul class="pager">
    <li class="next">
        <a href="/page/2/">Next <span aria-hidden="true">&rarr;</span></a>
    </li>
</ul>
```
我们可以尝试在shell中提取它：
```html
>>> response.css('li.next a').get()
'<a href="/page/2/">Next <span aria-hidden="true">→</span></a>'
```
这将获取锚元素，但我们需要属性href。为此，Scrapy支持CSS扩展，让您选择属性内容，如下所示：
```python
>>> response.css('li.next a::attr(href)').get()
'/page/2/'
```
还有一个attrib属性可用（请参阅[选择元素属性](https://docs.scrapy.org/en/latest/topics/selectors.html#selecting-attributes)以获取更多信息）：
```python
>>> response.css('li.next a').attrib['href']
'/page/2'
```
现在让我们看看我们的蜘蛛被修改为递归地跟随到下一页的链接，从中提取数据：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"
    start_urls = [
        'http://quotes.toscrape.com/page/1/',
    ]

    def parse(self, response):
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('small.author::text').get(),
                'tags': quote.css('div.tags a.tag::text').getall(),
            }

        next_page = response.css('li.next a::attr(href)').get()
        if next_page is not None:
            next_page = response.urljoin(next_page)
            yield scrapy.Request(next_page, callback=self.parse)
```
现在，在提取数据之后，parse（）方法查找到下一页的链接，使用urljoin（）方法构建完整的绝对URL（因为链接可以是相对的）并向下一页生成新请求，将自身注册为回调以处理下一页的数据提取并保持爬网遍历所有页面。

你在这里看到的是Scrapy跟踪链接的机制：当你在回调方法中产生一个Request时，Scrapy会安排发送该请求并注册一个回调方法，以便在该请求完成时执行。

在我们的示例中，它创建了一种循环，跟随到下一页的所有链接，直到它找不到 - 方便于爬行博客，论坛和其他具有分页的网站。

## 创建请求的快捷方式
作为创建Request对象的快捷方式，您可以使用response.follow：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"
    start_urls = [
        'http://quotes.toscrape.com/page/1/',
    ]

    def parse(self, response):
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('span small::text').get(),
                'tags': quote.css('div.tags a.tag::text').getall(),
            }

        next_page = response.css('li.next a::attr(href)').get()
        if next_page is not None:
            yield response.follow(next_page, callback=self.parse)
```
与scrapy.Request不同，response.follow直接支持相对URL - 无需调用urljoin。请注意，response.follow只返回一个Request实例;你仍然需要提出这个请求。

您还可以将**选择器**传递给response.follow而不是字符串;此选择器应提取必要的属性：
```python
for href in response.css('li.next a::attr(href)'):
    yield response.follow(href, callback=self.parse)
```
对于\<a>元素，有一个快捷方式：response.follow自动使用其href属性。所以代码可以进一步缩短：
```python
for a in response.css('li.next a'):
    yield response.follow(a, callback=self.parse)
```
## 更多示例和模式
这是另一个蜘蛛，它介绍了回调和以下链接，这次是为了抓取作者信息：
```python
import scrapy


class AuthorSpider(scrapy.Spider):
    name = 'author'

    start_urls = ['http://quotes.toscrape.com/']

    def parse(self, response):
        # follow links to author pages
        for href in response.css('.author + a::attr(href)'):
            yield response.follow(href, self.parse_author)

        # follow pagination links
        for href in response.css('li.next a::attr(href)'):
            yield response.follow(href, self.parse)

    def parse_author(self, response):
        def extract_with_css(query):
            return response.css(query).get(default='').strip()

        yield {
            'name': extract_with_css('h3.author-title::text'),
            'birthdate': extract_with_css('.author-born-date::text'),
            'bio': extract_with_css('.author-description::text'),
        }
```
这个蜘蛛将从主页面开始，它将跟随作者页面的所有链接，为每个页面调用parse_author回调，以及我们之前看到的与解析回调的分页链接。

在这里，我们将回调传递给response.follow作为位置参数，以使代码更短;它也适用于scrapy.Request。

parse_author回调定义了一个辅助函数，用于从CSS查询中提取和清除数据，并生成带有作者数据的Python dict。

这个蜘蛛演示的另一个有趣的事情是，即使同一作者有很多引用，**我们也不必担心多次访问同一作者页面**。默认情况下，Scrapy会筛选出已访问过的URL的重复请求，从而避免因编程错误而导致服务器过多的问题。这可以通过设置DUPEFILTER_CLASS来配置。

希望到现在为止，您已经很好地理解了如何使用Scrapy跟踪链接和回调的机制。

作为另一个利用后续链接机制的蜘蛛，请查看[CrawlSpider](https://docs.scrapy.org/en/latest/topics/spiders.html#scrapy.spiders.CrawlSpider)类以获取一个通用蜘蛛，该蜘蛛实现了一个小规则引擎，您可以使用该规则引擎在其上编写爬虫。

此外，常见的模式是使用一个技巧来构建包含来自多个页面的数据的项目，以将[其他数据传递给回调](https://docs.scrapy.org/en/latest/topics/request-response.html#topics-request-response-ref-request-callback-arguments)。

## 使用spider参数
您可以在运行它们时使用-a选项为您的蜘蛛提供命令行参数：

`scrapy crawl quotes -o quotes-humor.json -a tag=humor`

这些参数传递给Spider的__init__方法，默认情况下变为spider属性。

在此示例中，为tag参数提供的值将通过self.tag提供。您可以使用此选项使您的蜘蛛只获取具有特定标记的引号，并根据参数构建URL：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"

    def start_requests(self):
        url = 'http://quotes.toscrape.com/'
        tag = getattr(self, 'tag', None)
        if tag is not None:
            url = url + 'tag/' + tag
        yield scrapy.Request(url, self.parse)

    def parse(self, response):
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.css('small.author::text').get(),
            }

        next_page = response.css('li.next a::attr(href)').get()
        if next_page is not None:
            yield response.follow(next_page, self.parse)
```
如果您将tag = humor参数传递给此蜘蛛，您会发现它只会访问humor标记中的URL，例如http://quotes.toscrape.com/tag/humor。

您[可以在此处了解有关处理spider参数的更多信息](https://docs.scrapy.org/en/latest/topics/spiders.html#spiderargs)。

## 下一步
本教程仅介绍了Scrapy的基础知识，但这里没有提到很多其他功能。检查还有[什么](https://docs.scrapy.org/en/latest/intro/overview.html#topics-whatelse)？ Scrapy中的[Scrapy at a glance](https://docs.scrapy.org/en/latest/intro/overview.html#intro-overview)提供最重要章节的快速概述。

您可以继续阅读基本概念部分，以了解有关命令行工具，蜘蛛，选择器以及教程未涵盖的其他内容的更多信息，例如对已爬取数据进行建模。如果您更喜欢使用示例项目，请查看[Example](https://docs.scrapy.org/en/latest/intro/examples.html#intro-examples)部分。