from flask import Flask, request, jsonify
from datetime import datetime
import openpyxl

Buffer = []

def GetEmptyCell(sheet):
    i = 2
    while sheet[i][0].value != None:
        i += 1
    return i


def ListGenerate(sheet):
    num = GetEmptyCell(sheet)
    for i in range(len(Buffer)):
        for j in range(len(Buffer[i]['check'])):
            sheet[num][0].value = num - 1
            sheet[num][1].value = Buffer[i]['user_id']
            sheet[num][2].value = Buffer[i]['datetime']
            sheet[num][3].value = Buffer[i]['check'][j]['item']
            sheet[num][4].value = Buffer[i]['check'][j]['price']
            num += 1
    del num, i, j
    return sheet


def BufferToExcel():
    global Buffer
    try:
        book = openpyxl.open(r'C:\Users\Inquisitor\source\repos\Programming\Lab\02\excel\data.xlsx', read_only=False)
    except:
        book = openpyxl.Workbook()
    sheet = book.active
    if sheet['A1'].value == None:
        sheet['A1'] = 'N'
        sheet['B1'] = 'User ID'
        sheet['C1'] = 'Datetime'
        sheet['D1'] = 'Item'
        sheet['E1'] = 'Prise'
    sheet = ListGenerate(sheet)
    book.save(r'C:\Users\Inquisitor\source\repos\Programming\Lab\02\excel\data.xlsx')
    book.close()


def BufferGenerate(data):
    global Buffer
    data['datetime'] = datetime.now().strftime("%d.%m.%Y %H:%M:%S")
    Buffer.append(data)
    if len(Buffer) >= 1000:
        BufferToExcel()
        Buffer = []


app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        data = request.json
        BufferGenerate(data)
        return 'OK'
      
    elif request.method == 'GET':
        return 'Это GET запрос'
if __name__ == "__main__":
	app.run()
