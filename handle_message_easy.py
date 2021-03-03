from db_utils import get_easiest_unsolved
from discord_utils import send_message

async def handle_message_easy(message, client):
    if "-h" in message.content:
        await send_message(message.channel, "Use this command to get an unsolved problem with the lowest difficulty on Kattis\n\nTakes no arguments")
        return
    easy = get_easiest_unsolved()
    await send_message(message.channel, "http://open.kattis.com/problems/"+easy[3])
