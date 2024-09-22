import os
import discord
import requests
from shutil import copyfile

from db_utils import get_kattis_problem, get_solution, get_user_from_author, insert_solution
from kattis_utils import check_status, submit_helper
from scan import scan
from discord_utils import send_message, make_progress, edit_message, get_emoji

# Handle message submission, fetch attachments, and submit them for judging
async def handle_message_submission(message, client):
    attachment = message.attachments[0]
    fname = attachment.filename

    # Download and save the attachment locally
    with open(fname, 'wb') as f:
        f.write(requests.get(attachment.url).content)

    # Verify the submission's annotation
    annotation_issues = verify_annotation(fname)
    if annotation_issues is not None:
        await send_message(message.channel, annotation_issues)
        return

    # Create progress status
    progress = make_progress(1, 2)
    response = await send_message(message.channel, f"Submitting...\n{progress}")

    # Submit the solution to Kattis (or the relevant service)
    cmd = f"{fname} {message.content} -f"
    submission_id = submit_helper(cmd)

    # Handle error cases during submission
    if submission_id.startswith("ERROR"):
        await send_message(message.channel, submission_id)
    else:
        progress = make_progress(2, 1)
        await edit_message(response, f"Judging...\n{progress}")
        split = submission_id.split()

        # Check status of the submission
        post_status = check_status(split[0])
        status = post_status

        # If the submission is accepted, add it to the knowledge base
        if status == "Accepted":
            user = get_user_from_author(message.author)
            print(user)
            post_status = on_accepted(fname, user)

        # Update the message with the final status and appropriate emoji
        await edit_message(response, f"{get_emoji(status)} {post_status}")

    # Clean up by removing the downloaded file
    os.remove(fname)

# Verify the solution annotation and ensure it's valid
def verify_annotation(fname):
    prefix = fname.split('.')[0]
    solved = get_solution(prefix)

    if solved is not None:
        return "This problem is already solved."

    annotation = scan(fname)
    if len(annotation) == 0:
        return "Denied: Annotation not formatted correctly or does not exist."

    parsed = parse_annotation(annotation)

    # Validate the annotation against problem URL and tags
    if not parsed[0].lower().endswith(prefix.lower()):
        return "Denied: Annotation problem URL does not match solution name."
    if len(parsed[1]) == 0 or len(parsed[1][0]) == 0:
        return "Denied: At least one problem tag is required."
    if len(parsed[2]) < 5:
        return "Denied: Explanation was trivially short."
    if "TAGS:" not in annotation[1]:
        return "Denied: No list of tags."
    if "EXPLANATION:" not in annotation[2]:
        return "Denied: Error reading explanation."

    return None

# Handle accepted submission by adding it to the knowledge base
def on_accepted(fname, user):
    prefix = fname.split('.')[0]
    annotation = scan(fname)
    parsed = parse_annotation(annotation)

    # Create directories for storing the solution and write-up
    directory = f"kb/{prefix}"
    if not os.path.exists(directory):
        os.makedirs(directory)

    sol_path = f"kb/{prefix}/{fname}"
    copyfile(fname, sol_path)

    with open(f"{prefix}.txt", 'w') as f:
        for ss in annotation:
            f.write(ss)
            if ss.startswith("TAGS:"):
                tags = ss[5:]

    write_up_path = f"kb/{prefix}/{prefix}.txt"
    copyfile(f"{prefix}.txt", write_up_path)
    os.remove(f"{prefix}.txt")

    kattis_prob = get_kattis_problem(prefix)
    kattis_id = kattis_prob[0]
    prob_id = kattis_prob[1]

    # Insert the solution into the database
    insert_solution(kattis_id, prob_id, user, sol_path, write_up_path, parsed)

    return "Accepted! Adding your solution to the knowledge base."

# Parse the annotation from the solution
def parse_annotation(annotation):
    url = annotation[0][12:].strip()
    taglist = annotation[1][5:].strip().split(",")
    taglist = [tag.strip() for tag in taglist]
    explanation = "".join(annotation[2:])
    return [url, taglist, explanation[12:]]
