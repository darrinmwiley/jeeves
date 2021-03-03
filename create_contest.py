import os
from datetime import datetime, timedelta
import time
import argparse
import webbrowser
import requests
import requests.exceptions
from selenium import webdriver;
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.common.exceptions import TimeoutException
import urllib.request
import urllib.parse
from bs4 import BeautifulSoup
from dotenv import load_dotenv

from discord_utils import make_progress, send_message, edit_message

load_dotenv()
KATTIS_USER = os.getenv('KATTIS_USER')
KATTIS_PASS = os.getenv('KATTIS_PASS')

async def create_contest(name, year, month, day, hour, minute, second, duration_seconds, problems, channel):
    progress = make_progress(1,3)
    response = await send_message(channel, "creating new contest\n"+progress)
    driver = webdriver.PhantomJS()
    #driver = webdriver.Firefox()
    driver.get('http://open.kattis.com/login/email?')
    username = driver.find_element_by_name("user")
    username.send_keys(KATTIS_USER)
    password = driver.find_element_by_name("password")
    password.send_keys(KATTIS_PASS)
    submit = driver.find_element_by_name("submit")
    submit.click()

    progress = make_progress(2, 2)
    await edit_message(response, "editing fields\n"+progress)

    driver.get("https://open.kattis.com/new-contest")
    driver.find_element_by_id("session-name").send_keys(name);

    datetime_pattern = "{year:d}-{month:02d}-{day:02d} {hour:02d}:{minute:02d}:{second:02d}"
    start_time = datetime_pattern.format(year = year, month = month, day = day, hour = hour, minute = minute, second = second)

    cmd = "document.getElementById('start-time').value = '" + start_time+"';"
    driver.execute_script(cmd)

    MINUTE = 60
    HOUR = 60*MINUTE

    duration_pattern = "{hours:d}:{minutes:02d}:{seconds:02d}"
    duration = duration_pattern.format(hours = duration_seconds//HOUR, minutes = (duration_seconds%HOUR)//MINUTE, seconds = duration_seconds%MINUTE)

    cmd = "document.getElementById('duration').value = '" + duration+"';"
    driver.execute_script(cmd)

    driver.find_element_by_id("create-btn").click()

    time.sleep(5)

    progress = make_progress(3, 1)
    await edit_message(response, "adding problems\n"+progress)

    driver.get("https://open.kattis.com/contests")

    table = driver.find_element_by_class_name("table")

    soup = BeautifulSoup(table.get_attribute('innerHTML'), 'html.parser')

    rows = soup.find_all("tr")

    edit_href = None
    href = None
    flag = False

    for row in rows:
        aa = row.find_all("a")
        for a in aa:
            if a.get_text() == name and flag == False:
                edit_href = a['href']+"/edit"
                href = a['href']
                flag = True

    if edit_href is not None:
        driver.get("https://open.kattis.com"+edit_href)

    for problem in problems:
        driver.find_element_by_id("add-problem-name").clear()
        driver.find_element_by_id("add-problem-name").send_keys(problem)
        driver.find_element_by_id("add-problem-btn").click()
        time.sleep(5)

    driver.execute_script("window.alert = function(msg){};");
    driver.execute_script("window.confirm = function(msg){return true;};");
    driver.find_element_by_id("publish-btn").click()
    await edit_message(response, "http://open.kattis.com"+href)
