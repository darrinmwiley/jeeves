from discord_utils import send_message

async def handle_message_help(message, client):
    response = "Commands: !help, !header, !easy, !status, !hint, !solution, !leaderboard, !me, !writeup, !solved, !tags, !problem\n\n"
    response += "Type a command followed by -h for more information\n\n"
    response += "You can also drop a file in this channel to submit to Kattis and our knowledge base. Just make sure it has a proper header and is named the same as the problem tag."
    await send_message(message.channel, response)
