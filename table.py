from __future__ import print_function
import os
import discord
from dotenv import load_dotenv
from discord.ext import tasks, commands
from datetime import datetime, timedelta
import time
import socketserver
import argparse
import re
import sys
import webbrowser
import requests
import requests.exceptions
from selenium import webdriver
import urllib.request
import urllib.parse
from scan import scan
from shutil import copyfile
import io
from io import StringIO

#list of titles, list of tuples, assumes not jagged
def table(headers, list, snippet):
    thickest = []
    for i in range(len(headers)):
        thickest.append(len(str(headers[i])) + 2)
    for tup in range(len(list)):
        asdf = len(list[tup])
        for i in range(len(list[tup])):
            thickest[i] = max(thickest[i], len(str(list[tup][i]))+2)
    result = "```\n"
    if not snippet:
        result = ""
    result += make_line(thickest)+"\n"
    result += make_row(headers, thickest)+"\n"
    for t in list:
        result += make_line(thickest)+"\n";
        result += make_row(t, thickest)+"\n";
    result += make_line(thickest);
    if not snippet:
        return result
    return result+"\n```";

def make_line(thickest):
    ans = "+"
    for i in thickest:
        for j in range(i):
            ans += "-"
        ans += "+"
    return ans;

def make_row(tup, thickest):
    ans = "|"
    for i in range(len(tup)):
        ans += " "+pad(str(tup[i]), thickest[i] - 1)+"|"
    return ans

def pad(str, l):
    while len(str) < l:
        str += " ";
    return str;
