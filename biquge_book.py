import os
import requests
from lxml import etree
import time
import random


# 获取下一页链接的函数
def next_url(next_url_element):
    #nxturl = 'http://www.365kk.cc/255/255036/'
    nxturl='https://www.bige3.cc/book/66/'
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


# 请求头，使用前需填入自己浏览器的信息
headers= {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36 Edg/119.0.0.0',
    'Cookie': 'hm=0614940c5550f8dc77073d3a2be486aa',
    #'Host': '',
    'Connection': 'keep-alive'
}


file = input('请建立一个存储图片的文件夹，输入文件夹名称即可: ')
y = os.path.exists(file)
if y == 1:
    #print('文件夹已存在')
    #file = input('请建立一个存储图片的文件夹，)输入文件夹名称即可: ')
    #os.mkdir(file)
    print('文件夹已存在,将保存进其中')
else:
    os.mkdir(file)
    print('文件夹不存在，已创建')
folder=file+'/'
 


# 小说主页
main_url = "https://www.bige3.cc/book/26580/"

# 使用get方法请求网页
main_resp = requests.get(main_url, headers=headers)

# 将网页内容按utf-8规范解码为文本形式
main_text = main_resp.content.decode('utf-8')

#调试用
print(main_text)

# 将文本内容创建为可解析元素
main_html = etree.HTML(main_text)


#bookTitle = main_html.xpath('/html/body/div[4]/div[1]/div/div/div[2]/div[1]/h1/text()')[0]
bookTitle=main_html.xpath('/html/body/div[4]/div[2]/h1/text()')[0]
#author = main_html.xpath('/html/body/div[4]/div[1]/div/div/div[2]/div[1]/div/p[1]/text()')[0]
author =main_html.xpath('/html/body/div[4]/div[2]/div[2]/span[1]/text()')[0]
#update = main_html.xpath('/html/body/div[4]/div[1]/div/div/div[2]/div[1]/div/p[5]/text()')[0]
#introduction = main_html.xpath('/html/body/div[4]/div[1]/div/div/div[2]/div[2]/text()')[0]
update=main_html.xpath('/html/body/div[4]/div[2]/div[2]/span[3]/text()')[0]
introduction=main_html.xpath('/html/body/div[4]/div[2]/div[4]/dl/dd/text()')[0]

# 调试期间仅爬取六个页面
maxPages = 6
cnt = 0

# 记录上一章节的标题
lastTitle = ''

# 爬取起点
url = 'https://www.bige3.cc/book/26580/1.html'

# 爬取终点
endurl = 'https://www.bige3.cc/book/26580/6.html'

#while url != endurl:
while True:
    cnt += 1  # 记录当前爬取的页面
    if cnt > maxPages:
        break  # 当爬取的页面数超过maxPages时停止
    
    resp = requests.get(url, headers)
    text = resp.content.decode('utf-8')
    html = etree.HTML(text)
    title = html.xpath('//*[@class="wap_none"]/text()')[0]
    contents = html.xpath('//*[@id="chaptercontent"]/text()')

    # 输出爬取进度信息
    print("cnt: {}, title = {}, url = {}".format(cnt, title, url))
    print(contents)
    file_name = f"{folder}/{bookTitle}"
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

    # 传入函数next_url得到下一页链接
    url = next_url(next_url_element)

    sleepTime = random.randint(2, 6)  # 产生一个2~5之间的随机数
    time.sleep(sleepTime)             # 暂停2~5之间随机的秒数

    
clean_data(file_name + '.txt', [bookTitle, author, update, introduction],file+"/")
print("complete!")

