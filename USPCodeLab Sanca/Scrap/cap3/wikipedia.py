from urllib.request import urlopen
from urllib.error import HTTPError
from urllib.error import URLError
from bs4 import BeautifulSoup
import re
import random

def getLinks(url):
    url2 = 'https://pt.wikipedia.org' + url

    try:
        html = urlopen(url2)
    except HTTPError as e:
        return None
    except URLError as e:
        return None

    bs = BeautifulSoup(html.read(),'html.parser')

    links = bs.find('div',{'id':'bodyContent'}).find_all('a',{'href':re.compile('^\/wiki\/((?!:).)*$')})

    return [link['href'] for link in links if 'href' in link.attrs]

url = ''

for i in range(0,30):
    links = getLinks(url)
    url = links[random.randint(0,len(links)-1)]
    print(url)