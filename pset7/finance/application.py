from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    rows = db.execute("SELECT * FROM users WHERE id = :user", user = session["user_id"]) ## Stores the current user info
    uhistory = db.execute("SELECT * FROM portfolio WHERE owner = :user",  user = session["user_id"]) ## Stores the user's transactions
    ucash = round(rows[0]["cash"], 2)
    uTotalStocksList = db.execute("SELECT owner, SUM(total) as 'Total Stocks' FROM portfolio WHERE owner = :user", user = session["user_id"])
    ## How to name the result of a query to create a temporary reference (Alias): https://www.w3schools.com/sql/sql_alias.asp

    if uTotalStocksList[0]["Total Stocks"] == None:
        uTotalStocks = 0
    else:
        uTotalStocks = uTotalStocksList[0]["Total Stocks"]


    return render_template("index.html", history = uhistory, uname = rows[0]["username"],
    cash = ucash, totalStocks = uTotalStocks)
    ## https://stackoverflow.com/questions/29525758/data-from-sqlite-to-an-html-table-in-a-flask-page
    ## Found a way to print the database content to a HTML page

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "GET": ## If function was accessed from a link, display the blank form
        return render_template("buy.html")

    elif request.method == "POST": ## If function was accessed from the button
        if request.form["symbol"] == "" or request.form["amount"] == "": ## Make sure no fields are blank
            return apology("All fields are mandatory")

        else:
            rows = db.execute("SELECT * FROM users WHERE id = :user", user = session["user_id"]) ## Stores the current user info
            cash = rows[0]["cash"] ## Gets the cash amount in a more managable variable
            quote = lookup(request.form["symbol"]) ## Gets the symbol infos: price, name and symbol
            if quote == None:
                return apology("Quote symbol does not exist")

            ## Check if the user has enough money in the bank to buy
            if cash < (float(quote["price"]) * float(request.form["amount"])):
                return apology("Not enough funds to complete purchase")
            else:
                db.execute("INSERT into portfolio (owner, symbol, value, amount, total) VALUES (:owner, :symbol, :value, :amount, :total)",
                owner = session["user_id"], symbol = quote["symbol"], value = quote["price"], amount = request.form["amount"],
                total = float(quote["price"]) * float(request.form["amount"]) )

                db.execute("UPDATE users SET cash = cash - :total WHERE id = :user",
                total = float(quote["price"]) * float(request.form["amount"]), user = session["user_id"])
                db.execute("INSERT INTO history (owner, symbol, amount, value, total, action) VALUES(:owner, :symbol, :amount, :value, :total, 'BOUGHT')",
                owner = session["user_id"], symbol = quote["symbol"], amount = request.form["amount"], value = quote["price"],
                total = float(request.form["amount"]) * float(quote["price"]))

                return render_template("bought.html", amount = request.form["amount"], symbol = quote["symbol"],
                total = float(quote["price"]) * float(request.form["amount"]))

    return apology("Server error")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    uHistory = db.execute("SELECT * from history WHERE owner = :user ORDER BY date DESC", user = session["user_id"])

    return render_template("history.html", history = uHistory)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("Wrong password,fool!")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    elif request.method == "POST":
        if request.form["symbol"] == "":
            return apology("Search field cannot be blank")

        try:
            quote = lookup(request.form["symbol"])
        except:
            return apology("Quote symbol does not exist")
        if quote == None:
            return apology("Quote symbol does not exist")
        else:
            return render_template("quoted.html", name = quote["name"], price = quote["price"], symbol = quote["symbol"])

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    ##TODO: PREVENT DUPLICATE USER NAMES
    ##TODO: PREVENT USERNAMES & PASSWORDS THAT ARE TOO LONG

    if request.method == "POST": ## If the user access the function through the button, it activates the registering
        if request.form["username"] =="" or request.form["password"] =="" or request.form["confirm"] =="":
            return apology("All fields are mandatory")
        elif request.form["password"] != request.form["confirm"]:
            return apology("Password and confirmation do not match")
        else:
            db.execute("INSERT INTO \'users\' (\'username\', \'hash\') VALUES (:username, :password)",
            username = request.form['username'], password = pwd_context.hash(request.form['password']))
            return apology("You are now registered")
    else:
        return render_template("register.html") ## If the user access the function from a link, it displays the blank form


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    rows = db.execute("SELECT * FROM users WHERE id = :user", user = session["user_id"]) ## Stores the current user info
    uhistory = db.execute("SELECT * FROM portfolio WHERE owner = :user",  user = session["user_id"]) ## Stores the user's transactions

    if request.method == "GET":
        return render_template("sell.html", history = uhistory)

    if request.method == "POST":
        try:
            if request.form["amount"] == "" or int(request.form["amount"]) < 1:
                return apology("Amount of stocks to be sold must be greater than 0")
        except ValueError:
            return apology("Numbers and letters in the right field")

        else:
            try:
                quote = lookup(request.form["symbol"])
            except:
                return apology("Quote symbol does not exist")
            if quote == None:
                return apology("Quote symbol does not exist")

            valueSold = float(request.form["amount"]) * float(quote["price"])
            toSell = int(request.form["amount"])

            totalStocks = db.execute("SELECT SUM(amount) as 'Total Stocks' FROM portfolio WHERE owner = :user AND symbol = :quote",
            user = session["user_id"], quote = quote["symbol"])

            if totalStocks[0]["Total Stocks"] == None or totalStocks[0]["Total Stocks"] == 0:
                return apology("You don't have any shares of that company")
            elif int(totalStocks[0]["Total Stocks"]) < int(request.form["amount"]):
                return apology("Not enough shares to sell")


            stocksSorted = db.execute("SELECT * FROM portfolio WHERE owner = :user AND symbol = :quote ORDER BY amount DESC",
            user = session["user_id"], quote = quote["symbol"])


            for rows in range(0, len(stocksSorted)):
                curAmount = int(stocksSorted[rows]["amount"])
                if toSell == 0:
                    break
                while curAmount > 0 and toSell > 0:
                    db.execute("UPDATE portfolio SET amount = amount - 1 WHERE id = :id", id = stocksSorted[rows]["id"])
                    toSell = toSell - 1
                    curAmount = curAmount - 1

            ## Deletes the rows where the amount is 0, Updates the total value of a row and ADDS the cash to the user account
            db.execute("DELETE from portfolio WHERE amount = 0")
            db.execute("UPDATE portfolio SET total = amount * value WHERE symbol = :symbol AND owner = :user",
            symbol = request.form["symbol"], user = session["user_id"])
            db.execute("UPDATE \'users\' SET \'cash\' = cash + :sold WHERE id = :user", sold = float(valueSold), user = session["user_id"])


            db.execute("INSERT INTO history (owner, symbol, amount, value, total, action) VALUES(:owner, :symbol, :amount, :value, :total, 'SOLD')",
            owner = session["user_id"], symbol = quote["symbol"], amount = request.form["amount"], value = quote["price"],
            total = float(request.form["amount"]) * float(quote["price"]))

            ## db.execute("UPDATE \'portfolio\' SET amount = amount - :amount WHERE \'symbol\' = :quote AND \'amount\' >= :amount AND \'owner\' = :user", quote = quote["symbol"], amount = int(request.form["amount"]), user = session["user_id"])

            return render_template("sold.html", amount = request.form["amount"], symbol = quote["symbol"],
                total = round(float(quote["price"]) * float(request.form["amount"]), 2))

