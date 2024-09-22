import discord

from db_utils import get_all_solved
from table import table
from discord_utils import get_display_name
from discord_utils import send_message

async def handle_message_solved(message, client):
    if "-h" in message.content:
        await send_message(message.channel, "Use this to get a list of all solved problems. Takes no arguments")
        return
    results = get_all_solved()
    altered = []
    dict = {}
    for result in results:
        if result[3] not in dict:
            display_name = await get_display_name(result[3], client)
            dict[result[3]] = display_name
        altered.append((result[0], result[1], result[2], dict[result[3]], result[4]))
    fname = "solved_problems.txt"
    file = open(fname, "w")
    tab = table(("Problem Name", "Tag", "Diff","Solved By", "Date"), altered, False)
    file.write(tab)
    file.close()
    fil = discord.File(fname)
    await message.channel.send(file = fil)
