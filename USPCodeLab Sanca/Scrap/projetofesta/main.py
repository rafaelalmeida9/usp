from bs4 import BeautifulSoup
from urllib.request import urlopen
from urllib.error import HTTPError
from urllib.error import URLError
from openpyxl import Workbook, load_workbook
import csv

try:
    html = urlopen(
        'https://docs.google.com/spreadsheets/d/1988BmMRwyQwNTZpP5xqyWH8oCsXXG2KJOVLz8X2vJAA/export?format=xlsx&id=1988BmMRwyQwNTZpP5xqyWH8oCsXXG2KJOVLz8X2vJAA'
    )
	

except HTTPError as e:
    print(e)


# read by default 1st sheet of an excel file
#dataframe1 = pd.read_excel('roles.xlsx')
#print(dataframe1)

wb = load_workbook('roles.xlsx')
#print(wb)

#for sheet in wb:
#    print(sheet)


def filtro(item):
    if item == '':
        return False
    elif item.isnumeric():
        return False
    elif item == ' ':
        return False
    else:
        return True


lista = []
with open("role.csv", 'r', encoding='utf-8') as file:
    csvreader = csv.reader(file)
    for row in csvreader:
        for item in row:
            if (filtro(item)):
                lista.append(item)

def filtro2(lista):
    tam = len(lista)
    for j in range(tam):
        if 'Semana' in lista[j]:
            print('jaja')

semana = "Semana"
lista_role = [[]]
lista_tmp = []
i = -1
for palavra in lista:

    if semana in palavra or palavra == "Natal":
        if i != -1:
            lista_copia = lista_tmp.copy()
            lista_role.append(lista_copia)
            lista_tmp.clear()
        i += 1

    if i != -1:
        lista_tmp.append(palavra)
        
# print(lista_role)

f = open("roles.txt", "w", encoding='utf-8')
for semana in lista_role:
    f.write(', '.join(semana).replace('\n',''))
    f.write('\n')
    # for role in semana:
    #     f.write(role)
    #     f.write('\n')
f.close()