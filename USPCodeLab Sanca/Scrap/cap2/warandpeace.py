from urllib.request import urlopen
from urllib.error import HTTPError
from urllib.error import URLError
from bs4 import BeautifulSoup

try:
    html = urlopen('https://www.pythonscraping.com/pages/warandpeace.html')
except HTTPError as e:
    print(e)
except URLError as e:
    print("Server not found")
else:
    bs = BeautifulSoup(html.read(),'html.parser')
    green = bs.find_all('span',{'class':'green'})

    for name in green:
        print(name.get_text())