import discord
import argparse
import os
import io
import time

from discord_utils import send_message
from db_utils import get_user_problems_solved, get_user_stats, get_user_from_author
from table import table
from discord_utils import send_message

embedVar = discord.Embed(title="Title", description="Desc", color=0x9900cd)
embedVar.add_field(name="Field1", value="hi", inline=False)
embedVar.add_field(name="Field2", value="hi2", inline=False)

async def handle_message_me(message, client):
    parser = argparse.ArgumentParser(prog = "!me", description = "see information about yourself")
    parser.add_argument("-a","--all",help="if this flag is true, list all problems solved", action='store_true')
    response = ""

    help = "-h" in message.content;

    if help:
        output = io.StringIO()
        parser.print_help(output)
        response += output.getvalue() + "\n\n";
        await send_message(message.channel, response)
        return
    parsed = None
    try:
        parsed = parser.parse_args(message.content[3:].strip().split())
    except:
        await send_message(message.channel, "invalid syntax")
        return
    result = get_user_stats(message.author.id)
    if result == None or result[1] == 0:
        response = "you haven't solved anything yet."
    else:
        response = "you've solved "+str(result[1])+" problems, with a combined difficulty of "+str(result[0])+". ("+"{:.2f}".format(result[0]/result[1])+" avg)"

    if parsed.all:
        user = get_user_from_author(message.author)
        results = get_user_problems_solved(message.author.id)
        fname = "solved_problems.txt"
        file = open(fname, "w")
        tab = table(("Problem Name", "Tag", "Diff", "Date"), results, False)
        file.write(tab)
        file.close()
        fil = discord.File("solved_problems.txt")
        await send_message(message.channel, description = response)
        await message.channel.send(file = fil)
        os.remove(fname)
    else:
        await send_message(message.channel, description = response)
