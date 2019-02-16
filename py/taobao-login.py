#!/usr/bin/ env python3
# -*-coding:utf-8-*-

import urllib.request
import urllib.error
import re
import http.cookiejar
import urllib.parse
import urllib.error


# TODO:使用header的data发送请求模拟登陆
# 模拟登陆淘宝taobao.com 并获取响应


class TSpiderUnity:

    def __init__(self):
        # for init the parameter
        self.login_url = 'https://login.taobao.com/member/login.jhtml' #登陆url

        self.user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36'
        self.ua ='115#1WPQC11O1Tac9evwGCnA1CsoE562Cnf61gqiOsXM+5i14UPClpLe1HKouXCCI8c0jaUz+uTQ18pXszEQ9gf1bvz8ukNQi/KIUaUXAyVVaiJfyo+QAlFPen/8yzZQi/WJh5/8vBNDaLBfy5fpvn39IrL8ukZQgQXRhEPCOSgaCY9XuzFZASAyeKa8ukNQiFMJhUU4AWNcaB6fyzFQgSPoTRDv5h1pxfMSHmGsO7ZkdQQNr6RgtQ6NXzUq75rquEKbeLj9WPaKT+P5CC9yF1XwZ3t2Yk1fxYau4cjhT9vh7w10TxRBcxvj7p790EOaletqJog/ojbmRKdgmGmzUZ6TN8/mMAZxjZQNiUWrWsDNPIzo1H+tyCppS6YA4UGK+AhQSI0NGIn0Nj3UJrU5FtyoBZ6Cuh0AnwDQvLHeGnYhaFJB8jSGxa/T51BH0hxNEKnbXWgyhnDr/MLE2oTbuIJDRhJe1RxnZXqBpmKUj69pf01htpwWBKqXfBHrKxzCt9OBLCtunoQ2EAJLek03vPH0LIXg0NZC2UaLTZEFNg2BkZOehN6AiskQThsNGlLqrNNRd7dgNX4kT3HiCJkzZjpTgrU9xaC49/j+ug8wIS/F1mOAZMMKmrP6gNfGeKD/SL2WQOK8um2pT28VqIlFqs4IYWM2FPUMI1SLNuhee+m7sOEzxD6SIqsaHddm616LhIg+Lfd7PL5eNNay9CD0fhm1ZYPekO+P6B0zMjFv5UMEBseUopP8yVIMN9X6LSlpKiCyVCYWN4NejnDBCWTz+kCt90QqeI7oSMvQsRxRGS57JOTDSbqyUY18WSqpYgLSFLcrXSfG5gAbd+7/K7HtExhjfjM4UKn5QeiUVp6nqRlRt1mHmqTbLp0b70Um/NC/GUTqsm8FcbbA0aavIB3sAsptJxqy10DoAt+onh5OjmnF+5AkB/nRmFdaGekYUTUTkIzzFJ9ZpN1g8TCFSi6bgSWDLt/jmSdIvG5VBQksZv+C7PnoIWYp714dsnYZYH9Tq2UwRVRVJ974O48lOHaUL8vbHx8RP5M0DRyBuiCwpFIOoDZvp9Mx9DVwEPW4/f=='
        self.TPL_username = 'xxx'  # 此处为自己的账号
        self.TPL_password_2 = '15d6edce27e804e7f5b6dbf8aab507fe27f0c61ef18e28feb256674619f98ab773649a7225ad85ad710dc8d7d1001f295aed8e9710bbbf93dc8c94fbe8de26582be13b2d36b005e4b8bf4114acc6453c0fcbc7f3febb5fa9b72861077d07a9ffc3bc2bb61ffbfdeb4657ca352a163d6654ae19d7cde02e4cf4512574f822cc12'
        self.data = {
            'TPL_username': self.TPL_username,
            'TPL_password': '',
            'ncoToken': '2e70113c078b084d51b5a0a0fce2f7755c880295',
            'slideCodeShow': 'false',
            'useMobile': 'false',
            'lang': 'zh_CN',
            'loginsite': '0',
            'newlogin': '0',
            'TPL_redirect_url': '',
            'from': 'tb',
            'fc': 'default',
            'style': 'default',
            'css_style':'',
            'keyLogin': 'false',
            'qrLogin': 'true',
            'newMini': 'false',
            'newMini2': 'false',
            'tid': '',
            'loginType': '3',
            'minititle': '',
            'minipara': '',
            'pstrong': '',
            'sign': '' ,
            'need_sign': '',
            'isIgnore': '',
            'full_redirect': '',
            'sub_jump': '',
            'popid': '',
            'callback': '',
            'guf': '',
            'not_duplite_str': '',
            'need_user_id': '',
            'poy': '',
            'gvfdcname': '10',
            'gvfdcre': '',
            'from_encoding': '',
            'sub': '',
            'TPL_password_2': self.TPL_password_2,
            'loginASR': '1',
            'loginASRSuc': '1',
            'allp': '',
            'oslanguage': 'zh-CN',
            'sr': '1366*768',
            'osVer': '',
            'naviVer': 'chrome|71.0357898',
            'osACN': 'Mozilla',
            'osAV': '5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
            'osPF': 'Win32',
            'miserHardInfo': '',
            'appkey': '00000000',
            'nickLoginLink': '',
            'mobileLoginLink': 'https://login.taobao.com/member/login.jhtml?useMobile = true',
            'showAssistantLink': '',
            'um_token': 'HV02PAAZ0b83c243b7c64b415c2f8ab1077f72e3999999',
            'ua': self.ua
        }
        self.headers = {
            'Origin': 'https://login.taobao.com',
            'Referer': 'https://login.taobao.com/member/login.jhtml',
            'Content-Type': 'application/x-www-form-urlencoded',
            'User-Agent': self.user_agent
        }
        self.headers2 = {
            'User-Agent': self.user_agent
        }
        self.cookie = http.cookiejar.CookieJar()  # 设置cookie
        self.cookie_handler = urllib.request.HTTPCookieProcessor(self.cookie)  # handler of cookie
        self.opener = urllib.request.build_opener(self.cookie_handler)  # Link to OpenerDirector
        # 对 data数据编码
        self.post_data = urllib.parse.urlencode(self.data).encode('ascii')

    def __send_request(self):
        # for send request and return response
        req = urllib.request.Request(self.login_url, self.post_data, headers=self.headers)  # 请求行和请求头构成一个请求
        try:
            response = self.opener.open(req)  # 使用OpenerDirector 的open()方法请求 url或 request,得到响应值
        except urllib.error.HTTPError as e:
            print('HTTPError: The server couldn\'t fulfill the request.')
            print('\nHTTPError Code: ', e.code)
            print('\nHTTPError Reason: ', e.reason)
        except urllib.error.URLError as e:
            print('\nURLError: We failed to reach a server.')
            print('\nURLError Reason', e.reason)
        else:
            print('\nNo Error Occurs !')
            # response encoded
            content = response.read()  # 字节串编码格式
            return content
        finally:
            print('\nErrorProcessed !')
            print('...............................................')

    def __parse_response(self):
        # for parse the content using regex
        bytes_ = self.__send_request()
        # decode
        content = bytes_.decode('gbk')  # 解码gbk的编码格式
        return content

    def __re_parse_response(self):
        # arrange the flow of action
        content = self.__parse_response()
        #print(content)
        # 成功获得具有 "页面跳转中”的字样，说明成功登陆 ，之后我们提取
        # "https://passport.alibaba.com/mini_apply_st.js?site=0&token=1dODbiZbrk3ZM5VbfYWv5AA&callback=callback"
        # 中的 token字样

        # 使用 re提取token
        token = re.findall('(?<=token=)(.*)(?=&callback)', content)
       # print(token)
        url2 = 'https://passport.alibaba.com/mini_apply_st.js?site=0&token=%s&callback=callback' % str(token[0])
        # 进一步获取内容st
        req = urllib.request.Request(url2, headers=self.headers)
        response = urllib.request.urlopen(req)  # 获得返回值
        content_token = response.read().decode('utf-8')
        #print(content_token)
        return content_token

    def __re_re_parse_response(self):
        # 上一步获得token后我们继续提取st值
        content_token = self.__re_parse_response()
        st = re.findall('(?<={"st":")(.*)"}', content_token)
        #print(st)
        return st

    #"""
    def __get_login_html(self):
        # 当我们获取st值后，通过 st, TPL_usrname可以登陆
        st = self.__re_re_parse_response()
        final_login_url = 'https://login.taobao.com/member/vst.htm?st=%s' % (str(st[0]))
        req = urllib.request.Request(final_login_url, headers=self.headers2)
        response = self.opener.open(req)  # st opener打开带有新的cookie
        str_content = response.read().decode("gbk")
        print(str_content)
        return str_content
    #"""

    def __get_final_html(self):
        str_content = self.__get_login_html()
        # 提取top_location_href
        list_ = re.findall('(?<=top.location.href = ")(.*)(?=";)', str_content)
        top_location_href = str(list_[0])
        print(top_location_href)
        top_location_href_req = urllib.request.Request(top_location_href, headers=self.headers2)
        top_location_href_opener_response = self.opener.open(top_location_href_req)
        man_page = top_location_href_opener_response.read().decode('utf-8')
        #print(man_page)

        # 我们已经成功登陆，通过调用一个登陆后的第一个网页，可以得到有关“已买到宝贝”等的信息
        # 在manpage尝试提取“已买到宝贝”网页，并获取响应页面

        # 1.5.2019 1:18还是失败，很大可能是cookie处理的不对，或者头部信息缺失？
        # TODO:再浏览一遍请求的header
        # 1.5.2019 22:43 难道淘宝的登陆方式为什么显示的和请求的页面，差一个未登录呢？？？？

        have_bought_href = re.findall('(?<=<a id="bought" href=")(.*)(?=")', man_page)
        have_bought_url = 'https:' + str(have_bought_href[0])
        print(have_bought_url)
        # have_bought_req = urllib.request.Request(have_bought_url, headers=self.headers2)
        have_bought_response = self.opener.open(have_bought_url)
        list_bought_item = have_bought_response.read().decode('gbk')
        print(list_bought_item)
        # 现在用regex解析，提取“已买到的宝贝”的链接





    def start_crawl(self):
        #self.__re_parse_response()
       # self.__re_re_parse_response()
        #self.__get_login_html()
        self.__get_final_html()


        # 验证码的情形先不考虑


taobao = TSpiderUnity()
taobao.start_crawl()