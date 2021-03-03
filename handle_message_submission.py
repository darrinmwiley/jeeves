import os
import discord
import requests
from shutil import copyfile

from db_utils import get_kattis_problem, get_solution, get_user_from_author, insert_solution
from kattis_utils import check_status, submit_helper
from scan import scan
from discord_utils import send_message, make_progress, edit_message, get_emoji

#TODO UPDATE WITH PROGRESS

async def handle_message_submission(message, client):
    attachment = message.attachments[0]
    fname = attachment.filename

    with open(fname, 'wb') as f:
        f.write(requests.get(attachment.url).content)

    annotation_issues = verify_annotation(fname)
    if annotation_issues is not None:
        await send_message(message.channel, annotation_issues)
        return


    progress = make_progress(1,2)
    response = await send_message(message.channel, "submitting...\n"+progress)

    cmd = fname+" "+message.content+" -f"
    id = submit_helper(cmd)
    if id.startswith("ERROR"):
        await send_message(message.channel, id)
    else:
        progress = make_progress(2,1)
        await edit_message(response, "judging...\n"+progress)
        split = id.split()
        post_status = check_status(split[0])
        status = post_status
        if status == "Accepted":
            user = get_user_from_author(message.author)
            post_status = on_accepted(f, fname, user)
        await edit_message(response, get_emoji(status)+" "+post_status)
    os.remove(fname)

def verify_annotation(fname):
    prefix = fname.split('.')[0]
    solved = get_solution(prefix)
    if solved != None:
        return "this problem is already solved"
    annotation = scan(fname)
    if len(annotation) == 0:
        return "denied, annotation not formatted correctly or does not exist"
    parsed = parse_annotation(annotation)
    if not parsed[0].lower().endswith(prefix.lower()):
        return "denied, annotation problem url does not match solution name"
    if len(parsed[1]) == 0 or len(parsed[1][0]) == 0:
        return "denied, at least one problem tag is required"
    if len(parsed[2]) < 5:
        return "denied, explanation was trivially short"
    if("TAGS:" not in annotation[1]):
        return "denied, no list of tags"
    if("EXPLANATION:" not in annotation[2]):
        return "denied, error reading explanation"
    return None

#return response string
def on_accepted(file, fname, user):
    prefix = fname.split('.')[0]
    annotation = scan(fname)
    parsed = parse_annotation(annotation)
    directory = "kb/"+prefix
    if not os.path.exists(directory):
        os.makedirs(directory)
    sol_path ="kb/"+prefix+"/"+fname
    copyfile(fname, sol_path)
    with open(prefix+".txt", 'w') as f:
        for ss in annotation:
            f.write(ss)
            if ss.startswith("TAGS:"):
                tags = ss[5:]
    write_up_path = "kb/"+prefix+"/"+prefix+".txt"
    copyfile(prefix+".txt", write_up_path)
    os.remove(prefix+".txt")
    kattis_prob = get_kattis_problem(prefix)
    kattis_id = kattis_prob[0]
    prob_id = kattis_prob[1]
    #we already have user

    insert_solution(kattis_id, prob_id, user, sol_path, write_up_path, parsed)
    return "Accepted! Adding your solution to the knowledge base."

def parse_annotation(annotation):
    url = annotation[0][12:].strip()
    taglist = annotation[1][5:].strip().split(",")
    for i in range(len(taglist)):
        taglist[i] = taglist[i].strip()
    explanation = ""
    for i in range(2, len(annotation)):
        explanation += annotation[i]
    return [url, taglist, explanation[12:]]
