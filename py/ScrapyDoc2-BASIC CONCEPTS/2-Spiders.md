蜘蛛是定义如何抓取某个站点（或一组站点）的类，包括如何执行爬行（即跟随链接）以及如何从其页面中提取结构化数据（即，抓取项目）。换句话说，Spiders是您为特定站点（或者在某些情况下，一组站点）爬取和解析页面定义自定义行为的地方。

对于蜘蛛，爬取周期经历如下：
1. 首先生成初始请求以爬取第一个URL，并指定要使用从这些请求下载的响应调用的回调函数。


   第一个执行请求是通过调用`start_requests()`方法获得的，该方法（默认情况下）为`start_urls`中指定的URL生成`Request`，并将`parse`方法生成为Requests的回调函数。
2. 在回调函数中，您解析响应（网页）并返回带有提取数据的dicts，`Item`对象，`Request`对象或这些对象的可迭代对象。这些请求还将包含一个回调（可能相同），然后由Scrapy下载，然后由指定的回调处理它们的响应。
3. 在回调函数中，您通常使用选择器解析页面内容（但您也可以使用BeautifulSoup，lxml或您喜欢的任何机制）并使用解析的数据生成项目。
4. 最后，从蜘蛛返回的项目通常会持久保存到数据库（在某些[Item Pipeline](https://docs.scrapy.org/en/latest/topics/item-pipeline.html#topics-item-pipeline)或使用[Feed exports](https://docs.scrapy.org/en/latest/topics/feed-exports.html#topics-feed-exports)写入文件。

尽管这个循环（或多或少）适用于任何类型的蜘蛛，但是为了不同的目的，Scrapy中捆绑了不同种类的默认蜘蛛。我们将在这里讨论这些类型。

# **scrapy.Spider**
## **class scrapy.spiders.Spider**

这是最简单的蜘蛛，也是每个其他蜘蛛必须继承的蜘蛛（包括与Scrapy捆绑在一起的蜘蛛，以及你自己编写的蜘蛛）。它不提供任何特殊功能。它只提供了一个默认的`start_requests()`实现，它从`start_urls` spider属性发送请求，并为每个结果响应调用spider的方法`parse`。

### name
一个字符串，用于定义此蜘蛛的名称。蜘蛛名称是Scrapy如何定位（并实例化）蜘蛛，因此它必须是**唯一**的。但是，没有什么可以阻止您实例化同一个蜘蛛。这是最重要的蜘蛛属性，它是必需的。

如果蜘蛛爬取单个域，通常的做法是在域之后命名蜘蛛，无论是否有[TLD(Top-level domain)](https://en.wikipedia.org/wiki/Top-level_domain)。因此，例如，爬取`mywebsite.com`的蜘蛛通常被称为`mywebsite`。

### allowed_domains
包含允许此爬虫爬行的域的字符串的可选列表。如果启用`OffsiteMiddleware`，则不会遵循不属于此列表（或其子域）中指定的域名的URL的请求。

假设您的目标网址是`https://www.example.com/1.html`，然后将`"example.com"`添加到列表中。

### start_urls
当没有指定特定URL时，蜘蛛将开始爬取的URL列表。因此，下载的第一页将是此处列出的页面。后续请求将从起始URL中包含的数据连续生成。

### custom_settings
运行此蜘蛛时将从项目范围配置中覆盖的设置字典。必须将其定义为类属性，因为在实例化之前更新了设置。

有关可用内置设置的列表，请参阅：[Built-in settings reference](https://docs.scrapy.org/en/latest/topics/settings.html#topics-settings-ref)。

### crawler
初始化类后，此属性由`from_crawler()`类方法设置，并链接到此spider实例绑定到的`Crawler`对象。

Crawler在项目中封装(encapsulate )了许多组件，用于单一条目访问（例如扩展，中间件，信号管理器等）。请参阅[Crawler API](https://docs.scrapy.org/en/latest/topics/api.html#topics-api-crawler)以了解有关它们的更多信息。

### settings
运行此蜘蛛的配置。这是一个[settings](https://docs.scrapy.org/en/latest/topics/api.html#scrapy.settings.Settings)实例，有关此主题的详细介绍，请参阅[Settings](https://docs.scrapy.org/en/latest/topics/settings.html#topics-settings)主题。

### logger
使用Spider名称创建的Python记录器。您可以使用它来发送日志消息，如"[Logging from Spiders]https://docs.scrapy.org/en/latest/topics/logging.html#topics-logging-from-spiders)"中所述。

### from_crawler(*crawler, *args, **kwargs*)
它是Scrapy用来创造蜘蛛的类方法。

您可能不需要直接覆盖它，因为默认实现充当__init__() 方法的代理，使用给定参数*args*和命名参数*kwargs*调用它。

尽管如此，此方法在新实例中设置`crawler`和`settings`属性，以便稍后可以在spider代码中访问它们。

参数：
- **crawler**([Crawler](https://docs.scrapy.org/en/latest/topics/api.html#scrapy.crawler.Crawler)实例) - spider要绑定的爬虫
- **args**(*list*) - 传递给__init__()方法的参数
- **kwargs**(*dict*) - 传递给__init__()方法的关键字参数

### start_requests()
此方法必须返回一个带有第一个爬网请求的iterable。当蜘蛛打开进行刮擦时，Scrapy会调用它。 Scrapy只调用一次，因此将`start_requests()`实现为生成器是安全的。

默认实现为`start_urls`中的每个url生成`Request(url, dont_filter=True)`。

如果要更改用于开始抓取域的请求，则这是要覆盖的方法。例如，如果您需要使用`POST`请求登录，则可以执行以下操作：
```
class MySpider(scrapy.Spider):
    name = 'myspider'

    def start_requests(self):
        return [scrapy.FormRequest("http://www.example.com/login", formdata={'user':'join, 'pass': secret}, callback=self.logged_in)]
    
    def logged_in(self, response):
        # here you would extract links to follow and return Requests for
        # each of them, with another callback
        pass
```

### parse(*response*)
这是Scrapy在其请求未指定回调时处理下载的响应时使用的默认回调。

`parse`方法负责处理响应并返回要爬取的数据和/或更多URL。其他请求回调与`Spider`类具有相同的要求。

此方法以及任何其他Request回调必须返回可迭代的`Request`和/或dicts或`Item`对象。

参数：
- **response**([Response](https://docs.scrapy.org/en/latest/topics/request-response.html#scrapy.http.Response)) - 即将解析的响应

### log(*message[,level,component*])
通过Spider记录器发送日志消息的包装器，用于向后兼容。有关更多信息，请参阅[Logging from Spiders](https://docs.scrapy.org/en/latest/topics/logging.html#topics-logging-from-spiders)。

### closed(*reason*)
蜘蛛关闭时调用。此方法为`spider_closed`信号的`signals.connect()`提供了快捷方式。

让我们来看一个例子：
```python
import scrapy

class MySpider(scrapy.Spider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = [
        'http://www.example.com/1.html',
        'http://www.example.com/2.html',
        'http://www.example.com/3.html',
    ]

    def parse(self, response):
        self.logger.info('A response from %s just arrived!', response.url)
```
从单个回调中返回多个请求和项目：
```python
import scrapy

class MySpider(scrapy.Spider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = [
        'http://www.example.com/1.html',
        'http://www.example.com/2.html',
        'http://www.example.com/3.html',
    ]

    def parse(self, response):
        for h3 in response.xpath('//h3').getall():
            yield {"title":h3}
        
        for href in response.xpath("//a/@href").getall():
            yield scrapy.Request(response.urljoin(href), self.parse)
```
您可以直接使用`start_requests()`代替`start_urls`;为数据提供更多结构，您可以使用[Items](https://docs.scrapy.org/en/latest/topics/items.html#topics-items)：
```python
import scrapy
from myproject.items import MyItem

class MySpider(scrapy.Spider):
    name = 'example.com'
    allowed_domains = ['example.com']

    def start_requests(self):
        yield scrapy.Request('http://www.example.com/1.html', self.parse)
        yield scrapy.Request('http://www.example.com/2.html', self.parse)
        yield scrapy.Request('http://www.example.com/3.html', self.parse)

    def parse(self, response):
        for h3 in response.xpath('//h3').getall():
            yield MyItem(title=h3)

        for href in response.xpath('//a/@href').getall():
            yield scrapy.Request(response.urljoin(href), self.parse)
```


# **Spider arguments**
蜘蛛可以接收修改其行为的参数。 spider参数的一些常见用途是定义起始URL或将限制爬取到站点的某些部分，但它们可用于配置spider的任何功能。

Spider参数使用`-a`选项通过crawl命令传递。

例如：

`scrapy crawl myspider -a category=electronics`

爬虫可以在`__init__`方法中访问参数：
```python
import scrapy

class MySpider(scrapy.Spider):
    name = 'myspider'

    def __init__(self, category=None, *args, **kwargs):
        super(MySpider, self).__init__(*args, **kwargs)
        self.start_urls = ['http://www.example.com/categories/%s' % category]
        # ...
```
默认的`__init__`方法将接受任何spider参数并将它们作为属性复制到spider。上面的例子也可以写成如下：
```python
import scrapy

class MySpider(scrapy.Spider):
    name = 'myspider'

    def start_requests(self):
        yield scrapy.Request('http://www.example.com/categories/%s' % self.category)
```
请记住，爬虫参数只是字符串。蜘蛛本身不会进行任何解析。如果要从命令行设置`start_urls`属性，则必须使用[ast.literal_eval](https://docs.python.org/library/ast.html#ast.literal_eval)或[json.loads](https://docs.python.org/library/json.html#json.loads)等方法将其自行解析为列表，然后将其设置为属性。否则，将导致对`start_urls`字符串进行迭代（一个非常常见的python陷阱），导致每个字符被视为一个单独的URL。

一个有效的用例是设置`http auth`凭证，由`HttpAuthMiddleware`或用户代理(其由`UserAgentMiddleware`使用)使用：
```
scrapy crawl myspider -a http_user=myusr -a http_pass=mypassword -a user_agent=mybot
```
Spider参数也可以通过Scrapyd `schedule.json` API传递。请参阅[Scrapyd documentation](https://scrapyd.readthedocs.io/en/latest/)。

# **通用爬虫**
Scrapy附带了一些有用的通用爬虫，您可以使用这些爬虫来对你的爬虫进行子类化。他们的目的是为一些常见的抓取案例提供方便的功能，例如根据特定规则跟踪站点上的所有链接，从[Sitemaps](https://www.sitemaps.org/index.html)抓取或解析XML/CSV Feed。

对于以下蜘蛛中使用的示例，我们假设您有一个项目，其中包含在`myproject.items`模块中声明的`TestItem`：
```python
import scrapy

class TestItem(scrapy.Item):
    id = scrapy.Field()
    name = scrapy.Field()
    description = scrapy.Field()
```

## **CrawlSpider**
### ***class* scrapy.spiders.CrawlSpider**
这是用于抓取常规网站的最常用的蜘蛛，因为它通过定义一组规则为跟踪链接提供了便利的机制。它可能不是最适合您的特定网站或项目，但它在几种情况下足够通用，因此你可以从它开始并根据需要覆盖它以获得更多自定义功能，或者只是实现你自己的爬虫。

除了从Spider继承的属性（您必须指定）之外，此类还支持一个新属性：
### rules
这是一个（或多个）Rule对象的列表。每个规则定义用于爬取站点的特定行为。规则对象如下所述。如果多个规则匹配相同的链接，则将根据它们在此属性中定义的顺序使用第一个规则。

这个爬虫还暴露了一个可重写的方法：
### parse_start_url(*response*)
为start_urls响应调用此方法。它允许解析初始响应，并且必须返回`Item`对象，`Request`对象或包含其中任何一个的iterable。

## **Crawling rules**
### ***class* scrapy.spiders.Rule(*link_extractor, callback=None, cb_kwargs=None, follow=None, process_links=None, process_request=None*)**
`link_extractor`是一个[Link Extractor](https://docs.scrapy.org/en/latest/topics/link-extractors.html#topics-link-extractors)对象，它定义了如何从每个已爬网页面中提取链接。

`callback`是一个可调用的或一个字符串（在这种情况下，将使用来自具有该名称的spider对象的方法）为使用指定的link_extractor提取的每个链接调用。此回调接收响应作为其第一个参数，并且必须返回包含`Item`和/或`Request`对象（或其任何子类）的列表。

`cb_kwargs`是一个包含要传递给回调函数的关键字参数的dict。

`follow`是一个布尔值，指定是否应该从使用此规则提取的每个响应中跟踪链接。如果回调为None，则默认为True，否则默认为False。

`process_links`是一个可调用的或一个字符串（在这种情况下，将使用来自具有该名称的spider对象的方法），将使用指定的`link_extractor`为每个响应中提取的每个链接列表调用该方法。这主要用于过滤目的。

`process_request`是一个可调用的，或一个字符串（在这种情况下，将使用来自具有该名称的spider对象的方法），该方法将被此规则提取的每个请求调用，并且必须返回请求或None（以过滤掉请求） ）。

## CrawlSpider示例
现在让我们看看带有规则的示例CrawlSpider：
```python
import scrapy
from scrapy.spiders import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor

class MySpider(CrawlSpider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = ['http://www.example.com']

    rules = (
        # Extract links matching 'category.php' (but not matching 'subsection.php')
        # and follow links from them (since no callback means follow=True by default).
        Rule(LinkExtractor(allow=('category\.php', ), deny=('subsection\.php', ))),

        # Extract links matching 'item.php' and parse them with the spider's method parse_item
        Rule(LinkExtractor(allow=('item\.php', )), callback='parse_item'),
    )

    def parse_item(self, response):
        self.logger.info('Hi, this is an item page! %s', response.url)
        item = scrapy.Item()
        item['id'] = response.xpath('//td[@id="item_id"]/text()').re(r'ID: (\d+)')
        item['name'] = response.xpath('//td[@id="item_name"]/text()').get()
        item['description'] = response.xpath('//td[@id="item_description"]/text()').get()
        return item
```
这个爬虫会开始抓取example.com的主页，收集类别链接和项链接，使用`parse_item`方法解析后者。对于每个项目响应，将使用XPath从HTML中提取一些数据，并且将使用它填充`Item`。

## **XMLFeedSpider**
### ***class* scrapy.spiders.XMLFeedSpider**
XMLFeedSpider用于通过按某个节点名称迭代XML feed来解析XML feed。迭代器可以选自：`iternodes`，`xml`和`html`。出于性能原因，建议使用`iternodes`迭代器，因为`xml`和`html`迭代器一次生成整个DOM以便解析它。但是，在使用错误标记解析XML时，使用`html`作为迭代器可能很有用。

要设置迭代器和标记名称，必须定义以下类属性：
### iterator
一个字符串，它定义要使用的迭代器。它可以是：
- `iternodes` - 基于正则表达式的快速迭代器
- `html` - 一个使用`Selector`的迭代器。请记住，这使用DOM解析，并且必须在内存中加载所有DOM，这可能是大型Feed的问题
- `xml` - 一个使用`Selector`的迭代器。请记住，这使用DOM解析，并且必须在内存中加载所有DOM，这可能是大型Feed的问题

它默认为：'iternodes'。
### itertag
一个字符串，其中包含要迭代的节点（或元素）的名称。示例：

`itertag = 'product'`

### namespaces
一个`(prefix，uri)`元组列表，用于定义将使用此spider处理的该文档中可用的名称空间。`prefix`和`uri`将用于使用`register_namespace()`方法自动注册名称空间。

然后，您可以在`itertag`属性中指定具有名称空间的节点。

示例：
```python
class YourSpider(XMLFeedSpider):

    namespaces = [('n', 'http://www.sitemaps.org/schemas/sitemap/0.9')]
    itertag = 'n:url'
    # ...
```
除了这些新属性外，此蜘蛛还具有以下可重写方法：
### adapt_response(*response*)
[详情请看此](https://docs.scrapy.org/en/latest/topics/spiders.html#scrapy.spiders.XMLFeedSpider.adapt_response)
### parse_node(*response,selector*)
[详情请看此](https://docs.scrapy.org/en/latest/topics/spiders.html#scrapy.spiders.XMLFeedSpider.parse_node)
### process_results(*response,results*)
[详情请看此](https://docs.scrapy.org/en/latest/topics/spiders.html#scrapy.spiders.XMLFeedSpider.process_results)

## XMLFeedSpider example
```python
from scrapy.spiders import XMLFeedSpider
from myproject.items import TestItem

class MySpider(XMLFeedSpider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = ['http://www.example.com/feed.xml']
    iterator = 'iternodes'  # This is actually unnecessary, since it's the default value
    itertag = 'item'

    def parse_node(self, response, node):
        self.logger.info('Hi, this is a <%s> node!: %s', self.itertag, ''.join(node.getall()))

        item = TestItem()
        item['id'] = node.xpath('@id').get()
        item['name'] = node.xpath('name').get()
        item['description'] = node.xpath('description').get()
        return item
```
基本上我们在那里做的是创建一个爬虫，从给定的`start_urls`下载一个feed，然后遍历每个`item`标签，打印出来，并将一些随机数据存储在`Item`中。

## **CSVFeedSpider**
### ***class* scrapy.spiders.CSVFeedSpider**
这个蜘蛛与XMLFeedSpider非常相似，只不过它遍历行而不是节点。在每次迭代中调用的方法是`parse_row()`。
### delimiter
CSV文件中每个字段的分隔符字符串默认为`','`（逗号）。
### quotechar
带有CSV文件中每个字段的enclosure character的字符串默认为`'"'`（引号）。
### headers
CSV文件中的列名列表。
### parse_row(*response, row*)
使用CSV文件的每个提供（或检测到的）标头的密钥接收响应和字典（表示每行）。

## CSVFeedSpider example
让我们看一个与前一个类似的示例，但使用CSVFeedSpider：
```python
from scrapy.spiders import CSVFeedSpider
from myproject.items import TestItem

class MySpider(CSVFeedSpider):
    name = 'example.com'
    allowed_domains = ['example.com']
    start_urls = ['http://www.example.com/feed.csv']
    delimiter = ';'
    quotechar = "'"
    headers = ['id', 'name', 'description']

    def parse_row(self, response, row):
        self.logger.info('Hi, this is a row!: %r', row)

        item = TestItem()
        item['id'] = row['id']
        item['name'] = row['name']
        item['description'] = row['description']
        return item
```

## **SitemapSpider**
### ***class* scrapy.spiders.SitemapSpider**
SitemapSpider允许您通过使用Sitemaps发现URL来抓取网站。

它支持嵌套的站点地图，并从[robots.txt](http://www.robotstxt.org/)中发现站点地图网址。
### sitemap_urls
指向要抓取其网址的站点地图的网址列表。 

您还可以指向robots.txt，它将被解析以从中提取站点地图网址。

### sitemap_rules
元组列表`(regex, callback)`, 其中:
- `regex`是一个正则表达式，用于匹配从站点地图中提取的网址。

  则表达式可以是str或编译的正则表达式对象。
- callback是用于处理与正则表达式匹配的url的回调。回调可以是一个字符串（表示一个爬虫方法的名称）或一个可调用的。

示例：

`sitemap_rules = [('/product/', 'parse_product')]`

规则按顺序应用，并且仅使用匹配的第一个规则。

如果省略此属性，则将使用`parse`回调处理站点地图中找到的所有网址。

### sitemap_follow
应遵循的站点地图的正则表列表。这仅适用于使用指向其他站点地图文件的[站点地图索引文件](https://www.sitemaps.org/protocol.html#index)的站点。

默认情况下，将遵循所有站点地图。

### sitemap_alternate_links
指定是否应遵循一个`URL`的备用链接。这些是在同一个`url`块中传递的另一种语言的同一网站的链接。

示例：
```html
<url>
    <loc>http://example.com/</loc>
    <xhtml:link rel="alternate" hreflang="de" href="http://example.com/de"/>
</url>
```
设置`sitemap_alternate_links`后，这将检索两个URL。禁用`sitemap_alternate_links`后，系统只会检索`http://example.com/`。

默认`sitemap_alternate_links`已禁用。

### sitemap_filter(*entries*)
这是一个过滤功能，可以根据其属性覆盖选择站点地图条目。

示例：
```html
<url>
    <loc>http://example.com/</loc>
    <lastmod>2005-01-01</lastmod>
</url>
```
我们可以定义一个`sitemap_filter`函数来按日期过滤`entries`：
```python
from datetime import datetime
from scrapy.spiders import SitemapSpider

class FilteredSitemapSpider(SitemapSpider):
    name = 'filtered_sitemap_spider'
    allowed_domains = ['example.com']
    sitemap_urls = ['http://example.com/sitemap.xml']

    def sitemap_filter(self, entries):
        for entry in entries:
            date_time = datetime.strptime(entry['lastmod'], '%Y-%m-%d')
            if date_time.year >= 2005:
                yield entry
```
这将仅检索2005年和随后几年修改的`entries`。

`Entries`是从站点地图文档中提取的dict对象。通常，**键是标记名称，值是其中的文本**。

重要的是要注意：
- 由于需要loc属性，因此将丢弃没有此标记的条目
- 备用链接存储在具有关键字`alternate`的列表中（请参阅`sitemap_alternate_links`）
- 名称空间被删除，因此名为`{namespace}tagname`的lxml标记仅变为`tagname`

如果省略此方法，将处理站点地图中找到的所有条目，并观察其他属性及其设置。

## SitemapSpider示例
最简单的示例：使用`parse`回调处理通过站点地图发现的所有网址：
```python
from scrapy.spiders import SitemapSpider

class MySpider(SitemapSpider):
    sitemap_urls = ['http://www.example.com/sitemap.xml']

    def parse(self, response):
        pass # ... scrape item here ...
```
处理一些具有特定回调的网址和其他具有不同回调的网址：
```python
from scrapy.spiders import SitemapSpider

class MySpider(SitemapSpider):
    sitemap_urls = ['http://www.example.com/sitemap.xml']
    sitemap_rules = [
        ('/product/', 'parse_product'),
        ('/category/', 'parse_category'),
    ]

    def parse_product(self, response):
        pass # ... scrape product ...

    def parse_category(self, response):
        pass # ... scrape category ...
```
按照robots.txt文件中定义的站点地图，只关注其网址包含`/sitemap_shop`的站点地图：
```python
from scrapy.spiders import SitemapSpider

class MySpider(SitemapSpider):
    sitemap_urls = ['http://www.example.com/robots.txt']
    sitemap_rules = [
        ('/shop/', 'parse_shop'),
    ]
    sitemap_follow = ['/sitemap_shops']

    def parse_shop(self, response):
        pass # ... scrape shop here ...
```
将SitemapSpider与其他网址源结合使用：
```python
from scrapy.spiders import SitemapSpider

class MySpider(SitemapSpider):
    sitemap_urls = ['http://www.example.com/robots.txt']
    sitemap_rules = [
        ('/shop/', 'parse_shop'),
    ]

    other_urls = ['http://www.example.com/about']

    def start_requests(self):
        requests = list(super(MySpider, self).start_requests())
        requests += [scrapy.Request(x, self.parse_other) for x in self.other_urls]
        return requests

    def parse_shop(self, response):
        pass # ... scrape shop here ...

    def parse_other(self, response):
        pass # ... scrape other here ...
```