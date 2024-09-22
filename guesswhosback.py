# This example requires the 'message_content' intent.
import os
import discord
from dotenv import load_dotenv
from handle_message import handle_message

load_dotenv()
TOKEN = os.getenv('DISCORD_TOKEN')
GUILD = "UTD Codeburners"
CHANNEL = "general"

class MyClient(discord.Client):
    async def on_message(self, message):
        if message.author == client.user:
            return
        if message.channel.name != CHANNEL:
            return
        await handle_message(message, client)

    async def on_ready(self):
        guild = discord.utils.get(client.guilds, name=GUILD)
        channel = None
        for ch in guild.channels:
            if ch.name == CHANNEL:
                channel = ch
        await channel.send("I host myself")

    async def message_in_channel(channel, message):
        guild = discord.utils.get(client.guilds, name=GUILD)
        chan = None
        for ch in guild.channels:
            if ch.name == channel:
                chan = ch
        if chan != None:
            await chan.send(message)

intents = discord.Intents.default()
intents.message_content = True

client = MyClient(intents=intents)
client.run(TOKEN)
