# FIRST STEPS
## Scrapy at a glance
Scrapy是一种用于抓取网站和提取结构化数据的应用程序框架，可用于广泛的有用应用程序，如数据挖掘，信息处理或历史存档。

尽管Scrapy最初是为网络抓取而设计的，但它也可以用于使用API​​（例如Amazon Associates Web Services）或作为通用网络爬虫来提取数据。

## 一个蜘蛛示例过程
为了向您展示Scrapy带来的内容，我们将以最简单的方式运行蜘蛛，向您介绍Scrapy Spider的示例。

这是一个蜘蛛的代码，它在网页http://quotes.toscrape.com上爬取quotes：
```python
import scrapy


class QuotesSpider(scrapy.Spider):
    name = 'quotes'
    start_urls = [
        'http://quotes.toscrape.com/tag/humor/',
    ]

    def parse(self, response):
        for quote in response.css('div.quote'):
            yield {
                'text': quote.css('span.text::text').get(),
                'author': quote.xpath('span/small/text()').get(),
            }

        next_page = response.css('li.next a::attr("href")').get()
        if next_page is not None:
            yield response.follow(next_page, self.parse)
```
将它放在一个文本文件中，将其命名为quotes_spider.py并使用runspider命令运行spider：
```python
scrapy runspider quotes_spider.py -o quotes.json
```
完成后，你将在quotes.json文件中包含JSON格式的引号列表，其中包含文本和作者，如下所示（为了更好的可读性，此处重新格式化）：
```
[{
    "author": "Jane Austen",
    "text": "\u201cThe person, be it gentleman or lady, who has not pleasure in a good novel, must be intolerably stupid.\u201d"
},
{
    "author": "Groucho Marx",
    "text": "\u201cOutside of a dog, a book is man's best friend. Inside of a dog it's too dark to read.\u201d"
},
{
    "author": "Steve Martin",
    "text": "\u201cA day without sunshine is like, you know, night.\u201d"
},
...]
```
## **What just happened?**
当您运行命令scrapy runspider quotes_spider.py时，Scrapy在其中查找Spider定义并通过其爬虫引擎运行它。

通过向start_urls属性中定义的URL发出请求（在这种情况下，URL只是包含humor category 条目）开始爬行，并调用默认的回调方法parse，将响应对象作为参数传递。parse回调中,我们使用CSS选择器来循环浏览元素,yield一个具有提取的引用文本和作者的python字典，寻找下一个页面的链接和使用与回调相同的解析方法安排另一个请求。

在这里，您会注意到Scrapy的一个主要优点：请求是[异步调度和处理](https://docs.scrapy.org/en/latest/topics/architecture.html#topics-architecture)的。这意味着Scrapy不需要等待请求完成和处理，它可以在此期间发送另一个请求或执行其他操作。这也意味着即使某些请求失败或在处理错误时发生错误，其他请求也可以继续运行。

这使您能够进行非常快速的爬网（以容错的方式同时发送多个并发请求），但Scrapy还可以通过一些[设置](https://docs.scrapy.org/en/latest/topics/settings.html#topics-settings-ref)控制爬取的礼貌(?the politeness of the crawl)。您可以执行以下操作：在每个请求之间设置下载延迟，限制每个域或每个IP的并发请求数量，甚至使用自动限制扩展，以尝试自动解决这些问题。
> NOTE
> 
> 这是使用[feed exports](https://docs.scrapy.org/en/latest/topics/feed-exports.html#topics-feed-exports)导出生成JSON文件，您可以轻松更改导出格式（例如XML或CSV）或存储后端（例如FTP或Amazon S3）。您还可以编写项目管道以将项目存储在数据库中。

## 还有什么？
您已经了解了如何使用Scrapy从网站中提取和存储项目，但这只是表面。 Scrapy提供了许多强大的功能，可以轻松高效地进行抓取，例如：
- 内置支持使用扩展的CSS选择器和XPath表达式从HTML / XML源中选择和提取数据，并使用正则表达式提取辅助方法。
- 一个交互式shell控制台（支持IPython），用于尝试使用CSS和XPath表达式来抓取数据，在编写或调试蜘蛛时非常有用。
- 内置支持以多种格式（JSON，CSV，XML）生成Feed导出并将其存储在多个后端（FTP，S3，本地文件系统）中。
- 强大的编码支持和自动检测，用于处理外部，非标准和损坏的编码声明。
- 强大的可扩展性支持，允许您使用信号和定义良好的API（中间件，扩展和管道）插入您自己的功能。
- 广泛的内置扩展和中间件用于处理：
  - cookie和会话处理
  - HTTP功能，如压缩，身份验证，缓存
  - 用户代理欺骗
  - robots.txt
  - 爬行深度限制
  - 更多
- 一个Telnet控制台，用于连接到Scrapy进程内运行的Python控制台，以内省和调试您的爬虫
- 还有其他好东西，比如可重复使用的蜘蛛，可以从Sitemaps和XML / CSV Feed中抓取网站，自动下载与抓取项目相关联的图像（或任何其他媒体）的媒体管道，缓存DNS解析器等等！

## **What's next?**
接下来的步骤是安装Scrapy，按照教程学习如何创建一个完整的Scrapy项目并加入社区。谢谢你的关注！