import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")
# Here we are creating a database equal to the SQL birthday database

@app.route("/", methods=["GET", "POST"])
# / is the default route - the index homepage
# 2 methods are allowed on the homepage - get which displays the content of the URL and post which allows users to submit the form
def index():
    # If the user submits the form (using POST), store their name, month and day entered as variables
    if request.method == "POST":
        
        #These variables are created by accessing the names of the inputs in the index.html file
        name = request.form.get("name")
        month = request.form.get("birthmonth")
        day = request.form.get("birthday")
        id = request.form.get("id")
        act = request.form.get("act")
        
        #allow a user to register or deregister based on what they typed in the act field
        if act.lower() == "deregister":
            # Forget the person and their data (birthday)
            db.execute("DELETE FROM birthdays WHERE id = ?", id)

        
        # if not name or not birthday:
        
        # TODO: Add the user's entry into the database
        # enter the name, month and day variables of the user into the sql database
        else:
            # only if you give a new unique id (number), you can register
            if id:
                db.execute("INSERT INTO birthdays (name, month, day, id) VALUES(?, ?, ?, ?)", name, month, day, id)
        
        # This line confirms their birthday entry/form submission; it reloads the page
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html (via GET! before a user submits)

        # Bdays is a list; a vraible that is set equal to the table from the SQL database
        Bdays = db.execute("SELECT * FROM birthdays")
        # select * = select all rows
        # direct the user to the index.html page; the index page will use a Bdays variable somewhere in there
        # we are passing this variable based on our query and work in this application.py file
        return render_template("index.html", Bdays = Bdays)