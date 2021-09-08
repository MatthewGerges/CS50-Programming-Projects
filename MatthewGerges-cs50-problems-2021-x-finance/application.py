import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

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


@app.route("/")
@login_required
# @loginrequired is a decorator that requires a user to be logged in to go to the index page
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE buyer = ? AND amount != ?", username, 0)
    cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
    cash = cash[0]['cash']
    cash = round(cash, 2)
    
    totalALL = cash
    
    stocktotals = db.execute("SELECT valuetotal FROM stocks WHERE buyer = ? and amount != ?", username, 0)

    for stocktot in stocktotals:
        # print(stocktot['valuetotal'])
        totalALL += stocktot['valuetotal']
                
    if (stocks != None):
        return render_template("index.html", stocks=stocks, cash=cash, totalALL=totalALL)
    
    # return apology("TODO")
    # apology function returns error message in general
    else:
        return render_template("success.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    
    else:
       
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("shares must be a posative integer", 400)
            
        money = db.execute("SELECT cash FROM users WHERE username = ?", username)
        
        cash = money[0]['cash']

        # we have to include [0] because money is a LIST of dictionaries

        amount = request.form.get("shares")
        share = request.form.get("symbol")
        
        if not amount or not share:
            return apology("One or more fields were left blank", 400)
        
        if int(amount) <= 0:
            return apology("Amount must be greater than 0", 400)
        
        amount = int(amount)

        '''    
        if (isinstance(amount, int) != True):
            return apology("Amount must be an integer", 400)
        '''
        
        info = lookup(share)
        
        if (info == None):
            return apology("The stock you are trying to buy does not exist")
        
        price = info['price']
        name = info['name']
        price = float(price)
        print(price)
        
        vatotal = price * amount
        
        cost = amount * price
        total = cash - cost
        
        if (total > 0):
            
            db.execute("UPDATE users SET cash = ? WHERE username = ?", total, username)
            
            #db.execute("INSERT INTO stocks (shares, amount, buyer, name) VALUES(?, ?, ?, ?)", share, amount, username, name)
            #db.execute("UPDATE stocks SET (shares, amount, buyer, name) VALUES(?, ?, ?, ?)", share, amount, username, name)
            uniqueshare = db.execute("SELECT shares FROM stocks WHERE shares = ? AND buyer = ?", share, username)
            
            if not uniqueshare:
                db.execute("INSERT INTO stocks (shares, amount, buyer, name, price, valuetotal) VALUES(?, ?, ?, ?, ?, ?)", 
                           share, amount, username, name, price, round(vatotal, 2))            
                #db.execute("UPDATE stocks SET shares = ?, amount = ?, buyer = ?, name = ?", share, amount, username, name)
            else:
                number = db.execute("SELECT amount FROM stocks WHERE shares = ? AND buyer = ? LIMIT 1", share, username)
                number = number[0]['amount']
                pretotal = db.execute("SELECT valuetotal FROM stocks WHERE shares = ? AND buyer = ? LIMIT 1", share, username)
                pretotal = pretotal[0]['valuetotal']
                combinedtotal = round(vatotal + pretotal, 2)
                db.execute("UPDATE stocks SET amount = ?, price = ?, valuetotal = ? WHERE shares = ? AND buyer = ? AND name = ?", 
                           amount + number, price, combinedtotal, share, username, name)
            
            rn = datetime.datetime.now()
            
            #print("Current date and time = %s" %e)
            db.execute("INSERT INTO history (symbol, amount, price, time, buyer) VALUES(?, ?, ?, ?, ?)", 
                       share, amount, price, rn, username)
            
            return redirect("/")
            

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    pastevents = db.execute("SELECT * FROM history WHERE buyer = ?", username)
    return render_template("history.html", pastevents=pastevents)
    

@app.route("/login", methods=["GET", "POST"])
# Get gives me the login page so i can type them in
# post submits the login data
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST); the user tried to submit data
    if request.method == "POST":
        
        global username
        username = request.form.get("username")

        # Ensure username was submitted (did they put something in that field)
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct, length of rows means user exists
        # check if the password hashes match up
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # if only 1 row came back from db execute then row[0] gets us the one and only row representing the user THEN get the value of the id column for that row

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect); didn't submit login informatio
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
        quote = request.form.get("symbol")
        quote = lookup(quote)
        
        if (quote == None):
            return apology("The stock you are looking up does not exist")
            
        # quote is a python dictionary, so we index the keys to access the values
        return render_template("value.html", quote=quote)
        
    else:
        return render_template("quote.html")
        
    """Get stock quote."""
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # insert the new user into the users table
        username = request.form.get("username")
        users = db.execute("SELECT username FROM users")
        print(username)
        for user in users:
            yourname = user['username']
            if yourname == username:
                return apology("Choose a different username as this one already exists", 400)
        
        # cash = 10000
        # no need for the above line because it's a default value
        password = request.form.get("password")
        passcon = request.form.get("confirmation")
        KEYLOCK = generate_password_hash(password)
        KEYCON = generate_password_hash(passcon)
        
        passcode = generate_password_hash(password)
        #passcon = generate_password_hash(passcon)
        
        # change password in brackets to request . get form
        if not username:
            return apology("must provide username", 400)
        
        if not password:
            return apology("must provide password", 400)
        
        # change to if KEYLOCK == KEYCON
        if password != passcon:
            return apology("password and password confirmation do not match")
        
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, passcode)
        
        '''
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, passcode)
        
        if not registerstatus:
            return apology("Choose a different username as this one already exists")
        '''
            
        '''
        #This was my initial attempt to tell users to choose a different username; idk why it didnt work
        #instead if they put the username in, they can't submit
        if username in users:
            return apology("Choose a different username as this one already exists", 400)
        
        if username not in users:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, passcode)
        '''
        
        return redirect("/")

    # if requested via get
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        selections = db.execute("SELECT * FROM stocks WHERE buyer = ?", username)
        return render_template("sell.html", selections=selections)
    else:
        choice = request.form.get("symbol")
        symbol = request.form.get("shares")
        
        possible_choices = db.execute("SELECT shares FROM stocks WHERE buyer = ?", username)
        choice_number = db.execute("SELECT amount FROM stocks WHERE buyer = ? and shares = ?", username, choice)
        
        existing_stocks = []
        for posschoice in possible_choices:
            selection = posschoice['shares']
            existing_stocks.append(selection)
            #existing_stocks = posschoice['shares']
        
        if not choice or not symbol:
            return apology("A field was left blank")
            
        symbol = int(symbol)
        choice_number = choice_number[0]['amount']
        
        if choice not in existing_stocks:
            return apology("Sorry you don't own that stock")
        
        if (symbol > choice_number):
            return apology("Sorry you don't own enough " + choice + " stocks to sell.")
        
        stock_info = lookup(choice)
        stock_price = stock_info['price']
        
        valuesold = stock_price * symbol
        valuesold = round(valuesold, 2)
        
        og_amount = db.execute("SELECT amount FROM stocks WHERE shares = ? and buyer = ?", choice, username)
        og_amount = og_amount[0]['amount']
        cash = db.execute("SELECT cash FROM users WHERE username = ?", username)
        cash = cash[0]['cash']
        
        valtotal = db.execute("SELECT valuetotal FROM stocks WHERE shares = ? and buyer = ?", choice, username)
        
        valtotal = valtotal[0]['valuetotal']
        
        db.execute("UPDATE stocks SET amount = ?, valuetotal = ? WHERE shares = ? AND buyer = ?", 
                   og_amount - symbol, valtotal - valuesold, choice, username)
        
        if og_amount - symbol == 0:
            db.execute("DELETE FROM stocks WHERE buyer = ? AND amount = ?", username, 0)
        
        db.execute("UPDATE users SET cash = ? WHERE username = ?", cash + valuesold, username)
        
        negamount = -1 * symbol
        rn = datetime.datetime.now()
        
        db.execute("INSERT INTO history (symbol, amount, price, time, buyer) VALUES(?, ?, ?, ?, ?)", 
                   choice, negamount, stock_price, rn, username)

        return redirect("/")


@app.route("/success", methods=["GET", "POST"])
def success():
    return render_template("success.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

'''
# schema table set up for cs50 finance
CREATE TABLE users (id INTEGER, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00, PRIMARY KEY(id));
CREATE UNIQUE INDEX username ON users (username);
'''


# check_password_hash('pbkdf2:sha1:1000$tYqN0VeL$2ee2568465fa30c1e6680196f8bb9eb0d2ca072d', 'foobar')

'''
export API_KEY=pk_218e8d9721c44b67a9544ed1affd62cd 
'''

'''
@app.route("/search")
def search():
    shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", "%" + request.args.get("q") + "%")


'''