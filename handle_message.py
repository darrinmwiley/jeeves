import os
import discord
from dotenv import load_dotenv

from handle_message_no_response import handle_message_no_response
from handle_message_help import handle_message_help
from handle_message_header import handle_message_header
from handle_message_easy import handle_message_easy
from handle_message_status import handle_message_status
from handle_message_hint import handle_message_hint
from handle_message_solution import handle_message_solution
from handle_message_leaderboard import handle_message_leaderboard
from handle_message_me import handle_message_me
from handle_message_update import handle_message_update
from handle_message_writeup import handle_message_writeup
from handle_message_solved import handle_message_solved
from handle_message_tags import handle_message_tags
from handle_message_consolidate import handle_message_consolidate
from handle_message_problem import handle_message_problem
from handle_message_set import handle_message_set
from handle_message_submission import handle_message_submission

handler_dict = {
    "!help": handle_message_help,
    "!header":handle_message_header,
    "!easy":handle_message_easy,
    "!status":handle_message_status,
    "!hint":handle_message_hint,
    "!solution":handle_message_solution,
    "!leaderboard":handle_message_leaderboard,
    "!me":handle_message_me,
    "!update":handle_message_update,
    "!writeup":handle_message_writeup,
    "!solved":handle_message_solved,
    "!tags":handle_message_tags,
    "!consolidate":handle_message_consolidate,
    "!problem":handle_message_problem,
    "!set":handle_message_set
}

async def handle_message(message, client):
    handle_func = get_message_handler(message)
    await handle_func(message,client)

def get_message_handler(message):
    for key in handler_dict:
        if message.content.lower().startswith(key):
            return handler_dict[key]
    if len(message.attachments) != 0:
        return handle_message_submission
    return handle_message_no_response
