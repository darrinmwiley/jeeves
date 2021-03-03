import argparse
import io

from table import table
from db_utils import get_problems_between_dates, get_user
from discord_utils import get_display_name
from discord_utils import send_message

async def handle_message_leaderboard(message, client):
    parser = argparse.ArgumentParser(prog = "!leaderboard", description = "Display Leaderboard")
    parser.add_argument("-l", "--length", type=int, help="number of positions to list", nargs = "?", default = 10)
    parser.add_argument("-a","--after",  type=str, help="consider problems on or after this date (YYYY-MM-DD)", nargs = "?", default = "2019-1-1")
    parser.add_argument("-b","--before", type=str, help="consider problems on or before this date (YYYY-MM-DD)", nargs = "?", default = "2099-1-1")
    parser.add_argument("-i","--ignore-diff",help="if this flag is true, ignore problem weight", action='store_true')
    response = ""

    help = "-h" in message.content;

    if help:
        output = io.StringIO()
        parser.print_help(output)
        response += output.getvalue() + "\n\n";
        await send_message(message.channel, response)
        return;
    parsed = None
    try:
        parsed = parser.parse_args(message.content[12:].strip().split())
    except:
        await send_message(message.channel, "invalid syntax")
        return
    lb_size = parsed.length
    after = parsed.after
    before = parsed.before
    ignore_diff = 2 if parsed.ignore_diff == True else 1

    before_arr = before.split("-")
    after_arr = after.split("-")

    probs = get_problems_between_dates(int(after_arr[0]),int(after_arr[1]),int(after_arr[2]),int(before_arr[0]),int(before_arr[1]),int(before_arr[2]))
    diffMap = dict()
    numMap = dict()
    for prob in probs:
        discordId = prob[0]
        if discordId not in diffMap:
            diffMap[discordId] = 0
            numMap[discordId] = 0
        diffMap[discordId] += prob[2]
        numMap[discordId] += 1;
    users = []
    for key in diffMap.keys():
        user = get_user(key)
        display_name = await get_display_name(user[1], client)
        users.append((display_name, diffMap[key], numMap[key]))
    index_to_sort_by = 1;#2 would be by abolute number of probs
    users = sorted(users, key = sort_by_tuple_index(ignore_diff, False))
    ans = []
    for i in range(min(lb_size, len(users))):
        ans.append((i+1, users[i][0], users[i][1], users[i][2]));
    if len(ans) == 0:
        response = "no problems solved at this time"
    else:
        response = table(("Rank", "User", "Diff Sum", "Solved"), ans, True)
    await send_message(message.channel, response);

#only works for numeric
def sort_by_tuple_index(index, asc):
    if asc:
        return lambda tup: tup[index]
    return lambda tup: -tup[index]
