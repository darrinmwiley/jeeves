from db_utils import get_kattis_problem, get_solution
from discord_utils import send_message

async def handle_message_status(message, client):
    if "-h" in message.content:
        await send_message(message.channel, "usage: !status <tag>, use this to determine if any Kattis Problem has been solved yet")
        return

    tag = message.content[7:].lower().strip()

    prob = get_kattis_problem(tag)
    if prob == None:
        await send_message(message.channel, "that problem does not exist")
        return
    sol = get_solution(tag)
    if sol == None:
        res = tag+" is unsolved"
    else:
        res = tag+" has been solved"
    await send_message(message.channel, res)
