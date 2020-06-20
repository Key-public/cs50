import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == "POST":
        if request.form.get("action") == "sell":
            return sell()
        elif request.form.get("action") == "buy":
            return buy()
        else:
            return render_template("index.html", message="Ни BUY ни SELL")
    else:
        """Show portfolio of stocks"""
        user_id = session.get("user_id")
        shares = db.execute("select symbol, company_name, sum(shares) as shares from deals where user_id = :user_id group by symbol", user_id=user_id)
        cash = db.execute("select cash from users where id = :user_id", user_id=user_id)
        cash = cash[0]["cash"]
        total = cash
        for share in shares:
            share_prices = lookup(share["symbol"])
            share_prices = share_prices["price"]
            share.update({"share_price" : share_prices, "total_price" : share_prices * share["shares"]})
            total = total + share["total_price"]
            share["share_price"], share["total_price"] = usd(share["share_price"]), usd(share["total_price"])
        return render_template("index.html", cash=usd(cash), total=usd(total), shares=shares)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        result = lookup(request.form.get("symbol"))
        user_id = session.get("user_id")
        company_name = result["name"]
        symbol = result["symbol"]
        price = result["price"]
        if not result:
            return apology("Sorry, there is no symbol like that")
        elif int(shares) <= 0:
            return apology("You have to choose at least 1 stock")
        else:
            have_cash = db.execute("select cash from users where id = :id", id=user_id)
            have_cash = have_cash[0]["cash"]
            need_cash = result["price"] * float(shares)
            if have_cash >= need_cash:
                db.execute("insert into deals (user_id, symbol, company_name, shares, share_price, total_price) VALUES (:user, :symbol, :company_name, :shares, :price, :total)", user=user_id, symbol=symbol, company_name=company_name, shares=shares, price=price, total=need_cash)
                db.execute("update users set cash = :new_cash where id = :user", new_cash = have_cash - need_cash, user=user_id)
                return render_template("buy.html", message="Congratulation!")
            else:
                return apology("Sorry, you don't have enough cash for this deal")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    return render_template("history.html", shares=db.execute("select * from deals where user_id = :user_id", user_id = session.get("user_id")))


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        result = lookup(request.form.get("symbol"))
        if not result:
            return render_template("quote.html", message="Sorry, there is no symbol like that")
        else:
            name = result["name"]
            symbol = result["symbol"]
            price = result["price"]
            return render_template("quoted.html", name=name, symbol=symbol, price=usd(price))
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        """Render an apology if the user’s input is blank or the username already exists."""
        if not username:
            return apology("must provide name", 403)
        """Render an apology if either input is blank or the passwords do not match"""
        if not password:
            return apology("must provide password", 403)
        if confirmation != password:
            return apology("must confirm password", 403)
        if not db.execute("select username from users where username = :username", username=username):
            db.execute("insert into users (username, hash, cash) values (:username, :hash)", username=username, hash=generate_password_hash(password))
            return login()
        else:
            return apology("name is already taken", 403)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session.get("user_id")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        print(symbol)
        shares = request.form.get("shares")
        print(shares)
        if not symbol or not shares or int(shares) <= 0:
            return apology("You have to choose at least 1 stock")
        shares = int(shares)
        have_shares = db.execute("select sum(shares) as shares from deals where user_id=:user_id and symbol=:symbol", user_id=user_id, symbol=symbol)[0]["shares"]
        if shares > have_shares:
            return apology("You've tried to sell more than you have")
        parsed_share_info = lookup(symbol)
        total_income = float(shares) * parsed_share_info["price"]
        db.execute("insert into deals (user_id, symbol, company_name, shares, share_price, total_price) VALUES (:user_id, :symbol, :company_name, :shares, :price, :total_income)", user_id=user_id, symbol=parsed_share_info["symbol"], company_name=parsed_share_info["name"], shares=-shares, price=parsed_share_info["price"], total_income=total_income)
        cash = db.execute("select cash from users where id=:user_id", user_id=user_id)[0]["cash"]
        new_cash = cash + total_income
        db.execute("update users set cash=:new_cash where id=:user_id", new_cash=new_cash, user_id=user_id)
        return render_template("sell.html", message="Ok")
    else:
        have_symbols = db.execute("select symbol, sum(shares) as positive_shares from deals where user_id = :user_id group by symbol having positive_shares > 0", user_id=user_id)
        return render_template("sell.html", have_symbols=have_symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
