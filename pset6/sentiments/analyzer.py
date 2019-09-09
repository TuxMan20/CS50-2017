import nltk

class Analyzer():
    """Implements sentiment analysis."""


    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        self.good = set()
        self.bad = set()

        file = open(positives, "r")

        for line in file:
            if str(line).isalpha and line[0] != ";":
                self.good.add(line.rstrip("\n"))
        file.close()


        file = open(negatives, "r")

        for line in file:
            if str(line).isalpha and line[0] != ";":
                self.bad.add(line.rstrip("\n"))

        file.close()

        self.tokenizer = nltk.tokenize.TweetTokenizer()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

    ## Iterates each words in the inputed text, and checks if each words is in the "good" or "bad" set
    ## No need to check for numbers or special characters because they will simply be marked as "neutral"


        ##token = nltk.word_tokenize(text)

        token = self.tokenizer.tokenize(text)

        score = 0

        for word in token:
            if word.lower() in self.good:
                score += 1
            elif word.lower() in self.bad:
                score -= 1
            else:
                score = score

        return score


