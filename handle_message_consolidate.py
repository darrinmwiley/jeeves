import argparse
import io
from db_utils import consolidate_tag, get_user_from_author
from discord_utils import send_message
async def handle_message_consolidate(message, client):
    parser = argparse.ArgumentParser(prog='consolidate', usage='consolidate two tags')
    parser.add_argument('-a', '--child', nargs='?', help='child tag')
    parser.add_argument('-b', '--parent', nargs='?', help='parent tag')
    help = "-h" in message.content
    response = ""
    if help:
        output = io.StringIO()
        parser.print_help(output)
        response += output.getvalue() + "\n\n"
        await send_message(message.channel, response)
        return;
    user = get_user_from_author(message.author)
    if user[3] == 1:
        parsed = None
        try:
            parsed = parser.parse_args(message.content[12:].strip().split())
            rc = consolidate_tag(parsed.child, parsed.parent)
            await send_message(message.channel, str(rc)+" rows affected")
        except:
            await send_message(message.channel, "invalid syntax")
            return
    else:
        await send_message(message.channel, "absolutely not")
