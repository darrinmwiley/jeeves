from bs4 import BeautifulSoup
import requests
import mysql.connector

begin = "BEGIN ANNOTATION"
end = "END ANNOTATION"

def scan(fname):
    f = open(fname,"r")
    annotation = []
    flag = False
    for str in f.readlines():
        if end in str:
            flag = False
        if flag:
            annotation.append(str)
        if begin in str:
            flag = True
    if not flag:
        return annotation
    return []
