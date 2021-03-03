import os
from dotenv import load_dotenv

from db_utils import get_user_from_author
from scrape import scrape
from discord_utils import send_message

load_dotenv()
HOST = os.getenv('DB_HOST')
USER = os.getenv('DB_USER')
PASSWD = os.getenv('DB_PASSWD')
DATABASE = os.getenv('DB_DATABASE')

#TODO fix difficulty update
async def handle_message_update(message, client):
    user = get_user_from_author(message.author)
    if user[3] == 1:
        await send_message(message.channel, "updating my records, this may take a sec")
        added = scrape()
        if added == -1:
            await send_message(message.channel, "my code is broken, @TheDarBear")
        else:
            await send_message(message.channel, "all done, "+str(added)+" new problems scanned")
    else:
        await send_message(message.channel, "absolutely not")
