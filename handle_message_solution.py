import discord

from db_utils import get_kattis_problem, get_solution
from discord_utils import send_message

async def handle_message_solution(message, client):
    tag = message.content[9:].strip()
    if "-h" in message.content:
        await send_message(message.channel, "usage: !solution <tag>, use this to see the code for any solution in the knowledge base")
        return
    prob = get_kattis_problem(tag)
    if prob == None:
        await send_message(message.channel, "that problem does not exist")
        return None
    sol = get_solution(tag)
    if sol == None:
        await send_message(message.channel, tag+" is unsolved")
        return None
    file = discord.File(sol[3])
    await message.channel.send(file = file)
