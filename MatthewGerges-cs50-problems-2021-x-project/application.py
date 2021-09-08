import os

from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session

from helpers import apology, componentcount, setvector
#, dotvectors, crossvectors

# Configure application
app = Flask(__name__)

@app.route("/", methods = ["GET", "POST"])
def index():
    
    if request.method == "GET":
        return render_template("calc.html")
    
    else:
        vector1 = request.form.get("vector1")
        vector2 = request.form.get("vector2")
        choice = request.form.get("choice")
        #print(vector1)
        #print(vector2)
        components1 = componentcount(vector1)
        components2 = componentcount(vector2)
        
        if (components1 != components2):
            return apology("Both vectors must have the same number of components", 400)
            # return
            
        vi = setvector(vector1)
        vf = setvector(vector2)
        if choice == "crossprod":
            '''
            print("vi", vi)
            for i in range(len(vi)):
                print(vi[i])
            '''
            
            crossprod1 = (vi[1] * vf[2] - vi[2] * vf[1]) 
            crossprod2 = (vi[2] * vf[0] - vi[0] * vf[2])
            crossprod3 = (vi[0] * vf[1] - vi[1] * vf[0])
            print("cross prod is", crossprod1, ",", crossprod2, ",", crossprod3)
            answer = f"({crossprod1}, {crossprod2}, {crossprod3})"
            return render_template("success.html", answer = answer)
            
        elif choice == "dotprod":
            answer = vi[0] + vf[0] + vi[1] + vf[1] + vi[2] + vf[2]
            return render_template("success.html", answer = answer)            
            
            
            
            
            
            '''
            setup = setvectors(vector1, vector2, components1)
            return setup
            '''
            
            
        