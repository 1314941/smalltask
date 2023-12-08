import random
import requests
import os
import time
import urllib.parse
from lxml import etree


# 获取下一页链接的函数
def next_url(next_url_element):
    nxturl = 'https://www.bige3.cc/book/'
    # rfind('/') 获取最后一个'/'字符的索引
    index = next_url_element.rfind('/') + 1
    nxturl += next_url_element[index:]
    return nxturl




# 数据清洗函数
def clean_data(filename, info,output_folder):
    """
    :param filename: 原文档名
    :param info: [bookTitle, author, update, introduction]
    """

    print("\n==== 数据清洗开始 ====")

    # 新的文件名
    btitle ="new"+info[0]+".txt"
    #new_filename ="new"+filename
    #保存到文件夹里
    new_filename = f"{output_folder}/{btitle}"

    # 打开两个文本文档
    f_old = open(filename, 'r', encoding='utf-8')
    f_new = open(new_filename, 'w', encoding='utf-8')

    # 首先在新的文档中写入书籍信息
    f_new.write('==  《' + info[0] + '》\r\n')  # 标题
    f_new.write('==  ' + info[1] + '\r\n')     # 作者
    f_new.write('==  ' + info[2] + '\r\n')     # 最后更新时间
    f_new.write("=" * 10)
    f_new.write('\r\n')
    f_new.write('==  ' + info[3] + '\r\n')     # 简介
    f_new.write("=" * 10)
    f_new.write('\r\n')

    lines = f_old.readlines()  # 按行读取原文档中的内容
    empty_cnt = 0  # 用于记录连续的空行数

    # 遍历原文档中的每行
    for line in lines:
        if line == '\n':        # 如果当前是空行
            empty_cnt += 1      # 连续空行数+1
            if empty_cnt >= 2:  # 如果连续空行数不少于2
                continue        # 直接读取下一行，当前空行不写入
        else:                   # 如果当前不是空行
            empty_cnt = 0       # 连续空行数清零
        if line.startswith("\u3000\u3000"):  # 如果有段首缩进
            line = line[2:]                  # 删除段首缩进
            f_new.write(line)                # 写入当前行
        elif line.startswith("第"):          # 如果当前行是章节标题
            f_new.write("\r\n")              # 写入换行
            f_new.write("-" * 20)            # 写入20个'-'
            f_new.write("\r\n")              # 写入换行
            f_new.write(line)                # 写入章节标题
        else:                                # 如果当前行是未缩进的普通段落
            f_new.write(line)                # 保持原样写入

    f_old.close()
    f_new.close()
    print(f"\n==== 数据清洗完成，新文件已保存到 {new_filename} ====")






header= {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36 Edg/119.0.0.0',
    'Cookie': 'hm=2ddbda39dfd88aa4b3ff183cae79e636',
    #'Host': '',
    'Connection': 'keep-alive'
}


url='https://www.bige3.cc/xuanhuan/'
response = requests.get(url=url,headers=header)

# 将网页内容按utf-8规范解码为文本形式
text = response.content.decode('utf-8')

# 将文本内容创建为可解析元素
html = etree.HTML(text)
ht=html.xpath('//div[@class="image"]/a/@href')

#拼接网页地址的例子
'''
url = 'https://www.bige3.cc/'
get_url = 'book/110697/'
next_url = urllib.parse.urljoin(url , get_url )
'''


# 遍历所有书籍目录地址
for htt in ht:
        shht=str(htt)
        print(shht)
        nxturl = 'https://www.bige3.cc/book/'
        # rfind('/') 获取最后一个'/'字符的索引
        #index = shht.rfind('/') + 1
        nxturl = urllib.parse.urljoin(nxturl,shht)
        print(nxturl)
        res = requests.get(url=nxturl,headers=header)
        t_res=res.content.decode('utf-8')
        #print(t_res)
        htt_tree = etree.HTML(t_res)
        #提取标题
        hh_title = htt_tree.xpath('/html/body/div[4]/div[2]/h1/text()')[0]
        author =htt_tree.xpath('/html/body/div[4]/div[2]/div[2]/span[1]/text()')[0]
        #update = main_html.xpath('/html/body/div[4]/div[1]/div/div/div[2]/div[1]/div/p[5]/text()')[0]
        #introduction = main_html.xpath('/html/body/div[4]/div[1]/div/div/div[2]/div[2]/text()')[0]
        update=htt_tree.xpath('/html/body/div[4]/div[2]/div[2]/span[3]/text()')[0]
        introduction=htt_tree.xpath('/html/body/div[4]/div[2]/div[4]/dl/dd/text()')[0]
        # 创建文件
        folder='./笔趣阁/' + hh_title
        try:
                os.makedirs(folder)
        except Exception:
                print('文件已创建！')
        #第一章节
        htt_tr = htt_tree.xpath('/html/body/div[4]/div[2]/div[3]/a[2]/@href')
        htt_tr =  nxturl + htt_tr[0]
        print(htt_tr)

        
        maxPages = 767
        cnt = 0 

        # 记录上一章节的标题
        lastTitle = ''

        # 爬取起点
        url =  htt_tr

        # 爬取终点
        endurl =htt_tree.xpath('/html/body/div[4]/div[2]/div[2]/span[4]/a/@href')
        endurl =  nxturl + endurl[0]
        
        while url != endurl:
        #while True:
            cnt += 1  # 记录当前爬取的页面
            if cnt > maxPages:
                     break  # 当爬取的页面数超过maxPages时停止
    
                    #resp = requests.get(url, headers)
            try:
                    resp = requests.get(url, header)  # 超时设置为10秒
            except:
                    for i in range(4):  # 循环去请求网站
                        resp = requests.get(url, header, timeout=20)
                        if resp.status_code == 200:
                                 break
            
            text = resp.content.decode('utf-8')
            html = etree.HTML(text)
            title = html.xpath('//*[@class="content"]/h1/text()')[0]
            contents = html.xpath('//*[@id="chaptercontent"]/text()')

              # 输出爬取进度信息
            print("cnt: {}, title = {}, url = {}".format(cnt, title, url))
             #print(contents)
            file_name = f"{folder}/{title}"
             #file_name=bookTitle+'.txt'
            #with open(bookTitle + '.txt', 'a', encoding='utf-8') as f_new:
            with open(file_name + '.txt', 'a', encoding='utf-8') as f_new:
              if title != lastTitle:  # 章节标题改变
                f_new.write(title)      # 写入新的章节标题
                lastTitle = title   # 更新章节标题
              for content in contents:
                f_new.write(content)
                f_new.write('\n\n')
            f_new.close( )

              # 获取"下一页"按钮指向的链接
            next_url_element = html.xpath('//*[@class="Readpage pagedown"]/a[3]/@href')[0]
            url='https://www.bige3.cc/'+next_url_element
            
            # 传入函数next_url得到下一页链接
            #url = next_url(next_url_element)

            sleepTime = random.randint(2, 6)  # 产生一个2~5之间的随机数
            time.sleep(sleepTime)             # 暂停2~5之间随机的秒数

    
        clean_data(file_name + '.txt', [hh_title, author, update, introduction],folder+"/")
        print("complete!")

