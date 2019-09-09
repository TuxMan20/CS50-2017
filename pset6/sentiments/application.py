from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer
from nltk import tokenize
import nltk
import os
import sys

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)


    positive, negative, neutral = 0.0, 0.0, 0.0

    if tweets is None or len(tweets) < 1:
        return redirect(url_for("index"))

    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")


    # instantiate analyzer (imports the lists of words)
    analyzer = Analyzer(positives, negatives)

    # Iterates over each tweets, sends them to be analyzed. Score is returned and
    # corresponding adjective is incremented
    for eachTweet in tweets:
        score = analyzer.analyze(str(eachTweet))
        if score > 0.0:
            positive  = positive + 1
        elif score < 0.0:
            negative = negative + 1
        else:
            neutral = neutral + 1


    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
