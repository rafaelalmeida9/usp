from urllib.request import urlopen
from urllib.error import HTTPError
from urllib.error import URLError
from bs4 import BeautifulSoup
import re

try:
    html = urlopen('https://www.pythonscraping.com/pages/page3.html')
except HTTPError as e:
    print(e)
except URLError as e:
    print('Server not found')
else:
    bs = BeautifulSoup(html.read(),'html.parser')
    
    # #Exibe os filhos de 'table'
    # for child in bs.find('table',{'id':'giftList'}).children:
    #     print(child)

    # #Exibe os descendentes de 'table', isto eh, os filhos e todas as tags abaixo deles recursivamente
    # for child in bs.find('table',{'id':'giftList'}).descendants:
    #     print(child)

    # #Exibe os proximos irmaos de tr, excluindo ele proprio
    # for sibling in bs.find('table',{'id':'giftList'}).tr.next_siblings:
    #     print(sibling)

    # #Obtem o irmão anterior do pai da tag 'img', com src '../img/gifts/img1.jpg'
    # preco = bs.find('img',{'src':'../img/gifts/img1.jpg'}).parent.previous_sibling
    # print(preco.get_text())

    # #Regex para achar os 'src' das imagens do diretório '../img/gifts'
    # images = bs.find_all('img',{'src':re.compile('\.\.\/img\/gifts\/img.*\.jpg')})
    # for image in images:
    #     print(image['src'])

    #Exibe todas as tags com 2 atributos
    tagList = bs.find_all(lambda tag: len(tag.attrs) == 2)
    for tag in tagList:
        print(tag)
        print('|--------------|')