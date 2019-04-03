import pymysql
import json
from datetime import datetime

def Sensor(jsonData):
  json_Dict = json.loads(jsonData.decode('utf-8'))
  Temp1 = json_Dict['Temp1']
  Hum1 = json_Dict['Hum1']
  Temp2 = json_Dict['Temp2']
  Hum2 = json_Dict['Hum2']
  Date_and_Time = (datetime.today()).strftime("%d-%b-%Y %H:%M:%S")
  # date_time = json_Dict['Date']
  # MO ket noi den Databas
  db = pymysql.connect("localhost","root","13071996","wsn")
  cursor = db.cursor()
  sql = """INSERT INTO Data(Temp1,Hum1,Temp2,Hum2,Date_and_Time) VALUES (%s,%s,%s,%s,%s)"""
  val = (Temp1,Hum1,Temp2,Hum2,Date_and_Time)
  cursor.execute(sql,val)
  db.commit()
  print ("Insert complete values topic  to db")
  print ("-----------------------------------------")
  db.close()
