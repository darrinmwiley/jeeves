import os
import discord
from dotenv import load_dotenv

from handle_message import handle_message

load_dotenv()
TOKEN = os.getenv('DISCORD_TOKEN')
GUILD = os.getenv('DISCORD_GUILD')
CHANNEL = os.getenv('CHANNEL')

client = discord.Client()

@client.event
async def on_message(message):
    if message.author == client.user:
        return
    if message.channel.name != CHANNEL:
        return
    await handle_message(message, client)

@client.event
async def on_ready():
    guild = discord.utils.get(client.guilds, name=GUILD)
    channel = None
    for ch in guild.channels:
        if ch.name == CHANNEL:
            channel = ch
    #await channel.send("ready")

async def message_in_channel(channel, message):
    guild = discord.utils.get(client.guilds, name=GUILD)
    chan = None
    for ch in guild.channels:
        if ch.name == channel:
            chan = ch
    if chan != None:
        await chan.send(message)

client.run(TOKEN)
