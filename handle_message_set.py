import os
import io
import discord
import argparse
from datetime import datetime
from datetime import timedelta

from db_utils import get_user_from_author, select_problem_set
from create_contest import create_contest
from discord_utils import send_message

async def handle_message_set(message, client):
    #!set -n NAME -d DATE -t TIME -l LENGTH -p PROBLEMS -a ABOVE -b BELOW
    parser = argparse.ArgumentParser(prog = "!set", description = "set a kattis contest")
    parser.add_argument("-n", "--name", type=str, help="contest name, no spaces")
    parser.add_argument("-d","--date", type=str, help="contest date (YYYY-MM-DD)")
    parser.add_argument("-t","--time" , type=str, help="contest time (HH:MM)", nargs = "?", default = "12:00")
    parser.add_argument("-l","--length" , type=str, help="contest duration (HH:MM)", nargs = "?", default = "5:00")
    parser.add_argument("-p","--problems" , type=int, help="number of problems", nargs = "?", default = 7)
    parser.add_argument("-a","--above" , type=float, help="minimum problem difficulty", nargs = "?", default = 0.0)
    parser.add_argument("-b","--below" , type=float, help="maximum problem difficulty", nargs = "?", default = 10.0)
    parser.add_argument("-u","--unsolved", action="store_true", help="use this flag to only use unsolved problems")
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
        parsed = parser.parse_args(message.content[4:].strip().split())
    except:
        await send_message(message.channel, "invalid syntax")
        return

    user = get_user_from_author(message.author)
    if user[3] == 1:
        #await send_message(message.channel, "sure! setting contest.")
        split = message.content.split()
        name = parsed.name
        date = parsed.date
        time = parsed.time
        if name is None:
            await send_message(message.channel, "name is a required field")
            return
        if date is None:
            await send_message(message.channel, "date is a required field")
            return
        duration = parsed.length
        datesplit = date.split("-")
        year = int(datesplit[0])
        month = int(datesplit[1])
        day = int(datesplit[2])
        timesplit = time.split(":")
        hour = int(timesplit[0])
        minute = int(timesplit[1])
        durationsplit = duration.split(":")
        duration_hours = int(durationsplit[0])
        duration_minutes = int(durationsplit[1])
        cdt_time = datetime(year, month, day, hour, minute, 0, 0)
        utc_time = cdt_time + timedelta(hours = 6)

        results = select_problem_set(parsed.above, parsed.below, parsed.problems, parsed.unsolved)

        problems = []
        for result in results:
            problems.append(result)
        await create_contest(name, utc_time.year, utc_time.month, utc_time.day, utc_time.hour, utc_time.minute, utc_time.second, duration_hours*3600+duration_minutes*60, problems, message.channel)
    else:
        await send_message(message.channel, "absolutely not")
