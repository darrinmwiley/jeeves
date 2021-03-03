import discord

async def get_display_name(discordId, client):
    user = await client.fetch_user(discordId)
    if user is None:
        return "none"
    return user.display_name

async def send_message(channel, description):
    embedVar = discord.Embed(description=description, color=0x9900cd)
    return await channel.send(embed = embedVar)

async def edit_message(message, description):
    embedVar = discord.Embed(description=description, color=0x9900cd)
    await message.edit(embed = embedVar)

async def edit_message_to_file(message, f):
    await message.edit(file = f)

def make_progress(green, red):
    ret = ""
    for i in range(green):
        ret+=":green_square:"
    for i in range(red):
        ret+=":red_square:"
    return ret

def get_emoji(verdict):
    if verdict == "Accepted":
        return ":white_check_mark:"
    if verdict == "Time Limit Exceeded":
        return ":alarm_clock:"
    return ":x:"
