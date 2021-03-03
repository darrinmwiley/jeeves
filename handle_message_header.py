from discord_utils import send_message

async def handle_message_header(message, client):
    if "-h" in message.content[7:]:
        await send_message(message.channel, "The header returned by this command must go at the top of every submission for it to be accepted. That way, we have some information on the problem when we pull up your solution later.")
        return
    response = "/*\n"
    response += "BEGIN ANNOTATION\n"
    response += "PROBLEM URL: open.kattis.com/problems/example\n"
    response += "TAGS: example tag 1, example tag 2, etc...\n"
    response += "EXPLANATION:\n"
    response += "example explanation,\n"
    response += "can span multiple lines\n"
    response += "END ANNOTATION\n"
    response += "*/"
    await send_message(message.channel, response)
