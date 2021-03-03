import discord
import os

from db_utils import get_tags
from table import table
from discord_utils import send_message

async def handle_message_tags(message, client):
    if "-h" in message.content:
        await send_message(message.channel, "generate a list of tags")
        return
    results = get_tags()
    fname = "tags.txt"
    file = open(fname, "w")
    tab = table(("Tag", "Prob #"), results, False)
    file.write(tab)
    file.close()
    fil = discord.File(fname)
    await message.channel.send(file = fil)
    os.remove(fname)
