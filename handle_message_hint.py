import discord

from db_utils import get_kattis_problem, get_solution
from discord_utils import send_message

async def handle_message_hint(message, client):
    tag = message.content[5:].strip()
    if "-h" in message.content:
        await send_message(message.channel, "Usage: !hint <tag>, use this to get the annotation for any solution in the knowledge base")
        return
    prob = get_kattis_problem(tag)
    if prob == None:
        await send_message(message.channel, "That problem does not exist")
        return None
    sol = get_solution(tag)
    if sol == None:
        await send_message(message.channel, tag+" is unsolved")
        return None
    file = discord.File(sol[4])
    await message.channel.send(file = file)
