import os
import discord
import random
import argparse
import io

from db_utils import get_problems_in_difficulty_range, get_problems_in_difficulty_range_with_tags
from table import table
from discord_utils import send_message

async def handle_message_problem(message, client):
    parser = argparse.ArgumentParser(prog = "!problem", description = "pick a set of problems")
    parser.add_argument("-l", "--least", type=float, help="low range for difficulty", nargs = "?", default = 0)
    parser.add_argument("-m","--most", type=float, help="high range for difficulty", nargs = "?", default = 10)
    parser.add_argument("-t","--tag" , type=str, help="only retrieve problems with this tag", nargs = "?")
    parser.add_argument("-n","--num" , type=int, help="number of problems to retrieve", nargs = "?", default = 1)
    response = ""

    help = "-h" in message.content;

    if help:
        output = io.StringIO()
        parser.print_help(output)
        response += output.getvalue() + "\n\n";
        await send_message(message.channel, response)
        return;
    parsed = None
    try:
        parsed = parser.parse_args(message.content[8:].strip().split())
    except:
        await send_message(message.channel, "invalid syntax")
        return
    length = parsed.num
    low_range = parsed.least
    high_range = parsed.most

    if parsed.tag:
        probs = get_problems_in_difficulty_range_with_tags(low_range, high_range, parsed.tag)
    else:
        probs = get_problems_in_difficulty_range(low_range, high_range)

    random.shuffle(probs)

    ans = []

    while len(probs) != 0 and len(ans) != length:
        prob = probs.pop()
        ans.append(("http://open.kattis.com/problems/"+prob[0], prob[1]))

    if len(ans) == 0:
        response = "no problems available"
        await send_message(message.channel, response)
        return

    if len(ans) == 1:
        response = ans[0][0]+" ("+str(ans[0][1])+")"
        await send_message(message.channel, response)
        return

    if len(ans) <= 10:
        for i in range(len(ans)):
            ans[i][0]
        response = table(("URL","Difficulty"), ans, True)
        await send_message(message.channel, response)
        return
    else:
        fname = "problems.txt"
        file = open(fname, "w")
        tab = table(("URL","Difficulty"), ans, False)
        file.write(tab)
        file.close()
        fil = discord.File(fname)
        await send_message(message.channel, response)
        await message.channel.send(file = fil)
        os.remove(fname)
