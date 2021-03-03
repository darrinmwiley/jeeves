import os
import discord
import requests
from bs4 import BeautifulSoup

from db_utils import get_kattis_problem, get_solution
from discord_utils import send_message, make_progress, edit_message, edit_message_to_file

headers = {
    'Access-Control-Allow-Origin': '*',
    'Access-Control-Allow-Methods': 'GET',
    'Access-Control-Allow-Headers': 'Content-Type',
    'Access-Control-Max-Age': '3600',
    'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0'
}

#TODO add progress update messages
#todo ACCOUNT FOR NON EXISTENCE
async def handle_message_writeup(message, client):
    if "-h" in message.content:
        await send_message(message.channel, "usage: !writeup [contest_name], use this to generate a writeup of a contest using the solutions available in the knowledge base")
        return

    progress = make_progress(1,2)
    response = await send_message(message.channel, "finding contest\n"+progress)

    cname = message.content[8:].strip()

    problem_list = await get_problem_list(cname, response)

    file = open(cname+".txt", "w")

    done = []

    x = 0
    for tag in problem_list:
        if tag in done:
            continue
        done.append(tag)
        file.write(str(chr(65+x))+": "+tag+"\n\n")
        x+=1
        prob = get_kattis_problem(tag)
        sol = get_solution(tag)
        if sol == None:
            file.write(tag+" is not currently in the knowledge base\n\n")
        else:
            prob = open(sol[4], "r")
            file.write(prob.read()+"\n\n")
    file.close();
    sendfile = discord.File(cname+".txt")
    os.remove(cname+".txt")
    await message.channel.send(file = sendfile)
    await response.delete()
    #await edit_message_to_file(response, sendfile)

def get_contest_id(name):
    url = "https://open.kattis.com/past-contests"
    req = requests.get(url, headers)
    soup = BeautifulSoup(req.content, 'html.parser')

    tables = soup.find_all("tbody")

    rows = tables[0].find_all("tr")

    for row in rows:
        a = row.find_all("a")[0]
        nm = a.get_text().lower()
        if nm == name.lower():
            return a['href'][10:]
    return None

async def get_problem_list(cname, response):

    id = get_contest_id(cname)

    progress = make_progress(2,1)
    await edit_message(response, "compiling solutions\n"+progress)

    url = "https://open.kattis.com/contests/"+id

    req = requests.get(url, headers)
    soup = BeautifulSoup(req.content, 'html.parser')

    titles = soup.find_all("th", {"class": "problemcolheader-standings"})

    problem_list = []

    for title in titles:
        problem_list.append(title.find_all("a")[0]['href'][20+len(str(id)):])

    return problem_list
